#include "graph.hpp"
#include "shape.hpp"
#include "gscroll.hpp"
#include "gdefine.hpp"

#define SCROLL_BUTTON_FIRST   1
#define SCROLL_BUTTON_SECOND  2
#define SCROLL_BUTTON_MOVE    3

#ifndef _GSCROLL
#define _GSCROLL

#include "geventha.hpp"

class GScroll : public GEventHandler
{
 int ScrollType;
 int ScrollStatus;
 unsigned int MaxPos;
 unsigned int Position;   // kurio vietoje yra vid. buttonas
 int TmpPosition;
public:
 ~GScroll();
  GScroll(int x,int y,int delta,int type,int scale = 0);

  void SetMaxPos(int scale);
  int  GetMaxPos(void);
  void SetPos(int scale);
  int  GetPos(void);
  virtual void Show(void);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);          // mouse eventai
private:
  unsigned int ButtonPlace(void);
  int isFirst(int x,int y);
  int isSecond(int x,int y);
  int isPlace(int x,int y);
  void PlaceBeginMove(void);
  void PlaceMoveTo(int x,int y);
  void PlaceEndMove(void);
  void ButtonEvent(int i);
};
#endif

GScroll :: GScroll(int x,int y,int delta,int type,int scale)
        :  GEventHandler(x,y)
{
 ScrollStatus = 0;
 ScrollType = type;
 MaxPos = scale;
 Position = 0;
 if(ScrollType & VERTICAL)
  {
   DX = 16;
   DY = delta;
  }
 else
  {
   DY = 16;
   DX = delta;
  }
}

GScroll :: ~GScroll()
{
}

int GScroll :: GetPos(void)
{
 return Position;
}

void GScroll :: Show(void)
{
 if(ScrollType & VERTICAL)
  {
   ButtonDraw(X,Y,16,16,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
   ButtonDraw(X,Y + DY - 16,16,16,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
   Bar(X,Y + 16,16,DY - 32,GRAY_12);
   Rectangle(X,Y + 16,DX,DY - 32,_BLACK);
   if(MaxPos)
    ButtonDraw(X + 1,Y + 16 + ButtonPlace(),14,14,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
  }
 else
  {
   ButtonDraw(X,Y,16,16,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
   ButtonDraw(X + DX - 16,Y,16,16,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
   Bar(X + 16,Y,DX - 32,16,GRAY_12);
   Rectangle(X + 16,Y,DX - 32,DY,_BLACK);
   if(MaxPos)
    ButtonDraw(X + 16 + ButtonPlace(),Y + 1,14,14,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
  }
}

void GScroll :: ButtonEvent(int i)
{
 int Delta;

 if(ScrollType & VERTICAL)
  {
   if(MaxPos)
    {
     Delta = ((float)(DY - 32 - 14) / MaxPos) * Position;
     Bar(X + 1,Y + 16 + Delta,14,14,GRAY_12);
    }
  }
 else
  {
   if(MaxPos)
    {
     Delta = ((float)(DX - 32 - 14) / MaxPos) * Position;
     Bar(X + 16 + Delta,Y + 1,14,14,GRAY_12);
    }
  }
 SetPos(Position + i);
 if(ScrollType & VERTICAL)
  {
   if(i == -1)
    ButtonDraw(X,Y,16,16,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
   else
    ButtonDraw(X,Y + DY - 16,16,16,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
   if(MaxPos)
    ButtonDraw(X + 1,Y + 16 + ButtonPlace(),14,14,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
  }
 else
  {
   if(i == -1)
    ButtonDraw(X,Y,16,16,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
   else
    ButtonDraw(X + DX - 16,Y,16,16,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
   if(MaxPos)
    ButtonDraw(X + 16 + ButtonPlace(),Y + 1,14,14,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
  }
}

int GScroll :: GetMaxPos(void)
{
 return MaxPos;
}

void GScroll :: SetMaxPos(int scale)
{
 MaxPos = scale;
 if(Position > MaxPos)
  Position = MaxPos;
}

void GScroll :: SetPos(int scale)
{
 if(scale < 0)
  scale = 0;
 if(scale <= MaxPos)
  Position = scale;
 if(scale > MaxPos)
  Position = MaxPos;
}

unsigned int GScroll :: ButtonPlace(void)
{
 if(MaxPos)
  {
   if(ScrollType & VERTICAL)
    return ((float)(DY - 32 - 14) / MaxPos) * Position;
   else
    return ((float)(DX - 32 - 14) / MaxPos) * Position;
  }
 else
  return 0;
}

ClassType GScroll :: isA()
{
 return _GScroll;
}

int GScroll :: isFirst(int x,int y)
{
 if(x > X && x < X + 16 && y > Y && y < Y + 16)
  return 1;
 return 0;
}

int GScroll :: isSecond(int x,int y)
{
 if(ScrollType & VERTICAL)
  {
   if(x > X && x < X + 16 && y > Y + DY - 16 && y < Y + DY)
    return 1;
  }
 else
  if(x > X  + DX - 16 && x < X + DX && y > Y && y < Y + 16)
   return 1;

 return 0;
}

int GScroll :: isPlace(int x,int y)
{
 if(ScrollType & VERTICAL)
  {
   if(x > X && x < X + 16 &&
      y > Y + 16 + ButtonPlace() && y < Y + 16 + ButtonPlace() + 14)
    return 1;
  }
 else
  if(x > X + 16 + ButtonPlace() && x < X + 16 + ButtonPlace() + 14 &&
     y > Y && y < Y + 16)
   return 1;

 return 0;
}

void GScroll :: PlaceBeginMove(void)
{
 TmpPosition = Position;
 SetColor(_BLACK);
 SetWriteMode(XOR_PUT);
 if(ScrollType & VERTICAL)
  Rectangle(X + 1,Y + 16 + ButtonPlace(),14,14);
 else
  Rectangle(X + 16 + ButtonPlace(),Y + 1,14,14);
 SetWriteMode(COPY_PUT);
}

void GScroll :: PlaceMoveTo(int x,int y)
{
 int Delta;
 int MemPlace = TmpPosition;

 SetWriteMode(XOR_PUT);
 SetColor(_BLACK);
 if(ScrollType & VERTICAL)
  {
   if(y > Y + 16 && y < Y + DY - 16 - 14)
    TmpPosition = (y - Y - 16) / ((float)(DY - 16 - 16 - 14) / MaxPos) + 0.5;
   if(y < Y + 16)
    TmpPosition = 0;
   if(y > Y + DY - 16 - 14)
    TmpPosition = MaxPos;
   if(MemPlace != TmpPosition)
    {
     Delta = ((float)(DY - 32 - 14) / MaxPos) * MemPlace;
     Rectangle(X + 1,Y + 16 + Delta,14,14);
     Delta = ((float)(DY - 32 - 14) / MaxPos) * TmpPosition;
     Rectangle(X + 1,Y + 16 + Delta,14,14);
    }
  }
 else
  {
   if(x > X + 16 && x < X + DX - 16 - 14)
    TmpPosition = (x - X - 16) / ((float)(DX - 16 - 16 - 14) / MaxPos) + 0.5;
   if(x < X + 16)
    TmpPosition = 0;
   if(x > X + DX - 16 - 14)
    TmpPosition = MaxPos;
   if(MemPlace != TmpPosition)
    {
     Delta = ((float)(DX - 32 - 14) / MaxPos) * MemPlace;
     Rectangle(X + 16 + Delta,Y + 1,14,14);
     Delta = ((float)(DX - 32 - 14) / MaxPos) * TmpPosition;
     Rectangle(X + 16 + Delta,Y + 1,14,14);
    }
  }
 SetWriteMode(COPY_PUT);
}

void GScroll :: PlaceEndMove(void)
{
 int Delta;

 if(ScrollType & VERTICAL)
  {
   if(MaxPos)
    {
     Delta = ((float)(DY - 32 - 14) / MaxPos) * Position;
     Bar(X + 1,Y + 16 + Delta,14,14,GRAY_12);
     Position = TmpPosition;
     ButtonDraw(X + 1,Y + 16 + ButtonPlace(),14,14,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
    }
  }
 else
  {
   if(MaxPos)
    {
     Delta = ((float)(DX - 32 - 14) / MaxPos) * Position;
     Bar(X + 16 + Delta,Y + 1,14,14,GRAY_12);
     Position = TmpPosition;
     ButtonDraw(X + 16 + ButtonPlace(),Y + 1,14,14,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
    }
  }
}

int GScroll :: Mouse(MSG &msg)
{
 if(!MaxPos)
  return 0;

 if(msg.Mouse & LBUTTON && isMyFrame(msg.X,msg.Y))
  {
   if(isFirst(msg.X,msg.Y))
    {
     if(ScrollType & VERTICAL)
      ButtonDraw(X,Y,16,16,"",0xffff,BUTTON_DOWN,JUSTIFY_CENTER,1);
     else
      ButtonDraw(X,Y,16,16,"",0xffff,BUTTON_DOWN,JUSTIFY_CENTER,1);
     Sound();
     ScrollStatus = SCROLL_BUTTON_FIRST;
     return SCROLL_BUTTON;
    }
   if(isSecond(msg.X,msg.Y))
    {
     if(ScrollType & VERTICAL)
      ButtonDraw(X,Y + DY - 16,16,16,"",0xffff,BUTTON_DOWN,JUSTIFY_CENTER,1);
     else
      ButtonDraw(X + DX - 16,Y,16,16,"",0xffff,BUTTON_DOWN,JUSTIFY_CENTER,1);
     Sound();
     ScrollStatus = SCROLL_BUTTON_SECOND;
     return SCROLL_BUTTON;
    }
   if(isPlace(msg.X,msg.Y))
    {
     if(ScrollType & VERTICAL)
      ButtonDraw(X + 1,Y + 16 + ButtonPlace(),14,14,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
     else
      ButtonDraw(X + 16 + ButtonPlace(),Y + 1,14,14,"",0xffff,BUTTON_UP,JUSTIFY_CENTER,0);
     ScrollStatus = SCROLL_BUTTON_MOVE;
     PlaceBeginMove();
     return SCROLL_MOVE;
    }
   return 1;
  }


 if(msg.Mouse & LBUTTON_UP)
  switch(ScrollStatus)
   {
    case SCROLL_BUTTON_MOVE:
         PlaceEndMove();
         ScrollStatus = 0;
         return SCROLL_BUTTON;
    case SCROLL_BUTTON_FIRST:
         ButtonEvent(-1);
         ScrollStatus = 0;
         return SCROLL_BUTTON;
    case SCROLL_BUTTON_SECOND:
         ButtonEvent(1);
         ScrollStatus = 0;
         return SCROLL_BUTTON;
   }

 if(msg.Mouse & MOVE)
  switch(ScrollStatus)
   {
    case SCROLL_BUTTON_MOVE:
         PlaceMoveTo(msg.X,msg.Y);
         return SCROLL_MOVE;
   }

 return 0;
}





