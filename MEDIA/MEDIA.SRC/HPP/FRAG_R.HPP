#ifndef _FRAGMENT_RECTANGLE
#define _FRAGMENT_RECTANGLE

#include "GEventHandler.hpp"

class FragmentRectangle : public GEventHandler
{
 long MBackup;
protected:
 int isInit;
 long MHandler;
 int FragmentNumber;
 int SendAdr;
 int FiltrNumber;
 int HistoNumber;

public:
 ~FragmentRectangle();
  FragmentRectangle(int FragNumber,int Index,int Sendadr = 0);

  int isOK(void);      // jau esama pilnai inicializuoti
  virtual void Show(void);
  void SetFragmentNumber(int i);
  virtual void MCopy(long Handler,int PictSizeDX,int PictSizeDY,int DisplayPlaceX,int DisplayPlaceY);
  virtual void CalculateHistogram(long HistoHandler);
// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Mouse(MSG &msg);           // mouse eventai
  virtual int Command(MSG &msg);         // apdorosime komandas
  virtual int Keyboard(MSG &msg);        // klaviaturos
protected:
  virtual void DisplayFragmentInfo(void);
  virtual void BeginMark(int x,int y);
  virtual void EndMark(int x,int y);
  virtual void MoveMark(int x,int y);
private:
  void HistoRectangle( long Handler,int DX, int DY, long HistoHandler);
  void HistoPrapletimas(int type,int percent,int dmin,int dmax);
  void HistoColorReduce(int i);
};
#endif

