// small.h - makes small executables with MSVC++ 6.0 - copy to Include folder
// **************************************************************************

#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.rdata=.data")
#pragma comment(linker,"/MERGE:.text=.data")
//#pragma comment( linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
#pragma comment(lib,"msvcrt.lib")
#if (_MSC_VER < 1300)
	#pragma comment(linker,"/IGNORE:4078")
	#pragma comment(linker,"/OPT:NOWIN98")
#endif

#define WIN32_LEAN_AND_MEAN
