#include <string.h>
#include "calstr.hpp"

#ifndef _CAL_STRUCT
#define _CAL_STRUCT

#include "point.hpp"

class CalStruct
{
public:
 int CalculateRegisterNumber;
 int CViewX;
 int CViewY;
 int CViewDX;
 int CViewDY;

 int RegisterNumber;  // window register number

 int ViewX;
 int ViewY;
 int ViewDX;
 int ViewDY;

 float V[2];
 float D[6];
 float S;   //Plotas

 int SV[2];   // status
 int SD[6];

 Point P1D[6];    // atstumu koordinates   1 tsk
 Point P2D[6];    // atstumu koordinates   2 tsk

 float Mastelis;   // pixel i atstuma
 float Scale;

 int FillV1[3];  // is kokiu D sudareme V, 0 reiks kad nera
 int FillV2[3];
 int FillV;      // kuri turi pildom %2

 int TuriuSantykis[2];
 int AtstumuSantykis[2];

public:
 ~CalStruct();
  CalStruct();

  void Init(void);
  void DPasive(int nr);
};
#endif

CalStruct :: CalStruct()
{
 CalculateRegisterNumber = 0;
 CViewX = 0;
 CViewY = 0;
 CViewDX = 0;
 CViewDY = 0;

 RegisterNumber = 0;

 ViewX = 0;
 ViewY = 0;
 ViewDX = 0;
 ViewDY = 0;

 memset(D,0,6 * sizeof(float));
 memset(V,0,2 * sizeof(float));
 S = 0;

 memset(SD,0,6 * sizeof(float));
 memset(SV,0,2 * sizeof(float));

 Mastelis = 0;
 Scale = 0;

 memset(FillV1,0,3 * sizeof(int));
 memset(FillV2,0,3 * sizeof(int));

 FillV = 0;

 Init();
}

CalStruct :: ~CalStruct()
{
}

void CalStruct:: DPasive(int nr)
{
 if(SD[nr - 1])
  SD[nr - 1] = 0;
}

void CalStruct:: Init(void)
{
 int i;

 for(i = 1;i < 7;i ++)
  DPasive(i);

 memset(TuriuSantykis,0,2 * sizeof(int));
 memset(AtstumuSantykis,0,2 * sizeof(int));
}
