/**********************************************************************
Trace alloc
-----------
Purpose:

  Implement a allocation check routine that reports the whole
  callstack for each leaked allocation.

  Based on the code for ExtendedTrace written by
  Zoltan Csizmadia, zoltan_csizmadia@yahoo.com.

Author:

  Erik Rydgren, erik@rydgrens.net.
  
Usage:
  1/ Define DETECT_LEAKS in the project settings under
     C++/preprocessor.

     If you want checking of overwrites then define DETECT_OVERWRITES
     in the project settings. Change the frequency of the checks by
     altering the NML_CHECK_EVERY define in tracealloc.cpp.
  
  2/ Compile.
  
     If you get multiple defined symbols (overloaded new and delete)
     add linker switch /FORCE:MULTIPLE on the exe and make sure the
     tracealloc new and delete is the ones used. If not, reorder the
     included libraries until they do.

**********************************************************************/

#if defined(_DEBUG) && defined(WIN32) && defined(DETECT_LEAKS)

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <ImageHlp.h>
#include <string>
#include <assert.h>

using namespace std;

typedef std::basic_string<TCHAR, char_traits<TCHAR> > tcstring;

// Setup how much buffer is used for a single path fetch, increase if you get AV's during leak dump (4096 is plenty though)
#define BUFFERSIZE 4096

// Define how many levels of callstack that should be fetched for each allocation.
// Each level costs 2*sizof(ULONG) bytes / allocation.
#define MAXSTACK 5

// Define size of no mans land
#define NO_MANS_LAND_SIZE 16

// Define frequency of no mans land checking
#define NML_CHECK_EVERY 1000

#pragma comment( lib, "imagehlp.lib" )

void GetStackTrace(HANDLE hThread, ULONG ranOffsets[][2], ULONG nMaxStack );
void WriteStackTrace(ULONG ranOffsets[][2], ULONG nMaxStack, tcstring& roOut);
void* TraceAlloc(size_t nSize);
void TraceDealloc(void* poMem);

void OutputDebugStringFormat( LPCTSTR lpszFormat, ... )
{
	TCHAR    lpszBuffer[BUFFERSIZE];
	va_list  fmtList;

	va_start( fmtList, lpszFormat );
	_vstprintf( lpszBuffer, lpszFormat, fmtList );
	va_end( fmtList );

   ::OutputDebugString( lpszBuffer );
}

// Unicode safe char* -> TCHAR* conversion
void PCSTR2LPTSTR( PCSTR lpszIn, LPTSTR lpszOut )
{
#if defined(UNICODE)||defined(_UNICODE)
   ULONG index = 0; 
   PCSTR lpAct = lpszIn;
   
	for( ; ; lpAct++ )
	{
		lpszOut[index++] = (TCHAR)(*lpAct);
		if ( *lpAct == 0 )
			break;
	} 
#else
   // This is trivial :)
	strcpy( lpszOut, lpszIn );
#endif
}

// Let's figure out the path for the symbol files
// Search path= ".;%_NT_SYMBOL_PATH%;%_NT_ALTERNATE_SYMBOL_PATH%;%SYSTEMROOT%;%SYSTEMROOT%\System32;" + lpszIniPath
// Note: There is no size check for lpszSymbolPath!
void InitSymbolPath( PSTR lpszSymbolPath, PCSTR lpszIniPath )
{
	CHAR lpszPath[BUFFERSIZE];

   // Creating the default path
   // ".;%_NT_SYMBOL_PATH%;%_NT_ALTERNATE_SYMBOL_PATH%;%SYSTEMROOT%;%SYSTEMROOT%\System32;"
	strcpy( lpszSymbolPath, "." );

	// environment variable _NT_SYMBOL_PATH
	if ( GetEnvironmentVariableA( "_NT_SYMBOL_PATH", lpszPath, BUFFERSIZE ) )
	{
	   strcat( lpszSymbolPath, ";" );
		strcat( lpszSymbolPath, lpszPath );
	}

	// environment variable _NT_ALTERNATE_SYMBOL_PATH
	if ( GetEnvironmentVariableA( "_NT_ALTERNATE_SYMBOL_PATH", lpszPath, BUFFERSIZE ) )
	{
	   strcat( lpszSymbolPath, ";" );
		strcat( lpszSymbolPath, lpszPath );
	}

	// environment variable SYSTEMROOT
	if ( GetEnvironmentVariableA( "SYSTEMROOT", lpszPath, BUFFERSIZE ) )
	{
	   strcat( lpszSymbolPath, ";" );
		strcat( lpszSymbolPath, lpszPath );
		strcat( lpszSymbolPath, ";" );

		// SYSTEMROOT\System32
		strcat( lpszSymbolPath, lpszPath );
		strcat( lpszSymbolPath, "\\System32" );
	}

   // Add user defined path
	if ( lpszIniPath != NULL )
		if ( lpszIniPath[0] != '\0' )
		{
		   strcat( lpszSymbolPath, ";" );
			strcat( lpszSymbolPath, lpszIniPath );
		}
}

// Uninitialize the loaded symbol files
BOOL UninitSymInfo()
{
	return SymCleanup( GetCurrentProcess() );
}

// Initializes the symbol files
BOOL InitSymInfo( PCSTR lpszInitialSymbolPath )
{
	CHAR     lpszSymbolPath[BUFFERSIZE];
   DWORD    symOptions = SymGetOptions();

	symOptions |= SYMOPT_LOAD_LINES; 
	symOptions &= ~SYMOPT_UNDNAME;
	SymSetOptions( symOptions );

   // Get the search path for the symbol files
	InitSymbolPath( lpszSymbolPath, lpszInitialSymbolPath );

	return SymInitialize( GetCurrentProcess(), lpszSymbolPath, TRUE);
}

// Get the module name from a given address
BOOL GetModuleNameFromAddress( UINT address, LPTSTR lpszModule )
{
	BOOL              ret = FALSE;
	IMAGEHLP_MODULE   moduleInfo;

	::ZeroMemory( &moduleInfo, sizeof(moduleInfo) );
	moduleInfo.SizeOfStruct = sizeof(moduleInfo);

	if ( SymGetModuleInfo( GetCurrentProcess(), (DWORD)address, &moduleInfo ) )
	{
	   // Got it!
		PCSTR2LPTSTR( moduleInfo.ModuleName, lpszModule );
		ret = TRUE;
	}
	else
	   // Not found :(
		_tcscpy( lpszModule, _T("?") );
	
	return ret;
}

// Get function prototype and parameter info from ip address and stack address
BOOL GetFunctionInfoFromAddresses( ULONG fnAddress, ULONG stackAddress, LPTSTR lpszSymbol )
{
	BOOL              ret = FALSE;
	DWORD             dwDisp = 0;
	DWORD             dwSymSize = 10000;
   TCHAR             lpszUnDSymbol[BUFFERSIZE]=_T("?");
	CHAR              lpszNonUnicodeUnDSymbol[BUFFERSIZE]="?";
	LPTSTR            lpszParamSep = NULL;
	LPCTSTR           lpszParsed = lpszUnDSymbol;
	PIMAGEHLP_SYMBOL  pSym = (PIMAGEHLP_SYMBOL)GlobalAlloc( GMEM_FIXED, dwSymSize );

	::ZeroMemory( pSym, dwSymSize );
	pSym->SizeOfStruct = dwSymSize;
	pSym->MaxNameLength = dwSymSize - sizeof(IMAGEHLP_SYMBOL);

   // Set the default to unknown
	_tcscpy( lpszSymbol, _T("?") );

	// Get symbol info for IP
	if ( SymGetSymFromAddr( GetCurrentProcess(), (ULONG)fnAddress, &dwDisp, pSym ) )
	{
	   // Make the symbol readable for humans
		UnDecorateSymbolName( pSym->Name, lpszNonUnicodeUnDSymbol, BUFFERSIZE, 
			UNDNAME_COMPLETE | 
			UNDNAME_NO_THISTYPE |
			UNDNAME_NO_SPECIAL_SYMS |
			UNDNAME_NO_MEMBER_TYPE |
			UNDNAME_NO_MS_KEYWORDS |
			UNDNAME_NO_ACCESS_SPECIFIERS );

      // Symbol information is ANSI string
		PCSTR2LPTSTR( lpszNonUnicodeUnDSymbol, lpszUnDSymbol );

      // I am just smarter than the symbol file :)
		if ( _tcscmp(lpszUnDSymbol, _T("_WinMain@16")) == 0 )
			_tcscpy(lpszUnDSymbol, _T("WinMain(HINSTANCE,HINSTANCE,LPCTSTR,int)"));
		else
		if ( _tcscmp(lpszUnDSymbol, _T("_main")) == 0 )
			_tcscpy(lpszUnDSymbol, _T("main(int,TCHAR * *)"));
		else
		if ( _tcscmp(lpszUnDSymbol, _T("_mainCRTStartup")) == 0 )
			_tcscpy(lpszUnDSymbol, _T("mainCRTStartup()"));
		else
		if ( _tcscmp(lpszUnDSymbol, _T("_wmain")) == 0 )
			_tcscpy(lpszUnDSymbol, _T("wmain(int,TCHAR * *,TCHAR * *)"));
		else
		if ( _tcscmp(lpszUnDSymbol, _T("_wmainCRTStartup")) == 0 )
			_tcscpy(lpszUnDSymbol, _T("wmainCRTStartup()"));

		lpszSymbol[0] = _T('\0');

      // Let's go through the stack, and modify the function prototype, and insert the actual
      // parameter values from the stack
		if ( _tcsstr( lpszUnDSymbol, _T("(void)") ) == NULL && _tcsstr( lpszUnDSymbol, _T("()") ) == NULL)
		{
			ULONG index = 0;
			for( ; ; index++ )
			{
				lpszParamSep = _tcschr( lpszParsed, _T(',') );
				if ( lpszParamSep == NULL )
					break;

				*lpszParamSep = _T('\0');

				_tcscat( lpszSymbol, lpszParsed );
				_stprintf( lpszSymbol + _tcslen(lpszSymbol), _T("=0x%08X,"), *((ULONG*)(stackAddress) + 2 + index) );

				lpszParsed = lpszParamSep + 1;
			}

			lpszParamSep = _tcschr( lpszParsed, _T(')') );
			if ( lpszParamSep != NULL )
			{
				*lpszParamSep = _T('\0');

				_tcscat( lpszSymbol, lpszParsed );
				_stprintf( lpszSymbol + _tcslen(lpszSymbol), _T("=0x%08X)"), *((ULONG*)(stackAddress) + 2 + index) );

				lpszParsed = lpszParamSep + 1;
			}
		}

		_tcscat( lpszSymbol, lpszParsed );
   
		ret = TRUE;
	}

	GlobalFree( pSym );

	return ret;
}

// Get source file name and line number from IP address
// The output format is: "sourcefile(linenumber)" or
//                       "modulename!address" or
//                       "address"
BOOL GetSourceInfoFromAddress( UINT address, LPTSTR lpszSourceInfo )
{
	BOOL           ret = FALSE;
	IMAGEHLP_LINE  lineInfo;
	DWORD          dwDisp;
	TCHAR          lpszFileName[BUFFERSIZE] = _T("");
	TCHAR          lpModuleInfo[BUFFERSIZE] = _T("");

	_tcscpy( lpszSourceInfo, _T("?(?)") );

	::ZeroMemory( &lineInfo, sizeof( lineInfo ) );
	lineInfo.SizeOfStruct = sizeof( lineInfo );

	if ( SymGetLineFromAddr( GetCurrentProcess(), address, &dwDisp, &lineInfo ) )
	{
	   // Got it. Let's use "sourcefile(linenumber)" format
		PCSTR2LPTSTR( lineInfo.FileName, lpszFileName );
		_stprintf( lpszSourceInfo, _T("%s(%d)"), lpszFileName, lineInfo.LineNumber );
		ret = TRUE;
	}
	else
	{
      // There is no source file information. :(
      // Let's use the "modulename!address" format
	  	GetModuleNameFromAddress( address, lpModuleInfo );

		if ( lpModuleInfo[0] == _T('?') || lpModuleInfo[0] == _T('\0'))
		   // There is no modulename information. :((
         // Let's use the "address" format
			_stprintf( lpszSourceInfo, _T("0x%08X"), lpModuleInfo, address );
		else
			_stprintf( lpszSourceInfo, _T("%s!0x%08X"), lpModuleInfo, address );

		ret = FALSE;
	}
	
	return ret;
}

void GetStackTrace(HANDLE hThread, ULONG ranOffsets[][2], ULONG nMaxStack )
{
	STACKFRAME     callStack;
	BOOL           bResult;
	CONTEXT        context;
	TCHAR          symInfo[BUFFERSIZE] = _T("?");
	TCHAR          srcInfo[BUFFERSIZE] = _T("?");
	HANDLE         hProcess = GetCurrentProcess();

   // If it's not this thread, let's suspend it, and resume it at the end
	if ( hThread != GetCurrentThread() )
		if ( SuspendThread( hThread ) == -1 )
		{
		   // whaaat ?!
		   OutputDebugStringFormat( _T("Call stack info(thread=0x%X) failed.\n") );
			return;
		}

	::ZeroMemory( &context, sizeof(context) );
	context.ContextFlags = CONTEXT_FULL;

	if ( !GetThreadContext( hThread, &context ) )
	{
      OutputDebugStringFormat( _T("Call stack info(thread=0x%X) failed.\n") );
	   return;
	}
	
	::ZeroMemory( &callStack, sizeof(callStack) );
	callStack.AddrPC.Offset    = context.Eip;
	callStack.AddrStack.Offset = context.Esp;
	callStack.AddrFrame.Offset = context.Ebp;
	callStack.AddrPC.Mode      = AddrModeFlat;
	callStack.AddrStack.Mode   = AddrModeFlat;
	callStack.AddrFrame.Mode   = AddrModeFlat;

	for( ULONG index = 0; ; index++ ) 
	{
		bResult = StackWalk(
			IMAGE_FILE_MACHINE_I386,
			hProcess,
			hThread,
	      &callStack,
			NULL, 
			NULL,
			SymFunctionTableAccess,
			SymGetModuleBase,
			NULL);

    // Ignore the first two levels (it's only TraceAlloc and operator new anyhow)
		if ( index < 3 )
	    continue;

    // Break if we have fetched nMaxStack levels
    if ( index-3 == nMaxStack)
      break;

    // If we are at the top of the stackframe then break.
		if( !bResult || callStack.AddrFrame.Offset == 0) {
      ranOffsets[index-3][0] = 0;
      ranOffsets[index-3][1] = 0;
			break;
    }
    	
    // Remember program counter and frame pointer
    ranOffsets[index-3][0] = callStack.AddrPC.Offset;
    ranOffsets[index-3][1] = callStack.AddrFrame.Offset;
	}

	if ( hThread != GetCurrentThread() )
		ResumeThread( hThread );
}

void WriteStackTrace(ULONG ranOffsets[][2], ULONG nMaxStack, tcstring& roOut)
{
	TCHAR          symInfo[BUFFERSIZE] = _T("?");
	TCHAR          srcInfo[BUFFERSIZE] = _T("?");

  for (ULONG index = 0; index < nMaxStack && ranOffsets[index][0] != 0 && ranOffsets[index][1] != 0; index++) {
  	GetFunctionInfoFromAddresses( ranOffsets[index][0], ranOffsets[index][1], symInfo );
	  GetSourceInfoFromAddress( ranOffsets[index][0], srcInfo );

    roOut += _T("     ");
    roOut += srcInfo;
    roOut += _T(" : ");
    roOut += symInfo;
    roOut += _T("\n");
  }
}

struct sdAllocBlock {
  unsigned long nMagicNumber;
  sdAllocBlock* poNext;
  sdAllocBlock* poPrev;
  size_t nSize;
  ULONG anStack[MAXSTACK][2];
  char pzNoMansLand[NO_MANS_LAND_SIZE];

  sdAllocBlock()
  {
    Init();
  }

  void Init() {
    poNext = this;
    poPrev = this;
    nMagicNumber = 0x55555555;
  }

  void Disconnect() {
    if (poNext != this) {
      poNext->poPrev = poPrev;
      poPrev->poNext = poNext;
      poNext = this;
      poPrev = this;
    }
  }

  void ConnectTo(sdAllocBlock* poPos) {
    Disconnect();
    poPrev = poPos;
    poNext = poPos->poNext;
    poPos->poNext->poPrev = this;
    poPos->poNext = this;
  }
};

void LeakDump(tcstring& roOut);

class CS {
  CRITICAL_SECTION cs;
public:
  CS() { InitializeCriticalSection(&cs); }
  ~CS() { }
  operator CRITICAL_SECTION& () { return cs; }
};

class Guard {
  CRITICAL_SECTION& rcs;
public:
  Guard(CRITICAL_SECTION& rcs)
  : rcs(rcs) { EnterCriticalSection(&rcs); }
  ~Guard() { LeaveCriticalSection(&rcs); }
};


class cLeakDetector
{
public:

  cLeakDetector() {
    InitSymInfo(NULL);
  }
  
  ~cLeakDetector() {    
    tcstring leaks;    
    LeakDump(leaks);    
    OutputDebugString(leaks.c_str());    
    UninitSymInfo();  
  }
};

static unsigned int nNumAllocs = 0;
static unsigned int nCurrentAllocs = 0;
static unsigned int nMaxConcurrent = 0;

CS& Gate() {
  static CS cs;
  return cs;
}

sdAllocBlock& Head()
{
  static cLeakDetector oDetector;
  static sdAllocBlock oHead;
  return oHead;
}

class cInitializer { 
  public: cInitializer() { Head(); }; 
} oInitalizer;

void LeakDump(tcstring& roOut)
{
  Guard at(Gate());
  
  TCHAR buffer[65];

  sdAllocBlock* poBlock = Head().poNext;
  while (poBlock != &Head()) {
    tcstring stack;
    WriteStackTrace(poBlock->anStack, MAXSTACK, stack);

    bool bIsKnownLeak = false;

    // afxMap leaks is MFC. Not ours.
    if (stack.find(_T(": afxMap")) != tcstring::npos)
      bIsKnownLeak = true;

    if (!bIsKnownLeak) {
      roOut += _T("Leak of ");
      roOut += _itot(poBlock->nSize, buffer, 10);
      roOut += _T(" bytes detected:\n");
      roOut += stack;
      roOut += _T("\n");
    }

    poBlock = poBlock->poNext;
  }

  roOut += _T("Memory statistics\n-----------------\n");
  roOut += _T("Total allocations: ");
  roOut += _itot(nNumAllocs, buffer, 10);
  roOut += _T("\n");
  roOut += _T("Max concurrent allocations: ");
  roOut += _itot(nMaxConcurrent, buffer, 10);
  roOut += _T("\n");
}


bool AssertMem(char* m, char c, size_t s)
{
  for (size_t i = 0; i < s; i++)
    if (m[i] != c) break;
  return i >= s;
}

void CheckNoMansLand()
{
  Guard at(Gate());

  sdAllocBlock* poBlock = Head().poNext;
  while (poBlock != &Head()) {
    if (!AssertMem(poBlock->pzNoMansLand, 0x55, NO_MANS_LAND_SIZE)) {
      bool MEMORYERROR_STUFF_WRITTEN_IN_NOMANSLAND_LEAD = false;
      tcstring stack;
      WriteStackTrace(poBlock->anStack, MAXSTACK, stack);
      assert(MEMORYERROR_STUFF_WRITTEN_IN_NOMANSLAND_LEAD);
    }
    char* pzNoMansLand = ((char*)poBlock) + sizeof(sdAllocBlock) + poBlock->nSize;
    if (!AssertMem(pzNoMansLand, 0x55, NO_MANS_LAND_SIZE)) {
      bool MEMORYERROR_STUFF_WRITTEN_IN_NOMANSLAND_TAIL = false;
      tcstring stack;
      WriteStackTrace(poBlock->anStack, MAXSTACK, stack);
      assert(MEMORYERROR_STUFF_WRITTEN_IN_NOMANSLAND_TAIL);
    }
    poBlock = poBlock->poNext;
  }
}

void* TraceAlloc(size_t nSize)
{
  Guard at(Gate());
  
  nNumAllocs++;
#ifdef DETECT_OVERWRITES
  if (nNumAllocs % NML_CHECK_EVERY == 0) {
    CheckNoMansLand();
  }
#endif

  sdAllocBlock* poBlock = (sdAllocBlock*) malloc(nSize + sizeof(sdAllocBlock) + NO_MANS_LAND_SIZE);
  poBlock->Init();
  poBlock->nSize = nSize;
  char* pzNoMansLand = ((char*)poBlock) + sizeof(sdAllocBlock) + poBlock->nSize;
  memset(poBlock->pzNoMansLand, 0x55, NO_MANS_LAND_SIZE);
  memset(pzNoMansLand, 0x55, NO_MANS_LAND_SIZE);

  GetStackTrace(GetCurrentThread(), poBlock->anStack, MAXSTACK );

  poBlock->ConnectTo(&Head());
  nCurrentAllocs++;
  if (nCurrentAllocs > nMaxConcurrent)
    nMaxConcurrent = nCurrentAllocs;
  return (void*)(((char*) poBlock) + sizeof(sdAllocBlock));
}


void TraceDealloc(void* poMem)
{
  Guard at(Gate());

  if (!poMem) return; // delete NULL; = do nothing

  sdAllocBlock* poBlock = (sdAllocBlock*) ((char*)poMem - sizeof(sdAllocBlock));
  char* pzNoMansLand = ((char*)poBlock) + sizeof(sdAllocBlock) + poBlock->nSize;

  if (poBlock->nMagicNumber != 0x55555555) {
    // Whupps, something fishy is going on

    // Validate the address against our list of allocated blocks
    sdAllocBlock* poLoopBlock = Head().poNext;
    while (poLoopBlock != &Head() && poLoopBlock != poBlock)
      poLoopBlock = poLoopBlock->poNext;
    if (poLoopBlock == &Head()) {
      // Hell we didn't allocate this block.
      // Just free the memory and hope for the best.
      free(poMem);
    }
    else {
      bool MEMORYERROR_STUFF_WRITTEN_IN_NOMANSLAND_LEAD = false;
      assert(MEMORYERROR_STUFF_WRITTEN_IN_NOMANSLAND_LEAD);
    }
  }  
  else if (!AssertMem(poBlock->pzNoMansLand, 0x55, NO_MANS_LAND_SIZE)) {
    bool MEMORYERROR_STUFF_WRITTEN_IN_NOMANSLAND_LEAD = false;
    assert(MEMORYERROR_STUFF_WRITTEN_IN_NOMANSLAND_LEAD);
  }
  else if (!AssertMem(pzNoMansLand, 0x55, NO_MANS_LAND_SIZE)) {
    bool MEMORYERROR_STUFF_WRITTEN_IN_NOMANSLAND_TAIL = false;
    assert(MEMORYERROR_STUFF_WRITTEN_IN_NOMANSLAND_TAIL);
  }
  else {
    poBlock->Disconnect();
    free(poBlock);
    nCurrentAllocs--;
  }
}

// Take over global new and delete
void* operator new(size_t s)
{
  return TraceAlloc(s);
}

void* operator new[](size_t s)
{
  return TraceAlloc(s);
}

void operator delete(void* pMem)
{
  TraceDealloc(pMem);
}

void operator delete[] (void* pMem)
{
  TraceDealloc(pMem);
}

// And then some crap for taking over MFC allocations.
void* __cdecl operator new(size_t s, LPCSTR lpszFileName, int nLine)
{
  return TraceAlloc(s);
}

void* __cdecl operator new[](size_t s, LPCSTR lpszFileName, int nLine)
{
  return TraceAlloc(s);
}

void __cdecl operator delete(void* pMem, LPCSTR /* lpszFileName */, int /* nLine */)
{
  TraceDealloc(pMem);
}

void __cdecl operator delete[](void* pMem, LPCSTR /* lpszFileName */, int /* nLine */)
{
  TraceDealloc(pMem);
}

#endif
