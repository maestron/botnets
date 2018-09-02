#include "Include.h"
#include "Hell.h"
#pragma warning (disable:4786)

void *CConnectIRC::Run(void)
{
	try{
		while(1) {
			if (!noReconnect) {
				if (ConnectServer()) {
					cout << "[x] Connected to " << cConf.cServer << ":" << cConf.cPort << " sucessfully." << endl;
					IRCRunning = true;						
					cConf.cRealNick = RndNick(cConf.cNick);				
					SendData("NICK %s\r\nUSER %s 0 0 :%s\r\n",cConf.cRealNick.c_str(),cConf.cRealNick.c_str(),cConf.cRealNick.c_str());		
					BOT->hMain.sTopic = true;
				} else {
					IRCRunning = false;
				}
				while(1) {
					if (!ReceiveIRCBuffer() || !IRCRunning) 
						break;
					
				}
				Disconnect();
				Sleep(5000);
				
			}
		}
	} catch (...) {
		Sleep(2500);
		//vRunning = false;
		return Run();		
	}
	
	return NULL;
}

string CConnectIRC::RndNick(string vPrefix)
{
	string vRet;
	srand(GetTickCount());
	for(int i=0; i<10; i++) 
		vRet += char((rand()%26)+97);
	return vPrefix+vRet;
}

bool CConnectIRC::ConnectServer(void)
{
	SOCKADDR_IN vSin;
	
	vSin.sin_family = AF_INET;
	vSin.sin_port = htons(cConf.cPort);
	vSin.sin_addr.s_addr = ResolveAddress(cConf.cServer);
	
	vSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (vSocket == SOCKET_ERROR) {
		cout << "Socket() socket error" << endl;
		closesocket(vSocket);
		return false;
	}
	
	cout << "[x] Attempting to connect..." << endl;
	if (connect(vSocket,(LPSOCKADDR)&vSin,sizeof(vSin)) == SOCKET_ERROR) {
		closesocket(vSocket);
		cout << "Connect() connect error" << endl;	
		return false;
	}
	
	return true;
}

bool CConnectIRC::ReceiveIRCBuffer(void)
{
	const int vBufSize = 4096;
	CCmd cCmd;
	char vBuffer[vBufSize];
	memset(vBuffer,0,vBufSize);
	string vBuf; 
	string contents;
	int bytesRecv = recv(vSocket,vBuffer,vBufSize - 1,0);
	if ( bytesRecv == 0 || GetLastError() != 0) 
		return false;
	else {
		if (GetLastError() != 0)
			return false;
			// check buffer for input
			contents = vBuffer;
			vector <string> eBuffer;
			eBuffer = ParseIRCBuffer(contents, "\r\n");
			for (int k=0;k<eBuffer.size();k++) {
				vector <string> iBuffer; 
				iBuffer = ParseIRCBuffer(eBuffer[k], " ");
				if (iBuffer.size()>1) {
					cCmd.InterpretCmd(iBuffer);
					cout << eBuffer[k] << endl;						
				}
			}
			
		return true;	
	}
}

vector <string> CConnectIRC::ParseIRCBuffer(string vBuffer, string type)
{
	vector <string> contents;
	int currentpos = -1;
	int prevpos = 0;
	int counter = 0;

	while (1)
	{
		currentpos = vBuffer.find(type, prevpos);
		if (currentpos == -1) break;
		contents.push_back(vBuffer.substr(prevpos, currentpos-prevpos));
		prevpos = currentpos+type.length();
	}
	contents.push_back(vBuffer.substr(prevpos, vBuffer.length()-prevpos-type.length()+1));
	return contents; 
}

void CConnectIRC::SendData(const char *vBuffer,...)
{	
	va_list va_alist; char formatbuf[8192]; va_start(va_alist, vBuffer);
	_vsnprintf(formatbuf, sizeof(formatbuf), vBuffer, va_alist); va_end(va_alist);

	if (send(vSocket,formatbuf,strlen(formatbuf),0) == SOCKET_ERROR) {
		closesocket(vSocket);
		cout << "Send() error" << endl;		
	}	
}

void CConnectIRC::Disconnect(void)
{
	closesocket(vSocket);
}

unsigned long CConnectIRC::ResolveAddress(string server)
{
	
	unsigned long IP = inet_addr(server.c_str());
	if (IP==INADDR_NONE) {
		hostent *pHE = gethostbyname(server.c_str());
		if (pHE == 0) 
			return INADDR_NONE;
		IP = *((unsigned long *)pHE->h_addr_list[0]);		
	}

	return IP;
}
