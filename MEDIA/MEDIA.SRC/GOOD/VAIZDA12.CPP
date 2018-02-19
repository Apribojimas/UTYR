#include "graph.hpp"
#include "gettext.hpp"
#include "proto.hpp"
#include "define.hpp"
#include "gfile.hpp"
#include "images.hpp"
#include "vcmd.hpp"
#include "fragment.hpp"
#include "magnify.hpp"
#include "vaizda12.hpp"
#include "warning.hpp"
#include "mouse.hpp"

#define KOREKCIJA_DEL_LANGO_REMO  (33 / 3)
#define SIZE_640     (160 - KOREKCIJA_DEL_LANGO_REMO)
#define SIZE_800     (200 - KOREKCIJA_DEL_LANGO_REMO)
#define SIZE_1024    (256 - KOREKCIJA_DEL_LANGO_REMO)


#ifndef _VAIZDA_12
#define _VAIZDA_12

#include "gwindow.hpp"
#include "phandler.hpp"

class Vaizda12 : public GWindow
{
 int Size;
 int Mode;
 int GFileRegisterNumber;
 Bag MyBag;

public:
 ~Vaizda12();
  Vaizda12();

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);        // apdorosime komandas
  virtual int Mouse(MSG &msg);          // mouse eventai
  virtual int Keyboard(MSG &msg);       // klaviaturos
private:
  void RunGFile(void);
  void FillMenu(int i);
  int SetSize(void);
  int ifWndDraw(int nr);
  int FindActiveFilter(void);
  void RunNewFilter(void);
  int RunModeFilter(PictureHandler *ph,int mode);  // mode=[0..2]
};
#endif

Vaizda12 :: Vaizda12()
         :  GWindow(0,0,0,0,GetText(10047),WND_GRAPH | WND_CLOSE_BUTTON | WND_MIN_BUTTON | WND_MAX_BUTTON),
            MyBag(DELETE)
{
 GFileRegisterNumber = 0;
 Mode = CurrentMode;
 Size = SetSize();

 SetWndMaxDXDY(Size * 4,Size * 3);
 SetDXDY(Size * 4,Size * 3);
 FillMenu(0);
}

Vaizda12 :: ~Vaizda12()
{
 if(GFileRegisterNumber)
  SendMSGCmd(ITEM_DESTROY,GFileRegisterNumber);
}

#pragma argsused
void Vaizda12 :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 int i;
 int flag;
 long MHandler;
 PictureHandler *ph;

 SetColor(_RED);
 for(i = 0;i < 12;i ++)
  {
   if(i < MyBag.GetBagSize())
    {
     ph = (PictureHandler *) MyBag.GetItem(i);
     switch(Mode)
      {
       case MODE_640:
            MHandler = ph->MHandler_640;
            flag = ph->Register[0];
            break;
       case MODE_800:
            MHandler = ph->MHandler_800;
            flag = ph->Register[1];
            break;
       case MODE_1024:
            MHandler = ph->MHandler_1024;
            flag = ph->Register[2];
            break;
      }
     if(flag || MHandler == ERROR_HANDLER)
      Bar(x + (i % 4) * Size,y + (i / 4) * Size,Size,Size,_BLACK);
     else
      MDisplay(MHandler,Size,Size,x + (i % 4) * Size,y + (i / 4) * Size);
     OutStr(x + (i % 4) * Size + 10,y + (i / 4) * Size,ph->String);
    }
   else
    Bar(x + (i % 4) * Size,y + (i / 4) * Size,Size,Size,_BLACK);
  }
}

void Vaizda12 :: FillMenu(int i)
{
 int Max;

 NewMenu();
 switch(i)
  {
   case 0:
        Max = TextMaxLen(10006,10046,10004,0);
        Max = Max * SmallFontTable[1] + 3;
        AddMenuItem(new GRadioButton(0,0,Max,20,GetText(10006),BMP_READ));
        AddMenuItem(new GRadioButton(0,20,Max,20,GetText(10046),CLOSE_PICTURE));
        AddMenuItem(new GRadioButton(0,40,Max,20,GetText(10004),ITEM_CLOSE));
        break;
  }
}

void Vaizda12 :: RunGFile(void)
{
 GFile *gf;

 gf = new GFile(190,0,RegisterNumber,READ);
 gf->SetFileMask(FileNameMask);
 gf->SetPath(GetImagesName(0L));
 gf->FillGFile();
 GFileRegisterNumber = Register((Object *)gf);
}

ClassType Vaizda12 :: isA()
{
 return _Vaizda12;
}

int Vaizda12 :: Mouse(MSG &msg)
{
 int i;
 int x;
 int y;
 PictureHandler *ph;
 long MHandler;

 i = GWindow :: Mouse(msg);

 if(isMyFrame(msg.X,msg.Y) && WndActive == WND_ACTIVE)
  {
   if(msg.Mouse & LBUTTON)
    {
     x = msg.X - ViewX;
     y = msg.Y - ViewY;
     if(x > 0 && y > 0)
      {
       i = (x / Size) + 4 * (y / Size);
       if(i < MyBag.GetBagSize())
        {
         ph = (PictureHandler *) MyBag.GetItem(i);
         MHandler = MAlloc((long)ph->Size*ph->Size);
         MCopyRectangle(ph->MHandler,ph->Size,ph->Size,0,0,
                        MHandler,ph->Size,ph->Size,0,0,ph->Size,ph->Size);
         Register(new Fragment(ph->String,MHandler,ph->Size,ph->Size));
         return 1;
        }
      }
    }
  }

return i;
}

int Vaizda12 :: Keyboard(MSG &msg)
{
/*
 switch(msg.Key)
  {
   case F1:
        RunHelp();
        return 1;
  }
*/
 return GWindow :: Keyboard(msg);
}

int Vaizda12 :: Command(MSG &msg)
{
 int PictureSizeDX;
 int PictureSizeDY;
 long MHandler;
 char drive[MAXDRIVE];
 char dir[MAXDIR];
 char file[MAXFILE];
 char ext[MAXEXT];
 char Path[MAX_PATH];
 PictureHandler *ph;

 switch(msg.Cmd)
  {
   case FILTER_LOCK_OUT:
        if(ifWndDraw((int)msg.Param1))
         WndDraw();
        SendMSGCmd(TERMINATE_FILTER,0,msg.Param1);
        if(!FindActiveFilter())
         RunNewFilter();
        return 0;
   case VIDEO_MODE_640:
        Mode = MODE_640;
        Size = SetSize();
        SetWndMaxDXDY(Size * 4,Size * 3);
        SetDXDY(Size * 4,Size * 3);
        break;
   case VIDEO_MODE_800:
        Mode = MODE_800;
        Size = SetSize();
        SetWndMaxDXDY(Size * 4,Size * 3);
        SetDXDY(Size * 4,Size * 3);
        break;
   case VIDEO_MODE_1024:
        Mode = MODE_1024;
        Size = SetSize();
        SetWndMaxDXDY(Size * 4,Size * 3);
        SetDXDY(Size * 4,Size * 3);
        break;
   case CLOSE_PICTURE:
        while(MyBag.GetBagSize())
         MyBag - 0;
        WndDraw();
        return 1;
   case BMP_READ:
        RunGFile();
        return 1;
   case FILE_READ_OK:
        MRead(msg.Param1,Path);
        MFree(msg.Param1);
        if(GetInfo(Path,PictureSizeDX,PictureSizeDY))
         {
          Register(new Warning(10061));
          return 1;
         }
        fnsplit(Path,drive,dir,file,ext);
        MHandler=MAlloc((long)PictureSizeDX*PictureSizeDY);
        SetMouseShape(CLOCK);
        ReadImage(Path,MHandler);
        SetMouseShape(ARROW);
        ph = new PictureHandler(MHandler,PictureSizeDX,file);
        MyBag + ph;
        switch(Mode)
         {
          case MODE_640:
               RunModeFilter(ph,0);
               break;
          case MODE_800:
               RunModeFilter(ph,1);
               break;
          case MODE_1024:
               RunModeFilter(ph,2);
               break;
         }
        if(MyBag.GetBagSize() < 12)
         RunGFile();
        return 1;
   case FILE_CANCEL:
        GFileRegisterNumber = 0;
        return 1;
  }

return GWindow :: Command(msg);
}

int Vaizda12 :: SetSize(void)
{
 switch(Mode)
  {
   case MODE_640:
        return SIZE_640;
   case MODE_800:
        return SIZE_800;
   case MODE_1024:
        return SIZE_1024;
  }
return 1;
}

int Vaizda12 :: ifWndDraw(int nr)
{
 int i;
 int j;
 PictureHandler *ph;

 for(i = 0;i < MyBag.GetBagSize();i ++)
  {
   ph = (PictureHandler *) MyBag.GetItem(i);
   for(j = 0;j < 3;j ++)
    {
     if(ph->Register[j] == nr)
      {
       ph->Register[j] = 0;
       switch(Mode)
        {
         case MODE_640:
              if(j == 0 && WndActive == WND_ACTIVE && WndEvent == 0 && WndStatus != WND_ICON)
               return 1;
              return 0;
         case MODE_800:
              if(j == 1 && WndActive == WND_ACTIVE && WndEvent == 0 && WndStatus != WND_ICON)
               return 1;
              return 0;
         case MODE_1024:
              if(j == 2 && WndActive == WND_ACTIVE && WndEvent == 0 && WndStatus != WND_ICON)
               return 1;
              return 0;
        }
      }
    }
  }

return 0;
}

int Vaizda12 :: FindActiveFilter(void)
{
 int i;
 int j;
 PictureHandler *ph;

 for(i = 0;i < MyBag.GetBagSize();i ++)
  {
   ph = (PictureHandler *) MyBag.GetItem(i);
   for(j = 0;j < 3;j ++)
    if(ph->Register[j])
     return 1;
  }

return 0;
}

void Vaizda12 :: RunNewFilter(void)
{
 int i;
 PictureHandler *ph;

 switch(Mode)
  {
   case MODE_640:
        for(i = 0;i < MyBag.GetBagSize();i ++)
         {
          ph = (PictureHandler *) MyBag.GetItem(i);
          if(RunModeFilter(ph,0))
           return;
         }
        break;
   case MODE_800:
        for(i = 0;i < MyBag.GetBagSize();i ++)
         {
          ph = (PictureHandler *) MyBag.GetItem(i);
          if(RunModeFilter(ph,1))
           return;
         }
        break;
   case MODE_1024:
        for(i = 0;i < MyBag.GetBagSize();i ++)
         {
          ph = (PictureHandler *) MyBag.GetItem(i);
          if(RunModeFilter(ph,2))
           return;
         }
        break;
  }

 for(i = 0;i < MyBag.GetBagSize();i ++)
  {
   ph = (PictureHandler *) MyBag.GetItem(i);
   if(RunModeFilter(ph,0))
    return;
   if(RunModeFilter(ph,1))
    return;
   if(RunModeFilter(ph,2))
    return;
  }

}

int Vaizda12 :: RunModeFilter(PictureHandler *ph,int mode)
{

 switch(mode)
  {
   case 0:
	if(!TestVideoMode(MODE_640))
	 if(ph->MHandler_640 == ERROR_HANDLER && ph->Register[0] == 0)
	 {
	  ph->MHandler_640 = MAlloc((long)SIZE_640 * SIZE_640);
	  ph->Register[0]= RegisterFilter(new Magnify(ph->MHandler,ph->Size,ph->Size,
				    ph->MHandler_640,SIZE_640,SIZE_640,RegisterNumber));
	  return 1;
	 }
	break;
   case 1:
	if(!TestVideoMode(MODE_800))
	 if(ph->MHandler_800 == ERROR_HANDLER && ph->Register[0] == 0)
	 {
	  ph->MHandler_800 = MAlloc((long)SIZE_800 * SIZE_800);
	  ph->Register[1]= RegisterFilter(new Magnify(ph->MHandler,ph->Size,ph->Size,
				  ph->MHandler_800,SIZE_800,SIZE_800,RegisterNumber));
	  return 1;
	 }
	break;
   case 2:
	if(!TestVideoMode(MODE_1024))
	 if(ph->MHandler_1024 == ERROR_HANDLER && ph->Register[0] == 0)
	 {
	  ph->MHandler_1024 = MAlloc((long)SIZE_1024 * SIZE_1024);
	  ph->Register[2]= RegisterFilter(new Magnify(ph->MHandler,ph->Size,ph->Size,
				  ph->MHandler_1024,SIZE_1024,SIZE_1024,RegisterNumber));
	  return 1;
	 }
	break;
  }
return 0;
}
