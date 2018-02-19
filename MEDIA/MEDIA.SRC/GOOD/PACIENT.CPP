#include <stdio.h>
#include <string.h>
#include "proto.hpp"
#include "graph.hpp"
#include "gettext.hpp"

#include "keys.h"
#include "pacient.hpp"

#ifndef _PACIENT
#define _PACIENT

#include "gwindow.hpp"

class Pacient : public GWindow
{
 GButton Button;
public:
 ~Pacient();
  Pacient();

  virtual int EventHandler(MSG &msg);
  virtual void Draw(int x,int y,int dx,int dy,int hscroll,int vscroll);
// reikalinga Object
  virtual ClassType isA();
};
#endif

Pacient :: Pacient()
       :   GWindow(100,100,100,100,GetText(10501),WND_GRAPH | WND_CLOSE_BUTTON),
           Button(0,0,100,20,GetText(2),ITEM_CLOSE,0,CR)
{
 int Size1,Size2;
 char str[80];

 sprintf(str,GetText(10502),PacientoVardas,PacientoPavarde,PacientoAmzius);
 Size1=strlen(str);
 sprintf(str,GetText(10503),PacientoData);
 Size2=strlen(str);
 if(Size1<Size2)
  Size1=Size2;
 sprintf(str,GetText(10504),PacientoNumeris);
 Size2=strlen(str);
 if(Size1<Size2)
  Size1=Size2;
 Size1*=SmallFontTable[1];
 Size1+=15;
 SetX((GraphMaxX+1-Size1)/2);
 SetDXDY(Size1,120);
 Show();
}

Pacient :: ~Pacient()
{
}

#pragma argsused
void Pacient :: Draw(int x,int y,int dx,int dy,int hscroll,int vscroll)
{
 char str[80];
 int nr;

 Bar(x,y,dx,dy,GRAY_11);
 SetColor(_BLACK);
 SetGroundColor(GRAY_11);
 strupr(FileNameMask);
 strupr(PacientoNumeris);
// if(strstr(FileNameMask,PacientoNumeris)!=0)
 {
  sprintf(str,GetText(10502),PacientoVardas,PacientoPavarde,PacientoAmzius);
  OutText(x + 10,y + 10,str);
  sprintf(str,GetText(10503),PacientoData);
  OutText(x + 10,y + 35,str);
  sscanf(PacientoNumeris,"%d",&nr);
  sprintf(str,GetText(10504),nr);
  OutText(x + 10,y + 60,str);
 }
// else
//  SendMSGCmd(ITEM_CLOSE,RegisterNumber);

 Button.SetXY(x + dx / 2 - 50,y + dy - 30);
 Button.Show();
}

int Pacient :: EventHandler(MSG &msg)
{
 int i;

 i = GWindow :: EventHandler(msg);
 if(Button.EventHandler(msg))
  i ++;

return i;
}

ClassType Pacient :: isA()
{
 return _Pacient;
}

