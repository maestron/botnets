#include <winsock2.h>
#include <windows.h>
#pragma comment( lib, "ws2_32.lib" )
#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include "../userauth.h"
using namespace std;

/************************************************************************************/
/* STEAMBOT 1.0 source by s0beit - greetz											*/
/* myg0t.com																		*/
/* bottalk.us																		*/
/* milw0rm.com																		*/
/* irc.lcirc.net #myg0t, #bottalk, #milw0rm											*/
/* irc.fuckurinter.net #FYINet to support me for no real reason :p					*/
/************************************************************************************/
/* cIRC class, based off of pBot source for PHP and my own workings					*/
/* also FroZenFruiT from someplace, i don't remember lol							*/
/************************************************************************************/

class cIRC;

//--------------------------------------------------------------------------------

struct irc_data_s
{
	bool		connected;
	char		server[256];
	int			port;
	char		user[256];
	char		nick[256];
	char		pass[256];
	char		modes[256];
	char		recievedata[1024];
	SOCKET		socket;
	cUserAuth*	userAuth;

	irc_data_s()
	{
		connected	= false;
		port		= 6667;
		memset( server, 0, 256 );
		memset( user, 0, 256 );
		memset( nick, 0, 256 );
		memset( pass, 0, 256 );
		memset( modes, 0, 256 );
		memset( recievedata, 0, 1024 );
		socket		= -1;
		userAuth = new cUserAuth;
	}
};

struct channel_info_s
{
	string channel;
	string key;
};

struct privmsg_info_s
{
	string name;
	string vhost;
	string location;	//channel/user
	string alldata;		//raw data
	string postcommand;	//all data after ([prefix][command string] (e.x. !help))
};

typedef void (*IRCCommand)(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd);

struct irc_command_s
{
	string	commandString;
	FARPROC	fpCallbackProc;
};
//--------------------------------------------------------------------------------

class cIRC
{
public:

	cIRC();
	~cIRC();

	//--------------------------------------------------------------------------------
	bool	CONNECT( char* server, int port );
	void	Init( char *server, int port, char *user, char *nickname, char *pass );
	void	JoinChannel( char *channel, char *key = "" );
	void	PrivMsg( char *to, char *msg );
	void	PrivMsg_s( char *to, char *msg, ... );
	void	Notice( char *to, char *msg );
	void	PartChannel( char *channel );
	void	SetNick( char *name );
	void	PacketLoop( void );
	void	SetUserModes( char *modes );

	//--------------------------------------------------------------------------------
	vector<string> explode( const string &inString, const string &separator )
	{
		vector<string> returnVector;
		string::size_type start = 0;
		string::size_type end = 0;

		while ((end = inString.find (separator, start)) != string::npos)
		{
			returnVector.push_back (inString.substr (start, end-start));
			start = end + separator.size();
		}

		returnVector.push_back (inString.substr (start));

		return returnVector;
	}

	string	chomp( string chompstr )
	{
		//remove the \n, \r, etc from the end
		//perl style, but not really
		const char* p = &chompstr[0];
		const char* p2 = &chompstr[0] + chompstr.size();

		while ( p2 > p && strchr("\r\n", p2[-1]) )
			p2--;

		return string ( p, p2-p );
	}

	int	send_local( const char *szFormat, ... )
	{
		va_list va_alist;
		char logbuf[ 1024 ] = { 0 };
		va_start( va_alist, szFormat);
		_vsnprintf( logbuf + strlen( logbuf ), sizeof( logbuf ) - strlen( logbuf ), szFormat, va_alist);
		va_end( va_alist );

		//for IRC
		strcat( logbuf, "\r\n" );
		return send( this->ircdata.socket, logbuf, (int)strlen( logbuf ), 0 );
	}

	irc_data_s *GetIRCData()
	{
		return &this->ircdata;
	}

	void AddJoinChannel( char *newChannel, char *newKey = "" )
	{
		channel_info_s ci;
		ci.channel = newChannel;
		ci.key = newKey;

		inChannels.push_back( ci );
	}

	void AddIRCCommand( const char *commandName, FARPROC fpCallback )
	{
		irc_command_s cmd;
		cmd.commandString	= commandName;
		cmd.fpCallbackProc	= fpCallback;
		this->irccommands.push_back(cmd);
	}

	vector<channel_info_s> GetChannelList()
	{
		return inChannels;
	}

	//--------------------------------------------------------------------------------

private:

	irc_data_s				ircdata;
	vector<channel_info_s>	inChannels;
	vector<irc_command_s>	irccommands;
	
};

//----------------------------------------------------------