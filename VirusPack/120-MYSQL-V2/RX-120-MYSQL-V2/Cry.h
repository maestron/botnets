/* |  _ \ \ \/ /    / |___ \ / _ \ TesT |  \/  |/ _ \|  _ \    \ \   / /___ \ 
   | |_) | \  /_____| | __) | | | |_____| |\/| | | | | | | |____\ \ / /  __) |
   |  _ <  /  \_____| |/ __/| |_| |_____| |  | | |_| | |_| |_____\ V /  / __/ 
   |_| \_\/_/\_\ BuZ|_|_____|\___/      |_|  |_|\___/|____/  BuZ  \_/  |_____|
   ---------------------------------------------------------------------------
   --MSSQL-NTPASS-SYM06010-MS04007-MS06040-VNCBRUTE-PSTORE-FIREFOX-SP2PATCH---  
   ---------------------------------------------------------------------------
               Greets To: THE REAL CODERS & The Ryan1918 Crew !!
 */
void Crypt(TCHAR *inp, DWORD inplen, TCHAR* key = "", DWORD keylen = 0);
#ifndef NO_CRYPT
void decryptstrings(int authsize, int versionsize);
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef DUMP_ENCRYPT
void encryptstring(char *str, char *varname, SOCKET sock, char *chan, BOOL notice);
void encryptstrings(int authsize, int versionsize, SOCKET sock, char *chan, BOOL notice);
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef SIMPLE_CRYPT
char *decrypt(char *str,int key);
char *encrypt(char *str,int key);
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef TEA_CRYPT
void code(long *data, long *key);
void decode(long *data, long *key);
void codestr(char *datastr, char *keystr);
void decodestr(char *datastr, char *keystr);
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef PLAIN_CRYPT
char *EncryptPassword(char *password, char *key);
char *DecryptPassword(char *password, char *key);
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#endif

