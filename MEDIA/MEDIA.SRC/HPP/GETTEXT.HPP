/* InitPath.cpp
 */
extern char GlobalPath[80];  // MAXPATH

void InitPath(char *fname);
// char *GetDataName(char *fname,char *Path=GlobalPath);  // GRAPH.HPP
// char *GetImagesName(char *fname,char *Path=GlobalPath);// GRAPH.HPP
// char *GetVideoDriver(char *fname=GlobalPath);          // GRAPH.HPP
char *GetTextFile(char *fname=GlobalPath);
char *GetMMSwap(char *fname=GlobalPath);
char *GetHelpFile(char *fname=GlobalPath);
char *GetDefaultExt(char *ext=GlobalPath);
char *GetDesktopGroundImage(char *ext=GlobalPath);

/* GetText.cpp
 */
void InitText(char *fname);
void CloseText(void);
char *GetText(unsigned nr);
unsigned TextMaxLen(unsigned first,...);

/* GetHlp.cpp
 */
long GetHelp(int HelpNr,int &Size);

