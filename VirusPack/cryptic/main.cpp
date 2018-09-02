#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <time.h>
#include <cstdlib>
#include "resource.h"

typedef struct _ICONDIRENTRY {
  BYTE bWidth;
  BYTE bHeight;
  BYTE bColorCount;
  BYTE bReserved;
  WORD wPlanes;
  WORD wBitCount;
  DWORD dwBytesInRes;
  DWORD dwImageOffset;
} ICONDIRENTRY, 
 * LPICONDIRENTRY;

typedef struct _ICONDIR {
  WORD idReserved;
  WORD idType;
  WORD idCount;
  ICONDIRENTRY idEntries[1];
} ICONDIR, 
 * LPICONDIR;

#pragma pack(push)
#pragma pack(2)
typedef struct _GRPICONDIRENTRY {
  BYTE bWidth;
  BYTE bHeight;
  BYTE bColorCount;
  BYTE bReserved;
  WORD wPlanes;
  WORD wBitCount;
  DWORD dwBytesInRes;
  WORD nID;
} GRPICONDIRENTRY, 
 * LPGRPICONDIRENTRY;
#pragma pack(pop)

#pragma pack(push)
#pragma pack(2)
typedef struct _GRPICONDIR {
  WORD idReserved;
  WORD idType;
  WORD idCount;
  GRPICONDIRENTRY idEntries[1];
} GRPICONDIR, 
 * LPGRPICONDIR;
#pragma pack(pop)

PIMAGE_DOS_HEADER pidh;
PIMAGE_NT_HEADERS pinh;
PIMAGE_SECTION_HEADER pish;

HINSTANCE hInst;
HICON hIcon;

DWORD dwFileSize;
LPBYTE lpFileBuffer;

CHAR szEFileName[MAX_PATH];
CHAR szIFileName[MAX_PATH];

BOOL LoadPE(LPSTR szFileName)
{
	HANDLE hFile = CreateFile(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	dwFileSize = GetFileSize(hFile, NULL);
	if(dwFileSize == INVALID_FILE_SIZE)
	{
		return FALSE;
	}
	lpFileBuffer = (LPBYTE)realloc(lpFileBuffer, dwFileSize);
	if(lpFileBuffer == NULL)
	{
		return FALSE;
	}
	DWORD dwBytesRead;
	ReadFile(hFile, lpFileBuffer, dwFileSize, &dwBytesRead, NULL);
	CloseHandle(hFile);
	pidh = (PIMAGE_DOS_HEADER)&lpFileBuffer[0];
	if(pidh->e_magic != IMAGE_DOS_SIGNATURE)
	{
		free(lpFileBuffer);
		return FALSE;
	}
	pinh = (PIMAGE_NT_HEADERS)&lpFileBuffer[pidh->e_lfanew];
	if(pinh->Signature != IMAGE_NT_SIGNATURE)
	{
		free(lpFileBuffer);
		return FALSE;
	}
	return TRUE;
}

BOOL AddIcon(LPSTR szIFileName, LPSTR szEFileName)
{
	HANDLE hFile = CreateFile(szIFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	LPICONDIR lpid;
	lpid = (LPICONDIR)malloc(sizeof(ICONDIR));
	if(lpid == NULL)
	{
		return FALSE;
	}
	DWORD dwBytesRead;
	ReadFile(hFile, &lpid->idReserved, sizeof(WORD), &dwBytesRead, NULL);
	ReadFile(hFile, &lpid->idType, sizeof(WORD), &dwBytesRead, NULL);
	ReadFile(hFile, &lpid->idCount, sizeof(WORD), &dwBytesRead, NULL);
	lpid = (LPICONDIR)realloc(lpid, (sizeof(WORD) * 3) + (sizeof(ICONDIRENTRY) * lpid->idCount));
	if(lpid == NULL)
	{
		return FALSE;
	}
	ReadFile(hFile, &lpid->idEntries[0], sizeof(ICONDIRENTRY) * lpid->idCount, &dwBytesRead, NULL);
	LPGRPICONDIR lpgid;
	lpgid = (LPGRPICONDIR)malloc(sizeof(GRPICONDIR));
	if(lpgid == NULL)
	{
		return FALSE;
	}
	lpgid->idReserved = lpid->idReserved;
	lpgid->idType = lpid->idType;
	lpgid->idCount = lpid->idCount;
	lpgid = (LPGRPICONDIR)realloc(lpgid, (sizeof(WORD) * 3) + (sizeof(GRPICONDIRENTRY) * lpgid->idCount));
	if(lpgid == NULL)
	{
		return FALSE;
	}
	for(int i = 0; i < lpgid->idCount; i++)
	{
		lpgid->idEntries[i].bWidth = lpid->idEntries[i].bWidth;
		lpgid->idEntries[i].bHeight = lpid->idEntries[i].bHeight;
		lpgid->idEntries[i].bColorCount = lpid->idEntries[i].bColorCount;
		lpgid->idEntries[i].bReserved = lpid->idEntries[i].bReserved;
		lpgid->idEntries[i].wPlanes = lpid->idEntries[i].wPlanes;
		lpgid->idEntries[i].wBitCount = lpid->idEntries[i].wBitCount;
		lpgid->idEntries[i].dwBytesInRes = lpid->idEntries[i].dwBytesInRes;
		lpgid->idEntries[i].nID = i + 1;
	}
	HANDLE hUpdate;
	hUpdate = BeginUpdateResource(szEFileName, TRUE);
	if(hUpdate == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	for(i = 0; i < lpid->idCount; i++)
	{
		LPBYTE lpBuffer = (LPBYTE)malloc(lpid->idEntries[i].dwBytesInRes);
		if(lpBuffer == NULL)
		{
			CloseHandle(hFile);
			return FALSE;
		}
		SetFilePointer(hFile, lpid->idEntries[i].dwImageOffset, NULL, FILE_BEGIN);
		ReadFile(hFile, lpBuffer, lpid->idEntries[i].dwBytesInRes, &dwBytesRead, NULL);
		if(UpdateResource(hUpdate, RT_ICON, MAKEINTRESOURCE(lpgid->idEntries[i].nID), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), &lpBuffer[0], lpid->idEntries[i].dwBytesInRes) == FALSE)
		{
			CloseHandle(hFile);
			free(lpBuffer);
			return FALSE;
		}
		free(lpBuffer);
	}
	CloseHandle(hFile);
	if(UpdateResource(hUpdate, RT_GROUP_ICON, MAKEINTRESOURCE(1), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), &lpgid[0], (sizeof(WORD) * 3) + (sizeof(GRPICONDIRENTRY) * lpgid->idCount)) == FALSE)
	{
		return FALSE;
	}
	if(EndUpdateResource(hUpdate, FALSE) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

LPBYTE RC4(LPBYTE lpBuf, LPBYTE lpKey, DWORD dwBufLen, DWORD dwKeyLen)
{
	int a, b = 0, s[256];
	BYTE swap;
	DWORD dwCount;
	for(a = 0; a < 256; a++)
	{
		s[a] = a;
	}
	for(a = 0; a < 256; a++)
	{
		b = (b + s[a] + lpKey[a % dwKeyLen]) % 256;
		swap = s[a];
		s[a] = s[b];
		s[b] = swap;
	}
	for(dwCount = 0; dwCount < dwBufLen; dwCount++)
	{
		a = (a + 1) % 256;
		b = (b + s[a]) % 256;
		swap = s[a];
		s[a] = s[b];
		s[b] = swap;
		lpBuf[dwCount] ^= s[(s[a] + s[b]) % 256];
	}
	return lpBuf;
}

VOID EnableControls(HWND hWnd, BOOL bEnable)
{
	EnableWindow(GetDlgItem(hWnd, IDC_FILE), bEnable);
	EnableWindow(GetDlgItem(hWnd, IDC_BROWSE), bEnable);
	EnableWindow(GetDlgItem(hWnd, IDC_BACKUP), bEnable);
	EnableWindow(GetDlgItem(hWnd, IDC_ADDICON), bEnable);
	EnableWindow(GetDlgItem(hWnd, IDC_ICONIMG), bEnable);
	EnableWindow(GetDlgItem(hWnd, IDC_BUILD), bEnable);
	EnableWindow(GetDlgItem(hWnd, IDC_ABOUT), bEnable);
	EnableWindow(GetDlgItem(hWnd, IDC_EXIT), bEnable);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	OPENFILENAME ofn;
	POINT pt;
	RECT rect;
	switch(uMsg){
	case WM_INITDIALOG:
		InitCommonControls();
		hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_MAIN));
		SendMessage(hDlg, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hIcon);
		CheckDlgButton(hDlg, IDC_BACKUP, BST_CHECKED);
		SendMessage(GetDlgItem(hDlg, IDC_FILE), EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
		hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_EXE));
		SendMessage(GetDlgItem(hDlg, IDC_ICONIMG), STM_SETICON, (WPARAM)hIcon, (LPARAM)0);
		EnableWindow(GetDlgItem(hDlg, IDC_BUILD), FALSE);
		SetWindowPos(hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	case WM_PAINT:
		SendMessage(GetDlgItem(hDlg, IDC_ICONIMG), STM_SETICON, (WPARAM)hIcon, (LPARAM)0);
		break;
	case WM_DROPFILES:
		HDROP hDrop;
		hDrop = HDROP(wParam);
		DragQueryFile(hDrop, 0, szEFileName, sizeof(szEFileName));
		DragFinish(hDrop);
		if(LoadPE(szEFileName) == FALSE)
		{
			MessageBox(hDlg, "Could not load file!", "Cryptic", MB_ICONERROR);
			return TRUE;
		}
		SetDlgItemText(hDlg, IDC_FILE, szEFileName);
		EnableWindow(GetDlgItem(hDlg, IDC_BUILD), TRUE);
		break;
	case WM_MOUSEMOVE:
		GetCursorPos(&pt);
		GetWindowRect(GetDlgItem(hDlg, IDC_ICONIMG), &rect);
		if(PtInRect(&rect, pt))
		{
			SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(32649)));
		}
		else
		{
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		break;
	case WM_LBUTTONDOWN:
		GetCursorPos(&pt);
		GetWindowRect(GetDlgItem(hDlg, IDC_ICONIMG), &rect);
		if(PtInRect(&rect, pt))
		{
			SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(32649)));
			memset(&ofn, 0, sizeof(ofn));
			szIFileName[0] = '\0';
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFilter = "Icon Files (*.ico)\0*.ico\0\0";
			ofn.lpstrFile = szIFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_PATHMUSTEXIST;
			if(GetOpenFileName(&ofn))
			{
				hIcon = ExtractIcon(hInst, szIFileName, 0);
				SendMessage(GetDlgItem(hDlg, IDC_ICONIMG), STM_SETICON, (WPARAM)hIcon, (LPARAM)0);
			}
		}
		break;
	case WM_RBUTTONDOWN:
		GetCursorPos(&pt);
		GetWindowRect(GetDlgItem(hDlg, IDC_ICONIMG), &rect);
		if(PtInRect(&rect, pt))
		{
			SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(32649)));
		}
		break;
	case WM_COMMAND:
		switch LOWORD(wParam){
		case IDC_BROWSE:
			memset(&ofn, 0, sizeof(ofn));
			szEFileName[0] = '\0';
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFilter = "Executable Files (*.exe)\0*.exe\0\0";
			ofn.lpstrFile = szEFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_PATHMUSTEXIST;
			if(GetOpenFileName(&ofn))
			{
				if(LoadPE(szEFileName) == FALSE)
				{
					MessageBox(hDlg, "Could not load file!", "Cryptic", MB_ICONERROR);
					return TRUE;
				}
				SetDlgItemText(hDlg, IDC_FILE, szEFileName);
				EnableWindow(GetDlgItem(hDlg, IDC_BUILD), TRUE);
			}
			break;
		case IDC_BUILD:
			EnableControls(hDlg, FALSE);
			HRSRC hRsrc;
			hRsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_STUB), "STUB");
			if(hRsrc == NULL)
			{
				MessageBox(hDlg, "Could not find resource!", "Cryptic", MB_ICONERROR);
				EnableControls(hDlg, TRUE);
				return TRUE;
			}
			DWORD dwRsrcSize;
			dwRsrcSize = SizeofResource(NULL, hRsrc);
			HGLOBAL hGlob;
			hGlob = LoadResource(NULL, hRsrc);
			if(hGlob == NULL)
			{
				MessageBox(hDlg, "Could not load resource!", "Cryptic", MB_ICONERROR);
				EnableControls(hDlg, TRUE);
				return TRUE;
			}
			LPBYTE lpBuffer;
			lpBuffer = (LPBYTE)LockResource(hGlob);
			if(lpBuffer == NULL)
			{
				MessageBox(hDlg, "Could not lock resource!", "Cryptic", MB_ICONERROR);
				EnableControls(hDlg, TRUE);
				return TRUE;
			}
			GetDlgItemText(hDlg, IDC_FILE, szEFileName, MAX_PATH);
			if(IsDlgButtonChecked(hDlg, IDC_BACKUP) == BST_CHECKED)
			{
				CHAR szBFileName[MAX_PATH];
				GetDlgItemText(hDlg, IDC_FILE, szBFileName, MAX_PATH);
				strcat(szBFileName, ".bak");
				if(CopyFile(szEFileName, szBFileName, FALSE) == 0)
				{
					free(lpBuffer);
					MessageBox(hDlg, "Could not copy file!", "Cryptic", MB_ICONERROR);
					EnableControls(hDlg, TRUE);
					return TRUE;
				}
			}
			BYTE lpKey[14];
			srand(time(NULL));
			int i;
			for(i = 0; i < 15; i++)
			{
				lpKey[i] = BYTE(rand() % 255 + 1);
			}
			HANDLE hFile;
			hFile = CreateFile(szEFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
			if(hFile == INVALID_HANDLE_VALUE)
			{
				free(lpBuffer);
				MessageBox(hDlg, "Could not create file!", "Cryptic", MB_ICONERROR);
				EnableControls(hDlg, TRUE);
				return TRUE;
			}
			DWORD dwBytesWritten;
			if(WriteFile(hFile, lpBuffer, dwRsrcSize, &dwBytesWritten, NULL) == 0)
			{
				CloseHandle(hFile);
				free(lpBuffer);
				MessageBox(hDlg, "Could not write to file!", "Cryptic", MB_ICONERROR);
				EnableControls(hDlg, TRUE);
				return TRUE;
			}
			CloseHandle(hFile);
			free(lpBuffer);
			if(IsDlgButtonChecked(hDlg, IDC_ADDICON) == BST_CHECKED)
			{
				if(AddIcon(szIFileName, szEFileName) == FALSE)
				{
					MessageBox(hDlg, "Could add icon!", "Cryptic", MB_ICONERROR);
					EnableControls(hDlg, TRUE);
					return TRUE;
				}
			}
			HANDLE hUpdate;
			hUpdate = BeginUpdateResource(szEFileName, FALSE);
			if(hUpdate == NULL)
			{
				MessageBox(hDlg, "Could add resource!", "Cryptic", MB_ICONERROR);
				EnableControls(hDlg, TRUE);
				return TRUE;
			}
			if(UpdateResource(hUpdate, RT_RCDATA, MAKEINTRESOURCE(150), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), RC4(lpFileBuffer, lpKey, dwFileSize, 15), dwFileSize) == FALSE)
			{
				MessageBox(hDlg, "Could add resource!", "Cryptic", MB_ICONERROR);
				EnableControls(hDlg, TRUE);
				return TRUE;
			}
			if(UpdateResource(hUpdate, RT_RCDATA, MAKEINTRESOURCE(151), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), &lpKey[0], 15) == FALSE)
			{
				MessageBox(hDlg, "Could add resource!", "Cryptic", MB_ICONERROR);
				EnableControls(hDlg, TRUE);
				return TRUE;
			}
			if(EndUpdateResource(hUpdate, FALSE) == FALSE)
			{
				MessageBox(hDlg, "Could add resource!", "Cryptic", MB_ICONERROR);
				EnableControls(hDlg, TRUE);
				return TRUE;
			}
			RC4(lpFileBuffer, lpKey, dwFileSize, 15);
			pish = (PIMAGE_SECTION_HEADER)&lpFileBuffer[pidh->e_lfanew + sizeof(IMAGE_NT_HEADERS) + sizeof(IMAGE_SECTION_HEADER) * (pinh->FileHeader.NumberOfSections - 1)];
			if(dwFileSize > (pish->PointerToRawData + pish->SizeOfRawData))
			{
				MessageBox(hDlg, "EOF data found!", "Cryptic", MB_OK);
				hFile = CreateFile(szEFileName, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
				if(hFile == INVALID_HANDLE_VALUE)
				{
					MessageBox(hDlg, "Could not open file!", "Cryptic", MB_ICONERROR);
					EnableControls(hDlg, TRUE);
					return TRUE;
				}
				SetFilePointer(hFile, 0, NULL, FILE_END);
				if(WriteFile(hFile, &lpFileBuffer[pish->PointerToRawData + pish->SizeOfRawData + 1], dwFileSize - (pish->PointerToRawData + pish->SizeOfRawData), &dwBytesWritten, NULL) == 0)
				{
					CloseHandle(hFile);
					MessageBox(hDlg, "Could not write to file!", "Cryptic", MB_ICONERROR);
					EnableControls(hDlg, TRUE);
					return TRUE;
				}
				CloseHandle(hFile);
			}
			MessageBox(hDlg, "File successfully crypted!", "Cryptic", MB_ICONINFORMATION);
			EnableControls(hDlg, TRUE);
			break;
		case IDC_ABOUT:
			MessageBox(hDlg, "Cryptic v3.0\nCoded by Tughack", "About", MB_ICONINFORMATION);
			break;
		case IDC_EXIT:
			EndDialog(hDlg, 0);
			break;
		}
	}
	return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "m_Cryptic");
	if(hMutex == NULL)
	{
		hMutex = CreateMutex(NULL, FALSE, "m_Cryptic");
	}
	else
	{
		return 0;
	}
	hInst = hInstance;
	DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN), NULL, (DLGPROC)DlgProc);
	return 0;
}