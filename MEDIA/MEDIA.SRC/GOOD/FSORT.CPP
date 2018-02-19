//#include <stdlib.h>
#include <dir.h>
#include <string.h>

#include "grollerd.hpp"

typedef int (*fptr)(const void*, const void*);

int SortEXT(const GRollerData **p1, const GRollerData **p2)
{
 int i;
 char drive[MAXDRIVE];
 char dir[MAXDIR];
 char file1[MAXFILE],file2[MAXFILE];
 char ext1[MAXEXT],ext2[MAXEXT];

 fnsplit(p1[0]->String,drive,dir,file1,ext1);
 fnsplit(p2[0]->String,drive,dir,file2,ext2);
 i=stricmp(ext1,ext2);
 if(i != 0)
  return i;
 return stricmp(file1,file2);
}
int SortNAME(const GRollerData **p1, const GRollerData **p2)
{
 int i;
 char drive[MAXDRIVE];
 char dir[MAXDIR];
 char file1[MAXFILE],file2[MAXFILE];
 char ext1[MAXEXT],ext2[MAXEXT];

 fnsplit(p1[0]->String,drive,dir,file1,ext1);
 fnsplit(p2[0]->String,drive,dir,file2,ext2);
 i=stricmp(file1,file2);
 if(i != 0)
  return i;
 return stricmp(ext1,ext2);
}
