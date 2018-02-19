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
#include "point.hpp"
#include "calculat.hpp"

#define BUTTON_LINE      142
#define SHOW_ITEM_NUMBER 9
#define INFO_PLACE       BUTTON_LINE + 68
#define CAL_SIZE_DY      INFO_PLACE + SHOW_ITEM_NUMBER * 20 + 2

void Heap(char far *record);

#ifndef _CALCULATE
#define _CALCULATE

#include "calfst.hpp"

class Calculate : public CalFirst
{
public:
 ~Calculate();
  Calculate();

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual int EventHandler(MSG &msg);
  virtual void DisplayInfo(int x,int y,int dx);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
  virtual int Keyboard(MSG &msg);        // klaviaturos
private:
  void FillMenu(int i);
  void SetStructViewPort(void);
};
#endif

Calculate :: Calculate()
{
 int SizeDX;

 SizeDX = TextMaxLen(10021,10022,10023,10024,10025,10030,10031,10032,0);
 if(SizeDX < 20)
  SizeDX = 20;
 SizeDX ++;

 SizeDX *= SmallFontTable[1];

 SetDXDY(SizeDX + 5,CAL_SIZE_DY);
 FillMenu(0);
}

Calculate :: ~Calculate()
{
}

#pragma argsused
void Calculate :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 Bar(x,y,dx,INFO_PLACE,GRAY_4);
 MyGroup.SetXY(x,y + 23);
 MyGroup.Show();
 DisplayInfo(x,y,dx);
}

void Calculate :: DisplayInfo(int x,int y,int dx)
{
 int i;
 int flag;
 char str[100];
 CalStruct CS;


 flag = 0;
 if(CStruct == 0L)
  CStruct = &CS;
 else
  flag = 1;

 SetColor(_WHITE);
 SetGroundColor(GRAY_4);
 Bar(x,y,dx - 1,22,GRAY_4);
 Bar(x,y + INFO_PLACE,dx,SHOW_ITEM_NUMBER * 20 + 2,GRAY_4);
 Rectangle(x,y,dx - 1,22);

 sprintf(str,"%-3.3s",GetText(10026));
 for(i = 0;i < SHOW_ITEM_NUMBER;i ++)
  OutText(x + dx - 2 - 38,y + INFO_PLACE + i * 20 + 2,str);

 OutText(x + dx - 2 - 10,y + INFO_PLACE + (SHOW_ITEM_NUMBER - 3) * 20 + 2,"3");
 OutText(x + dx - 2 - 10,y + INFO_PLACE + (SHOW_ITEM_NUMBER - 2) * 20 + 2,"3");
 OutText(x + dx - 2 - 10,y + INFO_PLACE + (SHOW_ITEM_NUMBER - 1) * 20 + 2,"2");

 for(i = 0;i < 6;i ++)
  {
   sprintf(str,"D%i  %-3.1f",i + 1,CStruct->D[i]);
   OutText(x + 3,y + INFO_PLACE + i * 20 + 2,str);
  }
 sprintf(str,"V1  %-3.1f",CStruct->V[0]);
 OutText(x + 3,y + INFO_PLACE + 6 * 20 + 2,str);
 sprintf(str,"V2  %-3.1f",CStruct->V[1]);
 OutText(x + 3,y + INFO_PLACE + 7 * 20 + 2,str);
 sprintf(str,"S   %-5.1f",CStruct->S);
 OutText(x + 3,y + INFO_PLACE + 8 * 20 + 2,str);

 if(CStruct->AtstumuSantykis[0])
  {
   if(CStruct->AtstumuSantykis[1])
    {
     if(CStruct->D[CStruct->AtstumuSantykis[1] - 1])
      sprintf(str,"D%i/D%i=%3.2f",CStruct->AtstumuSantykis[0],CStruct->AtstumuSantykis[1],
                                  CStruct->D[CStruct->AtstumuSantykis[0] - 1] /
                                  CStruct->D[CStruct->AtstumuSantykis[1] - 1]);
     else
      sprintf(str,"D%i/D%i=0.0",CStruct->AtstumuSantykis[0],CStruct->AtstumuSantykis[1]);
    }
   else
    sprintf(str,"D%i",CStruct->AtstumuSantykis[0]);
   OutText(x + 4,y + 4,str);
  }

 if(CStruct->TuriuSantykis[0])
  {
   if(CStruct->TuriuSantykis[1])
    {
     if(CStruct->D[CStruct->TuriuSantykis[1] - 1])
      sprintf(str,"V%i/V%i=%3.2f",CStruct->TuriuSantykis[0],CStruct->TuriuSantykis[1],
                                  CStruct->V[CStruct->TuriuSantykis[0] - 1] /
                                  CStruct->V[CStruct->TuriuSantykis[1] - 1]);
     else
      sprintf(str,"V%i/V%i=0.0",CStruct->TuriuSantykis[0],CStruct->TuriuSantykis[1]);
    }
   else
    sprintf(str,"V%i",CStruct->TuriuSantykis[0]);
   OutText(x + 4,y + 4,str);
  }

 if(VInit)
  {
   if(CStruct->FillV == 0)
    switch(VInit)
     {
      case 1:
           sprintf(str,"PI/6*D%i",CStruct->FillV1[0]);
           break;
      case 2:
           sprintf(str,"PI/6*D%i*D%i",CStruct->FillV1[0],CStruct->FillV1[1]);
           break;
      case 3:
           sprintf(str,"PI/6*D%i*D%i*D%i=%3.2f",CStruct->FillV1[0],
                                                CStruct->FillV1[1],
                                                CStruct->FillV1[2],
                                                CStruct->V[0]);
           break;
     }
    else
    switch(VInit)
     {
      case 1:
           sprintf(str,"PI/6*D%i",CStruct->FillV2[0]);
           break;
      case 2:
           sprintf(str,"PI/6*D%i*D%i",CStruct->FillV2[0],CStruct->FillV2[1]);
           break;
      case 3:
           sprintf(str,"PI/6*D%i*D%i*D%i=%3.2f",CStruct->FillV2[0],
                                                CStruct->FillV2[1],
                                                CStruct->FillV2[2],
                                                CStruct->V[1]);
           break;
     }

   OutText(x + 4,y + 4,str);
  }

 if(flag == 0)
  CStruct = 0L;

 for(i = 0;i <= SHOW_ITEM_NUMBER;i ++)
  HLine(x,y + INFO_PLACE + i * 20,dx - 2);

 VLine(x,              y + INFO_PLACE,SHOW_ITEM_NUMBER * 20);
 VLine(x + 20,         y + INFO_PLACE,SHOW_ITEM_NUMBER * 20);
 VLine(x + dx - 2,     y + INFO_PLACE,SHOW_ITEM_NUMBER * 20);
 VLine(x + dx - 2 - 40,y + INFO_PLACE,SHOW_ITEM_NUMBER * 20);
}

ClassType Calculate :: isA()
{
 return _Calculate;
}

int Calculate :: EventHandler(MSG &msg)
{
 MyGroup.EventHandler(msg);

 return GWindow :: EventHandler(msg);
}


int Calculate :: Mouse(MSG &msg)
{
 if(Init == 2 && SInit == 0)
  {
   if(msg.Mouse & RBUTTON)
    Abort();
   return GWindow :: Mouse(msg);
  }
 else
  {
   if(SInit)
    {
     if(msg.Mouse & LBUTTON)
      if(SInit == 1)
       {
        BeginMark(msg.X,msg.Y);
        SInit = 2;
       }
     if(msg.Mouse & RBUTTON)
      {
       EndMark(msg.X,msg.Y);
       SInit = 0;
       return 1;
      }
     if((msg.Mouse & MOVE) && msg.ButtonStatus)
      MoveMark(msg.X,msg.Y);
    }
   else
    {
     if(msg.Mouse & LBUTTON)
      if(Init == 0)
       BeginMove(msg.X,msg.Y);
     if(msg.Mouse & LBUTTON_UP || msg.Mouse & RBUTTON)
      EndMove(msg.X,msg.Y);
     if((msg.Mouse & MOVE) && msg.ButtonStatus)
      if(Init == 1)
       MoveTo(msg.X,msg.Y);
    }
  }

return 1;
}

int Calculate :: Command(MSG &msg)
{
 int i;

 i = DCommand(msg);
 switch(msg.Cmd)
  {
   case PLOTAS:
        if(!CStruct)
         return 1;
        SInit = 1;
        SetMouseArea(CStruct->ViewX,CStruct->ViewY,CStruct->ViewDX,CStruct->ViewDY);
        SetMouseShape(SMALL_KREST);
        return 1;
   case PLOTAS_FILL:
        DisplayBorder(NonReg.BorderHandler,NonReg.BorderSize,SP1.x,SP1.y,_RED);
        WndDraw();
//        DisplayInfo(ViewX,ViewY,ViewDX);
        return 1;
   case D_SANTYKIS:
        DInit = 1;
        return 1;
   case V_SANTYKIS:
        DInit = 2;
        return 1;
   case TURIS:
        DInit = 3;
        VInit = 0;
        return 1;
   case KOORD_ASYS:
        if(CStruct)
         {
          SetStructViewPort();
          Register(new Grid(X,Y,CStruct,KOORDINATES));
         }
        return 1;
   case GRID:
        if(CStruct)
         {
          SetStructViewPort();
          Register(new Grid(X,Y,CStruct,TINKLELIS));
         }
        return 1;
   case GRID_END:
        CStruct = (CalStruct *)msg.Param1;
        FillMenu(1);
        WndDraw();
        return 1;
   case KALIBRAVIMAS:
        if(CStruct)
         Register(new Kalibravimas(X,Y,CStruct));
        return 1;
   case KALIBRAVIMAS_OK:
        CStruct = (CalStruct *)msg.Param1;
        if(CStruct->Mastelis != 0.)
         FillMenu(1);
        else
         FillMenu(0);
        WndDraw();
        return 1;
   case KALIBRAVIMAS_CANCEL:
        CStruct = (CalStruct *)msg.Param1;
        FillMenu(0);
        return 1;
   case FILL_GROUP:
        MyGroup.Show();
        return 1;
   case ITEM_ACTIVE:
//        WndDraw();
//        MyGroup.Show();
        break;
   case ITEM_PASIVE:
        CStruct = 0L;
        DisplayInfo(ViewX,ViewY,ViewDX);
        FillMenu(0);
        MyGroup.Show();
        break;
   case KALKUL_STRUCT:
        CStruct = (CalStruct *)msg.Param1;
        if(CStruct->Mastelis != 0.)
         FillMenu(1);
        else
         FillMenu(0);
        SendMSGCmd(FILL_GROUP,RegisterNumber);
        return 1;
  }
 if(GWindow :: Command(msg))
  return 1;
return i;
}

int Calculate :: Keyboard(MSG &msg)
{
 switch(msg.Key)
  {
   case F1:
        RunHelp(7);
        return 1;
   case ESC:
        Abort(); 
        break;
  }
 return GWindow :: Keyboard(msg);
}

void Calculate :: FillMenu(int i)
{
 int SizeDX = GetDX() - 15;
 int Shift;

 Shift = SizeDX / 4;
 MyGroup.NewGroup();
 switch(i)
  {
   case 0:
        MyGroup.AddItem(new GButton(0,0,SizeDX,20,GetText(10024),KALIBRAVIMAS));
        MyGroup.AddItem(new GButton(0,20,SizeDX,20,GetText(10022),V_SANTYKIS,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        MyGroup.AddItem(new GButton(0,40,SizeDX,20,GetText(10023),D_SANTYKIS,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        MyGroup.AddItem(new GButton(0,60,SizeDX,20,GetText(10021),TURIS,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        MyGroup.AddItem(new GButton(0,80,SizeDX,20,GetText(10030),GRID,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        MyGroup.AddItem(new GButton(0,100,SizeDX,20,GetText(10031),KOORD_ASYS,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        MyGroup.AddItem(new GButton(0,120,SizeDX,20,GetText(10032),PLOTAS,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));

        MyGroup.AddItem(new GButton(Shift * 0,BUTTON_LINE +  0,Shift - 1,20,"D~1",0,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        MyGroup.AddItem(new GButton(Shift * 1,BUTTON_LINE +  0,Shift - 1,20,"D~2",0,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        MyGroup.AddItem(new GButton(Shift * 2,BUTTON_LINE +  0,Shift - 1,20,"D~3",0,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        MyGroup.AddItem(new GButton(Shift * 3,BUTTON_LINE +  0,Shift - 0,20,"D~4",0,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        MyGroup.AddItem(new GButton(Shift * 0,BUTTON_LINE + 20,Shift - 1,20,"D~5",0,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        MyGroup.AddItem(new GButton(Shift * 1,BUTTON_LINE + 20,Shift - 1,20,"D~6",0,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        MyGroup.AddItem(new GButton(Shift * 2,BUTTON_LINE + 20,Shift - 1,20,"V1",0,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        MyGroup.AddItem(new GButton(Shift * 3,BUTTON_LINE + 20,Shift - 0,20,"V2",0,0,0xffff,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
        break;
   case 1:
        MyGroup.AddItem(new GButton(0,0,SizeDX,20,GetText(10024),KALIBRAVIMAS));
        MyGroup.AddItem(new GButton(0,20,SizeDX,20,GetText(10022),V_SANTYKIS));
        MyGroup.AddItem(new GButton(0,40,SizeDX,20,GetText(10023),D_SANTYKIS));
        MyGroup.AddItem(new GButton(0,60,SizeDX,20,GetText(10021),TURIS));
        MyGroup.AddItem(new GButton(0,80,SizeDX,20,GetText(10030),GRID));
        MyGroup.AddItem(new GButton(0,100,SizeDX,20,GetText(10031),KOORD_ASYS));
        MyGroup.AddItem(new GButton(0,120,SizeDX,20,GetText(10032),PLOTAS));

        MyGroup.AddItem(new GButton(Shift * 0,BUTTON_LINE +  0,Shift - 1,20,"D~1",D1));
        MyGroup.AddItem(new GButton(Shift * 1,BUTTON_LINE +  0,Shift - 1,20,"D~2",D2));
        MyGroup.AddItem(new GButton(Shift * 2,BUTTON_LINE +  0,Shift - 1,20,"D~3",D3));
        MyGroup.AddItem(new GButton(Shift * 3,BUTTON_LINE +  0,Shift - 0,20,"D~4",D4));
        MyGroup.AddItem(new GButton(Shift * 0,BUTTON_LINE + 20,Shift - 1,20,"D~5",D5));
        MyGroup.AddItem(new GButton(Shift * 1,BUTTON_LINE + 20,Shift - 1,20,"D~6",D6));
        MyGroup.AddItem(new GButton(Shift * 2,BUTTON_LINE + 20,Shift - 1,20,"V1",V1));
        MyGroup.AddItem(new GButton(Shift * 3,BUTTON_LINE + 20,Shift - 0,20,"V2",V2));
        break;
  }
}

void Calculate :: SetStructViewPort(void)
{
 if(CStruct)
  {
   CStruct->CViewX = ViewX;
   CStruct->CViewY = ViewY;
   CStruct->CViewDX = ViewDX;
   CStruct->CViewDY = ViewDY;
   CStruct->CalculateRegisterNumber = RegisterNumber;
  }
}
