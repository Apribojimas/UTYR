#include "gvmode.hpp"
#include "graph.hpp"
#include "gdefine.hpp"

#ifndef _GVMODE
#define _GVMODE

#include "geventha.hpp"
extern int CurrentMode;

class GVideoMode : public GEventHandler
{
protected:
 int MemMode;
public:
 ~GVideoMode();
  GVideoMode(int x = 0,int y = 0,int dx = 0,int dy = 0);

  int ChangeVariable(int i,int mode = CurrentMode); // masteluoja kintamaji
  int GetVideoMode(void);
  virtual void SetVideoMode(int mode);
// reikalinga Object
  virtual ClassType isA();
};
#endif

GVideoMode :: GVideoMode(int x,int y,int dx,int dy)
            : GEventHandler(x,y,dx,dy)
{
 MemMode   = MODE_640;
}

GVideoMode :: ~GVideoMode()
{
}

void GVideoMode :: SetVideoMode(int mode)
{
 if(!(mode == MODE_TEXT ||
      mode == MODE_640 ||
      mode == MODE_800 ||
      mode == MODE_1024) ||
      mode == MemMode)
  return;

 if(X >= 0)
  X = ChangeVariable(X);
 if(Y >= 0)
  Y = ChangeVariable(Y);

 if(WndType & WND_TEXT)
  {
   DX = ChangeVariable(DX);
   DY = ChangeVariable(DY);
   if(X + DX <= 50)
    X += 50 - (X + DX);
  }

 MemMode = mode;
}

int GVideoMode :: ChangeVariable(int i,int mode)
{
 float NewMode;
 float OldMode;

 switch(mode)
  {
   case MODE_640:
        OldMode = 640.;
        break;
   case MODE_800:
        OldMode = 800.;
        break;
   case MODE_1024:
        OldMode = 1024.;
        break;
  }

 switch(MemMode)
  {
   case MODE_640:
        NewMode = 640.;
        break;
   case MODE_800:
        NewMode = 800.;
        break;
   case MODE_1024:
        NewMode = 1024.;
        break;
  }

 i = i * (OldMode / NewMode) + 0.5;
return i;
}

int GVideoMode :: GetVideoMode(void)
{
 return MemMode;
}

ClassType GVideoMode :: isA()
{
 return _GVideoMode;
}

