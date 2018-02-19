#include <string.h>
#include "graph.hpp"
#include "proto.hpp"
#include "mm.hpp"
#include "struct.hpp"
#include "keys.h"
#include "viewtext.hpp"


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

ViewText :: ViewText(int x,int y,int dx,int dy,char *name,int windowtype,int hscale,int vscale,int maxdx,int maxdy)
         :  GWindow(x,y,dx,dy,name,windowtype,hscale,vscale,maxdx,maxdy)
{
 TextHandler = ERROR_HANDLER;
 InfoHandler = ERROR_HANDLER;
 Size = 0;
 Lines = 0;
 MaxLine = 0;
 Show();
}


ViewText :: ~ViewText()
{
 if(TextHandler != ERROR_HANDLER)
  MFree(TextHandler);
 if(InfoHandler != ERROR_HANDLER)
  MFree(InfoHandler);
}

void ViewText :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 int i;
 int LineCount;
 int LetterCount;
 int TextDY;
 char *str;
 struct TextShiftInfo ti;


 if(TextHandler == ERROR_HANDLER || InfoHandler == ERROR_HANDLER)
  {
   Bar(x,y,dx,dy,GRAY_13);
   return;
  }

 LetterCount = dx / CharWidth() + 1;
 if(MaxLine > LetterCount)
  str = new char[MaxLine + 1];
 else
  str = new char[LetterCount + 1];

 if(str == 0L)
  {
   SendMSGCmd(OUT_OF_MEMORY);
   return;
  }

 TextDY = CharHeight();
 LineCount = dy / TextDY + 1;


 if(Lines > LineCount)
  SetMaxPos(Lines - LineCount,VERTICAL);
 else
  {
   vscroll = 0;
   SetMaxPos(0,VERTICAL);
  }

 if(MaxLine > LetterCount)
  SetMaxPos(MaxLine - LetterCount,HORIZANTAL);
 else
  {
   hscroll = 0;
   SetMaxPos(0,HORIZANTAL);
  }

 MLock(InfoHandler);
 MLock(TextHandler);
 SetColor(_BLACK);
 SetGroundColor(GRAY_13);
 for(i = 0;i <= LineCount;i ++)
  {
   if(vscroll + i < Lines)
    {
     MRead(InfoHandler,(char *)&ti,(vscroll + (long)i) * sizeof(TextShiftInfo),sizeof(TextShiftInfo));
     MRead(TextHandler,str,ti.Shift,ti.Size);
     StringForming(str,(unsigned)ti.Size,LetterCount,hscroll);
    }
   else
    StringForming(str,0,LetterCount,0);

   OutBigText(x,y + i * TextDY,str);
  }

 MUnLock(TextHandler);
 MUnLock(InfoHandler);
 delete str;
}

void ViewText :: SetTextHandler(long mhandler,long size)
{
 if(TextHandler != ERROR_HANDLER)
  MFree(TextHandler);
 TextHandler = mhandler;
 Size = size;
 TextAnalize();
 SetPos(0,VERTICAL);
 SetPos(0,HORIZANTAL);
}

void ViewText :: TextAnalize(void)
{
 long size;
 long shift;
 long ishift;
 unsigned counter;
 char str;
 struct TextShiftInfo ti;


 if(TextHandler == ERROR_HANDLER)
  return;

 MLock(TextHandler);
 for(shift = 0,counter = 0;shift < Size;shift ++)
  {
   MRead(TextHandler,&str,shift,1);
   if(str == '\n')
    counter ++;
  }

 Lines = counter + 1;
 if(InfoHandler != ERROR_HANDLER)
  MFree(InfoHandler);


 size = (long)Lines * sizeof(TextShiftInfo);
 InfoHandler = MAlloc(size);
 if(InfoHandler == ERROR_HANDLER)
  {
   MUnLock(TextHandler);
   SendMSGCmd(OUT_OF_MEMORY);
   return;
  }

 MLock(InfoHandler);
 ti.Shift = 0;
 for(shift = 0,ishift = 0,size = 0;shift < Size;shift ++)
  {
   MRead(TextHandler,&str,shift,1);
   size ++;
   if(MaxLine < size)
    MaxLine = (int)size;
   if(str == '\n')
    {
     ti.Size = size - 1;
     MWrite(InfoHandler,(char *)&ti,ishift,sizeof(TextShiftInfo));
     ti.Shift = shift + 1;
     ishift += sizeof(TextShiftInfo);
     size = 0;
    }
  }

 if(size)
  ti.Size = size - 1;
 MWrite(InfoHandler,(char *)&ti,ishift,sizeof(TextShiftInfo));
 MUnLock(InfoHandler);
 MUnLock(TextHandler);
}

ClassType ViewText :: isA()
{
 return _ViewText;
}

void ViewText :: StringForming(char *str,unsigned size,int wnd_dx,unsigned str_shift)
{
 int i;

 str[size] = 0;
 if(str_shift)
  {
   if(str_shift < size)
    memcpy(str,str + str_shift,size - str_shift + 1);
   else
    str[0] = 0;
  }
 i = strlen(str);
 if(wnd_dx > i)
  memset(str + i,' ',wnd_dx - i);
 str[wnd_dx] = 0;
}

int ViewText :: Keyboard(MSG &msg)
{
 int LetterCount = ViewDX / CharWidth() + 1;
 int LineCount = ViewDY / CharHeight() + 1;


 if(Lines > LineCount)
  LineCount = Lines - LineCount;
 else
  LineCount = 0;

 if(MaxLine > LetterCount)
  LetterCount = MaxLine - LetterCount;
 else
  LetterCount = 0;

 if(WndActive == WND_ACTIVE)
 switch(msg.Key)
  {
   case F1:
        RunHelp(6);
        return 1;
   case LEFT:
        if(GetPos(HORIZANTAL))
         {
          SetPos(GetPos(HORIZANTAL) - 1,HORIZANTAL);
          ScrollerShow();
          WndDraw();
         }
        WndDraw();
        return 1;
   case RIGHT:
        if(GetPos(HORIZANTAL) < LetterCount)
         {
          SetPos(GetPos(HORIZANTAL) + 1,HORIZANTAL);
          ScrollerShow();
          WndDraw();
         }
        return 1;
   case END:
        if(GetPos(HORIZANTAL) != LetterCount)
         {
          SetPos(LetterCount,HORIZANTAL);
          ScrollerShow();
          WndDraw();
         }
        return 1;
   case HOME:
        if(GetPos(HORIZANTAL))
         {
          SetPos(0,HORIZANTAL);
          ScrollerShow();
          WndDraw();
         }
        return 1;
   case UP:
        if(GetPos(VERTICAL))
         {
          SetPos(GetPos(VERTICAL) - 1,VERTICAL);
          ScrollerShow();
          WndDraw();
         }
        return 1;
   case DOWN:
        if(GetPos(VERTICAL) != LineCount)
         {
          SetPos(GetPos(VERTICAL) + 1,VERTICAL);
          ScrollerShow();
          WndDraw();
         }
        return 1;
   case PGUP:
        if(GetPos(VERTICAL))
         {
          SetPos(GetPos(VERTICAL) - ViewDY / CharHeight(),VERTICAL);
          ScrollerShow();
          WndDraw();
         }
        return 1;
   case PGDN:
        if(GetPos(VERTICAL) != LineCount)
         {
          SetPos(GetPos(VERTICAL) + ViewDY / CharHeight(),VERTICAL);
          ScrollerShow();
          WndDraw();
         }
        return 1;
   case CTRL_HOME:
   case CTRL_PGUP:
        if(GetPos(VERTICAL) || GetPos(HORIZANTAL))
         {
          SetPos(0,HORIZANTAL);
          SetPos(0,VERTICAL);
          ScrollerShow();
          WndDraw();
         }
        return 1;
   case CTRL_END:
   case CTRL_PGDN:
        if(GetPos(VERTICAL) || GetPos(HORIZANTAL) != LetterCount)
         {
          SetPos(0,HORIZANTAL);
          SetPos(LineCount,VERTICAL);
          ScrollerShow();
          WndDraw();
         }
        return 1;
  }

return GWindow :: Keyboard(msg);
}
