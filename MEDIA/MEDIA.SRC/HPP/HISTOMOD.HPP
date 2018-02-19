#ifndef _HISTOMOD
#define _HISTOMOD

#include "taipne.hpp"

class HistoMod : public Taip_Ne
{
 GScroll MinScroll;
 GScroll MaxScroll;

public:
 ~HistoMod();
  HistoMod(int SendMSG_ok,int SendMSG_cancel,int Sendadr);

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
