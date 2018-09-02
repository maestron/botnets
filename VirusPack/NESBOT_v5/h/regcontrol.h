
typedef struct rquery {
	DWORD dwQuery;
	char *szQuery;
} RQUERY;

char *GetKey(HKEY root,BOOL sh=TRUE);
HKEY GetKey(char *skey);
DWORD GetType(char *key);

BOOL RegExists(HKEY root,LPCTSTR subkey,char *name,DWORD type);

BOOL RegDelete(HKEY root,LPCTSTR subkey,LPCTSTR name);

BOOL RegWrite(HKEY hKey,LPCTSTR SubKey,LPCTSTR KeyName,DWORD Type,RQUERY Data);
BOOL RegWrite(HKEY root,char *subkey,char *name,char *data,DWORD type=REG_SZ);
BOOL RegWrite(HKEY root,char *subkey,char *name,DWORD data);

BOOL RegQuery(HKEY root,LPCTSTR subkey,char *target,void *conn);
char *RegQuery(HKEY root,LPCTSTR subkey,LPCTSTR name,DWORD type=REG_SZ);
DWORD RegQuery(HKEY root,LPCTSTR subkey,LPCTSTR name,BOOL &success);

BOOL RegQueryE(char *target,void *conn,HKEY root,LPCTSTR subkey);