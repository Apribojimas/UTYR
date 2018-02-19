#include <alloc.h>

#include "mm.hpp"
#include "filter.hpp"

#ifndef _FILTER
#define _FILTER

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

int Filter :: GetPercent(void)
{
 return 0;
}


Filtering :: Filtering(long ScrHandler,int dx,int dy,int sentAdr)
{
 scrHandler=ScrHandler;
 DX=dx;
 DY=dy;
 dstHandler=MAlloc((long)DX*DY);
 SentAddress = sentAdr;
 Sent = 0;
 pScr = 0L;
 pDst = 0L;
}

Filtering :: ~Filtering( )
{
 if( pScr != 0L )
  free(pScr);
 if( pDst != 0L )
  free( pDst );
 MFree(dstHandler);
}

int Filtering :: GetPercent(void)
{
 if(Sent)
  return 100;
 return ((float)CurentY / DY) * 100;
}
