#ifndef _FRAGMENT
#define _FRAGMENT

#include "greadbmp.hpp"
#include "frgroup.hpp"
#include "calstr.hpp"

class Fragment : public GReadBMP
{
 int isKalkuliatorius;
 int ScrollX;
 int ScrollY;
 int CurrentMenuFill;
 int FragmentIndex;
 CalStruct *CStruct;
 FragmentGroup MyGroup;
public:
 ~Fragment();
  Fragment(char *wndname = "",char *filemask = "*.*");
  Fragment(char *wndname = "",long mhandler,int pictsizedx,int pictsizedy);

  int isFragmentOK(void);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual int  EventHandler(MSG &msg);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);        // apdorosime komandas
  virtual int Keyboard(MSG &msg);       // klaviaturos
private:
  void FillMenu(int i);
  void DeleteFragment(int fragment_nr);
  long FillSaveFile(void);
  int CalculateLine(long *mhandler);
  int ifHaveFiltr(void);
};
#endif
