#include <alloc.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include "graph.hpp"

#include "warning.hpp"
#include "proto.hpp"
#include "define.hpp"

int HeapCounter = 0;

void Heap(char far *record)
{

 if( farheapcheck() != _HEAPCORRUPT || HeapCounter)
  return;

 SendMSGCmd(HEAPCORRUPT);
 HeapCounter ++;
 Register(new Warning(record));
// SendMSGCmd(ITEM_ACTIVE,Register(new Warning(record)));
/*
/*
 directvideo = 0;
 gotoxy(1,2);
 cprintf("\n\r%s",record);
 cprintf( "\n\rHeap is corrupted.\n" );
// cprintf("\n\rPress any key !!!");
*/
 int x,y,dx,dy;
 GetViewPort(x,y,dx,dy);
 SetViewPort(0,0,1000,1000);
 SetColor(_RED);
 SetGroundColor(_BLACK);
 OutText(10,10,record);
 OutText(10,30,"Heap is corrupted.");
 SetViewPort(x,y,dx,dy);
 sound(200);
 delay(100);
 nosound();
// getch();
// exit(-1);
 delay(1000);
*/
}