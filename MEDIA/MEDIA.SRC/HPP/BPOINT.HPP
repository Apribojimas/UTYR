#ifndef _BPOINT
#define _BPOINT

#include "object.hpp"

class BPoint : public Object
{
 public:
  int x;
  int y;
  int flg;
 public:
  BPoint(int x = 0,int y = 0,int flag = 0);
 ~BPoint();
  virtual ClassType isA();
};
#endif
