#ifndef _HISTOGRAMMA
#define _HISTOGRAMMA

class Histogramma
{
  long    area ;     // velu skaicius
  double  me ;       // statistinis vidurkis
  double  sigma ;    // vidutine kvadratine paklaida
  int     Imax ;     // piko intensyvumas
  long    Max;       // piko reiksme Max
  int     xmin ;     // minimali ne nuline riba
  int     xmax ;     // maksimali riba
  char    *Font ;    // fonto pointeris
  long    Handler;   // histogrmos mm handleris

 public:
  void Calculate(long HHandler);
  void Draw( int X, int Y, int dx, int dy);
  void GetLim(int &MinLim, int &MaxLim) {MinLim = xmin; MaxLim = xmax;};
};
#endif //_HISTOGRAMMA
