#ifndef _IMAGES_
#define _IMAGES_

int GetInfo  (char *fname,int &dx,int &dy);
int GetPalette(char *fname,char *palette);
int ReadImage(char *fname,long PictureHandler);
int WriteImage(char *fname,long PictureHandler,int dx,int dy,char *palette=0l,int color=256);
char huge * FarMalloc(int col,int row,int &MemRow,char PerCent);
int FilesFilter(char *fname);

#endif