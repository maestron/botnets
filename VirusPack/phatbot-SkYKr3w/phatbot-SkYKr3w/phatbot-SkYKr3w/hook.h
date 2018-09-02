

#ifndef __HOOK_H__
#define __HOOK_H__

#ifdef WIN32

typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation = 0,
    SystemPerformanceInformation = 2,
    SystemTimeOfDayInformation = 3,
    SystemProcessInformation = 5,
    SystemProcessorPerformanceInformation = 8,
    SystemInterruptInformation = 23,
    SystemExceptionInformation = 33,
    SystemRegistryQuotaInformation = 37,
    SystemLookasideInformation = 45
} SYSTEM_INFORMATION_CLASS;

typedef NTSTATUS (*NtQuerySystemInfoFunc)(SYSTEM_INFORMATION_CLASS SystemInformationClass, \
										  void *pSystemInformation, \
										  unsigned long lSystemInformationLength, \
										  unsigned long *lReturnLength);

class CHook : public CThread {
public:
			 CHook();
	virtual	~CHook();
	void	*Run();
	void	 Hook(HANDLE hProcess);
private:
	HMODULE  m_hDLL;
};

#else

// FIXME: Implement for linux
class CHook;

#endif // WIN32

#endif // __HOOK_H__
