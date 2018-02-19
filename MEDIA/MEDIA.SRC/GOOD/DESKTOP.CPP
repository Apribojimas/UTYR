#include <dos.h>
#include <string.h>
#include "proto.hpp"
#include "graph.hpp"
#include "bag.hpp"
#include "geventhandler.hpp"
#include "define.hpp"
#include "keys.h"
#include "gdefine.hpp"
#include "mminfo.hpp"
#include "warning.hpp"
#include "mousemer.hpp"
#include "mm.hpp"

Bag *DeskTopQueue = 0L;
int DeskTopCommand = EMPTY;
extern int WarningCounter;

extern unsigned long GroundHandler;
extern int GroundDX,GroundDY;

int Register(Object *Obj)
{
 unsigned int Search = 0;
 int i;
 Object *Tmp;

 if(DeskTopQueue == 0L || Obj == 0L)
  return -1;

 do
  {
   Search ++;
   for(i = 0;i < DeskTopQueue->GetBagSize();i ++)
    {
     Tmp = DeskTopQueue->GetItem(i);
     if(Tmp->RegisterNumber == Search)
      break;
    }
  }while(i != DeskTopQueue->GetBagSize());


 Obj->RegisterNumber = Search;
 SendMSGCmd(ITEM_REGISTER,Obj->RegisterNumber);

 *DeskTopQueue + Obj;
return Obj->RegisterNumber;
}

void InitDeskTop(void)
{
 if(DeskTopQueue != 0L)
  delete DeskTopQueue;
 DeskTopQueue = new Bag(DELETE);
}

void CloseDeskTop(void)
{
 if(DeskTopQueue != 0L)
  delete DeskTopQueue;
 DeskTopQueue = 0L;
}

int Uzdengimas(int x,int y,int dx,int dy);
void ReDraw(void)
{
 int x;
 int y;
 int dx;
 int dy;

 GetViewPort(x,y,dx,dy);
 if(Uzdengimas(x,y,dx,dy))
  {
   if(GroundHandler == ERROR_HANDLER)
    Bar(0,0,GraphMaxX + 1,GraphMaxY + 1,GRAY_4);
   else
    {
     MLock(GroundHandler);
     for(x = 0;x <= GraphMaxX;x += GroundDX)
      for(y = 0;y <= GraphMaxY;y += GroundDY)
       MPutFrame(GroundHandler,GroundDX,GroundDY,x,y);
     MUnLock(GroundHandler);
    }
  }
 Show();
}

int Sutapimas(int x1,int y1,int dx1,int dy1,int x2,int y2,int dx2,int dy2);
void SendActiveCMD(int i, int cmd = 0);
void SendActiveCMD(int i, int cmd)
{
 int j;
 Object *Obj;
 GRectangle *Rec1;
 GRectangle *Rec2;

 if(DeskTopQueue == 0L)
  return ;

 Obj = DeskTopQueue->GetItem(0);
 SendMSGCmd(ITEM_PASIVE,Obj->RegisterNumber);
 Rec1 = (GRectangle *)DeskTopQueue->GetItem(i);
 if(cmd == ITEM_REGISTER)
  SendMSGCmd(ITEM_SHOW,Rec1->RegisterNumber);
 else
  for(j = 0;j < i;j ++)
   {
    Rec2 = (GRectangle *)DeskTopQueue->GetItem(j);
    if(Sutapimas(Rec1->GetX(),Rec1->GetY(),Rec1->GetDX(),Rec1->GetDY(),
                Rec2->GetX(),Rec2->GetY(),Rec2->GetDX(),Rec2->GetDY()))
     {
      SendMSGCmd(ITEM_SHOW,Rec1->RegisterNumber);
      break;
     }
   }
 SendMSGCmd(ITEM_ACTIVE,Rec1->RegisterNumber);
 DeskTopQueue->ChangePlace(i,0);
}

void DeskTopMouse(MSG &msg)
{
 int i;
 Object *Obj;

 for(i = 0;i < DeskTopQueue->GetBagSize();i++)
  {
   Obj = DeskTopQueue->GetItem(i);
   if(EventHandler(Obj,msg))
    {
     if(i)
      SendActiveCMD(i);
     break;
    }
  }
}

void DeskTopKeyboard(MSG &msg)
{
 int i;
 Object *Obj;

 switch(msg.Key)
  {
   case CTRL_F10:
        geninterrupt(3);
        break;
   case ALT_M:
        if(WarningCounter)
         break;
	SendMSGCmd(ITEM_STATUS,Register(new MouseMer));
        break;
   case ALT_I:
        if(WarningCounter)
         break;
	SendMSGCmd(ITEM_ACTIVE,Register(new MemManInfo));
        break;
   case ALT_R:
        if(WarningCounter)
         break;
	SendMSGCmd(REDRAW);
        break;
   case F6:
        if(WarningCounter)
         break;
        msg.Type = COMMAND;
        msg.Cmd = ITEM_STATUS;
        if(DeskTopQueue->GetBagSize() > 1)
        for(i = DeskTopQueue->GetBagSize() - 1;i > 0;i--)
         {
          Obj = DeskTopQueue->GetItem(i);
	  if(EventHandler(Obj,msg))
           {
	    if(i)
             SendActiveCMD(i);
            break;
           }
         }
        break;
   case ALT_X:
        DeskTopCommand = DESKTOP_EXIT;
        msg.Type = COMMAND;
        msg.Cmd = ITEM_DESTROY;
        for(i = 0;i < DeskTopQueue->GetBagSize();i++)
         {
          Obj = DeskTopQueue->GetItem(i);
	  EventHandler(Obj,msg);
         }
	break;
   case KEY_MODE_640:
        if(WarningCounter)
         break;
        SendMSGCmd(VIDEO_MODE_640);
        break;
   case KEY_MODE_800:
        if(WarningCounter)
         break;
        SendMSGCmd(VIDEO_MODE_800);
        break;
   case KEY_MODE_1024:
        if(WarningCounter)
         break;
        SendMSGCmd(VIDEO_MODE_1024);
        break;
   default:
        for(i = 0;i < DeskTopQueue->GetBagSize();i++)
         {
          Obj = DeskTopQueue->GetItem(i);
	  if(EventHandler(Obj,msg))
           {
	    if(i)
             SendActiveCMD(i);
            break;
           }
         }
  }
}

void DeskTopCmd(MSG &msg)
{
 int i;
 Object *Obj;
 GRectangle *gr;

 switch(msg.Cmd)
  {
   case OUT_OF_MEMORY:
        SendMSGCmd(ITEM_ACTIVE,Register(new Warning(10)));
        break;
   case TERMINATE_FILTER:
        TerminateFilter((int)msg.Param1);
        break;
   case DESKTOP_EXIT:
	DeskTopCommand = DESKTOP_EXIT;
        msg.Type = COMMAND;
        msg.Cmd = ITEM_DESTROY;
        for(i = 0;i < DeskTopQueue->GetBagSize();i++)
         {
          Obj = DeskTopQueue->GetItem(i);
	  EventHandler(Obj,msg);
         }
	break;
   case REDRAW:
        ReDraw();
        break;
   case ITEM_DESTROY:
        for(i = 0;i < DeskTopQueue->GetBagSize();i++)
         {
          Obj = DeskTopQueue->GetItem(i);
          if(Obj->RegisterNumber == msg.Address && msg.Address)
           {
  	    EventHandler(Obj,msg);
            gr = (GRectangle *)Obj;
            SetViewPort(gr->GetX(),gr->GetY(),gr->GetDX(),gr->GetDY());
            *DeskTopQueue - i;                   // isemetam item
            SendMSGCmd(ITEM_ACTIVE);
            SendMSGCmd(REDRAW);
            break;
           }
         }
        break;
   default:
        if(msg.Cmd == VIDEO_MODE_640)
         if(!SetVideoMode(MODE_640))
          SendMSGCmd(REDRAW);
         else
          break;
        if(msg.Cmd == VIDEO_MODE_800)
         if(!SetVideoMode(MODE_800))
          SendMSGCmd(REDRAW);
         else
          break;
        if(msg.Cmd == VIDEO_MODE_1024)
         if(!SetVideoMode(MODE_1024))
          SendMSGCmd(REDRAW);
         else
          break;
	for(i = 0;i < DeskTopQueue->GetBagSize();i++)
         {
          Obj = DeskTopQueue->GetItem(i);
          if(msg.Address)                           // patikrinam ar globaline cmd
           if(msg.Address != Obj->RegisterNumber)   // patikrinam ar sutampa adresas
            continue;

          if(EventHandler(Obj,msg))
           {
            if(i)
             SendActiveCMD(i,msg.Cmd);
            break;
           }
         }
  }
}

void Show(void)
{
 int i;
 int j;
 int trigger;
 int x;
 int y;
 int dx;
 int dy;
 GRectangle *gr;
 GEventHandler *ge;


 if(DeskTopQueue == 0L)
  return ;
 for(i = DeskTopQueue->GetBagSize() - 1;i >= 0;i --)
  {
   if(i == 0)
    SetViewPort(0,0,GraphMaxX + 1,GraphMaxY + 1);
   gr = (GRectangle *)DeskTopQueue->GetItem(i);
   GraphBoundary(gr->GetX(),gr->GetY(),gr->GetDX(),gr->GetDY());
   x = BoundaryX;
   y = BoundaryY;
   dx = BoundaryDX;
   dy = BoundaryDY;
   trigger = 1;
   for(j = i - 1;j >= 0;j --)
    {
     ge = (GEventHandler *)DeskTopQueue->GetItem(j);
     if(ge->WndStatus == WND_ICON)
      continue;
     GraphBoundary(ge->GetX(),ge->GetY(),ge->GetDX(),ge->GetDY());
     if(x >= BoundaryX &&
        x + dx <= BoundaryX + BoundaryDX &&
        y >= BoundaryY &&
        y + dy <= BoundaryY + BoundaryDY)
      {
       trigger = 0;
       break;
      }
    }
   if(trigger)
    gr->Show();
  }
}

int CheckEvent(void)
{
 MSG msg;

 if(DeskTopQueue == 0L)
  return 0;

 if(GetMSG(msg))
  {
   switch (msg.Type)
    {
     case KEYBOARD:
	  DeskTopKeyboard(msg);
	  break;
     case MOUSE:
	  DeskTopMouse(msg);
	  break;
     case COMMAND:
	  DeskTopCmd(msg);
	  break;
    }
   return 1;
  }
 else
  TaskRun();

return 0;
}

int Sutapimas(int x1,int y1,int dx1,int dy1,int x2,int y2,int dx2,int dy2)
{
 int i = 1;
 int j;

 if(Clip(x1,y1,dx1,i,x2,y2,dx2,dy2))        // V
  return 1;

 if(Clip(x1,y1,i,dy1,x2,y2,dx2,dy2))        // K
  return 1;

 j = x1 + dx1 - 1;
 if(Clip(j,y1,i,dy1,x2,y2,dx2,dy2))         // D
  return 1;

 j = y1 + dy1 - 1;
 if(Clip(x1,j,dx1,i,x2,y2,dx2,dy2))         // A
  return 1;

 // patikrinam ar 1 kvadratas yra 2 kvadrate
 if(x1 >= x2 && x1 <= x2 + dx2 &&
    y1 >= y2 && y1 <= y2 + dy2)
  return 1;

 // patikrinam ar 2 kvadratas yra 1 kvadrate
 if(x2 >= x1 && x2 <= x1 + dx1 &&
    y2 >= y1 && y2 <= y1 + dy1)
  return 1;

 return 0;
}

int Uzdengimas(int x,int y,int dx,int dy)
{
 int i;
 int x1;
 int y1;
 int dx1;
 int dy1;
 GEventHandler *Rec;

 if(DeskTopQueue == 0L)
  return 1;

 for(i = 0;i < DeskTopQueue->GetBagSize();i ++)
  {
   Rec = (GEventHandler *)DeskTopQueue->GetItem(i);
   if(Rec->WndStatus == WND_ICON)
    continue;
   x1 = Rec->GetX();
   y1 = Rec->GetY();
   dx1 = Rec->GetDX();
   dy1 = Rec->GetDY();
   if(x > x1 &&
      x + dx < x1 + dx1 &&
      y > y1 &&
      y + dy < y1 + dy1)
   return 0;
  }
 return 1;
}