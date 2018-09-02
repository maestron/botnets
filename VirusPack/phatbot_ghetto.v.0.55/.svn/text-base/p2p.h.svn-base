#ifndef __P2P_H__
#define __P2P_H__

#include "cstring.h"
#include "utility.h"

using namespace std;

class CP2PConn;
class CP2PServer;
class CP2PManager;
class CP2PTarget;

#define P2P_SERVER_PORT 24288

class CP2PConn : public CThread
{
public:
	CP2PConn();
	virtual ~CP2PConn();
	void SetManager(CP2PManager *pManager);
	void SetServer(const char *szServer, int iPort);
	const char *GetServer();
	bool GotServer();
	bool IsConnected();
	bool IsRunning();
	void QueryServers();
	virtual void *Run();
	CMsgIface m_cMsgIface;			// The network message Interface
protected:
	CString m_sServer;				// Server hostname/ip
	int m_iPort;					// Server port
	CP2PManager *m_pManager;		// Pointer to the manager
	bool m_bConnected;				// Am I connected to the server ?
	bool m_bGotServer;				// Do I have a server set ?
	bool m_bSeeded;					// Am I seeded already ?
	bool m_bRunning;				// Am I running ?
	int m_sClientSock;				// Client socket to be connected to the server
};

class CP2PServer : public CThread
{
public:
	CP2PServer();
	virtual ~CP2PServer();
	void SetManager(CP2PManager *pManager);
	bool IsRunning();
	virtual void *Run();
	int m_sListenSock;				// Listen socket
	CMsgIface m_cMsgIface;			// The network message Interface
protected:
	CString m_sClientIp;			// Ip of the client
	CString m_sLocalIp;				// Ip of the server
	CP2PManager *m_pManager;		// Pointer to the manager
	int m_sServerSock;				// Server socket to be connected to the client
	bool m_bRunning;				// Am I running ?
};

class CP2PManager
{
public:
	void Init();
	void Deinit();
	bool Think();
	void AddServer(const char *szServer);
	void AddServer(const char *szServer, int iPort);
	void QueryServers();

	void Broadcast(message *pMsg);
	void Broadcast(const char *szCommand, const char *szParams, const int iContentLength, const char *szContent);
	void Broadcast(const char *szCommand, const char *szParams, const char *szId, const int iContentLength, const char *szContent);

	void AddTarget(CP2PTarget *pTarget);
	void DelTarget(CP2PTarget *pTarget);
	void ForTargets(message *pMsg);

	int m_iMaxConns;				// Maximum number of connections
	int m_iMaxServs;				// Maximum number of servers
	list<CString*> m_lServers;		// List of server adresses
	list<CString*> m_lIdCache;		// Message Ids that passed through recently
protected:
	int m_iNumConns;				// Number of connections
	int m_iNumServs;				// Number of servers
	int m_sListenSock;				// Listen socket
	list<CP2PConn*> m_lConns;		// Connection list
	list<CP2PServer*> m_lServs;		// Server list
	list<CP2PTarget*> m_lTargets;	// Target list
};

class CP2PTarget
{
public:
	virtual void Recv(char *szData, int iDataLen, message *pMsg)=0;
	void Send(char *szData, int iDataLen);
	void Send(char *szString);
	void SetManager(CP2PManager *pManager);
protected:
	CP2PManager *m_pManager;		// Pointer to the manager
};

#endif // __P2P_H__
