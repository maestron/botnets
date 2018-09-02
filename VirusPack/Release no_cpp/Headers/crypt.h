void Crypt(unsigned char *inp, DWORD inplen, unsigned char *key, DWORD keylen = 0);
#ifndef NO_CRYPT
void decryptstrings(int authsize, int versionsize, int serversize);
#endif