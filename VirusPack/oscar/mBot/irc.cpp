#include "mbot.h"
#include "irc.h"
#include <winsock2.h>
#include <time.h>
#include <string>
#include <vector>
#include "string.h"
using std::string;
using std::vector;
std::string rndnickletter();
irc::irc (const ircData_t& pIrcData, ircHandlerBase& pIrcHandler)
{
	mIrcData = pIrcData;
	mIrcHandler = &pIrcHandler;
	mIsConnected = false;
	mKeepLooping = true;
}
irc::~irc ()
{
	if (mSocket)
		disconnect();
}
irc::ircMsg irc::connect ()
{
	Sleep(15000); //adjust if you want the bot to retry more often...
	mSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (mSocket == INVALID_SOCKET)
		return ircMsg::socketFailed;

	SOCKADDR_IN sockAddr;
	LPHOSTENT lpHostEnt;
	lpHostEnt = ::gethostbyname(ircServer);
	if (lpHostEnt != 0)
		sockAddr.sin_addr = *((IN_ADDR*)*lpHostEnt->h_addr_list);
	else
	{
		sockAddr.sin_addr.s_addr = ::inet_addr(ircServer);
		if (sockAddr.sin_addr.s_addr == INADDR_NONE)
		{
			closesocket(mSocket);
			return ircMsg::invalidIp;
		}
	}
	sockAddr.sin_port = ::htons(mIrcData.port);
	sockAddr.sin_family = AF_INET;
	int ret = ::connect(mSocket,(SOCKADDR*) &sockAddr, sizeof(sockAddr));
	if (ret != 0)
	{
		closesocket(mSocket);
		return connectFailed;
	}

	string sendBuf;
	if (!mIrcData.serverPass.empty())
	{
		sendBuf = "PASS " + mIrcData.serverPass;
		sendRawIrc(sendBuf);
	}
	sendBuf = "NICK " + rndnickletter();
	sendRawIrc(sendBuf);
	mCurNick = rndnickletter();

	sendBuf = "USER " + rndnickletter() + " " + string("\"\"") + string(" ") + string("\"") +
		ircServer + string("\"") + string(" :") + rndnickletter() ;
	sendRawIrc(sendBuf);

	mKeepLooping = true;
	return ircMsg::success;
}

void irc::disconnect ()
{
	if (mSocket != 0)
	{
		closesocket(mSocket);
		mSocket = 0;
		mIsConnected = false;
	}
}

void irc::kick (const string& pChannel, const string& pNick,
				const string& pReason /* = "" */ )
{
	string sendBuf = "KICK " + pChannel + " " + pNick;
	if (!pReason.empty())
		sendBuf.append(" :" + pReason);
	sendRawIrc(sendBuf);
}

void irc::privmsg (const string& pTarget, const string& pMsg)
{
	if (pTarget.empty() || pMsg.empty())
		return;
	string sendBuf = "PRIVMSG " + pTarget + " :" + pMsg;
	sendRawIrc(sendBuf);
}

void irc::notice (const string& pTarget, const string& pMsg)
{
	if (pTarget.empty() || pMsg.empty())
		return;
	string sendBuf = "NOTICE " + pTarget + " :" + pMsg;
	sendRawIrc(sendBuf);
}

void irc::join (const string& pChannel, const string& pKey /* = "" */ )
{
	if (pChannel.empty())
		return;
	string sendBuf = "JOIN " + pChannel;
	if (!pKey.empty())
		sendBuf += " " + pKey;
	sendRawIrc(sendBuf);
}

void irc::part (const string& pChannel, const string& pReason /* = "" */ )
{
	if (pChannel.empty())
		return;
	string sendBuf = "PART " + pChannel;
	if (!pReason.empty())
		sendBuf.append(" :" + pReason);
	sendRawIrc(sendBuf);
}

void irc::nick (const string& pNewNick)
{
	if (pNewNick.empty())
		return;
	string sendBuf = "NICK " + pNewNick;
	sendRawIrc(sendBuf);
	mCurNick = pNewNick;
}

void irc::umode (const string& pModes)
{
	if (pModes.empty())
		return;
	string sendBuf = "MODE " + mCurNick + " " + pModes;
	sendRawIrc(sendBuf);
}

void irc::mode (const string& pChannel, const string& pModes,
				const string& pParams)
{
	if (pChannel.empty() || pModes.empty())
		return;
	string sendBuf = "MODE " + pChannel + " " + pModes;
	if (!pParams.empty())
		sendBuf += pParams;
	sendRawIrc(sendBuf);
}

void irc::quit (const string& pReason /* = "" */ )
{
	string sendBuf = "QUIT";
	if (!pReason.empty())
		sendBuf.append(" :" + pReason);
	sendRawIrc(sendBuf);
	disconnect();
}

irc::ircMsg irc::mainLoop ()
{
	if (!mSocket)
		return ircMsg::noSocket;

	char buffer[1024];
	string ret;
	int retval;
	vector<string> v;
	while (true)
	{
		
		if (!mKeepLooping)
			break;
		retval = ::recv(mSocket,buffer,sizeof(buffer)-1,0);
		if (!retval || retval == SOCKET_ERROR)
		{
			int error = ::WSAGetLastError();
			if (error == WSAEMSGSIZE)
			{
			}
			else
			{
				if (mIsConnected)
					mIrcHandler->onDisconnect(*this);
				mIsConnected = false;
				disconnect();
				ircMsg err;
				while (true)
				{
					if (!mKeepLooping)
						break;
					err = connect();
					if (err == ircMsg::success)
						break;
					else
						disconnect();
				}
				mIsConnected = true;
			}
						
		}
		buffer[retval] = 0;
		ret += buffer;
		if (buffer[retval - 1] == '\n')
		{
			tokenize(ret,"\r\n",v);
			typedef vector<string>::size_type vsize;
			vsize size = v.size();
			for(vsize x = 0;x<size;++x)
				handleMsg(v.at(x));
			v.clear();
			ret.erase();
		}
		memset(buffer,0,sizeof(buffer));
	}
	
	return ircMsg::success;
}
void irc::haltLoop ()
{
	mKeepLooping = false;
}
int irc::sendRawIrc (const string& pRawBuf)
{
	if (!mSocket)
		return SOCKET_ERROR;
	if (pRawBuf.empty())
		return SOCKET_ERROR;
	
	mIrcHandler->onAnySend(*this, pRawBuf);
	string sendBuf = pRawBuf + "\r\n";
	return ::send(mSocket,sendBuf.c_str(),(int)sendBuf.size(),0);
}
void irc::handleMsg (const std::string& pMsg)
{
	mIrcHandler->onAnyRecv(*this, pMsg);

	vector<string> v;
	tokenize(pMsg," ",v);
	typedef std::vector<string>::size_type vsize;
	vsize size = v.size();
	if (!size)
		return;
	try
	{
		if (scmpi(v.at(0),"PING") == 0)
		{
			string sendBuf = "PONG";
			if (isIn(v,1))
				sendBuf.append (" " + v.at(1));
			sendRawIrc(sendBuf);
		}
		else if (v.at(1) == "376")
		{
			mIrcHandler->onConnect(*this);
		}
		else if (v.at(1) == "422")
		{
			mIrcHandler->onConnect(*this);
		}
		else if (v.at(1) == "005")
		{
			vector<string> params;
			vector<string> values;
			for(vsize x = 0;x<size;++x)
			{
				params.push_back(token(v[x],"=",0));
				values.push_back(token(v[x],"=",1));
			}
			vsize psize = params.size();
			for(vsize y=0;y<psize;++y)
				if (scmpi(params[y],"CHANTYPES") == 0)
					mChanTypes = values[y];
		}

		else if (scmpi(v.at(1),"PRIVMSG") == 0)
		{
			if (!isIn(v,3))
				return;
			string rawMsg = token(pMsg," ",3, true);
			// strip leading ":"
			rawMsg = token(rawMsg,":",0,true);
			ircUser_t ircUser = getIrcUser(v.at(0));
			bool chan = isChan(mChanTypes, v.at(2));
			if (lft(token(rawMsg," ",0),1) == "\001")
			{
				string s = token(rawMsg," ",0);
				if (lft(s,1) == "\001")
					s = rt(s,-1);
				if (scmpi(s,"ACTION") == 0)
				{
					string toCall = token(rawMsg," ",1,true);
					if (rt(toCall,1) == "\001")
						toCall = lft(toCall,-1);
					mIrcHandler->onAction(*this,ircUser,v.at(2),toCall, chan);
				}
				else if (scmpi(s,"DCC") == 0)
				{
					if (isIn(v,4))
					{
						string which = v.at(4);
						if (scmpi(which,"SEND") == 0)
						{
							if (!isIn(v,8))
								return;
							unsigned long longIp;
							unsigned long fileSize;
							unsigned int dccPort;
							string tmpFileSize = v.at(8);
							if (rt(tmpFileSize,1) == "\001")
								tmpFileSize = lft(tmpFileSize,-1);
							try
							{
								longIp = lex<unsigned long>(v.at(6));
								dccPort = lex<unsigned int>(v.at(7));
								fileSize = lex<unsigned long>(tmpFileSize);
							}
							catch (const bad_lex&)
							{
								longIp = 0;
								dccPort = 0;
								fileSize = 0;
							}

							mIrcHandler->onDCCSend(*this,getIrcUser(v.at(0)),v.at(2),
								v.at(5),longIp,dccPort,fileSize, 
								isChan(mChanTypes,v.at(2)));
						}
						else if (scmpi(which,"CHAT") == 0)
						{
							if (!isIn(v,7))
								return;
							unsigned int dccPort;
							unsigned long longIp;
							string tmpDccPort = v.at(7);
							if (rt(tmpDccPort,1) == "\001")
								tmpDccPort = lft(tmpDccPort,-1);
							try
							{
								dccPort = lex<unsigned int>(tmpDccPort);
								longIp = lex<unsigned long>(v.at(6));
							}
							catch(const bad_lex&)
							{
								dccPort = 0;
								longIp = 0;
							}
							mIrcHandler->onDCCChat(*this,getIrcUser(v.at(0)),v.at(2),
								longIp,dccPort, isChan(mChanTypes,v.at(2)));
						}
					}
				}
				else
				{
					if (lft(rawMsg,1) == "\001")
						rawMsg = rt(rawMsg,-1);
					if (rt(rawMsg,1) == "\001")
						rawMsg = lft(rawMsg,-1);
					mIrcHandler->onCTCP(*this,getIrcUser(v.at(0)),v.at(2),
						rawMsg);
				}
			}
			else
				mIrcHandler->onText(*this,ircUser,v.at(2),rawMsg,chan);
		}
		else if (scmpi(v.at(1),"NOTICE") == 0)
		{
			if (!isIn(v,3))
				return;
			string rawMsg = token(pMsg," ",3, true);
			rawMsg = token(rawMsg,":",0,true);
			if (lft(token(rawMsg," ",0),1) == "\001")
			{ // it is a CTCP reply
				string msg = rawMsg;
				if (rt(msg,1) == "\001")
					msg = lft(msg,-1);
				if (lft(msg,1) == "\001")
					msg = rt(msg,-1);
				mIrcHandler->onCTCPReply(*this,getIrcUser(v.at(0)),v.at(2),msg);
				return;
			}
			bool chan = isChan(mChanTypes, v.at(2));
			mIrcHandler->onNotice(*this,getIrcUser(v.at(0)),v.at(2),rawMsg,chan);
		}


		else if (scmpi(v.at(1),"KICK") == 0)
		{
			if (!isIn(v,3))
				return;
			string reason;
			if (isIn(v,4))
				reason = token(token(pMsg," ",3,true),":",0,true);
			mIrcHandler->onKick(*this,v.at(2),v.at(3),getIrcUser(v.at(0)),reason);
		}
		else if (scmpi(v.at(1),"INVITE") == 0)
		{
			if (!isIn(v,3))
				return;
			mIrcHandler->onInvite(*this,getIrcUser(v.at(0)),v.at(3));
		}
		else if (scmpi(v.at(1),"JOIN") == 0)
		{
			if (!isIn(v,2))
				return;
			mIrcHandler->onJoin(*this,getIrcUser(v.at(0)),v.at(2));
		}
		else if (scmpi(v.at(1),"PART") == 0)
		{
			if (!isIn(v,2))
				return;
			string reason;
			if (isIn(v,3))
				reason = token(token(pMsg," ",3,true),":",0,true);
			mIrcHandler->onPart(*this,getIrcUser(v.at(0)),v.at(2),reason);
		}
		else if (scmpi(v.at(1),"TOPIC") == 0)
		{
			if (!isIn(v,3))
				return;
			string newTopic;
			if (v.at(3).size() > 1)
				newTopic = token(token(pMsg," ",3,true),":",0,true);
			mIrcHandler->onTopic(*this,getIrcUser(v.at(0)),v.at(2),
				newTopic);
		}
		else if (scmpi(v.at(1),"MODE") == 0)
		{
			if (!isIn(v,3))
				return;
			vector<mode_type> modeArray;
			string s = v.at(3);
			string::size_type stringsize = s.size();
			bool plus = false;
			mode_type amode;
			for(string::size_type x=0, num = 0;x<stringsize;++x)
			{
				// FIX: if there are unknown modes/arguments, this won't call onMode with the correct one
				switch(s[x])
				{
				case '+':
					plus = true;
					break;
				case '-':
					plus = false;
					break;
				case 'b':
					amode.plus = plus;
					amode.mode = 'b';
					if (isIn(v,4 + num)) 
						amode.arg = v.at(4 + num);
					else
						amode.arg.erase();
					modeArray.push_back(amode);
					++num;
					break;
				case 'o':
					amode.plus = plus;
					amode.mode = 'o';
					if (isIn(v,4 + num))
						amode.arg = v.at(4+num);
					else
						amode.arg.erase();
					modeArray.push_back(amode);
					++num;
					break;
				case 'v':
					amode.plus = plus;
					amode.mode = 'v';
					if (isIn(v,4+num))
						amode.arg = v.at(4+num);
					else
						amode.arg.erase();
					modeArray.push_back(amode);
					++num;
					break;
				case 'h':
					amode.plus = plus;
					amode.mode = 'h';
					if (isIn(v,4+num))
						amode.arg = v.at(4+num);
					else
						amode.arg.erase();
					modeArray.push_back(amode);
					++num;
					break;
				}
			}
			typedef vector<string>::size_type vsize;
			vsize modesize = modeArray.size();
			for(vsize x=0;x<modesize;++x)
			{
				switch(modeArray[x].mode)
				{
				case 'o':
					if (modeArray[x].plus)
						mIrcHandler->onOp(*this,getIrcUser(v.at(0)), v.at(2),
						modeArray[x].arg);
					else
						mIrcHandler->onDeOp(*this,getIrcUser(v.at(0)), v.at(2),
						modeArray[x].arg);
					break;
				case 'v':
					if (modeArray[x].plus)
						mIrcHandler->onVoice(*this,getIrcUser(v.at(0)),v.at(2),
						modeArray[x].arg);
					else
						mIrcHandler->onDeVoice(*this,getIrcUser(v.at(0)),v.at(2),
						modeArray[x].arg);
					break;
				case 'h':
					if (modeArray[x].plus)
						mIrcHandler->onHalfOp(*this,getIrcUser(v.at(0)),v.at(2),
						modeArray[x].arg);
					else
						mIrcHandler->onDeHalfOp(*this,getIrcUser(v.at(0)),v.at(2),
						modeArray[x].arg);
					break;
				case 'b':
					if (modeArray[x].plus)
						mIrcHandler->onBan(*this,getIrcUser(v.at(0)),
						v.at(2),modeArray[x].arg);
					else
						mIrcHandler->onUnBan(*this,getIrcUser(v.at(0)),v.at(2),
						modeArray[x].arg);
					break;
				}
			}
			if (modeArray.size())
				return;

			string args;
			if (isIn(v,4))
				args = token(pMsg," ",4,true);
			mIrcHandler->onMode(*this,getIrcUser(v.at(0)),v.at(2),v.at(3),args);
		}
		else if (scmpi(v.at(1),"NICK") == 0)
		{
			if (!isIn(v,2))
				return;
			mIrcHandler->onNick(*this,getIrcUser(v.at(0)),
				token(token(pMsg," ",2,true),":",0,true));
		}
		else if (scmpi(v.at(1),"QUIT") == 0)
		{
			if (!isIn(v,2))
				return;
			string reason;
			if (isIn(v,2))
				if (v.at(2).size() > 1)
					reason = token(token(pMsg," ",2,true),":",0,true);
			mIrcHandler->onQuit(*this,getIrcUser(v.at(0)),reason);
		}
	}
	catch (const exception &)
	{
		return;
	}
}
