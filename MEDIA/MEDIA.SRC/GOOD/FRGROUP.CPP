#include <string.h>
#include "keys.h"
#include "define.hpp"
#include "graph.hpp"
#include "frgroup.hpp"


#ifndef _FRAGMENT_GROUP
#define _FRAGMENT_GROUP

#include "Group.hpp"

class FragmentGroup : public Group
{
public:
 ~FragmentGroup();
  FragmentGroup(int x = 0,int y = 0);

  virtual void AddItem(Object *Obj);
  FragmentGroup & operator + (Object *Obj);
  void SetDisplayPort(int x,int y,int dx,int dy);
  virtual void SetActiveItem(int i);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Keyboard(MSG &msg);        // apdorosime klavisus
  virtual int Command(MSG &msg);
  virtual void SendActiveCommand(int i,int kr = 0); // siunciam item'ams active komanda
  virtual void SendPasiveCommand(int i); // siunciam item'ams pasive komanda
};
#endif

FragmentGroup :: FragmentGroup(int x,int y)
              :  Group(x,y)
{
 SetDisplayPort(0,0,0,0);
}

FragmentGroup :: ~FragmentGroup()
{
}

void FragmentGroup :: SetDisplayPort(int x,int y,int dx,int dy)
{
 ViewX = x;
 ViewY = y;
 ViewDX = dx;
 ViewDY = dy;
}

void FragmentGroup :: AddItem(Object *Obj)
{
 *this + Obj;
}

FragmentGroup & FragmentGroup :: operator + (Object *Obj)
{
 Group :: AddItem(Obj);
 if(MyBag.GetBagSize() == 1)
  SendActiveCommand(0);
 return *this;
}

#pragma argsused
void FragmentGroup :: SendActiveCommand(int i,int kr)
{
 int tmpX;
 int tmpY;
 int tmpDX;
 int tmpDY;
 MSG msg;
 GEventHandler *eh;

 GetViewPort(tmpX,tmpY,tmpDX,tmpDY);
 GraphBoundary(ViewX,ViewY,ViewDX,ViewDY);
 SetViewPort(BoundaryX,BoundaryY,BoundaryDX,BoundaryDY);

 memset(&msg,0,sizeof(MSG));
 msg.Type = COMMAND;
 if(i)
  {
   msg.Cmd = ITEM_PASIVE;
   eh = (GEventHandler *)MyBag.GetItem(0);
   if(eh != 0L)
    eh->EventHandler(msg);
  }
 msg.Cmd = ITEM_ACTIVE;
 eh = (GEventHandler *)MyBag.GetItem(i);
 if(eh != 0L)
  eh->EventHandler(msg);
 MyBag.PutToHead(i);
 ItemShift.PutToHead(i);

 SetViewPort(tmpX,tmpY,tmpDX,tmpDY);
}

void FragmentGroup :: SendPasiveCommand(int i)
{
 i++;
}

void FragmentGroup :: SetActiveItem(int i)
{
 ActiveItem = 0;
 i++;
}

ClassType FragmentGroup :: isA()
{
 return _FragmentGroup;
}

int FragmentGroup :: Keyboard(MSG &msg)
{
 int i = 0;
 GEventHandler *eh;

 switch(msg.Key)
  {
    case SHIFT_TAB:
    case TAB:
         if(MyBag.GetBagSize() > 1)
  	  SendActiveCommand(MyBag.GetBagSize() - 1);
	 i ++;
	 break;
    default:
 	 for(i = 0;i < MyBag.GetBagSize();i ++)
	  {
	   eh = (GEventHandler *)MyBag.GetItem(i);
	   if(eh->EventHandler(msg))
	    {
             if(i)
  	      SendActiveCommand(i);
	     return 1;
	    }
	  }
         return 0;
  }
return i;
}

int FragmentGroup :: Mouse(MSG &msg)
{
 int i;
 GEventHandler *eh;

 for(i = 0;i < MyBag.GetBagSize();i ++)
  {
   eh = (GEventHandler *)MyBag.GetItem(i);
   if(eh->EventHandler(msg))
    {
     if(i)
      SendActiveCommand(i);
     return 1;
    }
  }

 return 0;
}

int FragmentGroup :: Command(MSG &msg)
{
 int i = 0;
 GEventHandler *eh;

 switch(msg.Cmd)
  {
   case ITEM_ACTIVE:
   case ITEM_PASIVE:
        return 0;
  }

 for(i = 0;i < MyBag.GetBagSize();i ++)
  {
   eh = (GEventHandler *)MyBag.GetItem(i);
   if(eh->EventHandler(msg))
    {
     if(i)
      SendActiveCommand(i);
     return 1;
    }
  }

return 0;
}
