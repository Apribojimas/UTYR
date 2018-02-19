/* Hearder F_RDWR.HPP for class F_Read & F_Write
 */

enum
{
 UNKNOW,
 IMATYPE,
 PCXTYPE,
 PPCXTYPE,
 VPCXTYPE,
 BMPTYPE,
 BMPTYPE2,
 BMPTYPE16,
 RAWTYPE,
 RASTYPE,
 RIXTYPE,
 RIXTYPE16,
 EGATYPE,
 GIFTYPE,
};
/******************** Klases F_Read_Write apibrezimas *************/
#ifndef __F_READ_WRITE
#define __F_READ_WRITE

class F_Read_Write
{
 protected:
  int  dx;
  int  dy;
  int  color;
  int  header;
  int  handle;
  int  FileType;

  int Test(char *fname);

 public:
  F_Read_Write(void);
  int virtual Open(char *fname) = 0;
  void Close(void);
};
#endif

/******************** Klases F_Read apibrezimas ******************/
#ifndef __F_READ
#define __F_READ

class F_Read : public F_Read_Write
{
  int KoordIMA( void );
  int KoordPCX( void );
  int KoordBMP( void );
  int KoordRAW( void );
  int KoordRAS( void );
  int KoordRIX( void );
  int KoordGIF( void );

  int ReadIMA  (long PictureHandler);
  int ReadPCX  (long PictureHandler);
  int ReadBMP  (long PictureHandler);
  int ReadBMP2 (long PictureHandler);
  int ReadBMP16(long PictureHandler);
  int ReadRIX  (long PictureHandler);
  int ReadRIX16(long PictureHandler);
  int ReadEGA  (long PictureHandler);
  int ReadGIF  (long PictureHandler);

  int GetPaletteIMA(unsigned char *palette);
  int GetPalettePCX(unsigned char *palette);
  int GetPaletteBMP(unsigned char *palette);
  int GetPaletteRAW(unsigned char *palette);
  int GetPaletteRAS(unsigned char *palette);
  int GetPaletteRIX(unsigned char *palette);
  int GetPaletteEGA(unsigned char *palette);
  int GetPaletteGIF(unsigned char *palette);

 public:
  F_Read(void);
  ~F_Read();
  int  Open(char *fname);
  int  Read(long PictureHandler);
  int  GetRow(void){ return (FileType != UNKNOW)? dy : 0; }
  int  GetCol(void){ return (FileType != UNKNOW)? dx : 0; }
  int  GetColor(void){ return (FileType != UNKNOW)? color : 0; }
  int  GetPalette(unsigned char *palette);
};
#endif

/******************** Klases F_Write apibrezimas ******************/
#ifndef __WRITE
#define __WRITE

class F_Write : public F_Read_Write
{
  char name[80];

  int SetHeaderPCX( void );
  int SetHeaderBMP( void );
  int SetHeaderRAW( void );
  int SetHeaderRAS( void );
  int SetHeaderRIX( void );
  int SetHeaderGIF( void );
//  int SetHeaderEGA( void );

  int WriteIMA  (long PictureHandler);
  int WriteBMP  (long PictureHandler);
  int WritePCX  (long PictureHandler);
  int WriteGIF  (long PictureHandler);
//  int WriteBMP2 (long PictureHandler);
//  int WriteBMP16(long PictureHandler);
//  int WriteRIX16(long PictureHandler);
//  int WriteEGA  (long PictureHandler);

  int SetPalettePCX(unsigned char *palette);
  int SetPaletteBMP(unsigned char *palette);
  int SetPaletteRAW(unsigned char *palette);
  int SetPaletteRAS(unsigned char *palette);
  int SetPaletteRIX(unsigned char *palette);
  int SetPaletteGIF(unsigned char *palette);
//  int SetPaletteEGA(unsigned char *palette);
 public:
   F_Write(void);
  ~F_Write();
  int  Open(char *fname);
  int  Write(int PictureDX,int PictureDY,long PictureHandler);
  int  SetPalette(unsigned char *palette);
  int  SetColor(int Color);
};
#endif

