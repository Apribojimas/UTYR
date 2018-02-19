#include "gettext.hpp"
#include "proto.hpp"
#include "define.hpp"
#include "keys.h"
#include "help.hpp"

int HelpIndex = 0;

#ifndef HELP
#define HELP

#include "viewtext.hpp"

class Help : public ViewText
{

public:
 ~Help();
  Help();

// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Keyboard(MSG &msg);       // klaviaturos
};
#endif

Help :: Help()
     :  ViewText(100,100,250,150,GetText(11))
{
 int size;
 long mhandler;

 mhandler = GetHelp(HelpIndex,size);
 SetTextHandler(mhandler,size);
}

Help :: ~Help()
{
}

ClassType Help :: isA()
{
 return _Help;
}

int Help :: Keyboard(MSG &msg)
{
 switch(msg.Key)
  {
   case F1:
        RunHelp(2);
        return 1;
  }

return ViewText :: Keyboard(msg);
}

void SetHelpIndex(int index)
{
 HelpIndex = index;
}

int GetHelpIndex(void)
{
 return HelpIndex;
}

void RunHelp(int index)
{
 int i;

 i = HelpIndex;
 HelpIndex = index;
 Register(new Help);
// SendMSGCmd(ITEM_STATUS,Register(new Help));
 HelpIndex = i;
}
