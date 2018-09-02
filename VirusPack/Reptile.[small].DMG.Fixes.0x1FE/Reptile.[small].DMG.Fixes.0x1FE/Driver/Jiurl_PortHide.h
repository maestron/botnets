//================================================================
//	Copyright (c) JIURL, All Rights Reserved
//================================================================

NTSTATUS Jiurl_Dispatch(IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp);
void Jiurl_Unload(IN PDRIVER_OBJECT DriverObject);


#pragma pack(1)
typedef struct ServiceDescriptorEntry {
	unsigned int *ServiceTableBase;
	unsigned int *ServiceCounterTableBase; //Used only in checked build
	unsigned int NumberOfServices;
	unsigned char *ParamTableBase;
} ServiceDescriptorTableEntry_t, *PServiceDescriptorTableEntry_t;
#pragma pack()

__declspec(dllimport)  ServiceDescriptorTableEntry_t KeServiceDescriptorTable;

NTSYSAPI NTSTATUS NTAPI ZwDeviceIoControlFile(IN HANDLE FileHandle,IN HANDLE Event OPTIONAL,
    IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,IN PVOID ApcContext OPTIONAL,
    OUT PIO_STATUS_BLOCK IoStatusBlock,IN ULONG IoControlCode,IN PVOID InputBuffer OPTIONAL,
    IN ULONG InputBufferLength,OUT PVOID OutputBuffer OPTIONAL,IN ULONG OutputBufferLength);

typedef NTSTATUS (*ZWDEVICEIOCONTROLFILE)(IN HANDLE FileHandle,IN HANDLE Event OPTIONAL,
    IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,IN PVOID ApcContext OPTIONAL,
    OUT PIO_STATUS_BLOCK IoStatusBlock,IN ULONG IoControlCode,IN PVOID InputBuffer OPTIONAL,
    IN ULONG InputBufferLength,OUT PVOID OutputBuffer OPTIONAL,IN ULONG OutputBufferLength);

ZWDEVICEIOCONTROLFILE OldZwDeviceIoControlFile;

NTSTATUS NewZwDeviceIoControlFile(IN HANDLE FileHandle,IN HANDLE Event OPTIONAL,
	IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,IN PVOID ApcContext OPTIONAL,
    OUT PIO_STATUS_BLOCK IoStatusBlock,IN ULONG IoControlCode,IN PVOID InputBuffer OPTIONAL,
    IN ULONG InputBufferLength,OUT PVOID OutputBuffer OPTIONAL,IN ULONG OutputBufferLength);

// jiurl // from addrconv.cpp
#define ntohs(s)                         \
            ( ( ((s) >> 8) & 0x00FF ) |  \
              ( ((s) << 8) & 0xFF00 ) )

// jiurl // from tcpioctl.h tdiinfo.h tdistat.h
#define IOCTL_TCP_QUERY_INFORMATION_EX 0x00120003

//* Structure of an entity ID.
typedef struct TDIEntityID {
	ULONG		tei_entity;
	ULONG		tei_instance;
} TDIEntityID;

//* Structure of an object ID.
typedef struct TDIObjectID {
	TDIEntityID	toi_entity;
	ULONG		toi_class;
	ULONG		toi_type;
	ULONG		toi_id;
} TDIObjectID;

#define	CONTEXT_SIZE				16
//
// QueryInformationEx IOCTL. The return buffer is passed as the OutputBuffer
// in the DeviceIoControl request. This structure is passed as the
// InputBuffer.
//
struct tcp_request_query_information_ex {
	TDIObjectID   ID;                     // object ID to query.
    ULONG_PTR     Context[CONTEXT_SIZE/sizeof(ULONG_PTR)];  // multi-request context. Zeroed
	                                      // for the first request.
};

typedef struct tcp_request_query_information_ex
        TCP_REQUEST_QUERY_INFORMATION_EX,
        *PTCP_REQUEST_QUERY_INFORMATION_EX;

#define	CO_TL_ENTITY				0x400
#define	INFO_CLASS_PROTOCOL			0x200
#define	INFO_TYPE_PROVIDER			0x100
