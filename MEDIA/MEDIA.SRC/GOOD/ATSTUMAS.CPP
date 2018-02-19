#include <math.h>
#include "point.hpp"

int Atstumas(Point &p1,Point &p2)
{
 float i = (long)(p1.x - p2.x)*(p1.x - p2.x) + (long)(p1.y - p2.y)*(p1.y - p2.y);
 if(i)
  return sqrt(i);
return 0;
}
