#include <math.h>

#include "graph.hpp"

inline void Swap(int &pa,int &pb )
{
 int t;

 t = pa;
 pa = pb;
 pb = t;
}

void HistoLine(int Y,int x1,int y1,int x2,int y2,int n)
{
 int d,dx,dy;
 int Aincr,Bincr,yincr,xincr;
 int x,y;

 if( (x2 - x1) == 0 )
 {
  if(y1 > y2)
   Swap(y1,y2);
  VLine(x1,y1,y2 - y1 + 1, n);
  return;
 }
 if( (y2 - y1) == 0 )
 {
  if(x1 > x2)
   Swap(x1,x2);
  Bar(x1, y1, x2 - x1 + 1, Y - y1 + 1, n);
  return;
 }

 x=0;
 y=0;

 if( fabs( (float)(y2-y1)/(x2-x1) )<=1. )
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

  VLine(x, y, Y - y + 1, n);
  for (x=x1+1; x<=x2; x++)		/* do from x1+1 to x2 */
  {
   if (d >= 0)
   {
    y += yincr;				/* set pixel A */
    d += Aincr;
   }
   else					/* set pixel B */
    d += Bincr;
   VLine(x, y, Y - y + 1, n);
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

  VLine(x, y, Y - y + 1, n);
  for (y=y1+1; y<=y2; y++)		/* do from x1+1 to x2 */
  {
   if (d >= 0)
   {
    x += xincr;				/* set pixel A */
    d += Aincr;
   }
   else					/* set pixel B */
    d += Bincr;

   VLine(x, y, Y - y + 1, n);
  }
 }
}

