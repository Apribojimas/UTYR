#ifndef _GRECTANGLE
#define _GRECTANGLE

#include "gpoint.hpp"

class GRectangle : public GPoint
{
protected:
 int DX;
 int DY;
public:
 ~GRectangle();
  GRectangle(int x = 0,int y = 0,int dx = 0,int dy = 0);

  int GetDX(void);
  int GetDY(void);
  void SetDX(int dx);
  void SetDY(int dy);
  void SetDXDY(int dx,int dy);
  int isMyFrame(int x,int y);
// reikalinga Object
  virtual ClassType isA();
};
#endif
