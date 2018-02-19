#ifndef _GROLLERDATA
#define _GROLLERDATA

#include "Object.hpp"

class GRollerData : public Object
{
public:
 char *String;
public:
 ~GRollerData();
  GRollerData(char *string);
// reikalinga Object
  virtual ClassType isA();
};
#endif
