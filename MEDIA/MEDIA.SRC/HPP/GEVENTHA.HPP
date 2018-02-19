#ifndef _GEVENTHANDLER
#define _GEVENTHANDLER

#include "msgfilte.hpp"
#include "struct.hpp"
#include "shape.hpp"

class GEventHandler : public MSGFilter
{
protected:
 int WndType;       // isimenam koks yra langas
 int WndEvent;      // isimenam savo ivyki
 int WndActive;     // ar aktyvus langas
 char *WndName;

 int ViewX;
 int ViewY;
 int ViewDX;
 int ViewDY;
public:
 int WndStatus;     // isimenam savo busena
public:
 ~GEventHandler();
  GEventHandler(int x = 0,int y = 0,int dx = 0,int dy = 0);

  virtual int EventHandler(MSG &msg);
  char *GetWndName(void);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Keyboard(MSG &msg);        // apdorosime klavisus
  virtual int Command(MSG &msg);         // apdorosime komandas
};
#endif
