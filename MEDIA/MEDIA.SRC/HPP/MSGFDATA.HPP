#ifndef _MSGFILTERDATA
#define _MSGFILTERDATA

#include "Object.hpp"

class MSGFilterData : public Object
{
public:
 int Data;
public:
 ~MSGFilterData();
  MSGFilterData(int i = 0);
// reikalinga Object
  virtual ClassType isA();
};
#endif
