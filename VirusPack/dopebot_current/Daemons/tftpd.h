

#ifndef NO_TFTPD
DWORD WINAPI tftpd(LPVOID parameter);
DWORD WINAPI tftpd_handler(LPVOID parameter);
bool tftpd_request(SOCKET bsock, char *szIP);

typedef struct tftp
{
	int iPort;
	char szFileName[32];
	SOCKET bsock;
	struct sockaddr_in sin;
	char szAction[32];
	char szChannel[32];
} tftp;

typedef struct TFTP_PACKET
{
	unsigned short int opcode;
	unsigned short int blockid;
	char data[512];
} TFTP_PACKET;

typedef struct TFTP_RECEIVE
{
	unsigned short int opcode;
	unsigned short int blockid;
} TFTP_RECEIVE;
#endif