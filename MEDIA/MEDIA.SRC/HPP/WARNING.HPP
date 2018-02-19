#ifndef WARNING
#define WARNING

#include "gwindow.hpp"

class Warning : public GWindow
{
 char *WarningString;
 GButton Button;
public:
 ~Warning();
  Warning(int TextNr);
  Warning(char *str);

  virtual int EventHandler(MSG &msg);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Keyboard(MSG &msg);       // klaviaturos
private:
  void SetWarningString(char *str);
};
#endif
