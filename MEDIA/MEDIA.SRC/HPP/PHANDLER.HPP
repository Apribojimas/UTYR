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
