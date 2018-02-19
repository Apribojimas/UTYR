#ifndef _GROLLER
#define _GROLLER

#include "gdefine.hpp"
#include "GMenu.hpp"
#include "GScroll.hpp"
#include "Bag.hpp"

class GRoller : public GMenu
{
 int Justify;
 int WidthText;
 int HeightText;
 int SendCmd;
 int SendAdr;
 int ShowActiveItem;
 int isFillMenu;
 int MemScrollPos;
 unsigned int isSetActiveItem;
 GScroll Scroll;
 Bag MyBag;
public:
 ~GRoller();
  GRoller(int x = 0,int y = 0,int widthText = 0,int heightText = 0,int cmd = 0,int adr = 0,int justify = JUSTIFY_LEFT);

  char *GetItem(void);
  Object * GetObject(int i);
  Bag *ReturnBagPtr(void);
  virtual void AddObject(Object *Obj);
  virtual void AddString(char * String,int registernumber = 0);
  virtual void DropItem(int i);
  virtual void SetActiveItem(int i);
  virtual void SetActiveItem(char *str);
  virtual void SetActiveItem(void);
  virtual int  GetActiveItem(void);
  virtual void Show(void);
  virtual int  EventHandler(MSG &msg);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Keyboard(MSG &msg);       // klaviaturos
  virtual int Mouse(MSG &msg);
  virtual int Command(MSG &msg);
private:
  void FillMenu(void);
  int PrivateSetActiveItem(int i);
};
#endif
