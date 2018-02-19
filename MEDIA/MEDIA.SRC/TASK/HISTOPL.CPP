#include <alloc.h>

#include "mm.hpp"
#include "proto.hpp"
#include "histopl.hpp"

#define swap(a,b) {a^=b; b^=a;a^=b;}


#ifndef _HISTOPL
#define _HISTOPL

#include "filter.hpp"

class HistoPl : public Filter
{
 protected:
  long Handler;
  int DX;
  int DY;
  int CurentY;
  unsigned char *pScr;
  int SentAddress;
  int Sent;
  unsigned char Table[256];
 public:
  HistoPl(long ScrHandler,int dx, int dy,int sentAdr,long Histo,int Percent=5,
          int Type = 0,int Dgmin = 0,int Dgmax = 255);
  ~HistoPl();
  virtual void Run(void);
  virtual ClassType isA();
private:
  void Praplesti(int Percent,long Histo);
  void Modefikuoti(int Dgmin,int Dgmax,long Histo);
  void Nukirpti(int Dgmin,int Dgmax,long Histo);
  void Binerizuoti(int Vid);
};
#endif


ClassType HistoPl :: isA()
{
 return _HistoPl;
}

HistoPl :: HistoPl(long ScrHandler,int dx,int dy,int sentAdr,long Histo,
                   int Percent,int Type,int Dgmin,int Dgmax)
{
 Handler=ScrHandler;
 DX=dx;
 DY=dy;
 SentAddress = sentAdr;
 Sent = 0;

 CurentY=0;
 pScr = (unsigned char *)malloc(DX);

 switch(Type)
  {
   case 0:
        Praplesti(Percent,Histo);
        break;
   case 1:
        Modefikuoti(Dgmin,Dgmax,Histo);
        break;
   case 2:
        Nukirpti(Dgmin,Dgmax,Histo);
        break;
   case 3:
        Binerizuoti(Percent);
        break;
  }

 MFree(Histo);
 Histo = ERROR_HANDLER;
}

HistoPl :: ~HistoPl( )
{
 if( pScr != 0L )
  free(pScr);
}

void HistoPl :: Run(void)
{
 int i;

 if(CurentY < DY)
 {
  MRead(Handler,(char *)pScr,(long)CurentY*DX,DX);
  for ( i = 0; i < DX ; i++ )
   *( pScr + i )=*(Table + *( pScr + i ) );
  MWrite(Handler,(char *)pScr,(long)CurentY*DX,DX);
  CurentY++;
 }
 else
  if(!Sent)
  {
   SendMSGCmd(FILTER_LOCK_OUT,SentAddress,RegisterNumber);
   Sent++;
  }
}

void HistoPl :: Praplesti(int Percent,long Histo)
{
 long Histograma[256];
 int i;
 int Dmax;      // saugosime paveikslo Histogramos rez.
 int Dmin;      // jie nurodo spalvu ribas
 long Max=0;

 MRead(Histo,(char huge *)Histograma,0l,256l*sizeof(long));

 for(i = 0;i < 256;i ++)
  if(Histograma[i] > Max)
   Max = Histograma[i];
 Max = (Max * Percent) / 100;
 for(i = 0;i < 256;i ++)
  if(Histograma[i] > Max)
   break;
 Dmin = i;
 for(i = 255;i >= 0;i --)
  if(Histograma[i] > Max)
   break;
 Dmax = i;
 if(!(Dmin == 0 && Dmax == 255) || Dmin > Dmax)
 {
  for(i = 0;i < Dmin;i ++)
   Table[i]=0;

  if(Dmax != Dmin)
  {
   for(i=Dmin; i <= Dmax; i++)
    Table[i]=(unsigned char)((255U * (i - Dmin)) / (Dmax - Dmin));
  }

  for(i = Dmax;i <  256;i ++)
   Table[i]=255;
 }
 else
  CurentY=DY;
}

void HistoPl :: Modefikuoti(int Dgmin,int Dgmax,long Histo)
{
 long Histograma[256];
 int i;
 int Dfmax;      // saugosime paveikslo Histogramos rez.
 int Dfmin;      // jie nurodo spalvu ribas
 float KoefA;
 float KoefB;


 if(Dgmin > Dgmax)
  swap(Dgmin,Dgmax);

 MRead(Histo,(char huge *)Histograma,0l,256l*sizeof(long));

 for(i = 255,Dfmax = 0;i >= 0 && Dfmax == 0;i --)
  if(Histograma[i])
    Dfmax = i;

 for(i = 0, Dfmin = 0;i < 256;i ++)
  if(Histograma[i])
   {
    Dfmin = i;
    break;
   }

  for(i = 0;i < Dfmin;i ++)
   Table[i]=Dgmin;

  KoefA = (float)(Dgmax - Dgmin) / (Dfmax - Dfmin);
  KoefB = (float)(Dfmax * Dgmin - Dgmax * Dfmin) / (Dfmax - Dfmin);

  if(Dfmax != Dfmin)
  {
   for(i = Dfmin;i <= Dfmax;i ++)
    Table[i]=(unsigned char)(i * KoefA + KoefB);
  }

  for(i = Dfmax;i <  256;i ++)
   Table[i]=Dgmax;
}

void HistoPl :: Nukirpti(int Dgmin,int Dgmax,long Histo)
{
 long Histograma[256];
 int i;


 if(Dgmin > Dgmax)
  swap(Dgmin,Dgmax);

 MRead(Histo,(char huge *)Histograma,0l,256l*sizeof(long));


  for(i = 0;i < Dgmin;i ++)
   Table[i]=Dgmin;

  if(Dgmax != Dgmin)
  {
   for(i = Dgmin;i <= Dgmax;i ++)
    Table[i]=(unsigned char)(i);
  }

  for(i = Dgmax;i <  256;i ++)
   Table[i]=Dgmax;
}

void HistoPl :: Binerizuoti(int Vid)
{
 int i;

 for(i = 0;i < 256;i ++)
  if(i < Vid)
   Table[i] = 0;
  else
   Table[i] = 255;
}
