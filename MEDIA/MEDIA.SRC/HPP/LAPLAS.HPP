#ifndef _LAPLAS
#define _LAPLAS

#include "vcmd.hpp"
#include "filter.hpp"

class Laplas : public Filtering
{
 int Type;
 public:
  Laplas(long ScrHandler,int dx, int dy,int sentAdr,int Type = CLASIC);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif
