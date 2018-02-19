// proceduros kurios paiso 'langu' formas

void RectangleDraw(int x,int y,int dx,int dy);
void ButtonDraw(int x,int y,int dx,int dy,char far *str,int activeplace,int status,int justify,int ispressed);
void RadioButtonDraw(int x,int y,int dx,int dy,char far *str,int activeplace,int status,int justify);
void CheckButtonDraw(int x,int y,int dx,int dy,char far *str,int activeplace,int status,int varna);
void WindowDraw(int x,int y,int dx,int dy,char *name,int active,int type);
void WindowNameDraw(int x,int y,int dx,char *name,int color,int type);
void MenuDraw(int x,int y,int dx,int dy,int menutype);
void Sound(void);     // procedura skirta garsiniam signalui isgauti
void InputDraw(int x,int y,int dx,int dy,char *string,int active,int currentplace);
void MoveGInputCursor(int x,int y,int oldplace,int newplace);

