#ifndef _FMEDIAN3x3
#define _FMEDIAN3x3

#include "filter.hpp"

class Median3x3 : public Filtering
{
 public:
  Median3x3(long ScrHandler,int dx, int dy,int sentAdr);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif

#ifndef _FMEDIAN5x5
#define _FMEDIAN5x5

#include "filter.hpp"

class Median5x5 : public Filtering
{
 public:
  Median5x5(long ScrHandler,int dx, int dy,int sentAdr);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif

#ifndef _FMEDIAN1x2
#define _FMEDIAN1x3

#include "filter.hpp"

class Median1x3 : public Filtering
{
 public:
  Median1x3(long ScrHandler,int dx, int dy,int sentAdr);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif

#ifndef _FMEDIAN3x1
#define _FMEDIAN3x1

#include "filter.hpp"

class Median3x1 : public Filtering
{
 public:
  Median3x1(long ScrHandler,int dx, int dy,int sentAdr);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif

#ifndef _FMEDIANCROSS
#define _FMEDIANCROSS

#include "filter.hpp"

class MedianCross : public Filtering
{
 public:
  MedianCross(long ScrHandler,int dx, int dy,int sentAdr);
  virtual void Run(void);
  virtual ClassType isA();
};
#endif

