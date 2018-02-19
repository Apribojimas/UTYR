#ifndef TAIP_NE
#define TAIP_NE

#include "gwindow.hpp"

class Taip_Ne : public GWindow
{
protected:
 int TextNr;
 int SendMSG_OK;
 int SendMSG_Cancel;
 int SendAdr;
 GMenu MyGroup;
public:
 ~Taip_Ne();
  Taip_Ne(int SendMSG_ok,int SendMSG_cancel,int Sendadr,int Textnr);
  Taip_Ne(int SendMSG_ok,int SendMSG_cancel,int Sendadr,int Textnr,int x,int y,int dx,int dy,char *wndname);

  virtual int EventHandler(MSG &msg);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Keyboard(MSG &msg);       // klaviaturos
  virtual int Command(MSG &msg);
private:
  void SetWarningString(char *str);
  void Init(int SendMSG_ok,int SendMSG_cancel,int Sendadr,int Textnr);
};
#endif
