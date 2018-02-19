#include <alloc.h>

#include "mm.hpp"
#include "proto.hpp"

#ifndef _MEDIAN5x5
#define _MEDIAN5x5

#include "filter.hpp"

class Median5x5 : public Filtering
{
 public:
  Median5x5(long ScrHandler,int dx, int dy,int sentAdr);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif


ClassType Median5x5 :: isA()
{
 return _FMedian5x5;
}

Median5x5 :: Median5x5(long ScrHandler,int dx,int dy,int sentAdr)
           : Filtering(ScrHandler,dx,dy,sentAdr)
{
 CurentY=2;
 pScr = (unsigned char *)malloc( DX*5 );
 pDst = (unsigned char *)malloc( DX );
}

void Median5x5 :: Run(void)
{
 int i,x,y;
 unsigned char *pTmp;
 unsigned char fa[25];
 unsigned char tempo;

 if(CurentY < DY - 2)
 {
  MRead(scrHandler,(char *)pScr,(long)(CurentY-2)*DX,DX*5);

  for ( i = 2; i < DX - 2; i++ )
  {
   pTmp =  pScr + i;

   fa[0] =*(pTmp - 2);
   fa[1] =*(pTmp - 1);
   fa[2] =*(pTmp    );
   fa[3] =*(pTmp + 1);
   fa[4] =*(pTmp + 2);
   pTmp += DX;

   fa[5] =*(pTmp - 2);
   fa[6] =*(pTmp - 1);
   fa[7] =*(pTmp    );
   fa[8] =*(pTmp + 1);
   fa[9] =*(pTmp + 2);
   pTmp += DX;

   fa[10] =*(pTmp  - 2);
   fa[11] =*(pTmp  - 1);
   fa[12] =*(pTmp     );
   fa[13] =*(pTmp  + 1);
   fa[14] =*(pTmp  + 2);
   pTmp += DX;

   fa[15] =*(pTmp  - 2);
   fa[16] =*(pTmp  - 1);
   fa[17] =*(pTmp     );
   fa[18] =*(pTmp  + 1);
   fa[19] =*(pTmp  + 2);
   pTmp += DX;

   fa[20] =*(pTmp  - 2);
   fa[21] =*(pTmp  - 1);
   fa[22] =*(pTmp     );
   fa[23] =*(pTmp  + 1);
   fa[24] =*(pTmp  + 2);

//   MinMaxSort(fa,25);
   for( x=0; x<13; x++ )
    for( y=x+1; y<25; y++ )
     if ( fa[y] > fa[x] )
     {
      tempo = fa[y];
      fa[y] = fa[x];
      fa[x] = tempo;
     }
   *(pDst + i)=fa[12];
  }
  MWrite(dstHandler,(char *)pDst,(long)CurentY*DX,DX);
  CurentY++;
 }
 else
  if(!Sent)
  {
   MCopyRectangle(dstHandler,DX,DY,2,2,scrHandler,DX,DY,2,2,DX-4,DY-4 );
   SendMSGCmd(FILTER_LOCK_OUT,SentAddress,RegisterNumber);
   Sent++;
  }
}
