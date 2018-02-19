#include <alloc.h>
#include <dos.h>
#include <stdio.h>
#include "gframe.hpp"
#include "graph.hpp"
#include "mm.hpp"
#include "mminfo.hpp"
#include "proto.hpp"
#include "vcmd.hpp"
#include "mminfo.hpp"

long ConventionFreeMemorySize;

#define SIZE_X     250
#define SIZE_Y     310

int isSystemInfo = 0;

#ifndef _MEMMANINFO
#define _MEMMANINFO

#include "gwindow.hpp"

class MemManInfo : public GWindow
{
 char huge *EatMem;
public:
 ~MemManInfo();
  MemManInfo();

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);         // apdorosime komandas
private:
  void DisplayTaskInfo(void);
};
#endif

MemManInfo :: MemManInfo()
           :  GWindow(10,480 - SIZE_Y - 40,SIZE_X,SIZE_Y,"System info",WND_CLOSE_BUTTON,0,0)
{
 EatMem = 0;
 AddMenuItem(new GRadioButton(0,0,100,20,"~Eat mem",EAT_MEM));

 isSystemInfo ++;
}

MemManInfo :: ~MemManInfo()
{
 isSystemInfo --;

 if(EatMem != 0L)
  farfree(EatMem);
}

#pragma argsused
void MemManInfo :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 long ExpAllocSize;
 long ExpFreeSize;
 long ExtAllocSize;
 long ExtFreeSize;
 long DiskAllocSize;
 long DiskFreeSize;
 char string[80];

 Bar(x,y,dx,dy,GRAY_9);

 SetColor(_BLACK);
 SetGroundColor(GRAY_9);

 MMInfo(ExpAllocSize,ExpFreeSize,ExtAllocSize,ExtFreeSize,DiskAllocSize,DiskFreeSize);

 sprintf(string,"Type   Size (KB)   Free (KB)");
 OutText(x + 10,y + 10,string,SmallFontTable);

 sprintf(string,"EXP    %-6lu      %-6lu",ExpAllocSize / 1024,ExpFreeSize / 1024);
 OutText(x + 10,y + 30,string,SmallFontTable);

 sprintf(string,"EXT    %-6lu      %-6lu",ExtAllocSize / 1024,ExtFreeSize / 1024);
 OutText(x + 10,y + 50,string,SmallFontTable);

 sprintf(string,"DISK   %-6lu      %-6lu",DiskAllocSize / 1024,DiskFreeSize / 1024);
 OutText(x + 10,y + 70,string,SmallFontTable);

 sprintf(string,"RAM    %-6lu      %-6lu",ConventionFreeMemorySize / 1024,FreeMem() / 1024);
 OutText(x + 10,y + 90,string,SmallFontTable);

 if( farheapcheck() == _HEAPCORRUPT )
  OutText(x + 10,y + 110,"Heap is corrupted." );
 else
  OutText(x + 10,y + 110,"Heap is OK.");

 sprintf(string,"The bigest block : %lu b", Farcoreleft());
 OutText(x + 10,y + 130,string,SmallFontTable);

 DisplayTaskInfo();
}

void MemManInfo :: DisplayTaskInfo(void)
{
 int x = ViewX;
 int y = ViewY;
 int i;
 int count;
 char string[80];

 SetColor(_BLACK);
 SetGroundColor(GRAY_9);

 count = GetFilterCount();
 sprintf(string,"Total tasks: %3i", count);
 OutText(x + 10,y + 150,string,SmallFontTable);

 sprintf(string,"Task nr. Percent");
 OutText(x + 10,y + 170,string,SmallFontTable);

 for(i = 0;i < 6;i ++)
  {
   if(i < count)
    sprintf(string,"%5i     %3i",i + 1,GetFilterPercent(i));
   else
    sprintf(string,"             ");

   OutText(x + 10,y + 190 + i * 20,string,SmallFontTable);
  }
}

ClassType MemManInfo :: isA()
{
 return _MemManInfo;
}

int MemManInfo :: Command(MSG &msg)
{
 long Free;

 switch(msg.Cmd)
  {
   case EAT_MEM:
        Free = farcoreleft();
        if(EatMem != 0L)
         farfree(EatMem);

        Free = farcoreleft() - Free + Free / 2;
        EatMem = (char *)farmalloc(Free);
        WndDraw();
        return 1;
   case TASK_CHANGE_FILTER:
        if(WndActive == WND_ACTIVE)
         DisplayTaskInfo();
        break;
  }

return GWindow :: Command(msg);
}
