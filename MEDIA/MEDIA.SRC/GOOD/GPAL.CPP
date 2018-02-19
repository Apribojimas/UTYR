#include "graph.hpp"
#include "mm.hpp"
#include "gpal.hpp"

#ifndef _GPALETTE
#define _GPALETTE

#include "gwindow.hpp"

class GPalette : public GWindow
{
 long MHandler;
public:
 ~GPalette();
  GPalette(long mhandler);

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
//  virtual int Mouse(MSG &msg);           // mouse eventai
//  virtual int Command(MSG &msg);         // apdorosime komandas
//  virtual int Keyboard(MSG &msg);        // klaviaturos
};
#endif

GPalette :: GPalette(long mhandler)
         :  GWindow(100,30,380,200,"Palette",WND_GRAPH | WND_CLOSE_BUTTON)
{
 char str[768];

 MHandler = MAlloc(768);
 MRead(mhandler,str);
 MWrite(MHandler,str);
}

GPalette :: ~GPalette()
{
 if(MHandler != ERROR_HANDLER)
  MFree(MHandler);
}

#pragma argsused
void GPalette :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 Bar(x,y,dx,dy,GRAY_5);
}

ClassType GPalette :: isA()
{
 return _GPalette;
}
