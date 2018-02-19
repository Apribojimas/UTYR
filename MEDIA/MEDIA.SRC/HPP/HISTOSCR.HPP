#ifndef _HISTOSCROLLER
#define _HISTOSCROLLER

#include "taipne.hpp"

class HistoScroller : public Taip_Ne
{
 GScroll Scroll;
public:
 ~HistoScroller();
  HistoScroller(int SendMSG_ok,int SendMSG_cancel,int Sendadr,int Textnr,
                int WndName,int ScrollScale = 100);

  virtual int EventHandler(MSG &msg);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();

protected:
  virtual int Command(MSG &msg);

private:
  void DisplayInfo(void);
};
#endif
