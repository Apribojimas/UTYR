#ifndef _GREADBMP
#define _GREADBMP

#include "gwindow.hpp"

class GReadBMP : public GWindow
{
 int isInit;
 int GFileRegisterNumber;
 char FileMask[14];
 long PalHandler;
protected:
 int PictureSizeDX;
 int PictureSizeDY;
 long MHandler;
public:
 ~GReadBMP();
  GReadBMP(char *wndname = "",char *filemask = "*.*");

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  void SetFileMask(char *filemask);
  void SetInitOK(void);
  virtual ClassType isA();
protected:
  virtual int Command(MSG &msg);         // apdorosime komandas
  virtual int Keyboard(MSG &msg);        // klaviaturos
private:
  void SetMaxViewPort(void);
};
#endif
