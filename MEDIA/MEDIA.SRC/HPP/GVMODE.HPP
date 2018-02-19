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
