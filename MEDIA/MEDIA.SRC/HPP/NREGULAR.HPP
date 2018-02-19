#ifndef _NONREGULAR
#define _NONREGULAR

#include "fillreg.hpp"

class NonRegular
{
  int LeftPointY;
  FillRegion  *FR;

 public:
  long BorderHandler;
  int  BorderSize;
  long FillingHandler;
  int  FillingSize;

 public:
  NonRegular();
 ~NonRegular();
  void Delete(void);
  void FillMemory(int DX,int DY,Bag *pBag);
  // Bag'as jau nebereikalingas;
  void CopyBorderToMM();
};

#endif

