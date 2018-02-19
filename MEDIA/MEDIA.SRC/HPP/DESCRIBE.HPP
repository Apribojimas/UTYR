#ifndef __DESCRIBE
#define __DESCRIBE

#include "point.hpp"

class Describe
{
 public:
  enum Direct { North, NW, West, SW, South, SE, East, NE } direction;
  enum { Backword=-4, RightBack,   Right, RightForward,
	 Forward,     LeftForward, Left,  LeftBack      };
 public:
  Describe(void){direction=North;}
  Point NextPoint(int d);
  void Direction (int d);
};
#endif //__DESCRIBE

