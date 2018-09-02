
//////////////////////////////
// Version 1.10
// Jan 23rd, 2000
// Version 1.00
// May 20th, 1999
// Todd C. Wilson, Fresh Ground Software
// (todd@nopcode.com)
// This header file will kick in settings for Visual C++ 5 and 6 that will (usually)
// result in smaller exe's.
// The "trick" is to tell the compiler to not pad out the function calls; this is done
// by not using the /O1 or /O2 option - if you do, you implicitly use /Gy, which pads
// out each and every function call. In one single 500k dll, I managed to cut out 120k
// by this alone!
// The other two "tricks" are telling the Linker to merge all data-type segments together
// in the exe file. The relocation, read-only (constants) data, and code section (.text)
// sections can almost always be merged. Each section merged can save 4k in exe space,
// since each section is padded out to 4k chunks. This is very noticable with smaller
// exes, since you could have only 700 bytes of data, 300 bytes of code, 94 bytes of
// strings - padded out, this could be 12k of runtime, for 1094 bytes of stuff!
// Note that if you're using MFC static or some other 3rd party libs, you may get poor
// results with merging the readonly (.rdata) section - the exe may grow larger.
// To use this feature, define _MERGE_DATA_ in your project or before this header is used.
// With Visual C++ 5, the program uses a file alignement of 512 bytes, which results
// in a small exe. Under VC6, the program instead uses 4k, which is the same as the
// section size. The reason (from what I understand) is that 4k is the chunk size of
// the virtual memory manager, and that WinAlign (an end-user tuning tool for Win98)
// will re-align the programs on this boundary. The problem with this is that all of
// Microsoft's system exes and dlls are not tuned like this, and using 4k causes serious
// exe bloat. Very noticable for smaller programs.
// The "trick" for this is to use the undocumented FILEALIGN linker parm to change the
// padding from 4k to 1/2k, which results in a much smaller exe - anywhere from 20%-75%
// depending on the size. 


#ifdef NDEBUG
// /Og (global optimizations), /Os (favor small code), /Oy (no frame pointers)
#pragma optimize("gsy",on)

#pragma comment(linker,"/RELEASE")

// Note that merging the .rdata section will result in LARGER exe's if you using
// MFC (esp. static link). If this is desirable, define _MERGE_RDATA_ in your project.
#ifdef _MERGE_RDATA_
#pragma comment(linker,"/merge:.rdata=.data")
#endif // _MERGE_RDATA_

#pragma comment(linker,"/merge:.text=.data")
#pragma comment(linker,"/merge:.reloc=.data")

#if _MSC_VER >= 1000
// Only supported/needed with VC6; VC5 already does 0x200 for release builds.
// Totally undocumented! And if you set it lower than 512 bytes, the program crashes.
// Either leave at 0x200 or 0x1000
#pragma comment(linker,"/FILEALIGN:0x200")
#endif // _MSC_VER >= 1000

#endif // NDEBUG

//#pragma comment(linker,"/ENTRY:WinMain")
#pragma comment(linker,"/MERGE:.rdata=.data")
#pragma comment(linker,"/MERGE:.text=.data")
#pragma comment(lib,"msvcrt.lib")
#if (_MSC_VER < 1300)  
	#pragma comment(linker,"/IGNORE:4078")  
	#pragma comment(linker,"/OPT:NOWIN98")
#endif
#define WIN32_LEAN_AND_MEAN
