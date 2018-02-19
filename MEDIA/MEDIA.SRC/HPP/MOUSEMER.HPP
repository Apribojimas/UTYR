#ifndef _MOUSE_MER
#define _MOUSE_MER

#include "gwindow.hpp"

class MouseMer : public GWindow
{
 int MouseEventStatus;
 int MemMouseX;
 int MemMouseY;
 int LockMouseX;
 int LockMouseY;
public:
 ~MouseMer();
  MouseMer();

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);          // mouse eventai
  virtual int Keyboard(MSG &msg);       // klaviaturos
  virtual int Command(MSG &msg);        // apdorosime komandas
private:
  void OutMouseInfo(void);
};
#endif
