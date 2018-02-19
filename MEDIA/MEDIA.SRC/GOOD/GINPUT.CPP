#include <string.h>
#include "shape.hpp"
#include "gdefine.hpp"
#include "proto.hpp"
#include "keys.h"
#include "ginput.hpp"


#ifndef _GINPUT
#define _GINPUT

#include "gvmode.hpp"

class GInput : public GVideoMode
{
 int SendCmd;
 int SendAdr;
 int StringSize;
 int CurrentPlace;
public:
 ~GInput();
  GInput(int x = 0,int y = 0,int strsize = 0,char *string = "",int cmd = 0,int adr = 0);

  virtual void Show(void);
  char *GetItem(void);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Keyboard(MSG &msg);        // apdorosime klavisus
  virtual int Command(MSG &msg);         // apdorosime komandas
};
#endif


GInput :: GInput(int x,int y,int strsize,char *string,int cmd,int adr)
       :  GVideoMode(x,y,strsize * 8 + 4,20)
{
 SendCmd = cmd;
 SendAdr = adr;
 StringSize = strsize;
 CurrentPlace = 0;
 WndName = new char[StringSize + 1];
 if(WndName != 0L)
  {
   memcpy(WndName,string,StringSize);
   if(StringSize > strlen(WndName))
    memset(WndName + strlen(WndName),' ',StringSize - strlen(WndName));
   WndName[StringSize] = 0;
 }
}

GInput :: ~GInput()
{
 if(WndName != 0L)
  delete WndName;
}

void GInput :: Show(void)
{
 InputDraw(X,Y,DX,DY,WndName,WndActive,CurrentPlace);
}

ClassType GInput :: isA()
{
 return _GInput;
}

char *GInput :: GetItem(void)
{
 return WndName;
}

int GInput :: Mouse(MSG &msg)
{
 int i;

 if(isMyFrame(msg.X,msg.Y) && msg.ButtonStatus)
  {
   if(WndActive == WND_ACTIVE && (msg.Mouse & LBUTTON))
    {
     i = (msg.X - X + 2) / 8;
     if(i >= StringSize)
      return 1;
     MoveGInputCursor(X,Y,CurrentPlace,i);
     CurrentPlace = i;
    }
   return 1;
  }
return 0;
}

int GInput :: Keyboard(MSG &msg)
{
 int i;
 int oldPlace;

 switch(msg.Key)
  {
   case CR:
        SendMSGCmd(SendCmd,SendAdr);
        return 1;
   default:
        oldPlace = CurrentPlace;
        if((i = FillStr(msg.Key,WndName,CurrentPlace,StringSize)) != 0)
         {
          if(i == 1)
           Show();
          else
           MoveGInputCursor(X,Y,oldPlace,CurrentPlace);
          return 1;
         }
  }
return 0;
}

int GInput :: Command(MSG &msg)
{
 switch(msg.Cmd)
  {
   case ITEM_ACTIVE:
        WndActive = WND_ACTIVE;
        Show();
        return 1;
   case ITEM_PASIVE:
        WndActive = WND_PASIVE;
        Show();
        return 0;
  }
return 0;
}
