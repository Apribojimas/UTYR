#include <alloc.h>

#include "mm.hpp"
#include "proto.hpp"

#ifndef _MEDIAN3x1
#define _MEDIAN3x1

#include "filter.hpp"

class Median3x1 : public Filtering
{
 public:
  Median3x1(long ScrHandler,int dx, int dy,int sentAdr);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif


ClassType Median3x1 :: isA()
{
 return _FMedian3x1;
}

Median3x1 :: Median3x1(long ScrHandler,int dx,int dy,int sentAdr)
           : Filtering(ScrHandler,dx,dy,sentAdr)
{
 CurentY=0;
 pScr = (unsigned char *)malloc( DX );
 pDst = (unsigned char *)malloc( DX );
}

void Median3x1 :: Run(void)
{
 int i;
 unsigned char *pTmp;
 unsigned char fa[3];

 if(CurentY < DY)
 {
  MRead(scrHandler,(char *)pScr,(long)CurentY*DX,DX);

  for ( i = 1; i < DX -1; i++ )
  {
   pTmp =  pScr + i;

   fa[0] =*(pTmp - 1);
   fa[1] =*(pTmp    );
   fa[2] =*(pTmp + 1);

   *(pDst + i)=fa[4];

   if(fa[0] == fa[1] || fa[0] == fa[2])
     *( pDst + i )=fa[0];
   else
    if(fa[1] == fa[2])
     *( pDst + i )=fa[1];
    else
     if(fa[0] < fa[1])
      if(fa[1] < fa[2])
       *( pDst + i )=fa[1];     // 123
      else
       if(fa[0] < fa[2])
        *( pDst + i )=fa[2];    // 132
       else
        *( pDst + i )=fa[0];    // 231
     else
      if(fa[0] < fa[2])
       *( pDst + i )=fa[0];     // 213
      else
       if(fa[1] < fa[2])
        *( pDst + i )=fa[2];    // 312
       else
        *( pDst + i )=fa[1];    // 321
  }
  MWrite(dstHandler,(char *)pDst,(long)CurentY*DX,DX);
  CurentY++;
 }
 else
  if(!Sent)
  {
   MCopyRectangle(dstHandler,DX,DY,1,0,scrHandler,DX,DY,1,0,DX-2,DY );
   SendMSGCmd(FILTER_LOCK_OUT,SentAddress,RegisterNumber);
   Sent++;
  }
}
