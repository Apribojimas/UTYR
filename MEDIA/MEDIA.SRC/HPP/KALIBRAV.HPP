#ifndef _KALIBRAVIMAS
#define _KALIBRAVIMAS

#include "gwindow.hpp"
#include "calstr.hpp"
#include "point.hpp"

class Kalibravimas : public GWindow
{
 int Init;
 int MouseEvent;
 Point P1;
 Point P2;
 Group MyGroup;
 CalStruct *CStruct;

public:
 ~Kalibravimas();
  Kalibravimas(int x,int y,CalStruct *cstruct);

  virtual int EventHandler(MSG &msg);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
//  virtual int Keyboard(MSG &msg);        // klaviaturos
private:
  void BeginMove(int x,int y);
  void EndMove(int x,int y);
  void MoveTo(int x,int y);
};
#endif
