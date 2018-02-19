#ifndef _GBUTTON
#define _GBUTTON

#include "grbutton.hpp"

class GButton : public GRadioButton
{
protected:
 int isButtonPressed;         // butono statusas (paspaustas ar atleistas)
 int isButtonFixedMode;        // ar butonas dirba trigerio rezime

public:
 ~GButton();
  GButton(int x,int y,int dx,int dy,char *string = "",int cmd = 0,int adr = 0,int hotkey = 0xffff,int justify = JUSTIFY_CENTER,int status = BUTTON_PASIVE);

  virtual void Show(void);
  void FixedMode(void);
  void FlowMode(void);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Keyboard(MSG &msg);        // apdorosime klavisus
};
#endif
