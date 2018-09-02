#include "Main.h"
#include "resource.h"
void SetServer(HWND HwND, char * ADMIN, char * ServerVersion, char * User, char * Country, char * ID)
{
	LV_ITEM	item;
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	atoi(ID);
	item.iImage = 0;

	item.iSubItem=0;
	item.pszText=ID;
	item.iItem=ListView_InsertItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);

//	MessageBox(NULL, ID, "ID", MB_OK);

	item.iSubItem=1;
	item.pszText=User;
	ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);
	
	item.iSubItem=2;
	item.pszText=ADMIN;
	ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);
		
	item.iSubItem=3;
	item.pszText=ServerVersion;
	ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);
///////////////////////////////////////////////////////////////
}
void SetLog(char * Action, char * Result, char * Time, char * Client)
{
	LV_ITEM	item;
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;
	item.iImage = 0;
	
	item.iSubItem=0;
	item.pszText=Action;
	item.iItem=ListView_InsertItem(GetDlgItem(FBI,IDC_LOGS),&item);
	
	item.iSubItem=1;
	item.pszText=Result;
	ListView_SetItem(GetDlgItem(FBI,IDC_LOGS),&item);
	
	item.iSubItem=2;
	item.pszText=Client;
	ListView_SetItem(GetDlgItem(FBI,IDC_LOGS),&item);
	
	item.iSubItem=3;
	item.pszText=Time;
	ListView_SetItem(GetDlgItem(FBI,IDC_LOGS),&item);
}
void GetTime()
{
	time_t rawtime;
	struct tm * timeinfo;
	
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	
	Time = asctime (timeinfo);
	
}