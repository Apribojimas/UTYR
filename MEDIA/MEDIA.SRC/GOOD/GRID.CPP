#include <math.h>
#include <stdio.h>
#include "mouse.hpp"
#include "graph.hpp"
#include "proto.hpp"
#include "define.hpp"
#include "vcmd.hpp"
#include "gbutton.hpp"
#include "gettext.hpp"
#include "point.hpp"
#include "grid.hpp"

extern int AllMouseEvent;
extern int WarningCounter;
int Atstumas(Point &p1,Point &p2);

#ifndef _GRID
#define _GRID

#include "gwindow.hpp"
#include "calstr.hpp"
#include "point.hpp"

#define KOORDINATES  1
#define TINKLELIS    2

class Grid : public GWindow
{
 int What;
 int Init;
 int MouseEvent;
 float GridX;
 float GridY;
 Point P1;
 Point P2;
 Group MyGroup;
 CalStruct *CStruct;

public:
 ~Grid();
  Grid(int x,int y,CalStruct *cstruct,int what = TINKLELIS);

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual int EventHandler(MSG &msg);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
//  virtual int Keyboard(MSG &msg);        // klaviaturos
private:
  void ShowGrid(int x,int y);
  void DisplayInfo(int x,int y);
  int isCalculateShow(void);
};
#endif

Grid :: Grid(int x,int y,CalStruct *cstruct,int what)
             :  GWindow(x,y,150,130,GetText(10030),WND_GRAPH | WND_CLOSE_BUTTON)
{
 Init = 0;
 What = what;
 GridX = 0;
 GridY = 0;
 MouseEvent = AllMouseEvent;
 AllMouseEvent = 1;
 CStruct = cstruct;

 MyGroup + new GButton(0,0,140,20,GetText(10004),TAIP_NE_CANCEL);

 if(CStruct)
  {
   SetMouseArea(CStruct->ViewX,CStruct->ViewY,CStruct->ViewDX,CStruct->ViewDY);
   SetMouseShape(SMALL_KREST);
  }
 WarningCounter ++;
}

Grid :: ~Grid()
{
 SetMouseShape(ARROW);
 AllMouseEvent = MouseEvent;
 WarningCounter --;
}

#pragma argsused
void Grid :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 char str[20];

 SetColor(GRAY_2);
 SetGroundColor(GRAY_11);
 Bar(x,y,dx,dy,GRAY_11);
 sprintf(str,"%+8.8s",GetText(10029));
 OutText(x + 5,y +  5,str);
 sprintf(str,"%+8.8s","X :");
 OutText(x + 5,y + 25,str);
 sprintf(str,"%+8.8s","Y :");
 OutText(x + 5,y + 45,str);
 sprintf(str,"%+8.8s",GetText(10033));
 OutText(x + 5,y + 65,str);
 sprintf(str,"%+8.8s","D :");
 OutText(x + 5,y + 85,str);

 MyGroup.SetXY(x + 5,y + dy - 25);
 MyGroup.Show();

 DisplayInfo(x,y);
}

ClassType Grid :: isA()
{
 return _Grid;
}

int Grid :: EventHandler(MSG &msg)
{
 int i = 0;

 i = GWindow :: EventHandler(msg);
 if(MyGroup.EventHandler(msg))
  i ++;

return i;
}

int Grid :: Mouse(MSG &msg)
{
 if(Init == 1)
  GWindow :: Mouse(msg);

 if(Init == 0)
  {
   if(msg.Mouse & LBUTTON)
    {
     Init = 1;
     ShowGrid(msg.X,msg.Y);
     SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
   }
  }

 if(msg.Mouse & MOVE)
  {
   if(msg.X < CStruct->ViewX || msg.Y < CStruct->ViewY ||
      msg.X > CStruct->ViewX + CStruct->ViewDX || msg.Y > CStruct->ViewY + CStruct->ViewDY)
    SetMouseShape(ARROW);
   else
    {
     SetMouseShape(SMALL_KREST);
     if(Init == 1)
      {
       SetWriteMode(XOR_PUT);
       Line(P1.x,P1.y,P2.x,P2.y,_RED);
       P2.x = msg.X;
       P2.y = msg.Y;
       Line(P1.x,P1.y,P2.x,P2.y,_RED);
       SetWriteMode(COPY_PUT);
       GridX = (signed)(msg.X - P1.x) * CStruct->Mastelis;
       GridY = (signed)(msg.Y - P1.y) * CStruct->Mastelis;
       DisplayInfo(ViewX,ViewY);
      }
    }
  }

return 1;
}

int Grid :: Command(MSG &msg)
{
 switch(msg.Cmd)
  {
   case TAIP_NE_CANCEL:
        SendMSGCmd(ITEM_SHOW,CStruct->RegisterNumber);
        SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        SendMSGCmd(GRID_END,0,(long)CStruct);
        return 1;
  }
 return GWindow :: Command(msg);
}

void Grid :: ShowGrid(int x,int y)
{
 int i;
 int tmpx;
 int tmpy;
 int Step;
 char str[10];

 if((!CStruct->Mastelis) || (!CStruct->Scale))
  return;

 if(isCalculateShow())
  {
   SendMSGCmd(ITEM_SHOW,CStruct->CalculateRegisterNumber);
   SendMSGCmd(ITEM_SHOW,RegisterNumber);
  }

 SetColor(_GREEN);
 Step = CStruct->Scale / CStruct->Mastelis;
 P2.x = x;
 P2.y = y;
 P1 = P2;
 if(Step == 0.)
  {
   HLine(CStruct->ViewX,y,CStruct->ViewDX,_RED);
   VLine(x,CStruct->ViewY,CStruct->ViewDY,_RED);
   OutStr(x,y,"0");
   return;
  }

 SetWriteMode(XOR_PUT);
 Line(P1.x,P1.y,P2.x,P2.y,_RED);
 SetWriteMode(COPY_PUT);

 switch(What)
  {
   case TINKLELIS:
        for(tmpy = y;tmpy < CStruct->ViewY + CStruct->ViewDY;tmpy += Step)
         HLine(CStruct->ViewX,tmpy,CStruct->ViewDX,_RED);

        for(tmpy = y - Step;tmpy > CStruct->ViewY;tmpy -= Step)
         HLine(CStruct->ViewX,tmpy,CStruct->ViewDX,_RED);

        for(tmpx = x;tmpx < CStruct->ViewX + CStruct->ViewDX;tmpx += Step)
         VLine(tmpx,CStruct->ViewY,CStruct->ViewDY,_RED);

        for(tmpx = x - Step;tmpx > CStruct->ViewX;tmpx -= Step)
         VLine(tmpx,CStruct->ViewY,CStruct->ViewDY,_RED);
        break;
   case KOORDINATES:
        HLine(CStruct->ViewX,y,CStruct->ViewDX,_RED);
        VLine(x,CStruct->ViewY,CStruct->ViewDY,_RED);
        break;
  }


 Step = 1. / CStruct->Mastelis;

 if(!Step)
  return;

 for(tmpy = y,i = 0;tmpy + 16 < CStruct->ViewY + CStruct->ViewDY;tmpy += Step,i --)
  {
   Bar(x,tmpy,2,2);
   sprintf(str,"%-i",i);
   OutStr(x,tmpy,str);
  }

 for(tmpy = y - Step,i = 1;tmpy > CStruct->ViewY;tmpy -= Step,i ++)
  {
   Bar(x,tmpy,2,2);
   sprintf(str,"%-i",i);
   OutStr(x,tmpy,str);
  }

 for(tmpx = x + Step,i = 1;tmpx + 8 < CStruct->ViewX + CStruct->ViewDX;tmpx += Step,i ++)
  {
   Bar(tmpx,y,2,2);
   sprintf(str,"%-i",i);
   OutStr(tmpx,y,str);
  }

 for(tmpx = x - Step,i = - 1;tmpx > CStruct->ViewX;tmpx -= Step,i --)
  {
   Bar(tmpx,y,2,2);
   sprintf(str,"%-i",i);
   OutStr(tmpx,y,str);
  }
}

void Grid :: DisplayInfo(int x,int y)
{
 float D;
 int Angle;
 char str[20];

 SetColor(GRAY_2);
 SetGroundColor(GRAY_11);

 sprintf(str,"%3.2f",CStruct->Scale);
 OutText(x + 85,y +  5,str);
 sprintf(str,"%+3.2f",GridX);
 OutText(x + 85,y + 25,str);
 sprintf(str,"%+3.2f",GridY);
 OutText(x + 85,y + 45,str);

 D = (float)(Atstumas(P1,P2) * CStruct->Mastelis);
 if(P1==P2)
  Angle = 0;
 else
  {
   Angle = atan2((signed)(P1.y - P2.y),(signed)(P2.x - P1.x)) * 180 / M_PI;
   if(Angle < 0)
    Angle += 360;
  }
 sprintf(str,"%-03i",Angle);
 OutText(x + 85,y + 65,str);

 sprintf(str,"%3.2f",D);
 OutText(x + 85,y + 85,str);
}

int Sutapimas(int x1,int y1,int dx1,int dy1,int x2,int y2,int dx2,int dy2);
int Grid :: isCalculateShow(void)
{
 return Sutapimas(CStruct->ViewX,CStruct->ViewY,CStruct->ViewDX,CStruct->ViewDY,
                  CStruct->CViewX,CStruct->CViewY,CStruct->CViewDX,CStruct->CViewDY);
}
