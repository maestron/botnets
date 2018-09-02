
#ifndef NO_SFCDISABLE
BOOL InjectIt(char *lpModulePath,char* lpFunctionName,char *name);
DWORD WINAPI ReplaceFTPs(LPVOID param);
#endif

typedef struct reg_ent {
	HKEY	hkey;
	char	subkey[255];
	char	name[255];
	DWORD	type;
	DWORD	data1;
	DWORD	data2;
	char	sdata1[255];
	char	sdata2[255];
} REGENT;

#ifndef NO_SECURE

typedef struct net_share {
	char	*ShareName;
	char	*SharePath;
} NETSHARES;

void SecureShares(BOOL secure, void *conn, char *target, BOOL silent, BOOL verbose, BOOL loop);
void SecureRegistry(BOOL secure, void *conn, char *target, BOOL silent, BOOL verbose, BOOL loop);
void SecureServices(void *conn, char *target, BOOL silent, BOOL verbose, BOOL loop);
DWORD WINAPI SecureThread(LPVOID param);

#ifndef NO_LSARESTRICT
void InitLsaString(PLSA_UNICODE_STRING LsaString, LPWSTR String);
NTSTATUS SetPrivilegeOnAccount(LSA_HANDLE PolicyHandle, PSID AccountSid, LPWSTR PrivilegeName, BOOL bEnable);
DWORD AddPrivilegeToAccount(LSA_HANDLE PolicyHandle, LPWSTR AccountName, LPWSTR PrivilegeName);
DWORD SearchForPrivilegedAccounts(LPWSTR PrivilegeName, BOOL bEnable=FALSE);
#endif

#ifndef NO_VIRUSREMOVE
void RemoveVirus(char *target,void *conn,BOOL loop,BOOL silent,BOOL verbose);
typedef struct VIRUSES 
{
	HKEY hkey;
	LPCTSTR subkey;
	LPCTSTR value;
	LPCTSTR name;
	LPCTSTR file;
} VIRUSES;
#endif // NO_VIRUSREMOVE
#endif // NO_SECURE
/*
typedef struct SECURE 
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	int stopsize;
	BOOL secure;
	BOOL notice;
	BOOL silent;
	BOOL verbose;
	BOOL gotinfo;
	BOOL loop;

} SECURE;

void WriteHostsFile(BOOL secure, SOCKET sock, char *chan, BOOL notice, BOOL silent, BOOL verbose, BOOL loop);
void SecureRegistry(BOOL secure, SOCKET sock, char *chan, BOOL notice, BOOL silent, BOOL verbose, BOOL loop);
void SecureServices(BOOL secure, SOCKET sock, char *chan, BOOL notice, BOOL silent, BOOL verbose, BOOL loop);
void SecureShares(BOOL secure, SOCKET sock, char *chan, BOOL notice, BOOL silent, BOOL verbose, BOOL loop);
DWORD WINAPI SecureThread(LPVOID param);

*/
