#include <math.h>
#include "mm.hpp"
#include "proto.hpp"
#include "getline.hpp"

#define max(a,b)    (((a) > (b)) ? (a) : (b))


#ifndef _GET_LINE_FROM_MEMORY
#define _GET_LINE_FROM_MEMORY

#include "object.hpp"

class GetLineFromMemory : public Object
{
 long PictureMHandler;
 int PictureDX;
 int PictureDY;
 int CalculationPlace;

public:
 ~GetLineFromMemory();
  GetLineFromMemory(long mhandler,int dx,int dy);

  int GetLine(long &MHadler,int x1,int y1,int x2,int y2); // return size
  virtual ClassType isA();
protected:
  void GetVLine(long MHandler,int x,int y,int dy);
  void GetHLine(long MHandler,int x,int y,int dx);
  void GetPixel(long MHandler,int x,int y);
  void GetLocalLine(long MHandler,int x1,int y1,int x2,int y2);
};
#endif

GetLineFromMemory :: GetLineFromMemory(long mhandler,int dx,int dy)
{
 PictureMHandler = mhandler;
 PictureDX = dx;
 PictureDY = dy;
}

GetLineFromMemory :: ~GetLineFromMemory()
{
}

ClassType GetLineFromMemory :: isA()
{
 return _GetLineFromMemory;
}

int GetLineFromMemory :: GetLine(long &MHandler,int x1,int y1,int x2,int y2)
{
 int Size;

 if(x1 < 0)
  x1 = 0;

 if(x2 < 0)
  x2 = 0;

 if(y1 < 0)
  y1 = 0;

 if(y2 < 0)
  y2 = 0;

 if(x1 > PictureDX)
  x1 = PictureDX;

 if(x2 > PictureDX)
  x2 = PictureDX;

 if(y1 > PictureDY)
  y1 = PictureDY;

 if(y2 > PictureDY)
  y2 = PictureDY;

 Size = max(abs(x1 - x2),abs(y1 - y2)) + 1;
 if(Size == 0)
  {
   MHandler = ERROR_HANDLER;
   return 0;
  }

 CalculationPlace = 0;
 MHandler = MAlloc(Size);
 MLock(MHandler);
 MLock(PictureMHandler);
 if(x1 > x2)
  GetLocalLine(MHandler,x2,y2,x1,y1);
 else
  GetLocalLine(MHandler,x1,y1,x2,y2);
 MUnLock(MHandler);
 MUnLock(PictureMHandler);

return Size;
}

inline void Swap(int &pa,int &pb)
{
 int t;

 t = pa;
 pa = pb;
 pb = t;
}

void GetLineFromMemory :: GetLocalLine(long MHandler,int x1,int y1,int x2,int y2)
{
 int d,dx,dy;
 int Aincr,Bincr,yincr,xincr;
 int x,y;


 if( (x2 - x1) == 0 )
 {
  if(y1 > y2)
   Swap(y1,y2);
  GetVLine(MHandler,x1,y1,y2 - y1 + 1);
  return;
 }
 if( (y2 - y1) == 0 )
 {
  if(x1 > x2)
   Swap(x1,x2);
  GetHLine(MHandler,x1, y1, x2 - x1 + 1);
  return;
 }

 if( abs(y2-y1) <= abs(x2-x1) )
 {
  if(x1 > x2)				/* force x1 < x2 */
  {
   Swap( x1, x2 );
   Swap( y1, y2 );
  }
  if (y2 > y1)				/* determine increment for y */
   yincr = 1;
  else
   yincr = -1;

  dx = x2 - x1;				/* initialize constants */
  dy = abs( y2-y1 );

  d = 2 * dy - dx;
  Aincr = 2 * (dy - dx);
  Bincr = 2 * dy;

  x = x1;					/* initial x and y */
  y = y1;

  GetPixel(MHandler,x,y);			/* set pixel at (x1,y1) */
  for (x=x1+1; x<=x2; x++)		/* do from x1+1 to x2 */
  {
   if (d >= 0)
   {
    y += yincr;				/* set pixel A */
    d += Aincr;
   }
   else					/* set pixel B */
    d += Bincr;
   GetPixel(MHandler,x,y);
  }
 }
 else
 {
  if(y1 > y2)				/* force x1 < x2 */
  {
   Swap( x1, x2 );
   Swap( y1, y2 );
  }
  if(x2 > x1)				/* determine increment for y */
   xincr = 1;
  else
   xincr = -1;

  dy = y2 - y1;				/* initialize constants */
  dx = abs( x2-x1 );

  d = 2 * dx - dy;
  Aincr = 2 * (dx - dy);
  Bincr = 2 * dx;

  x = x1;					/* initial x and y */
  y = y1;

  GetPixel(MHandler,x,y);			/* set pixel at (x1,y1) */
  for (y=y1+1; y<=y2; y++)		/* do from x1+1 to x2 */
  {
   if (d >= 0)
   {
    x += xincr;				/* set pixel A */
    d += Aincr;
   }
   else					/* set pixel B */
    d += Bincr;
   GetPixel(MHandler,x,y);
  }
 }
}

void GetLineFromMemory :: GetVLine(long MHandler,int x,int y,int dy)
{
 MCopyRectangle(PictureMHandler,PictureDX,PictureDY,x,y,MHandler,1,dy,0,0,1,dy);
}

void GetLineFromMemory :: GetHLine(long MHandler,int x,int y,int dx)
{
 MCopyRectangle(PictureMHandler,PictureDX,PictureDY,x,y,MHandler,dx,1,0,0,dx,1);
}

void GetLineFromMemory :: GetPixel(long MHandler,int x,int y)
{
 char str[1];

 MRead(PictureMHandler,str,(long)y * PictureDX + x,1);
 MWrite(MHandler,str,CalculationPlace,1);
 CalculationPlace ++;
}
