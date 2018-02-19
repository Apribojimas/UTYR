#include <string.h>
#include "graph.hpp"
#include "gettext.hpp"
#include "define.hpp"
#include "keys.h"
#include "warning.hpp"


int WarningCounter = 0;

#ifndef WARNING
#define WARNING

#include "gwindow.hpp"

class Warning : public GWindow
{
 char *WarningString;
 GButton Button;
public:
 ~Warning();
  Warning(int TextNr);
  Warning(char *str);

  virtual int EventHandler(MSG &msg);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Keyboard(MSG &msg);       // klaviaturos
private:
  void SetWarningString(char *str);
};
#endif

Warning :: Warning(char *str)
        :  GWindow(200,200,120,70,GetText(9)),
           Button(0,0,100,20,GetText(1),ITEM_CLOSE,0,CR)
{
 WarningCounter ++;
 WarningString = 0L;
 SetWarningString(str);
 Show();
}

Warning :: Warning(int TextNr)
        :  GWindow(200,200,120,70,GetText(9)),
           Button(0,0,100,20,GetText(1),ITEM_CLOSE,0,CR)
{
 WarningCounter ++;
 WarningString = 0L;
 SetWarningString(GetText(TextNr));
 Show();
}

Warning :: ~Warning()
{
 WarningCounter --;
 if(WarningString != 0L)
  delete WarningString;
}

#pragma argsused
void Warning :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 SetColor(GRAY_10);
 Bar(x,y,dx,dy);
 SetColor(_BLACK);
 if(WarningString)
  OutStr(x + dx / 2 - strlen(WarningString) * 4,y + 10,WarningString);
 Button.SetXY(x + dx / 2 - 50,y + dy - 30);
 Button.Show();
}

int Warning :: EventHandler(MSG &msg)
{

 GWindow :: EventHandler(msg);
 Button.EventHandler(msg);

return 1;
}

ClassType Warning :: isA()
{
 return _Warning;
}

int Warning :: Keyboard(MSG &msg)
{
 switch(msg.Key)
  {
   case F1:
        return 1;
  }

return GWindow :: Keyboard(msg);
}

void Warning :: SetWarningString(char *str)
{
 if(WarningString != 0L)
  delete WarningString;

 if(str == 0L)
  return;
 WarningString = new char [strlen(str) + 1];
 strcpy(WarningString,str);
 if(strlen(str) > 15)
  SetDX(strlen(str) * 8 + 20);
}
