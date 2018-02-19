#include "mm.hpp"
#include "graph.hpp"
#include "gettext.hpp"
#include <math.h>
#include <stdio.h>
#include <string.h>

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

void HistoLine(int Y,int x1,int y1,int x2,int y2,int n);

/*********************************************************/
void Histogramma :: Calculate(long HHandler)
{
 int     x ;
 long    histo[256] ;

 Handler=HHandler;
 MRead(Handler,(char*)histo,0,256*sizeof(long));

 me = 0.;
 area = 0;
 sigma=0.;
 xmin = 255;
 xmax = 0;
 Font = SmallFontTable;

 for( x=0, Max=0l, Imax=0 ; x<256 ; x++ )
 {
  area+= *(histo+x);
  me += (double)( *(histo+x) * x );
  if( *(histo+x) > Max )
  {
   Imax = x ;
   Max = *(histo+x) ;
  }
  if(*(histo+x) != 0)
  {
   if(xmin>x)
    xmin=x;
   xmax=x;
  }
 }
 if(area)
  me /= (double)area ;
 else
  return ;

 for( x=0 ; x<256 ; x++ )
  sigma += (me - *(histo+x)) * (me - *(histo+x)) ;

 if(area > 1)
 {
  sigma /= (double)( area - 1 );
  sigma = sqrt( sigma );
 }
}

/*********************************************************/
void Histogramma :: Draw( int X, int Y, int dx, int dy)
{
 char   buf[80];
 int    i;
 double xm;
 double ym = 1.;
 long   histo[256] ;
 int    xx,yy;

 if( !area )
  return;
 dx-=(Font[1]/2);
 SetColor(_BLACK);
 sprintf(buf,"%s%lu",GetText(10054),area);
 OutStr( X, Y, buf, Font );
 sprintf(buf,"%s%#2lu/%2lu",GetText(10055),(long)(me/4.+0.5),(long)(me+0.5));
 OutStr( X, Y+Font[0], buf, Font );
 sprintf(buf, "%s%#2lu/%2lu",GetText(10056),(long)(sigma/4.+0.5),(long)(sigma+0.5));
 OutStr( X, Y+Font[0]*2, buf, Font );

 sprintf(buf, "%s%#2u/%2u",GetText(10057),Imax>>2,Imax);
 OutStr( X+(dx>>1), Y+Font[0], buf, Font );
 sprintf(buf, "%s%lu",GetText(10058), Max);
 OutStr( X+(dx>>1), Y+Font[0]*2, buf, Font );

 HLine( X+Font[1]/2, Y+dy-Font[0]*2.7, dx-Font[1]/2, _BLACK );
 HLine( X+Font[1]/2, Y+dy-Font[0]*1.4, dx-Font[1]/2, _BLACK );
 VLine( X+Font[1]/2, Y+dy-Font[0]*2.7,    Font[0]/2, _BLACK);
 VLine( X+Font[1]/2, Y+dy-Font[0]*1.4,    Font[0]/2, _BLACK);


 if( xmin == xmax )
 {
  sprintf(buf,"%d",xmin);
  i=strlen(buf)*Font[1];
  OutStr( X+(dx-i)/2,Y+dy-Font[0],buf, Font );
  sprintf(buf,"%d",xmin>>2);
  i=strlen(buf)*Font[1];
  OutStr( X+(dx-i)/2,Y+dy-Font[0]*2.4,buf, Font );
  ym = (double)(dy-Font[0]*7u) / (double)Max ;

  VLine(X+dx/2-Font[1]/4+Font[1]/2,Y+dy-Font[0]*4u - ym*Max,ym* Max,_BLACK);

  VLine(X+Font[1]/2,Y+dy-Font[0]*1.4,Font[0]/2,   _BLACK );
  VLine(X+Font[1]/2,Y+dy-Font[0]*2.7,Font[0]/2.6, _BLACK );
  return;
 }
 i=TextMaxLen(10053,0);
 OutStr( X+((dx-i*Font[1])>>1),Y+dy-Font[0],GetText(10053), Font );
 sprintf(buf,"%d",xmin);
 OutStr( X,Y+dy-Font[0],buf, Font );
 sprintf(buf,"%d",xmin>>2);
 OutStr( X,Y+dy-Font[0]*2.4,buf, Font );
 sprintf(buf,"%d",xmax);
 i=strlen(buf)*Font[1];
 OutStr( X+dx-i,Y+dy-Font[0],buf, Font );
 sprintf(buf,"%d",xmax>>2);
 i=strlen(buf)*Font[1];
 OutStr( X+dx-i,Y+dy-Font[0]*2.4,buf, Font );


 //------------------------------------------------  Reiksmiu isvedimas

 MRead(Handler,(char*)histo,0,256*sizeof(long));

 xm = (double)(dx-Font[1]/2) / (xmax-xmin) ;
 ym = (double)(dy-Font[0]*7u) / (double)Max ;

 yy = Y+dy-Font[0]*4u;

 for( i=xmin ; i<=xmax ; i++ )
 {
  xx = X+xm*(i-xmin)+Font[1]/2;

  if(  *(histo+i) != 0 )
   if(*(histo+i+1) == 0 || i == 255)
    Bar(xx,yy - ym* *(histo+i),xm+1.,ym* *(histo+i)+1,_BLACK);
   else
    HistoLine(yy,xx,yy-ym* *(histo+i),xx+xm,yy-ym* *(histo+i+1),_BLACK);
  if( ! (i%50) )
   VLine(xx,Y+dy-Font[0]*1.4,Font[0]/2, _BLACK );
  else
   if( ! (i%25) )
    VLine(xx,Y+dy-Font[0]*1.4,Font[0]/2.6, _BLACK );
  if( ! (i%40) )
   VLine(xx,Y+dy-Font[0]*2.7,Font[0]/2.6, _BLACK );
  if( ! (i%200) )
   VLine(xx,Y+dy-Font[0]*2.7,Font[0]/2, _BLACK );
 }
}
