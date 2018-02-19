#ifndef _DESKTOP_WINDOW
#define _DESKTOP_WINDOW

#include "gwindow.hpp"
#include "groller.hpp"

class DeskTopWindow : public GWindow
{
 int CurrentGroup;
 Group MyGroup;
public:
 ~DeskTopWindow();
  DeskTopWindow();

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual int  EventHandler(MSG &msg);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);         // apdorosime komandas
private:
  void FillGroup(int i);                 // uzpildom menu
  void NewIcon(int registernumber,char *windowname);
  void DropIcon(int registernumber);
  GRoller * FindGRoller(void);
};
#endif
