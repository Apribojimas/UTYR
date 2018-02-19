#include <string.h>
#include <stdio.h>
#include "graph.hpp"
#include "vcmd.hpp"
#include "gdefine.hpp"
#include "define.hpp"
#include "proto.hpp"
#include "mm.hpp"
#include "keys.h"
#include "histo.hpp"

void Heap(char far *record);


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

Histo :: Histo(char *wndname,int destroyindex,long mhandler,int histonumber,long fragregisternumber,int fragindex)
      :  GWindow(100,30,380,200,wndname,WND_GRAPH | WND_CLOSE_BUTTON | WND_MAX_BUTTON,0,0,600,400)
{
 DestroyIndex = destroyindex;
 MHandler = mhandler;
 DrawHisto.Calculate(MHandler);
 DrawHisto.GetLim(ZemRiba,VirRiba);
 Rodykle = (ZemRiba + VirRiba) / 2;
 SenaRodykle = Rodykle;
 HistoNumber = histonumber;
 FragmentIndex = fragregisternumber;
 SWndName = 0L;
 SaveWndName(wndname);
 FullWndName(fragindex);
 Heap("Histo :: Histo");
}

Histo :: ~Histo()
{
 if(MHandler != ERROR_HANDLER)
  MFree(MHandler);
 if(SWndName != 0L)
  delete SWndName;
}

#pragma argsused
void Histo :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 Bar(x,y,dx,dy,GRAY_11);
 DrawHisto.Draw(x,y,dx,dy);
 DisplayInfo();
 ShowRodykleShape('');
}

ClassType Histo :: isA()
{
 return _Histo;
}

void Histo :: DisplayInfo(void)
{
 char str[30];
 long value=0;

 SetGroundColor(GRAY_11);
 SetColor(_RED);
 Bar(ViewX+ViewDX/2,ViewY,ViewDX/2,SmallFontTable[0],GRAY_11);
 MRead(MHandler,(char huge *)&value,Rodykle*sizeof(long),sizeof(long));
 sprintf(str,"Pix.%i/%i.Value %lu",Rodykle/4,Rodykle,value);
 OutText(ViewX+ViewDX/2,ViewY,str);
}

void Histo :: ShowRodykleShape(char str)
{
 int i;

 SetGroundColor(GRAY_11);
 SetColor(_RED);
 if(VirRiba - ZemRiba)
  {
   if(str == ' ')
    i = (float)((ViewDX - SmallFontTable[1]) / (float)(VirRiba - ZemRiba+1)) * (SenaRodykle-ZemRiba+1);
   else
    i = (float)((ViewDX - SmallFontTable[1]) / (float)(VirRiba - ZemRiba+1)) * (Rodykle-ZemRiba+1);
  }
 else
  i = (ViewDX - SmallFontTable[1]) / 2;
 OutChar(ViewX + i,ViewY + ViewDY - SmallFontTable[0] * 4 + 2,str,SmallFontTable);
}

void Histo :: MoveRodykle(void)
{
 ShowRodykleShape(' ');
 ShowRodykleShape('');
 SenaRodykle = Rodykle;
}

int Histo :: Keyboard(MSG &msg)
{

 switch(msg.Key)
  {
   case F1:
        RunHelp(8);
        return 1;
   case END:
        if(Rodykle != VirRiba)
         {
          Rodykle = VirRiba;
          DisplayInfo();
          MoveRodykle();
         }
        return 1;
   case HOME:
        if(Rodykle != ZemRiba)
         {
          Rodykle = ZemRiba;
          DisplayInfo();
          MoveRodykle();
         }
        return 1;
   case RIGHT:
        if(Rodykle < VirRiba)
         {
          Rodykle ++;
          DisplayInfo();
          MoveRodykle();
         }
        return 1;
   case LEFT:
        if(Rodykle > ZemRiba)
         {
          Rodykle --;
          DisplayInfo();
          MoveRodykle();
         }
        return 1;
   case SHIFT_RIGHT:
        if(Rodykle < VirRiba)
         {
          Rodykle +=10;
          if(Rodykle > VirRiba)
           Rodykle = VirRiba;
          DisplayInfo();
          MoveRodykle();
         }
        return 1;
   case SHIFT_LEFT:
        if(Rodykle > ZemRiba)
         {
          Rodykle -=10;
          if(Rodykle < ZemRiba)
           Rodykle = ZemRiba;
          DisplayInfo();
          MoveRodykle();
         }
        return 1;
  }
return GWindow :: Keyboard(msg);
}

int Histo :: Command(MSG &msg)
{
 switch(msg.Cmd)
  {
   case DESTROY_HISTO:
        if(msg.Param1 == DestroyIndex)
         SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        break;
   case CHANGE_HISTO_NAME:
        if(msg.Param1 == FragmentIndex)
         FullWndName((int)msg.Param2);
        break;
  }
return GWindow :: Command(msg);
}

int Histo :: Mouse(MSG &msg)
{
 int  i;

 i = GWindow :: Mouse(msg);
 if(((msg.ButtonStatus) && (msg.Mouse & MOVE))  || (msg.Mouse & LBUTTON))
  if(WndActive == WND_ACTIVE && WndEvent == 0)
   if(isMyFrame(msg.X,msg.Y) && (VirRiba - ZemRiba))
    {
     Rodykle = ((signed int)(msg.X - ViewX) * (float)(VirRiba - ZemRiba)) / (ViewDX - SmallFontTable[1] / 2 - 1);
     Rodykle += ZemRiba;
     if(Rodykle < ZemRiba)
      Rodykle = ZemRiba;
     if(Rodykle > VirRiba)
      Rodykle = VirRiba;
     DisplayInfo();
     MoveRodykle();
    }

return i;
}

void Histo :: FullWndName(int fragmentnumber)
{
 char str[100];

 if(fragmentnumber)
  sprintf(str,"%s %i:%i",SWndName,fragmentnumber,HistoNumber);
 else
  sprintf(str,"%s",SWndName);
 SetWndName(str);
}

void Histo :: SaveWndName(char *wndname)
{
 if(SWndName != 0L)
  delete SWndName;
 SWndName = new char [strlen(wndname) + 1];
 if(SWndName != 0L)
  strcpy(SWndName,wndname);
}