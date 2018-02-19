#ifndef _GROUP
#define _GROUP

#include "geventha.hpp"
#include "bag.hpp"

class Group : public GEventHandler
{
protected:
 unsigned int ActiveItem;      // kuris 'button' aktyvus
 Bag ItemShift;  // cia saugom postumius lango atzvilgiu
 Bag MyBag;      // saugom item'us

public:
 ~Group();
  Group(int x = 0,int y = 0);

  virtual void Show(void);
  virtual int EventHandler(MSG &msg);

  Group & operator + (Object *Obj);
  virtual void AddItem(Object *Obj);
  void operator - (int i);
  void NewGroup(int activeitem = 0);

  Object * GetItem(int i);
  int GetGroupSize(void);
  virtual int  GetActiveItem(void);

  virtual void SetActiveItem(int i);
  virtual void SetItemShift(int i,int dx,int dy);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Keyboard(MSG &msg);        // apdorosime klavisus
  virtual int Command(MSG &msg);
  virtual void SendActiveCommand(int i,int kryptis = 0); // siunciam item'ams active komanda
                                                         // jei kryptis = 0 tai ieskom aktyviu item index ++ else index --
  virtual void SendPasiveCommand(int i); // siunciam item'ams pasive komanda
};
#endif
