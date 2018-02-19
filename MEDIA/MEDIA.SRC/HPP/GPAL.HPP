#ifndef _GPALETTE
#define _GPALETTE

#include "gwindow.hpp"

class GPalette : public GWindow
{
 long MHandler;
public:
 ~GPalette();
  GPalette(long mhandler);

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
//  virtual int Mouse(MSG &msg);           // mouse eventai
//  virtual int Command(MSG &msg);         // apdorosime komandas
//  virtual int Keyboard(MSG &msg);        // klaviaturos
};
#endif
