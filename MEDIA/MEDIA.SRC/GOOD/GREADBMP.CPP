#include <stdio.h>
#include <alloc.h>
#include <string.h>
#include "gettext.hpp"
#include "mm.hpp"
#include "define.hpp"
#include "graph.hpp"
#include "vcmd.hpp"
#include "proto.hpp"
#include "gfile.hpp"
#include "gdefine.hpp"
#include "images.hpp"
#include "greadbmp.hpp"
#include "warning.hpp"
#include "mouse.hpp"
#include "gpal.hpp"
#include "keys.h"

void Heap(char far *record);

#ifndef _GREADBMP
#define _GREADBMP

#include "gwindow.hpp"

class GReadBMP : public GWindow
{
 int isInit;
 int GFileRegisterNumber;
 char FileMask[14];
 long PalHandler;
protected:
 int PictureSizeDX;
 int PictureSizeDY;
 long MHandler;
public:
 ~GReadBMP();
  GReadBMP(char *wndname = "",char *filemask = "*.*");

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  void SetFileMask(char *filemask);
  void SetInitOK(void);
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);         // apdorosime komandas
  virtual int Keyboard(MSG &msg);        // klaviaturos
private:
  void SetMaxViewPort(void);
};
#endif

GReadBMP :: GReadBMP(char *wndname,char *filemask)
         :  GWindow(190,0,50,50,wndname,WND_GRAPH | WND_CLOSE_BUTTON | WND_MIN_BUTTON | WND_MAX_BUTTON,1,1)
{
 int Max;

 isInit = 0;
 GFileRegisterNumber = 0;
 MHandler = ERROR_HANDLER;
 PalHandler = ERROR_HANDLER;

 SetMaxPos(0,VERTICAL);
 SetMaxPos(0,HORIZANTAL);
 SetFileMask(filemask);

 Max = TextMaxLen(10006,10007,10004,0);
 Max = Max * SmallFontTable[1] + 3;
 AddMenuItem(new GRadioButton(0,0,Max,20,GetText(10006),BMP_READ));
 AddMenuItem(new GRadioButton(0,20,Max,20,GetText(10007),BMP_WRITE));
 AddMenuItem(new GRadioButton(0,40,Max,20,GetText(10004),ITEM_CLOSE));
}

GReadBMP :: ~GReadBMP()
{
 if(MHandler != ERROR_HANDLER)
  MFree(MHandler);
 if(PalHandler != ERROR_HANDLER)
  MFree(PalHandler);
 if(isInit != 2)
  SendMSGCmd(ITEM_DESTROY,GFileRegisterNumber);
}

ClassType GReadBMP :: isA()
{
 return _GReadBMP;
}

void GReadBMP :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 int i;
 int j;
 int X1,Y1;
 int memrow;
 int readrow = 0;
 char huge *picture;

 if(MHandler == ERROR_HANDLER)
  Bar(x,y,dx,dy,GRAY_8);
 else
  {
   if(PictureSizeDX)
    X1 = (PictureSizeDX - dx) * ((float)hscroll / PictureSizeDX);
   else
    X1 = 0;
   if(PictureSizeDY)
    Y1 = (PictureSizeDY - dy) * ((float)vscroll / PictureSizeDY);
   else
    Y1 = 0;

   if((picture = (char *)FarMalloc(dx,dy,memrow,80)) != 0l)
   {
    for(i=0; ;i += readrow)
    {
     if(PictureSizeDY - i >= memrow)
      readrow = memrow;
     else
      readrow = PictureSizeDY - i;
     if(readrow <= 0)
       break;
     if(dx != PictureSizeDX)
      for(j = 0;j < readrow;j++)
       MRead(MHandler,picture + (long)j * dx,(long)(j + Y1 + i) * PictureSizeDX + X1,dx);
     else
      MRead(MHandler,picture,(long)(Y1 + i) * PictureSizeDX,(long)PictureSizeDX * readrow);

     Display(x,y + i,dx,readrow,picture);
    }
    farfree(picture);
   }
  }
}

void GReadBMP :: SetFileMask(char *filemask)
{
 memcpy(FileMask,filemask,14);
 FileMask[13] = 0;
}

void GReadBMP :: SetInitOK(void)
{
 isInit = 2;
}

int GReadBMP :: Command(MSG &msg)
{
 int i;
// char wnd_name[100];
 char drive[MAXDRIVE];
 char dir[MAXDIR];
 char file[MAXFILE];
 char ext[MAXEXT];
 char Path[MAX_PATH];
 char palette[768];
 GFile *gf;

 if(isInit == 0)
  {
   SendMSGCmd(BMP_READ,RegisterNumber);
   isInit = 1;
  }

 switch(msg.Cmd)
  {
   case BMP_WRITE:
        gf = new GFile(190,0,RegisterNumber,WRITE);
        gf->SetFileMask(FileMask);
        gf->SetPath(GetImagesName(0L));
	gf->FillGFile();
        GFileRegisterNumber = Register((Object *)gf);
        return 1;
   case BMP_READ:
        gf = new GFile(190,0,RegisterNumber,READ);
        gf->SetFileMask(FileMask);
        gf->SetPath(GetImagesName(0L));
	gf->FillGFile();
        GFileRegisterNumber = Register((Object *)gf);
        return 1;
   case FILE_WRITE_OK:
        MRead(msg.Param1,Path);
        MFree(msg.Param1);
        if(MHandler == ERROR_HANDLER)
         return 1;
        SetMouseShape(CLOCK);
        if(WriteImage(Path,MHandler,PictureSizeDX,PictureSizeDY))
         Register(new Warning(10060));
        SetMouseShape(ARROW);
        return 1;
   case FILE_READ_OK:
        SetInitOK();
        MRead(msg.Param1,Path);
        MFree(msg.Param1);
        if(GetInfo(Path,PictureSizeDX,PictureSizeDY))
         {
          SendMSGCmd(ITEM_DESTROY,RegisterNumber);
          Register(new Warning(10061));
          return 1;
         }
        SetMaxViewPort();
        fnsplit(Path,drive,dir,file,ext);
//        sprintf(wnd_name,"%.30s %s",GetWndName(),file);
//        SetWndName(wnd_name);
        SetWndName(file);
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
        if(MHandler != ERROR_HANDLER)
         MFree(MHandler);
        if(PalHandler != ERROR_HANDLER)
         MFree(PalHandler);
        MHandler=MAlloc((long)PictureSizeDX*PictureSizeDY);
        PalHandler = MAlloc(768);
        SetMouseShape(CLOCK);
        ReadImage(Path,MHandler);
        GetPalette(Path,palette);
        MWrite(PalHandler,palette);
        SetMouseShape(ARROW);
        SetMaxViewPort();
//	SendMSGCmd(REDRAW);
        return 1;
   case FILE_CANCEL:
        if(isInit == 1)
         SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        return 1;
   case ITEM_MAX:
        SetMaxPos(0,VERTICAL);
        SetMaxPos(0,HORIZANTAL);
        if(WndStatus == WND_BIG)
         {
          if(PictureSizeDX > WINDOW_SIZE_DX)
           SetMaxPos(PictureSizeDX,HORIZANTAL);
          if(PictureSizeDY > WINDOW_SIZE_DY)
           SetMaxPos(PictureSizeDY,VERTICAL);
         }
        break;
  }

 i = GWindow :: Command(msg);

return i;
}

void GReadBMP :: SetMaxViewPort(void)
{
 int x,y,dx,dy;

//        SetViewPort(X,Y,DX,DY);
//        SetViewPort(0,0,GraphMaxX + 1,GraphMaxY + 1);
// paskaicuojam koki rajona reiks perpiesti
 GetViewPort(x,y,dx,dy);
 if(X + DX > x + dx)
  dx = X + DX - x;
 if(Y + DY > y + dy)
  dy = Y + DY - y;
 if(X < x)
  {
   dx += x - X;
   x = X;
  }
 if(Y < y)
  {
   dy += y - Y;
   y = Y;
  }
 SetViewPort(x,y,dx,dy);
}

int GReadBMP :: Keyboard(MSG &msg)
{
 switch(msg.Key)
  {
   case ALT_P:
        Register(new GPalette(PalHandler));
        return 1;
  }
 GWindow :: Keyboard(msg);
return 1;
}
