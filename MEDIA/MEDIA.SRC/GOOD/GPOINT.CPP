#include "gpoint.hpp"

#ifndef _GPOINT
#define _GPOINT

#include "object.hpp"
#include "define.hpp"

class GPoint : public Object
{
protected:
 int X;
 int Y;
public:
 ~GPoint();
  GPoint(int x = 0,int y = 0);

  int GetX(void);
  int GetY(void);
  void SetX(int x);
  void SetY(int y);
  void SetXY(int x,int y);
  virtual void Show(void);
  virtual void Hide(void);
// reikalinga Object
  virtual ClassType isA();
};
#endif

GPoint :: GPoint(int x,int y)
{
 X = x;
 Y = y;
}

GPoint :: ~GPoint()
{
}

int GPoint :: GetX(void)
{
 return X;
}

int GPoint :: GetY(void)
{
 return Y;
}

void GPoint :: SetX(int x)
{
 X = x;
}

void GPoint :: SetY(int y)
{
 Y = y;
}

void GPoint :: SetXY(int x,int y)
{
 X = x;
 Y = y;
}

void GPoint :: Show(void)
{
}

void GPoint :: Hide(void)
{
}

ClassType GPoint :: isA()
{
 return _GPoint;
}

