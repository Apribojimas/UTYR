#ifndef _HIGHPASS
#define _HIGHPASS

#include "vcmd.hpp"

#include "filter.hpp"

class HighPass : public Filtering
{
 int Type;
 public:
  HighPass(long ScrHandler,int dx, int dy,int sentAdr,int Type = CLASIC);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif
