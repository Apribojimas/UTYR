#include <string.h>
#include "proto.hpp"
#include "keys.h"
#include "define.hpp"
#include "graph.hpp"
#include "grbutton.hpp"
#include "grollerdata.hpp"
#include "groller.hpp"

#ifndef _GROLLER
#define _GROLLER

#include "gdefine.hpp"
#include "GMenu.hpp"
#include "GScroll.hpp"
#include "Bag.hpp"

class GRoller : public GMenu
{
 int Justify;
 int WidthText;
 int HeightText;
 int SendCmd;
 int SendAdr;
 int ShowActiveItem;
 int isFillMenu;
 int MemScrollPos;
 unsigned int isSetActiveItem;
 GScroll Scroll;
 Bag MyBag;
public:
 ~GRoller();
  GRoller(int x = 0,int y = 0,int widthText = 0,int heightText = 0,int cmd = 0,int adr = 0,int justify = JUSTIFY_LEFT);

  char *GetItem(void);
  Object * GetObject(int i);
  Bag *ReturnBagPtr(void);
  virtual void AddObject(Object *Obj);
  virtual void AddString(char * String,int registernumber = 0);
  virtual void DropItem(int i);
  virtual void SetActiveItem(int i);
  virtual void SetActiveItem(char *str);
  virtual void SetActiveItem(void);
  virtual int  GetActiveItem(void);
  virtual void Show(void);
  virtual int  EventHandler(MSG &msg);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Keyboard(MSG &msg);       // klaviaturos
  virtual int Mouse(MSG &msg);
  virtual int Command(MSG &msg);
private:
  void FillMenu(void);
  int PrivateSetActiveItem(int i);
};
#endif

GRoller :: GRoller(int x,int y,int widthText,int heightText,int cmd,int adr,int justify)
        :  GMenu(x,y),
           Scroll(0,0,heightText * SmallFontTable[0] + 4,VERTICAL),
           MyBag(DELETE)
{
 WidthText = widthText;
 HeightText = heightText;
 SendCmd = cmd;
 SendAdr = adr;
 Justify = justify;
 isFillMenu = 0;
 MemScrollPos = 0;
 ShowActiveItem = 0;
 isSetActiveItem = 0xffff;
}

GRoller :: ~GRoller()
{
}

void GRoller :: Show(void)
{
 FillMenu();
 SetMenuSize(WidthText * SmallFontTable[1] + 4,HeightText * SmallFontTable[0] + 4);
 GMenu :: Show();
 Scroll.SetXY(X + WidthText * SmallFontTable[1] + 4,Y);
 Scroll.Show();
}

void GRoller :: AddString(char *String,int registernumber)
{
 Object *Obj;

 Obj = (Object *)(new GRollerData(String));
 if(Obj == 0L)
  return;

 Obj->RegisterNumber = registernumber;
 Scroll.SetMaxPos(MyBag.GetBagSize());
 MyBag + Obj;
 isFillMenu = 1;
}

ClassType GRoller :: isA()
{
 return _GRoller;
}

int GRoller :: EventHandler(MSG &msg)
{
 int i;

 i = GEventHandler :: EventHandler(msg);
 if(Scroll.EventHandler(msg))
  {
   i ++;
   if(MemScrollPos - Scroll.GetPos() != 0)
    {
     if(PrivateSetActiveItem(Scroll.GetPos() - MemScrollPos))
      Show();
     MemScrollPos = Scroll.GetPos();
    }
  }

return i;
}

Object * GRoller :: GetObject(int i)
{
 return MyBag.GetItem(i);
}

void GRoller :: AddObject(Object *Obj)
{
 GEventHandler *ge;

 ge = (GEventHandler *)Obj;
 AddString(ge->GetWndName(),Obj->RegisterNumber);
 GMenu :: AddItem(Obj);
}

void GRoller :: FillMenu(void)
{
 int i;
 GRollerData *Data;

 if(isFillMenu == 0 && isSetActiveItem == 0xffff)
  return;

 NewMenu(Group :: GetActiveItem());
 for(i = 0;i + ShowActiveItem < MyBag.GetBagSize() && i < HeightText;i ++)
  {
   Data = (GRollerData *)MyBag.GetItem(i + ShowActiveItem);
   *this + new GRadioButton(0,i * 16,WidthText * SmallFontTable[1],SmallFontTable[0],Data->String,ROLLER_OK,0,0xffff,Justify);
  }

 if(isSetActiveItem != 0xffff)
  {
   int x,y,dx,dy;
   GetViewPort(x,y,dx,dy);
   SetViewPort(11110,11110,1,1);
   ShowActiveItem = 0;
   GMenu :: SetActiveItem (0);
   Scroll.SetPos(isSetActiveItem);
   MemScrollPos = Scroll.GetPos();
   PrivateSetActiveItem(isSetActiveItem);
   isSetActiveItem = 0xffff;
   FillMenu();
   SetViewPort(x,y,dx,dy);
  }

 isFillMenu = 0;
 isSetActiveItem = 0xffff;
}

char *GRoller :: GetItem(void)
{
 GRollerData *Data;
 if(MyBag.GetBagSize() == 0)
  return "";

 Data = (GRollerData *)MyBag.GetItem(GetActiveItem());
 return Data->String;
}

void GRoller :: DropItem(int i)
{
 isFillMenu = 1;
 MyBag - i;
 *(GMenu *)this - i;
 if(MyBag.GetBagSize())
  Scroll.SetMaxPos(MyBag.GetBagSize() - 1);
 else
  Scroll.SetMaxPos(0);
}

void GRoller :: SetActiveItem(int i)
{
 if(i < 0 || i >= MyBag.GetBagSize())
  return;

 isSetActiveItem = i;
}

void GRoller :: SetActiveItem(void)
{
 SetActiveItem(MyBag.GetBagSize() - 1);
}

void GRoller :: SetActiveItem(char *str)
{
 int i;
 GRollerData *Data;

 for(i = 0;i < MyBag.GetBagSize();i ++)
  {
   Data = (GRollerData *)MyBag.GetItem(i);
   if(strstr(str,Data->String))
    {
     SetActiveItem(i);
     break;
    }
  }
}

int GRoller :: PrivateSetActiveItem(int i)
{
 if(i > 0)
  {
   if(Group :: GetActiveItem() + i >= GetMenuSize())
    {
     if(ShowActiveItem + i + GetMenuSize() <= MyBag.GetBagSize())
      ShowActiveItem += i;
     else
      {
       if(ShowActiveItem == MyBag.GetBagSize() - GetMenuSize() &&
          Group :: GetActiveItem() == GetMenuSize() - 1)
        return 0;
       ShowActiveItem = MyBag.GetBagSize() - GetMenuSize();
       if(i - ShowActiveItem > GetMenuSize() - 1)
        GMenu :: SetActiveItem(GetMenuSize() - 1);
       else
        GMenu :: SetActiveItem(i - ShowActiveItem);
      }
     isFillMenu = 1;
     return 1;
    }
   else
    GMenu :: SetActiveItem(Group :: GetActiveItem() + i);
  }
 else
  {
   if(Group :: GetActiveItem() + i < 0)
    {
     if(ShowActiveItem + i >= 0)
      ShowActiveItem += i;
     else
      {
       if(ShowActiveItem == 0 && Group :: GetActiveItem() == 0)
        return 0;
       ShowActiveItem = 0;
       GMenu :: SetActiveItem(0);
      }
     isFillMenu = 1;
     return 1;
    }
   else
    GMenu :: SetActiveItem(Group :: GetActiveItem() + i);
  }

return 0;
}

int GRoller :: Keyboard(MSG &msg)
{
 int i;

 switch(msg.Key)
  {
   case LEFT:
   case UP:
        i = Scroll.GetPos();
        Scroll.SetPos(Scroll.GetPos() - 1);
        if(PrivateSetActiveItem(-1))
         Show();
        else
         if(i != Scroll.GetPos())
  	  Scroll.Show();
        return 1;
   case DOWN:
   case RIGHT:
        i = Scroll.GetPos();
        Scroll.SetPos(Scroll.GetPos() + 1);
        if(PrivateSetActiveItem(1))
         Show();
        else
         if(i != Scroll.GetPos())
  	  Scroll.Show();
        return 1;
   default:
        i = GMenu :: Keyboard(msg);
        break;
  }

return i;
}

int GRoller :: Command(MSG &msg)
{
 int i;

 i = GMenu :: Command(msg);
 switch(msg.Cmd)
  {
   case ROLLER_OK:
        SendMSGCmd(SendCmd,SendAdr);
        return 1;
   case ITEM_SHOW:
        Show();
        break;
   case ITEM_ACTIVE:
        Show();
        break;
  }
return i;
}

int GRoller :: Mouse(MSG &msg)
{
 if((msg.Mouse & RBUTTON) || (msg.Mouse & RBUTTON_UP))
  return 0;

 return GMenu :: Mouse(msg);
}

int GRoller :: GetActiveItem(void)
{
 return Group :: GetActiveItem() + ShowActiveItem;
}

Bag * GRoller :: ReturnBagPtr( void )
{
 return &(this->MyBag);
}
