#ifndef _AVERAGE
#define _AVERAGE

#include "filter.hpp"

class Average : public Filtering
{
 int Type;
 int MatShift;
 int MatSize;
 public:
  Average(long ScrHandler,int dx, int dy,int sentAdr, int Type = 0);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif
