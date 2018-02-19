#include <string.h>
#include <stdio.h>
#include <math.h>
#include "keys.h"
#include "graph.hpp"
#include "gettext.hpp"
#include "mm.hpp"
#include "vcmd.hpp"
#include "proto.hpp"
#include "fronto.hpp"

void Heap(char far *record);

#define WindowDX  280
#define WindowDY  180
#define FreePlaceX  (((Max<10)?2:(Max<100)?3:4)*SmallFontTable[1])
#define FreePlaceDX (FreePlaceX + SmallFontTable[1]/2)
#define FreePlaceY  (SmallFontTable[0]/2)
#define FreePlaceDY (4*SmallFontTable[0])


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

FrontoGrama :: FrontoGrama(long *MHandler,int size,long fragregisternumber,int fragindex)
            :  GWindow(200,100,WindowDX,WindowDY,GetText(10063),WND_GRAPH | WND_CLOSE_BUTTON)
{
 int i;
 int MaxLen;

 Max = 0;
 Min = -1;
 if(size)
  {
   Size = size;
   FillGrama(MHandler);
   FillGramaAverage();
  }
 else
  for(i = 0;i < GramaCount;i ++)
   Grama[i] = 0L;
 DisplayGrama = Grama[0];
 NewMenu();
 MaxLen = TextMaxLen(10064,10065,10066,10067,10067,10069,0);
 MaxLen = MaxLen * SmallFontTable[1] + 3;
 AddMenuItem(new GRadioButton(0,0,MaxLen,20,GetText(10064),VIENA_LINIJA));
 AddMenuItem(new GRadioButton(0,20,MaxLen,20,GetText(10065),TRYS_LINIJOS));
 AddMenuItem(new GRadioButton(0,40,MaxLen,20,GetText(10066),PENKIOS_LINIJOS));
 AddMenuItem(new GRadioButton(0,60,MaxLen,20,GetText(10067),SEPTYNIOS_LINIJOS));
 AddMenuItem(new GRadioButton(0,80,MaxLen,20,GetText(10068),DEVYNIOS_LINIJOS));
 AddMenuItem(new GRadioButton(0,100,MaxLen,20,GetText(10069),VIENUOLIKA_LINIJU));

 ZemRiba = 0;
 VirRiba = Size;
 Rodykle = Size / 2;
 SenaRodykle = Rodykle;

 FragmentIndex = fragregisternumber;
 SWndName = 0L;
 SaveWndName(GetText(10063));
 FullWndName(fragindex);
 Heap("FrontoGrama :: FrontoGrama");
}

FrontoGrama :: ~FrontoGrama()
{
 int i;

 for(i = 0;i < GramaCount;i ++)
  if(Grama[i] != 0L)
   delete Grama[i];

 if(SWndName != 0L)
  delete SWndName;

 SendMSGCmd(DESTROY_FRAGMENT_LINE,(int)((unsigned long)FragmentIndex >> 16),FragmentIndex & 0xffffL);
 Heap("FrontoGrama :: ~FrontoGrama");
}

void FrontoGrama :: DisplayInfo(void)
{
 char str[32];

 SetGroundColor(GRAY_10);
 SetColor(_RED);
 sprintf(str,"Pix.%3i  ",(int)DisplayGrama[Rodykle]);
 OutText(ViewX+(ViewDX - strlen(str)*SmallFontTable[1])/2,ViewY+ViewDY-18,str);
}

ClassType FrontoGrama :: isA()
{
 return _FrontoGrama;
}

int FrontoGrama :: Command(MSG &msg)
{
 switch(msg.Cmd)
  {
   case VIENA_LINIJA:
        DisplayGrama = Grama[0];
        WndDraw();
        return 1;
   case TRYS_LINIJOS:
        DisplayGrama = Grama[1];
        WndDraw();
        return 1;
   case PENKIOS_LINIJOS:
        DisplayGrama = Grama[2];
        WndDraw();
        return 1;
   case SEPTYNIOS_LINIJOS:
        DisplayGrama = Grama[3];
        WndDraw();
        return 1;
   case DEVYNIOS_LINIJOS:
        DisplayGrama = Grama[4];
        WndDraw();
        return 1;
   case VIENUOLIKA_LINIJU:
        DisplayGrama = Grama[5];
        WndDraw();
        return 1;
   case CHANGE_HISTO_NAME:
        if(msg.Param1 == FragmentIndex)
         FullWndName((int)msg.Param2);
        break;
   case DESTROY_FRONTO:
        if(msg.Param1 == FragmentIndex)
         SendMSGCmd(ITEM_DESTROY,RegisterNumber);
        return 0;
 }
 return (GWindow :: Command(msg));
}

int FrontoGrama :: Keyboard(MSG &msg)
{
 switch(msg.Key)
  {
   case F1:
//        RunHelp(8);
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

void FrontoGrama :: FillGrama(long *MHandler)
{
 int i;

 for(i = 0;i < GramaCount;i ++)
  {
   Grama[i] = new unsigned char[Size + 1];
   MRead(MHandler[i],(char *)Grama[i]);
  }
}

void FrontoGrama :: FillGramaAverage(void)
{
 int i;
 int j;
 unsigned int aver;

 for(i = 0;i < Size;i ++)
  {
   aver = Grama[0][i] + Grama[1][i] + Grama[2][i];
   Grama[1][i] = aver / 3;
   aver += Grama[3][i] + Grama[4][i];
   Grama[2][i] = aver / 5;
   aver += Grama[5][i] + Grama[6][i];
   Grama[3][i] = aver / 7;
   aver += Grama[7][i] + Grama[8][i];
   Grama[4][i] = aver / 9;
   aver += Grama[9][i] + Grama[10][i];
   Grama[5][i] = aver / 11;
  }
 for(j = 0;j < 6;j ++)
  for(i = 0;i < Size;i ++)
   {
    if(Grama[j][i] > Max)
     Max = Grama[j][i];
    if(Grama[j][i] < Min)
     Min = Grama[j][i];
   }
 for(i = 6;i < GramaCount;i ++)
  if(Grama[i] == 0l)
  {
   delete Grama[i];
   Grama[i] = 0l;
  }
}

void FrontoGrama :: MoveRodykle(void)
{
 ShowRodykleShape(' ');
 ShowRodykleShape('');
 SenaRodykle = Rodykle;
}

void FrontoGrama :: FullWndName(int fragmentnumber)
{
 char str[100];

 if(fragmentnumber)
  sprintf(str,"%s %i",SWndName,fragmentnumber);
 else
  sprintf(str,"%s",SWndName);
 SetWndName(str);
}

void FrontoGrama :: SaveWndName(char *wndname)
{
 if(SWndName != 0L)
  delete SWndName;
 SWndName = new char [strlen(wndname) + 1];
 if(SWndName != 0L)
  strcpy(SWndName,wndname);
}

#pragma argsused
void FrontoGrama :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 int i;
 int y1;
 int x1;
 int y2;
 int x2;
 float MastX;
 float MastY;
 char buf[10];

 Bar(x,y,dx,dy,GRAY_10);
 if(DisplayGrama == 0L)
  return;

 if(Size)
  MastX = (float)(dx - FreePlaceDX) / (float)(Size);
 if(Max == Min)
  MastY = 0.;
 else
  MastY = (float)(dy - FreePlaceDY) / fabs(Max - Min);

 SetGroundColor(GRAY_10);
 SetColor(_WHITE);

 sprintf(buf,"%d",Max);
 OutText(x + SmallFontTable[1]/2,y,buf);
 x += FreePlaceX;
 y += FreePlaceY;
 VLine(x,y,dy - FreePlaceDY,_WHITE);
 y += (dy - FreePlaceDY);
 HLine(x,y,dx-FreePlaceDX,_WHITE);
 sprintf(buf,"%d",Min);
 OutText(x - FreePlaceX + SmallFontTable[1]/2,y - SmallFontTable[0]/2,buf);
 sprintf(buf,"%d",Size);
 x1=strlen(buf) * SmallFontTable[1];
 OutText(ViewX + ViewDX - x1,ViewY + ViewDY - SmallFontTable[0] * 3 - 5,buf);

 x1 = x;
 y1 = y - MastY * (DisplayGrama[0] - Min);

 for(i = 1;i < Size;i ++)
  {
   x2 = x + i * MastX;
   y2 = y - MastY * (DisplayGrama[i] - Min);
   Line(x1,y1,x2,y2,_RED);
   x1 = x2;
   y1 = y2;
  }

 DisplayInfo();
 ShowRodykleShape('');
}

void FrontoGrama :: ShowRodykleShape(char str)
{
 int i;

 SetGroundColor(GRAY_10);
 SetColor(_RED);
 if(Size)
  {
   if(str == ' ')
    i = (float)((ViewDX - FreePlaceDX) / (float)Size) * (SenaRodykle-ZemRiba);
   else
    i = (float)((ViewDX - FreePlaceDX) / (float)Size) * (Rodykle-ZemRiba);
  }
 else
  i = (ViewDX - FreePlaceDX) / 2;
 OutChar(ViewX + i + FreePlaceX - SmallFontTable[1]/2,ViewY + ViewDY - SmallFontTable[0] * 2 - 5,str,SmallFontTable);
}

int FrontoGrama :: Mouse(MSG &msg)
{
 int  i;

 i = GWindow :: Mouse(msg);
 if(((msg.ButtonStatus) && (msg.Mouse & MOVE))  || (msg.Mouse & LBUTTON))
  if(WndActive == WND_ACTIVE && WndEvent == 0)
   if(isMyFrame(msg.X,msg.Y) && Size)
    {
//     Rodykle = ((signed int)(msg.X - ViewX) * (float)Size) / (ViewDX - FreePlaceDX);
     Rodykle = ((signed int)(msg.X - (ViewX + FreePlaceDX)) * (float)Size) / (ViewDX - FreePlaceDX);
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
