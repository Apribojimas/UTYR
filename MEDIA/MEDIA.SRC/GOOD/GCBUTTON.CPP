#include "proto.hpp"
#include "keys.h"
#include "gcbutton.hpp"

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

GCheckButton :: GCheckButton(int x,int y,int dx,int dy,char *string,int cmdactive,int cmdpasive,int adr,int hotkey,int status)
             :  GButton(x,y,dx,dy,string,cmdactive,adr,hotkey,status)
{
 ButtonCmdPasive = cmdpasive;
}

GCheckButton :: ~GCheckButton()
{
}

void GCheckButton :: Show(void)
{
 CheckButtonDraw(X,Y,DX,DY,WndName,ButtonPlaceActiveKey,WndEvent,isButtonPressed);
}


ClassType GCheckButton :: isA()
{
 return _GCheckButton;
}

int GCheckButton :: Mouse(MSG &msg)
{
 if((msg.Mouse & LBUTTON) && isMyFrame(msg.X,msg.Y))
  {
   if(isButtonPressed == PRESSED)
    {
     isButtonPressed = RELEASE;
     SendMSGCmd(ButtonCmd,RegisterNumber);
    }
   else
    {
     isButtonPressed = PRESSED;
     SendMSGCmd(ButtonCmdPasive,RegisterNumber);
    }
   Show();
   Sound();
   return 1;
  }

return 0;
}

int GCheckButton :: Keyboard(MSG &msg)
{
 if(Toupper(msg.Key) == Toupper(ButtonActiveKey) ||
    msg.Key == ButtonHotKey ||
    msg.Key == CR)
  {
   if(isButtonPressed == PRESSED)
    {
     isButtonPressed = RELEASE;
     SendMSGCmd(ButtonCmd,RegisterNumber);
    }
   else
    {
     isButtonPressed = PRESSED;
     SendMSGCmd(ButtonCmdPasive,RegisterNumber);
    }
   Show();
   Sound();
   return 1;
  }

return 0;
}
