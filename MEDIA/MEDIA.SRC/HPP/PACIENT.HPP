#ifndef _PACIENT
#define _PACIENT

#include "gwindow.hpp"

class Pacient : public GWindow
{
  GButton Button;
 public:
  ~Pacient();
   Pacient();

  virtual int EventHandler(MSG &msg);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
};
#endif
