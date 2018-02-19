#include <string.h>
#include <stdio.h>
#include <alloc.h>
#include <stdlib.h>
#include "define.hpp"
#include "graph.hpp"
#include "vcmd.hpp"
#include "images.hpp"
#include "gdefine.hpp"
#include "mouse.hpp"
#include "mm.hpp"
#include "proto.hpp"
#include "keys.h"
#include "fragment.hpp"
#include "lupa.hpp"


extern int WarningCounter;
extern int AllMouseEvent;
/*
#define MAX_X_SIZE       250
#define BEGIN_LUPA_SIZE  170
#define MIN_LUPA_SIZE    20
#define MAX_LUPA_SIZE    250
*/

#define MAX_X_SIZE       180
#define BEGIN_LUPA_SIZE  110
#define MIN_LUPA_SIZE    40
#define MAX_LUPA_SIZE    160


#ifndef _LUPA
#define _LUPA

#include "geventha.hpp"

class Lupa : public GEventHandler
{
 int OldMouseEvent;        // isimenam Ar mouse visus event praleidzia
 long MHandler;            // padidinto paveikslo handler
 long PictMHandler;        // pradinio paveikslo handler
 int PictureSizeDX;        // pradinio paveikslo dydis
 int PictureSizeDY;
 int LupaSize;             // koks pradinis didinamo paveisklo dydis
 int ReadX;                // kurioje vieto skaitom is paveikslo
 int ReadY;
 int HScroll;           // scroll bar postumis
 int VScroll;
 long ShadowHandler;

public:
 ~Lupa();
  Lupa(int hScroll,int vScroll,char *wndname);

  virtual void Show();
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
  virtual int Keyboard(MSG &msg);        // klaviaturos
protected:
  virtual void DisplayFragmentInfo(void);
  virtual void BeginMark(int x,int y);
  virtual void EndMark(void);
  virtual void MoveMark(int x,int y);
  void Didinti(int x,int y);
  void HideShadow(int x,int y);
  void ShowShadow(int x,int y);
};
#endif


Lupa :: Lupa(int hScroll,int vScroll,char *wndname)
     :  GEventHandler(0,0,0,0)
{
 OldMouseEvent = AllMouseEvent;
 ShadowHandler = MAlloc((long)MAX_X_SIZE * MAX_X_SIZE);
 PictMHandler = ERROR_HANDLER;
 DX = DY = MAX_X_SIZE;
 LupaSize = BEGIN_LUPA_SIZE;
 HScroll = hScroll;
 VScroll = vScroll;
 WndName = new char [strlen(wndname) + 1];
 if(WndName != 0L)
  strcpy(WndName,wndname);
 MHandler = MAlloc((long)MAX_X_SIZE*MAX_X_SIZE);
 WarningCounter ++;
}

Lupa :: ~Lupa()
{
 AllMouseEvent = OldMouseEvent;

 if(MHandler != ERROR_HANDLER)
  MFree(MHandler);

 if(PictMHandler != ERROR_HANDLER)
  MFree(PictMHandler);

 if(ShadowHandler != ERROR_HANDLER)
  MFree(ShadowHandler);

 if(WndName != 0L)
  delete WndName;
 WarningCounter --;
}

void Lupa :: Show()
{
 if(MHandler != ERROR_HANDLER && PictMHandler != ERROR_HANDLER)
  {
   MDisplay(MHandler,DX,DY,X - (MAX_X_SIZE / 2),Y - (MAX_X_SIZE / 2));
   DisplayFragmentInfo();
   Rectangle(X - (MAX_X_SIZE / 2),Y - (MAX_X_SIZE / 2),MAX_X_SIZE,MAX_X_SIZE,_RED);
  }
}

void Lupa :: DisplayFragmentInfo(void)
{
 char string[10];

 sprintf(string,"x%1.1f",MAX_X_SIZE / (float)LupaSize);
 SetColor(_RED);
 OutStr(X - (MAX_X_SIZE / 2) + 2,Y - (MAX_X_SIZE / 2) + 2,string);
}

ClassType Lupa :: isA()
{
 return _Lupa;
}

void Lupa :: BeginMark(int x,int y)
{
 X = x;
 Y = y;
}

void Lupa :: EndMark(void)
{
 char string[80];

 sprintf(string,"%sx%1.1f",WndName,MAX_X_SIZE / (float)LupaSize);

// MoveMark(x,y);
 Register(new Fragment(string,MHandler,MAX_X_SIZE,MAX_X_SIZE));
 MHandler = -1;
}

void Lupa :: MoveMark(int x,int y)
{
 int tmpx;
 int tmpy;

 tmpx = X;
 tmpy = Y;

 X = x;
 if(ViewX > x - (MAX_X_SIZE / 2))
  X = ViewX + (MAX_X_SIZE / 2);
 if(ViewX + ViewDX < x + (MAX_X_SIZE / 2))
  X = ViewX + ViewDX - (MAX_X_SIZE / 2);

 Y = y;
 if(ViewY > y - (MAX_X_SIZE / 2))
  Y = ViewY + (MAX_X_SIZE / 2);
 if(ViewY + ViewDY < y + (MAX_X_SIZE / 2))
  Y = ViewY + ViewDY - (MAX_X_SIZE / 2);

 ReadX = x;
 if(ViewX > x - (LupaSize / 2))
  ReadX = ViewX + (LupaSize / 2);
 if(ViewX + ViewDX < x + (LupaSize / 2))
  ReadX = ViewX + ViewDX - (LupaSize / 2);
 ReadX -= ViewX;

 ReadY = y;
 if(ViewY > y - (LupaSize / 2))
  ReadY = ViewY + (LupaSize / 2);
 if(ViewY + ViewDY < y + (LupaSize / 2))
  ReadY = ViewY + ViewDY - (LupaSize / 2);
 ReadY -= ViewY;

 Didinti(ReadX,ReadY);
 if(X != tmpx || Y != tmpy)
  {
   ShowShadow(tmpx,tmpy);
   HideShadow(X,Y);
  }
 Show();
}

int Lupa :: Mouse(MSG &msg)
{

 if((msg.Mouse & RBUTTON) || (msg.Mouse & LBUTTON))
  {
   SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
   SetMouseShape(ARROW);
   AllMouseEvent = OldMouseEvent;
   SendMSGCmd(FRAGMENT_FILL_ABORT,RegisterNumber);

   if(msg.Mouse & LBUTTON)
    {
     MoveMark(msg.X,msg.Y);
     EndMark();
    }
   return 1;
  }

 if(msg.Mouse & MOVE)
  MoveMark(msg.X,msg.Y);
 return 1;
}

int Lupa :: Command(MSG &msg)
{

 switch(msg.Cmd)
  {
   case FRAGMENT_FILL:
//        SetMouseShape(MOUSE_HIDE);
        RegisterNumber = msg.Address;
        ViewX = (int)(msg.Param1 >> 16);
        ViewY = (int)(msg.Param1 & 0xffff);
        ViewDX = (int)(msg.Param2 >> 16);
        ViewDY = (int)(msg.Param2 & 0xffff);
        SetMouseArea(ViewX,ViewY,ViewDX,ViewDY);
        OldMouseEvent = AllMouseEvent;
        AllMouseEvent = 1;
        return 1;
   case LUPA_PICTURE_HANDLER:
        PictMHandler = msg.Param1;
        PictureSizeDX = (int)(msg.Param2 >> 16);
        PictureSizeDY = (int)(msg.Param2 & 0xffff);
        BeginMark(ViewX + ViewDX / 2,ViewY + ViewDY / 2);
        Didinti(ViewDX / 2,ViewDY / 2);
        HideShadow(X,Y);
        Show();
        return 1;
  }
return 0;
}

int Lupa :: Keyboard(MSG &msg)
{
 switch(msg.Key)
  {
   case '+':
        if(LupaSize > MIN_LUPA_SIZE)
         {
          LupaSize -= 10;
          if(ReadX > ViewDX - LupaSize / 2)
           ReadX = ViewDX - LupaSize / 2;
          if(ReadY > ViewDY - LupaSize / 2)
           ReadY = ViewDY - LupaSize / 2;
          Didinti(ReadX,ReadY);
          Show();
         }
        return 1;
   case '-':
        if(LupaSize < MAX_LUPA_SIZE)
         {
          LupaSize += 10;
          if(ReadX < LupaSize / 2)
           ReadX = LupaSize / 2;
          if(ReadY < LupaSize / 2)
           ReadY = LupaSize / 2;
          Didinti(ReadX,ReadY);
          Show();
         }
        return 1;
   case CR:
   case ESC:
        SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
        SetMouseShape(ARROW);
        AllMouseEvent = OldMouseEvent;
        SendMSGCmd(FRAGMENT_FILL_ABORT,RegisterNumber);
        if(msg.Key == CR)
         EndMark();
        return 1;
  }
return 0;
}

void Lupa :: Didinti(int x,int y)
{
 long TmpHandle = -1;

 ReadX = x;
 ReadY = y;

 TmpHandle = MAlloc((long)LupaSize*LupaSize);
 MLock(TmpHandle);
 MCopyRectangle( PictMHandler,PictureSizeDX,PictureSizeDY,x + HScroll - (LupaSize / 2),y + VScroll - (LupaSize / 2),
                 TmpHandle,LupaSize,LupaSize,0,0,LupaSize,LupaSize );

 MLock(MHandler);
 magnify(TmpHandle,LupaSize,LupaSize,MHandler,MAX_X_SIZE,MAX_X_SIZE);
 MUnLock(MHandler);
 MFree(TmpHandle);
}

void Lupa :: HideShadow(int x,int y)
{
 
 if (ShadowHandler != ERROR_HANDLER)
  {
   MLock(ShadowHandler);
   MLock(PictMHandler);
   MCopyRectangle(PictMHandler,PictureSizeDX,PictureSizeDY,x + HScroll - (MAX_X_SIZE / 2) - ViewX,y + VScroll - (MAX_X_SIZE / 2) - ViewY,
                 ShadowHandler,MAX_X_SIZE,MAX_X_SIZE,0,0,MAX_X_SIZE,MAX_X_SIZE);
   MUnLock(PictMHandler);
   MUnLock(ShadowHandler);
  }
}

void Lupa :: ShowShadow(int x,int y)
{
 if (ShadowHandler == ERROR_HANDLER)
  SendMSGCmd(OUT_OF_MEMORY);
 else
  MDisplay(ShadowHandler,MAX_X_SIZE,MAX_X_SIZE,x - (MAX_X_SIZE / 2),y - (MAX_X_SIZE / 2));
}
