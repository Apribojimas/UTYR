#ifndef _GCHECKBUTTON
#define _GCHECKBUTTON

#include "gbutton.hpp"

class GCheckButton : public GButton
{
protected:
 int ButtonCmdPasive;
public:
 ~GCheckButton();
  GCheckButton(int x,int y,int dx,int dy,char *string = "",int cmdactive = 0,int cmdpasive = 0,int adr = 0,int hotkey = 0xffff,int status = BUTTON_PASIVE);

  virtual void Show(void);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Keyboard(MSG &msg);        // apdorosime klavisus
};
#endif
