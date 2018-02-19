#include <stdarg.h>
#include "gdefine.hpp"
#include "msgfdata.hpp"
#include "define.hpp"
#include "msgfilte.hpp"


#ifndef _MSGFILTER
#define _MSGFILTER

#include "bag.hpp"
#include "grec.hpp"
#include "struct.hpp"


class MSGFilter : public GRectangle
{
 Bag MouseBag;
 Bag KeyboardBag;
 Bag CommandBag;

 int MouseBagFlag;
 int KeyboardBagFlag;
 int CommandBagFlag;

public:
 ~MSGFilter();
  MSGFilter(int x = 0,int y = 0,int dx = 0,int dy = 0);

  void ClearAllMSG(void);
  void ClearMouseMSG(void);
  void ClearKeyboardMSG(void);
  void ClearCommandMSG(void);
  void SetMSGFilter(int i = 1);
  void SetMouseMSGFilter(int i = 1);
  void SetKeyboardMSGFilter(int i = 1);
  void SetCommandMSGFilter(int i = 1);
  void SetMouseMSG(int i,...);
  void SetKeyboardMSG(int i,...);
  void SetCommandMSG(int i,...);
  int isMyMSG(MSG &msg);
  int isMyMouseMSG(MSG &msg);
  int isMyKeyboardMSG(MSG &msg);
  int isMyCommandMSG(MSG &msg);

  virtual ClassType isA();
};
#endif

MSGFilter :: MSGFilter(int x,int y,int dx,int dy)
          :  GRectangle(x,y,dx,dy),
             MouseBag(DELETE),
             KeyboardBag(DELETE),
             CommandBag(DELETE)
{
 MouseBagFlag = ENABLE_ALL_MSG;
 KeyboardBagFlag = ENABLE_ALL_MSG;
 CommandBagFlag = ENABLE_ALL_MSG;
}

MSGFilter :: ~MSGFilter()
{

}

void MSGFilter :: ClearAllMSG(void)
{
 ClearMouseMSG();
 ClearKeyboardMSG();
 ClearCommandMSG();
}

void MSGFilter :: ClearMouseMSG(void)
{
 while(MouseBag.GetBagSize())
  MouseBag - 0;
}

void MSGFilter :: ClearKeyboardMSG(void)
{
 while(KeyboardBag.GetBagSize())
  KeyboardBag - 0;
}

void MSGFilter :: ClearCommandMSG(void)
{
 while(CommandBag.GetBagSize())
  CommandBag - 0;
}

void MSGFilter :: SetMSGFilter(int i)
{
 SetMouseMSGFilter(i);
 SetKeyboardMSGFilter(i);
 SetCommandMSGFilter(i);
}

void MSGFilter :: SetMouseMSGFilter(int i)
{
 MouseBagFlag = i;
}

void MSGFilter :: SetKeyboardMSGFilter(int i)
{
 KeyboardBagFlag = i;
}

void MSGFilter :: SetCommandMSGFilter(int i)
{
 CommandBagFlag = i;
}

#pragma argsused
void MSGFilter :: SetMouseMSG(int i,...)
{
 int arg;
 va_list ap;

 va_start(ap, i);

 while ((arg = va_arg(ap,int)) != 0)
  MouseBag + new MSGFilterData(arg);

 va_end(ap);
}

#pragma argsused
void MSGFilter :: SetKeyboardMSG(int i,...)
{
 int arg;
 va_list ap;

 va_start(ap, i);

 while ((arg = va_arg(ap,int)) != 0)
  KeyboardBag + new MSGFilterData(arg);

 va_end(ap);
}

#pragma argsused
void MSGFilter :: SetCommandMSG(int i,...)
{
 int arg;
 va_list ap;

 va_start(ap, i);

 while ((arg = va_arg(ap,int)) != 0)
  CommandBag + new MSGFilterData(arg);

 va_end(ap);
}

int MSGFilter :: isMyMSG(MSG &msg)
{
 switch (msg.Type)
  {
   case KEYBOARD:
        return isMyKeyboardMSG(msg);
   case MOUSE:
        return isMyMouseMSG(msg);
   case COMMAND:
        return isMyCommandMSG(msg);
  }
return 0;
}

int MSGFilter :: isMyMouseMSG(MSG &msg)
{
 int i;
 MSGFilterData *fd;

 if(MouseBagFlag == ENABLE_ALL_MSG)
  return 1;

 for(i = MouseBag.GetBagSize() - 1;i >= 0;i --)
  {
   fd = (MSGFilterData *)MouseBag.GetItem(i);
   if(msg.Mouse & fd->Data)
    return 1;
  }
return 0;
}

int MSGFilter :: isMyKeyboardMSG(MSG &msg)
{
 int i;
 MSGFilterData *fd;

 if(KeyboardBagFlag == ENABLE_ALL_MSG)
  return 1;

 for(i = KeyboardBag.GetBagSize() - 1;i >= 0;i --)
  {
   fd = (MSGFilterData *)KeyboardBag.GetItem(i);
   if(msg.Key == fd->Data)
    return 1;
  }
return 0;
}

int MSGFilter :: isMyCommandMSG(MSG &msg)
{
 int i;
 MSGFilterData *fd;

 if(CommandBagFlag == ENABLE_ALL_MSG)
  return 1;

 for(i = CommandBag.GetBagSize() - 1;i >= 0;i --)
  {
   fd = (MSGFilterData *)CommandBag.GetItem(i);
   if(msg.Cmd == fd->Data)
    return 1;
  }
return 0;
}

ClassType MSGFilter :: isA()
{
 return _MSGFilter;
}
