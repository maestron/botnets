#define _WIN32_WINNT	0x0403				// Very important for critical sections.
#define WIN32_LEAN_AND_MEAN					// Good to use.
#ifndef _DEBUG
#pragma optimize("gsy", on)					// Global optimization, Short sequences, Frame pointers.
#pragma comment(linker,"/ALIGN:4096 /IGNORE:4108 /RELEASE")
#endif
#include <windows.h>

char servicename[]		= "dumpreg";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Erase the service
	SC_HANDLE scm;
	SC_HANDLE service;
	scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	service = OpenService(scm, servicename, SERVICE_ALL_ACCESS);
	DeleteService(service);

	return 0;
}