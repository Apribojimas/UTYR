#ifndef _MEMMANINFO
#define _MEMMANINFO

#include "gwindow.hpp"

class MemManInfo : public GWindow
{
 char huge *EatMem;
public:
 ~MemManInfo();
  MemManInfo();

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);         // apdorosime komandas
private:
  void DisplayTaskInfo(void);
};
#endif
