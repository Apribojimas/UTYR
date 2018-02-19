#ifndef _GET_LINE_FROM_MEMORY
#define _GET_LINE_FROM_MEMORY

#include "object.hpp"

class GetLineFromMemory : public Object
{
 long PictureMHandler;
 int PictureDX;
 int PictureDY;
 int CalculationPlace;

public:
 ~GetLineFromMemory();
  GetLineFromMemory(long mhandler,int dx,int dy);

  int GetLine(long &MHadler,int x1,int y1,int x2,int y2); // return size
  virtual ClassType isA();
protected:
  void GetVLine(long MHandler,int x,int y,int dy);
  void GetHLine(long MHandler,int x,int y,int dx);
  void GetPixel(long MHandler,int x,int y);
  void GetLocalLine(long MHandler,int x1,int y1,int x2,int y2);
};
#endif
