#include <stdlib.h>
#include <string.h>
#include "proto.hpp"

#define NORMAL_MSG_QUEUE 0
#define BACKUP_MSG       1
#define ROLL_BACK_MSG    2

//#define BackupMSG   "/backup"
//#define RollBack    "/rollback"
//#define MSGDebug    "/msgdebug:"
//#define MouseEvent  "/mouse"
//#define NoTimeCount "/time"

#define BackupMSG   "/b"
#define RollBack    "/r"
#define MSGDebug    "/d:"
#define MouseEvent  "/m"
#define NoTimeCount "/t"

#define EmptyKey    "/p"
#define Skaner      "/c"

extern int AllMouseEvent;
unsigned int MSGDebugStop    = -1;
int AboutPacient = 0;

void InitParam(int arg,char *argv[])
{
 int i;
 char *msg_debug;


 strlwr(argv[1]);
 if(strstr(argv[1],EmptyKey) || strstr(argv[1],Skaner))
  {
   AboutPacient++;
   if(arg > 1)
    SetFileName(argv[2]);
   else
    SetFileName(0L);

   if(arg > 2)
    SetAmzius(argv[3]);
   else
    SetAmzius(0L);

   if(arg > 3)
    SetData(argv[4]);
   else
    SetData(0L);

   if(arg > 4)
    SetPavarde(argv[5]);
   else
    SetPavarde(0L);

   if(arg > 5)
    SetVarda(argv[6]);
   else
    SetVarda(0L);

   if(strstr(argv[1],Skaner))
    SetBaseKey(1);
   if(strstr(argv[1],EmptyKey))
    SetBaseKey(2);
  }
 else
  {
   SetFileName(0L);
   SetAmzius(0L);
   SetData(0L);
   SetPavarde(0L);
   SetVarda(0L);
  }

 for(i = 0;i < arg;i ++)
  strlwr(argv[i]);

 for(i = 0;i < arg;i ++)
  if(strstr(argv[i],BackupMSG))
   {
    SetMSGQueueType(BACKUP_MSG);
    InitDemo(1);
    break;
   }

 #ifndef DEMO_VERSION
 for(i = 0;i < arg;i ++)
  if(strstr(argv[i],RollBack))
   {
    SetMSGQueueType(ROLL_BACK_MSG);
    InitDemo(0);
    break;
   }
 #else
  SetMSGQueueType(ROLL_BACK_MSG);
  InitDemo(0);
 #endif

 for(i = 0;i < arg;i ++)
  if(strstr(argv[i],MSGDebug))
   {
    msg_debug = strstr(argv[i],":");
    msg_debug ++;
    MSGDebugStop = atoi(msg_debug);
    break;
   }

 for(i = 0;i < arg;i ++)
  if(strstr(argv[i],MouseEvent))
   {
    AllMouseEvent = 1;
    break;
   }

 for(i = 0;i < arg;i ++)
  if(strstr(argv[i],NoTimeCount))
   {
    SetNoTimeCheck(1);
    break;
   }
}

void CloseParam(void)
{
 CloseDemo();
}