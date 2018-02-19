#ifndef _GRAPH
#define _GRAPH

extern int GraphMaxX;  // nurodo ekrano dydi
extern int GraphMaxY;

extern int GraphMouseX;  // MouseShape vieta ir dydis
extern int GraphMouseY;
extern int GraphMouseDX;
extern int GraphMouseDY;

extern int GraphViewPortX; // void SetViewPort(int x,int y,int dx,int dy);
extern int GraphViewPortY;
extern int GraphViewPortDX;
extern int GraphViewPortDY;

extern int BoundaryX;     // tai grafinem funkcijom kintamieji kurie nusako
extern int BoundaryY;     // realius isvedimo remus
extern int BoundaryDX;
extern int BoundaryDY;

extern "C"
{
 void _ClearScreen(int Color);
 void _SetPixel(int x,int y,int Color);
 void _SetPixelXor(int x,int y,int Color);
 void _HLine(int x,int y,int dx,int Color);
 void _HLineXor(int x,int y,int dx,int Color);
 void _VLine(int x,int y,int dy,int Color);
 void _VLineXor(int x,int y,int dy,int Color);
 void _PutFrame(int x,int y,int dx,int dy,char huge *screen);
 void _GetFrame(int x,int y,int dx,int dy,char huge *screen);
 void _GetMouse(char *screen);
 void _PutMouse(char *screen);
 void _Display(int x,int y,int dx,int dy,char huge *screen);
 void MouseOff(void);
 void MouseOn(void);
 int  GraphBoundary(int x,int y,int dx,int dy);
 int  MouseBoundary(int x,int y,int dx,int dy);
}

extern int GlobalColor;
extern int GlobalGroundColor;

extern char *FontTable;              // table[0] = y table[1] = x
extern char *SmallFontTable;         // 8  x 16
extern char *MediumFontTable;        // 10 x 20
extern char *LargeFontTable;         // 12 x 25

extern int CurrentMode;
extern int WriteMode;

extern void (*ClearScreen)(int Color = GlobalColor);
extern void (*SetPixel)(int x,int y,int Color = GlobalColor);
extern void (*HLine)(int x,int y,int dx,int Color = GlobalColor);
extern void (*VLine)(int x,int y,int dy,int Color = GlobalColor);

extern void (*pPutFrame)(int x,int y,int dx,int dy,char huge *screen);
extern void (*pGetFrame)(int x,int y,int dx,int dy,char huge *screen);
extern void (*pDisplay)(int x,int y,int dx,int dy,char huge *screen);

void Line(int x1,int y1,int x2,int y2,int color = GlobalColor);
void PutFrame(int x,int y,int dx,int dy,char huge * screen);
void GetFrame(int x,int y,int dx,int dy,char huge *screen);
void Display(int x,int y,int dx,int dy,char huge *screen);
void FillArea(int x,int y,int dx,int dy,int sizemaskx,int sizemasky,char *mask);
void Rectangle(int x,int y,int dx,int dy,int color = GlobalColor);
void Bar(int x,int y,int dx,int dy,int color = GlobalColor);

void Circle(int xc,int yc,int r,int color = GlobalColor);
void DisplayCircle(int xc,int yc,int r,int FirstLine,int LineCount,char huge *picture);
void Ellipse(int x1,int y1,int x2,int y2,int a0,int color = GlobalColor);
void EllipseBoundary( int x1, int y1,int x2, int y2, int b0);
int  EllipsePoint(int x1,int y1,int x2,int y2,int b0,int x,int y);
void DisplayEllipse( int x1, int y1,int x2, int y2, int b0,int FirstLine,int LineCount,char huge *picture);

void InitPath(char *fname);         // tik inicializacijos failo vardas
                                    // ieskomas einamojoje direktorijoje
				    // paskui SET SPINDULYS - direktorijoje
void InitAdapter(char *fname = 0l); // tik vesa, jei ne rezimu neijungs
void CloseAdapter(void);
int TestVideoMode(int mode);        // testuoti ar yra toks rezimas,
				    // jei 0 yra

extern char GlobalPath[80];                //MAXPATH
char *GetDataName(char *Fname,char *Path=GlobalPath);
char *GetImagesName(char *Fname,char *Path=GlobalPath);
char *GetVideoDriver(char *Path=GlobalPath);

int  SetVideoMode(int mode);
void CloseGraph(void);
void SetWriteMode(int mode);
void SetColor(int Color);
void SetGroundColor(int Color);
void GetAllPalette(char *palette,int color_num,int color_count);
void SetAllPalette(char *palette,int color_num,int color_count);
void GetRGBpalette(int color_num,char &R,char &G,char &B);
void SetRGBpalette(int color_num,char R,char G,char B);
void SetGrayPalette(int zona);
void SetGrayInvertPalette(int zona);
void SetVideoPalette(void);
void SetViewPort(int x,int y,int dx,int dy);
void GetViewPort(int &x,int &y,int &dx,int &dy);

char *LoadFontTable(char *filename);
char *LoadFontTable(void);  // Default font table
char *LoadFontTable(int width,int height);

void OutFont(int x,int y,char chr,char *point_table = FontTable,int color = GlobalColor);
void OutChar(int x,int y,char chr,char *point_table = FontTable,int color = GlobalColor,int groundcolor = GlobalGroundColor);
void OutFont(int x,int y,char chr,int width,int height);
void OutChar(int x,int y,char chr,int width,int height);
void OutText(int x,int y,char * text,char *pFont = SmallFontTable);
void OutStr(int x,int y,char * text,char *pFont = SmallFontTable);
inline void OutBigText(int x,int y,char *text){OutText(x,y,text,FontTable);}
inline void OutBigStr(int x,int y,char *text){OutStr(x,y,text,FontTable);}
void OutText(int x,int y,char *text,int width,int height);
void OutStr(int x,int y,char *text,int width,int height);
int  CharHeight(void);
int  CharWidth(void);

int  Clip(int &LineX1,int &LineY1,int &LineDX,int &LineDY,
	   int BarX1,  int BarY1,  int BarDX,  int BarDY);
void Rotate(char *scr,char *dst,int dx,int dy);
void Rotate(char huge *scr,char huge *dst,int dx,int dy);
void resample (unsigned char * IN, unsigned char * OUT, int INLEN, int OUTLEN);
void resamplef(unsigned char * IN, unsigned char * OUT, int INLEN, int OUTLEN);


#define MODE_TEXT  0x3      // resoliution    80x25  (text)
#define MODE_400   0x100    // resoliution  640x400  (graph)
#define MODE_640   0x101    // resoliution  640x480  (graph)
#define MODE_800   0x103    // resoliution  800x600  (graph)
#define MODE_1024  0x105    // resoliution 1024x768  (graph)
#define MODE_1280  0x107    // resoliution 1280x1024 (graph)


#define COPY_PUT  0  // Copies source bitmap onto screen
#define XOR_PUT   1  // Exclusive ORs source image with that already onscreen
#define OR_PUT    2  // Inclusive ORs image with that already onscreen
#define AND_PUT   3  // ANDs image with that already onscreen
#define NOT_PUT   4  // Copy the inverse of the source

/************  Color Table for SVGA 256 colors modes   *************/
enum SVGA_COLORS {
    _BLACK=240,          /* dark colors */
    _BLUE=241,
    _GREEN=242,
    _CYAN=243,
    _RED=244,
    _MAGENTA=245,
    _BROWN=246,
    _LIGHTGRAY=247,
    _DARKGRAY=248,           /* light colors */
    _LIGHTBLUE=249,
    _LIGHTGREEN=250,
    _LIGHTCYAN=251,
    _LIGHTRED=252,
    _LIGHTMAGENTA=253,
    _YELLOW=254,
    _WHITE=255
};

enum GRAY_SCALE {
    GRAY_0=224,
    GRAY_1=225,
    GRAY_2=226,
    GRAY_3=227,
    GRAY_4=228,
    GRAY_5=229,
    GRAY_6=230,
    GRAY_7=231,
    GRAY_8=232,
    GRAY_9=233,
    GRAY_10=234,
    GRAY_11=235,
    GRAY_12=236,
    GRAY_13=237,
    GRAY_14=238,
    GRAY_15=239
};

#endif
