#include <math.h>
#include <stdio.h>
#include "keys.h"
#include "proto.hpp"
#include "gdefine.hpp"
#include "vcmd.hpp"
#include "graph.hpp"
#include "gettext.hpp"
#include "kalibrav.hpp"
#include "mouse.hpp"
#include "grid.hpp"
#include "bpoint.hpp"
#include "point.hpp"
#include "calfst.hpp"

void Heap(char far *record);
extern int AllMouseEvent;
int Atstumas(Point &p1,Point &p2);
int CalFirstWarning = 0;

#ifndef _CAL_FIRST
#define _CAL_FIRST

#include "gwindow.hpp"
#include "calstr.hpp"
#include "point.hpp"
#include "nregular.hpp"

class CalFirst : public GWindow
{
protected:
 int SInit;
 int Init;
 int DInit;
 int VInit;
 int MouseEvent;
 int DLineNr;
 Point P1;
 Point P2;
 Point SP1; // ploto kvadratas
 Point SP2;
 GMenu MyGroup;
 CalStruct *CStruct;
 Bag MyBag;
 NonRegular NonReg;
public:
 ~CalFirst();
  CalFirst();

  virtual void DisplayInfo(int x,int y,int dx);

protected:
  void DLine(int nr);
  void BeginMove(int x,int y);  // DLine
  void MoveTo(int x,int y);     // DLine
  void EndMove(int x,int y);    // DLine
  void ShowLine(int nr,Point &p1,Point &p2);
  void DCall(int nr);
  int DMSGCall(MSG &msg);
  void DPasive(int nr);
  void DAtstumas(int nr,Point &p1,Point &p2);
  int DCommand(MSG &msg);
  int DAtstumuSantykis(MSG &msg);
  int DAtstumuSantykis(int nr);
  int VTuriuSantykis(MSG &msg);
  int VTuriuSantykis(int nr);
  int FillV(MSG &msg);
  int FillV(int nr);
  void Abort(void);

  virtual void BeginMark(int x,int y);
  virtual void EndMark(int x,int y);
  virtual void MoveMark(int x,int y);
};
#endif

CalFirst :: CalFirst()
          :  GWindow(0,50,0,0,GetText(10025),WND_GRAPH | WND_CLOSE_BUTTON),
             MyGroup(0,0,MENU_FRAME),
             MyBag(DELETE)
{
 SInit = 0;
 DInit = 0;
 VInit = 0;
 Init = 2;
 CStruct = 0L;
 DLineNr = 0;
 CalFirstWarning ++;
}

CalFirst :: ~CalFirst()
{
 CalFirstWarning --;
}

#pragma argsused
void CalFirst :: DisplayInfo(int x,int y,int dx)
{
}

void CalFirst :: BeginMove(int x,int y)
{
 P2.x = x;
 P2.y = y;
 P1 = P2;

 SetWriteMode(XOR_PUT);
 Line(P1.x,P1.y,P2.x,P2.y,_RED);
 SetWriteMode(COPY_PUT);

 Init = 1;
}

void CalFirst :: MoveTo(int x,int y)
{
 SetWriteMode(XOR_PUT);
 Line(P1.x,P1.y,P2.x,P2.y,_RED);

 P2.x = x;
 P2.y = y;

 Line(P1.x,P1.y,P2.x,P2.y,_RED);
 SetWriteMode(COPY_PUT);
}

void CalFirst :: EndMove(int x,int y)
{
 MoveTo(x,y);

 SetWriteMode(XOR_PUT);
 Line(P1.x,P1.y,P2.x,P2.y,_RED);
 SetWriteMode(COPY_PUT);

 Init = 2;

 SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
 AllMouseEvent = MouseEvent;
 SetMouseShape(ARROW);

 switch(DLineNr)
  {
   case 1:
        DAtstumas(1,P1,P2);
        break;
   case 2:
        DAtstumas(2,P1,P2);
        break;
   case 3:
        DAtstumas(3,P1,P2);
        break;
   case 4:
        DAtstumas(4,P1,P2);
        break;
   case 5:
        DAtstumas(5,P1,P2);
        break;
   case 6:
        DAtstumas(6,P1,P2);
        break;
  }
 if(DLineNr > 0 && DLineNr < 7)
  {
   ShowLine(DLineNr,P1,P2);
   DisplayInfo(ViewX,ViewY,ViewDX);
  }
}

void CalFirst :: DLine(int nr)
{
 DLineNr = nr;

 SetMouseArea(CStruct->ViewX,CStruct->ViewY,CStruct->ViewDX,CStruct->ViewDY);
 MouseEvent = AllMouseEvent;
 AllMouseEvent = 1;
 Init = 0;
}

void CalFirst :: ShowLine(int nr,Point &p1,Point &p2)
{
 char str[10];

 SetWriteMode(XOR_PUT);
 SetColor(_RED);
 Line(p1.x,p1.y,p2.x,p2.y);
 Circle(p1.x,p1.y,2);
 Circle(p2.x,p2.y,2);
 sprintf(str,"%1.1i",nr);
 OutStr(p1.x,p1.y,str);
 SetWriteMode(COPY_PUT);
}

void CalFirst :: DCall(int nr)
{
 DLine(nr);
 if(CStruct->SD[nr - 1])
  {
   CStruct->SD[nr - 1] = 0;
   ShowLine(nr,CStruct->P1D[nr - 1],CStruct->P2D[nr - 1]);
  }
 SetMouseShape(SMALL_KREST);
}

void CalFirst :: DPasive(int nr)
{
 if(CStruct->SD[nr - 1])
  ShowLine(nr,CStruct->P1D[nr - 1],CStruct->P2D[nr - 1]);
}

void CalFirst :: DAtstumas(int nr,Point &p1,Point &p2)
{
 CStruct->SD[nr - 1] = 1;
 CStruct->P1D[nr - 1] = p1;
 CStruct->P2D[nr - 1] = p2;
 CStruct->D[nr - 1] = Atstumas(p1,p2) * CStruct->Mastelis;
}

int CalFirst :: DCommand(MSG &msg)
{
 int i = 0;
 int j;

 if(CStruct == 0L || Init != 2)
  return 0;

 switch(DInit)
  {
   case 0:
        i = DMSGCall(msg);
        break;
   case 1:
        i = DAtstumuSantykis(msg);
        break;
   case 2:
        i = VTuriuSantykis(msg);
        break;
   case 3:
        i = FillV(msg);
        break;
  }

 switch(msg.Cmd)
  {
   case ITEM_PASIVE:
        for(j = 1;j < 7;j ++)
         DPasive(j);
        CStruct->Init();
        break;
  }
return i;
}

int CalFirst :: DMSGCall(MSG &msg)
{
 switch(msg.Cmd)
  {
   case D1:
        DCall(1);
        return 1;
   case D2:
        DCall(2);
        return 1;
   case D3:
        DCall(3);
        return 1;
   case D4:
        DCall(4);
        return 1;
   case D5:
        DCall(5);
        return 1;
   case D6:
        DCall(6);
        return 1;
  }

return 0;
}

int CalFirst :: DAtstumuSantykis(MSG &msg)
{
 switch(msg.Cmd)
  {
   case D1:
        DAtstumuSantykis(1);
        return 1;
   case D2:
        DAtstumuSantykis(2);
        return 1;
   case D3:
        DAtstumuSantykis(3);
        return 1;
   case D4:
        DAtstumuSantykis(4);
        return 1;
   case D5:
        DAtstumuSantykis(5);
        return 1;
   case D6:
        DAtstumuSantykis(6);
        return 1;
  }

return 0;
}

int CalFirst :: DAtstumuSantykis(int nr)
{
 if(CStruct->AtstumuSantykis[0] && CStruct->AtstumuSantykis[1])
  return 0;

 if(CStruct->AtstumuSantykis[0])
  {
   CStruct->AtstumuSantykis[1] = nr;
   DisplayInfo(ViewX,ViewY,ViewDX);
   DInit = 0;
   CStruct->AtstumuSantykis[0] = 0;
   CStruct->AtstumuSantykis[1] = 0;
  }
 else
  {
   CStruct->AtstumuSantykis[0] = nr;
   DisplayInfo(ViewX,ViewY,ViewDX);
  }
return 0;
}

int CalFirst :: VTuriuSantykis(MSG &msg)
{
 switch(msg.Cmd)
  {
   case V1:
        VTuriuSantykis(1);
        return 1;
   case V2:
        VTuriuSantykis(2);
        return 1;
  }
return 0;
}

int CalFirst :: VTuriuSantykis(int nr)
{
 if(CStruct->TuriuSantykis[0] && CStruct->TuriuSantykis[1])
  return 0;

 if(CStruct->TuriuSantykis[0])
  {
   CStruct->TuriuSantykis[1] = nr;
   DisplayInfo(ViewX,ViewY,ViewDX);
   DInit = 0;
   CStruct->TuriuSantykis[0] = 0;
   CStruct->TuriuSantykis[1] = 0;
  }
 else
  {
   CStruct->TuriuSantykis[0] = nr;
   DisplayInfo(ViewX,ViewY,ViewDX);
  }
return 0;
}

int CalFirst :: FillV(MSG &msg)
{
 switch(msg.Cmd)
  {
   case D1:
        FillV(1);
        return 1;
   case D2:
        FillV(2);
        return 1;
   case D3:
        FillV(3);
        return 1;
   case D4:
        FillV(4);
        return 1;
   case D5:
        FillV(5);
        return 1;
   case D6:
        FillV(6);
        return 1;
  }
return 0;
}

int CalFirst :: FillV(int nr)
{

 if(CStruct->FillV == 0)
  CStruct->FillV1[VInit] = nr;
 else
  CStruct->FillV2[VInit] = nr;

 VInit ++;
 if(VInit == 3)
  {
   if(CStruct->FillV == 0)
    CStruct->V[0] = M_PI / 6 * CStruct->D[CStruct->FillV1[0] - 1]
                             * CStruct->D[CStruct->FillV1[1] - 1]
                             * CStruct->D[CStruct->FillV1[2] - 1];
   else
    CStruct->V[1] = M_PI / 6 * CStruct->D[CStruct->FillV2[0] - 1]
                             * CStruct->D[CStruct->FillV2[1] - 1]
                             * CStruct->D[CStruct->FillV2[2] - 1];
   DisplayInfo(ViewX,ViewY,ViewDX);
   CStruct->FillV ++;
   if(CStruct->FillV == 2)
    CStruct->FillV = 0;
   DInit = 0;
   VInit = 0;
  }
 else
  DisplayInfo(ViewX,ViewY,ViewDX);

return 0;
}

void CalFirst :: Abort(void)
{
 if(DInit || VInit)
  {
   CStruct->TuriuSantykis[0] = 0;
   CStruct->TuriuSantykis[1] = 0;
   CStruct->AtstumuSantykis[0] = 0;
   CStruct->AtstumuSantykis[1] = 0;
   DisplayInfo(ViewX,ViewY,ViewDX);
   DInit = 0;
   VInit = 0;
  }
}

void CalFirst :: BeginMark(int x,int y)
{
 P2.x = x;
 P2.y = y;
 P1 = P2;
 SP1 = P2;
 SP2.x = 0;
 SP2.y = 0;
 while(MyBag.GetBagSize())
  MyBag - 0;
 MyBag + new BPoint(x,y);
}

#pragma argsused
void CalFirst :: EndMark(int x,int y)
{
 int i;
 GPoint *gp;

// MoveMark(x,y);
 gp = (GPoint *)MyBag.GetItem(0);
 Line(P1.x,P1.y,gp->GetX(),gp->GetY(),_WHITE);
 SetMouseArea(0,0,GraphMaxX + 1,GraphMaxY + 1);
 SetMouseShape(ARROW);
 for(i = MyBag.GetBagSize() - 1;i >= 0;i --)
  {
   gp = (GPoint *)MyBag.GetItem(i);
   gp->SetX(gp->GetX() - SP1.x);
   gp->SetY(gp->GetY() - SP1.y);
  }

 SP2.x -= SP1.x - 1;       // dx
 SP2.y -= SP1.y - 1;       // dy
 NonReg.Delete();
 NonReg.FillMemory(SP2.x,SP2.y,&MyBag);              // cia kvadrato koord. saugomos SPx
 for(i = MyBag.GetBagSize() - 1;i >= 0;i --)
  MyBag - 0;
 NonReg.CopyBorderToMM();
 CStruct->S = GetAreaNotRegular(NonReg.FillingHandler,NonReg.FillingSize) * (CStruct->Mastelis * CStruct->Mastelis);

 SendMSGCmd(PLOTAS_FILL,RegisterNumber);
}

void CalFirst :: MoveMark(int x,int y)
{
 if(MyBag.GetBagSize() > 16000)
  return;
 P2.x = x;
 P2.y = y;
 Line(P1.x,P1.y,P2.x,P2.y,_WHITE);
 P1 = P2;
 MyBag + new BPoint(x,y);

 if(SP1.x > x)                  // surandame fragmento dydi
  SP1.x = x;
 if(SP2.x < x)
  SP2.x = x;
 if(SP1.y > y)
  SP1.y = y;
 if(SP2.y < y)
  SP2.y = y;
}
