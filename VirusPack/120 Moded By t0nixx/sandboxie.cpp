#include <windows.h>
#include <string>
#include <iostream>
#include <TlHelp32.h>
#include <Psapi.h>

using namespace std;

string StripFilePath(string ImageFile);

string StripFilePath(string ImageFile)
{
   string::size_type iPos = ImageFile.find_last_of("\\");
   string StrippedFileName = ImageFile.substr(iPos+1, ImageFile.length());
   return StrippedFileName;
}

int main()
{
   string targetDLL = "SbieDll.dll"; /* The injected SandBoxie DLL.*/

   HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   PROCESSENTRY32 pEntry32 = {0};
   MODULEENTRY32  mEntry32 = {0};

    if (hProcess == INVALID_HANDLE_VALUE)
      return 0;

    pEntry32.dwSize = sizeof(PROCESSENTRY32);

   char szModuleFile[MAX_PATH] = {0}; GetModuleFileName(GetModuleHandle(NULL),
      szModuleFile, MAX_PATH-1);

   string StrippedPath = szModuleFile; StrippedPath = StripFilePath(StrippedPath);

   if (Process32First(hProcess, &pEntry32))
   {  
      while (Process32Next(hProcess, &pEntry32))
      {
         if (!strcmp(pEntry32.szExeFile, StrippedPath.c_str()))
         {
            HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,
               pEntry32.th32ProcessID);
          
            if (hModule == INVALID_HANDLE_VALUE) { continue; }

            mEntry32.dwSize = sizeof(MODULEENTRY32);
        
            if(Module32First(hModule, &mEntry32))
            {
               while (Module32Next(hModule, &mEntry32))
               {
                  if (!strcmp(mEntry32.szModule, targetDLL.c_str())) {
                     MessageBox(NULL, "Error!", "64 Bits Operating Systems Only!.", MB_OK);
                     return 0;
                  }
               }
            }
         }
      }
   }
   return 0;

}