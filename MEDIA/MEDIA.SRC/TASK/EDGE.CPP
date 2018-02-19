#include <alloc.h>
#include <math.h>

#include "mm.hpp"
#include "proto.hpp"
#include "edge.hpp"

#ifndef _EDGE
#define _EDGE

#include "vcmd.hpp"
#include "filter.hpp"

class Edge : public Filtering
{
 int Type;
 public:
  Edge(long ScrHandler,int dx, int dy,int sentAdr,int Type = CLASIC);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif

ClassType Edge :: isA()
{
 return _Edge;
}

Edge :: Edge(long ScrHandler,int dx,int dy,int sentAdr,int type)
          : Filtering(ScrHandler,dx,dy,sentAdr)
{
 CurentY=1;
 pScr = (unsigned char *)malloc(DX * 3);
 pDst = (unsigned char *)malloc(DX);

 Type = type;
}

void Edge :: Run(void)
{
 int i,add;
 int k,j,tmp;
 int l1 = DX;
 int l2 = DX * 2;

 if(CurentY < DY - 1)
 {
  MRead(scrHandler,(char *)pScr,(long)(CurentY-1)*DX,DX*3);
  for ( i = 1; i < DX - 1; i++ )
  {
   switch(Type)
    {
     case MIN:
          add = 255;
          for(j = 0;j < 3;j ++)
           {
            tmp = j * DX;
            for(k = i - 1;k < i + 2;k ++)
             if(add > *(pScr + tmp + k))
              add = *(pScr + tmp + k);
           }
          break;
     case MAX:
          add = 0;
          for(j = 0;j < 3;j ++)
           {
            tmp = j * DX;
            for(k = i - 1;k < i + 2;k ++)
             if(add < *(pScr + tmp + k))
              add = *(pScr + tmp + k);
           }
          break;
     case BOUNDARY:
          add = *(pScr + i + l1);
          add = add + (add - *(pScr + i - 1     )) +
                      (add - *(pScr + i         )) +
                      (add - *(pScr + i + 1     )) +
                      (add - *(pScr + i - 1 + l1)) +
                      (add - *(pScr + i + 1 + l1)) +
                      (add - *(pScr + i - 1 + l2)) +
                      (add - *(pScr + i + 1 + l2)) +
                      (add - *(pScr + i     + l2));
          if(add < 0)
           add = 0;
          else
           if(add > 255)
            add = 255;
          break;
     case WRONGS:
          add = *(pScr + i + l1);
          add = (add - *(pScr + i - 1     )) +
                (add - *(pScr + i         )) +
                (add - *(pScr + i + 1     )) +
                (add - *(pScr + i - 1 + l1)) +
                (add - *(pScr + i + 1 + l1)) +
                (add - *(pScr + i - 1 + l2)) +
                (add - *(pScr + i + 1 + l2)) +
                (add - *(pScr + i     + l2));

          add = abs(add);
/*
          if(add < 0)
           add = 0;
          else
*/
           if(add > 255)
            add = 255;
          break;
     case FON:
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
