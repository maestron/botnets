
#ifndef NO_WFP

BOOL disable_wfp(VOID);
void patch_system(BOOL unpatch=FALSE);
void check_debug();
BOOL patch_ftps(BOOL unpatch=FALSE);
BOOL patch_tcpip(char *path, BOOL unpatch=FALSE);

#ifndef NTSTATUS
	typedef LONG NTSTATUS;
	#define NT_SUCCESS(Status)	((NTSTATUS)(Status) >= 0)
	#define STATUS_SUCCESS		((NTSTATUS)0x00000000L)
#endif

#ifndef SYSTEM_INFORMATION_CLASS
	typedef enum _SYSTEM_INFORMATION_CLASS {
		SystemBasicInformation,					// 0
		SystemProcessorInformation,				// 1
		SystemPerformanceInformation,			// 2
		SystemTimeOfDayInformation,				// 3
		SystemNotImplemented1,					// 4
		SystemProcessesAndThreadsInformation,	// 5
		SystemCallCounts,						// 6
		SystemConfigurationInformation,			// 7
		SystemProcessorTimes,					// 8
		SystemGlobalFlag,						// 9
		SystemNotImplemented2,					// 10
		SystemModuleInformation,				// 11
		SystemLockInformation,					// 12
		SystemNotImplemented3,					// 13
		SystemNotImplemented4,					// 14
		SystemNotImplemented5,					// 15
		SystemHandleInformation,				// 16
		SystemObjectInformation,				// 17
		SystemPagefileInformation,				// 18
		SystemInstructionEmulationCounts,		// 19
		SystemInvalidInfoClass1,				// 20
		SystemCacheInformation,					// 21
		SystemPoolTagInformation,				// 22
		SystemProcessorStatistics,				// 23
		SystemDpcInformation,					// 24
		SystemNotImplemented6,					// 25
		SystemLoadImage,						// 26
		SystemUnloadImage,						// 27
		SystemTimeAdjustment,					// 28
		SystemNotImplemented7,					// 29
		SystemNotImplemented8,					// 30
		SystemNotImplemented9,					// 31
		SystemCrashDumpInformation,				// 32
		SystemExceptionInformation,				// 33
		SystemCrashDumpStateInformation,		// 34
		SystemKernelDebuggerInformation,		// 35
		SystemContextSwitchInformation,			// 36
		SystemRegistryQuotaInformation,			// 37
		SystemLoadAndCallImage,					// 38
		SystemPrioritySeparation,				// 39
		SystemNotImplemented10,					// 40
		SystemNotImplemented11,					// 41
		SystemInvalidInfoClass2,				// 42
		SystemInvalidInfoClass3,				// 43
		SystemTimeZoneInformation,				// 44
		SystemLookasideInformation,				// 45
		SystemSetTimeSlipEvent,					// 46
		SystemCreateSession,					// 47
		SystemDeleteSession,					// 48
		SystemInvalidInfoClass4,				// 49
		SystemRangeStartInformation,			// 50
		SystemVerifierInformation,				// 51
		SystemAddVerifier,						// 52
		SystemSessionProcessesInformation		// 53
	} SYSTEM_INFORMATION_CLASS;
#endif

#ifndef HANDLEINFO
	typedef struct HandleInfo{
		ULONG Pid;
		USHORT  ObjectType;
		USHORT  HandleValue;
		PVOID ObjectPointer;
		ULONG AccessMask;
	} HANDLEINFO, *PHANDLEINFO;
#endif

#ifndef SYSTEMHANDLEINFO
	typedef struct SystemHandleInfo {
		ULONG nHandleEntries;
		HANDLEINFO HandleInfo[1];
	} SYSTEMHANDLEINFO, *PSYSTEMHANDLEINFO;
#endif

#ifndef STATUS_INFO_LENGTH_MISMATCH
	#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)
#endif

#ifndef OBJECT_INFORMATION_CLASS
	typedef enum _OBJECT_INFORMATION_CLASS {
		ObjectBasicInformation,
		ObjectNameInformation,
		ObjectTypeInformation,
		ObjectAllTypesInformation,
		ObjectHandleInformation
	} OBJECT_INFORMATION_CLASS;
#endif

#ifndef OBJECT_NAME_INFORMATION
	typedef struct _OBJECT_NAME_INFORMATION
	{
		UNICODE_STRING ObjectName;
	} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;
#endif

#ifndef OBJECT_BASIC_INFORMATION
	typedef struct _OBJECT_BASIC_INFORMATION
	{
		ULONG                   Unknown1;
		ACCESS_MASK             DesiredAccess;
		ULONG                   HandleCount;
		ULONG                   ReferenceCount;
		ULONG                   PagedPoolQuota;
		ULONG                   NonPagedPoolQuota;
		BYTE                    Unknown2[32];
	} OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;
#endif

#define Z_NULL		0
#define POLYNOMIAL	(unsigned long)0xedb88320
int crc32N(const void * buf, int len);

#endif