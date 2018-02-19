#include <alloc.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include "warning.hpp"
#include "mm.hpp"
#include "proto.hpp"
#include "graph.hpp"
#include "images.hpp"
#include "gettext.hpp"
#include "vcmd.hpp"
#include "ginput.hpp"
#include "skaner.hpp"
#include "mouse.hpp"


#ifndef _SKANER
#define _SKANER

#include "gwindow.hpp"

class Skaner : public GWindow
{
 int Index;
 char file[MAXFILE];
 char ext[MAXEXT];
 Group MyGroup;
public:
 ~Skaner();
  Skaner();

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual int EventHandler(MSG &msg);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);         // apdorosime komandas
private:
  void Griepti(void);
  void SetFile(void);
};
#endif

Skaner :: Skaner()
       :  GWindow(150,140,0,0,GetText(10041),WND_GRAPH | WND_CLOSE_BUTTON)
{
 int Size;
 int Size1;

 MyGroup.AddItem(new GButton(0,25,100,20,GetText(10042),NUSKANUOTI));
 MyGroup.AddItem(new GButton(110,25,100,20,GetText(10043),ITEM_CLOSE));
 MyGroup.AddItem(new GInput(110,0,12,FileNameMask,CHANGE_FILE_MASK));

 Index = 0;
 Size = TextMaxLen(10040,10044,0) + 10;
 Size1 = TextMaxLen(10045,0)+28;
 if(Size < Size1)
  Size=Size1;
 Size = Size * SmallFontTable[1] + 20;
 SetX((GraphMaxX+1-Size)/2);
 SetDXDY(Size,95);

 SetFile();
// Show();
}

Skaner :: ~Skaner()
{
}

#pragma argsused
void Skaner :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 char str[MAXFILE+MAXEXT];

 Bar(x,y,dx,dy,GRAY_11);
 MyGroup.SetXY(x + dx / 2 - 105,y + dy - 50);
 MyGroup.Show();

 SetColor(_BLACK);
 SetGroundColor(GRAY_11);
 if(Index)
 {
  OutText(x + 10,y + 5,GetText(10040));
  sprintf(str,"%s%s",file,ext);
  OutText(x + dx - 13 * SmallFontTable[1],y + 5,str);
 }
 OutText(x + 10,y + 25,GetText(10044));
 sprintf(str,"%i",Index);
 OutText(x + dx - 75,y + 25,str);
 OutText(x + 10,y + 45,GetText(10045));
}

int Skaner :: EventHandler(MSG &msg)
{
 int i;

 i = GWindow :: EventHandler(msg);
 if(MyGroup.EventHandler(msg))
  i ++;
return i;
}

ClassType Skaner :: isA()
{
 return _Skaner;
}

int Skaner :: Command(MSG &msg)
{
 GInput *gi;

 switch(msg.Cmd)
  {
   case NUSKANUOTI:
        Griepti();
        return 1;
   case CHANGE_FILE_MASK:
        gi = (GInput *)MyGroup.GetItem(2);
        strcpy(FileNameMask,gi->GetItem());
        SetFile();
        WndDraw();
        return 1;
  }
return GWindow :: Command(msg);
}

void Skaner :: Griepti(void)
{
 int i;
 int done;
 int trigger = 0;
 char *Place;
 char huge *pict;
 char Path[MAXPATH];
 char drive[MAXDRIVE];
 char dir[MAXDIR];
 long MHandler;
 struct ffblk ffblk;

 pict = (char huge*)farmalloc(512L*512L);
 if(pict == 0L)
  {
   SendMSGCmd(OUT_OF_MEMORY);
   return ;
  }
 MHandler = MAlloc(512L * 512L);
 graber((unsigned char huge *)pict);
 MWrite(MHandler,pict);
 farfree(pict);
 GetImagesName(FileNameMask,Path);
 fnsplit(Path,drive,dir,file,ext);
 Place = strstr(file,"*");
 if(Place == 0L)
  SendMSGCmd(ITEM_ACTIVE,Register(new Warning(15)));
 else
  {
   for(i = '0';i <= '9' && trigger == 0;i++)
    {
     Place[0] = i;
     fnmerge(Path,drive,dir,file,".*");
     done = findfirst(Path,&ffblk,0);
     if(done)
      trigger = 1;
     while (!done)
     {
      if(!FilesFilter(ffblk.ff_name))
      {
       trigger = 1;
       break;
      }
      done = findnext(&ffblk);
     }
    }
   for(i = 'a';i <= 'z' && trigger == 0;i++)
    {
     Place[0] = i;
     fnmerge(Path,drive,dir,file,".*");
     done = findfirst(Path,&ffblk,0);
     if(done)
      trigger = 1;
     while (!done)
     {
      if(!FilesFilter(ffblk.ff_name))
      {
       trigger = 1;
       break;
      }
      done = findnext(&ffblk);
     }
    }
   Place = strstr(ext,"*");
   if(Place != 0L)
    {
     Place[1]=0;
     if(stricmp(ext,".*")==0)
      strcpy(ext,GetDefaultExt());
    }
   fnmerge(Path,drive,dir,file,ext);
   SetMouseShape(CLOCK);
   if(WriteImage(Path,MHandler,512,512))
    Register(new Warning(10060));
   else
    Index ++;
   SetMouseShape(ARROW);
   fnsplit(Path,drive,dir,file,ext);
   WndDraw();
  }
 MFree(MHandler);
}

void Skaner :: SetFile(void)
{
 char drive[MAXDRIVE];
 char dir[MAXDIR];

 fnsplit(FileNameMask,drive,dir,file,ext);
}
