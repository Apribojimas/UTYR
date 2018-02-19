#include <alloc.h>
#include <string.h>
#include "define.hpp"
#include "grollerd.hpp"

void Heap(char far *record);

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

GRollerData :: GRollerData(char *string)
{
 String = new char [strlen(string) + 1];
 if(String != 0L)
  strcpy(String,string);
}

GRollerData :: ~GRollerData()
{
 if(String != 0L)
  delete String;
}

ClassType GRollerData :: isA()
{
 return _GRollerData;
}
