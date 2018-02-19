#ifndef _GINPUT
#define _GINPUT

#include "gvmode.hpp"

class GInput : public GVideoMode
{
 int SendCmd;
 int SendAdr;
 int StringSize;
 int CurrentPlace;
public:
 ~GInput();
  GInput(int x = 0,int y = 0,int strsize = 0,char *string = "",int cmd = 0,int adr = 0);

  virtual void Show(void);
  char *GetItem(void);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Keyboard(MSG &msg);        // apdorosime klavisus
  virtual int Command(MSG &msg);         // apdorosime komandas
};
#endif
