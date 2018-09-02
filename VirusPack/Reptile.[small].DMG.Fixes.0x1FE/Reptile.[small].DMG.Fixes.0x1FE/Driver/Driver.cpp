
#ifdef __cplusplus
extern "C"
{
#endif

#include <ntddk.h>
#include "Driver.h"

#ifdef __cplusplus
}
#endif

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS ntRet=STATUS_UNSUCCESSFUL;
	ntRet=FU_Entry(DriverObject,RegistryPath);
#ifdef GIVE_OUTPUT
	if (ntRet==STATUS_SUCCESS)
		DbgPrint("FU_Entry failed\n");
	else
		DbgPrint("FU_Entry successfull\n");
#endif

	ntRet=Jiurl_Entry(DriverObject,RegistryPath);
#ifdef GIVE_OUTPUT
	if (ntRet==STATUS_SUCCESS)
		DbgPrint("Jiurl_Entry failed\n");
	else
		DbgPrint("Jiurl_Entry successfull\n");
#endif

	return STATUS_SUCCESS;
}
