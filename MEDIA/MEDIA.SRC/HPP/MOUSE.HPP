
#ifndef __MOUSE
#define __MOUSE

// mouse proc
void InitMouse(void);
void CloseMouse(void);
void SetMouseArea(int x,int y,int dx,int dy);
void SetMouseShape(int Shape);
void MouseMove(int x,int y);
void MouseReset(void);
int  GetMouseShape(void);

extern "C"
{
 void NewMouseHandler(void);
 void interrupt MouseHandler(void);
 void MouseOff(void);
 void MouseOn(void);
 void MouseDrawEnable();
 void MouseDrawDisable();
}

enum Shape
{
 ARROW = 0,
 SMALL_KREST,
 MOUSE_HIDE,
 CLOCK,
};

#endif