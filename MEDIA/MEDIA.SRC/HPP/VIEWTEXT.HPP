#ifndef VIEWTEXT
#define VIEWTEXT

#include "gwindow.hpp"

class ViewText : public GWindow
{
 long TextHandler;
 long InfoHandler;
 long Size;
 unsigned Lines;
 unsigned MaxLine;
public:
 ~ViewText();
  ViewText(int x = 0,int y = 0,int dx = 200,int dy = 200,char *name = "",
           int windowtype = WND_TEXT | WND_CLOSE_BUTTON | WND_MAX_BUTTON,
           int hscale = 1,int vscale = 1,int maxdx = 600,int maxdy = 400);

  void SetTextHandler(long mhandler,long size);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Keyboard(MSG &msg);       // klaviaturos
private:
  void TextAnalize(void);
  void StringForming(char *str,unsigned size,int wnd_dx,unsigned str_shift);
};
#endif
