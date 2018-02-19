#ifndef _HISTOREDUCE
#define _HISTOREDUCE

#include "filter.hpp"

class HistoReduce : public Filtering
{
 long HistoGrama[256];
 int ColorCount;
 int BeginCount;
 int isEnd;
 int MinPlace;
 unsigned long Min;

public:
  ~HistoReduce();
  HistoReduce(long ScrHandler,int dx, int dy,int sentAdr,long Histo,int colorCount);


  virtual void Run(void);
  virtual ClassType isA();
  virtual int GetPercent(void);
private:
  void GetMinHisto(void);
  unsigned char GetValue(unsigned char *ptr);
  int GetColorCount(void);
};
#endif
