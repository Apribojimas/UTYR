#include <alloc.h>
#include <math.h>

#include "mm.hpp"
#include "proto.hpp"
#include "aver.hpp"

#ifndef _AVERAGE
#define _AVERAGE

#include "filter.hpp"

class Average : public Filtering
{
 int Type;
 int MatShift;
 int MatSize;
 public:
  Average(long ScrHandler,int dx, int dy,int sentAdr, int Type = 0);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif

ClassType Average :: isA()
{
 return _Average;
}

Average :: Average(long ScrHandler,int dx,int dy,int sentAdr,int type)
          : Filtering(ScrHandler,dx,dy,sentAdr)
{
 switch(type)
  {
   case 0:
   case 1:
        CurentY = 1;
        MatShift = 1;
        MatSize = 3;
        break;
   case 2:
   case 3:
        CurentY = 3;
        MatShift = 3;
        MatSize = 7;
        break;
   case 4:
   case 5:
        CurentY = 7;
        MatShift = 7;
        MatSize = 15;
        break;
  }

 pScr = (unsigned char *)malloc(DX * MatSize);
 pDst = (unsigned char *)malloc(DX);

 Type = type;
}

void Average :: Run(void)
{
 int i;
 unsigned long add;
 int j,k,tmp;
 int l1 = DX;
 int l2 = DX * 2;
 int l3 = DX * 3;
 int l4 = DX * 4;
 int l5 = DX * 5;
 int l6 = DX * 6;

 if(CurentY < DY - MatShift)
 {
  MRead(scrHandler,(char *)pScr,(long)(CurentY-MatShift)*DX,DX*MatSize);
  for (i = MatShift; i < DX - MatShift;i ++)
  {
   switch(Type)
   {
    case 0:
         /*
         1, 2, 1   1
         2, 4, 2 * --
         1, 2, 1   16
         */
         add = *(pScr + i - 1     ) +
               *(pScr + i + 1     ) +
               *(pScr + i - 1 + l2) +
               *(pScr + i + 1 + l2) +
              (*(pScr + i         ) +
               *(pScr + i - 1 + l1) +
               *(pScr + i + 1 + l1) +
               *(pScr + i     + l2)) * 2 +
               *(pScr + i     + l1) * 4;
         *(pDst + i) = add / 16;
         break;
    case 1:
         /*
         2, 1, 2   1
         1, 4, 1 * --
         2, 1, 2   16
         */
         add =(*(pScr + i - 1     ) +
               *(pScr + i + 1     ) +
               *(pScr + i - 1 + l2) +
               *(pScr + i + 1 + l2)) * 2 +
               *(pScr + i         ) +
               *(pScr + i - 1 + l1) +
               *(pScr + i + 1 + l1) +
               *(pScr + i     + l2) +
               *(pScr + i     + l1) * 4;
         *(pDst + i) = add / 16;
         break;
    case 2:
         /*
         1,1,1,1,1,1,1        // 7
         1,2,2,2,2,2,1        // 12
         1,2,4,4,4,2,1   1    // 18
         1,2,4,8,4,2,1 * --   // 22
         1,2,4,4,4,2,1   96   // 18
         1,2,2,2,2,2,1        // 12
         1,1,1,1,1,1,1        // 7
         */
         add = *(pScr + i - 3) +
               *(pScr + i - 2) +
               *(pScr + i - 1) +
               *(pScr + i    ) +
               *(pScr + i + 1) +
               *(pScr + i + 2) +
               *(pScr + i + 3) +
               *(pScr + i - 3 + l1) +
               *(pScr + i - 2 + l1) * 2 +
               *(pScr + i - 1 + l1) * 2 +
               *(pScr + i     + l1) * 2 +
               *(pScr + i + 1 + l1) * 2 +
               *(pScr + i + 2 + l1) * 2 +
               *(pScr + i + 3 + l1) +
               *(pScr + i - 3 + l2) +
               *(pScr + i - 2 + l2) * 2 +
               *(pScr + i - 1 + l2) * 4 +
               *(pScr + i     + l2) * 4 +
               *(pScr + i + 1 + l2) * 4 +
               *(pScr + i + 2 + l2) * 2 +
               *(pScr + i + 3 + l2) +
               *(pScr + i - 3 + l3) +
               *(pScr + i - 2 + l3) * 2 +
               *(pScr + i - 1 + l3) * 4 +
               *(pScr + i     + l3) * 8 +
               *(pScr + i + 1 + l3) * 4 +
               *(pScr + i + 2 + l3) * 2 +
               *(pScr + i + 3 + l3) +
               *(pScr + i - 3 + l4) +
               *(pScr + i - 2 + l4) * 2 +
               *(pScr + i - 1 + l4) * 4 +
               *(pScr + i     + l4) * 4 +
               *(pScr + i + 1 + l4) * 4 +
               *(pScr + i + 2 + l4) * 2 +
               *(pScr + i + 3 + l4) +
               *(pScr + i - 3 + l5) +
               *(pScr + i - 2 + l5) * 2 +
               *(pScr + i - 1 + l5) * 2 +
               *(pScr + i     + l5) * 2 +
               *(pScr + i + 1 + l5) * 2 +
               *(pScr + i + 2 + l5) * 2 +
               *(pScr + i + 3 + l5) +
               *(pScr + i - 3 + l6) +
               *(pScr + i - 2 + l6) +
               *(pScr + i - 1 + l6) +
               *(pScr + i     + l6) +
               *(pScr + i + 1 + l6) +
               *(pScr + i + 2 + l6) +
               *(pScr + i + 3 + l6);

         *(pDst + i) = add / 96;
         break;
    case 3:
         /*
         1,1,1,1,1,1,1
         1,1,1,1,1,1,1
         1,1,1,1,1,1,1   1
         1,1,1,1,1,1,1 * --
         1,1,1,1,1,1,1   49
         1,1,1,1,1,1,1
         1,1,1,1,1,1,1
         */
         add = *(pScr + i - 3) +
               *(pScr + i - 2) +
               *(pScr + i - 1) +
               *(pScr + i    ) +
               *(pScr + i + 1) +
               *(pScr + i + 2) +
               *(pScr + i + 3) +
               *(pScr + i - 3 + l1) +
               *(pScr + i - 2 + l1) +
               *(pScr + i - 1 + l1) +
               *(pScr + i     + l1) +
               *(pScr + i + 1 + l1) +
               *(pScr + i + 2 + l1) +
               *(pScr + i + 3 + l1) +
               *(pScr + i - 3 + l2) +
               *(pScr + i - 2 + l2) +
               *(pScr + i - 1 + l2) +
               *(pScr + i     + l2) +
               *(pScr + i + 1 + l2) +
               *(pScr + i + 2 + l2) +
               *(pScr + i + 3 + l2) +
               *(pScr + i - 3 + l3) +
               *(pScr + i - 2 + l3) +
               *(pScr + i - 1 + l3) +
               *(pScr + i     + l3) +
               *(pScr + i + 1 + l3) +
               *(pScr + i + 2 + l3) +
               *(pScr + i + 3 + l3) +
               *(pScr + i - 3 + l4) +
               *(pScr + i - 2 + l4) +
               *(pScr + i - 1 + l4) +
               *(pScr + i     + l4) +
               *(pScr + i + 1 + l4) +
               *(pScr + i + 2 + l4) +
               *(pScr + i + 3 + l4) +
               *(pScr + i - 3 + l5) +
               *(pScr + i - 2 + l5) +
               *(pScr + i - 1 + l5) +
               *(pScr + i     + l5) +
               *(pScr + i + 1 + l5) +
               *(pScr + i + 2 + l5) +
               *(pScr + i + 3 + l5) +
               *(pScr + i - 3 + l6) +
               *(pScr + i - 2 + l6) +
               *(pScr + i - 1 + l6) +
               *(pScr + i     + l6) +
               *(pScr + i + 1 + l6) +
               *(pScr + i + 2 + l6) +
               *(pScr + i + 3 + l6);

         *(pDst + i) = add / 49;
         break;
    case 4:
         /*
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
         */

         add = 0;
         for(j = 0;j < 15;j ++)
          {
           tmp = j * DX;
           for(k = i - 7;k < i + 8;k ++)
            add += *(pScr + tmp + k);
          }

         *(pDst + i) = add / 225;

         break;
    case 5:
         {
         unsigned char mat[] =
         {
          1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1,
          2, 4, 6, 8,10,12,14,16,14,12,10, 8, 6, 4, 2,
          3, 6, 9,12,15,18,21,24,21,18,15,12, 9, 6, 3,
          4, 8,12,16,20,24,28,32,28,24,20,16,12, 8, 4,
          5,10,15,20,25,30,35,40,35,30,25,20,15,10, 5,
          6,12,18,24,30,36,42,48,42,36,30,24,18,12, 6,
          7,14,21,28,35,42,49,56,49,42,35,28,21,14, 7,
          8,16,24,32,40,48,56,64,56,48,40,32,24,16, 8,
          7,14,21,28,35,42,49,56,49,42,35,28,21,14, 7,
          6,12,18,24,30,36,42,48,42,36,30,24,18,12, 6,
          5,10,15,20,25,30,35,40,35,30,25,20,15,10, 5,
          4, 8,12,16,20,24,28,32,28,24,20,16,12, 8, 4,
          3, 6, 9,12,15,18,21,24,21,18,15,12, 9, 6, 3,
          2, 4, 6, 8,10,12,14,16,14,12,10, 8, 6, 4, 2,
          1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1
         };
         unsigned int div = 4096;

         add = 0;
         for(j = 0;j < 15;j ++)
          {
           int mattmp = j * MatSize;
           int t;

           tmp = j * DX;
           for(t = 0,k = i - 7;k < i + 8;k ++,t ++)
            add += (*(pScr + tmp + k)) * (*(mat + mattmp + t));
          }

         add /= div;
         *(pDst + i) = (unsigned char)add;
         }
         break;

   }
  }
//  Heap("Average :: Run");
  for(i = 0;i < MatShift; i ++)
   {
    *(pDst + i) = *(pDst + MatShift);
    *(pDst + DX - i - 1) = *(pDst + DX - MatShift - 1);
   }
  MWrite(dstHandler,(char *)pDst,(long)CurentY*DX,DX);
  CurentY++;
 }
 else
  if(!Sent)
  {
   MRead(dstHandler,(char *)pDst,(long)(MatShift)*DX,DX);
   MRead(dstHandler,(char *)pScr,(long)(DY - MatShift - 1)*DX,DX);
   for (i = 0; i < MatShift; i++)
    {
     MWrite(dstHandler,(char *)pDst,(long)(i)*DX,DX);
     MWrite(dstHandler,(char *)pScr,(long)(DY - i - 1)*DX,DX);
    }
   MCopyRectangle(dstHandler,DX,DY,0,0,scrHandler,DX,DY,0,0,DX,DY);
   SendMSGCmd(FILTER_LOCK_OUT,SentAddress,RegisterNumber);
   Sent++;
  }
}
