#ifndef _EDGE
#define _EDGE

#include "vcmd.hpp"
#include "filter.hpp"

class Edge : public Filtering
{
 int Type;
 public:
  Edge(long ScrHandler,int dx, int dy,int sentAdr,int Type = CLASIC);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif
