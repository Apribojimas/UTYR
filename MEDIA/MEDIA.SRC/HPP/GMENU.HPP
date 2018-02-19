#ifndef _GMENU
#define _GMENU

#include "bag.hpp"
#include "group.hpp"

class GMenu : public Group
{
 int MenuType;
 int SendCmd;
public:
 ~GMenu();
  GMenu(int x = 0,int y = 0,int menutype = 0,int sendcmd = 0);

  GMenu & operator + (Object *Obj);
  int  GetMenuSize(void);
  void NewMenu(int activeitem = 0);
  void SetMenuSize(int dx,int dy);
  virtual void AddItem(Object *Obj);
  virtual void SetActiveItem(int i);
  virtual void Show(void);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Keyboard(MSG &msg);        // apdorosime klavisus
  virtual int Command(MSG &msg);
};
#endif
