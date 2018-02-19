#include <stdio.h>
#include <alloc.h>
#include <string.h>
#include "images.hpp"
#include "keys.h"
#include "define.hpp"
#include "struct.hpp"
#include "proto.hpp"
#include "vcmd.hpp"
#include "mousemer.hpp"
#include "gbutton.hpp"
#include "graph.hpp"
#include "gettext.hpp"
#include "fragment.hpp"
#include "taipne.hpp"
#include "mm.hpp"
#include "warning.hpp"
#include "skaner.hpp"
#include "vaizda12.hpp"
#include "desktopw.hpp"
#include "pacient.hpp"

#define MENU_LINE_COUNTER  7
#define DESKTOP_CHAR       18
#define DESKTOP_DX         DESKTOP_CHAR * 8 + 22
#define DESKTOP_MAX        DESKTOP_DX - 6

void Heap(char far *record);
extern int PaletteType;
extern int AboutPacient;

#ifndef _DESKTOP_WINDOW
#define _DESKTOP_WINDOW

#include "gwindow.hpp"
#include "groller.hpp"

class DeskTopWindow : public GWindow
{
 int CurrentGroup;
 Group MyGroup;
public:
 ~DeskTopWindow();
  DeskTopWindow();

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual int  EventHandler(MSG &msg);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);         // apdorosime komandas
private:
  void FillGroup(int i);                 // uzpildom menu
  void NewIcon(int registernumber,char *windowname);
  void DropIcon(int registernumber);
  GRoller * FindGRoller(void);
};
#endif

DeskTopWindow :: DeskTopWindow()
	      :	 GWindow(0,0,DESKTOP_DX,MENU_LINE_COUNTER * 20 + 130,GetText(3),WND_GRAPH),
                 MyGroup(0,0)
{
 MyGroup + new GMenu
         + new GRoller(0,MENU_LINE_COUNTER * 20 + 25,DESKTOP_CHAR,6,DROP_ICON);
 CurrentGroup = 0;

 FillGroup(0);
}

DeskTopWindow :: ~DeskTopWindow()
{
// SendMSGCmd(DESKTOP_EXIT);
}

ClassType DeskTopWindow :: isA()
{
 return _DeskTopWindow;
}

#pragma argsused
void DeskTopWindow :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{

 Bar(x,y,dx,dy,GRAY_7);

 SetColor(_BLACK);
 OutStr(x + dx / 2 - (strlen(GetText(12)) / 2) * SmallFontTable[1],y + dy - 120,GetText(12));

 MyGroup.SetXY(x + 1,y + 1);
 MyGroup.Show();
}

int DeskTopWindow :: EventHandler(MSG &msg)
{
 int i = 0;

 if(MyGroup.EventHandler(msg))
  i ++;

 if(GWindow :: EventHandler(msg))
  i ++;

return i;
}

int DeskTopWindow :: Command(MSG &msg)
{
 int i;
 Object *ob;
 GRoller *rl;

 i = GWindow :: Command(msg);
 switch(msg.Cmd)
  {
   case INVERSE_PALETTE:
        if(PaletteType)
         {
          SetGrayPalette(0);
          PaletteType = 0;
         }
        else
         {
          SetGrayInvertPalette(0);
          PaletteType = 1;
         }
        return 1;
   case VAIZDA_12:
        Register(new Vaizda12);
        return 1;
   case DESKTOP_END:
        Register(new Taip_Ne(DESKTOP_EXIT,0,0,13));
        return 1;
   case VAIZDO_APDOR:
	Register(new Fragment(PacientoPavarde,FileNameMask));
        return 1;
   case VM_640:
        SendMSGCmd(DESKTOP_WND_DRAW);
        SendMSGCmd(VIDEO_MODE_640);
        break;
   case VM_800:
        SendMSGCmd(DESKTOP_WND_DRAW);
        SendMSGCmd(VIDEO_MODE_800);
        break;
   case VM_1024:
        SendMSGCmd(DESKTOP_WND_DRAW);
        SendMSGCmd(VIDEO_MODE_1024);
        break;
   case DESKTOP_WND_DRAW:
        CurrentGroup = 0;
        FillGroup(CurrentGroup);
        WndDraw();
        return 1;
   case GRABER:
        Register(new Skaner);
	return 1;
   case VIDEO_MODE:
        CurrentGroup = 1;
        FillGroup(CurrentGroup);
        WndDraw();
        return 1;
   case DROP_ICON:
        rl = FindGRoller();
        if(rl == 0L)
         return 1;
        ob = rl->GetObject(rl->GetActiveItem());
        SendMSGCmd(ITEM_NORMAL,ob->RegisterNumber);
        DropIcon(ob->RegisterNumber);
        return 1;
   case ITEM_ICON:
        NewIcon((int)msg.Param1,(char *)msg.Param2);
        return 1;
   case PACIENTAS:
        Register(new Pacient);
	return 1;
  }
return i;
}

void DeskTopWindow :: FillGroup(int i)
{
 int j;
 Object *ob;
 GMenu *gm;
 int Max = DESKTOP_MAX;

 for(j = 0;j < MyGroup.GetGroupSize();j ++)
  {
   ob = MyGroup.GetItem(j);
   if(ob->isA() == _GMenu)
    break;
  }

 if(j == MyGroup.GetGroupSize())
  return;

 gm = (GMenu *)ob;
 gm->NewMenu();
 switch(i)
  {
   case 0:
//        Max = TextMaxLen(10002,10003,10004,10005,0);
//        Max = Max * SmallFontTable[1] + 3;
	gm->AddItem(new GButton(0,j=0,Max,20,GetText(10002),GRABER));
	gm->AddItem(new GButton(0,j+=20,Max,20,GetText(10005),VAIZDO_APDOR));
	gm->AddItem(new GButton(0,j+=20,Max,20,GetText(10039),VAIZDA_12));
	if((TestVideoMode(MODE_640)^1)+(TestVideoMode(MODE_800)^1)+(TestVideoMode(MODE_1024)^1) > 1)
	 gm->AddItem(new GButton(0,j+=20,Max,20,GetText(10003),VIDEO_MODE));
	else
	 gm->AddItem(new GButton(0,j+=20,Max,20,GetText(10003),VIDEO_MODE,0,0xFFFF,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
	gm->AddItem(new GButton(0,j+=20,Max,20,GetText(10059),INVERSE_PALETTE));
	if(AboutPacient)
	 gm->AddItem(new GButton(0,j+=20,Max,20,GetText(10500),PACIENTAS));
	else
	 gm->AddItem(new GButton(0,j+=20,Max,20,GetText(10500),PACIENTAS,0,0xFFFF,JUSTIFY_CENTER,BUTTON_UNAVAILABLE));
	gm->AddItem(new GButton(0,j+=20,Max,20,GetText(10004),DESKTOP_END));
	break;
   case 1:
//        Max = 130;
	if(!TestVideoMode(MODE_640))
	 gm->AddItem(new GButton(0,j=0  ,Max,20,GetText(10048),VM_640));
	if(!TestVideoMode(MODE_800))
	 gm->AddItem(new GButton(0,j+=20,Max,20,GetText(10049),VM_800));
	if(!TestVideoMode(MODE_1024))
	 gm->AddItem(new GButton(0,j+=20,Max,20,GetText(10050),VM_1024));
	break;
  }
}

void DeskTopWindow :: NewIcon(int registernumber,char *windowname)
{
 GRoller *rl;

 rl = FindGRoller();
 if(rl == 0L)
  return;
 rl->AddObject(new GRadioButton(0,0,130,20,windowname,ITEM_NORMAL,registernumber));
 rl->Show();
}

#pragma argsused
void DeskTopWindow :: DropIcon(int registernumber)
{
 GRoller *rl;

 rl = FindGRoller();
 if(rl == 0L)
  return;

 rl->DropItem(rl->GetActiveItem());
 rl->Show();
}

GRoller * DeskTopWindow :: FindGRoller(void)
{
 int i;
 Object *ob;

 for(i = 0;i < MyGroup.GetGroupSize();i ++)
  {
   ob = MyGroup.GetItem(i);
   if(ob->isA() == _GRoller)
    break;
  }

 if(i == MyGroup.GetGroupSize())
  return 0L;

return (GRoller *)ob;
}
