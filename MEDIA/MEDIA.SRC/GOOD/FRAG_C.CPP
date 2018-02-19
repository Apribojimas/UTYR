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
#include "mouse.hpp"
#include "vcmd.hpp"
#include "frag_c.hpp"


#ifndef _FRAGMENT_CIRCLE
#define _FRAGMENT_CIRCLE

#include "frag_r.hpp"

class FragmentCircle : public FragmentRectangle
{
 int CX;
 int CY;
 int CR;
public:
 ~FragmentCircle();
  FragmentCircle(int FragNumber,int Index,int Sendadr = 0);

  virtual void Show();
  virtual void CalculateHistogram(long HistoHandler);
  virtual void MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual void DisplayFragmentInfo(void);
  virtual void BeginMark(int x,int y);
  virtual void EndMark(int x,int y);
  virtual void MoveMark(int x,int y);
private:
 void HistoCircle( long Handler,int r,long HistoHandler);
};
#endif

FragmentCircle :: FragmentCircle(int FragNumber,int Index,int Sendadr)
                : FragmentRectangle(FragNumber,Index,Sendadr)
{
 CX = 0;
 CY = 0;
 CR = 0;
}

FragmentCircle :: ~FragmentCircle()
{
}

void FragmentCircle :: Show()
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

       DisplayCircle(CX+X,CY+Y,CR,i,readrow,picture);
      }
     farfree(picture);
    }
   DisplayFragmentInfo();
  }
}

void FragmentCircle :: DisplayFragmentInfo(void)
{
 char string[10];

 if(WndActive == WND_ACTIVE)
  SetColor(_RED);
 else
  SetColor(_BLUE);

 Circle(X + CX,Y + CY,CR);
 itoa(FragmentNumber,string,10);
 OutStr(X + 1,Y + DY / 2,string);
}

ClassType FragmentCircle :: isA()
{
 return _FragmentCircle;
}

void FragmentCircle :: BeginMark(int x,int y)
{
 CX = x;
 CY = y;
 WndStatus = FRAGMENT_STATUS_FILL_MOVE;
 SetWriteMode(XOR_PUT);
 Circle(CX,CY,CR);
 SetWriteMode(COPY_PUT);
}

void FragmentCircle :: EndMark(int x,int y)
{
 MoveMark(x,y);
 WndStatus = 0;
 SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
 SetMouseShape(ARROW);
 X = CX - CR;
 Y = CY - CR;
 CX -= X;
 CY -= Y;
 DX = DY = 2 * CR + 1;
 SendMSGCmd(FRAGMENT_COPY,SendAdr,((long)X << 16) + Y,((long)DX << 16) + DY);
}

void FragmentCircle :: MoveMark(int x,int y)
{
 int TmpR;
 SetWriteMode(XOR_PUT);
 TmpR = sqrt((float)(CX - x) * (CX - x) + (float)(CY - y) * (CY - y));
 if(TmpR > CX - ViewX)
  TmpR = CX - ViewX;
 if(TmpR > CY - ViewY)
  TmpR = CY - ViewY;
 if(TmpR > ViewX + ViewDX - CX)
  TmpR = ViewX + ViewDX - CX;
 if(TmpR > ViewY + ViewDY - CY)
  TmpR = ViewY + ViewDY - CY;
 if(TmpR != CR)
  {
   Circle(CX,CY,CR);
   CR = TmpR;
   Circle(CX,CY,CR);
  }
 SetWriteMode(COPY_PUT);
}

void FragmentCircle :: MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY)
{
 if(MHandler != ERROR_HANDLER)
  MCopyCircle(MHandler,CX + X - DisplayPlaceX,CY + Y - DisplayPlaceY,CR,Handler,PictSizeDX,PictSizeDY);
}
/*
  Suskaiciuoti Apskritiminio vaizdo HISTOGRAMA
  Handler      - paveiksliuko mm handleris
                 dydis (r + r + 1) * (r + r + 1)
  r            - apskritimo spindulys (jei r=0 taskas );
  HistoHandler - histogramos masyvo mm handleris
                 dydis 256 * sizeof(long)
*/
void FragmentCircle :: HistoCircle( long Handler,int r,long HistoHandler)
{
 long  sqr;
 int   dx,dy;
 char  *pic;
 int   diametr,dia;
 long  Histograma[256];
 int   i;

 if(r < 0)
  r = (-r);
 diametr = r + r + 1;
 pic = (char  *)malloc(diametr);
 memset(Histograma,0,256*sizeof(long));

 MRead (Handler,pic,(long)r*diametr,diametr);
 for(i=0;i<diametr;i++)
  (*(Histograma + (unsigned char)*(pic+i)))++;
 sqr = (long)(r + 1) * r;

 dx  = r;
 dy = 0;

 while(++dy <= r)
 {
  if(dx)
  {
   sqr -= (dy + dy - 1);
   dx = (dx + (int)(sqr/dx)) / 2;
  }

  dia = dx + dx + 1;
  MRead (Handler,pic,(long)(r - dy)*diametr + r - dx ,dia);
  for(i=0;i<dia;i++)
   (*(Histograma + (unsigned char)*(pic+i)))++;
  MRead (Handler,pic,(long)(r + dy)*diametr + r - dx ,dia);
  for(i=0;i<dia;i++)
   (*(Histograma + (unsigned char)*(pic+i)))++;
 }
 free(pic);
 MWrite(HistoHandler,(char huge*)Histograma,0,256*sizeof(long));
}

void FragmentCircle :: CalculateHistogram(long HistoHandler)
{
 HistoCircle(MHandler,CR,HistoHandler);
}
