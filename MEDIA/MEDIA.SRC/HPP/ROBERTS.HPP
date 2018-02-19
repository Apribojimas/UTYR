#ifndef _ROBERTS
#define _ROBERTS

#include "vcmd.hpp"
#include "filter.hpp"

class Roberts : public Filtering
{
 int Type;
 public:
  Roberts(long ScrHandler,int dx, int dy,int sentAdr,int Type = MAX);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif
