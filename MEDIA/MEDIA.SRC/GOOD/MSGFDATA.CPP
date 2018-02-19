#include "define.hpp"
#include "msgfdata.hpp"

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

MSGFilterData :: MSGFilterData(int i)
{
 Data = i;
}

MSGFilterData :: ~MSGFilterData()
{
}

ClassType MSGFilterData :: isA()
{
 return _MSGFilterData;
}
