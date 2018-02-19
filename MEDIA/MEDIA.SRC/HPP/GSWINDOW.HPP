#ifndef _GSMALLWINDOW
#define _GSMALLWINDOW

#include "gframe.hpp"
#include "gbutton.hpp"

class GSmallWindow : public GFrame
{
 int LocalX;   // reikalinga move operacijai atlikti
 int LocalY;
 int LocalTmpX;
 int LocalTmpY;
 int NormalDX;    // normalaus ekrano dysi
 int NormalDY;
 int ReSizeX;     // isimenam keitimo metu XY dydi
 int ReSizeY;

 GButton *CloseButton;
 GButton *MinButton;
 GButton *MaxButton;
protected:
 int MaxDX;     // isimenam didelio ekrano dydi
 int MaxDY;

public:
 ~GSmallWindow();
  GSmallWindow(int x = 0,int y = 0,int dx = 0,int dy = 0,char *name = "",int windowtype = WND_GRAPH,int maxdx = 580,int maxdy = 440);

  virtual void Show();
  virtual void SetVideoMode(int mode);
  virtual int  EventHandler(MSG &msg);
  virtual void SetWndMaxDXDY(int dx,int dy);
  virtual void SetDXDY(int dx,int dy);
  void SetWndName(char *wndname);

// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);        // apdorosime komandas
  virtual int Mouse(MSG &msg);          // mouse eventai
  virtual int Keyboard(MSG &msg);       // klaviaturos

private:
  int isTitle(int x,int y);     // tikrinam ar titlas
  int isCheckBox(int x,int y);  // patikrina ar Check Box
  void MoveTo(int x,int y);     // pernesime lango 'seseli'
  void WindowMinMax(void);      // procedura su kuria atliekam keitima is normal i big ir atvirksciai
  void WindowBeginMove(int x,int y);   // sios proceduros reikalingos pradeti lango perstumima ir pabaigti
  void WindowEndMove(void);
  void PrivateSetVideoMode(void);
};
#endif
