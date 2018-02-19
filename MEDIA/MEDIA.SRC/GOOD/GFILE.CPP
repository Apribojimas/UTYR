#include <bios.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <dir.h>
#include <stdlib.h>
#include "graph.hpp"
#include "mouse.hpp"
#include "gettext.hpp"
#include "define.hpp"
#include "proto.hpp"
#include "mm.hpp"
#include "keys.h"
#include "gfile.hpp"
#include "ginput.hpp"
#include "grollerd.hpp"
#include "images.hpp"

void Heap(char far *record);

typedef int (*fptr)(const void*, const void*);
int SortEXT(const GRollerData **p1, const GRollerData **p2);
int SortNAME(const GRollerData **p1, const GRollerData **p2);

#define BUTTON_CANCEL 0
#define BUTTON_OK     1
#define FILES_MASK    2
#define FILES         3
#define DIRECTORS     4
#define DISK          5


#ifndef _GFILE
#define _GFILE

#include "groller.hpp"
#include "gwindow.hpp"

class GFile : public GWindow
{
 int SendAdr;
 int GFileType;
 char FileMask[14];
 char *Path;
 Group MyGroup;
public:
 ~GFile();
  GFile(int x = 0,int y = 0,int adr = 0,int type = READ);

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual int  EventHandler(MSG &msg);
  void SetFileMask(char *filemask = "*.*");
  void SetPath(char *path = "");
  void FillGFile(void);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Keyboard(MSG &msg);
  virtual int Command(MSG &msg);        // apdorosime komandas

private:
  void FillFiles(void);
  void FillDirectors(void);
  void FillDisks(void);
  void MarkActiveItem(int i);
  void OutSplitPath(void);
};
#endif


GFile :: GFile(int x,int y,int adr,int type)
      :  GWindow(x,y,400,200,"",WND_GRAPH),
         MyGroup(x,y)
{
 char buffer[MAX_PATH];

 SendAdr = adr;
 GFileType = type;
 Path = 0L;
 getcwd(buffer, MAXPATH);
 SetPath(buffer);

 if(GFileType == READ)
  {
   SetWndName(GetText(4));
   SetFileMask("*.*");
  }
 else
  {
   SetWndName(GetText(8));
   SetFileMask("");
  }

// FillGFile();
}

GFile :: ~GFile()
{
 if(Path != 0L)
  delete Path;
}

ClassType GFile :: isA()
{
 return _GFile;
}

void GFile :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 SetColor(_BLACK);
 SetGroundColor(GRAY_8);
 Bar(x,y,dx,dy,GRAY_8);
 OutText(x + 15,y + 10,GetText(5));
 OutText(x + 155,y + 10,GetText(6));
 OutText(x + 310,y + 10,GetText(7));

 MarkActiveItem(MyGroup.GetActiveItem());
 OutSplitPath();
 MyGroup.SetXY(x,y);
 MyGroup.Show();
 vscroll++;
 hscroll++;
}

void GFile :: SetPath(char *path)
{
 if(Path != 0L)
  delete Path;

 Path = new char [strlen(path) + 1];
 if(Path != 0L)
  {
   strcpy(Path,path);
   strlwr(Path);
  }
}

void GFile :: SetFileMask(char *filemask)
{
 memcpy(FileMask,filemask,14);
}

void GFile :: FillGFile(void)
{
 int i;

 SetMouseShape(CLOCK);
 i = MyGroup.GetActiveItem();
 MyGroup.NewGroup();
 MyGroup + new GButton(288,170,100,20,GetText(2),ITEM_CANCEL);
 MyGroup + new GButton(150,170,100,20,GetText(1),ITEM_OK);
 MyGroup + new GInput(10,170,13,FileMask,FILE_MASK);
 FillFiles();
 FillDirectors();
 FillDisks();
 MyGroup.SetActiveItem(i);
 SetMouseShape(ARROW);
}

void GFile :: FillFiles(void)
{
 int done;
 char *path;
 GRoller *gr;
 struct ffblk ffblk;
 Bag *HBag;

 if(GFileType == READ)
  gr = new GRoller(10,55,13,6,ITEM_OK,RegisterNumber);
 else
  gr = new GRoller(10,55,13,6,EMPTY,RegisterNumber);

 if(gr == 0L)
  return;
 path = new char [strlen(Path) + 14];
 if(path == 0L)
  {
   delete gr;
   return;
  }
 sprintf(path,"%s\\%s",Path,FileMask);
 done = findfirst(path,&ffblk,0);
 delete path;

 HBag = gr->ReturnBagPtr();
 while (!done)
  {
   if(FilesFilter(ffblk.ff_name))
   {
    Strlwr(ffblk.ff_name);
    gr->AddString(ffblk.ff_name);
   }
   done = findnext(&ffblk);
  }
 qsort(HBag->Array,HBag->GetBagSize(),sizeof(GRollerData*),fptr(SortEXT));
 MyGroup.AddItem((Object *)gr);
}

void GFile :: FillDirectors(void)
{
 int done;
 char *path;
 GRoller *gr;
 struct ffblk ffblk;
 Bag *HBag;

 gr = new GRoller(150,55,15,6,FILE_DIRECTORY,RegisterNumber);
 if(gr == 0L)
  return;
 path = new char [strlen(Path) + 14];
 if(path == 0L)
  {
   delete gr;
   return;
  }
 sprintf(path,"%s\\%s",Path,"*.*");
 done = findfirst(path,&ffblk,FA_DIREC);
 delete path;

 HBag = gr->ReturnBagPtr();
 while (!done)
  {
   if((ffblk.ff_attrib & FA_DIREC) &&
     !(ffblk.ff_name[0] == '.' && ffblk.ff_name[1] == 0))
    {
     Strlwr(ffblk.ff_name);
     gr->AddString(ffblk.ff_name);
    }
   done = findnext(&ffblk);
  }
 qsort(HBag->Array,HBag->GetBagSize(),sizeof(GRollerData*),fptr(SortNAME));
 MyGroup.AddItem((Object *)gr);
}

void GFile :: FillDisks(void)
{
 int i;
 GRoller *gr;
 int CheckDisk;
 int CurrentDisk;
 char str[20];

 gr = new GRoller(305,55,8,6,FILE_DISK,RegisterNumber);
 if(gr == 0L)
  return;

 outportb(0x70,0x10);
 CheckDisk = inportb(0x71);
 if(CheckDisk & 0x0f)
  {
   gr->AddString("a:");
   if(strstr(Path,"a:") != 0L)
    gr->SetActiveItem();
  }
 if(CheckDisk & 0xf0)
  {
   if(CheckDisk & 0x0f)
    {
     gr->AddString("b:");
     if(strstr(Path,"b:") != 0L)
      gr->SetActiveItem();
    }
   else
    {
     gr->AddString("a:");
     if(strstr(Path,"a:") != 0L)
      gr->SetActiveItem();
    }
  }

 CurrentDisk = getdisk();
 for(i = 2;i < 26;i ++)
  {
   setdisk(i);
   if(i == getdisk())
    {
     sprintf(str,"%c:",i + 'a');
     gr->AddString(str);
     if(strstr(Path,str) != 0L)
      gr->SetActiveItem();
    }
  }
 setdisk(CurrentDisk);
 MyGroup.AddItem((Object *)gr);
}

int GFile :: EventHandler(MSG &msg)
{
 int i = 0;
 int j;
 int MemGroupActiveItem;

 Heap("GFile :: EventHandler 1");

 if(WndEvent == 0)
  {
   if(GWindow :: EventHandler(msg))
    i ++;
   MemGroupActiveItem = MyGroup.GetActiveItem();
   if((j = MyGroup.EventHandler(msg)) != 0)
    {
     OutSplitPath();
     i ++;
    }
   if(MemGroupActiveItem != MyGroup.GetActiveItem() && j != 0)
    {
     MarkActiveItem(MemGroupActiveItem);
     MarkActiveItem(MyGroup.GetActiveItem());
    }
  }
 else
  {
   if(GWindow :: EventHandler(msg))
    i ++;
  }
 Heap("GFile :: EventHandler 2");
return i;
}

int GFile :: Command(MSG &msg)
{
 int i;
 long MHandler;
 GRoller *gr = 0L;
 GInput *gi = 0L;
 char TmpPath[MAX_PATH];

 i = GWindow :: Command(msg);

  Heap("GFile :: Command 1");

 switch(msg.Cmd)
  {
   case ITEM_CANCEL:
        SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        SendMSGCmd(FILE_CANCEL,SendAdr);
        return 1;
   case ITEM_OK:
        if(GFileType == READ)
         {
          gr = (GRoller *)MyGroup.GetItem(FILES);
          if(gr == 0L)
           return 1;
          sprintf(TmpPath,"%s\\%s",Path,gr->GetItem());
         }
        else
         {
          gi = (GInput *)MyGroup.GetItem(FILES_MASK);
          if(gi == 0L)
           return 1;
          sprintf(TmpPath,"%s\\%s",Path,gi->GetItem());
         }
        MHandler = MAlloc(MAX_PATH);
        MWrite(MHandler,TmpPath);
        SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        if(GFileType == READ)
         SendMSGCmd(FILE_READ_OK,SendAdr,MHandler);
        else
         SendMSGCmd(FILE_WRITE_OK,SendAdr,MHandler);
        return 1;
   case FILE_MASK:
        gi = (GInput *)MyGroup.GetItem(FILES_MASK);
        if(gi == 0L)
         return 1;
        SetFileMask(gi->GetItem());
        FillGFile();
	MyGroup.Show();
        return 1;
   case FILE_DISK:
        gr = (GRoller *)MyGroup.GetItem(DISK);
        if(gr == 0L)
         return 1;
        if(getcurdir(*gr->GetItem() - 'a' + 1,TmpPath))
         sprintf(Path,"%s",gr->GetItem());
        else
         {
          if(strlen(TmpPath))
           sprintf(Path,"%s\\%s",gr->GetItem(),TmpPath);
          else
           sprintf(Path,"%s",gr->GetItem());
         }
        FillGFile();
	MyGroup.Show();
        OutSplitPath();
        return 1;
   case FILE_DIRECTORY:
        gr = (GRoller *)MyGroup.GetItem(DIRECTORS);
        if(gr == 0L)
         return 1;
        if(strstr(gr->GetItem(),"..") != 0L)
         {
          for(i = strlen(Path);i >= 0;i --)
           if(Path[i] == '\\')
            {
             Path[i] = 0;
             break;
            }
         }
        else
         {
          sprintf(TmpPath,"%s\\%s",Path,gr->GetItem());
          SetPath(TmpPath);
         }
        FillGFile();
	MyGroup.Show();
        OutSplitPath();
        return 1;
  }

  Heap("GFile :: Command 2");

return i;
}

int GFile :: Keyboard(MSG &msg)
{
 int i = 0;

 switch(msg.Key)
  {
   case F1:
        RunHelp(5);
        return 1;
   case TAB:
   case SHIFT_TAB:
        i ++;
        break;
   case ESC:
        SendMSGCmd(ITEM_CANCEL,RegisterNumber);
        break;
  }

 if(GWindow :: Keyboard(msg))
  i ++;

return i;
}

void GFile :: MarkActiveItem(int i)
{
 int x = X + 5;
 int y = Y + 29;

 SetWriteMode(XOR_PUT);
 SetColor(GRAY_0);
 switch(i)
  {
   case BUTTON_CANCEL:
        Rectangle(x + 286,y + 168,104,24);
        break;
   case BUTTON_OK:
        Rectangle(x + 148,y + 168,104,24);
        break;
   case FILES_MASK:
        break;
   case FILES:
        Rectangle(x + 8,y + 53,128,104);
        break;
   case DIRECTORS:
        Rectangle(x + 148,y + 53,144,104);
        break;
   case DISK:
        Rectangle(x + 303,y + 53,88,104);
        break;
  }
 SetWriteMode(COPY_PUT);
}


void GFile :: OutSplitPath(void)
{
 int x = X + 5;
 int y = Y + 29;
 GRoller *gr;
 char TmpPath[MAX_PATH];

// isvedam failus
 SetGroundColor(GRAY_8);
 if(MyGroup.GetActiveItem() == FILES)
  SetColor(_WHITE);
 else
  SetColor(_BLACK);
 gr = (GRoller *)MyGroup.GetItem(FILES);
 if(gr != 0L)
  sprintf(TmpPath,"%-13s",gr->GetItem());
 else
  sprintf(TmpPath,"%-13s"," ");
 Rectangle(x + 13,y + 28,108,20);
 OutText(x + 15,y + 30,TmpPath);

// isvedam directorijas
 if(MyGroup.GetActiveItem() == DIRECTORS)
  SetColor(_WHITE);
 else
  SetColor(_BLACK);
/*
 gr = (GRoller *)MyGroup.GetItem(DIRECTORS);
 if(gr != 0L)
  sprintf(TmpPath,"%-15s",gr->GetItem());
 else
  sprintf(TmpPath,"%-15s"," ");
*/
////////////
 int i;
 i = strlen(Path);
 if(i>15)
  {
   sprintf(TmpPath,"%-15.15s",&Path[i - 14]);
/*    Hariu
   for(;i != 0;i --)
    if(TmpPath[i] == '\\')
     {

      break;
     }
*/
  }
 else
  sprintf(TmpPath,"%-15.15s",Path);
//////////////

 Rectangle(x + 153,y + 28,124,20);
 OutText(x + 155,y + 30,TmpPath);

// isvedam diskus
 if(MyGroup.GetActiveItem() == DISK)
  SetColor(_WHITE);
 else
  SetColor(_BLACK);
 gr = (GRoller *)MyGroup.GetItem(DISK);
 if(gr != 0L)
  {
   Rectangle(x + 308,y + 28,68,20);
   OutText(x + 310,y + 30,gr->GetItem());
  }
}