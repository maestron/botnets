#include "stdafx.h"

// all comments are in german - when i have alot of time i will translate them
// this class was written by me in 2004

//---------------------------------------------------------------------------
CNetwork::CNetwork()
{
	// alle arrays leeren bzw. mit startwerten initialisieren
	for(int i=0;i<MAX_CLIENTS;i+=1)
	{
		Clients[i]=INVALID_SOCKET;
		NewStat[i]=0;
		RecvStat[i]=0;
		CloseStat[i]=0;
		for(int a=0; a<100; a++)RecvBuffer[i][a]='\0';
		RecvBufCnt[i]=0;
	}
	lca=sizeof(SOCKADDR);
	NOC=MAX_CLIENTS;
	NOCS=0;
	ClassUse=0;
}
//---------------------------------------------------------------------------
CNetwork::~CNetwork()
{
	// wenn klasse geschlossen wird, alle verbindungen trennen und Winsock freigeben
	this->CloseAllConnections();
	this->CloseWinsock();
}
//---------------------------------------------------------------------------
void CNetwork::IPToHostname(char *IP, char *RetHostname)
{
	unsigned int addr;

	//String in reale IP umwandeln
	addr=inet_addr(IP);

	//Workstationname für IP suchen
	struct hostent* ClientName = gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);

     //Hostname kopieren
	strcpy(RetHostname,ClientName->h_name);
}
//---------------------------------------------------------------------------
int CNetwork::C_ConnectToServer(char *HostnameOrIP, int Port)
{
	//struktur mit daten füllen (ip daten usw.)
	memset(&addr,0,sizeof(SOCKADDR_IN));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(Port);
	//hostname in ip auflösen
	int ret=this->IPStringToIPStruct(HostnameOrIP,&addr);
	if(ret!=0)
	{
     	return ret;
	}

	//array auf freien platz prüfen
	for(int i=0;i<NOC;i++)
	{
		if(Clients[i]==INVALID_SOCKET)
		{
			//SOCKET ERZEUGEN
			Clients[i]=socket(PF_INET,SOCK_STREAM,0);
			if(Clients[i]==INVALID_SOCKET)
			{
				return -1;
			}			

			//verbindung herstellen
			ret=connect(Clients[i],(SOCKADDR*)&addr,sizeof(SOCKADDR));
			if(ret==0)
			{
                    NewStat[i]=1;
				return i;
			}
			else
			{
				return -19;
			}
			break;
		}
	}
     return -20;
}
//---------------------------------------------------------------------------
int CNetwork::C_RunClient(void)
{   
	rc=0;
	char temp='\0';

	// Timeout für select setzen
	Timeout.tv_usec=TOU;
	Timeout.tv_sec=TOS;
		
	// Inhalt leeren
	FD_ZERO(&fdSet);

	// alle gültigen client sockets hinzufügen (nur die, die nicht INVALID_SOCKET sind)
	for(int i=0;i<NOC;i++)
	{
		if(Clients[i]!=INVALID_SOCKET)
		{
			FD_SET(Clients[i],&fdSet);
		}
		//status arrays leeren
		NewStat[i]=0;
		RecvStat[i]=0;
		CloseStat[i]=0;
	}

	// fdSet Struktur füllen
	// (nicht vergessen den ersten parameter bei anderen betriebssystem anzugeben)
	rc=select(0,&fdSet,NULL,NULL,&Timeout);
	if(rc==SOCKET_ERROR)
	{
		return -4;
	}

	// prüfen welcher client sockets im fd_set sind
	for(int i=0;i<NOC;i++)
	{
		if(Clients[i]==INVALID_SOCKET)
		{
			// ungültiger socket, d.h. kein verbunder client an dieser position im array
			RecvStat[i]=0;
			continue;
		}

		// socket bleibt in fdSet wenn verbindung geschlossen oder daten verfügbar
		if(FD_ISSET(Clients[i],&fdSet))
		{
			//daten abrufen, status arrays setzen
			//empfangenes byte in array kopieren, wir später vor die eigentlichen daten gehängt
			rc=recv(Clients[i],&temp,1,0);
			RecvBuffer[i][RecvBufCnt[i]]=temp;
			RecvStat[i]=1;
			RecvBufCnt[i]+=1;

			//wenn rückgabewert von recv = 0 oder fehler dann wurde verbindung geschlossen
			if(rc==0 || rc==SOCKET_ERROR)
			{
				// socket schliessen
				closesocket(Clients[i]);
                    // seinen platz wieder freigeben
				Clients[i]=INVALID_SOCKET;
				CloseStat[i]=1;
				RecvStat[i]=0;
			}
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
int CNetwork::C_GetMessageFromServer(int ServerNumber, char *Buf, int BufSize)
{
	if(RecvStat[ServerNumber]==0)return -8;
	if(Clients[ServerNumber]==INVALID_SOCKET)return -21;
	if(!ServerNumber && !Buf && !BufSize)return -9;

	//temporäre variable für abruf von daten allokieren
	char *tempBuf = new char[BufSize];
	int ret=0;

	for(int i=0; i<BufSize; i++)tempBuf[i]='\0';

	//daten abrufen, aber nur die größe des puffers - der bereits abgerufenen bytes von run...()
	ret=recv(Clients[ServerNumber],tempBuf,BufSize-(RecvBufCnt[ServerNumber]),0);

	//bytes von run...() in array kopieren
	for(int c=0; c<BufSize-(RecvBufCnt[ServerNumber]); c+=1)
	{
		Buf[c]=RecvBuffer[ServerNumber][c];
	}

	//rest der daten einfügen
	int d=0;
	for(int c=RecvBufCnt[ServerNumber]; c<BufSize; c+=1)
	{
		Buf[c]=tempBuf[d];
		d+=1;
	}

	//array für nächste verwendung wieder leeren
	for(int a=0; a<100; a++)RecvBuffer[ServerNumber][a]='\0';

	RecvStat[ServerNumber]=0;
	if(ret==-1)ret=-7;

	ret=ret+(RecvBufCnt[ServerNumber]);

	RecvBufCnt[ServerNumber]=0;

	delete[] tempBuf;

	return ret;
}
//---------------------------------------------------------------------------
int CNetwork::C_SendToServer(int ServerNumber, char *Buf, int BufSize)
{
	if(!Buf && !BufSize && !ServerNumber)return -9;

	char *tempBuf = new char[BufSize];
	int ret=0;

	for(int i=0; i<BufSize; i++)tempBuf[i]='\0';

	//zu sendende daten in temporäres array kopieren
	memcpy(tempBuf,Buf,BufSize);

	if(Clients[ServerNumber]!=INVALID_SOCKET)
	{
		//daten senden
		ret=send(Clients[ServerNumber],tempBuf,BufSize,0);
	}
	else
	{
		delete[] tempBuf;
		return -21;
	}
	delete[] tempBuf;
	return 0;
}
//---------------------------------------------------------------------------
int CNetwork::C_SendToAllServer(char *Buf, int BufSize)
{
	if(!Buf && !BufSize)return -9;

	char *tempBuf = new char[BufSize];
	int ret=0;

	for(int i=0; i<BufSize; i++)tempBuf[i]='\0';

	//zu sendende daten in temporäres array kopieren
	memcpy(tempBuf,Buf,BufSize);

	for(int i=0; i<NOC; i++)
	{
		if(Clients[i]!=INVALID_SOCKET)
		{
			//daten an alle server senden
			ret=send(Clients[i],tempBuf,BufSize,0);
		}
	}

	delete[] tempBuf;

	return 0;
}
//---------------------------------------------------------------------------
int CNetwork::C_GetServerIP(int ServerNumber, char *Buf)
{
	//daten aus client info struktur kopieren und zurückliefern
	if(!ServerNumber && !Buf)return -9;
	if(Clients[ServerNumber]==INVALID_SOCKET)return -6;
	lstrcpy(Buf, inet_ntoa(ClientInfo[ServerNumber].sin_addr));
	return 0;
}
//---------------------------------------------------------------------------
int CNetwork::InitWinsock(void)
{
	//sockets für windows initialisieren
	return WSAStartup(MAKEWORD(2,0),&wsa);
}
//---------------------------------------------------------------------------
int CNetwork::S_StartServer(int Port)
{
	if(!Port)return -14;
	if(Port<0 && Port>65535)return -15;
	if(ClassUse==2)return -17;
	ClassUse=1;

	//socket erzeugen
	rc=0;
	acceptSocket=socket(AF_INET,SOCK_STREAM,0);
	if(acceptSocket==INVALID_SOCKET)
	{
		return -1;
	}

	//addr struktur mit daten füllen (verbindungsart, port usw.)
	memset(&addr,0,sizeof(SOCKADDR_IN));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(Port);
	// gewisse compiler brauchen hier ADDR_ANY
	addr.sin_addr.s_addr=INADDR_ANY;
	// socket auf festgelegten port binden
	rc=bind(acceptSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR_IN));
	if(rc==SOCKET_ERROR)
	{
		return -2;
	}

	//socket in "abhörmodus" versetzen, ab dann können verbindungen angenommen werden
	rc=listen(acceptSocket,NOC);
	if(rc==SOCKET_ERROR)
	{
		return -3;
	}

	return 0;
}
//---------------------------------------------------------------------------
int CNetwork::SetNumberOfConnections(int ClientCount)
{
	if(!ClientCount)return -9;
	//wenn anzahl der verbindungen noch nicht festgelegt wurde, dann neue zahl setzen
	//zahl muss unter maximaler anzahl liegen
	if(ClientCount>0 && ClientCount<MAX_CLIENTS && NOCS==0)
	{
		NOC=ClientCount;
		NOCS=1;
	}
	else
	{
		return -13;
	}
	return 0;
}
//---------------------------------------------------------------------------
int CNetwork::GetNumberOfConnections(void)
{
	//anzahl der maximalen verbindungen zurückliefern
	return NOC;
}
//---------------------------------------------------------------------------
void CNetwork::SetSelectTimeout(int Microseconds, int Seconds)
{
	//timeout für socket festlegen, kann performance steigern (wenn werte größer werden)
	TOU=Microseconds;
	TOS=Seconds;
}
//---------------------------------------------------------------------------
void CNetwork::GetErrorMessage(int ErrNr, char *Buf)
{
	// fehlernachrichten abrufen, dazu nachricht in array kopieren
	switch(ErrNr)
	{
		case -1:
			strcpy(Buf,"socket couldn't be created");
			break;
		case -2:
			strcpy(Buf,"socket couldn't be binded");
			break;
		case -3:
			strcpy(Buf,"socket listen error");
			break;
		case -4:
			strcpy(Buf,"socket select error");
			break;
		case -5:
			strcpy(Buf,"invalid option");
			break;
		case -6:
			strcpy(Buf,"invalid client");
			break;
		case -7:
			strcpy(Buf,"no more data");
			break;
		case -8:
			strcpy(Buf,"data must be available");
			break;
		case -9:
			strcpy(Buf,"missing parameter");
			break;
		case -10:
			strcpy(Buf,"host not found");
			break;
		case -11:
			strcpy(Buf,"no alias found");
			break;
		case -12:
			strcpy(Buf,"no ip found");
			break;
		case -13:
			strcpy(Buf,"number of clients allready set or to high/low");
			break;
		case -14:
			strcpy(Buf,"no port specified");
			break;
		case -15:
			strcpy(Buf,"port to high or low");
			break;
		case -16:
			strcpy(Buf,"server already started");
			break;
		case -17:
			strcpy(Buf,"client already started");
			break;
		case -18:
			strcpy(Buf,"undefined error");
			break;
		case -19:
			strcpy(Buf,"error while connecting");
			break;
		case -20:
			strcpy(Buf,"no more sockets available");
			break;
		case -21:
			strcpy(Buf,"invalid server");
			break;
		default:
			strcpy(Buf,"this is not a valid errornumber");
			break;
	}
}
//---------------------------------------------------------------------------
int CNetwork::S_RunServer(void)
{
	rc=0;
	char temp='\0';

	// Timeout für select setzen
	Timeout.tv_usec=TOU;
	Timeout.tv_sec=TOS;

	// Inhalt leeren
	FD_ZERO(&fdSet);
	// Den Socket der verbindungen annimmt hinzufügen
	FD_SET(acceptSocket,&fdSet);

	// alle gültigen client sockets hinzufügen (nur die die nicht INVALID_SOCKET sind)
	for(int i=0;i<NOC;i++)
	{
		if(Clients[i]!=INVALID_SOCKET)
		{
			FD_SET(Clients[i],&fdSet);
		}
		NewStat[i]=0;
		RecvStat[i]=0;
		CloseStat[i]=0;
	}

	// fdSet Struktur füllen
	// (nicht vergessen den ersten parameter bei anderen betriebssystem anzugeben)
	rc=select(0,&fdSet,NULL,NULL,&Timeout);
	if(rc==SOCKET_ERROR)
	{
		return -4;
	}

	// acceptSocket is im fd_set? => verbindung annehmen (sofern es platz hat)
	if(FD_ISSET(acceptSocket,&fdSet))
	{
		// einen freien platz für den neuen client suchen, und die verbingung annehmen
		for(int i=0;i<NOC;i++)
		{
			if(Clients[i]==INVALID_SOCKET)
			{
				Clients[i]=accept(acceptSocket,(LPSOCKADDR)&ClientInfo[i],&lca);
				NewStat[i]=1;
				break;
			}
		}
	}

	// prüfen welcher client sockets im fd_set sind
	for(int i=0;i<NOC;i++)
	{
		if(Clients[i]==INVALID_SOCKET)
		{
			// ungültiger socket, d.h. kein verbunder client an dieser position im array
			RecvStat[i]=0;
			continue;
		}

		// wenn socket in array, dann daten verfügbar bzw. verbindung getrennt
		if(FD_ISSET(Clients[i],&fdSet))
		{
			rc=recv(Clients[i],&temp,1,0);
			RecvBuffer[i][RecvBufCnt[i]]=temp;
			RecvStat[i]=1;
			RecvBufCnt[i]+=1;


			if(rc==0 || rc==SOCKET_ERROR)
			{
				closesocket(Clients[i]); // socket schliessen
				Clients[i]=INVALID_SOCKET; // seinen platz wieder freigeben
				CloseStat[i]=1;
				RecvStat[i]=0;
			}
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
int CNetwork::GetSocketStatus(int ClientOrServerNumber, int StatusNr)
{
	//status arrays abrufen
	//NewStat steht für eine neue verbindung
	//RecvStat steht für verfügbare daten
	//ClosStat Steht für eine geschlossene Verbindung
	if(!StatusNr && !ClientOrServerNumber)return -9;

	if(StatusNr==1)return NewStat[ClientOrServerNumber];
	if(StatusNr==2)return RecvStat[ClientOrServerNumber];
	if(StatusNr==3)return CloseStat[ClientOrServerNumber];
	return -5;
}
//---------------------------------------------------------------------------
int CNetwork::S_GetMessageFromClient(int ClientNumber, char *Buf, int BufSize)
{
	if(RecvStat[ClientNumber]==0)return -8;
	if(Clients[ClientNumber]==INVALID_SOCKET)return -21;
	if(!ClientNumber && !Buf && !BufSize)return -9;

	char *tempBuf = new char[BufSize];
	int ret=0;

	for(int i=0; i<BufSize; i++)tempBuf[i]='\0';

	//rufe daten aus socket ab, anzahl = abrufgröße - temporärer größe aus run...()
	ret=recv(Clients[ClientNumber],tempBuf,BufSize-(RecvBufCnt[ClientNumber]),0);

	//temporäre daten aus run...() kopieren
	for(int c=0; c<BufSize-(RecvBufCnt[ClientNumber]); c+=1)
	{
		Buf[c]=RecvBuffer[ClientNumber][c];
	}

	int d=0;
	//rest in array kopieren
	for(int c=RecvBufCnt[ClientNumber]; c<BufSize; c+=1)
	{
		Buf[c]=tempBuf[d];
		d+=1;
	}

	for(int a=0; a<100; a++)RecvBuffer[ClientNumber][a]='\0';

	RecvStat[ClientNumber]=0;
	if(ret==-1)ret=-7;

	ret=ret+(RecvBufCnt[ClientNumber]);

	RecvBufCnt[ClientNumber]=0;

	delete[] tempBuf;

	return ret;
}
//---------------------------------------------------------------------------
int CNetwork::S_SendToAllClients(char *Buf, int BufSize)
{
	if(!Buf && !BufSize)return -9;

	char *tempBuf = new char[BufSize];
	int ret=0;

	for(int i=0; i<BufSize; i++)tempBuf[i]='\0';

	memcpy(tempBuf,Buf,BufSize);

	for(int i=0; i<NOC; i++)
	{
		if(Clients[i]!=INVALID_SOCKET)
		{
			//daten senden wenn socket nicht ungültig
			ret=send(Clients[i],tempBuf,BufSize,0);
		}
	}

	delete[] tempBuf;

	return 0;
}
//---------------------------------------------------------------------------
int CNetwork::S_SendToClient(int ClientNumber, char *Buf, int BufSize)
{
	if(!Buf && !BufSize && !ClientNumber)return -9;

	char *tempBuf = new char[BufSize];
	int ret=0;

	for(int i=0; i<BufSize; i++)tempBuf[i]='\0';

	memcpy(tempBuf,Buf,BufSize);

	if(Clients[ClientNumber]!=INVALID_SOCKET)
	{
		//daten senden wenn socket gültig
		ret=send(Clients[ClientNumber],tempBuf,BufSize,0);
	}
	else
	{
		delete[] tempBuf;
		return -6;
	}

	delete[] tempBuf;

	return 0;
}
//---------------------------------------------------------------------------
int CNetwork::CloseConnection(int ClientOrServerNumber)
{
	if(Clients[ClientOrServerNumber]!=INVALID_SOCKET)
	{
		//verbindung beenden und status arrays setzen /zurücksetzen
		// socket schliessen
		closesocket(Clients[ClientOrServerNumber]);
		// seinen platz wieder freigeben
		Clients[ClientOrServerNumber]=INVALID_SOCKET;
		CloseStat[ClientOrServerNumber]=1;
		RecvStat[ClientOrServerNumber]=0;
	}
	else
	{
		return -6;
	}
	return 0;
}
//---------------------------------------------------------------------------
void CNetwork::CloseAllConnections(void)
{
	for(int i=0; i<NOC; i++)
	{
		if(Clients[i]!=INVALID_SOCKET)
		{
			// socket schliessen, wenn socket gültig ist
			closesocket(Clients[i]);
			// seinen platz wieder freigeben
			Clients[i]=INVALID_SOCKET;
			CloseStat[i]=1;
			RecvStat[i]=0;
		}
	}
}
//---------------------------------------------------------------------------
void CNetwork::CloseWinsock(void)
{
	//winsock wieder freigeben
	WSACleanup();
}
//---------------------------------------------------------------------------
int CNetwork::IPStringToIPStruct(char* hostnameOrIp, SOCKADDR_IN* addr)
{
	unsigned long ip;
	HOSTENT* he;

	// Parameter prüfen
	if(hostnameOrIp==NULL || addr==NULL)
		return SOCKET_ERROR;

	// eine IP in hostnameOrIp ?
	ip=inet_addr(hostnameOrIp);

	// bei einem fehler liefert inet_addr den Rückgabewert INADDR_NONE
	if(ip!=INADDR_NONE)
	{
		addr->sin_addr.s_addr=ip;
		return -18;
	}
	else
	{
		// Hostname in hostnameOrIp auflösen
		he=gethostbyname(hostnameOrIp);
		if(he==NULL)
		{
			return SOCKET_ERROR;
		}
		else
		{
			//die 4 Bytes der IP von he nach addr kopieren
			memcpy(&(addr->sin_addr),he->h_addr_list[0],4);
			return 0;
		}
	return -18;
	}
}
//---------------------------------------------------------------------------
int CNetwork::GetInfoAboutPC(char* hostname, char* Buf, int InfoNr)
{
	HOSTENT* he;

	strcpy(Buf,"");

	if(hostname==NULL || InfoNr==NULL || Buf== NULL)return -9;

	//daten von pc über struktur abrufen
	he=gethostbyname(hostname);
	if(he==NULL)
	{
		return -10;
	}

	if(InfoNr==1)
	{
		//pcnamen kopieren
		strcpy(Buf,he->h_name);
		return 0;
	}

	int i=0;
	while(he->h_aliases[i])
	{
		if(InfoNr==2)
		{
			// aliase kopieren
			strcat(Buf,he->h_aliases[i]);
			strcat(Buf,"; ");
		}
		i++;
	}
	if(InfoNr==2)return 0;
	if(i==0 && InfoNr==2)
	{
		return -11;
	}

	i=0;
	IN_ADDR addr;

	while(he->h_addr_list[i])
	{
		if(InfoNr==3)
		{
			// ip adressen kopieren
			addr.s_addr=*((long*)he->h_addr_list[i]);
			strcat(Buf,inet_ntoa(addr));
			strcat(Buf,"; ");
		}
		i++;
	}
	if(i==0 && InfoNr==3)return -12;

	return 0;
}
//---------------------------------------------------------------------------
int CNetwork::S_GetClientIP(int ClientNumber, char* Buf)
{
	if(!ClientNumber && !Buf)return -9;
	if(Clients[ClientNumber]==INVALID_SOCKET)return -6;
	//client ip aus struktur zurückgeben
	lstrcpy(Buf, inet_ntoa(ClientInfo[ClientNumber].sin_addr));
	return 0;
}
//---------------------------------------------------------------------------
/*
   //winsock-statusdaten abrufen
   printf("Winsock started:\n");
   printf("Version: %d.%d\n",LOBYTE(wsaData.wVersion),HIBYTE(wsaData.wVersion));
   printf("High Version: %d.%d\n",LOBYTE(wsaData.wHighVersion),HIBYTE(wsaData.wHighVersion));
   printf("Description: %s\n",wsaData.szDescription);
   printf("System Status: %s\n",wsaData.szSystemStatus);

   memset(&addr,0,sizeof(SOCKADDR_IN));
   addr.sin_family=AF_INET;
   addr.sin_port=htons(1234);
   rc=getAddrFromString(argv[1],&addr);

   s=socket(PF_INET,SOCK_STREAM,0);

   rc=connect(s,(SOCKADDR*)&addr,sizeof(SOCKADDR));
*/
//---------------------------------------------------------------------------
