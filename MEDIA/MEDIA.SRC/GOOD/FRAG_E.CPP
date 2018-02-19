#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <alloc.h>
#include "mm.hpp"
#include "images.hpp"
#include "define.hpp"
#include "gdefine.hpp"
#include "graph.hpp"
#include "proto.hpp"
#include "graph.hpp"
#include "vcmd.hpp"
#include "graph.hpp"
#include "mouse.hpp"
#include "frag_e.hpp"


#ifndef _FRAGMENT_ELLIPSE
#define _FRAGMENT_ELLIPSE

#include "frag_r.hpp"

class FragmentEllipse : public FragmentRectangle
{
 int EX1;
 int EX2;
 int EY1;
 int EY2;
 int ERadius;
public:
 ~FragmentEllipse();
  FragmentEllipse(int FragNumber,int Index,int Sendadr = 0);

  virtual void Show();
  int isMyFrame(int x,int y);
  virtual void CalculateHistogram(long HistoHandler);
  virtual void MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
protected:
  virtual void DisplayFragmentInfo(void);
  virtual void BeginMark(int x,int y);
  virtual void EndMark(int x,int y);
  virtual void MoveMark(int x,int y);
private:
void HistoEllipse( long Handler,
                   int x1, int y1,int x2, int y2, int b0,
                   long HistoHandler);
};
#endif

FragmentEllipse :: FragmentEllipse(int FragNumber,int Index,int Sendadr)
                :  FragmentRectangle(FragNumber,Index,Sendadr)
{
 EX1 = 0;
 EX2 = 0;
 EY1 = 0;
 EY2 = 0;
 ERadius = 0;
}

FragmentEllipse :: ~FragmentEllipse()
{
}

void FragmentEllipse :: Show()
{
 int i;
 int memrow;
 int readrow = 0;
 char huge *picture;

 if(MHandler != ERROR_HANDLER)
  {
   if(GraphBoundary(X,Y,DX,DY))
    return;
   if((picture = (char *)FarMalloc(DX,DY,memrow,80)) != 0l)
    {
     for(i=0; ;i += readrow)
      {
       if(DY - i >= memrow)
        readrow = memrow;
       else
        readrow = DY - i;
       if(readrow <= 0)
        break;
       MRead(MHandler,picture,(long)(i) * DX,(long)DX * readrow);

       DisplayEllipse(EX1+X,EY1+Y,EX2+X,EY2+Y,ERadius,i,readrow,picture);
      }
     farfree(picture);
    }
   DisplayFragmentInfo();
  }
}

void FragmentEllipse :: DisplayFragmentInfo(void)
{
 char string[10];

 if(WndActive == WND_ACTIVE)
  SetColor(_RED);
 else
  SetColor(_BLUE);

 Ellipse(X + EX1,Y + EY1,X + EX2,Y + EY2,ERadius);
 itoa(FragmentNumber,string,10);
 if(EX1 < EX2)
  OutStr(X + EX1,Y + EY1,string);
 else
  OutStr(X + EX2,Y + EY2,string);
}

ClassType FragmentEllipse :: isA()
{
 return _FragmentEllipse;
}

void FragmentEllipse :: BeginMark(int x,int y)
{
 EX1 = x;
 EY1 = y;
 EX2 = x;
 EY2 = y;
 SetWriteMode(XOR_PUT);
 Line(EX1,EY1,EX2,EY2,_RED);
 SetWriteMode(COPY_PUT);
}

void FragmentEllipse :: EndMark(int x,int y)
{
 MoveMark(x,y);
 if(WndStatus == FRAGMENT_STATUS_FILL_FIRST)
  {
   SetWriteMode(XOR_PUT);
   Line(EX1,EY1,EX2,EY2,_RED);
   Ellipse(EX1,EY1,EX2,EY2,ERadius,_RED);
   SetWriteMode(COPY_PUT);
  }
 if(WndStatus == FRAGMENT_STATUS_FILL_MOVE)
  {
   WndStatus = 0;
   SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
   SetMouseShape(ARROW);
   EllipseBoundary(EX1,EY1,EX2,EY2,ERadius);
   X = BoundaryX - ViewX;
   Y = BoundaryY - ViewY;
   DX = BoundaryDX;
   DY = BoundaryDY;
   EX1 -= BoundaryX;
   EX2 -= BoundaryX;
   EY1 -= BoundaryY;
   EY2 -= BoundaryY;
   SendMSGCmd(FRAGMENT_COPY,SendAdr,
             ((long)BoundaryX << 16) + BoundaryY,
             ((long)BoundaryDX << 16) + BoundaryDY);
  }
}

void FragmentEllipse :: MoveMark(int x,int y)
{
 int TmpRadius;
 long TmpSqrt;

 if(WndStatus == FRAGMENT_STATUS_FILL_FIRST)
  {
   SetWriteMode(XOR_PUT);
   Line(EX1,EY1,EX2,EY2,_RED);
   EX2 = x;
   EY2 = y;
   Line(EX1,EY1,EX2,EY2,_RED);
   SetWriteMode(COPY_PUT);
  }
 if(WndStatus == FRAGMENT_STATUS_FILL_MOVE)
  {
   TmpSqrt = (long)(EX1 - EX2) * (EX1 - EX2) + (long)(EY1 - EY2) * (EY1 - EY2);
   if(TmpSqrt)
    TmpRadius = fabs(((float)(EY1 - y) * (EX2 - EX1) + (float)(x - EX1) * (EY2 -EY1)) / sqrt(TmpSqrt));
   else
    TmpRadius = 0;

   EllipseBoundary(EX1,EY1,EX2,EY2,TmpRadius);
   while(!(BoundaryX > ViewX && BoundaryX + BoundaryDX < ViewX + ViewDX &&
           BoundaryY > ViewY && BoundaryY + BoundaryDY < ViewY + ViewDY))
    {
     TmpRadius --;
     EllipseBoundary(EX1,EY1,EX2,EY2,TmpRadius);
    }

   if(TmpRadius != ERadius)
    {
     SetWriteMode(XOR_PUT);
     Ellipse(EX1,EY1,EX2,EY2,ERadius,_RED);
     ERadius = TmpRadius;
     Ellipse(EX1,EY1,EX2,EY2,ERadius,_RED);
     SetWriteMode(COPY_PUT);
    }
  }
}

int FragmentEllipse :: Mouse(MSG &msg)
{
 if(msg.Mouse & LBUTTON)
  {
   if(WndStatus == FRAGMENT_STATUS_FILL_BEGIN)
    {
     BeginMark(msg.X,msg.Y);
     WndStatus = FRAGMENT_STATUS_FILL_FIRST;
     return 1;
    }
   if(WndStatus == FRAGMENT_STATUS_FILL_FIRST)
    {
     WndStatus = FRAGMENT_STATUS_FILL_MOVE;
     return 1;
    }
   if(isMyFrame(msg.X,msg.Y))
    return 1;
  }

 if(msg.Mouse & LBUTTON_UP)
  switch(WndStatus)
   {
    case FRAGMENT_STATUS_FILL_FIRST:
    case FRAGMENT_STATUS_FILL_MOVE:
         EndMark(msg.X,msg.Y);
         return 1;
   }

 if(msg.Mouse & MOVE)
  switch(WndStatus)
   {
    case FRAGMENT_STATUS_FILL_FIRST:
    case FRAGMENT_STATUS_FILL_MOVE:
         MoveMark(msg.X,msg.Y);
         return 1;
   }

 if(msg.Mouse & RBUTTON)
  if(WndStatus)
   {
    WndStatus = 0;
    SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
    SetMouseShape(ARROW);
    SendMSGCmd(FRAGMENT_FILL_ABORT,SendAdr,FragmentNumber);
    return 1;
   }

return 0;
}

int FragmentEllipse :: isMyFrame(int x,int y)
{
 return EllipsePoint(X + EX1,Y + EY1,X + EX2,Y + EY2,ERadius,x,y);
}

void FragmentEllipse :: MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY)
{
 if(MHandler != ERROR_HANDLER)
  MCopyEllipse(MHandler,EX1 + X - DisplayPlaceX,EY1 + Y - DisplayPlaceY,EX2 + X - DisplayPlaceX,EY2 + Y - DisplayPlaceY,ERadius,Handler,PictSizeDX,PictSizeDY);
}

/*
  Suskaiciuoti ELIPSINIO vaizdo HISTOGRAMA
  Handler      - paveiksliuko mm handleris
                 dydis pagal EllipseBoundary();
  x1,y1,x2,y2  - viena elipse pusase
  b0           - kitos pusases ilgis
  HistoHandler - histogramos masyvo mm handleris
                 dydis 256 * sizeof(long)
*/
void FragmentEllipse :: HistoEllipse( long Handler,
                   int x1, int y1,int x2, int y2, int b0,
                   long HistoHandler)
{
 int    lines, y, width;

 long   dx = x1 - x2;
 long   dy = y1 - y2;

 float  c = sqrt(dx * dx + dy * dy);
 int    a0=((int)(c+0.5))>>1;

 float  Cos,Sin;
 float  A,B,C,D,tmp;

 char  *pic;
 int   dia;
 long  Histograma[256];
 int   i;

 Sin = (dy/c);
 Cos = -(dx/c);

 A=b0*Cos*b0*Cos+a0*Sin*a0*Sin;
 B=a0*Cos*a0*Cos+b0*Sin*b0*Sin;
 C=((float)a0*a0-(float)b0*b0)*2.*Cos*Sin;
 D=((float)a0*a0)*((float)b0*b0);
 EllipseBoundary(x1,y1,x2,y2,b0);

 width = BoundaryDX;
 lines = (( y1 + y2 ) >> 1) - BoundaryY;

 pic = (char  *)malloc(width);
 memset(Histograma,0,256*sizeof(long));

 tmp=sqrt(4.*A*D);
 x1=tmp/(2.*A);
 dia = x1 + x1 + 1;
 MRead (Handler,pic,(long)lines*width+width/2-x1,dia);
 for(i=0;i<dia;i++)
  (*(Histograma + (unsigned char)*(pic+i)))++;

 for(y=1; y <= lines; y++)
 {
  tmp=(C*y*C*y-4.*A*(B*y*y-D));
  if(tmp < 0.0)
   continue;
  tmp=sqrt(tmp);

  x1 = ( C * y - tmp) / (2. * A);
  x2 = ( C * y + tmp) / (2. * A);
  dia = x2 - x1 + 1;
  MRead (Handler,pic,(long)(lines - y)*width+width/2+x1,dia);
  for(i=0;i<dia;i++)
   (*(Histograma + (unsigned char)*(pic+i)))++;

  x1=(-C * y - tmp) / (2. * A);
  x2=(-C * y + tmp) / (2. * A);
  dia = x2 - x1 + 1;
  MRead (Handler,pic,(long)(lines + y)*width+width/2+x1,dia);
  for(i=0;i<dia;i++)
   (*(Histograma + *(pic+i)))++;
 }
 free(pic);
 MWrite(HistoHandler,(char huge*)Histograma,0,256*sizeof(long));
}

void FragmentEllipse :: CalculateHistogram(long HistoHandler)
{
 HistoEllipse(MHandler,EX1,EY1,EX2,EY2,ERadius,HistoHandler);
}
