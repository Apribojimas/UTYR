#ifndef _HISTOGRAMA
#define _HISTOGRAMA

#include "gwindow.hpp"
#include "drawhist.hpp"

class Histo : public GWindow
{
 int DestroyIndex;
 long MHandler;
 int Rodykle;
 int SenaRodykle;
 int ZemRiba;
 int VirRiba;
 Histogramma DrawHisto;
 int HistoNumber;
 long FragmentIndex;
 char *SWndName;
public:
 ~Histo();
  Histo(char *wndname,int destroyindex,long mhandler,int histonumber,long fragregisternumber,int fragindex);

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
  virtual int Keyboard(MSG &msg);        // klaviaturos
private:
  virtual void DisplayInfo(void);
  void ShowRodykleShape(char str);
  void MoveRodykle(void);
  void FullWndName(int fragmentnumber);
  void SaveWndName(char *wndname);
};
#endif
