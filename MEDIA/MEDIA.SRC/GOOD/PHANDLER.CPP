#include <string.h>
#include "proto.hpp"
#include "define.hpp"
#include "phandler.hpp"

#ifndef PICTURE_HANDLER
#define PICTURE_HANDLER

#include "object.hpp"
#include "mm.hpp"

class PictureHandler : public Object
{
public:
 int Size;            // ir jo dydis pagal dx asi
 long MHandler;       // tikras paveiksliukas
 long MHandler_640;
 long MHandler_800;
 long MHandler_1024;
 int Register[3];    // filtro reg numeris
 char *String;

public:
 ~PictureHandler();
  PictureHandler(long mhandler = ERROR_HANDLER,int size = 0,char *str = "");
// reikalinga Object
  virtual ClassType isA();
};
#endif

PictureHandler :: PictureHandler(long mhandler,int size,char *str)
{
 MHandler = mhandler;
 Size = size;
 MHandler_640 = ERROR_HANDLER;
 MHandler_800 = ERROR_HANDLER;
 MHandler_1024 = ERROR_HANDLER;
 Register[0] = 0;
 Register[1] = 0;
 Register[2] = 0;
 String = new char[strlen(str) + 1];
 if(String)
  strcpy(String,str);
}

PictureHandler :: ~PictureHandler()
{
 int j;
 for(j = 0;j < 3;j ++)
  if(Register[j])
   SendMSGCmd(TERMINATE_FILTER,0,Register[j]);

 if(String)
  delete String;
 if(MHandler != ERROR_HANDLER)
  MFree(MHandler);
 if(MHandler_640 != ERROR_HANDLER)
  MFree(MHandler_640);
 if(MHandler_800 != ERROR_HANDLER)
  MFree(MHandler_800);
 if(MHandler_1024 != ERROR_HANDLER)
  MFree(MHandler_1024);
}

ClassType PictureHandler :: isA()
{
 return _PictureHandler;
}
