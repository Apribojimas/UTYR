#ifndef _FRONTO_GRAMA
#define _FRONTO_GRAMA

#define GramaCount 11
#include "gwindow.hpp"

class FrontoGrama : public GWindow
{
 int Size;
 unsigned char *Grama[GramaCount];
 unsigned char *DisplayGrama;
 unsigned int Max;
 unsigned int Min;
 int ZemRiba;
 int VirRiba;
 int Rodykle;
 int SenaRodykle;

 long FragmentIndex;
 char *SWndName;
public:
 ~FrontoGrama();
  FrontoGrama(long *MHandler,int size,long fragregisternumber,int fragindex);

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);

  virtual ClassType isA();
private:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
  virtual int Keyboard(MSG &msg);        // klaviaturos

protected:
  virtual void DisplayInfo(void);
  void FillGrama(long *MHandler);
  void FillGramaAverage(void);
  void ShowRodykleShape(char str);
  void MoveRodykle(void);
  void FullWndName(int fragmentnumber);
  void SaveWndName(char *wndname);
};
#endif
