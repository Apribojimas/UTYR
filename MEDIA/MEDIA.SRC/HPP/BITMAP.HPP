#ifndef __BITMAP
#define __BITMAP

class BitMap
{
 protected:
  unsigned MaxX,MaxY;
  unsigned ScrX;
  unsigned char *Screen;

 public:
  BitMap(int dx,int dy);
  ~BitMap();
  int  GetPixel(int x, int y);
  void SetPixel(int x, int y, int color);
  void HLine(int x1,int y1,int dx,int color);
  void VLine(int x1,int y1,int dy,int color);
  void Line(int x1,int y1,int x2,int y2,int color);
};

#endif
