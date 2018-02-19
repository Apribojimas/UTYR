#include <alloc.h>
#include <mem.h>

#include "graph.hpp"
#include "mm.hpp"
#include "images.hpp"
#include "gettext.hpp"

long unsigned GroundHandler = ERROR_HANDLER;
int GroundDX = 0,GroundDY = 0;
extern char desktopPal[48];

void InitGround(void)
{
 char pal[768];
 char *buf;
 int i,j;

 if(GetInfo(GetDesktopGroundImage(),GroundDX,GroundDY))
  return;
 if(GetPalette(GetDesktopGroundImage(),pal))
  return;
 memcpy(desktopPal,pal,48);

 GroundHandler = MAlloc((long)GroundDX*GroundDY);
 if(ReadImage(GetDesktopGroundImage(),GroundHandler) || GroundDX == 0 || GroundDY == 0)
  {
   MFree(GroundHandler);
   GroundHandler = ERROR_HANDLER;
   return;
  };

 buf = (char*)malloc(GroundDX);
 MLock(GroundHandler);

 for(i = 0;i < GroundDY;i ++)
  {
   MRead(GroundHandler,buf,(long)i*GroundDX,GroundDX);
   for(j = 0;j < GroundDX;j ++)
    buf[j] += (GRAY_0 - 16);
   MWrite(GroundHandler,buf,(long)i*GroundDX,GroundDX);
  }
 MUnLock(GroundHandler);
 free(buf);
}

void CloseGround(void)
{
 if(GroundHandler != ERROR_HANDLER)
  MFree(GroundHandler);
}