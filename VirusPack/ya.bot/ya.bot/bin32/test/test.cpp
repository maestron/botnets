#pragma optimize("gsy", on) 
#pragma comment(linker, "/RELEASE")
#pragma comment(linker, "/ENTRY:EntryPoint")
#pragma comment(linker, "/MERGE:.rdata=.data") 
#pragma comment(linker, "/MERGE:.text=.data")
#pragma comment(linker, "/MERGE:.reloc=.data") 
#pragma comment(linker, "/SECTION:.text,EWR /IGNORE:4078")
#pragma comment(linker, "/FILEALIGN:0x200")
#pragma comment(linker, "/stub:stub.dat")
#pragma comment(linker, "/subsystem:console")
#pragma comment(linker, "/NODEFAULTLIB:libc")
#pragma comment(lib, "msvcrt")
#pragma comment(lib, "ws2_32")

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

void EntryPoint()
{
		printf("hi\n");
		Sleep(5000);
		MessageBox(0, "hi", "hi", 0);
		ExitProcess(0);
}