#include <stdio.h>
#include "proto.hpp"
#include "graph.hpp"
#include "mm.hpp"
#include "gettext.hpp"

void GlobalInit(int arg,char *argv[])
{
 printf("Set up:\n");
 printf(" Hard disk error handler");
 InitHD_ErrorHandler();
 printf("  OK \n Init param");
 InitParam(arg,argv);           // visada pirmas
 printf("  OK \n Init path");
 InitPath("system.ini");        // po param init kelius
 printf("  OK \n Memory manager");
 InitMemoryManager(GetMMSwap());// patariam but pirmam    // po InitPatch()
 printf("  OK \n Init text");
 InitText(GetTextFile());       // po keliu init txt isvedima  // InitMemoryManager()
 printf("  OK \n Init multitasking");
 InitTask();
 printf("  OK \n Init video driver");
 InitAdapter(GetVideoDriver());
 printf("  OK \n Init desktop");
 InitDeskTop();                 // pries init event
 printf("  OK \n Event manager");
 InitEvent();
 printf("  OK \n Init desktop background");
 InitGround();                // po MemoryManager ir InitText
 printf("  OK \n Set video mode");
 if(SetVideoMode(MODE_640))   // gali buti paskutinis
  if(SetVideoMode(MODE_800))
   if(SetVideoMode(MODE_1024))
    DeskTopCommand = DESKTOP_EXIT;

 printf("  OK \n Init name");
 InitName();                    // turi buti po SetVideoMode
 printf("  OK \n");
}

void GlobalClose(void)
{
 CloseGround();
 CloseHD_ErrorHandler();
 CloseDeskTop(); // pries closeevent
 CloseEvent(); // pirmam
 CloseParam(); // patartina paskutiniam
 CloseMemoryManager(); // po CloseDeskTop
 CloseTask();
 CloseGraph();
 CloseAdapter();
 CloseText();
}
