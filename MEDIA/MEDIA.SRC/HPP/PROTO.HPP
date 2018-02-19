#ifndef _PROTO
#define _PROTO

void Heap(char far *record);

#include "struct.hpp"
#include "object.hpp"
#include "filter.hpp"

// jeigu turi neigiama postumi tai si procedura perskaicuoja koord. ir postumi padaro teigiama
void AbsKoordinate(int &x,int &y,int &dx,int &dy);

//
int FillStr(int key,char *Str,int &CurrentPlace,int StrSize);

// keicia raides
int Toupper(int i);  // keicia i dydziasias
int Tolower(int i);  // keicia i mazasias
void Strupr(char *string); // keiciam visa eilute i dydziasias
void Strlwr(char *string); // keiciam visa eilute i mazasias

// parametru apdorojimo proc.
void InitParam(int arg,char *argv[]);
void CloseParam(void);

// eventu proc
int  GetMSG(MSG &msg);
int  SendMSG(MSG &msg);
void SendMSGCmd(int Cmd,int Adr = 0,long Param1 = 0,long Param2 = 0);
void CloseEvent(void);
void InitEvent(void);
void BackupMSG(MSG &msg);
int  RestoreMSG(MSG &msg);
void InitDemo(int status = 1); // jei 0 tai restore else bakup
void CloseDemo(void);
void SetNoTimeCheck(int i);   // 0 tikrinti laika, !0 - netikrinti (demo)
void SetMSGQueueType(int i); //#define NORMAL_MSG_QUEUE 0 (demo)
                             //#define BACKUP_MSG       1
                             //#define ROLL_BACK_MSG    2

// desktop proc. ir kint
extern int DeskTopCommand;

int  Register(Object *Obj);
void Show(void);
void ReDraw(void);
void InitDeskTop(void);
void CloseDeskTop(void);
int  CheckEvent(void);
int  EventHandler(Object *Obj,MSG &msg);

// globalis inicializavimas
void GlobalInit(int arg,char *argv[]);
void GlobalClose(void);

// didinimas
void magnify(long ScrHandler,int ScrDX,int ScrDY,
             long DstHandler,int DstDX,int DstDY );

// nuskaitom fragment is atm manager'io i atm manager'i
void MCopyRectangle( long scrHandler, int scrDX, int scrDY, int scrX, int scrY,
                     long dstHandler, int dstDX, int dstDY, int dstX  , int dstY, int FragmentDX, int FragmentDY );

void MCopyCircle( long scrHandler,
                  int xc,int yc,int r,
                  long dstHandler,int dstDX,int dstDY );

void MCopyEllipse( long scrHandler,
                   int x1, int y1,int x2, int y2, int b0,
                   long dstHandler,int dstDX,int dstDY );

void MDisplay(long Handler,int PictureDX,int PictureDY,int ScreenX,int ScreenY);
void MPutFrame(long Handler,int PictureDX,int PictureDY,int ScreenX,int ScreenY);
void MGetFrame(long Handler,int PictureDX,int PictureDY,int ScreenX,int ScreenY);
// is mminfo
// Darbui su nereguliariu fragmentu
void DisplayBorder(long BorderHandler,int BorderSize,int ScreenX,int ScreenY,int color);

void DisplayNotRegular(long FillingHandler,int FillingSize,
                       long PictureHandler,int PictureDX,int PictureDY,
                       int ScreenX,int ScreenY);
void MCopyNotRegular(long FillingHandler,int FillingSize,
                     long scrHandler,int scrDX,
                     long dstHandler,int dstDX,int dstDY,int dstX, int dstY);
void HistoNotRegular(long FillingHandler,int FillingSize,
                     long Handler,int DX,
                     long HistoHandler);
// Grazina nereguliarus frag. plota.
long GetAreaNotRegular( long FillingHandler,int FillingSize);

long FreeMem(void);    // kiek yra visos laisvos atm.
long Farcoreleft(void);// max vientisos laisvos atm.

void DrawHist( int X, int Y,int DX,int DY,long HHandler);// PIESTI HISTOGRAMA

// Susije su TASK'u
void InitTask(void);
void CloseTask(void);
int  RegisterFilter(Filter *NewFilter);
void TerminateFilter(int FilterNr);
void TaskRun(void);
int GetFilterCount(void);
int GetFilterPercent(int i);

// help
extern int HelpIndex;
void SetHelpIndex(int index);
int  GetHelpIndex(void);
void RunHelp(int index = HelpIndex);

extern "C" void _MemCopy(char huge *dest,char huge *scr,int size);
extern "C" void MinMaxSort(unsigned char *cptr,int number);

// hard disk error handler
void CloseHD_ErrorHandler(void);
void InitHD_ErrorHandler(void);

// nuskaitom is video griebiklio faila
void graber(unsigned char huge *screen);

extern char FileNameMask[15];
extern char PacientoNumeris[15];
extern char PacientoAmzius[10];
extern char PacientoData[15];
extern char PacientoPavarde[30];
extern char PacientoVardas[30];

void SetFileName(char *str);
void SetAmzius(char *str);
void SetData(char *str);
void SetPavarde(char *str);
void SetVarda(char *str);
void SetBaseKey(int i);
void InitName(void);


void InitGround(void);
void CloseGround(void);

#endif

