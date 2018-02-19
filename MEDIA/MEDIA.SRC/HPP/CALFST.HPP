#ifndef _CAL_FIRST
#define _CAL_FIRST

#include "gwindow.hpp"
#include "calstr.hpp"
#include "point.hpp"
#include "nregular.hpp"

class CalFirst : public GWindow
{
protected:
 int SInit;
 int Init;
 int DInit;
 int VInit;
 int MouseEvent;
 int DLineNr;
 Point P1;
 Point P2;
 Point SP1; // ploto kvadratas
 Point SP2;
 GMenu MyGroup;
 CalStruct *CStruct;
 Bag MyBag;
 NonRegular NonReg;
public:
 ~CalFirst();
  CalFirst();

  virtual void DisplayInfo(int x,int y,int dx);

protected:
  void DLine(int nr);
  void BeginMove(int x,int y);  // DLine
  void MoveTo(int x,int y);     // DLine
  void EndMove(int x,int y);    // DLine
  void ShowLine(int nr,Point &p1,Point &p2);
  void DCall(int nr);
  int DMSGCall(MSG &msg);
  void DPasive(int nr);
  void DAtstumas(int nr,Point &p1,Point &p2);
  int DCommand(MSG &msg);
  int DAtstumuSantykis(MSG &msg);
  int DAtstumuSantykis(int nr);
  int VTuriuSantykis(MSG &msg);
  int VTuriuSantykis(int nr);
  int FillV(MSG &msg);
  int FillV(int nr);
  void Abort(void);

  virtual void BeginMark(int x,int y);
  virtual void EndMark(int x,int y);
  virtual void MoveMark(int x,int y);
};
#endif

