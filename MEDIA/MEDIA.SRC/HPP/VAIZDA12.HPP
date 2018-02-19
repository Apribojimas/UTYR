#ifndef _VAIZDA_12
#define _VAIZDA_12

#include "gwindow.hpp"
#include "phandler.hpp"

class Vaizda12 : public GWindow
{
 int Size;
 int Mode;
 int GFileRegisterNumber;
 Bag MyBag;

public:
 ~Vaizda12();
  Vaizda12();

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);        // apdorosime komandas
  virtual int Mouse(MSG &msg);          // mouse eventai
  virtual int Keyboard(MSG &msg);       // klaviaturos
private:
  void RunGFile(void);
  void FillMenu(int i);
  int SetSize(void);
  int ifWndDraw(int nr);
  int FindActiveFilter(void);
  void RunNewFilter(void);
  int RunModeFilter(PictureHandler *ph,int mode);  // mode=[0..2]
};
#endif
