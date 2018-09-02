@cl /GS- /c 64_absolute_1Gen.c
@cl /O1 /GS- /c 64_absolute.c
@link 64_absolute.obj 64_absolute_1Gen.obj /ENTRY:vxmain /OUT:64_absolute.exe /MERGE:.rdata=.data /MERGE:.data=.text /MERGE:.text=.vxbody /SECTION:.vxbody,ERW /SUBSYSTEM:CONSOLE /NODEFAULTLIB