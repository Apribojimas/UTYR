#include "gframe.hpp"

#ifndef _GFRAME
#define _GFRAME

#include "gvmode.hpp"

class GFrame : public GVideoMode
{
public:
 ~GFrame();
  GFrame(int x = 0,int y = 0,int dx = 0,int dy = 0);

  virtual void Show();
// reikalinga Object
  virtual ClassType isA();
};
#endif

GFrame :: GFrame(int x,int y,int dx,int dy)
            : GVideoMode(x,y,dx,dy)
{
}

GFrame :: ~GFrame()
{
}

void GFrame :: Show()
{
 RectangleDraw(X,Y,DX,DY);
}

ClassType GFrame :: isA()
{
 return _GFrame;
}

