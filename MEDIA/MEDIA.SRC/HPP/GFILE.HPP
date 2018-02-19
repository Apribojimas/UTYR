#ifndef _GFILE
#define _GFILE

#include "groller.hpp"
#include "gwindow.hpp"

class GFile : public GWindow
{
 int SendAdr;
 int GFileType;
 char FileMask[14];
 char *Path;
 Group MyGroup;
public:
 ~GFile();
  GFile(int x = 0,int y = 0,int adr = 0,int type = READ);

  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
  virtual int  EventHandler(MSG &msg);
  void SetFileMask(char *filemask = "*.*");
  void SetPath(char *path = "");
  void FillGFile(void);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Keyboard(MSG &msg);
  virtual int Command(MSG &msg);        // apdorosime komandas

private:
  void FillFiles(void);
  void FillDirectors(void);
  void FillDisks(void);
  void MarkActiveItem(int i);
  void OutSplitPath(void);
};
#endif
