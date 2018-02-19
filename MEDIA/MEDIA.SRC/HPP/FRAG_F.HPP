#ifndef _FRAGMENT_FRAGMENT
#define _FRAGMENT_FRAGMENT

#include "nregular.hpp"
#include "frag_r.hpp"
#include "bag.hpp"

class FragmentFragment : public FragmentRectangle
{
 int LineX;
 int LineY;
 Bag MyBag;
 NonRegular NonReg;
public:
 ~FragmentFragment();
  FragmentFragment(int FragNumber,int Index,int Sendadr = 0);

  virtual void Show();
  virtual void MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY);
  virtual void CalculateHistogram(long HistoHandler);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
protected:
  virtual void DisplayFragmentInfo(void);
  virtual void BeginMark(int x,int y);
  virtual void EndMark(int x,int y);
  virtual void MoveMark(int x,int y);
};
#endif
