#include <stdio.h>
#include "proto.hpp"
#include "gettext.hpp"
#include "graph.hpp"
#include "define.hpp"
#include "gdefine.hpp"
#include "vcmd.hpp"
#include "gscroll.hpp"
#include "histomod.hpp"

#ifndef _HISTOMOD
#define _HISTOMOD

#include "taipne.hpp"

class HistoMod : public Taip_Ne
{
 GScroll MinScroll;
 GScroll MaxScroll;

public:
 ~HistoMod();
  HistoMod(int SendMSG_ok,int SendMSG_cancel,int Sendadr);

  virtual int EventHandler(MSG &msg);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();

protected:
  virtual int Command(MSG &msg);

private:
  void DisplayInfo(void);
};
#endif

HistoMod :: HistoMod(int SendMSG_ok,int SendMSG_cancel,int Sendadr)
              : Taip_Ne(SendMSG_ok,SendMSG_cancel,Sendadr,0,200,200,330,120,GetText(10092)),
                MinScroll(20,30,240,HORIZANTAL,255),
                MaxScroll(20,30,240,HORIZANTAL,255)
{
 MinScroll.SetPos(0);
 MaxScroll.SetPos(255);
}

HistoMod :: ~HistoMod()
{
}

#pragma argsused
void HistoMod :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{

 SetGroundColor(GRAY_10);
 SetColor(GRAY_10);
 Bar(x,y,dx,dy);

 MinScroll.SetXY(x + 45,y + dy - 50);
 MinScroll.Show();
 OutText(x + 10,y + dy - 50,"Min");

 MaxScroll.SetXY(x + 45,y + dy - 70);
 MaxScroll.Show();
 OutText(x + 10,y + dy - 70,"Max");

 MyGroup.SetXY(x + dx / 2 - 105,y + dy - 30);
 MyGroup.Show();

 DisplayInfo();

 OutText(x + 15,y + 15,GetText(10107));
}

int HistoMod :: EventHandler(MSG &msg)
{

 Taip_Ne :: EventHandler(msg);
 if(MinScroll.EventHandler(msg))
  DisplayInfo();
 if(MaxScroll.EventHandler(msg))
  DisplayInfo();

return 1;
}

int HistoMod :: Command(MSG &msg)
{
 switch(msg.Cmd)
  {
   case ITEM_OK:
	SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        SendMSGCmd(SendMSG_OK,SendAdr,MinScroll.GetPos(),MaxScroll.GetPos());
        return 1;
   }

return Taip_Ne :: Command(msg);
}

ClassType HistoMod :: isA()
{
 return _HistoMod;
}

void HistoMod :: DisplayInfo(void)
{
 char str[20];

 SetGroundColor(GRAY_10);
 SetColor(_BLACK);
 sprintf(str,"%3i",MinScroll.GetPos());
 OutText(ViewX + 300,ViewY + ViewDY - 50,str);

 sprintf(str,"%3i",MaxScroll.GetPos());
 OutText(ViewX + 300,ViewY + ViewDY - 70,str);
}
