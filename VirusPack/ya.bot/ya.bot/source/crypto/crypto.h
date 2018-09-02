/*  ya.bot  */

DWORD crypto_elfhash(char *pszBuffer);

#ifndef NO_CRYPTORC4
void crypto_rc4(char *pszBuffer, DWORD dwBufferLength, char *pszKey, DWORD dwKeyLength);
#endif

void crypto_rot47(char *pszBuffer);

#ifndef NO_CRYPTOSHA256
void crypto_sha256(char *pszData, DWORD dwDataLength, char *pszBuffer, DWORD dwBufferSize);
#endif

inline void crypto_xor(char *pszBuffer, int nKey);
void crypto_xorcommands();
void crypto_xorconfig();
void crypto_xorstrings();