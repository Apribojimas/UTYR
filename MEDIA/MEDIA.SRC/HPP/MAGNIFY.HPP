#ifndef _FMAGNIFY
#define _FMAGNIFY

#include "filter.hpp"

class Magnify : public Filter
{
 protected:
  long scrHandler;
  int scrdx;
  int scrdy;
  long dstHandler;
  int dstdx;
  int dstdy;
  long tmpHandler1;
  long tmpHandler2;
  int CurentX;
  int CurentY;
  char *pScr;
  char *pDst;
  int SentAddress;
  int Sent;
 public:
  Magnify(long ScrHandler,int ScrDx,int ScrDy,
          long DstHandler,int DstDx,int DstDy,
          int sentAdr);
  ~Magnify();

  virtual void Run(void);
  virtual ClassType isA();

  virtual int GetPercent(void);
};
#endif
