USHORT checksum(USHORT *buffer, int size);
char *GetIP(SOCKET sock);
bool IsPrivate(const char *ip);
unsigned long ResolveAddress(char *szHost);
int fphost(char *sHost,int iFpType);


//---- OS DETECT ------//

//os types
#define OS_UNKNOWN			0
#define OS_WINNT			1
#define OS_WIN2K			2
#define	OS_WINXP			3
#define OS_WIN2K3			4
#define OS_LINUX			5

//os detect types
#define FP_RPC				1
#define FP_SMB				2

#define DCE_PKT_BINDACK		0x0C
#define DCE_PKT_RESPONSE	0x02

//---- END OS DETECT ------//