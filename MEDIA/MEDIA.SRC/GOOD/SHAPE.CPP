#include <dos.h>
#include <string.h>
#include "graph.hpp"
#include "shape.hpp"
#include "gbutton.hpp"
#include "gmenu.hpp"

void Sound(void)
{
 sound(100);
 delay(10);
 nosound();
}

void RectangleDraw(int x,int y,int dx,int dy)
{
 Bar(x+5,y+5,dx-10,dy-10,GRAY_8);

 HLine(x,y,dx-1,GRAY_14);
 HLine(x,y + dy-1,dx,GRAY_4);
 VLine(x,y+1,dy-2,GRAY_14);
 VLine(x + dx-1,y,dy-1,GRAY_4);

 Rectangle(x+1,y+1,dx-2,dy-2,GRAY_10);
 Rectangle(x+2,y+2,dx-4,dy-4,GRAY_10);
 Rectangle(x+3,y+3,dx-6,dy-6,GRAY_10);

 HLine(x+4,     y+4,     dx-1-8,GRAY_4);
 HLine(x+4,     y+dy-1-4,dx  -8,GRAY_14);
 VLine(x+4,     y+1+4,   dy-2-8,GRAY_4);
 VLine(x+dx-1-4,y+4,     dy-1-8,GRAY_14);

}

void WindowNameDraw(int x,int y,int dx,char *name,int color,int type)
{
 char str;
 int tmp;

 str = 0;
 x+=5;
 dx-=10;
 if(type & WND_CLOSE_BUTTON)
 {
  x+=20;
  dx-=20;
 }
 if(type & WND_MIN_BUTTON)
  dx-=39;
 else
  if(type & WND_MAX_BUTTON)
   dx-=21;


 Bar(x,y + 5,dx,18,color);

 tmp=strlen(name) * SmallFontTable[1];

 if(tmp > dx)
  {
   tmp = (dx - (dx / SmallFontTable[1]) * SmallFontTable[1]) / 2;
   if(SmallFontTable[1])
    dx = dx / SmallFontTable[1];
   else
    dx = 0;
   str = name[dx];
   name[dx] = 0;
  }
 else
  {
   tmp = (dx - tmp) / 2;
   dx = strlen(name);
  }

 SetColor(GRAY_4);
 OutStr(x + tmp,y + 6,name);
 SetColor(GRAY_15);
 OutStr(x + tmp - 1,y + 5,name);
 name[dx] = str;
}

void WindowDraw(int x,int y,int dx,int dy,char *name,int active,int type)
{
// RectangleDraw(x,y,dx,dy);
// rectangle draw
 HLine(x,y,dx-1,GRAY_14);
 HLine(x,y + dy-1,dx,GRAY_4);
 VLine(x,y+1,dy-2,GRAY_14);
 VLine(x + dx-1,y,dy-1,GRAY_4);

 Rectangle(x+1,y+1,dx-2,dy-2,GRAY_10);
 Rectangle(x+2,y+2,dx-4,dy-4,GRAY_10);
 Rectangle(x+3,y+3,dx-6,dy-6,GRAY_10);

 HLine(x+4,     y+4,     dx-1-8,GRAY_4);
 HLine(x+4,     y+dy-1-4,dx  -8,GRAY_14);
 VLine(x+4,     y+1+4,   dy-2-8,GRAY_4);
 VLine(x+dx-1-4,y+4,     dy-1-8,GRAY_14);



// uztvaros butonams
 if(type & WND_CLOSE_BUTTON)
 {
  VLine(x + 5 + 18    ,y + 4,20,GRAY_14);
  VLine(x + 5 + 18 + 1,y + 4,20,GRAY_10);
  VLine(x + 5 + 18 + 2,y + 4,20,GRAY_4);
 }
 if(type & WND_MIN_BUTTON)
 {
  VLine(x + dx - 6 - 18*2 - 2,y + 4,20,GRAY_14);
  VLine(x + dx - 6 - 18*2 - 1,y + 4,20,GRAY_10);
  VLine(x + dx - 6 - 18*2    ,y + 4,20,GRAY_4);
 }
 else
  if(type & WND_MAX_BUTTON)
  {
   VLine(x + dx - 6 - 18 - 2,y + 4,20,GRAY_14);
   VLine(x + dx - 6 - 18 - 1,y + 4,20,GRAY_10);
   VLine(x + dx - 6 - 18    ,y + 4,20,GRAY_4);
  }

// textui
 HLine(x + 4,y + 5 + 18 + 0,dx - 8,GRAY_14);
 HLine(x + 4,y + 5 + 18 + 1,dx - 8,GRAY_10);
 HLine(x + 4,y + 5 + 18 + 2,dx - 8,GRAY_4);
 HLine(x + 4,y + 5 + 18 + 3,dx - 8,GRAY_14);
 HLine(x + 4,y + 5 + 18 + 4,dx - 8,GRAY_10);
 HLine(x + 4,y + 5 + 18 + 5,dx - 8,GRAY_4);

 if(active)
  WindowNameDraw(x,y,dx,name,_LIGHTBLUE,type);
 else
  WindowNameDraw(x,y,dx,name,GRAY_8,type);
}

void ButtonDraw(int x,int y,int dx,int dy,char far *str,int activeplace,int status,int justify,int ispressed)
{
 int CActiveKey,CText,CLeftTop,CRightDown,Down=0;

 if(ispressed)
  {
   CActiveKey = _LIGHTGREEN;
   CText      = GRAY_0;
   CLeftTop   = GRAY_4;
   CRightDown = GRAY_14;
   Down = 1;
  }
 else
  {
   CActiveKey = _RED;
   CText      = GRAY_0;
   CLeftTop   = GRAY_14;
   CRightDown = GRAY_4;
  }

 switch(status)
 {
  case BUTTON_ACTIVE:
       CActiveKey = _RED;
       CText      = _LIGHTGREEN;
       break;
  case BUTTON_UNAVAILABLE:
       CActiveKey = GRAY_9;
       CText      = GRAY_9;
       break;
 }


 Bar(x + 1,y + 1,dx - 2,dy - 2,GRAY_10);

 HLine(x     ,y,     dx-1,CLeftTop);
 VLine(x     ,y+1,   dy-2,CLeftTop);
 HLine(x     ,y+dy-1,dx,  CRightDown);
 VLine(x+dx-1,y,     dy-1,CRightDown);

 x ++;
 dx -= 2;
 if(strlen(str) * SmallFontTable[1] > dx)
  str[dx / SmallFontTable[1]] = 0;

 SetColor(CText);
 switch(justify)
  {
   case JUSTIFY_LEFT:
        OutStr(x + Down,y + (dy - SmallFontTable[0]) / 2 + Down,str);
        if(activeplace < strlen(str))
         OutFont(x + activeplace * SmallFontTable[1] + Down,
                 y + (dy - SmallFontTable[0]) / 2 + Down,
                 str[activeplace],SmallFontTable,CActiveKey);
        break;
   case JUSTIFY_RIGHT:
   case JUSTIFY_CENTER:
        OutStr(x + (dx - strlen(str) * SmallFontTable[1]) / 2 + Down,
               y + (dy - SmallFontTable[0]) / 2 + Down,str);
        if(activeplace < strlen(str))
         OutFont(x + (dx - strlen(str) * SmallFontTable[1]) / 2 + activeplace * SmallFontTable[1] + Down,
                 y + (dy - SmallFontTable[0]) / 2 + Down,
                 str[activeplace],SmallFontTable,CActiveKey);
        break;
  }
}

void RadioButtonDraw(int x,int y,int dx,int dy,char far *str,int activeplace,int status,int justify)
{
 int CActiveKey = _RED,CText = _BLACK,CBar = _WHITE;

 switch(status)
 {
  case BUTTON_UNAVAILABLE:
       CActiveKey = GRAY_10;
       CText      = GRAY_10;
       CBar       = _WHITE;
       break;
  case BUTTON_UP:
  case BUTTON_ACTIVE:
       CActiveKey = _RED;
       CText      = _BLACK;
       CBar       = _LIGHTBLUE;
       break;
  case BUTTON_PASIVE:
       CActiveKey = _RED;
       CText      = _BLACK;
       CBar       = _WHITE;
       break;
 }

 Bar(x,y,dx,dy,CBar);

 x ++;
 dx -= 2;
 if(strlen(str) * SmallFontTable[1] > dx)
  str[dx / SmallFontTable[1]] = 0;

 SetColor(CText);
 switch(justify)
  {
   case JUSTIFY_LEFT:
        OutStr(x,y + (dy - SmallFontTable[0]) / 2,str);
        if(activeplace < strlen(str))
         OutFont(x + activeplace * SmallFontTable[1],
                 y + (dy - SmallFontTable[0]) / 2,
                 str[activeplace],SmallFontTable,CActiveKey);
        break;
   case JUSTIFY_RIGHT:
   case JUSTIFY_CENTER:
        OutStr(x + (dx - strlen(str) * SmallFontTable[1]) / 2,
               y + (dy - SmallFontTable[0]) / 2,str);
        if(activeplace < strlen(str))
         OutFont(x + (dx - strlen(str) * SmallFontTable[1]) / 2 + activeplace * SmallFontTable[1],
                 y + (dy - SmallFontTable[0]) / 2,
                 str[activeplace],SmallFontTable,CActiveKey);
        break;
  }
}

void Varna(int x,int y,int dx,int dy)
{
 Bar(x + 1,y + 1,dx - 2,dy - 2,_LIGHTBLUE);
 Line(x,y,x + dx / 2,y + dy,_BLACK);
 Line(x + dx / 2,y + dy,x + dx,y,_BLACK);
}

void CheckButtonDraw(int x,int y,int dx,int dy,char far *str,int activeplace,int status,int varna)
{
 int CActiveKey = _RED,CText = _BLACK,CBar = _WHITE;

 switch(status)
 {
  case BUTTON_UNAVAILABLE:
       CActiveKey = GRAY_5;
       CText      = GRAY_5;
       CBar       = _WHITE;
       break;
  case BUTTON_UP:
  case BUTTON_ACTIVE:
       CActiveKey = _RED;
       CText      = _BLACK;
       CBar       = _LIGHTBLUE;
       break;
  case BUTTON_PASIVE:
       CActiveKey = _RED;
       CText      = _BLACK;
       CBar       = _WHITE;
       break;
  case BUTTON_DOWN:
       CActiveKey = _RED;
       CText      = GRAY_0;
       break;
 }

 Bar(x,y,dx,dy,CBar);
 Rectangle(x + 1,y + (dy - SmallFontTable[0]) / 2,SmallFontTable[1],SmallFontTable[0],_BLACK);
 if(varna == PRESSED)
  Varna(x + 1,y + (dy - SmallFontTable[0]) / 2,SmallFontTable[1],SmallFontTable[0]);

 x += SmallFontTable[1] + 1;
 dx -= SmallFontTable[0] + 2;

 if(strlen(str) * SmallFontTable[1] > dx)
  str[dx / SmallFontTable[1]] = 0;

 SetColor(CText);
 OutStr(x + (dx - strlen(str) * SmallFontTable[1]) / 2,
        y + (dy - SmallFontTable[0]) / 2,str);
 if(activeplace < strlen(str))
  OutFont(x + (dx - strlen(str) * SmallFontTable[1]) / 2 + activeplace * SmallFontTable[1],
          y + (dy - SmallFontTable[0]) / 2,
          str[activeplace],SmallFontTable,CActiveKey);
}

void MenuDraw(int x,int y,int dx,int dy,int menutype)
{
 switch(menutype)
  {
   case MENU_FILL:
        Bar(x + 1,y + 1,dx - 2,dy - 2,_WHITE);
        Rectangle(x,y,dx,dy,_BLACK);
        break;
   case MENU_FRAME:
        Rectangle(x + 1,y + 1,dx - 2,dy - 2,_WHITE);
        Rectangle(x,y,dx,dy,_BLACK);
        break;
  }
}

void InputDraw(int x,int y,int dx,int dy,char *string,int active,int currentplace)
{
 int color;
 int groundcolor;

 if(active == WND_PASIVE)
  {
   color = _WHITE;
   groundcolor = _BLACK;
  }
 else
  {
   color = _BLACK;
   groundcolor = _WHITE;
  }

 SetColor(color);
 SetGroundColor(groundcolor);
 Rectangle(x,y,dx,dy,color);
 Bar(x + 1,y + 1,dx - 2,dy - 2,groundcolor);
 OutText(x + 2,y + 2,string);
 if(active == WND_ACTIVE)
  {
   SetWriteMode(XOR_PUT);
   HLine(x + 2 + currentplace * 8,y + 2 + 13,8,_BLACK);
   HLine(x + 2 + currentplace * 8,y + 2 + 14,8,_BLACK);
   SetWriteMode(COPY_PUT);
  }
}

void MoveGInputCursor(int x,int y,int oldplace,int newplace)
{
 SetWriteMode(XOR_PUT);
 HLine(x + 2 + oldplace * 8,y + 2 + 13,8,_BLACK);
 HLine(x + 2 + oldplace * 8,y + 2 + 14,8,_BLACK);

 HLine(x + 2 + newplace * 8,y + 2 + 13,8,_BLACK);
 HLine(x + 2 + newplace * 8,y + 2 + 14,8,_BLACK);
 SetWriteMode(COPY_PUT);
}