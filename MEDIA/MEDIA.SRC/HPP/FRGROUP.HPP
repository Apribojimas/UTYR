#ifndef _FRAGMENT_GROUP
#define _FRAGMENT_GROUP

#include "Group.hpp"

class FragmentGroup : public Group
{
public:
 ~FragmentGroup();
  FragmentGroup(int x = 0,int y = 0);

  virtual void AddItem(Object *Obj);
  FragmentGroup & operator + (Object *Obj);
  void SetDisplayPort(int x,int y,int dx,int dy);
  virtual void SetActiveItem(int i);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Keyboard(MSG &msg);        // apdorosime klavisus
  virtual int Command(MSG &msg);
  virtual void SendActiveCommand(int i,int kr = 0); // siunciam item'ams active komanda
  virtual void SendPasiveCommand(int i); // siunciam item'ams pasive komanda
};
#endif
