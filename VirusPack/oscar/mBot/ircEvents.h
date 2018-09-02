#ifndef INC_IRCEVENTS_H
#define INC_IRCEVENTS_H

#include <string>
#include "irc.h"

struct relInfo_t
{
	std::string name;
	std::string time;
	std::string section;
};
class ircHandler : public ircHandlerBase
{
public:
	explicit ircHandler ();
	~ircHandler ();
	virtual void onText (irc& pIrc, const ircUser_t& pIrcUser,
		const std::string& pTarget, const std::string& pMsg, bool pIsChannel);
	virtual void onAnySend (irc& pIrc, const std::string& pMsg);
	virtual void onAnyRecv (irc& pIrc, const std::string& pMsg);
	virtual void onConnect (irc& pIrc);
};
	
#endif