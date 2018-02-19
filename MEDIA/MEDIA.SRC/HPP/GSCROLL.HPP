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
