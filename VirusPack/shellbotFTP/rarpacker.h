/** rarpacker.h **/

#include "vInclude.h"

#ifndef NO_RAR_PACKER

DWORD crc32(void *xdata,int xsize);
BOOL AddToRar(char RarFile[],char FileToAdd[],char PackedFileName[],DWORD Attributes);

#endif