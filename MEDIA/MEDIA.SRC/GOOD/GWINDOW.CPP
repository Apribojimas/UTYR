#include "proto.hpp"
#include "gettext.hpp"
#include "keys.h"
#include "gwindow.hpp"
#include "graph.hpp"

#ifndef _GWINDOW
#define _GWINDOW

#include "gswindow.hpp"
#include "gmenu.hpp"
#include "gscroll.hpp"

class GWindow : public GSmallWindow
{
 int WndScroll;  // kokie Scroll bar yra inizializuoti
 GMenu MyMenu;   // Meniu
 GScroll HScroll;  // Scroll bar
 GScroll VScroll;
protected:
 int WndMenu;    // ar yra iskviestas menu
public:
 ~GWindow();
  GWindow(int x = 0,int y = 0,int dx = 0,int dy = 0,char *name = "",int windowtype = WND_GRAPH,int hscale = 0,int vscale = 0,int maxdx = 640,int maxdy = 480);

  void NewMenu(void);
  void AddMenuItem(Object *Obj);
  void WndDraw(void);
  void SetPos(int i,int who);
  int  GetPos(int who);
  void SetMaxPos(int i,int who);
  void ScrollerShow(void);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual void Show(void);
  virtual int EventHandler(MSG &msg);
  virtual void SetWndMaxDXDY(int dx,int dy);
  virtual void SetDXDY(int dx,int dy);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);         // apdorosime komandas
  virtual int Keyboard(MSG &msg);       // klaviaturos
private:
  void SetView(void);            // nustatom View kintamuosius
};
#endif

GWindow :: GWindow(int x,int y,int dx,int dy,char *name,int windowtype,int hscale,int vscale,int maxdx,int maxdy)
	:  GSmallWindow(x,y,dx,dy,name,windowtype,maxdx,maxdy),
	   MyMenu(0,0,MENU_FRAME,MENU_PASIVE),
           HScroll(0,0,0,HORIZANTAL,hscale),
           VScroll(0,0,0,VERTICAL,vscale)
{
 WndMenu = 0;
 WndScroll = 0;
 if(vscale)
  WndScroll |= WND_VSCROLL;
 if(hscale)
  WndScroll |= WND_HSCROLL;
 SetDXDY(dx,dy);
 SetView();
}

GWindow :: ~GWindow()
{
}

ClassType GWindow :: isA()
{
 return _GWindow;
}

void GWindow :: Show(void)
{
 if(WndStatus == WND_ICON)
  return;

 GSmallWindow :: Show();
 SetView();
 if((WndScroll & WND_HSCROLL) && (WndScroll & WND_VSCROLL))
  Bar(ViewX + ViewDX,ViewY + ViewDY,16,16,GRAY_8);

 WndDraw();
 ScrollerShow();
 if(WndMenu == DTW_MENU)
  {
   MyMenu.SetXY(ViewX,ViewY);
   MyMenu.Show();
  }
}

void GWindow :: WndDraw(void)
{
 int tmpX;
 int tmpY;
 int tmpDX;
 int tmpDY;

 GetViewPort(tmpX,tmpY,tmpDX,tmpDY);
 if(GraphBoundary(ViewX,ViewY,ViewDX,ViewDY))
  return;
 SetViewPort(BoundaryX,BoundaryY,BoundaryDX,BoundaryDY);
 Draw(ViewX,ViewY,ViewDX,ViewDY,HScroll.GetPos(),VScroll.GetPos());
 SetViewPort(tmpX,tmpY,tmpDX,tmpDY);
}
#pragma argsused
void GWindow :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
}

void GWindow :: SetWndMaxDXDY(int dx,int dy)
{
 GSmallWindow :: SetWndMaxDXDY(dx,dy);
 if(WndScroll & WND_VSCROLL)
  MaxDX += 16;
 if(WndScroll & WND_HSCROLL)
  MaxDY += 16;
}

void GWindow :: SetDXDY(int dx,int dy)
{
 GSmallWindow :: SetDXDY(dx,dy);
 if(WndScroll & WND_VSCROLL)
  DX += 16;
 if(WndScroll & WND_HSCROLL)
  DY += 16;
}

void GWindow :: NewMenu(void)
{
 MyMenu.NewMenu();
}

void GWindow :: AddMenuItem(Object *Obj)
{
 MyMenu + Obj;
}

int GWindow :: EventHandler(MSG &msg)
{
 int i = 0;
 int j;

 if(WndMenu == DTW_MENU && msg.Type != COMMAND)
  {
   i = MyMenu.EventHandler(msg);
   if(msg.Type == KEYBOARD)
    return 1;
   return i;
  }

 if(GSmallWindow :: EventHandler(msg))
  i ++;
 if(WndActive == WND_ACTIVE && WndStatus != WND_ICON)
  {
   if((j = HScroll.EventHandler(msg)) != 0)
    {
     i ++;
     if (j == SCROLL_BUTTON)
      WndDraw();
    }
   if((j = VScroll.EventHandler(msg)) != 0)
    {
     i ++;
     if (j == SCROLL_BUTTON)
      WndDraw();
    }
  }
 return i;
}

int GWindow :: Command(MSG &msg)
{
 int i;
 i = GSmallWindow :: Command(msg);
 switch(msg.Cmd)
  {
   case MENU_ACTIVE:
	if(MyMenu.GetMenuSize())
	 {
	  WndMenu = DTW_MENU;
	  MyMenu.SetXY(ViewX,ViewY);
	  MyMenu.Show();
	 }
	return 1;
   case MENU_PASIVE:
	WndMenu = 0;
        SetViewPort(MyMenu.GetX(),MyMenu.GetY(),MyMenu.GetDX(),MyMenu.GetDY());
        WndDraw();
        SetViewPort(0,0,GraphMaxX + 1,GraphMaxY + 1);
	return 1;
   case ITEM_PASIVE:
        if(WndMenu)
         {
	  WndMenu = 0;
          SetViewPort(MyMenu.GetX(),MyMenu.GetY(),MyMenu.GetDX(),MyMenu.GetDY());
          WndDraw();
          SetViewPort(0,0,GraphMaxX + 1,GraphMaxY + 1);
         }
        break;
  }
return i;
}

void GWindow :: SetPos(int i,int who)
{
 if(who & VERTICAL)
  {
   VScroll.SetPos(i);
//   VScroll.Show();
  }
 else
  {
   HScroll.SetPos(i);
//   HScroll.Show();
  }
}

int  GWindow :: GetPos(int who)
{
 if(who & VERTICAL)
  return VScroll.GetPos();
 else
  return HScroll.GetPos();
}

void GWindow :: SetMaxPos(int i,int who)
{
 if(who & VERTICAL)
  VScroll.SetMaxPos(i);
 else
  HScroll.SetMaxPos(i);
}

void GWindow :: SetView(void)
{
 ViewX = X + 5;
 ViewY = Y + 29;
 ViewDX = DX - 10;
 ViewDY = DY - 34;

 if(WndScroll & WND_VSCROLL)
  ViewDX -= 16;

 if(WndScroll & WND_HSCROLL)
  ViewDY -= 16;
}

int GWindow :: Keyboard(MSG &msg)
{
 switch(msg.Key)
  {
   case F1:
        RunHelp(3);
        return 1;
  }

return GSmallWindow :: Keyboard(msg);
}

void GWindow :: ScrollerShow(void)
{
 if(WndScroll & WND_HSCROLL)
  {
   HScroll.SetX(ViewX);
   HScroll.SetY(ViewY + ViewDY);
   HScroll.SetDX(ViewDX);
   HScroll.Show();
  }
 if(WndScroll & WND_VSCROLL)
  {
   VScroll.SetX(ViewX + ViewDX);
   VScroll.SetY(ViewY);
   VScroll.SetDY(ViewDY);
   VScroll.Show();
  }

}
