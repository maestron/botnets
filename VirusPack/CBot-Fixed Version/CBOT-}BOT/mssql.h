#ifndef __MSSQL_H__
#define __MSSQL_H__
/*#include <mysql.h>

  struct SqlConnectInfo_s 
  {
  unsigned short	usRemotePort;			// Port we infect the target on
  DWORD			dwRemoteIp;				// Target IP in network format
  DWORD			dwExploitId;			// Pointer to the exploit id
  MYSQL			*hMYSQL;				// Pointer to sql handle
  };
*/
void MSSQL(ExploitInfo_s* pExploitInfo);
void MSSQLResolution(ExploitInfo_s* pExploitInfo);
void MSSQLUDP(ExploitInfo_s* pExploitInfo);
void MSSQLWeakPassword(ExploitInfo_s* pExploitInfo);
//void MySQLPass(ExploitInfo_s* pExploitInfo);
//void InitialiseMySQL();

#endif // __MSSQL_H__
