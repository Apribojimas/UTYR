#ifndef _GRADIOBUTTON
#define _GRADIOBUTTON

#include "gvmode.hpp"
#include "gdefine.hpp"

class GRadioButton : public GEventHandler
{
protected:
 int Justify;
 int ButtonCmd;
 int ButtonActiveKey;     // aktivavimo raktas
 int ButtonHotKey;        // taip pat aktyvavimo raktas
 int ButtonPlaceActiveKey; // aktyvaus rakto vieta uzrase

public:
 ~GRadioButton();
  GRadioButton(int x,int y,int dx,int dy,char *string = "",int cmd = 0,int adr = 0,int hotkey = 0xffff,int justify = JUSTIFY_CENTER,int status = BUTTON_PASIVE);

  virtual void Show(void);
// reikalinga Object
  virtual ClassType isA();

protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Keyboard(MSG &msg);        // apdorosime klavisus
  virtual int Command(MSG &msg);         // apdorosime komandas
};
#endif
