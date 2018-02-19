#include <alloc.h>

#include "mm.hpp"
#include "proto.hpp"

#ifndef _MEDIAN1x3
#define _MEDIAN1x3

#include "filter.hpp"

class Median1x3 : public Filtering
{
 public:
  Median1x3(long ScrHandler,int dx, int dy,int sentAdr);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif


ClassType Median1x3 :: isA()
{
 return _FMedian1x3;
}

Median1x3 :: Median1x3(long ScrHandler,int dx,int dy,int sentAdr)
           : Filtering(ScrHandler,dx,dy,sentAdr)
{
 CurentY=1;
 pScr = (unsigned char *)malloc( DX*3 );
 pDst = (unsigned char *)malloc( DX );
}

void Median1x3 :: Run(void)
{
 int i;
 unsigned char *pTmp;
 unsigned char fa[3];

 if(CurentY < DY - 1)
 {
  MRead(scrHandler,(char *)pScr,(long)(CurentY-1)*DX,DX*3);

  for ( i = 0; i < DX ; i++ )
  {
   pTmp =  pScr + i;

   fa[0] =*(pTmp ); pTmp += DX;
   fa[1] =*(pTmp ); pTmp += DX;
   fa[2] =*(pTmp );

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
   MCopyRectangle(dstHandler,DX,DY,1,1,scrHandler,DX,DY,1,1,DX-2,DY-2 );
   SendMSGCmd(FILTER_LOCK_OUT,SentAddress,RegisterNumber);
   Sent++;
  }
}
