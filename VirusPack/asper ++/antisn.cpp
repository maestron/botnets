#include "includes.h"
#include "externs.h"
                  
char* sUsers[] = { "UserName", //threat expert
                  "user", //sandbox
				  "sandbox", "honey", "vmware", "currentuser", "nepenthes", "andy", //vmware
                  "CurrentUser" };  //norman
                  
char* sModules[] = { "SbieDll.dll",  //sandboxie 
					 "api_log.dll", //sunbelt
					 "dir_watch.dll", //sunbelt sanbox
					 "dbghelp.dll"}; //vmware
					 

BOOL ModuleCheck()
{
    for( int i = 0; i < ( sizeof( sModules ) / sizeof( char* ) ); i++ )
    {
        if( GetModuleHandle( sModules[ i ] ) ) 
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL UserCheck()
{
    char szBuffer[30];
    unsigned long lSize = sizeof( szBuffer );
    
    if( GetUserName( szBuffer, &lSize ) == 0 )
        return( 1 );
        
    for( int i = 0; i < ( sizeof( sUsers ) / sizeof( char* ) ); i++ )
    {
         if( strstr( szBuffer, sUsers[ i ] ) )
         {
             return TRUE;
         }
    }
    return FALSE;
}




  

