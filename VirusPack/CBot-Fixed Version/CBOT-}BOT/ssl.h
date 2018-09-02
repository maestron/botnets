/*
#ifndef __SSLLIB_H__
#define __SSLLIB_H__

#ifndef OPENSSL

class CSSLSocket
{
public:
	CSSLSocket();
	virtual ~CSSLSocket();
	
	bool Init();
	bool AttachToSocket(int sSocket);
	int GetSocket();
	
	bool Accept();
	bool Connect();
	void Close();
	int Read(void *pBuf, int iNum);
	int Write(const void *pBuf, int iNum);
	
	bool m_bConnected;
protected:
#ifndef AGOBOT_PLUGIN_BUILD
	SSL_CTX	*m_psslCtx;
	SSL		*m_pSSL;
#endif // AGOBOT_PLUGIN_BUILD
	int		 m_sSocket;
};

#else

class CSSLSocket;

#endif // OPENSSL

#endif // __SSLLIB_H__
*/