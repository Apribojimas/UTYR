#include <stdio.h>
#include <string.h>
#include "images.hpp"
#include "shape.hpp"
#include "proto.hpp"
#include "keys.h"
#include "gswindow.hpp"
#include "graph.hpp"
#include "help.hpp"
#include "mm.hpp"

int PrintScreenNumber = 0;


#ifndef _GSMALLWINDOW
#define _GSMALLWINDOW

#include "gframe.hpp"
#include "gbutton.hpp"

class GSmallWindow : public GFrame
{
 int LocalX;   // reikalinga move operacijai atlikti
 int LocalY;
 int LocalTmpX;
 int LocalTmpY;
 int NormalDX;    // normalaus ekrano dysi
 int NormalDY;
 int ReSizeX;     // isimenam keitimo metu XY dydi
 int ReSizeY;

 GButton *CloseButton;
 GButton *MinButton;
 GButton *MaxButton;
protected:
 int MaxDX;     // isimenam didelio ekrano dydi
 int MaxDY;

public:
 ~GSmallWindow();
  GSmallWindow(int x = 0,int y = 0,int dx = 0,int dy = 0,char *name = "",int windowtype = WND_GRAPH,int maxdx = 580,int maxdy = 440);

  virtual void Show();
  virtual void SetVideoMode(int mode);
  virtual int  EventHandler(MSG &msg);
  virtual void SetWndMaxDXDY(int dx,int dy);
  virtual void SetDXDY(int dx,int dy);
  void SetWndName(char *wndname);

// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);        // apdorosime komandas
  virtual int Mouse(MSG &msg);          // mouse eventai
  virtual int Keyboard(MSG &msg);       // klaviaturos

private:
  int isTitle(int x,int y);     // tikrinam ar titlas
  int isCheckBox(int x,int y);  // patikrina ar Check Box
  void MoveTo(int x,int y);     // pernesime lango 'seseli'
  void WindowMinMax(void);      // procedura su kuria atliekam keitima is normal i big ir atvirksciai
  void WindowBeginMove(int x,int y);   // sios proceduros reikalingos pradeti lango perstumima ir pabaigti
  void WindowEndMove(void);
  void PrivateSetVideoMode(void);
};
#endif

GSmallWindow :: GSmallWindow(int x,int y,int dx,int dy,char *name,int windowtype,int maxdx,int maxdy)
             :  GFrame(x,y)
{
 WndName = 0L;
 SetWndName(name);
 SetDXDY(dx,dy);

 WndEvent = 0;
 ReSizeX = X;
 ReSizeY = Y;
 NormalDX = DX;
 NormalDY = DY;
 WndType = windowtype;

 if(maxdx < dx)
  maxdx = dx;
 if(maxdy < dy)
  maxdy = dy;
 SetWndMaxDXDY(maxdx,maxdy);
// PrivateSetVideoMode();

 CloseButton = 0L;
 MinButton = 0L;
 MaxButton = 0L;
 if(WndType & WND_CLOSE_BUTTON)
  CloseButton = new GButton(x + 5,y + 5,18,18,"þ",ITEM_CLOSE,0,ALT_F3);
 if((WndType & WND_MIN_BUTTON) && (WndType & WND_MAX_BUTTON))
  MinButton = new GButton(x + dx - 41,y + 5,18,18,"",ITEM_MIN,0,ALT_F5);
 if(WndType & WND_MAX_BUTTON)
  MaxButton = new GButton(x + dx - 23,y + 5,18,18,"",ITEM_MAX,0,F5);
}

GSmallWindow :: ~GSmallWindow()
{
 if(WndName != 0L)
  delete WndName;
 if(CloseButton != 0L)
  delete CloseButton;
 if(MinButton != 0L)
  delete MinButton;
 if(MaxButton != 0L)
  delete MaxButton;
}

void GSmallWindow :: Show()
{
 if(WndStatus == WND_ICON)
  return;

 PrivateSetVideoMode();
 WindowDraw(X,Y,DX,DY,WndName,WndActive,WndType);
 if(CloseButton != 0L)
  {
   CloseButton->SetXY(X + 5,Y + 5);
   CloseButton->Show();
  }
 if(MinButton != 0L)
  {
   MinButton->SetXY(X + DX - 41,Y + 5);
   MinButton->Show();
  }
 if(MaxButton != 0L)
  {
   MaxButton->SetXY(X + DX - 23,Y + 5);
   MaxButton->Show();
  }
}

void GSmallWindow :: SetWndMaxDXDY(int dx,int dy)
{
 MaxDX = dx + 10;
 MaxDY = dy + 34;
 if(WndStatus)
  WndStatus = WND_NORMAL;
}

ClassType GSmallWindow :: isA()
{
 return _GSmallWindow;
}

void GSmallWindow :: SetDXDY(int dx,int dy)
{
 DX = dx + 10;
 DY = dy + 34;
}

void GSmallWindow :: SetWndName(char *wndname)
{
 if(WndName != 0L)
  delete WndName;
 WndName = new char [strlen(wndname) + 1];
 if(WndName != 0L)
  strcpy(WndName,wndname);
}

int GSmallWindow :: isTitle(int x,int y)
{
 if(y < Y || y > Y + 22)   // patikrinam ar papuolam i y koord. intervala
  return 0;

 if(!(WndType & WND_CLOSE_BUTTON))  // patikrinam ar CloseButtono vietoje
  if(x > X + 4 && x < X + 26)
   return 1;

 if(!(WndType & WND_MIN_BUTTON))  // patikrinam ar MinButtono vietoje
  if(x > X + DX - 44 && x < X + DX - 26)
   return 1;

 if(!(WndType & WND_MAX_BUTTON))  // patikrinam ar MaxButtono vietoje
  if(x > X + DX - 26 && x < X + DX - 4)
   return 1;

 if(x > X + 26 && x < X + DX - 45)   // patikrinam ar pavadinimo vietoje
  return 1;

return 0;
}

void GSmallWindow :: MoveTo(int x,int y)
{
 if(x + DX <= 0)     // patikrinam ar langa gali buti uznestas uz displejaus ribu
  return;
 if(x > GraphMaxX)
  return;
 if(y + DY <= 0)
  return;
 if(y > GraphMaxY)
  return;

 SetColor(GRAY_2);
 SetWriteMode(XOR_PUT);
 Rectangle(LocalX,LocalY,DX,DY);
 Rectangle(x,y,DX,DY);
 LocalX = x;
 LocalY = y;
 SetWriteMode(COPY_PUT);
}

void GSmallWindow :: WindowMinMax(void)
{
 switch(WndStatus)
  {
   case WND_NORMAL:
        if(DX == MaxDX && DY == MaxDY)
         return;
        WndStatus = WND_BIG;
        NormalDX = DX;
        NormalDY = DY;
        ReSizeX = X;
        ReSizeY = Y;
        DX = MaxDX;
        DY = MaxDY;

        if(X + DX > GraphMaxX + 1)
         X = GraphMaxX + 1 - DX;
        if(X < 0)
         X = 0;
        if(Y + DY > GraphMaxY + 1)
         Y = GraphMaxY + 1 - DY;
        if(Y < 0)
         Y = 0;
	Show();
        break;
   case WND_BIG:
        WndStatus = WND_NORMAL;
        SetViewPort(X,Y,DX,DY);
        DX = NormalDX;
        DY = NormalDY;
        X = ReSizeX;
        Y = ReSizeY;
        if(X + DX < 0)
	 X = 50 - DX;
	if(Y + DY < 0)
	 Y = 50 - DY;
	ReDraw();
	break;
  }
}

void GSmallWindow :: WindowBeginMove(int x,int y)
{
 SetColor(GRAY_2);
 SetWriteMode(XOR_PUT);
 Rectangle(X,Y,DX,DY);
 LocalX = X;
 LocalY = Y;
 LocalTmpX = X - x;
 LocalTmpY = Y - y;
 SetWriteMode(COPY_PUT);
}

void GSmallWindow :: WindowEndMove(void)
{
 WndEvent = 0;
 if(X != LocalX || Y != LocalY)
  {
   SetViewPort(X,Y,DX,DY);
   X = LocalX;
   Y = LocalY;
   ReDraw();
  }
 else
  {
   SetColor(GRAY_2);
   SetWriteMode(XOR_PUT);
   Rectangle(LocalX,LocalY,DX,DY);
   SetWriteMode(COPY_PUT);
  }
}

void GSmallWindow :: SetVideoMode(int mode)
{
 if(!(mode == MODE_TEXT ||
      mode == MODE_640 ||
      mode == MODE_800 ||
      mode == MODE_1024) ||
      mode == MemMode)
  return;

 if(X >= 0)
  X = ChangeVariable(X);
 if(Y >= 0)
  Y = ChangeVariable(Y);

 if(WndType & WND_TEXT)
  {
   DX = ChangeVariable(DX - 10) + 10;
   DY = ChangeVariable(DY - 36) + 36;

   if(X + DX <= 50)
    X += 50 - (X + DX);
  }

 MemMode = mode;
}

int GSmallWindow :: EventHandler(MSG &msg)
{

 switch (msg.Type)
  {
   case KEYBOARD:
        if(WndStatus != WND_ICON)
         return (Keyboard(msg));
        break;
   case MOUSE:
        if(WndStatus != WND_ICON)
         return (Mouse(msg));
        break;
   case COMMAND:
        return (Command(msg));
  }
return 0;
}

int GSmallWindow :: Command(MSG &msg)
{
 if(WndStatus == WND_ICON && msg.Cmd != ITEM_NORMAL)
  return 0;

 switch(msg.Cmd)
  {
   case ITEM_REGISTER:
        return 1;
   case ITEM_ACTIVE:
        WndActive = WND_ACTIVE;
        PrivateSetVideoMode();
        WindowNameDraw(X,Y,DX,WndName,_LIGHTBLUE,WndType);
        return 1;
   case ITEM_PASIVE:
        WndActive = WND_PASIVE;
        WindowNameDraw(X,Y,DX,WndName,GRAY_8,WndType);
        break;
   case ITEM_NORMAL:
        WndActive = WND_ACTIVE;
        WndStatus = WND_NORMAL;
	Show();
	return 1;
   case ITEM_SHOW:
        Show();
        break;
   case ITEM_CLOSE:
	SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        return 1;
   case ITEM_MAX:
        WindowMinMax();
        return 1;
   case ITEM_MIN:
        WndStatus = WND_ICON;
        SendMSGCmd(ITEM_ICON,0,RegisterNumber,(long)WndName);
        SetViewPort(X,Y,DX,DY);
        ReDraw();
        return 1;
   case MENU_ACTIVE:
        return 1;
   case ITEM_STATUS:
	return WndStatus;
  }
return 0;
}

int GSmallWindow :: Mouse(MSG &msg)
{
 if(msg.Mouse & LBUTTON)
  switch(WndEvent)
   {
    case WND_MOUSE_MOVE:
    case WND_MOVE:
         return 1;
    default:
         if(isMyFrame(msg.X,msg.Y))
          {
           if(WndActive == WND_PASIVE)
            return 1;
           if(isTitle(msg.X,msg.Y))
            {
             WndEvent = WND_MOUSE_MOVE;
             WindowBeginMove(msg.X,msg.Y);
             return 1;
            }
           if(CloseButton != 0L)
            if(CloseButton->EventHandler(msg))
             {
              WndEvent = WND_BUTTON;
              return 1;
             }
           if(MinButton != 0L)
            if(MinButton->EventHandler(msg))
             {
              WndEvent = WND_BUTTON;
              return 1;
             }
           if(MaxButton != 0L)
            if(MaxButton->EventHandler(msg))
             {
              WndEvent = WND_BUTTON;
              return 1;
             }
           return 1;
          }
   }

 if(msg.Mouse & RBUTTON)
  {
   switch(WndEvent)
    {
     case WND_MOUSE_MOVE:
     case WND_MOVE:
          WndEvent = 0;
          SetWriteMode(XOR_PUT);
          Rectangle(LocalX,LocalY,DX,DY);
          SetWriteMode(COPY_PUT);
          return 1;
     case 0:
          if(isTitle(msg.X,msg.Y))
           {
            SendMSGCmd(MENU_ACTIVE,RegisterNumber);
            return 1;
           }
          break;
    }
  }

 if(msg.Mouse & LBUTTON_UP)
  switch(WndEvent)
   {
    case WND_MOUSE_MOVE:
    case WND_MOVE:
         WndEvent = 0;
         WindowEndMove();
         return 1;
    case WND_BUTTON:
         WndEvent = 0;
         if(CloseButton != 0L)
          if(CloseButton->EventHandler(msg))
           return 1;
         if(MinButton != 0L)
          if(MinButton->EventHandler(msg))
           return 1;
         if(MaxButton != 0L)
          if(MaxButton->EventHandler(msg))
           return 1;
         break;
   }

 if(msg.Mouse & MOVE)
  switch(WndEvent)
   {
    case WND_MOVE:                  // pakeiciam busena nes dabar bus mouse_move
	 WndEvent = WND_MOUSE_MOVE;
    case WND_MOUSE_MOVE:
         MoveTo(msg.X + LocalTmpX,msg.Y + LocalTmpY);
         return 1;
   }

return 0;
}

int GSmallWindow :: Keyboard(MSG &msg)
{
 long MHandler;
 char str[20];
 char pal[768];

 if(WndEvent == WND_MOVE)
  switch(msg.Key)
   {
    case ESC:
         WndEvent = 0;
         SetWriteMode(XOR_PUT);
         Rectangle(LocalX,LocalY,DX,DY);
         SetWriteMode(COPY_PUT);
         return 1;
    case CR:
         WindowEndMove();
         return 1;
    case UP:
         MoveTo(LocalX,LocalY - 1);
         return 1;
    case DOWN:
         MoveTo(LocalX,LocalY + 1);
         return 1;
    case LEFT:
         MoveTo(LocalX - 1,LocalY);
         return 1;
    case RIGHT:
         MoveTo(LocalX + 1,LocalY);
         return 1;
    case SHIFT_UP:
         MoveTo(LocalX,LocalY - 10);
         return 1;
    case SHIFT_DOWN:
         MoveTo(LocalX,LocalY + 10);
         return 1;
    case SHIFT_LEFT:
         MoveTo(LocalX - 10,LocalY);
         return 1;
    case SHIFT_RIGHT:
         MoveTo(LocalX + 10,LocalY);
         return 1;
   }
 switch(msg.Key)
  {
   case F1:
        RunHelp(1);
        return 1;
   case CR:
        break;
   case SPACE:
        if(msg.KeyStatus & ALT)
         SendMSGCmd(MENU_ACTIVE,RegisterNumber);
        return 1;
   case CTRL_F5:
        WndEvent = WND_MOVE;
        WindowBeginMove(X + DX / 2,Y + 3);
        return 1;
   case F12:
        MHandler = MAlloc((long)DX * DY);
        MGetFrame(MHandler,DX,DY,X,Y);
        sprintf(str,"%0i.bmp",PrintScreenNumber);
        GetAllPalette(pal,0,256);
        WriteImage(str,MHandler,DX,DY,pal);
        MFree(MHandler);
        PrintScreenNumber ++;
        return 1;
   case ALT_F12:
        MHandler = MAlloc((long)ViewDX * ViewDY);
        MGetFrame(MHandler,ViewDX,ViewDY,ViewX,ViewY);
        sprintf(str,"%0i.bmp",PrintScreenNumber);
        GetAllPalette(pal,0,256);
        WriteImage(str,MHandler,ViewDX,ViewDY,pal);
        MFree(MHandler);
        PrintScreenNumber ++;
        return 1;
   default:
        if(CloseButton != 0L)
         if(CloseButton->EventHandler(msg))
          return 1;
        else
         if(msg.Key == ALT_F3)
          {
           SendMSGCmd(ITEM_CLOSE,RegisterNumber);
           return 1;
          }
        if(MinButton != 0L)
         if(MinButton->EventHandler(msg))
          return 1;
        if(MaxButton != 0L)
         if(MaxButton->EventHandler(msg))
          return 1;
  }
 if(WndEvent == WND_MOUSE_MOVE)
  return 1;

return 1;
}

void GSmallWindow :: PrivateSetVideoMode(void)
{
 if(WndType & WND_TEXT)
  {
   MaxDX = ChangeVariable(MaxDX);
   MaxDY = ChangeVariable(MaxDY);
   NormalDX = ChangeVariable(NormalDX);
   NormalDY = ChangeVariable(NormalDY);
  }
 ReSizeX = ChangeVariable(ReSizeX);
 ReSizeY = ChangeVariable(ReSizeY);
 SetVideoMode(CurrentMode);
}
