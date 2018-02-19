#include "graph.hpp"
#include "gdefine.hpp"
#include "geventha.hpp"

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

int EventHandler(Object *Obj,MSG &msg)
{
 GEventHandler *eh = (GEventHandler *)Obj;
return eh->EventHandler(msg);
}

GEventHandler :: GEventHandler(int x,int y,int dx,int dy)
              :  MSGFilter(x,y,dx,dy)
{
 WndStatus = WND_NORMAL;
 WndActive = WND_PASIVE;
 WndType   = WND_GRAPH;
 WndName   = 0L;

 ViewX = 0;
 ViewY = 0;
 ViewDX = 0;
 ViewDY = 0;
}

GEventHandler :: ~GEventHandler()
{
}

int GEventHandler :: EventHandler(MSG &msg)
{
 switch (msg.Type)
  {
   case KEYBOARD:
        return Keyboard(msg);
   case MOUSE:
        return Mouse(msg);
   case COMMAND:
        return Command(msg);
  }
return 0;
}

#pragma argsused
int GEventHandler :: Keyboard(MSG &msg)
{
 return 0;
}

#pragma argsused
int GEventHandler :: Mouse(MSG &msg)
{
 return 0;
}

#pragma argsused
int GEventHandler :: Command(MSG &msg)
{
 return 0;
}

ClassType GEventHandler :: isA()
{
 return _GEventHandler;
}

char *GEventHandler :: GetWndName(void)
{
 return WndName;
}
