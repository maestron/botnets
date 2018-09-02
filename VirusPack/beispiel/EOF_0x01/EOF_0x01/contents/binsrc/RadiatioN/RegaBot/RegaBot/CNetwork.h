#define MAX_CLIENTS 2

/*

return values:
0 = success
<0 = error
0< = success and value for result (e.g. returned bytes)

*/

#define ICMP_ECHOREPLY 0
#define ICMP_UNREACHABLE 3
#define ICMP_ECHO 8

#define ICMP_CODE_NETWORK_UNREACHABLE 0
#define ICMP_CODE_HOST_UNREACHABLE 1

#define ICMP_MIN_SIZE 8

#define STATUS_FAILED 0xFFFF

#define PING_RECVTIMEO 1000 //Wait max x / 1000 seconds
#define PING_FAILED 0xFFFFF0
#define PING_TIMEOUT 0xFFFFF1
#define PING_NOHOST 0xFFFFF2

class CNetwork
{    
	public:
		//general network functions
		CNetwork();
		~CNetwork();
		int CloseConnection(int ClientOrServerNumber);
		void CloseAllConnections(void);
		void CloseWinsock(void);
		int GetInfoAboutPC(char* hostname, char* Buf, int InfoNr);
		void GetErrorMessage(int ErrNr, char* Buf);
		int InitWinsock();
		int SetNumberOfConnections(int ClientCount);
		int GetNumberOfConnections(void);
		int GetSocketStatus(int ClientOrServerNumber, int StatusNr);
		void SetSelectTimeout(int Microseconds, int Seconds);
		DWORD PingComputer(const char *szIP, unsigned int nDataSize);
		void IPToHostname(char *IP, char *RetHostname);

		//functions for a server
		int S_StartServer(int Port);
		int S_RunServer(void);
		int S_GetMessageFromClient(int ClientNumber, char *Buf, int BufSize);
		int S_SendToAllClients(char *Buf, int BufSize);
		int S_SendToClient(int ClientNumber, char *Buf, int BufSize);
		int S_GetClientIP(int ClientNumber, char *Buf);

        //functions for a client
		int C_ConnectToServer(char *HostnameOrIP, int Port);
		int C_RunClient(void);
		int C_GetMessageFromServer(int ServerNumber, char *Buf, int BufSize);
		int C_SendToServer(int ServerNumber, char *Buf, int BufSize);
		int C_SendToAllServer(char *Buf, int BufSize);
		int C_GetServerIP(int ServerNumber, char *Buf);

	private:
		SOCKET Clients[MAX_CLIENTS], acceptSocket;
		SOCKADDR_IN ClientInfo[MAX_CLIENTS], addr;
		int rc, lca, NOC, NOCS, NewStat[MAX_CLIENTS], RecvStat[MAX_CLIENTS], CloseStat[MAX_CLIENTS], TOU, TOS;
		WSADATA wsa;
		FD_SET fdSet;
		timeval Timeout;
		char RecvBuffer[MAX_CLIENTS][100];
		int ClassUse, RecvBufCnt[MAX_CLIENTS];
		int IPStringToIPStruct(char* hostnameOrIp, SOCKADDR_IN* addr);
		void WinsockStartup();
		unsigned short Checksum(unsigned short *buffer, int size);

		typedef struct
		{
			unsigned int   h_len:4;          
			unsigned int   version:4;        
			unsigned char  tos;              
			unsigned short total_len;        
			unsigned short ident;            
			unsigned short frag_and_flags;   
			unsigned char  ttl;              
			unsigned char  proto;            
			unsigned short checksum;         
			unsigned int   sourceIP;         
			unsigned int   destIP;           
		}ip_header_t;

		typedef struct
		{
			char           i_type;    
			char           i_code;    
			unsigned short i_cksum;   
			unsigned short i_id;      
			unsigned short i_seq;     
			unsigned long  timestamp; 
		}icmp_header_t;

	protected:
};
