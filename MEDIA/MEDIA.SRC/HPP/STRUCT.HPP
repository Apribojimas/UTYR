#ifndef _MSG
#define _MSG

#define KEYBOARD        0  // Type reiksmes
#define MOUSE           1
#define COMMAND		2

#define MOVE            0x01  // tai susija su mask
#define LBUTTON         0x02  // visos reiksmes  kai button down
#define LBUTTON_UP      0x04  // kai up
#define RBUTTON         0x08
#define RBUTTON_UP      0x10
#define MBUTTON         0x20
#define MBUTTON_UP      0x40

#define LEFT_BUTTON     0x01
#define RIGHT_BUTTON    0x02
#define MIDLE_BUTTON    0x04

#define DEFAULT_MOUSE_MASK 0x2a
#define ALL_MOUSE_MASK     0x7f

struct MSG
{
 int Type;             // kas keyboard ar mouse
 int Key;              // key reiksme
 int KeyStatus;        // key shift status
 int Mouse;            // mouse busena (event)
 int ButtonStatus;     // mouse klavisu busena
 unsigned int X;       // mouse koordinates
 unsigned int Y;
 int Cmd;	       // komanda
 unsigned int Address; // kam adresuojam komanda
 long Param1;          // su komanda galimi kintamieji
 long Param2;
};



struct TextShiftInfo
{
 long Shift;
 long Size;
};


#endif