# Microsoft Developer Studio Generated NMAKE File, Based on NITE.dsp
!IF "$(CFG)" == ""
CFG=Wisdom - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Wisdom - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Wisdom - Win32 Release" && "$(CFG)" != "Wisdom - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NITE.mak" CFG="Wisdom - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Wisdom - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Wisdom - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Wisdom - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\NITE.exe"


CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\NITE.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp1 /ML /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\NITE.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NITE.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msvcrt.lib wininet.lib ws2_32.lib vfw32.lib mpr.lib psapi.lib urlmon.lib /nologo /entry:"EntryPoint" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\NITE.pdb" /machine:I386 /out:"$(OUTDIR)\NITE.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj"

"$(OUTDIR)\NITE.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Wisdom - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\NITE.exe"


CLEAN :
	-@erase "$(OUTDIR)\NITE.exe"
	-@erase ".\Release\main.obj"
	-@erase ".\Release\vc60.idb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp1 /ML /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"Release/NITE.pch" /YX /Fo"Release/" /Fd"Release/" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NITE.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msvcrt.lib wininet.lib ws2_32.lib vfw32.lib mpr.lib psapi.lib urlmon.lib /nologo /entry:"EntryPoint" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\NITE.pdb" /machine:I386 /out:"$(OUTDIR)\NITE.exe" 
LINK32_OBJS= \
	".\Release\main.obj"

"$(OUTDIR)\NITE.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("NITE.dep")
!INCLUDE "NITE.dep"
!ELSE 
!MESSAGE Warning: cannot find "NITE.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Wisdom - Win32 Release" || "$(CFG)" == "Wisdom - Win32 Debug"
SOURCE=.\main.cpp

!IF  "$(CFG)" == "Wisdom - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Wisdom - Win32 Debug"


".\Release\main.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

