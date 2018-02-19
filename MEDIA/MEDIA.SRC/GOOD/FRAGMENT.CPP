#include "fronto.hpp"
#include "mouse.hpp"
#include "proto.hpp"
#include "graph.hpp"
#include "gettext.hpp"
#include "define.hpp"
#include "vcmd.hpp"
#include "frag_r.hpp"
#include "frag_e.hpp"
#include "frag_c.hpp"
#include "frag_f.hpp"
#include "frag_l.hpp"
#include "mm.hpp"
#include "keys.h"
#include "lupa.hpp"
#include "images.hpp"
#include "calculat.hpp"
#include "config.hpp"
#include "warning.hpp"
#include "fragment.hpp"

void Heap(char far *record);

extern int CalFirstWarning;

#ifndef _FRAGMENT
#define _FRAGMENT

#include "greadbmp.hpp"
#include "frgroup.hpp"
#include "calstr.hpp"

class Fragment : public GReadBMP
{
 int isKalkuliatorius;
 int ScrollX;
 int ScrollY;
 int CurrentMenuFill;
 int FragmentIndex;
 CalStruct *CStruct;
 FragmentGroup MyGroup;
public:
 ~Fragment();
  Fragment(char *wndname = "",char *filemask = "*.*");
  Fragment(char *wndname = "",long mhandler,int pictsizedx,int pictsizedy);

  int isFragmentOK(void);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual int  EventHandler(MSG &msg);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);        // apdorosime komandas
  virtual int Keyboard(MSG &msg);       // klaviaturos
private:
  void FillMenu(int i);
  void DeleteFragment(int fragment_nr);
  long FillSaveFile(void);
  int CalculateLine(long *mhandler);
  int ifHaveFiltr(void);
};
#endif

Fragment :: Fragment(char *wndname,char *filemask)
         :  GReadBMP(wndname,filemask)
{
 isKalkuliatorius = 0;
 CurrentMenuFill = 0;
 ScrollX = 0;
 ScrollY = 0;
 FragmentIndex = 0;
 CStruct = new CalStruct;

 FillMenu(100);
}

Fragment :: Fragment(char *wndname,long mhandler,int pictsizedx,int pictsizedy)
         :  GReadBMP(wndname)
{
 isKalkuliatorius = 0;
 CurrentMenuFill = 0;
 ScrollX = 0;
 ScrollY = 0;
 FragmentIndex = 0;
 MHandler = mhandler;
 PictureSizeDX = pictsizedx;
 PictureSizeDY = pictsizedy;

 FillMenu(0);
 SetInitOK();
 SetWndMaxDXDY(PictureSizeDX,PictureSizeDY);
 SetDXDY(PictureSizeDX,PictureSizeDY);
 SetMaxPos(0,VERTICAL);
 SetMaxPos(0,HORIZANTAL);
 if(PictureSizeDX > WINDOW_SIZE_DX || PictureSizeDY > WINDOW_SIZE_DY)
  {
   if(PictureSizeDX > WINDOW_SIZE_DX)
    {
     DX = WINDOW_SIZE_DX;
     SetMaxPos(PictureSizeDX,HORIZANTAL);
     SetPos(PictureSizeDX / 2,HORIZANTAL);
    }
   if(PictureSizeDY > WINDOW_SIZE_DY)
    {
     DY = WINDOW_SIZE_DY;
     SetMaxPos(PictureSizeDY,VERTICAL);
     SetPos(PictureSizeDY / 2,VERTICAL);
    }
  }
 CStruct = new CalStruct;
}

Fragment :: ~Fragment()
{
 SendMSGCmd(DESTROY_HISTO,0,RegisterNumber);
 Heap("Fragment :: ~Fragment 1");
 if(CStruct != 0L)
  delete CStruct;
 Heap("Fragment :: ~Fragment 2");
}

void Fragment :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 GReadBMP :: Draw(x,y,dx,dy,hscroll,vscroll);

 if(PictureSizeDX)
  ScrollX = (PictureSizeDX - dx) * ((float)hscroll / PictureSizeDX);
 else
  ScrollX = 0;
 if(PictureSizeDY)
  ScrollY = (PictureSizeDY - dy) * ((float)vscroll / PictureSizeDY);
 else
  ScrollY = 0;
 MyGroup.SetX(x - ScrollX);
 MyGroup.SetY(y - ScrollY);
 MyGroup.SetDisplayPort(x,y,dx,dy);
 MyGroup.Show();
}

ClassType Fragment :: isA()
{
 return _Fragment;
}

void Fragment :: FillMenu(int i)
{
 int Max;
 int Shift = 0;

 NewMenu();
 switch(i)
  {
   case 0:
        if(MyGroup.GetGroupSize())
         Max = TextMaxLen(10006,10007,10008,10013,10014,10015,10016,10004,10062,0);
        else
         Max = TextMaxLen(10006,10007,10008,10013,10014,10004,10062,0);
        Max = Max * SmallFontTable[1] + 3;
        AddMenuItem(new GRadioButton(0,0,Max,18,GetText(10006),BMP_READ,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,18,Max,18,GetText(10007),BMP_WRITE,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,36,Max,18,GetText(10008),FRAGMENT_SWITCH,0,0xffff,JUSTIFY_LEFT));
        if(MyGroup.GetGroupSize())
         AddMenuItem(new GRadioButton(0,54,Max,18,GetText(10013),FRAGMENT_FILL_ABORT,0,0xffff,JUSTIFY_LEFT));
        else
         AddMenuItem(new GRadioButton(0,54,Max,18,GetText(10013),FRAGMENT_FILL_ABORT,0,0xffff,JUSTIFY_LEFT,BUTTON_UNAVAILABLE));
        AddMenuItem(new GRadioButton(0,72,Max,18,GetText(10014),LUPA,0,0xffff,JUSTIFY_LEFT));
        if(CalFirstWarning == 0)
         AddMenuItem(new GRadioButton(0,90,Max,18,GetText(10027),KALKULIATORIUS,0,0xffff,JUSTIFY_LEFT));
        else
         AddMenuItem(new GRadioButton(0,90,Max,18,GetText(10027),KALKULIATORIUS,0,0xffff,JUSTIFY_LEFT,BUTTON_UNAVAILABLE));
        if(ifHaveFiltr())
         {
          AddMenuItem(new GRadioButton(0,108,Max,18,GetText(10015),HISTOGRAMA,0,0xffff,JUSTIFY_LEFT));
          AddMenuItem(new GRadioButton(0,126,Max,18,GetText(10016),FR_FILTRAI,0,0xffff,JUSTIFY_LEFT));
         }
        else
         {
          AddMenuItem(new GRadioButton(0,108,Max,18,GetText(10015),HISTOGRAMA,0,0xffff,JUSTIFY_LEFT,BUTTON_UNAVAILABLE));
          AddMenuItem(new GRadioButton(0,126,Max,18,GetText(10016),FR_FILTRAI,0,0xffff,JUSTIFY_LEFT,BUTTON_UNAVAILABLE));
         }
        AddMenuItem(new GRadioButton(0,144,Max,18,GetText(10062),FRONTOGRAMA,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,162,Max,18,GetText(10004),ITEM_CLOSE,0,0xffff,JUSTIFY_LEFT));
        break;
   case 1:
        Max = TextMaxLen(10009,10010,10011,10012,0);
        Max = Max * SmallFontTable[1] + 3;
        AddMenuItem(new GRadioButton(0,0,Max,20,GetText(10009),FRAGMENT_RECTANGLE,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,20,Max,20,GetText(10010),FRAGMENT_CIRCLE,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,40,Max,20,GetText(10011),FRAGMENT_ELLIPSE,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,60,Max,20,GetText(10012),FRAGMENT_FRAGMENT,0,0xffff,JUSTIFY_LEFT));
        break;
   case 2:
        Max = TextMaxLen(10051,10070,10071,10072,10073,10100,10093,0);
        Max = Max * SmallFontTable[1] + 3;

        AddMenuItem(new GRadioButton(0,0,Max,18,GetText(10051),HISTO_PL,0,0xffff,JUSTIFY_LEFT));
        #ifdef LAPLASS_FILTER
        AddMenuItem(new GRadioButton(0,Shift += 18,Max,18,GetText(10070),LAPLASS,0,0xffff,JUSTIFY_LEFT));
        #endif
        #ifdef MEDIAN_FILTER
        AddMenuItem(new GRadioButton(0,Shift += 18,Max,18,GetText(10071),MEDIAN,0,0xffff,JUSTIFY_LEFT));
        #endif
        #ifdef AVERAGE_FILTER
        AddMenuItem(new GRadioButton(0,Shift += 18,Max,18,GetText(10072),AVERAGE,0,0xffff,JUSTIFY_LEFT));
        #endif
        #ifdef HIGH_PASS_FILTER
        AddMenuItem(new GRadioButton(0,Shift += 18,Max,18,GetText(10073),HIGH_PASS,0,0xffff,JUSTIFY_LEFT));
        #endif
        #ifdef GRADIENT_FILTER
        AddMenuItem(new GRadioButton(0,Shift += 18,Max,18,GetText(10074),GRADIENT,0,0xffff,JUSTIFY_LEFT));
        #endif
        #ifdef ROBERTS_FILTER
        AddMenuItem(new GRadioButton(0,Shift += 18,Max,18,GetText(10100),ROBERTS,0,0xffff,JUSTIFY_LEFT));
        #endif
        #ifdef HISTO_REDUCE_FILTER
        AddMenuItem(new GRadioButton(0,Shift += 18,Max,18,GetText(10104),HISTO_REDUCE,0,0xffff,JUSTIFY_LEFT));
        #endif
        #ifdef EDGE_DETECTION_FILTER
        AddMenuItem(new GRadioButton(0,Shift += 18,Max,18,GetText(10093),EDGE_DETECTION,0,0xffff,JUSTIFY_LEFT));
        #endif
        break;
   case 3:
// laplass
        Max = TextMaxLen(10017,10018,10019,10020,0);
        Max = Max * SmallFontTable[1] + 3;

        AddMenuItem(new GRadioButton(0,0,Max,20,GetText(10017),LAPLAS1,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10018),LAPLAS2,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10019),LAPLAS3,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10020),LAPLAS4,0,0xffff,JUSTIFY_LEFT));
        break;
   case 4:
// median
        Max = TextMaxLen(10034,10035,10036,10037,10038,0);
        Max = Max * SmallFontTable[1] + 3;

        AddMenuItem(new GRadioButton(0,0,Max,20,GetText(10034),MEDIAN1x3,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10035),MEDIAN3x1,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10036),MEDIAN3x3,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10037),MEDIAN5x5,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10038),MEDIANCROSS,0,0xffff,JUSTIFY_LEFT));
        break;
   case 5:
// average
        Max = TextMaxLen(10075,10076,10077,10111,10112,10113,0);
        Max = Max * SmallFontTable[1] + 3;

        AddMenuItem(new GRadioButton(0,0,Max,20,GetText(10075),AVERAGE_1,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10076),AVERAGE_2,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10077),AVERAGE_3,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10112),AVERAGE_4,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10111),AVERAGE_5,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10113),AVERAGE_6,0,0xffff,JUSTIFY_LEFT));
        break;
   case 6:
// high pass
        Max = TextMaxLen(10078,10079,10080,0);
        Max = Max * SmallFontTable[1] + 3;

        AddMenuItem(new GRadioButton(0,0,Max,20,GetText(10078),HIGH_PASS_1,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10079),HIGH_PASS_2,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10080),HIGH_PASS_3,0,0xffff,JUSTIFY_LEFT));
        break;
   case 7:
// gradient
        Max = TextMaxLen(10081,10081,10082,10083,10084,10085,10086,10087,10088,0);
        Max = Max * SmallFontTable[1] + 3;

        AddMenuItem(new GRadioButton(0,0,Max,20,GetText(10081),GRADIENT_1,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10082),GRADIENT_2,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10083),GRADIENT_3,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10084),GRADIENT_4,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10085),GRADIENT_5,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10086),GRADIENT_6,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10087),GRADIENT_7,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10088),GRADIENT_8,0,0xffff,JUSTIFY_LEFT));
        break;
   case 8:
   // edge detection
        Max = TextMaxLen(10095,10094,10096,10097,0);
        Max = Max * SmallFontTable[1] + 3;

        AddMenuItem(new GRadioButton(0,0,Max,20,GetText(10094),DETECT_MAX,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10095),DETECT_MIN,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10096),WBOUNDARY,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10097),EWRONGS,0,0xffff,JUSTIFY_LEFT));
        break;
   case 9:
   // roberts
        Max = TextMaxLen(10101,10102,10103,0);
        Max = Max * SmallFontTable[1] + 3;

        AddMenuItem(new GRadioButton(0,0,Max,20,GetText(10101),ROBERTS_SQRT,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10102),ROBERTS_MAX,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10103),ROBERTS_ABS,0,0xffff,JUSTIFY_LEFT));
        break;
   case 10:
   // Histograma
        Max = TextMaxLen(10099,10098,10108,10109,0);
        Max = Max * SmallFontTable[1] + 3;

        AddMenuItem(new GRadioButton(0,0,Max,20,GetText(10098),HISTO_PL1,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10099),HISTO_PL2,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10108),HISTO_PL3,0,0xffff,JUSTIFY_LEFT));
        AddMenuItem(new GRadioButton(0,Shift += 20,Max,20,GetText(10109),BIN,0,0xffff,JUSTIFY_LEFT));
        break;
  }
}

int Fragment :: EventHandler(MSG &msg)
{
 int i = 0;

 if(WndStatus != WND_ICON)
  if(WndMenu != DTW_MENU || msg.Type == COMMAND)
   if(MyGroup.EventHandler(msg) && WndActive == WND_ACTIVE)
    i ++;

 if(GReadBMP :: EventHandler(msg))
  i ++;

return i;
}
int Fragment :: Command(MSG &msg)
{
 int i = 0;
 char Path[MAX_PATH];
 long TmpMHandler = ERROR_HANDLER;
 long LokalMHandler;
 Object *Obj;

 switch(msg.Cmd)
  {
   case FILE_READ_OK:
        MyGroup.NewGroup();
        FillMenu(0);
        Heap("Fragment :: Command 0");
        if(CStruct != 0L)
         delete CStruct;
        CStruct = new CalStruct;
        Heap("Fragment :: Command 1");
        break;
   case FILE_WRITE_OK:
        MRead(msg.Param1,Path);
        MFree(msg.Param1);
        if(MHandler == ERROR_HANDLER)
         return 1;

        TmpMHandler = FillSaveFile();
        if(WriteImage(Path,TmpMHandler,PictureSizeDX,PictureSizeDY))
         Register(new Warning(10060));
        MFree(TmpMHandler);
        return 1;
  }

 if(GReadBMP :: Command(msg))
  i ++;

 switch(msg.Cmd)
  {
   case DESTROY_FRAGMENT_LINE:
        DeleteFragment((int)msg.Param1);
        return 1;
   case FRONTOGRAMA:
        MyGroup.AddItem(new FragmentLine(MyGroup.GetGroupSize() + 1,FragmentIndex,
                            RegisterNumber));
        FragmentIndex ++;
        SendMSGCmd(FRAGMENT_FILL,RegisterNumber,((long)(X + 5) << 16) + Y + 29,((long)(DX - 26) << 16) + DY - 50);
        return 1;
   case ITEM_ACTIVE:
        if(isKalkuliatorius)
         {
          WndDraw();
          isKalkuliatorius = 0;
          FillMenu(0);
         }
        break;
   case KALKULIATORIUS:
        if(CStruct)
         {
          CStruct->RegisterNumber = RegisterNumber;
          CStruct->ViewX = ViewX;
          CStruct->ViewY = ViewY;
          CStruct->ViewDX = ViewDX;
          CStruct->ViewDY = ViewDY;
         }
        isKalkuliatorius = 1;

        if(CalFirstWarning == 0)
         Register(new Calculate);

        SendMSGCmd(KALKUL_STRUCT,0,(long)CStruct);
        Heap("Fragment :: Command 2");
        return 1;
   case ITEM_PASIVE:
        CurrentMenuFill = 0;
        break;
   case HISTO_PL:
        CurrentMenuFill = 10;
        SendMSGCmd(MENU_ACTIVE,RegisterNumber);
        return 1;
   case FR_FILTRAI:
        CurrentMenuFill = 2;
        SendMSGCmd(MENU_ACTIVE,RegisterNumber);
        return 1;
   case LAPLASS:
        CurrentMenuFill = 3;
        SendMSGCmd(MENU_ACTIVE,RegisterNumber);
        return 1;
   case MEDIAN:
        CurrentMenuFill = 4;
        SendMSGCmd(MENU_ACTIVE,RegisterNumber);
        return 1;
   case AVERAGE:
        CurrentMenuFill = 5;
        SendMSGCmd(MENU_ACTIVE,RegisterNumber);
        return 1;
   case EDGE_DETECTION:
        CurrentMenuFill = 8;
        SendMSGCmd(MENU_ACTIVE,RegisterNumber);
        return 1;
   case HIGH_PASS:
        CurrentMenuFill = 6;
        SendMSGCmd(MENU_ACTIVE,RegisterNumber);
        return 1;
   case GRADIENT:
        CurrentMenuFill = 7;
        SendMSGCmd(MENU_ACTIVE,RegisterNumber);
        return 1;
   case ROBERTS:
        CurrentMenuFill = 9;
        SendMSGCmd(MENU_ACTIVE,RegisterNumber);
        return 1;
   case MENU_PASIVE:
        FillMenu(CurrentMenuFill);
        if(CurrentMenuFill != 0)
         CurrentMenuFill = 0;
        return 1;
   case FRAGMENT_SHOW:
        if(WndActive == WND_ACTIVE)
         {
          if(WndMenu != DTW_MENU && isFragmentOK())
           MyGroup.Show();
          return 1;
         }
        break;
   case FRAGMENT_SWITCH:
        CurrentMenuFill = 1;
        SendMSGCmd(MENU_ACTIVE,RegisterNumber);
        return 1;
   case FRAGMENT_FILL_ABORT:
        Obj = MyGroup.GetItem(0);
        DeleteFragment(Obj->RegisterNumber);
        return 1;
   case FRAGMENT_COPY:
        TmpMHandler = MAlloc((long)(msg.Param2 >> 16)*(msg.Param2 & 0xffff));
        LokalMHandler  = FillSaveFile();
        MCopyRectangle( LokalMHandler,
                         PictureSizeDX,PictureSizeDY,
                         (int)(msg.Param1 >> 16) + ScrollX - (X + 5),
                         (int)(msg.Param1 & 0xffff) + ScrollY - (Y + 29),
                        TmpMHandler,
                         (int)(msg.Param2 >> 16),(int)(msg.Param2 & 0xffff),0,0,
                        (int)(msg.Param2 >> 16),(int)(msg.Param2 & 0xffff) );
        MFree(LokalMHandler);
        SendMSGCmd(FRAGMENT_HANDLER,RegisterNumber,TmpMHandler);
        MyGroup.SetItemShift(0,(int)(msg.Param1 >> 16) + ScrollX - (X + 5),(int)(msg.Param1 & 0xffff) + ScrollY - (Y + 29));
        return 1;
   case FRAGMENT_RECTANGLE:
        MyGroup.AddItem(new FragmentRectangle(MyGroup.GetGroupSize() + 1,FragmentIndex,RegisterNumber));
        FragmentIndex ++;
        SendMSGCmd(FRAGMENT_FILL,RegisterNumber,((long)(X + 5) << 16) + Y + 29,((long)(DX - 26) << 16) + DY - 50);
        return 1;
   case FRAGMENT_CIRCLE:
        MyGroup.AddItem(new FragmentCircle(MyGroup.GetGroupSize() + 1,FragmentIndex,RegisterNumber));
        FragmentIndex ++;
        SendMSGCmd(FRAGMENT_FILL,RegisterNumber,((long)(X + 5) << 16) + Y + 29,((long)(DX - 26) << 16) + DY - 50);
        return 1;
   case FRAGMENT_ELLIPSE:
        MyGroup.AddItem(new FragmentEllipse(MyGroup.GetGroupSize() + 1,FragmentIndex,RegisterNumber));
        FragmentIndex ++;
        SendMSGCmd(FRAGMENT_FILL,RegisterNumber,((long)(X + 5) << 16) + Y + 29,((long)(DX - 26) << 16) + DY - 50);
        return 1;
   case FRAGMENT_FRAGMENT:
        MyGroup.AddItem(new FragmentFragment(MyGroup.GetGroupSize() + 1,FragmentIndex,RegisterNumber));
        FragmentIndex ++;
        SendMSGCmd(FRAGMENT_FILL,RegisterNumber,((long)(X + 5) << 16) + Y + 29,((long)(DX - 26) << 16) + DY - 50);
        return 1;
   case LUPA:
        MyGroup.AddItem(new Lupa((PictureSizeDX - ViewDX) * ((float)GetPos(HORIZANTAL) / PictureSizeDX),(PictureSizeDY - ViewDY) * ((float)GetPos(VERTICAL) / PictureSizeDY),WndName));
        SendMSGCmd(FRAGMENT_FILL,RegisterNumber,((long)(X + 5) << 16) + Y + 29,((long)(DX - 26) << 16) + DY - 50);
        LokalMHandler = FillSaveFile();
        SendMSGCmd(LUPA_PICTURE_HANDLER,RegisterNumber,LokalMHandler,(long)((long)PictureSizeDX << 16) + PictureSizeDY); // ?????
//        MFree(LokalMHandler);
        return 1;
  }

return i;
}


int Fragment :: Keyboard(MSG &msg)
{
 Object *Obj;

 switch(msg.Key)
  {
   case F1:
        RunHelp(4);
        return 1;
   case DEL:
        Obj = MyGroup.GetItem(0);
        DeleteFragment(Obj->RegisterNumber);
        return 1;
  }

 GReadBMP :: Keyboard(msg);
return 1;
}

void Fragment :: DeleteFragment(int fragment_nr)
{
 int i = 0;
 Object *Obj;
 FragmentCircle *fc;
 FragmentEllipse *fe;
 FragmentRectangle *fr;
 FragmentLine *fl;
 FragmentFragment *ff;

 for(i = 0;i < MyGroup.GetGroupSize();i++)
  {
   Obj = MyGroup.GetItem(i);
   if(fragment_nr == Obj->RegisterNumber)
    {
     MyGroup - i;
     break;
    }
  }
 for(i = 0;i < MyGroup.GetGroupSize();i++)
  {
   Obj = MyGroup.GetItem(i);
   switch(Obj->isA())
    {
     case _FragmentRectangle:
          fr = (FragmentRectangle *)Obj;
          fr->SetFragmentNumber(i + 1);
          break;
     case _FragmentLine:
          fl = (FragmentLine *)Obj;
          fl->SetFragmentNumber(i + 1);
          break;
     case _FragmentEllipse:
	  fe = (FragmentEllipse *)Obj;
	  fe->SetFragmentNumber(i + 1);
	  break;
     case _FragmentCircle:
	  fc = (FragmentCircle *)Obj;
	  fc->SetFragmentNumber(i + 1);
	  break;
     case _FragmentFragment:
	  ff = (FragmentFragment *)Obj;
	  ff->SetFragmentNumber(i + 1);
	  break;
    }
  }
 FillMenu(0);
 WndDraw();
}

long Fragment :: FillSaveFile(void)
{
 int i = 0;
 long handler = -1;
 Object *Obj;
 FragmentCircle *fc;
 FragmentEllipse *fe;
 FragmentRectangle *fr;
 FragmentFragment *ff;

 handler = MAlloc((long)PictureSizeDX*PictureSizeDY);

 MCopyRectangle( MHandler,PictureSizeDX,PictureSizeDY,0,0,
                 handler,PictureSizeDX,PictureSizeDY,0,0,
                 PictureSizeDX,PictureSizeDY );

 for(i = MyGroup.GetGroupSize() - 1;i >= 0 ;i --)
  {
   Obj = MyGroup.GetItem(i);
   switch(Obj->isA())
    {
     case _FragmentRectangle:
          fr = (FragmentRectangle *)Obj;
          fr->MCopy(handler,PictureSizeDX,PictureSizeDY,ViewX - ScrollX,ViewY - ScrollY);
          break;
     case _FragmentEllipse:
	  fe = (FragmentEllipse *)Obj;
	  fe->MCopy(handler,PictureSizeDX,PictureSizeDY,ViewX - ScrollX,ViewY - ScrollY);
	  break;
     case _FragmentCircle:
	  fc = (FragmentCircle *)Obj;
	  fc->MCopy(handler,PictureSizeDX,PictureSizeDY,ViewX - ScrollX,ViewY - ScrollY);
	  break;
     case _FragmentFragment:
	  ff = (FragmentFragment *)Obj;
	  ff->MCopy(handler,PictureSizeDX,PictureSizeDY,ViewX - ScrollX,ViewY - ScrollY);
	  break;
    }
  }
 return handler;
}

int Fragment :: isFragmentOK(void)
{
 FragmentRectangle *fr;

 fr = (FragmentRectangle *)MyGroup.GetItem(0);
 return fr->isOK();
}

int Fragment :: ifHaveFiltr(void)
{
 int i = 0;
 Object *Obj;

 for(i = 0;i < MyGroup.GetGroupSize();i++)
  {
   Obj = MyGroup.GetItem(i);
   switch(Obj->isA())
    {
     case _FragmentRectangle:
     case _FragmentEllipse:
     case _FragmentCircle:
     case _FragmentFragment:
          return 1;
    }
  }
 return 0;
}
