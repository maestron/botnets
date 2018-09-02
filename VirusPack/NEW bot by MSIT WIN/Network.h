#ifndef NETWORK_H
#define NETWORK_H

#include "Includes.h"
#include "Config.h"

class Net
{
public:
    
	//Net();
	//Net(const Net& c);
	//~Net() {}

	void SetAddrStructure(SOCKET sock, struct sockaddr_in addr, int port, char *ip); // setamo sockaddr_in
    int Connect();
	
	void Send(char *text, SOCKET sock);
	char *Recv(SOCKET sock);
	
	void QuitConnection();

	char *GetLocalIp();

	int WebDownload(char *server, int port, char *down_file, char *file_position, SOCKET sock);

private:
	SOCKET BotSocket;
	struct sockaddr_in BotAddress;
	struct hostent     *host;
	//struct hostent *host;

	/* send() */
	int STextLen;
	char *SText;

	/* recv() */
	char *RText;

	/* WebDownload() */
    
};

#endif // NETWORK_H