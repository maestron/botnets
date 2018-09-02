# Microsoft Developer Studio Generated NMAKE File, Based on Driver.dsp
!IF "$(CFG)" == ""
CFG=DRIVER - WIN32 RELEASE
!MESSAGE No configuration specified. Defaulting to DRIVER - WIN32 RELEASE.
!ENDIF 

!IF "$(CFG)" != "Driver - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Driver.mak" CFG="DRIVER - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Driver - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\Bin\Driver.sys"


CLEAN :
	-@erase "$(INTDIR)\Driver.obj"
	-@erase "$(INTDIR)\Jiurl_PortHide.obj"
	-@erase "$(INTDIR)\ProcessName.obj"
	-@erase "$(INTDIR)\Rootkit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase ".\Bin\driver.sys"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Gz /ML /W3 /Gm /Gi /Zi /O1 /I "E:\PROGRAM FILES\MICROSOFT SDK\INCLUDE" /I "E:\Program Files\Microsoft Visual Studio\VC98\INCLUDE" /I "E:\Program Files\Microsoft Visual Studio\VC98\MFC\INCLUDE" /I "E:\Program Files\Microsoft Visual Studio\VC98\ATL\INCLUDE" /I "E:\WINDDK\2600.1106\inc\ddk\wxp" /I "E:\WINDDK\2600.1106\inc\wxp" /D "WIN32" /D "NDEBUG" /D "_X86_" /D "i386" /D "DBG" /D _WIN32_WINNT=0x0500 /Fp"$(INTDIR)\Driver.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Driver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ntoskrnl.lib hal.lib /nologo /entry:"DriverEntry" /incremental:no /pdb:"$(OUTDIR)\driver.pdb" /machine:I386 /out:"Bin/driver.sys" /libpath:"E:\WINDDK\2600.1106\lib\wxp\i386" /subsystem:native /driver 
LINK32_OBJS= \
	"$(INTDIR)\Driver.obj" \
	"$(INTDIR)\Jiurl_PortHide.obj" \
	"$(INTDIR)\ProcessName.obj" \
	"$(INTDIR)\Rootkit.obj"

".\Bin\driver.sys" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Driver.dep")
!INCLUDE "Driver.dep"
!ELSE 
!MESSAGE Warning: cannot find "Driver.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Driver - Win32 Release"
SOURCE=.\Driver.cpp

"$(INTDIR)\Driver.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Jiurl_PortHide.cpp

"$(INTDIR)\Jiurl_PortHide.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ProcessName.c

"$(INTDIR)\ProcessName.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Rootkit.cpp

"$(INTDIR)\Rootkit.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

