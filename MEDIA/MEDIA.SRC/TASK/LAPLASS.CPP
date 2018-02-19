#include <alloc.h>
#include <math.h>

#include "mm.hpp"
#include "proto.hpp"
#include "laplas.hpp"

#ifndef _LAPLAS
#define _LAPLAS

#include "vcmd.hpp"
#include "filter.hpp"

class Laplas : public Filtering
{
 int Type;
 public:
  Laplas(long ScrHandler,int dx, int dy,int sentAdr,int Type = CLASIC);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif

ClassType Laplas :: isA()
{
 return _Laplas;
}

Laplas :: Laplas(long ScrHandler,int dx,int dy,int sentAdr,int type)
          : Filtering(ScrHandler,dx,dy,sentAdr)
{
 CurentY=1;
 pScr = (unsigned char *)malloc( DX*3 );
 pDst = (unsigned char *)malloc( DX );

 Type = type;
}

void Laplas :: Run(void)
{
 int i,add;

 if(CurentY < DY - 1)
 {
  MRead(scrHandler,(char *)pScr,(long)(CurentY-1)*DX,DX*3);
  for ( i = 1; i < DX - 1; i++ )
  {
   switch(Type)
    {
     case CROSS:
          /*
            0,-1, 0
           -1, 4,-1
            0,-1, 0
          */
          add =(*(pScr + i + DX    ) * 4) -
                *(pScr + i         )-
	        *(pScr + i + DX * 2)-
	        *(pScr + i + DX - 1)-
                *(pScr + i + DX + 1);
          break;
     case DIAGONAL:
          /*
          -1, 0 ,-1
          0 , 4 , 0
          -1, 0 ,-1
          */
          add =(*(pScr + i + DX        ) * 4) -
                *(pScr + i - 1         ) -
                *(pScr + i + 1         ) -
	        *(pScr + i - 1 + DX * 2) -
	        *(pScr + i + 1 + DX * 2);
          break;
     case WEIGHT:
          /*
           1,-2, 1
          -2, 4,-2
           1,-2, 1
          */
          add =(*(pScr + i + DX        ) * 4) +
                *(pScr + i - 1         ) +
	        *(pScr + i + 1         ) +
	        *(pScr + i + 1 + DX * 2) +
  	        *(pScr + i - 1 + DX * 2) -
               (*(pScr + i             ) +
                *(pScr + i + 1 + DX    ) +
	        *(pScr + i - 1 + DX    ) +
	        *(pScr + i     + DX * 2)) * 2;
          break;
     case CLASIC:
          /*
          -1,-1,-1
          -1, 8,-1
          -1,-1,-1
          */
          add =(*(pScr + i + DX        ) * 8) -
                *(pScr + i - 1         ) -
                *(pScr + i             ) -
                *(pScr + i + 1         ) -
	        *(pScr + i - 1 + DX * 2) -
	        *(pScr + i     + DX * 2) -
	        *(pScr + i + 1 + DX * 2) -
	        *(pScr + i - 1 + DX    ) -
	        *(pScr + i + 1 + DX    );
          break;
    }
   add = abs( add );
   *(pDst + i) = (add >= 255) ? 255 : add;
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
