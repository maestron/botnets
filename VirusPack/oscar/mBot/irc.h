#ifndef INC_IRC_H
#define INC_IRC_H

#include <string>
#include <vector>
#include <winsock2.h>
#include "string.h"

struct ircData_t
{
	ircData_t () : port(0) {}
	~ircData_t () {}
	unsigned short port;
	std::string nick;
	std::string user;
	std::string fullName;
	std::string serverPass;
};
struct ircUser_t
{
	std::string nick;
	std::string ident;
	std::string host;
};
struct mode_type
{
	bool plus;
	char mode;
	std::string arg;
};
class ircHandlerBase;
class irc;
struct ircUser_t;
namespace 
{
	inline bool isIn (const std::vector<std::string>& pV, 
		   std::vector<std::string>::size_type pIndex);
	inline ircUser_t getIrcUser (const std::string& pAddress);
	bool isChan (const std::string& pChanTypes, const std::string& pChan);

	inline bool isIn (const std::vector<std::string>& pV, 
		   std::vector<std::string>::size_type pIndex)
	{
		if (pIndex > pV.size()-1)

			return false;
		else
			return true;
	}
	inline ircUser_t getIrcUser (const std::string& pAddress)
	{
		ircUser_t ret;
		std::string s = pAddress;
		if (pAddress.empty())
			return ret;
		if (lft(s,1) == ":")
			s = rt(s,-1);
		ret.nick = token(s,"!",0);
		ret.ident = token( token(s,"!",1),"@",0);
		ret.host = token(s,"@",1);
		return ret;
	}

	bool isChan (const std::string& pChanTypes, const std::string& pChan)
	{
		if (pChanTypes.empty() || pChan.empty())
			return false;
		typedef std::string::size_type ssize_t;
		ssize_t size = pChanTypes.size();
		char determinant = pChan[0];
		for(ssize_t x=0;x<size;++x)
			if (pChanTypes[x] == determinant)
				return true;
		return false;
	}
};
class irc
{
public:
	enum ircMsg {
		error         = -1,
		socketFailed  = -2,
		varsNotSet    = -3,
		noSocket      = -4,
		connectFailed = -5,
		invalidIp     = -6,
		success       = 0

	};

	explicit irc (const ircData_t& pIrcData, ircHandlerBase& pIrcHandler);
	virtual ~irc ();
	ircMsg connect( );
	void disconnect ();
	void kick (const std::string& pChannel, const std::string& pNick, 
		const std::string& pReason = "");
	void privmsg (const std::string& pTarget, const std::string& pMsg);
	void notice (const std::string& pTarget, const std::string& pMsg);
	void join (const std::string& pChannel, const std::string& pKey = "");
	void part (const std::string& pChannel, const std::string &pReason = "");
	void nick (const std::string& pNewNick);
	void umode (const std::string& pModes);
	void mode (const std::string& pChannel, const std::string& pModes, 
		const std::string& pParams);
	void quit (const std::string& pReason = "");
	ircMsg mainLoop ();
	void haltLoop ();

	int sendRawIrc (const std::string& pRawBuf);
	void handleMsg (const std::string& pMsg);
private:
	ircData_t mIrcData;
	std::string mCurNick;
	std::string mChanTypes;
	SOCKET mSocket;
	bool mIsConnected;
	bool mKeepLooping;
	ircHandlerBase *mIrcHandler;
	irc (const irc&);
	irc& operator=(const irc&);
};
class ircHandlerBase
{
private:
	ircHandlerBase(const ircHandlerBase&);
	ircHandlerBase& operator=(const ircHandlerBase&);
protected:
	ircHandlerBase()
	{
	}
public:
	virtual ~ircHandlerBase()
	{
	}
	virtual void onConnect (irc& pIrc)
	{
	}
	virtual void onDisconnect (irc& pIrc)
	{
	}
	virtual void onText (irc& pIrc,const ircUser_t& pIrcUser,
		const std::string& pTarget, const std::string& pMsg, bool pIsChannel)
	{
	}
	virtual void onNotice (irc& pIrc,const ircUser_t& pIrcUser, 
		const std::string& pTarget,const std::string& pMsg, bool pIsChannel)
	{
	}
	virtual void onAction (irc& pIrc, const ircUser_t& pIrcUser, 
		const std::string& pTarget, const std::string& pMsg, bool pIsChannel)
	{
	}
	virtual void onKick (irc& pIrc,const std::string& pChannel, 
		const std::string& pKickee, const ircUser_t& pKicker, 
		const std::string& pReason)
	{
	}
	virtual void onDCCChat (irc& pIrc,const ircUser_t& pIrcUser,
		const std::string& pTarget,const unsigned long pLongIp,
		const unsigned int pPort, bool pIsChannel) 
	{
	}
	virtual void onDCCSend (irc& pIrc,const ircUser_t& pIrcUser, 
		const std::string& pTarget,const std::string& pFileName, 
		const unsigned long pLongIp, const unsigned int pPort, 
		const unsigned long pFileSize, bool pIsChannel)
	{
	}
	virtual void onCTCP (irc& pIrc,const ircUser_t& pIrcUser, 
		const std::string& pTarget, const std::string& pMsg)
	{
	}
	virtual void onCTCPReply (irc& pIrc, const ircUser_t& pIrcUser,
		const std::string& pTarget, const std::string& pMsg)
	{
	}
	virtual void onInvite (irc& pIrc,const ircUser_t& pIrcUser, 
		const std::string& pChannel)
	{
	}
	virtual void onJoin (irc& pIrc, const ircUser_t& pIrcUser,
		const std::string& pChannel)
	{
	}
	virtual void onPart (irc& pIrc, const ircUser_t& pIrcUser,
		const std::string& pChannel, const std::string& pReason)
	{
	}
	virtual void onTopic (irc& pIrc, const ircUser_t& pIrcUser,
		const std::string& pChannel, const std::string& pTopic)
	{
	}
	virtual void onMode (irc& pIrc, const ircUser_t& pIrcUser,
		const std::string& pChannel, const std::string& pModes,
		const std::string& pModeArgs)
	{
	}
	virtual void onNick (irc& pIrc, const ircUser_t& pIrcUser,
		const std::string& pNewNick)
	{
	}
	virtual void onOp (irc& pIrc, const ircUser_t& pOper, const std::string& pChannel,
		const std::string& pOpee)
	{
	}
	virtual void onDeOp (irc& pIrc, const ircUser_t& pDeOper,
		const std::string& pChannel, const std::string& pDeOpee)
	{
	}
	virtual void onBan (irc& pIrc, const ircUser_t& pBanner,
		const std::string& pChannel, const std::string& pBannee)
	{
	}
	virtual void onUnBan (irc& pIrc, const ircUser_t& pUnBanner,
		const std::string& pChannel, const std::string& pUnBannee)
	{
	}
	virtual void onQuit (irc& pIrc, const ircUser_t& pIrcUser,
		const std::string& pQuitMsg)
	{
	}
	virtual void onVoice (irc& pIrc, const ircUser_t& pVoicer,
		const std::string& pChannel, const std::string& pVoicee)
	{
	}
	virtual void onDeVoice (irc& pIrc, const ircUser_t& pDeVoicer,
		const std::string& pChannel, const std::string& pDeVoicee)
	{
	}
	virtual void onHalfOp (irc& pIrc, const ircUser_t& pHalfOper,
		const std::string& pChannel, const std::string& pHalfOpee)
	{
	}
	virtual void onDeHalfOp (irc& pIrc, const ircUser_t& pHalfDeOper,
		const std::string& pChannel, const std::string& pHalfDeOpee)
	{
	}
	virtual void onAnyRecv (irc& pIrc, const std::string& pMsg)
	{
	}
	virtual void onAnySend (irc& pIrc, const std::string& pMsg)
	{
	}
};



#endif // INC_IRC_H
