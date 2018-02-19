
void AbsKoordinate(int &x,int &y,int &dx,int &dy)
{
 if(dx < 0)
  {
   x += dx;
   dx = -dx;
  }
 if(dy < 0)
  {
   y += dy;
   dy = -dy;
  }
}