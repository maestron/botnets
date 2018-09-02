#include "stdafx.h"
#include "IRC.h"
#include "AppTools.h"

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

cIRC::cIRC()
{
	this->inChannels.clear();
	this->irccommands.clear();
}

bool cIRC::CONNECT( char* server, int port )
{
	SOCKADDR_IN serverInfo;
	SOCKET sck; 
	WSADATA wsaData; 
	LPHOSTENT hostEntry; 
	WSAStartup(MAKEWORD(2,2),&wsaData);
	hostEntry = gethostbyname(server);
	if(!hostEntry)
	{  
		WSACleanup();  
		return false;
	} 
	sck = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sck==INVALID_SOCKET)
	{
		WSACleanup(); 
		return false; 
	} 
	serverInfo.sin_family = AF_INET;
 	serverInfo.sin_addr   = *((LPIN_ADDR)*hostEntry->h_addr_list); 
	serverInfo.sin_port   = htons(port); 
	int i = connect(sck,(LPSOCKADDR)&serverInfo,sizeof(struct sockaddr));
     
	if( sck == SOCKET_ERROR)
		return false;

	if(i!=0) 
		return false;

	this->ircdata.socket = sck;
	return true;
}

cIRC::~cIRC()
{
	this->inChannels.clear();
}

//---------------------------------------------

void cIRC::Init( char *server, int port, char *user, char *nickname, char *pass )
{
	if( CONNECT( server, port ) )
	{
		//we have connected to the server via socket
		SOCKET s = this->ircdata.socket;

		send_local( "USER %s 127.0.0.1 localhost :%s", user, user );
		send_local( "NICK %s", nickname );

		//join channels here
		for( int i = 0; i < (int)inChannels.size(); i++ )
		{
			send_local( "JOIN %s %s", 
				inChannels[i].channel.c_str(), inChannels[i].key.c_str() );
		}

		PacketLoop();

		this->ircdata.connected = true;
	}
	this->ircdata.connected = false;
}

void cIRC::JoinChannel( char *channel, char *key )
{
	send_local( "JOIN %s %s", channel, key );

	channel_info_s ci;
	ci.channel = channel;
	ci.key = key;

	inChannels.push_back( ci );
}

void cIRC::PrivMsg( char *to, char *msg )
{
	send_local( "PRIVMSG %s :%s", to, msg );
}

void cIRC::PrivMsg_s( char *to, char *msg, ... )
{
	va_list va_alist;
	char logbuf[ 1024 ] = { 0 };
	va_start( va_alist, msg);
	_vsnprintf( logbuf + strlen( logbuf ), sizeof( logbuf ) - strlen( logbuf ), msg, va_alist);
	va_end( va_alist );

	this->PrivMsg( to, logbuf );
}

void cIRC::Notice( char *to, char *msg )
{
	send_local( "NOTICE %s :%s", to, msg );
}

void cIRC::PartChannel( char *channel )
{
	send_local( "PART %s", channel );
}

void cIRC::SetNick( char *name )
{
	send_local( "NICK %s", name );
}

void cIRC::PacketLoop( void )
{
	while( recv( this->ircdata.socket, this->ircdata.recievedata, 1024, 0 ) > 0 )
	{
		if( strlen( this->ircdata.recievedata ) > 0 )
		{
			//packet loop
			privmsg_info_s pmi;

			pmi.alldata = this->ircdata.recievedata;
			vector<string> cmd = this->explode( this->ircdata.recievedata, " " );

			if( strncmp( this->ircdata.recievedata, "PING", 4 ) == 0 )
			{
				char pongReply[ 1024 ];
				memcpy( &pongReply, &this->ircdata.recievedata, 1024 );
				pongReply[1] = 'O';
				send_local( pongReply );
				memset( &pongReply, 0, 1024 );
				goto clear_data_redo;
			}

			if( cmd[1].size() > 0 )
			{
				if( !strcmp( cmd[1].c_str(), "001" ) )
				{
					send_local( "MODE %s %s", this->ircdata.nick, this->ircdata.modes );
					
					for( int i = 0; i < (int)this->inChannels.size(); i++ )
					{
						channel_info_s joinChan = inChannels[i];

						send_local( "JOIN %s %s", 
							joinChan.channel.c_str(), 
							joinChan.key.c_str() );
					}

					goto clear_data_redo;
				}
				if( !strcmp( cmd[1].c_str(), "433" ) )
				{
					//Nickname already exists in the server
					//duplicate process? or, i dunno
					ExitProcess( 0 );
				}
				if( !strcmp( cmd[1].c_str(), "421" ) )
				{
					//unknown command
					goto clear_data_redo;
				}
			}

			if( cmd.size() > 1 )
			{
				for( int c = 0; c < (int)inChannels.size(); c++ )
				{
					//commandable channels
					if( !strcmp( cmd[2].c_str(), inChannels[c].channel.c_str() ) )
					{
						string commandString = cmd[1];

						if( 
							!strcmp( cmd[1].c_str(), "QUIT" )
							|| !strcmp( cmd[1].c_str(), "PART" ) )
						{
							vector<string>	userInfo = explode( cmd[0], "!" );
							vector<string>	hostInfo = explode( userInfo[1], "@" );
							string name = userInfo[0].substr(1);
							string host = hostInfo[1];
							ircdata.userAuth->LogoutUser( host );
							
							//if the user leaves or parts we remove their auth
							//don't need people stealing, do we?

							goto clear_data_redo;
						}

						if( !strcmp( cmd[1].c_str(), "PRIVMSG" ) )
						{
							//get past ":"
							string firstText = cmd[3].substr(1);

							//command prefix
							if( firstText.c_str()[0] == '!' )
							{
								if( this->GetIRCData()->userAuth->GetUsersInfo().size() == 0 )
									goto clear_data_redo;

								int iCmd_Size = (int)cmd.size();

								//we don't need the \r\n if we are recieving a command
								cmd[ iCmd_Size - 1 ] = chomp( cmd[ iCmd_Size - 1 ] );

								//string fix
								string commandCode = firstText.substr(1);

								pmi.location	= cmd[2].c_str();

								vector<string>	userInfo = explode( cmd[0], "!" );
								vector<string>	hostInfo = explode( userInfo[1], "@" );

								pmi.name		= userInfo[0].substr(1);
								pmi.vhost		= hostInfo[1];

								//just remove this chunk to make it work for anyone
								if( !ircdata.userAuth->AuthCheckLoop( pmi.vhost ) )
								{
									//not auth'ed, however we can also add
									char *sauth		= strstr( (char*)pmi.alldata.c_str(), "!auth " );

									if( !sauth )
										goto clear_data_redo;

									char *str_auth = sauth + 6;

									if( str_auth == NULL )
										goto clear_data_redo;

									string str_pass = str_auth;

									if( str_pass.empty() )
										goto clear_data_redo;

									pmi.postcommand = chomp( str_pass );

									if( ircdata.userAuth->AuthHost( pmi.name, pmi.postcommand, pmi.vhost ) )
									{
										this->PrivMsg_s( (char*)pmi.location.c_str(), 
											"[auth] User [%s] auth success!", 
											pmi.name.c_str() );
									}
									else
									{
										this->PrivMsg_s( (char*)pmi.location.c_str(), 
											"[auth] User [%s] FAILED LOGIN [%s]",
											pmi.name.c_str(), pmi.postcommand.c_str() );
									}

									goto clear_data_redo;
								}
								//just remove this chunk to make it work for anyone

								if( irccommands.size() > 0 )
								{
									for( int n = 0; n < (int)irccommands.size(); n++ )
									{
										string currentCommand	= irccommands[n].commandString;
										IRCCommand iCmd			= (IRCCommand)irccommands[n].fpCallbackProc;

										if( !strncmp( commandCode.c_str(), currentCommand.c_str(), strlen( currentCommand.c_str() ) ) )
										{
											if(iCmd)
											{
												//check this

												//postcommand
												string findThis = "!";
												findThis.append( currentCommand );

												string pcmd = pmi.alldata;

												//+1 is to trim the unused " " (0x20)
												pcmd = pcmd.substr( pcmd.find( findThis ) + findThis.size() + 1,
													pcmd.size() );

												pmi.postcommand = chomp( pcmd );

												iCmd( this, this->ircdata, pmi, cmd );
											}
										}
									}
								}
							}
						}
					}
				}
			}

clear_data_redo:

			//clear the data for reuse later
			memset( this->ircdata.recievedata, 0, 1024 );
			memset( &pmi, 0, sizeof( privmsg_info_s ) );
		}
	}
}

void cIRC::SetUserModes( char *modes )
{
	strcpy( this->ircdata.modes, modes );
}