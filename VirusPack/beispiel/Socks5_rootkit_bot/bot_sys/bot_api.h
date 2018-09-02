/*typedef ULONG_PTR PKPROCESS;
typedef ULONG_PTR PRKAPC_STATE;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef PVOID	(*ExAllocatePoolWithTagPtr)(IN POOL_TYPE  PoolType,IN SIZE_T  NumberOfBytes,IN ULONG  Tag);
typedef VOID	(*ExFreePoolWithTagPtr)(IN PVOID  P,IN ULONG  Tag ); 
typedef PMDL	(*IoAllocateMdlPtr)(IN PVOID  VirtualAddress,IN ULONG  Length,IN BOOLEAN  SecondaryBuffer,IN BOOLEAN  ChargeQuota,IN OUT PIRP  Irp  OPTIONAL);
typedef VOID	(*IoFreeMdlPtr)(IN PMDL  Mdl);
typedef VOID	(*KeStackAttachProcessPtr)(PKPROCESS Process,PRKAPC_STATE  ApcState);
typedef VOID	(*KeUnstackDetachProcessPtr)(IN PRKAPC_STATE  ApcState);
typedef PVOID	(*KeServiceDescriptorTablePtr)();
typedef VOID	(*MmBuildMdlForNonPagedPoolPtr)(IN OUT PMDL  MemoryDescriptorList);
typedef PVOID	(*MmMapLockedPagesSpecifyCachePtr)(IN PMDL  MemoryDescriptorList,IN KPROCESSOR_MODE  AccessMode,IN MEMORY_CACHING_TYPE  CacheType,IN PVOID  BaseAddress,IN ULONG  BugCheckOnFailure,IN MM_PAGE_PRIORITY  Priority);
typedef VOID	(*MmUnmapLockedPagesPtr)(IN PVOID  BaseAddress,IN PMDL  MemoryDescriptorList);
typedef PUSHORT (*NtBuildNumberPtr)();
typedef VOID	(*ObDereferenceObjectPtr)(IN PVOID  Object);
typedef NTSTATUS(*PsCreateSystemThreadPtr)(OUT PHANDLE  ThreadHandle,IN ULONG  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes  OPTIONAL,IN HANDLE  ProcessHandle  OPTIONAL,OUT PCLIENT_ID  ClientId  OPTIONAL,IN PKSTART_ROUTINE  StartRoutine,IN PVOID  StartContext);
typedef NTSTATUS(*PsLookupProcessByProcessIdPtr)(IN HANDLE ProcessId,OUT PEPROCESS *Process);
typedef NTSTATUS(*PsSetCreateProcessNotifyRoutinePtr)(IN PCREATE_PROCESS_NOTIFY_ROUTINE  NotifyRoutine,IN BOOLEAN  Remove);
typedef NTSTATUS(*KeDelayExecutionThreadPtr)(IN KPROCESSOR_MODE  WaitMode,IN BOOLEAN  Alertable,IN PLARGE_INTEGER  Interval);
typedef NTSTATUS(*PsTerminateSystemThreadPtr)(IN NTSTATUS  ExitStatus);
typedef int		(*_wcsnicmpPtr)(const wchar_t *string1,const wchar_t *string2,size_t count );
typedef PVOID	(*memcpyPtr)(void *dest,const void *src,size_t count );
typedef PVOID	(*memsetPtr)(void *dest,int c,size_t count );
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct _apis {
	ExAllocatePoolWithTagPtr			api_ExAllocatePoolWithTag;
	ExFreePoolWithTagPtr				api_ExFreePoolWithTag;
	IoAllocateMdlPtr					api_IoAllocateMdl;
	IoFreeMdlPtr						api_IoFreeMdl;
	KeStackAttachProcessPtr				api_KeStackAttachProcessPtr;
	KeDelayExecutionThreadPtr			api_KeDelayExecutionThread;
	KeUnstackDetachProcessPtr			api_KeUnstackDetachProcess;
	KeServiceDescriptorTablePtr			api_KeServiceDescriptorTable;
	MmBuildMdlForNonPagedPoolPtr		api_MmBuildMdlForNonPagedPool;
	MmMapLockedPagesSpecifyCachePtr		api_MmMapLockedPagesSpecifyCache;
	MmUnmapLockedPagesPtr				api_MmUnmapLockedPages;
	NtBuildNumberPtr					api_NtBuildNumber;
	ObDereferenceObjectPtr				api_ObDereferenceObject;
	PsCreateSystemThreadPtr				api_PsCreateSystemThread;
	PsLookupProcessByProcessIdPtr		api_PsLookupProcessByProcessId;
	PsSetCreateProcessNotifyRoutinePtr	api_PsSetCreateProcessNotifyRoutine;
	PsTerminateSystemThreadPtr			api_PsTerminateSystemThread;
	_wcsnicmpPtr						api_wcsnicmp;
	memcpyPtr							api_memcpy;
	memsetPtr							api_memset;
} api;

static ULONG ntoskrnl[ ] = {
	0xA8AF5D76	/ ExAllocatePoolWithTag               /,
	0x1BA421E2	/ ExFreePoolWithTag                   /,
	0x405B1E51	/ IoAllocateMdl                       /,
	0x45C78A0C	/ IoFreeMdl                           /,
	0xEADEB1CD	/ KeStackAttachProcess                /,
	0xC73B7087	/ KeDelayExecutionThread              /,
	0x051EB19C	/ KeUnstackDetachProcess              /,
	0x9DA61437	/ KeServiceDescriptorTable            /,
	0x3E889164	/* MmBuildMdlForNonPagedPool          /,
	0x3B3EA6ED	/* MmMapLockedPagesSpecifyCache       /,
	0x15CDF0FB	/* MmUnmapLockedPages                 /,
	0x4D3095C1	/* NtBuildNumber                      /,
	0xDB4C3219	/* ObDereferenceObject                /,
	0x1F9F66C7	/* PsCreateSystemThread               /,
	0xD3378AA4	/* PsLookupProcessByProcessId         /,
	0xB3AB17EC	/* PsSetCreateProcessNotifyRoutine    /,
	0xB4B507BB	/* PsTerminateSystemThread            /,
	0x5053A9D8	/* _wcsnicmp                          /,
	0x00301139	/* memcpy                             /,
	0x0030159C	/* memset                             /,
	0x00000000
};

HANDLE g_KernelBase;*/