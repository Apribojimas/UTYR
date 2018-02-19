#include <string.h>
#include "define.hpp"
#include "keys.h"
#include "group.hpp"

void Heap(char far *record);

#ifndef _GROUP
#define _GROUP

#include "geventha.hpp"
#include "bag.hpp"

class Group : public GEventHandler
{
protected:
 unsigned int ActiveItem;      // kuris 'button' aktyvus
 Bag ItemShift;  // cia saugom postumius lango atzvilgiu
 Bag MyBag;      // saugom item'us

public:
 ~Group();
  Group(int x = 0,int y = 0);

  virtual void Show(void);
  virtual int EventHandler(MSG &msg);

  Group & operator + (Object *Obj);
  virtual void AddItem(Object *Obj);
  void operator - (int i);
  void NewGroup(int activeitem = 0);

  Object * GetItem(int i);
  int GetGroupSize(void);
  virtual int  GetActiveItem(void);

  virtual void SetActiveItem(int i);
  virtual void SetItemShift(int i,int dx,int dy);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Keyboard(MSG &msg);        // apdorosime klavisus
  virtual int Command(MSG &msg);
  virtual void SendActiveCommand(int i,int kryptis = 0); // siunciam item'ams active komanda
                                                         // jei kryptis = 0 tai ieskom aktyviu item index ++ else index --
  virtual void SendPasiveCommand(int i); // siunciam item'ams pasive komanda
};
#endif

Group :: Group(int x,int y)
      :  GEventHandler(x,y),
         MyBag(DELETE),
         ItemShift(DELETE)
{
 ActiveItem = 0;
}

Group :: ~Group()
{
}

void Group :: Show(void)
{
 int i;
 GPoint *gp;
 GEventHandler *eh;

 for(i = 0;i < MyBag.GetBagSize();i ++)
  {
   eh = (GEventHandler *)MyBag.GetItem(i);
   gp = (GPoint *)ItemShift.GetItem(i);
   eh->SetXY(X + gp->GetX(),Y + gp->GetY());
   if(i != ActiveItem)
    eh->Show();
  }

 if(MyBag.GetBagSize())
  {
   SendActiveCommand(ActiveItem);
   eh = (GEventHandler *)MyBag.GetItem(ActiveItem);
   eh->Show();
  }
}

Group & Group :: operator + (Object *Obj)
{
 GRectangle *gr;

 MyBag + Obj;
 gr = (GRectangle *)Obj;
 ItemShift + (Object *)(new GPoint(gr->GetX(),gr->GetY()));
 return *this;
}

void Group :: operator - (int i)
{
 MyBag - i;
 ItemShift - i;
 if(ActiveItem >= MyBag.GetBagSize())
  {
   ActiveItem = MyBag.GetBagSize() - 1;
   if(MyBag.GetBagSize() == 0)
    ActiveItem = 0;
   SendActiveCommand(ActiveItem);
  }
}

void Group :: AddItem(Object *Obj)
{
 *this + Obj;
}

ClassType Group :: isA()
{
 return _Group;
}

int Group :: GetGroupSize(void)
{
 return MyBag.GetBagSize();
}

void Group :: SendActiveCommand(int i,int kryptis)
{
 MSG msg;
 GEventHandler *eh;

 memset(&msg,0,sizeof(MSG));
 msg.Type = COMMAND;
 msg.Cmd = ITEM_ACTIVE;
 eh = (GEventHandler *)MyBag.GetItem(i);
 if(eh != 0L)
  if(eh->EventHandler(msg))
   return;
 if(kryptis)
  {
   for(i = i - 1;i >= 0;i --)
    {
     eh = (GEventHandler *)MyBag.GetItem(i);
     if(eh != 0L)
      if(eh->EventHandler(msg))
       {
        ActiveItem = i;
        return;
       }
    }
   for(i = MyBag.GetBagSize() - 1;i >= 0 ;i --)
    {
     eh = (GEventHandler *)MyBag.GetItem(i);
     if(eh != 0L)
      if(eh->EventHandler(msg))
       {
        ActiveItem = i;
        return;
       }
    }
  }
 else
  {
   for(i = i + 1;i < MyBag.GetBagSize();i ++)
    {
     eh = (GEventHandler *)MyBag.GetItem(i);
     if(eh != 0L)
      if(eh->EventHandler(msg))
       {
        ActiveItem = i;
        return;
       }
    }
   for(i = 0;i < MyBag.GetBagSize();i ++)
    {
     eh = (GEventHandler *)MyBag.GetItem(i);
     if(eh != 0L)
      if(eh->EventHandler(msg))
       {
        ActiveItem = i;
        return;
       }
    }
  }
}

void Group :: SendPasiveCommand(int i)
{
 MSG msg;
 GEventHandler *eh;

 if(!MyBag.GetBagSize())
  return;
 memset(&msg,0,sizeof(MSG));
 msg.Type = COMMAND;
 msg.Cmd = ITEM_PASIVE;
 eh = (GEventHandler *)MyBag.GetItem(i);
 if(eh != 0L)
  eh->EventHandler(msg);
}

int Group :: GetActiveItem(void)
{
 return ActiveItem;
}

void Group :: SetActiveItem(int i)
{
 ActiveItem = i;
}

void Group :: NewGroup(int activeitem)
{
 ActiveItem = activeitem;
 while(MyBag.GetBagSize())
  MyBag - 0;
 while(ItemShift.GetBagSize())
  ItemShift - 0;
}

Object * Group :: GetItem(int i)
{
 return MyBag.GetItem(i);
}

int Group :: EventHandler(MSG &msg)
{
 if(MyBag.GetBagSize())
  return (GEventHandler :: EventHandler(msg));
return 0;
}

int Group :: Keyboard(MSG &msg)
{
 int i = 0;
 GEventHandler *eh;

 switch(msg.Key)
  {
    case TAB:
	 SendPasiveCommand(ActiveItem);
	 ActiveItem --;
	 if(ActiveItem >= MyBag.GetBagSize())
	  ActiveItem = MyBag.GetBagSize() - 1;
	 SendActiveCommand(ActiveItem,1);
	 i ++;
	 break;
    case SHIFT_TAB:
	 SendPasiveCommand(ActiveItem);
	 ActiveItem ++;
	 if(ActiveItem == MyBag.GetBagSize())
	  ActiveItem = 0;
	 SendActiveCommand(ActiveItem);
	 i ++;
	 break;
    default:
         eh = (GEventHandler *)MyBag.GetItem(ActiveItem);
         if(eh != 0L)
          if(eh->EventHandler(msg))
	   return 1;
 	 for(i = 0;i < MyBag.GetBagSize();i ++)
	  {
	   eh = (GEventHandler *)MyBag.GetItem(i);
	   if(eh->EventHandler(msg))
	    {
	     SendPasiveCommand(ActiveItem);
	     ActiveItem = i;
	     SendActiveCommand(ActiveItem);
	     return 1;
	    }
	  }
         return 0;
  }
return i;
}

int Group :: Mouse(MSG &msg)
{
 int i;
 int j;
 GEventHandler *eh;

 eh = (GEventHandler *)MyBag.GetItem(ActiveItem);
 if(eh != 0L)
  if(eh->EventHandler(msg))
   return 1;
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
    break;
  }

 return j;
}

int Group :: Command(MSG &msg)
{
 int i = 0;
 GEventHandler *eh;

 switch(msg.Cmd)
  {
   case ITEM_ACTIVE:
   case ITEM_PASIVE:
        return 0;
  }

 eh = (GEventHandler *)MyBag.GetItem(ActiveItem);
 if(eh != 0L)
  if(eh->EventHandler(msg))
   return 1;
 for(i = 0;i < MyBag.GetBagSize();i ++)
  {
   eh = (GEventHandler *)MyBag.GetItem(i);
   if(eh->EventHandler(msg))
    {
     SendPasiveCommand(ActiveItem);
     ActiveItem = i;
     SendActiveCommand(ActiveItem);
     return 1;
    }
  }
return 0;
}

void Group :: SetItemShift(int i,int dx,int dy)
{
 GPoint *gp;
 GEventHandler *eh;

 eh = (GEventHandler *)MyBag.GetItem(i);
 gp = (GPoint *)ItemShift.GetItem(i);
 if(gp == 0L || eh == 0L)
  return;
 eh->SetXY(X + dx,Y + dy);
 gp->SetX(dx);
 gp->SetY(dy);
}
