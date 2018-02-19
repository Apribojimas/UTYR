#include <string.h>
#include "keys.h"
#include "graph.hpp"
#include "proto.hpp"
#include "gbutton.hpp"

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

GButton :: GButton(int x,int y,int dx,int dy,char *string,int cmd,int adr,int hotkey,int justify,int status)
         : GRadioButton(x,y,dx,dy,string,cmd,adr,hotkey,justify,status)
{
 isButtonFixedMode = 0;
 isButtonPressed = RELEASE;

 Heap("GButton :: GButton");
}

GButton :: ~GButton()
{
}

void GButton :: Show(void)
{
 Heap("GButton :: Show");
 ButtonDraw(X,Y,DX,DY,WndName,ButtonPlaceActiveKey,WndEvent,Justify,isButtonPressed);
}

void GButton :: FixedMode(void)
{
 isButtonFixedMode = 1;
}

void GButton :: FlowMode(void)
{
 isButtonFixedMode = 0;
}

ClassType GButton :: isA()
{
 return _GButton;
}

int GButton :: Mouse(MSG &msg)
{
 if((msg.Mouse & LBUTTON) && isMyFrame(msg.X,msg.Y))
  {
   if(isButtonFixedMode)
    {
     if(isButtonPressed == PRESSED)
      {
       isButtonPressed = RELEASE;
       if(WndEvent != BUTTON_UNAVAILABLE)
        SendMSGCmd(ButtonCmd,RegisterNumber);
       Show();
      }
     else
      {
       isButtonPressed = PRESSED;
       Show();
      }
     Sound();
    }
   else
    {
     isButtonPressed = PRESSED;
     Show();
    }
   return 1;
  }

 if(msg.Mouse & LBUTTON_UP && !isButtonFixedMode)
  switch(isButtonPressed)
   {
    case PRESSED:
         isButtonPressed = RELEASE;
         if(WndEvent != BUTTON_UNAVAILABLE)
          SendMSGCmd(ButtonCmd,RegisterNumber);
         Show();
         Sound();
         return 1;
   }

return 0;
}

int GButton :: Keyboard(MSG &msg)
{
 if(Toupper(msg.Key) == Toupper(ButtonActiveKey) ||
    msg.Key == ButtonHotKey ||
    msg.Key == CR)
  {
   if(isButtonFixedMode)
    {
     if(isButtonPressed == PRESSED)
      {
       if(WndEvent != BUTTON_UNAVAILABLE)
        SendMSGCmd(ButtonCmd,RegisterNumber);
       isButtonPressed = RELEASE;
      }
     else
      {
       isButtonPressed = PRESSED;
      }
     Show();
     Sound();
    }
   else
    {
     ButtonDraw(X,Y,DX,DY,WndName,ButtonPlaceActiveKey,WndEvent,Justify,PRESSED);
     Sound();
     ButtonDraw(X,Y,DX,DY,WndName,ButtonPlaceActiveKey,WndEvent,Justify,RELEASE);
     if(WndEvent != BUTTON_UNAVAILABLE)
      SendMSGCmd(ButtonCmd,RegisterNumber);
    }
   Heap("int GButton :: Keyboard(MSG &msg) 0");
   return 1;
  }
Heap("int GButton :: Keyboard(MSG &msg) 1");
return 0;
}
