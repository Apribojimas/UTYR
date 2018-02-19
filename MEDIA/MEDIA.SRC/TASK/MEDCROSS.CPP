#include <alloc.h>

#include "mm.hpp"
#include "proto.hpp"

#ifndef _MEDIANCROSS
#define _MEDIANCROSS

#include "filter.hpp"

class MedianCross : public Filtering
{
 public:
  MedianCross(long ScrHandler,int dx, int dy,int sentAdr);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif


ClassType MedianCross :: isA()
{
 return _FMedianCross;
}

MedianCross :: MedianCross(long ScrHandler,int dx,int dy,int sentAdr)
             : Filtering(ScrHandler,dx,dy,sentAdr)
{
 CurentY=1;
 pScr = (unsigned char *)malloc( DX*3 );
 pDst = (unsigned char *)malloc( DX );
}

void MedianCross :: Run(void)
{
 int i,x,y;
 unsigned char *pTmp;
 unsigned char fa[5];
 unsigned char tempo;

 if(CurentY < DY - 1)
 {
  MRead(scrHandler,(char *)pScr,(long)(CurentY-1)*DX,DX*3);

  for ( i = 1; i < DX - 1; i++ )
  {
   pTmp =  pScr + i;

   fa[0] =*(pTmp    );  pTmp += DX;
   fa[1] =*(pTmp - 1);
   fa[2] =*(pTmp    );
   fa[3] =*(pTmp + 1);  pTmp += DX;
   fa[4] =*(pTmp    );

   //MinMaxSort(fa,5);
   for( x=0; x<3; x++ )
    for( y=x+1; y<5; y++ )
     if ( fa[y] > fa[x] )
     {
      tempo = fa[y];
      fa[y] = fa[x];
      fa[x] = tempo;
     }
   *(pDst + i)=fa[2];
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
