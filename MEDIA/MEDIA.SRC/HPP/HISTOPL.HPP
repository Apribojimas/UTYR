#ifndef _HISTOPL
#define _HISTOPL

#include "filter.hpp"

class HistoPl : public Filter
{
 protected:
  long Handler;
  int DX;
  int DY;
  int CurentY;
  unsigned char *pScr;
  int SentAddress;
  int Sent;
  unsigned char Table[256];
 public:
  HistoPl(long ScrHandler,int dx, int dy,int sentAdr,long Histo,int Percent=5,
          int Type = 0,int Dgmin = 0,int Dgmax = 255);
  ~HistoPl();
  virtual void Run(void);
  virtual ClassType isA();
private:
  void Praplesti(int Percent,long Histo);
  void Modefikuoti(int Dgmin,int Dgmax,long Histo);
  void Nukirpti(int Dgmin,int Dgmax,long Histo);
  void Binerizuoti(int Vid);
};
#endif
