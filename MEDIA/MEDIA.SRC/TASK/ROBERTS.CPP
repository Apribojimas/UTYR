#include <alloc.h>
#include <math.h>

#include "mm.hpp"
#include "proto.hpp"
#include "roberts.hpp"

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

#ifndef _ROBERTS
#define _ROBERTS


#include "vcmd.hpp"
#include "filter.hpp"

class Roberts : public Filtering
{
 int Type;
 public:
  Roberts(long ScrHandler,int dx, int dy,int sentAdr,int Type = MAX);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif

ClassType Roberts :: isA()
{
 return _Roberts;
}

Roberts :: Roberts(long ScrHandler,int dx,int dy,int sentAdr,int type)
          : Filtering(ScrHandler,dx,dy,sentAdr)
{
 CurentY=1;
 pScr = (unsigned char *)malloc( DX*3 );
 pDst = (unsigned char *)malloc( DX );

 Type = type;
}

void Roberts :: Run(void)
{
 int i, add;
 int h1, h2;

 if(CurentY < DY - 1)
 {
  MRead(scrHandler,(char *)pScr,(long)(CurentY-1)*DX,DX*3);
  for ( i = 1; i < DX - 1; i++ )
  {
/*
-1, 0  !  0, 1
 0, 1  ! -1, 0
*/
/* vasia */
   h1 = *(pScr + i + 1 + DX) - *(pScr + i);
   h2 = *(pScr + i + 1) - *(pScr + i + DX);
   switch(Type)
   {
    case SQRT:
         add = sqrt((long)h1 * h1 + (long)h2 * h2);
         break;
    case MAX:
         add = max(abs(h1),abs(h2));
         break;
    case ABS:
         add = (int)(abs(h1) + abs(h2)) / 2;
         break;
   }
   *(pDst + i) = add;
  }
  *(pDst) = *(pDst + 1);
  *(pDst + DX - 1) = *(pDst + DX - 2);
  MWrite(dstHandler,(char *)pDst,(long)CurentY*DX,DX);
  CurentY++;
 }
 else
  if(!Sent)
  {
   MRead(dstHandler,(char *)pDst,(long)DX,DX);
   MWrite(dstHandler,(char *)pDst,0L,DX);
   MRead(dstHandler,(char *)pDst,(long)(DY - 2)*DX,DX);
   MWrite(dstHandler,(char *)pDst,(long)(DY - 1)*DX,DX);

   MCopyRectangle(dstHandler,DX,DY,0,0,scrHandler,DX,DY,0,0,DX,DY);
   SendMSGCmd(FILTER_LOCK_OUT,SentAddress,RegisterNumber);
   Sent++;
  }
}
