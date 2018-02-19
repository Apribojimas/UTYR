#ifndef _FRAGMENT_CIRCLE
#define _FRAGMENT_CIRCLE

#include "frag_r.hpp"

class FragmentCircle : public FragmentRectangle
{
 int CX;
 int CY;
 int CR;
public:
 ~FragmentCircle();
  FragmentCircle(int FragNumber,int Index,int Sendadr = 0);

  virtual void Show();
  virtual void CalculateHistogram(long HistoHandler);
  virtual void MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual void DisplayFragmentInfo(void);
  virtual void BeginMark(int x,int y);
  virtual void EndMark(int x,int y);
  virtual void MoveMark(int x,int y);
private:
 void HistoCircle( long Handler,int r,long HistoHandler);
};
#endif
