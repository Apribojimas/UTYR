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
