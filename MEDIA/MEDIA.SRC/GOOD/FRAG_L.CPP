#include <math.h>
#include <stdlib.h>
#include "getline.hpp"
#include "vcmd.hpp"
#include "proto.hpp"
#include "gdefine.hpp"
#include "graph.hpp"
#include "mm.hpp"
#include "define.hpp"
#include "mouse.hpp"
#include "fronto.hpp"
#include "frag_l.hpp"



#ifndef _FRAGMENT_LINE
#define _FRAGMENT_LINE

#include "frag_r.hpp"
#include "point.hpp"

class FragmentLine : public FragmentRectangle
{
 Point TP1;
 Point TP2;
 int isFronto;
public:
 ~FragmentLine();
  FragmentLine(int FragNumber,int Index,int Sendadr = 0);

  virtual void Show();
  virtual void MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
protected:
  virtual void DisplayFragmentInfo(void);
  virtual void BeginMark(int x,int y);
  virtual void EndMark(int x,int y);
  virtual void MoveMark(int x,int y);
private:
  int CalculateLine(long *mhandler);
};
#endif

FragmentLine :: FragmentLine(int FragNumber,int Index,int Sendadr)
              : FragmentRectangle(FragNumber,Index,Sendadr)
{
 isFronto = 0;
 HistoNumber = 1;
}

FragmentLine :: ~FragmentLine()
{
 SendMSGCmd(DESTROY_FRONTO,0,(long)(((long)SendAdr << 16) | RegisterNumber),0);
 HistoNumber = 0;
}

void FragmentLine :: Show()
{
 if(MHandler != ERROR_HANDLER)
  {
   DisplayFragmentInfo();
  }
}

void FragmentLine :: DisplayFragmentInfo(void)
{
 char string[10];

 if(WndActive == WND_ACTIVE)
  SetColor(_RED);
 else
  SetColor(_BLUE);

 Line(TP1.x + X,TP1.y + Y,TP2.x + X,TP2.y + Y);
 itoa(FragmentNumber,string,10);
 OutStr(TP1.x + X,TP1.y + Y,string);
}

ClassType FragmentLine :: isA()
{
 return _FragmentLine;
}

int FragmentLine :: Mouse(MSG &msg)
{
 if(msg.Mouse & LBUTTON)
  {
   if(WndStatus == FRAGMENT_STATUS_FILL_BEGIN)
    {
     BeginMark(msg.X,msg.Y);
     return 1;
    }
   if(isMyFrame(msg.X,msg.Y))
    return 1;
  }

 if(msg.Mouse & LBUTTON_UP)
  if(WndStatus == FRAGMENT_STATUS_FILL_MOVE)
   {
    EndMark(msg.X,msg.Y);
    return 1;
   }

 if(msg.Mouse & MOVE)
  if(WndStatus == FRAGMENT_STATUS_FILL_MOVE)
   {
    MoveMark(msg.X,msg.Y);
    return 1;
   }

 if(msg.Mouse & RBUTTON)
  if(WndStatus == FRAGMENT_STATUS_FILL_MOVE || WndStatus == FRAGMENT_STATUS_FILL_BEGIN)
   {
    WndStatus = 0;
    SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
    SetMouseShape(ARROW);
    SendMSGCmd(FRAGMENT_FILL_ABORT,SendAdr,FragmentNumber);
    return 1;
   }

return 0;
}

void FragmentLine :: BeginMark(int x,int y)
{
 WndStatus = FRAGMENT_STATUS_FILL_MOVE;
 SetMouseShape(SMALL_KREST);
 SetWriteMode(XOR_PUT);
 TP1.x = x;
 TP1.y = y;
 TP2 = TP1;
 Line(TP1.x,TP1.y,TP2.x,TP2.y);
 SetWriteMode(COPY_PUT);
}

void FragmentLine :: EndMark(int x,int y)
{
 MoveMark(x,y);
 WndStatus = 0;
 Line(TP1.x,TP1.y,TP2.x,TP2.y);
 TP2.x = x;
 TP2.y = y;
 SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
 SetMouseShape(ARROW);

 X = TP1.x;
 Y = TP1.y;
 DX = TP2.x - TP1.x;
 DY = TP2.y - TP1.y;
 if(DX == 0)
  {
   TP1.x ++;
   DX ++;
  }

 if(DY == 0)
  {
   TP1.y ++;
   DY ++;
  }

 AbsKoordinate(X,Y,DX,DY);
 SendMSGCmd(FRAGMENT_COPY,SendAdr,((long)X << 16) + Y,((long)DX << 16) + DY);
}

void FragmentLine :: MoveMark(int x,int y)
{
 SetWriteMode(XOR_PUT);
 Line(TP1.x,TP1.y,TP2.x,TP2.y);
 TP2.x = x;
 TP2.y = y;
 Line(TP1.x,TP1.y,TP2.x,TP2.y);
 SetWriteMode(COPY_PUT);
}

int FragmentLine :: Command(MSG &msg)
{
 int i;
 int Size;
 long mhandler[20];

 switch(msg.Cmd)
  {
   case HISTO_PL:
   case LAPLAS1:
   case LAPLAS2:
   case LAPLAS3:
   case LAPLAS4:
   case MEDIAN1x3:
   case MEDIAN3x1:
   case MEDIAN3x3:
   case MEDIAN5x5:
   case MEDIANCROSS:
   case HISTOGRAMA:
        return 1;
   case FRAGMENT_SHOW:
        if(!isFronto)
         {
          TP1.x -= X;
          TP2.x -= X;
          TP1.y -= Y;
          TP2.y -= Y;

          Size = CalculateLine(mhandler);
          Register(new FrontoGrama(mhandler,Size,
                       (long)(((long)SendAdr << 16) | RegisterNumber),
                       FragmentNumber));
          for(i = 0;i < 11;i ++)
           MFree(mhandler[i]);
          isFronto = 1;
         }
        break;
  }

 return FragmentRectangle :: Command(msg);
}

#pragma argsused
void FragmentLine :: MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY)
{
}

float RetK(int x1,int y1,int x2,int y2)
{
 int i = (x2 - x1);

 if(i)
  return ((y2 - y1) / i);

return 0.;
}

int RetA(int x,int y,float k)
{
 return (y - k * x);
}

int RetE(int x)
{
 return 2 * x;
}

float RetF(int x,int y,float k,int a,float d)
{
 return (float)x * x + (float)(y - (k * x + a)) * (y - (k * x + a)) - d * d;
}

int RetXP(float e,float f)
{
 float i = e * e - 4 * f;

 if(i > 0)
  return (e + sqrt(i)) / 2;

return 0.;
}

int RetXM(float e,float f)
{
 float i = e * e - 4 * f;

 if(i > 0)
  return (e - sqrt(i)) / 2;

return 0.;
}

int RetY(float k,int x,int a)
{
 return k * x + a;
}

int FragmentLine :: CalculateLine(long *mhandler)
{
 int Size;
 float k,k1;
 int x1,y1;
 int x2,y2;
 int a1,a2;
 int e1,e2;
 float f1,f2;
 int d;

 GetLineFromMemory gm(MHandler,DX,DY);

 Size = gm.GetLine(mhandler[0],TP1.x,TP1.y,TP2.x,TP2.y);

 // suskaicuojam tieses kooef y = kx + a
 // statmena tiese k1 = -1 / k
 //                (y - y1) = k1(x - x1) cia x1,y1 zinomas tsk.
 //  / sgrt((x1 + x)*(x1 + x) + (y1 + y)*(x1 + x)) = d cia d kinta 1,2,...
 //  \ y = k1x + a                                <- lygciu sistema
 k = RetK(TP1.x,TP1.y,TP2.x,TP2.y);

 // suskaiciavom tieses y = kx + a einancios per du tsk. lygti
 // skaicuojam statmena tiese
 if(k != 0.)
  k1 = - 1 / k;
 else
  k1 = 0.;
 // suskaicuojma statmenos tieses a1 ir a2
 a1 = RetA(TP1.x,TP1.y,k1);
 a2 = RetA(TP2.x,TP2.y,k1);

 // skaicuojant lygciu sistema gavome sprendinius
 // 2x*x + ex + f = 0
 // kur e = -2x
 //     f = x1*x1 + (y1 - (k1x1 + a1))*(y1 - (k1x1 + a1)) - d * d
 e1 = RetE(TP1.x);
 e2 = RetE(TP2.x);
 d = 1;    // atstumas = 1
 f1 = RetF(TP1.x,TP1.y,k1,a1,d);
 f2 = RetF(TP2.x,TP2.y,k1,a2,d);

 x1 = RetXP(e1,f1);
 x2 = RetXP(e2,f2);
 y1 = RetY(k1,x1,a1);
 y2 = RetY(k1,x2,a2);

 gm.GetLine(mhandler[1],x1,y1,x2,y2);

 x1 = RetXM(e1,f1);
 x2 = RetXM(e2,f2);
 y1 = RetY(k1,x1,a1);
 y2 = RetY(k1,x2,a2);

 gm.GetLine(mhandler[2],x1,y1,x2,y2);

 d = 2;    // atstumas = 1
 f1 = RetF(TP1.x,TP1.y,k1,a1,d);
 f2 = RetF(TP2.x,TP2.y,k1,a2,d);

 x1 = RetXP(e1,f1);
 x2 = RetXP(e2,f2);
 y1 = RetY(k1,x1,a1);
 y2 = RetY(k1,x2,a2);

 gm.GetLine(mhandler[3],x1,y1,x2,y2);

 x1 = RetXM(e1,f1);
 x2 = RetXM(e2,f2);
 y1 = RetY(k1,x1,a1);
 y2 = RetY(k1,x2,a2);

 gm.GetLine(mhandler[4],x1,y1,x2,y2);

 d = 3;    // atstumas = 1
 f1 = RetF(TP1.x,TP1.y,k1,a1,d);
 f2 = RetF(TP2.x,TP2.y,k1,a2,d);

 x1 = RetXP(e1,f1);
 x2 = RetXP(e2,f2);
 y1 = RetY(k1,x1,a1);
 y2 = RetY(k1,x2,a2);

 gm.GetLine(mhandler[5],x1,y1,x2,y2);

 x1 = RetXM(e1,f1);
 x2 = RetXM(e2,f2);
 y1 = RetY(k1,x1,a1);
 y2 = RetY(k1,x2,a2);

 gm.GetLine(mhandler[6],x1,y1,x2,y2);

 d = 4;    // atstumas = 1
 f1 = RetF(TP1.x,TP1.y,k1,a1,d);
 f2 = RetF(TP2.x,TP2.y,k1,a2,d);

 x1 = RetXP(e1,f1);
 x2 = RetXP(e2,f2);
 y1 = RetY(k1,x1,a1);
 y2 = RetY(k1,x2,a2);

 gm.GetLine(mhandler[7],x1,y1,x2,y2);

 x1 = RetXM(e1,f1);
 x2 = RetXM(e2,f2);
 y1 = RetY(k1,x1,a1);
 y2 = RetY(k1,x2,a2);

 gm.GetLine(mhandler[8],x1,y1,x2,y2);

 d = 5;    // atstumas = 1
 f1 = RetF(TP1.x,TP1.y,k1,a1,d);
 f2 = RetF(TP2.x,TP2.y,k1,a2,d);

 x1 = RetXP(e1,f1);
 x2 = RetXP(e2,f2);
 y1 = RetY(k1,x1,a1);
 y2 = RetY(k1,x2,a2);

 gm.GetLine(mhandler[9],x1,y1,x2,y2);

 x1 = RetXM(e1,f1);
 x2 = RetXM(e2,f2);
 y1 = RetY(k1,x1,a1);
 y2 = RetY(k1,x2,a2);

 gm.GetLine(mhandler[10],x1,y1,x2,y2);

return Size;
}
