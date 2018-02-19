#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "mouse.hpp"
#include "graph.hpp"
#include "proto.hpp"
#include "define.hpp"
#include "vcmd.hpp"
#include "gbutton.hpp"
#include "ginput.hpp"
#include "gettext.hpp"
#include "kalibrav.hpp"

#define max(a,b)    (((a) > (b)) ? (a) : (b))

extern int AllMouseEvent;
extern int WarningCounter;

#ifndef _KALIBRAVIMAS
#define _KALIBRAVIMAS

#include "gwindow.hpp"
#include "calstr.hpp"
#include "point.hpp"

class Kalibravimas : public GWindow
{
 int Init;
 int MouseEvent;
 Point P1;
 Point P2;
 Group MyGroup;
 CalStruct *CStruct;

public:
 ~Kalibravimas();
  Kalibravimas(int x,int y,CalStruct *cstruct);

  virtual int EventHandler(MSG &msg);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
//  virtual int Keyboard(MSG &msg);        // klaviaturos
private:
  void BeginMove(int x,int y);
  void EndMove(int x,int y);
  void MoveTo(int x,int y);
};
#endif

Kalibravimas :: Kalibravimas(int x,int y,CalStruct *cstruct)
             :  GWindow(x,y,220,80,GetText(10024))
{
 Init = 0;
 MouseEvent = AllMouseEvent;
 AllMouseEvent = 1;
 CStruct = cstruct;

 MyGroup + new GInput(115,5,6)
         + new GButton(115,55,100,20,GetText(2),TAIP_NE_CANCEL)
         + new GButton(5,55,100,20,GetText(1),TAIP_NE_OK)
         + new GInput(115,30,6);

 if(CStruct)
  {
   SetMouseArea(CStruct->ViewX,CStruct->ViewY,CStruct->ViewDX,CStruct->ViewDY);
   SetMouseShape(SMALL_KREST);
  }
 WarningCounter ++;
}

Kalibravimas :: ~Kalibravimas()
{
 SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
 AllMouseEvent = MouseEvent;
 SetMouseShape(ARROW);
 WarningCounter --;
}

#pragma argsused
void Kalibravimas :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 char str[100];

 SetColor(GRAY_2);
 SetGroundColor(GRAY_11);
 Bar(x,y,dx,dy,GRAY_11);
 sprintf(str,"%12.12s",GetText(10028));
 OutText(x,y + 8,str);
 sprintf(str,"%12.12s",GetText(10029));
 OutText(x,y + 32,str);

 MyGroup.SetXY(x,y);
 MyGroup.Show();
}

ClassType Kalibravimas :: isA()
{
 return _Kalibravimas;
}

int Kalibravimas :: EventHandler(MSG &msg)
{
 int i = 0;

 i = GWindow :: EventHandler(msg);
 if(!WndEvent && Init == 2)
  if(MyGroup.EventHandler(msg))
   i ++;

return i;
}

int Kalibravimas :: Mouse(MSG &msg)
{

 if(Init == 2)
  GWindow :: Mouse(msg);
 else
  {
   if(msg.Mouse & LBUTTON)
    {
     if(Init == 0)
      BeginMove(msg.X,msg.Y);
     else
      EndMove(msg.X,msg.Y);
     return 1;
    }

   if(msg.Mouse & MOVE)
    {
     if(Init == 1)
      MoveTo(msg.X,msg.Y);
    }

   if(msg.Mouse & RBUTTON)
    {
     SendMSGCmd(KALIBRAVIMAS_CANCEL,0,(long)CStruct);
     SendMSGCmd(ITEM_DESTROY,RegisterNumber);
     SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
     return 1;
    }
  }

return 1;
}

int Kalibravimas :: Command(MSG &msg)
{
 int i;
 GInput *gi;

 switch(msg.Cmd)
  {
   case TAIP_NE_OK:
        if(CStruct)
         {
          gi = (GInput *)MyGroup.GetItem(0);
          CStruct->Mastelis = atof(gi->GetItem());
          i = max(abs(P1.x - P2.x),abs(P1.y - P2.y));
          CStruct->Mastelis /= i;
          gi = (GInput *)MyGroup.GetItem(3);
          CStruct->Scale = atof(gi->GetItem());
          if(CStruct->Scale == 0)
           CStruct->Scale = 0.1;
         }
        SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        SendMSGCmd(KALIBRAVIMAS_OK,0,(long)CStruct);
        return 1;
   case TAIP_NE_CANCEL:
        SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        SendMSGCmd(KALIBRAVIMAS_CANCEL,0,(long)CStruct);
        return 1;
  }
 return GWindow :: Command(msg);
}

void Kalibravimas :: BeginMove(int x,int y)
{
 P2.x = x;
 P2.y = y;
 P1 = P2;

 SetWriteMode(XOR_PUT);
 Line(P1.x,P1.y,P2.x,P2.y,_RED);
 SetWriteMode(COPY_PUT);

 Init = 1;
}

void Kalibravimas :: MoveTo(int x,int y)
{
 SetWriteMode(XOR_PUT);
 Line(P1.x,P1.y,P2.x,P2.y,_RED);

 P2.x = x;
 P2.y = y;

 Line(P1.x,P1.y,P2.x,P2.y,_RED);
 SetWriteMode(COPY_PUT);
}

void Kalibravimas :: EndMove(int x,int y)
{
 MoveTo(x,y);

 SetWriteMode(XOR_PUT);
 Line(P1.x,P1.y,P2.x,P2.y,_RED);
 SetWriteMode(COPY_PUT);

 Init = 2;

 SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
 AllMouseEvent = MouseEvent;
 SetMouseShape(ARROW);
}
