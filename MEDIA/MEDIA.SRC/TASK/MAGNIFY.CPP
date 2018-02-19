#include <alloc.h>
#include <math.h>

#include "mm.hpp"
#include "proto.hpp"
#include "graph.hpp"
#include "magnify.hpp"
#include "images.hpp"

#define uchar unsigned char
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

void Rotate(long scrHandler,long dstHandler,int dx,int dy);

#ifndef _FMAGNIFY
#define _FMAGNIFY

#include "filter.hpp"

class Magnify : public Filter
{
 protected:
  long scrHandler;
  int scrdx;
  int scrdy;
  long dstHandler;
  int dstdx;
  int dstdy;
  long tmpHandler1;
  long tmpHandler2;
  int CurentX;
  int CurentY;
  char *pScr;
  char *pDst;
  int SentAddress;
  int Sent;
 public:
  Magnify(long ScrHandler,int ScrDx,int ScrDy,
          long DstHandler,int DstDx,int DstDy,
          int sentAdr);
  ~Magnify();
  virtual void Run(void);
  virtual ClassType isA();

  virtual int GetPercent(void);
};
#endif

ClassType Magnify :: isA()
{
 return _Magnify;
}

Magnify:: Magnify(long ScrHandler,int ScrDx,int ScrDy,
                  long DstHandler,int DstDx,int DstDy,
                  int sentAdr)
{
 scrHandler=ScrHandler;
 scrdx=ScrDx;
 scrdy=ScrDy;
 dstHandler=DstHandler;
 dstdx=DstDx;
 dstdy=DstDy;
 tmpHandler1 = MAlloc((long)scrdy*dstdx);
 tmpHandler2 = MAlloc((long)scrdy*dstdx);
 CurentX=0;
 CurentY=0;
 pScr = new char [max(max(scrdx,scrdy),max(dstdx,dstdy))];
 pDst = new char [max(max(dstdx,dstdy),max(scrdx,scrdy))];
 SentAddress = sentAdr;
 Sent = 0;
}

Magnify :: ~Magnify( )
{
 if( pScr != 0L )
  delete pScr;
 if( pDst != 0L )
  delete pDst;
 MFree(tmpHandler1);
 MFree(tmpHandler2);
}

void Magnify :: Run(void)
{
 if(CurentY < scrdy)
 {
  MRead(scrHandler,pScr,(long)scrdx*CurentY,scrdx);
  resample((uchar*)pScr,(uchar*)pDst,scrdx,dstdx);
  MWrite(tmpHandler1,pDst,(long)dstdx*CurentY,dstdx);
  CurentY++;
 }
 else
  if(CurentX < dstdx)
  {
   if(CurentX==0)
   {
    Rotate(tmpHandler1,tmpHandler2,dstdx,scrdy);
    MFree(tmpHandler1);
    tmpHandler1 = MAlloc((long)dstdy*dstdx);
   }
   MRead(tmpHandler2,pScr,(long)scrdy*CurentX,scrdy);
   resample((uchar*)pScr,(uchar*)pDst,scrdy,dstdy);
   MWrite(tmpHandler1,pDst,(long)dstdy*CurentX,dstdy);
   CurentX++;
  }
  else
   if(!Sent)
   {
    Rotate(tmpHandler1,dstHandler,dstdy,dstdx);
    SendMSGCmd(FILTER_LOCK_OUT,SentAddress,RegisterNumber);
    Sent++;
   }
}
/***********************************************************/
void Rotate(long scrHandler,long dstHandler,int dx,int dy)
{
 char huge *pScr;
 char huge *pDst;
 int i,count,memrow,readrow;

 pScr = FarMalloc(dx,dy,memrow,40);
 pDst = (char huge *)farmalloc((long)dx*memrow);

 for( count=0,readrow=0; ; count += readrow)
 {
  if(dy-count >= memrow)
   readrow = memrow;
  else
   readrow = dy-count;
  if(readrow <= 0)
   break;

  MRead(scrHandler,pScr,(long)count*dx,(long)dx*readrow);
  Rotate(pScr,pDst,dx,readrow);
  for(i=0;i<dx;i++)
   MWrite(dstHandler,pDst+(long)i*readrow,(long)i*dy+count,readrow);
 }
 farfree(pScr);
 farfree(pDst);
}

int Magnify :: GetPercent(void)
{
 if(Sent)
  return 100;
 if(CurentY < scrdy)
  return ((float)CurentY / scrdy) * 50;
 else
  return ((float)CurentX / dstdx) * 50 + 50;
}
