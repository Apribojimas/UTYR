#ifndef __FILLREGION
#define __FILLREGION

#include "point.hpp"
#include "describe.hpp"
#include "bitmap.hpp"
#include "bag.hpp"

class FillRegion : protected Describe, public BitMap
{
 public:
  Bag *BorderBag;

 public:
  FillRegion(int dx,int dy);
 ~FillRegion();
  void TraceBorder(Point &StartP);    // Apeiti sriti ir
                                      // pseudo ekranas sunaikinti
  void GetFillingArea(void);          // uzpildymo masyvo gavimas
};

#endif //__FILLREGION
