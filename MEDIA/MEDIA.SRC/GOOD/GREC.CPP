#include "grec.hpp"

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

GRectangle :: GRectangle(int x,int y,int dx,int dy)
            : GPoint(x,y)
{
 DX = dx;
 DY = dy;
}

GRectangle :: ~GRectangle()
{
}

int GRectangle :: GetDX(void)
{
 return DX;
}

int GRectangle :: GetDY(void)
{
 return DY;
}

void GRectangle :: SetDX(int dx)
{
 DX = dx;
}

void GRectangle :: SetDY(int dy)
{
 DY = dy;
}

void GRectangle :: SetDXDY(int dx,int dy)
{
 DX = dx;
 DY = dy;
}

ClassType GRectangle :: isA()
{
 return _GRectangle;
}

int GRectangle:: isMyFrame(int x,int y)
{
 if (x > X && x < X + DX && y > Y && y < Y + DY)
  return 1;

return 0;
}
