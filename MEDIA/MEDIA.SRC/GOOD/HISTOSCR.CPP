#include <stdio.h>
#include "proto.hpp"
#include "gettext.hpp"
#include "graph.hpp"
#include "define.hpp"
#include "gdefine.hpp"
#include "vcmd.hpp"
#include "gscroll.hpp"
#include "histoscr.hpp"

#ifndef _HISTOSCROLLER
#define _HISTOSCROLLER

#include "taipne.hpp"

class HistoScroller : public Taip_Ne
{
 GScroll Scroll;
public:
 ~HistoScroller();
  HistoScroller(int SendMSG_ok,int SendMSG_cancel,int Sendadr,int Textnr,
                int WndName,int ScrollScale = 100);

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

HistoScroller :: HistoScroller(int SendMSG_ok,int SendMSG_cancel,int Sendadr,int Textnr,int WndName,int ScrollScale)
              : Taip_Ne(SendMSG_ok,SendMSG_cancel,Sendadr,Textnr,200,200,340,90,GetText(WndName)),
                Scroll(20,30,260,HORIZANTAL,ScrollScale)
{
 Scroll.SetPos(1);
 if(DX < 340 + 16)
  SetDXDY(340,90);
}


HistoScroller :: ~HistoScroller()
{
}

#pragma argsused
void HistoScroller :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{

 SetGroundColor(GRAY_10);
 SetColor(GRAY_10);
 Bar(x,y,dx,dy);

 Scroll.SetXY(x + 15,y + dy - 50);
 Scroll.Show();

 MyGroup.SetXY(x + dx / 2 - 105,y + dy - 30);
 MyGroup.Show();

 DisplayInfo();

 OutText(x + 15,y + 15,GetText(TextNr));
}

int HistoScroller :: EventHandler(MSG &msg)
{

 Taip_Ne :: EventHandler(msg);
 if(Scroll.EventHandler(msg))
  DisplayInfo();

return 1;
}

int HistoScroller :: Command(MSG &msg)
{
 switch(msg.Cmd)
  {
   case ITEM_OK:
	SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        SendMSGCmd(SendMSG_OK,SendAdr,Scroll.GetPos());
        return 1;
   }

return Taip_Ne :: Command(msg);
}

ClassType HistoScroller :: isA()
{
 return _HistoScroller;
}

void HistoScroller :: DisplayInfo(void)
{
 char str[20];

 SetGroundColor(GRAY_10);
 SetColor(_BLACK);
 sprintf(str,"%3i",Scroll.GetPos());
 OutText(ViewX + 300,ViewY + ViewDY - 50,str);
}
