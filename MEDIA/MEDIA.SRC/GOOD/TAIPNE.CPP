#include <string.h>
#include "graph.hpp"
#include "gettext.hpp"
#include "define.hpp"
#include "gdefine.hpp"
#include "vcmd.hpp"
#include "proto.hpp"
#include "keys.h"
#include "taipne.hpp"

extern int WarningCounter;

#ifndef TAIP_NE
#define TAIP_NE

#include "gwindow.hpp"

class Taip_Ne : public GWindow
{
protected:
 int TextNr;
 int SendMSG_OK;
 int SendMSG_Cancel;
 int SendAdr;
 GMenu MyGroup;
public:
 ~Taip_Ne();
  Taip_Ne(int SendMSG_ok,int SendMSG_cancel,int Sendadr,int Textnr);
  Taip_Ne(int SendMSG_ok,int SendMSG_cancel,int Sendadr,int Textnr,int x,int y,int dx,int dy,char *wndname);

  virtual int EventHandler(MSG &msg);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Keyboard(MSG &msg);       // klaviaturos
  virtual int Command(MSG &msg);
private:
  void SetWarningString(char *str);
  void Init(int SendMSG_ok,int SendMSG_cancel,int Sendadr,int Textnr);
};
#endif

Taip_Ne :: Taip_Ne(int SendMSG_ok,int SendMSG_cancel,int Sendadr,int Textnr)
        :  GWindow(200,200,260,70,GetText(14)),
           MyGroup(0,0,MENU_EMPTY)
{
 MyGroup + new GButton(110,0,100,20,GetText(17),TAIP_NE_CANCEL)
         + new GButton(0,0,100,20,GetText(16),TAIP_NE_OK);

 Init(SendMSG_ok,SendMSG_cancel,Sendadr,Textnr);
}

Taip_Ne :: Taip_Ne(int SendMSG_ok,int SendMSG_cancel,int Sendadr,int Textnr,int x,int y,int dx,int dy,char *wndname)
        :  GWindow(x,y,dx,dy,wndname),
           MyGroup(0,0,MENU_EMPTY)
{
 MyGroup + new GButton(110,0,100,20,GetText(2),ITEM_CANCEL)
         + new GButton(0,0,100,20,GetText(1),ITEM_OK);

 Init(SendMSG_ok,SendMSG_cancel,Sendadr,Textnr);
}

Taip_Ne :: ~Taip_Ne()
{
 WarningCounter --;
}

#pragma argsused
void Taip_Ne :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{

 SetColor(GRAY_10);
 Bar(x,y,dx,dy);
 SetColor(_BLACK);
 OutStr(x + dx / 2 - strlen(GetText(TextNr)) * 4,y + 10,GetText(TextNr));
 MyGroup.SetXY(x + dx / 2 - 105,y + dy - 30);
 MyGroup.Show();
}

int Taip_Ne :: EventHandler(MSG &msg)
{

 GWindow :: EventHandler(msg);
 MyGroup.EventHandler(msg);

return 1;
}

ClassType Taip_Ne :: isA()
{
 return _Taip_Ne;
}

int Taip_Ne :: Keyboard(MSG &msg)
{

 switch(msg.Key)
  {
   case F1:
        return 1;
  }

return GWindow :: Keyboard(msg);
}

int Taip_Ne :: Command(MSG &msg)
{

 switch(msg.Cmd)
  {
   case ITEM_OK:
   case TAIP_NE_OK:
	SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        SendMSGCmd(SendMSG_OK,SendAdr);
        return 1;
   case TAIP_NE_CANCEL:
   case ITEM_CANCEL:
	SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        SendMSGCmd(SendMSG_Cancel,SendAdr);
        return 1;
   case ITEM_ACTIVE:
        Show();
        break;
  }

return GWindow :: Command(msg);
}

void Taip_Ne :: SetWarningString(char *str)
{
 if(strlen(str) > 32)
  SetDX(strlen(str) * 8 + 20);
}

void Taip_Ne :: Init(int SendMSG_ok,int SendMSG_cancel,int Sendadr,int Textnr)
{

 WarningCounter ++;
 TextNr = Textnr;
 SendMSG_OK = SendMSG_ok;
 SendMSG_Cancel = SendMSG_cancel;
 SendAdr = Sendadr;
 SetWarningString(GetText(TextNr));
}
