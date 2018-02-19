#ifndef _GRID
#define _GRID

#include "gwindow.hpp"
#include "calstr.hpp"
#include "point.hpp"

#define KOORDINATES  1
#define TINKLELIS    2

class Grid : public GWindow
{
 int What;
 int Init;
 int MouseEvent;
 float GridX;
 float GridY;
 Point P1;
 Point P2;
 Group MyGroup;
 CalStruct *CStruct;

public:
 ~Grid();
  Grid(int x,int y,CalStruct *cstruct,int what = TINKLELIS);

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual int EventHandler(MSG &msg);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
//  virtual int Keyboard(MSG &msg);        // klaviaturos
private:
  void ShowGrid(int x,int y);
  void DisplayInfo(int x,int y);
  int isCalculateShow(void);
};
#endif
