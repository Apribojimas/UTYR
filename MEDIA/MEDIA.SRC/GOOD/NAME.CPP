#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mem.h>
#include "proto.hpp"
#include "vcmd.hpp"
#include "fragment.hpp"
#include "skaner.hpp"

char FileNameMask[15];
char PacientoNumeris[15];
char PacientoAmzius[10];
char PacientoData[15];
char PacientoPavarde[30];
char PacientoVardas[30];
int  BaseKey = 0;


void SetFileName(char *str)
{
 if(str)
 {
  sprintf(PacientoNumeris,"%07.7i*",atoi(str));
  sprintf(FileNameMask,"%07.7i*.*",atoi(str));
 }
 else
 {
  sprintf(PacientoNumeris,"*");
  sprintf(FileNameMask,"*.*");
 }
}

void SetAmzius(char *str)
{
 if(str)
  sprintf(PacientoAmzius,"%2.2i",atoi(str));
 else
  memset(PacientoAmzius,0,sizeof(PacientoAmzius));
}

void SetData(char *str)
{
 if(str)
  strcpy(PacientoData,str);
 else
  memset(PacientoData,0,sizeof(PacientoData));
}

void SetPavarde(char *str)
{
 if(str)
  strcpy(PacientoPavarde,str);
 else
  memset(PacientoPavarde,0,sizeof(PacientoPavarde));
}

void SetVarda(char *str)
{
 if(str)
  strcpy(PacientoVardas,str);
 else
  memset(PacientoVardas,0,sizeof(PacientoVardas));
}

void SetBaseKey(int i)
{
 BaseKey = i;
}

void InitName(void)
{
 if(BaseKey == 1)
//  Register(new Skaner);
  SendMSGCmd(GRABER);
 if(BaseKey == 2)
//  Register(new Fragment(PacientoPavarde,FileNameMask));
  SendMSGCmd(VAIZDO_APDOR);
}