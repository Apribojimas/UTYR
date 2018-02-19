#ifndef __POINT
#define __POINT

class Point
{
  public:

    int x,y;

  public:
    Point(int InitX=0,int InitY=0) { x=InitX; y=InitY; }
    Point(const Point& Init) { x=Init.x; y=Init.y; }

    Point& operator += ( const Point& adder );
    Point& operator -= ( const Point& subber );
    Point  operator  - ( const Point& adder );
    Point  operator  + ( const Point& subber );

    int operator ==  ( const Point& one );
    int operator !=  ( const Point& one );
};

inline Point& Point::operator += ( const Point& adder )
{
  x += adder.x;
  y += adder.y;
  return *this;
}

inline Point& Point::operator -= ( const Point& subber )
{
   x -= subber.x;
   y -= subber.y;
   return *this;
}

inline int Point::operator == ( const Point& one )
{
    return x == one.x && y == one.y;
}

inline int Point::operator != ( const Point& one )
{
    return x != one.x || y != one.y;
}

#endif  // Point
