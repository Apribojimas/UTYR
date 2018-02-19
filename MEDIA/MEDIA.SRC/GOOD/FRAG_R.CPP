#include <string.h>
#include <stdlib.h>
#include <alloc.h>
#include "keys.h"
#include "gettext.hpp"
#include "mm.hpp"
#include "images.hpp"
#include "define.hpp"
#include "gdefine.hpp"
#include "graph.hpp"
#include "proto.hpp"
#include "graph.hpp"
#include "vcmd.hpp"
#include "mouse.hpp"
#include "histo.hpp"
#include "laplas.hpp"
#include "median.hpp"
#include "histopl.hpp"
#include "frag_r.hpp"
#include "aver.hpp"
#include "aver.hpp"
#include "highpass.hpp"
#include "roberts.hpp"
#include "hr.hpp"
#include "histoscr.hpp"
#include "edge.hpp"
#include "histomod.hpp"


#ifndef _FRAGMENT_RECTANGLE
#define _FRAGMENT_RECTANGLE

#include "GEventHandler.hpp"

class FragmentRectangle : public GEventHandler
{
 long MBackup;
protected:
 int isInit;
 long MHandler;
 int FragmentNumber;
 int SendAdr;
 int FiltrNumber;
 int HistoNumber;

public:
 ~FragmentRectangle();
  FragmentRectangle(int FragNumber,int Index,int Sendadr = 0);

  int isOK(void);      // jau esama pilnai inicializuoti
  virtual void Show(void);
  void SetFragmentNumber(int i);
  virtual void MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY);
  virtual void CalculateHistogram(long HistoHandler);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
  virtual int Keyboard(MSG &msg);        // klaviaturos
protected:
  virtual void DisplayFragmentInfo(void);
  virtual void BeginMark(int x,int y);
  virtual void EndMark(int x,int y);
  virtual void MoveMark(int x,int y);
private:
  void HistoRectangle( long Handler,int DX, int DY, long HistoHandler);
  void HistoPrapletimas(int type,int percent,int dmin,int dmax);
  void HistoColorReduce(int i);
};
#endif

FragmentRectangle :: FragmentRectangle(int FragNumber,int Index,int Sendadr)
                  :  GEventHandler(0,0,0,0)
{
 FragmentNumber = FragNumber;
 MHandler = ERROR_HANDLER;
 MBackup = ERROR_HANDLER;
 RegisterNumber = Index;
 SendAdr = Sendadr;
 isInit = 0;
 FiltrNumber = 0;
 HistoNumber = 0;
}

FragmentRectangle :: ~FragmentRectangle()
{
 if(MHandler != ERROR_HANDLER)
  MFree(MHandler);
 if(MBackup != ERROR_HANDLER)
  MFree(MBackup);

 if(isInit != 2)
  {
   SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
   SetMouseShape(ARROW);
  }

 if(FiltrNumber)
  SendMSGCmd(TERMINATE_FILTER,0,FiltrNumber);
 if(HistoNumber)
  SendMSGCmd(CHANGE_HISTO_NAME,0,(long)(((long)SendAdr << 16) | RegisterNumber),0);
}

void FragmentRectangle :: Show(void)
{
 if(MHandler != ERROR_HANDLER)
  {
   if(GraphBoundary(X,Y,DX,DY))
    return;
   MDisplay(MHandler,DX,DY,X,Y);
   DisplayFragmentInfo();
  }
}

void FragmentRectangle :: DisplayFragmentInfo(void)
{
 char string[10];

 if(WndActive == WND_ACTIVE)
  SetColor(_RED);
 else
  SetColor(_BLUE);

 Rectangle(X,Y,DX,DY);
 itoa(FragmentNumber,string,10);
 OutStr(X + 1,Y + 1,string);
}

ClassType FragmentRectangle :: isA()
{
 return _FragmentRectangle;
}
void FragmentRectangle :: CalculateHistogram(long HistoHandler)
{
 HistoRectangle(MHandler,DX,DY,HistoHandler);
}

void FragmentRectangle :: BeginMark(int x,int y)
{
 X = x;
 Y = y;
 WndStatus = FRAGMENT_STATUS_FILL_MOVE;
 SetWriteMode(XOR_PUT);
 Rectangle(X,Y,DX,DY,_RED);
 SetWriteMode(COPY_PUT);
}

void FragmentRectangle :: EndMark(int x,int y)
{
 MoveMark(x,y);
 WndStatus = 0;
 SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
 SetMouseShape(ARROW);
 AbsKoordinate(X,Y,DX,DY);
 SendMSGCmd(FRAGMENT_COPY,SendAdr,((long)X << 16) + Y,((long)DX << 16) + DY);
}

void FragmentRectangle :: MoveMark(int x,int y)
{
 int x1;
 int y1;
 int dx;
 int dy;

 SetWriteMode(XOR_PUT);

 x1 = X;
 y1 = Y;
 dx = DX;
 dy = DY;
 AbsKoordinate(x1,y1,dx,dy);
 Rectangle(x1,y1,dx,dy,_RED);
 DX = x - X;
 DY = y - Y;
 x1 = X;
 y1 = Y;
 dx = DX;
 dy = DY;
 AbsKoordinate(x1,y1,dx,dy);
 Rectangle(x1,y1,dx,dy,_RED);
 SetWriteMode(COPY_PUT);
}

/*
  Suskaiciuoti KVADRATINIO vaizdo HISTOGRAMA
  Handler      - paveiksliuko mm handleris
  DX,DY        - dydis DX * DY
  HistoHandler - histogramos masyvo mm handleris
                 dydis 256 * sizeof(long)
*/
void FragmentRectangle :: HistoRectangle( long Handler,int dx, int dy, long HistoHandler)
{
 char  *pic;
 long  Histograma[256];
 int   i,j;

 pic = (char  *)malloc(dx);
 memset(Histograma,0,256*sizeof(long));

 for(j=0;j<dy;j++)
 {
  MRead (Handler,pic,(long)j*dx,dx);
  for(i=0;i<dx;i++)
   (*(Histograma + (unsigned char)*(pic+i)))++;
 }
 free(pic);
 MWrite(HistoHandler,(char huge*)Histograma,0,256*sizeof(long));
}

void FragmentRectangle :: SetFragmentNumber(int i)
{
 FragmentNumber = i;
 if(HistoNumber)
  SendMSGCmd(CHANGE_HISTO_NAME,0,(long)(((long)SendAdr << 16) | RegisterNumber),FragmentNumber);
}

int FragmentRectangle :: Mouse(MSG &msg)
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

void FragmentRectangle :: HistoPrapletimas(int type,int percent,int dmin,int dmax)
{
 long HistoHandler;

 if(FiltrNumber)
  return ;
 HistoHandler = MAlloc(256 * sizeof(long));
 if(HistoHandler == ERROR_HANDLER)
  return ;
 CalculateHistogram(HistoHandler);
 switch(type)
  {
   case 0:
        FiltrNumber = RegisterFilter(new HistoPl(MHandler,DX,DY,SendAdr,HistoHandler,percent));
        break;
   case 1:
   case 2:
        FiltrNumber = RegisterFilter(new HistoPl(MHandler,DX,DY,SendAdr,HistoHandler,percent,type,dmin,dmax));
        break;
   case 3:
        FiltrNumber = RegisterFilter(new HistoPl(MHandler,DX,DY,SendAdr,HistoHandler,percent,type));
        break;
  }
 MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
return ;
}

void FragmentRectangle :: HistoColorReduce(int i)
{
 long HistoHandler;

 if(FiltrNumber)
  return ;
 HistoHandler = MAlloc(256 * sizeof(long));
 if(HistoHandler == ERROR_HANDLER)
  return ;
 CalculateHistogram(HistoHandler);
 FiltrNumber = RegisterFilter(new HistoReduce(MHandler,DX,DY,SendAdr,HistoHandler,i));
 MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
return ;
}

int FragmentRectangle :: Command(MSG &msg)
{
 long HistoHandler;

 switch(msg.Cmd)
  {
   case FILTER_LOCK_OUT:
        if(msg.Param1 == FiltrNumber)
         {
          SendMSGCmd(TERMINATE_FILTER,0,FiltrNumber);
          SendMSGCmd(FRAGMENT_SHOW,SendAdr);
          FiltrNumber = 0;
          return 0;
         }
        break;
   case HISTO_REDUCE:
        Register(new HistoScroller(HISTO_REDUCE_OK,0,SendAdr,10106,10105,255));
        return 1;
   case HISTO_REDUCE_OK:
        HistoColorReduce((int)msg.Param1);
        return 1;
   case ROBERTS_SQRT:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Roberts(MHandler,DX,DY,SendAdr,SQRT));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case ROBERTS_MAX:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Roberts(MHandler,DX,DY,SendAdr,MAX));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case ROBERTS_ABS:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Roberts(MHandler,DX,DY,SendAdr,ABS));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case HISTO_PL1:
        if(!FiltrNumber)
         Register(new HistoScroller(HISTO_PL_OK,0,SendAdr,10091,10092));
        return 1;
   case BIN:
        if(!FiltrNumber)
         Register(new HistoScroller(BIN_OK,0,SendAdr,10110,10109,255));
        return 1;
   case HISTO_PL2:
        if(!FiltrNumber)
         Register(new HistoMod(HISTO_PL_OK1,0,SendAdr));
        return 1;
   case HISTO_PL3:
        if(!FiltrNumber)
         Register(new HistoMod(HISTO_PL_OK2,0,SendAdr));
        return 1;
   case HISTO_PL_OK:
        HistoPrapletimas(0,(int)msg.Param1,0,0);
        return 1;
   case HISTO_PL_OK1:
        HistoPrapletimas(1,0,(int)msg.Param1,(int)msg.Param2);
        return 1;
   case HISTO_PL_OK2:
        HistoPrapletimas(2,0,(int)msg.Param1,(int)msg.Param2);
        return 1;
   case BIN_OK:
        HistoPrapletimas(3,(int)msg.Param1,0,0);
        return 1;
   case LAPLAS1:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Laplas(MHandler,DX,DY,SendAdr,CROSS));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case LAPLAS2:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Laplas(MHandler,DX,DY,SendAdr,DIAGONAL));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case LAPLAS3:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Laplas(MHandler,DX,DY,SendAdr,CLASIC));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case LAPLAS4:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Laplas(MHandler,DX,DY,SendAdr,WEIGHT));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;

   case MEDIAN1x3:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Median1x3(MHandler,DX,DY,SendAdr));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case MEDIAN3x1:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Median3x1(MHandler,DX,DY,SendAdr));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case MEDIAN3x3:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Median3x3(MHandler,DX,DY,SendAdr));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case MEDIAN5x5:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Median5x5(MHandler,DX,DY,SendAdr));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case MEDIANCROSS:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new MedianCross(MHandler,DX,DY,SendAdr));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case AVERAGE_1:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Average(MHandler,DX,DY,SendAdr,0));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case AVERAGE_2:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Average(MHandler,DX,DY,SendAdr,1));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case AVERAGE_3:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Average(MHandler,DX,DY,SendAdr,3));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case AVERAGE_4:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Average(MHandler,DX,DY,SendAdr,2));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case AVERAGE_5:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Average(MHandler,DX,DY,SendAdr,4));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case AVERAGE_6:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Average(MHandler,DX,DY,SendAdr,5));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case DETECT_MAX:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Edge(MHandler,DX,DY,SendAdr,MAX));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case DETECT_MIN:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Edge(MHandler,DX,DY,SendAdr,MIN));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case EWRONGS:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Edge(MHandler,DX,DY,SendAdr,WRONGS));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case WBOUNDARY:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new Edge(MHandler,DX,DY,SendAdr,BOUNDARY));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case HIGH_PASS_1:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new HighPass(MHandler,DX,DY,SendAdr,CLASIC));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case HIGH_PASS_2:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new HighPass(MHandler,DX,DY,SendAdr,WEIGHT));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case HIGH_PASS_3:
        if(!FiltrNumber)
         {
          FiltrNumber = RegisterFilter(new HighPass(MHandler,DX,DY,SendAdr,CROSS));
          MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
         }
        return 1;
   case GRADIENT_1:
        return 1;
   case GRADIENT_2:
        return 1;
   case GRADIENT_3:
        return 1;
   case GRADIENT_4:
        return 1;
   case GRADIENT_5:
        return 1;
   case GRADIENT_6:
        return 1;
   case GRADIENT_7:
        return 1;
   case GRADIENT_8:
        return 1;

   case ITEM_ACTIVE:
        WndActive = WND_ACTIVE;
        Show();
        return 1;
   case ITEM_PASIVE:
        WndActive = WND_PASIVE;
//        Show();
        DisplayFragmentInfo();
        break;
   case HISTOGRAMA:
        HistoHandler = MAlloc(256 * sizeof(long));
        if(HistoHandler == ERROR_HANDLER)
         return 1;
        HistoNumber ++;
        CalculateHistogram(HistoHandler);
        Register(new Histo(GetText(10052),SendAdr,HistoHandler,HistoNumber,
                     (long)(((long)SendAdr << 16) | RegisterNumber),
                     FragmentNumber));
        return 1;
   case FRAGMENT_FILL:
        if(isInit)
         return 0;
        isInit = 1;
//        RegisterNumber = msg.Address;
        WndStatus = FRAGMENT_STATUS_FILL_BEGIN;
        SetMouseShape(SMALL_KREST);
        ViewX = (int)(msg.Param1 >> 16);
        ViewY = (int)(msg.Param1 & 0xffff);
        ViewDX = (int)(msg.Param2 >> 16);
        ViewDY = (int)(msg.Param2 & 0xffff);
        SetMouseArea(ViewX,ViewY,ViewDX,ViewDY);
        return 1;
   case FRAGMENT_HANDLER:
        if(isInit > 1)
         return 0;
        isInit = 2;
        MHandler = msg.Param1;
        MBackup = MAlloc((long)DX*DY);
        MCopyRectangle(MHandler,DX,DY,0,0,MBackup,DX,DY,0,0,DX,DY);
        SendMSGCmd(FRAGMENT_SHOW,SendAdr);
        return 1;
  }
return 0;
}

int FragmentRectangle :: Keyboard(MSG &msg)
{
 long tmp;

 if(FragmentNumber + '0' == msg.Key)
  return 1;
 switch(msg.Key)
  {
   case ESC:
        if(WndStatus == FRAGMENT_STATUS_FILL_MOVE || WndStatus == FRAGMENT_STATUS_FILL_BEGIN)
         {
          WndStatus = 0;
          SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
          SetMouseShape(ARROW);
          SendMSGCmd(FRAGMENT_FILL_ABORT,SendAdr,FragmentNumber);
          return 1;
         }
        break;
   case ALT_BS:
        if(!FiltrNumber)
         {
          tmp = MHandler;
          MHandler = MBackup;
          MBackup = tmp;
          Show();
         }
        return 1;
  }
return 0;
}

void FragmentRectangle :: MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY)
{
 if(MHandler != ERROR_HANDLER)
  MCopyRectangle(MHandler,DX,DY,0,0,
                 Handler,PictSizeDX,PictSizeDY,X - DisplayPlaceX,Y - DisplayPlaceY,DX,DY);
}

int FragmentRectangle :: isOK(void)
{
 if(isInit == 2)
  return 1;

return 0;
}
