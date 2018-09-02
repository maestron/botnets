/*
	Original Netstatp code by: Mark Russinovich from: www.sysinternals.com <3
	Ported to Reptile by someone you probably don't know.
*/
#ifndef NO_NETSTATP

#define HOSTNAMELEN		256
#define PORTNAMELEN		256
#define ADDRESSLEN		HOSTNAMELEN+PORTNAMELEN

#define FLAG_ALL_ENDPOINTS	1
#define FLAG_SHOW_NUMBERS	2

DWORD WINAPI NetstatpThread(LPVOID param);
#endif
