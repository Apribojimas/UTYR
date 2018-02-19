#include <math.h>
#include <stdio.h>
#include "keys.h"
#include "graph.hpp"
#include "proto.hpp"
#include "mousemer.hpp"
#include "gettext.hpp"
#include "mouse.hpp"


extern int AllMouseEvent;

#ifndef _MOUSE_MER
#define _MOUSE_MER

#include "gwindow.hpp"

class MouseMer : public GWindow
{
 int MouseEventStatus;
 int MemMouseX;
 int MemMouseY;
 int LockMouseX;
 int LockMouseY;
public:
 ~MouseMer();
  MouseMer();

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);          // mouse eventai
  virtual int Keyboard(MSG &msg);       // klaviaturos
  virtual int Command(MSG &msg);        // apdorosime komandas
private:
  void OutMouseInfo(void);
};
#endif

MouseMer :: MouseMer()
	 :  GWindow(639 - 82,0,72,76,GetText(10001),WND_TEXT | WND_CLOSE_BUTTON,0,0)
{
 MouseEventStatus = AllMouseEvent;
 LockMouseX = 0;
 LockMouseY = 0;
 MemMouseX = 0;
 MemMouseY = 0;
}

MouseMer :: ~MouseMer()
{
 AllMouseEvent = MouseEventStatus;
}

#pragma argsused
void MouseMer :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 Bar(x,y,dx,dy,GRAY_9);
 OutMouseInfo();
}

void MouseMer :: OutMouseInfo(void)
{
 char str[10];

 SetColor(_BLACK);
 SetGroundColor(GRAY_9);

 if(WndActive == WND_ACTIVE)
  {
   sprintf(str," X :%4.4i ",GraphMouseX);
   OutBigText(X + 5,Y + 33,str);
   sprintf(str," Y :%4.4i ",GraphMouseY);
   OutBigText(X + 5,Y + 35 + CharHeight(),str);
   sprintf(str," DX:%4.4i ",abs(GraphMouseX - LockMouseX));
   OutBigText(X + 5,Y + 37 + 2 * CharHeight(),str);
   sprintf(str," DY:%4.4i ",abs(GraphMouseY - LockMouseY));
   OutBigText(X + 5,Y + 39 + 3 * CharHeight(),str);
  }
 else
  {
   sprintf(str," X :%4.4i ",MemMouseX);
   OutBigText(X + 5,Y + 33,str);
   sprintf(str," Y :%4.4i ",MemMouseY);
   OutBigText(X + 5,Y + 35 + CharHeight(),str);
   sprintf(str," DX:%4.4i ",abs(MemMouseX - LockMouseX));
   OutBigText(X + 5,Y + 37 + 2 * CharHeight(),str);
   sprintf(str," DY:%4.4i ",abs(MemMouseY - LockMouseY));
   OutBigText(X + 5,Y + 39 + 3 * CharHeight(),str);
  }
}

int MouseMer :: Mouse(MSG &msg)
{
 if(WndActive == WND_ACTIVE)
  OutMouseInfo();
return GWindow :: Mouse(msg);
}

int MouseMer :: Command(MSG &msg)
{
 switch(msg.Cmd)
  {
   case ITEM_ACTIVE:
	MouseEventStatus = AllMouseEvent;
	AllMouseEvent = 1;
	break;
   case ITEM_PASIVE:
	AllMouseEvent = MouseEventStatus;
        MemMouseX = GraphMouseX;
        MemMouseY = GraphMouseY;
	break;
  }
return GWindow :: Command(msg);
}

int MouseMer :: Keyboard(MSG &msg)
{
 if(!WndEvent)
 switch(msg.Key)
  {
   case HOME:
        MouseMove(0,GraphMouseY);
        OutMouseInfo();
        return 1;
   case END:
        MouseMove(GraphMaxX,GraphMouseY);
        OutMouseInfo();
        return 1;
   case PGUP:
        MouseMove(GraphMouseX,0);
        OutMouseInfo();
        return 1;
   case PGDN:
        MouseMove(GraphMouseX,GraphMaxY);
        OutMouseInfo();
        return 1;
   case LEFT:
        MouseMove(GraphMouseX - 1,GraphMouseY);
        OutMouseInfo();
        return 1;
   case RIGHT:
        MouseMove(GraphMouseX + 1,GraphMouseY);
        OutMouseInfo();
        return 1;
   case UP:
        MouseMove(GraphMouseX,GraphMouseY - 1);
        OutMouseInfo();
        return 1;
   case DOWN:
        MouseMove(GraphMouseX,GraphMouseY + 1);
        OutMouseInfo();
        return 1;
   case SHIFT_LEFT:
        MouseMove(GraphMouseX - 10,GraphMouseY);
        OutMouseInfo();
        return 1;
   case SHIFT_RIGHT:
        MouseMove(GraphMouseX + 10,GraphMouseY);
        OutMouseInfo();
        return 1;
   case SHIFT_UP:
        MouseMove(GraphMouseX,GraphMouseY - 10);
        OutMouseInfo();
        return 1;
   case SHIFT_DOWN:
        MouseMove(GraphMouseX,GraphMouseY + 10);
        OutMouseInfo();
        return 1;
   case SPACE:
        LockMouseX = GraphMouseX;
        LockMouseY = GraphMouseY;
        OutMouseInfo();
        return 1;
  }
 return GWindow :: Keyboard(msg);
}

ClassType MouseMer :: isA()
{
 return _MouseMer;
}
