/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


void Crypt(unsigned char *inp, DWORD inplen, unsigned char *key, DWORD keylen = 0);
#ifndef NO_CRYPT
void decryptstrings(int authsize, int versionsize);
#endif

#ifdef DUMP_ENCRYPT
void encryptstring(char *str, char *varname, SOCKET sock, char *chan, BOOL notice);
void encryptstrings(int authsize, int versionsize, SOCKET sock, char *chan, BOOL notice);
#endif