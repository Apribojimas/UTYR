#include <stdlib.h>
#include <alloc.h>
#include "mm.hpp"
#include "images.hpp"
#include "define.hpp"
#include "gdefine.hpp"
#include "graph.hpp"
#include "proto.hpp"
#include "graph.hpp"
#include "vcmd.hpp"
#include "mouse.hpp"
#include "bpoint.hpp"
#include "frag_f.hpp"

#ifndef _FRAGMENT_FRAGMENT
#define _FRAGMENT_FRAGMENT

#include "nregular.hpp"
#include "frag_r.hpp"
#include "bag.hpp"

class FragmentFragment : public FragmentRectangle
{
 int LineX;
 int LineY;
 Bag MyBag;
 NonRegular NonReg;
public:
 ~FragmentFragment();
  FragmentFragment(int FragNumber,int Index,int Sendadr = 0);

  virtual void Show();
  virtual void MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY);
  virtual void CalculateHistogram(long HistoHandler);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
protected:
  virtual void DisplayFragmentInfo(void);
  virtual void BeginMark(int x,int y);
  virtual void EndMark(int x,int y);
  virtual void MoveMark(int x,int y);
};
#endif

FragmentFragment :: FragmentFragment(int FragNumber,int Index,int Sendadr)
                 : FragmentRectangle(FragNumber,Index,Sendadr),
                   MyBag(DELETE)
{
 WndStatus = FRAGMENT_STATUS_FILL_BEGIN;
}

FragmentFragment :: ~FragmentFragment()
{
}

void FragmentFragment :: Show()
{
 if(!GraphBoundary(X,Y,DX,DY))
 {
  DisplayNotRegular(NonReg.FillingHandler,NonReg.FillingSize,MHandler,DX,DY,X,Y);
  DisplayFragmentInfo();
 }
}

void FragmentFragment :: DisplayFragmentInfo(void)
{
 char string[10];

 if(WndActive == WND_ACTIVE)
  SetColor(_RED);
 else
  SetColor(_BLUE);

 DisplayBorder(NonReg.BorderHandler,NonReg.BorderSize,X,Y,GlobalColor);

 itoa(FragmentNumber,string,10);
 OutStr(X + 1,Y + 1,string);
}

ClassType FragmentFragment :: isA()
{
 return _FragmentFragment;
}

void FragmentFragment :: BeginMark(int x,int y)
{
 LineX = x;
 LineY = y;
 X = x;
 Y = y;
 DX = 0;
 DY = 0;
 MyBag + new BPoint(x,y);
}

#pragma argsused
void FragmentFragment :: EndMark(int x,int y)
{
 int i;
 GPoint *gp;

// MoveMark(x,y);
 gp = (GPoint *)MyBag.GetItem(0);
 Line(LineX,LineY,gp->GetX(),gp->GetY(),_WHITE);
 SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
 SetMouseShape(ARROW);
 for(i = MyBag.GetBagSize() - 1;i >= 0;i --)
  {
   gp = (GPoint *)MyBag.GetItem(i);
   gp->SetX(gp->GetX() - X);
   gp->SetY(gp->GetY() - Y);
  }

 NonReg.FillMemory(DX,DY,&MyBag);
 for(i = MyBag.GetBagSize() - 1;i >= 0;i --)
  MyBag - 0;
 NonReg.CopyBorderToMM();

 SendMSGCmd(FRAGMENT_COPY,SendAdr,((long)X << 16) + Y,((long)DX << 16) + DY);
}

void FragmentFragment :: MoveMark(int x,int y)
{
 if(MyBag.GetBagSize() > 16000)
  return;
 Line(LineX,LineY,x,y,_WHITE);
 LineX = x;
 LineY = y;
 MyBag + new BPoint(x,y);
 if(X > x)                  // surandame fragmento dydi
  {
   DX += X - x;
   X = x;
  }
 if(X + DX - 1 < x)
  DX = x - X + 1;
 if(Y > y)
  {
   DY += Y - y;
   Y = y;
  }
 if(Y + DY - 1 < y)
  DY = y - Y + 1;
}

int FragmentFragment :: Mouse(MSG &msg)
{
 if(msg.Mouse & LBUTTON)
  {
   if(WndStatus == FRAGMENT_STATUS_FILL_BEGIN)
    {
     WndStatus = FRAGMENT_STATUS_FILL_MOVE;
     BeginMark(msg.X,msg.Y);
     return 1;
    }
   if(WndStatus == FRAGMENT_STATUS_FILL_MOVE)
    {
     MoveMark(msg.X,msg.Y);
     return 1;
    }
   if(isMyFrame(msg.X,msg.Y))
    return 1;
  }

 if(msg.Mouse & RBUTTON)
  if(WndStatus == FRAGMENT_STATUS_FILL_MOVE)
   {
    WndStatus = FRAGMENT_STATUS_FILL_END;
    EndMark(msg.X,msg.Y);
    return 1;
   }

 if(msg.Mouse & MOVE)
  if(WndStatus == FRAGMENT_STATUS_FILL_MOVE)
   {
    MoveMark(msg.X,msg.Y);
    return 1;
   }

return 0;
}
void FragmentFragment :: MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY)
{
 MCopyNotRegular( NonReg.FillingHandler,
                  NonReg.FillingSize,
                  MHandler,
                  DX,
                  Handler,
                  PictSizeDX,
                  PictSizeDY,
                  X-DisplayPlaceX,
                  Y-DisplayPlaceY
                  );

}
void FragmentFragment :: CalculateHistogram(long HistoHandler)
{

 HistoNotRegular( NonReg.FillingHandler,
                  NonReg.FillingSize,
                  MHandler,
                  DX,
                  HistoHandler);
}
