#include <string.h>
#include <stdio.h>
#include <alloc.h>
#include <conio.h>
#include <dos.h>
#include <time.h>

#include "desktopw.hpp"
#include "gscroll.hpp"
#include "gcbutton.hpp"
#include "proto.hpp"
#include "mm.hpp"
#include "graph.hpp"
#include "groller.hpp"
#include "gfile.hpp"
#include "ginput.hpp"
#include "calculate.hpp"
#include "viewtext.hpp"
#include "hardlock.hpp"
#include "config.hpp"

extern unsigned int MSGDebugCounter;
extern unsigned int MSGDebugStop;
extern long ConventionFreeMemorySize;

void main(int arg,char *argv[])
{
 clock_t start, end;
 start = clock();
 long addr1=farcoreleft(),addr2;

 ConventionFreeMemorySize = farcoreleft();
 #ifdef HARDLOCK
 if(HardLockTest() == 0)
  {
   printf("Not fount hard lock\n");
   return;
  }
 #endif
 GlobalInit(arg,argv); // tik po init galima register
 SendMSGCmd(ITEM_SHOW);   // reikia aktyvuoti pirma object'a
 SendMSGCmd(ITEM_ACTIVE);
 
 ReDraw();
 Register(new DeskTopWindow);

 while(DeskTopCommand != DESKTOP_EXIT)
  if(MSGDebugCounter != MSGDebugStop)
   {
    CheckEvent();
//    Heap("Main");
   }
  else
   MSGDebugCounter ++;

 GlobalClose();

////////////////////////////////////////////////////////
 end = clock();
 addr2=farcoreleft();
 printf("The time was: %f %lu\n", (end - start) / CLK_TCK, (end - start));
 printf("%lu-%lu=%lu\n",addr2,addr1,addr2-addr1);
 if( farheapcheck() == _HEAPCORRUPT )
  {
   printf( "   Heap is corrupted.\n" );
   return;
  }
 else
   printf( "   Heap is OK.\n" );
 struct farheapinfo hi;
 hi.ptr = NULL;
 printf( "   Size   Status\n" );
 printf( "   ----   ------\n" );
 while( farheapwalk( &hi ) == _HEAPOK )
  printf( "%7lu    %s\n", hi.size, hi.in_use ? "used" : "free" );
 printf("--------------------------------------------------------\n\n");
 printf("                    ' Spindulys 2 '\n");
 printf(" Created: 1994.10.20\n");
 printf(" Copyright (c) Lithuania Kaunas Academic Clinical Hospital\n");
 printf("  ver 2.17 beta \n");
 printf(" Programmers :\n");
 printf("  Haris Balcius\n");
 printf("  Audrius Vasiliauskas\n");
 printf(" Beta tester:\n");
 printf("  Darius Kirna\n");
 printf(" Specials thanks:\n");
 printf("  Kestutis Stankevicius\n");
 printf("  Vytautas Stankevicius\n");
}

// farmalloc(farcoreleft()-20000);
// Register(new Calculate(0,0,100,100,"Vasia"));
// SendMSGCmd(OUT_OF_MEMORY);
// Register(new GWindow(0,0,200,200,"No Button"));
// Register(new GWindow(200,0,200,200,"Close Button",WND_GRAPH | WND_CLOSE_BUTTON));
// Register(new GWindow(400,0,200,200,"Max Button",WND_GRAPH | WND_MAX_BUTTON));
// Register(new GWindow(0,200,200,200,"Close & Max Button",WND_GRAPH | WND_CLOSE_BUTTON | WND_MAX_BUTTON));
// Register(new GWindow(200,200,200,200,"Max & Min Button",WND_GRAPH | WND_MIN_BUTTON | WND_MAX_BUTTON));
// Register(new GWindow(400,200,200,200,"All Button",WND_GRAPH | WND_CLOSE_BUTTON | WND_MIN_BUTTON | WND_MAX_BUTTON));
// Register(new Calculate);

// Register(new GScroll(0,0,100,HORIZANTAL,100));
// Register(new GScroll(0,0,100,VERTICAL,100));
/*
 GRoller *gr = new GRoller(300,100,13,5);
 gr->AddString("Bing 1");
 gr->AddString("Bing 2");
 gr->AddString("Bing 3");
 gr->AddString("Bing 4");
 gr->AddString("Bing 5");
 gr->AddString("NAMAS 6");
 gr->AddString("Galas 7");
 gr->AddString("Pabaiga 8");
 gr->AddString("Vasia 9");
 Register((Object *)gr);

 Register(new GInput(10,10,15,"Vasiayg"));
 Register(new GFile(210,0,0,WRITE));

/////////////////// test view text /////////////////////

char str[] =" printf(The time was: %f %lu\n, (end - start) / CLK_TCK, (end - start)); \n if( farheapcheck() == _HEAPCORRUPT )\n   printf(    Heap is corrupted.\n );\n else\n   printf(    Heap is OK.\n );\n struct farheapinfo hi;\n hi.ptr = NULL;\n printf(    Size   Status\n );\n printf(    ----   ------\n );\n while( farheapwalk( &hi ) == _HEAPOK )\n  printf( %7lu    %s\n, hi.size, hi.in_use ? used : free );\n";
//char str[] = "Vasia";
long MHandler = MAlloc(strlen(str) + 1);
ViewText *vt;

 MWrite(MHandler,str);
 vt = new ViewText;
 vt->SetTextHandler(MHandler,strlen(str) + 1);
 Register(vt);


////////////////////////////////////////////////////////
*/
