#ifndef _LUPA
#define _LUPA

#include "geventha.hpp"

class Lupa : public GEventHandler
{
 int OldMouseEvent;        // isimenam Ar mouse visus event praleidzia
 long MHandler;            // padidinto paveikslo handler
 long PictMHandler;        // pradinio paveikslo handler
 int PictureSizeDX;        // pradinio paveikslo dydis
 int PictureSizeDY;
 int LupaSize;             // koks pradinis didinamo paveisklo dydis
 int ReadX;                // kurioje vieto skaitom is paveikslo
 int ReadY;
 int HScroll;           // scroll bar postumis
 int VScroll;
 long ShadowHandler;

public:
 ~Lupa();
  Lupa(int hScroll,int vScroll,char *wndname);

  virtual void Show();
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
  virtual int Keyboard(MSG &msg);        // klaviaturos
protected:
  virtual void DisplayFragmentInfo(void);
  virtual void BeginMark(int x,int y);
  virtual void EndMark(void);
  virtual void MoveMark(int x,int y);
  void Didinti(int x,int y);
  void HideShadow(int x,int y);
  void ShowShadow(int x,int y);
};
#endif

