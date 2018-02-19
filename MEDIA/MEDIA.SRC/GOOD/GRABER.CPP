#pragma inline

#include <stdio.h>
#include <dos.h>

#define  LENGHT   262144UL
extern unsigned  FG_PORT;          //  default 0x238

void graber(unsigned char huge *screen)
{
// unsigned long k;
unsigned int segment,ofset;

 outp( FG_PORT, 0x7 );// jei senas v. tai sito nereikia
 //outp( C, 0x7 );// jei senas v. tai sito nereikia
 //outp( C, 0x7 );// jei senas v. tai sito nereikia
 delay(100);
 *(screen)= (unsigned char)inp( FG_PORT );
// for(k=0;k<LENGHT;k++)
//   *(screen + k)=(unsigned char)inp( A );

 segment=FP_SEG(screen);
 ofset=FP_OFF(screen);
  asm{
		pusha
		mov	ax,segment
		mov	es,ax
		mov	bx,ofset
		mov	dx,FG_PORT

    }
kartoti1:
 asm{
		in	al,dx
		mov	es:bx,al
		inc	bx
		jnz	kartoti1

		mov	ax,es
		add	ax,0x1000
		mov	es,ax
    }
 kartoti2:
 asm{
		in	al,dx
		mov	es:bx,al
		inc	bx
		jnz	kartoti2

		mov	ax,es
		add	ax,0x1000
		mov	es,ax
    }
 kartoti3:
 asm{
		in	al,dx
		mov	es:bx,al
		inc	bx
		jnz	kartoti3

		mov	ax,es
		add	ax,0x1000
		mov	es,ax
    }
 kartoti4:
 asm{
		in	al,dx
		mov	es:bx,al
		inc	bx
		jnz	kartoti4

		mov	ax,es
		add	ax,0x1000
		mov	es,ax

		mov	cx,4
    }
 galiukas:
 asm{
		in	al,dx
		mov	es:bx,al
		inc	bx
		loop	galiukas

		popa
    }
 sound(1000);
 delay(200);
 nosound();
}
