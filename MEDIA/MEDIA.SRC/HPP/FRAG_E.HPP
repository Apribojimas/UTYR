#ifndef _FRAGMENT_ELLIPSE
#define _FRAGMENT_ELLIPSE

#include "frag_r.hpp"

class FragmentEllipse : public FragmentRectangle
{
 int EX1;
 int EX2;
 int EY1;
 int EY2;
 int ERadius;
public:
 ~FragmentEllipse();
  FragmentEllipse(int FragNumber,int Index,int Sendadr = 0);

  virtual void Show();
  int isMyFrame(int x,int y);
  virtual void CalculateHistogram(long HistoHandler);
  virtual void MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
protected:
  virtual void DisplayFragmentInfo(void);
  virtual void BeginMark(int x,int y);
  virtual void EndMark(int x,int y);
  virtual void MoveMark(int x,int y);
private:
void HistoEllipse( long Handler,
                   int x1, int y1,int x2, int y2, int b0,
                   long HistoHandler);
};
#endif
