
#ifndef MM_HPP
#define MM_HPP

#define ERROR_HANDLER 0xffff

int MRead(unsigned long index,
	  char huge *Buffer,
	  unsigned long Shift = 0x0,
	  unsigned long Size = 0xffffffffL);
int MWrite(unsigned long index,
	   char huge *Buffer,
	   unsigned long Shift = 0x0,
	   unsigned long Size = 0xffffffffL);
unsigned long MAlloc(unsigned long Size);
void MFree(unsigned long index);
void InitMemoryManager(char *fname);
void CloseMemoryManager(void);
char huge *GetMMBufferPointer(unsigned long index);
void MLock(unsigned long index);
void MUnLock(unsigned long index);
void MMInfo(long &ExpAllocSize,long &ExpFreeSize,long &ExtAllocSize,long &ExtFreeSize,long &DiskAllocSize,long &DiskFreeSize);
long Farcoreleft(void);
long FreeMem(void);

#endif