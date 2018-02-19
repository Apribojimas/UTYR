#ifndef _FILTER
#define _FILTER

#include "object.hpp"

class Filter : public Object
{
 public:
  virtual void Run(void) = 0;
  virtual int GetPercent(void);
};

/***************** vienos eiltutes filtrams **************/
class Filtering : public Filter
{
 protected:
  long scrHandler;
  long dstHandler;
  int DX;
  int DY;
  int CurentY;
  unsigned char *pScr;
  unsigned char *pDst;
  int SentAddress;
  int Sent;
 public:
  Filtering(long ScrHandler,int dx, int dy,int sentAdr);
  ~Filtering();

  virtual int GetPercent(void);
};
#endif
