#ifndef _SKANER
#define _SKANER

#include "gwindow.hpp"

class Skaner : public GWindow
{
 int Index;
 char file[MAXFILE];
 char ext[MAXEXT];
 Group MyGroup;
public:
 ~Skaner();
  Skaner();

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual int EventHandler(MSG &msg);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);         // apdorosime komandas
private:
  void Griepti(void);
  void SetFile(void);
};
#endif
