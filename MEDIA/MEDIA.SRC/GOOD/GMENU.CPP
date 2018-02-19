#include <string.h>
#include "keys.h"
#include "gmenu.hpp"
#include "proto.hpp"
#include "graph.hpp"

#ifndef _GMENU
#define _GMENU

#include "bag.hpp"
#include "group.hpp"

class GMenu : public Group
{
 int MenuType;
 int SendCmd;
public:
 ~GMenu();
  GMenu(int x = 0,int y = 0,int menutype = 0,int sendcmd = 0);

  GMenu & operator + (Object *Obj);
  int  GetMenuSize(void);
  void NewMenu(int activeitem = 0);
  void SetMenuSize(int dx,int dy);
  virtual void AddItem(Object *Obj);
  virtual void SetActiveItem(int i);
  virtual void Show(void);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Keyboard(MSG &msg);        // apdorosime klavisus
  virtual int Command(MSG &msg);
};
#endif

GMenu :: GMenu(int x,int y,int menutype,int sendcmd)
       :  Group(x,y)
{
 MenuType = menutype;
 SendCmd = sendcmd;
 NewMenu();
}

GMenu :: ~GMenu()
{
}

int GMenu :: GetMenuSize(void)
{
 return MyBag.GetBagSize();
}

void GMenu :: Show(void)
{
 MenuDraw(X,Y,DX,DY,MenuType);
 Group :: Show();
}

void GMenu :: NewMenu(int activeitem)
{
 Group :: NewGroup(activeitem);
 DX = 0;
 DY = 0;
}

GMenu & GMenu :: operator + (Object *Obj)
{
 GRectangle *gr;

 gr = (GRectangle *)Obj;
 if(gr->GetX() + gr->GetDX() > DX - 4)
  DX = gr->GetX() + gr->GetDX() + 4;
 if(gr->GetY() + gr->GetDY() > DY - 4)
  DY = gr->GetY() + gr->GetDY() + 4;

 gr->SetX(gr->GetX() + 2);
 gr->SetY(gr->GetY() + 2);
 Group :: AddItem(Obj);
 return *this;
}

void GMenu :: AddItem(Object *Obj)
{
 *this + Obj;
}

ClassType GMenu :: isA()
{
 return _GMenu;
}

void GMenu :: SetActiveItem(int i)
{
 if(i < 0 || i >= MyBag.GetBagSize())
  return;
 SendPasiveCommand(ActiveItem);
 ActiveItem = i;
 SendActiveCommand(ActiveItem);
}

int GMenu :: Keyboard(MSG &msg)
{
 int i = 0;
 GEventHandler *eh;

 switch(msg.Key)
  {
    case UP:
    case LEFT:
	 SendPasiveCommand(ActiveItem);
	 ActiveItem --;
	 if(ActiveItem >= MyBag.GetBagSize())
	  ActiveItem = MyBag.GetBagSize() - 1;
	 SendActiveCommand(ActiveItem,1);
         return 1;
    case DOWN:
    case RIGHT:
	 SendPasiveCommand(ActiveItem);
	 ActiveItem ++;
	 if(ActiveItem == MyBag.GetBagSize())
	  ActiveItem = 0;
	 SendActiveCommand(ActiveItem);
         return 1;
   case CR:
	eh = (GEventHandler *)MyBag.GetItem(ActiveItem);
        if(eh != 0L)
 	 if(eh->EventHandler(msg))
          SendMSGCmd(SendCmd);
	return 1;
   case ESC:
	SendMSGCmd(SendCmd);
	return 1;
   default:
	for(i = 0;i < MyBag.GetBagSize();i ++)
	 {
	  eh = (GEventHandler *)MyBag.GetItem(i);
	  if(eh->EventHandler(msg))
	   {
            if(ActiveItem != i)
             {
 	      SendPasiveCommand(ActiveItem);
	      ActiveItem = i;
	      SendActiveCommand(ActiveItem);
             }
 	    SendMSGCmd(SendCmd);
	    return 1;
	   }
	 }
  }

return 0;
}

int GMenu :: Mouse(MSG &msg)
{
 int i;
 int j = 0;
 GEventHandler *eh;

 if(msg.Mouse & RBUTTON)           // deaktyvuojam menu
  {
   SendMSGCmd(SendCmd);
   return 1;
  }

 for(i = 0;i < MyBag.GetBagSize();i ++)
  {
   eh = (GEventHandler *)MyBag.GetItem(i);
   j = eh->EventHandler(msg);
   if(j && ActiveItem != i)
    {
     SendPasiveCommand(ActiveItem);
     ActiveItem = i;
     SendActiveCommand(ActiveItem);
    }
   if(j)
    {
     SendMSGCmd(SendCmd);
     break;
    }
  }

 return j;
}

int GMenu :: Command(MSG &msg)
{
 switch(msg.Cmd)
  {
   case ITEM_ACTIVE:
        return 1;
  }

return 0;
}

void GMenu :: SetMenuSize(int dx,int dy)
{
 DX = dx;
 DY = dy;
}
