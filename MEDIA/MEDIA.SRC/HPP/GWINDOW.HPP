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
