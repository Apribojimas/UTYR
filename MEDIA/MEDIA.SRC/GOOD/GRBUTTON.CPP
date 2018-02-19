#include <string.h>
#include "keys.h"
#include "proto.hpp"
#include "grbutton.hpp"

#ifndef _GRADIOBUTTON
#define _GRADIOBUTTON

#include "gvmode.hpp"
#include "gdefine.hpp"

class GRadioButton : public GEventHandler
{
protected:
 int Justify;
 int ButtonCmd;
 int ButtonActiveKey;     // aktyvavimo raktas
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

GRadioButton :: GRadioButton(int x,int y,int dx,int dy,char *string,int cmd,int adr,int hotkey,int justify,int status)
             :  GEventHandler(x,y,dx,dy)
{
 int i;
 int j;

 ButtonCmd            = cmd;
 WndEvent             = status;
 ButtonActiveKey      = 0;
 ButtonPlaceActiveKey = 0xffff;
 ButtonHotKey         = hotkey;
 RegisterNumber       = adr;
 Justify              = justify;

 WndName = new char [strlen(string) + 1];
 for(i = 0,j = 0;i < strlen(string) + 1;i ++)
  {
   if(string[i] == '~')
    {
     ButtonPlaceActiveKey = i;
     ButtonActiveKey = string[i + 1];
     j = 1;
    }
   WndName[i] = string[i + j];
  }
 WndName[strlen(string) - j] = 0;
}

GRadioButton :: ~GRadioButton()
{
 if(WndName != NULL)
  delete WndName;
}

void GRadioButton :: Show(void)
{
 RadioButtonDraw(X,Y,DX,DY,WndName,ButtonPlaceActiveKey,WndEvent,Justify);
}

ClassType GRadioButton :: isA()
{
 return _GRadioButton;
}

int GRadioButton :: Mouse(MSG &msg)
{
 if(isMyFrame(msg.X,msg.Y))
  if(msg.Mouse & LBUTTON)
   {
    if(WndEvent != BUTTON_UNAVAILABLE)
     {
      WndEvent = BUTTON_ACTIVE;
      Show();
      SendMSGCmd(ButtonCmd,RegisterNumber);
     }
    return 1;
   }
return 0;
}

int GRadioButton :: Keyboard(MSG &msg)
{
 if((Toupper(msg.Key) == Toupper(ButtonActiveKey) ||
     msg.Key == ButtonHotKey ||
     msg.Key == CR) &&
     WndEvent != BUTTON_UNAVAILABLE)
  {
   WndEvent = BUTTON_ACTIVE;
   Show();
   SendMSGCmd(ButtonCmd,RegisterNumber);
   return 1;
  }
return 0;
}

int GRadioButton :: Command(MSG &msg)
{
 switch(msg.Cmd)
  {
   case ITEM_ACTIVE:
        if(WndEvent == BUTTON_UNAVAILABLE)
         return 0;
        WndEvent = BUTTON_ACTIVE;
        Show();
        return 1;
   case ITEM_PASIVE:
        if(WndEvent == BUTTON_UNAVAILABLE)
         return 0;
        WndEvent = BUTTON_PASIVE;
        Show();
        return 0;
   case ITEM_UNAVAILABLE:
        WndEvent = BUTTON_UNAVAILABLE;
        break;
   case ITEM_SHOW:
        Show();
        break;
  }
return 0;
}
