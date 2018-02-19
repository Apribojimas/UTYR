#ifndef _CALCULATE
#define _CALCULATE

#include "calfst.hpp"

class Calculate : public CalFirst
{
public:
 ~Calculate();
  Calculate();

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual int EventHandler(MSG &msg);
  virtual void DisplayInfo(int x,int y,int dx);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
  virtual int Keyboard(MSG &msg);        // klaviaturos
private:
  void FillMenu(int i);
  void SetStructViewPort(void);
};
#endif
