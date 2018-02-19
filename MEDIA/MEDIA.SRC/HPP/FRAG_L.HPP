#ifndef _FRAGMENT_LINE
#define _FRAGMENT_LINE

#include "frag_r.hpp"
#include "point.hpp"

class FragmentLine : public FragmentRectangle
{
 Point TP1;
 Point TP2;
 int isFronto;
public:
 ~FragmentLine();
  FragmentLine(int FragNumber,int Index,int Sendadr = 0);

  virtual void Show();
  virtual void MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
protected:
  virtual void DisplayFragmentInfo(void);
  virtual void BeginMark(int x,int y);
  virtual void EndMark(int x,int y);
  virtual void MoveMark(int x,int y);
private:
  int CalculateLine(long *mhandler);
};
#endif
