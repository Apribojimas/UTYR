#include <alloc.h>

#include "mm.hpp"
#include "proto.hpp"

#ifndef _MEDIAN3x3
#define _MEDIAN3x3

#include "filter.hpp"

class Median3x3 : public Filtering
{
 public:
  Median3x3(long ScrHandler,int dx, int dy,int sentAdr);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif


ClassType Median3x3 :: isA()
{
 return _FMedian3x3;
}

Median3x3 :: Median3x3(long ScrHandler,int dx,int dy,int sentAdr)
           : Filtering(ScrHandler,dx,dy,sentAdr)
{
 CurentY=1;
 pScr = (unsigned char *)malloc( DX*3 );
 pDst = (unsigned char *)malloc( DX );
}

void Median3x3 :: Run(void)
{
 int i,x,y;
 unsigned char *pTmp;
 unsigned char fa[9];
 unsigned char tempo;

 if(CurentY < DY - 1)
 {
  MRead(scrHandler,(char *)pScr,(long)(CurentY-1)*DX,DX*3);

  for ( i = 1; i < DX - 1; i++ )
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

//   MinMaxSort(fa,9);
   for( x=0; x<5; x++ )
    for( y=x+1; y<9; y++ )
     if ( fa[y] > fa[x] )
     {
      tempo = fa[y];
      fa[y] = fa[x];
      fa[x] = tempo;
     }
   *(pDst + i)=fa[4];
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
