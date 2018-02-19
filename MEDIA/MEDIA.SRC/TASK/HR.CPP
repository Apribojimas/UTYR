#include <string.h>
#include <alloc.h>
#include <math.h>

#include "mm.hpp"
#include "proto.hpp"
#include "hr.hpp"

#ifndef _HISTOREDUCE
#define _HISTOREDUCE

#include "filter.hpp"

class HistoReduce : public Filtering
{
 long HistoGrama[256];
 int ColorCount;
 int BeginCount;
 int isEnd;
 int MinPlace;
 unsigned long Min;

public:
  ~HistoReduce();
  HistoReduce(long ScrHandler,int dx, int dy,int sentAdr,long Histo,int colorCount);


  virtual void Run(void);
  virtual ClassType isA();
  virtual int GetPercent(void);
private:
  void GetMinHisto(void);
  unsigned char GetValue(unsigned char *ptr);
  int GetColorCount(void);
};
#endif

ClassType HistoReduce :: isA()
{
 return _HistoReduce;
}

HistoReduce :: HistoReduce(long ScrHandler,int dx,int dy,int sentAdr,long Histo,int colorCount)
          : Filtering(ScrHandler,dx,dy,sentAdr)
{

 isEnd = 0;
 ColorCount = colorCount;

 MRead(Histo,(char huge *)HistoGrama,0l,256l*sizeof(long));
 MFree(Histo);

 GetMinHisto();
 BeginCount = GetColorCount();

 pScr = (unsigned char *)malloc(DX * 3);
 pDst = (unsigned char *)malloc( DX );
 CurentY=1;

}

HistoReduce :: ~HistoReduce(void)
{
}

int HistoReduce :: GetColorCount(void)
{
 int Count = 0;
 int i;

 for(i = 0;i < 256;i ++)
  {
   if(HistoGrama[i])
    Count ++;
  }

return Count;
}

int HistoReduce :: GetPercent(void)
{
 int tmp;

 if(Sent)
  return 100;

 tmp = GetColorCount();

return ((float)(BeginCount - tmp) / (BeginCount - ColorCount)) * 100;
}

void HistoReduce :: Run(void)
{
 int i;
 unsigned char *pTmp;
 unsigned char fa[9];

 if(CurentY >= DY - 1)
  {
   CurentY = 1;
   HistoGrama[MinPlace] = 0L;
   GetMinHisto();

   MRead(dstHandler,(char *)pDst,(long)DX,DX);
   MWrite(dstHandler,(char *)pDst,0L,DX);
   MRead(dstHandler,(char *)pDst,(long)(DY - 2)*DX,DX);
   MWrite(dstHandler,(char *)pDst,(long)(DY - 1)*DX,DX);
   MCopyRectangle(dstHandler,DX,DY,0,0,scrHandler,DX,DY,0,0,DX,DY);
  }

 if(!isEnd)
  {
   MRead(scrHandler,(char *)pScr,(long)(CurentY - 1)*DX,DX * 3);
   memcpy(pDst,pScr + DX,DX);
   for (i = 1; i < DX - 1;i ++)
    {
     if(*(pScr + i + DX) == MinPlace)
      {
       pTmp =  pScr + i;

       fa[0] =*(pTmp - 1);
       fa[1] =*(pTmp    );
       fa[2] =*(pTmp + 1);
       pTmp += DX;
       fa[3] =*(pTmp  - 1);
       fa[4] =*(pTmp     );
       fa[5] =*(pTmp  + 1);
       pTmp += DX;
       fa[6] =*(pTmp - 1);
       fa[7] =*(pTmp    );
       fa[8] =*(pTmp + 1);

       *(pDst + i) = GetValue(fa);
      }
    }

   *(pDst) = *(pDst + 1);
   *(pDst + DX - 1) = *(pDst + DX - 2);
   MWrite(dstHandler,(char *)pDst,(long)(CurentY)*DX,DX);
   CurentY++;
  }
 else
  if(!Sent)
  {
   SendMSGCmd(FILTER_LOCK_OUT,SentAddress,RegisterNumber);
   Sent++;
  }
}

void HistoReduce :: GetMinHisto(void)
{
 int Count = 0;
 int i;

 Min = -1;
 MinPlace = 0;
 for(i = 0;i < 256;i ++)
  {
   if(Min > HistoGrama[i] && HistoGrama[i])
    {
     Min = HistoGrama[i];
     MinPlace = i;
    }

   if(HistoGrama[i])
    Count ++;
  }

 if(Count <= ColorCount)
  isEnd = 1;
}

unsigned char HistoReduce :: GetValue(unsigned char *ptr)
{
 int i;

 int lmax;
 int lplace;
 unsigned char index[256];

 memset(index,0,256);
 for(i = 0;i < 9;i ++)
  if(ptr[i] != MinPlace)
   index[ptr[i]] ++;

 lmax = 0;
 lplace = 0;
 for(i = 0;i < 9;i ++)
  {
   if(lmax < index[ptr[i]])
    {
     lmax = index[ptr[i]];
     lplace = ptr[i];
    }
  }

 if(lmax)
  return lplace;


 for(i = 1;i < 255;i ++)
  {
   if(MinPlace + i <= 255)
    {
     if(HistoGrama[MinPlace + i])
      return MinPlace + i;
    }

   if(MinPlace - i >= 0)
    {
     if(HistoGrama[MinPlace - i])
      return MinPlace - i;
    }
  }

return MinPlace;

}
