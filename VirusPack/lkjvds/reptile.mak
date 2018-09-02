# Microsoft Developer Studio Generated NMAKE File, Based on reptile.dsp
!IF "$(CFG)" == ""
CFG=reptile - Win32 Debug
!MESSAGE No configuration specified. Defaulting to reptile - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "reptile - Win32 Release" && "$(CFG)" != "reptile - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "reptile.mak" CFG="reptile - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "reptile - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "reptile - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "reptile - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\Bin\reptile.exe"


CLEAN :
	-@erase "$(INTDIR)\advscan.obj"
	-@erase "$(INTDIR)\banner.obj"
	-@erase "$(INTDIR)\commands.obj"
	-@erase "$(INTDIR)\crypt.obj"
	-@erase "$(INTDIR)\dcom.obj"
	-@erase "$(INTDIR)\download.obj"
	-@erase "$(INTDIR)\driveinfo.obj"
	-@erase "$(INTDIR)\fphost.obj"
	-@erase "$(INTDIR)\ftpd.obj"
	-@erase "$(INTDIR)\fu.obj"
	-@erase "$(INTDIR)\info.obj"
	-@erase "$(INTDIR)\irc.obj"
	-@erase "$(INTDIR)\loaddlls.obj"
	-@erase "$(INTDIR)\lsass.obj"
	-@erase "$(INTDIR)\mssql.obj"
	-@erase "$(INTDIR)\netbios.obj"
	-@erase "$(INTDIR)\netdde.obj"
	-@erase "$(INTDIR)\netstatp.obj"
	-@erase "$(INTDIR)\netutils.obj"
	-@erase "$(INTDIR)\processes.obj"
	-@erase "$(INTDIR)\protocol.obj"
	-@erase "$(INTDIR)\pstore.obj"
	-@erase "$(INTDIR)\redirect.obj"
	-@erase "$(INTDIR)\regcontrol.obj"
	-@erase "$(INTDIR)\reptile.obj"
	-@erase "$(INTDIR)\secure.obj"
	-@erase "$(INTDIR)\service.obj"
	-@erase "$(INTDIR)\sniffer.obj"
	-@erase "$(INTDIR)\socks4.obj"
	-@erase "$(INTDIR)\speedtest.obj"
	-@erase "$(INTDIR)\svchost.obj"
	-@erase "$(INTDIR)\thcsql.obj"
	-@erase "$(INTDIR)\threads.obj"
	-@erase "$(INTDIR)\utility.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vscan.obj"
	-@erase "$(INTDIR)\wins.obj"
	-@erase "$(INTDIR)\wkssvc.obj"
	-@erase ".\Bin\reptile.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /I "lib/openssl/win32/include" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "NDEBUG" /Fp"$(INTDIR)\reptile.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\reptile.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\reptile.pdb" /machine:I386 /out:"Bin/reptile.exe" /libpath:"lib/openssl/win32/lib" 
LINK32_OBJS= \
	"$(INTDIR)\advscan.obj" \
	"$(INTDIR)\banner.obj" \
	"$(INTDIR)\dcom.obj" \
	"$(INTDIR)\fphost.obj" \
	"$(INTDIR)\lsass.obj" \
	"$(INTDIR)\mssql.obj" \
	"$(INTDIR)\netbios.obj" \
	"$(INTDIR)\netdde.obj" \
	"$(INTDIR)\svchost.obj" \
	"$(INTDIR)\thcsql.obj" \
	"$(INTDIR)\wins.obj" \
	"$(INTDIR)\wkssvc.obj" \
	"$(INTDIR)\commands.obj" \
	"$(INTDIR)\crypt.obj" \
	"$(INTDIR)\download.obj" \
	"$(INTDIR)\driveinfo.obj" \
	"$(INTDIR)\ftpd.obj" \
	"$(INTDIR)\fu.obj" \
	"$(INTDIR)\info.obj" \
	"$(INTDIR)\irc.obj" \
	"$(INTDIR)\loaddlls.obj" \
	"$(INTDIR)\netstatp.obj" \
	"$(INTDIR)\netutils.obj" \
	"$(INTDIR)\processes.obj" \
	"$(INTDIR)\protocol.obj" \
	"$(INTDIR)\pstore.obj" \
	"$(INTDIR)\redirect.obj" \
	"$(INTDIR)\regcontrol.obj" \
	"$(INTDIR)\reptile.obj" \
	"$(INTDIR)\secure.obj" \
	"$(INTDIR)\service.obj" \
	"$(INTDIR)\sniffer.obj" \
	"$(INTDIR)\socks4.obj" \
	"$(INTDIR)\speedtest.obj" \
	"$(INTDIR)\threads.obj" \
	"$(INTDIR)\utility.obj" \
	"$(INTDIR)\vscan.obj"

".\Bin\reptile.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "reptile - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\Bin\reptile-d.exe"


CLEAN :
	-@erase "$(INTDIR)\advscan.obj"
	-@erase "$(INTDIR)\banner.obj"
	-@erase "$(INTDIR)\commands.obj"
	-@erase "$(INTDIR)\crypt.obj"
	-@erase "$(INTDIR)\dcom.obj"
	-@erase "$(INTDIR)\download.obj"
	-@erase "$(INTDIR)\driveinfo.obj"
	-@erase "$(INTDIR)\fphost.obj"
	-@erase "$(INTDIR)\ftpd.obj"
	-@erase "$(INTDIR)\fu.obj"
	-@erase "$(INTDIR)\info.obj"
	-@erase "$(INTDIR)\irc.obj"
	-@erase "$(INTDIR)\loaddlls.obj"
	-@erase "$(INTDIR)\lsass.obj"
	-@erase "$(INTDIR)\mssql.obj"
	-@erase "$(INTDIR)\netbios.obj"
	-@erase "$(INTDIR)\netdde.obj"
	-@erase "$(INTDIR)\netstatp.obj"
	-@erase "$(INTDIR)\netutils.obj"
	-@erase "$(INTDIR)\processes.obj"
	-@erase "$(INTDIR)\protocol.obj"
	-@erase "$(INTDIR)\pstore.obj"
	-@erase "$(INTDIR)\redirect.obj"
	-@erase "$(INTDIR)\regcontrol.obj"
	-@erase "$(INTDIR)\reptile.obj"
	-@erase "$(INTDIR)\resources.res"
	-@erase "$(INTDIR)\secure.obj"
	-@erase "$(INTDIR)\service.obj"
	-@erase "$(INTDIR)\sniffer.obj"
	-@erase "$(INTDIR)\socks4.obj"
	-@erase "$(INTDIR)\speedtest.obj"
	-@erase "$(INTDIR)\svchost.obj"
	-@erase "$(INTDIR)\thcsql.obj"
	-@erase "$(INTDIR)\threads.obj"
	-@erase "$(INTDIR)\utility.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vscan.obj"
	-@erase "$(INTDIR)\wins.obj"
	-@erase "$(INTDIR)\wkssvc.obj"
	-@erase "$(OUTDIR)\reptile-d.pdb"
	-@erase ".\Bin\reptile-d.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /I "lib/openssl/win32/include" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_DEBUG" /Fp"$(INTDIR)\reptile.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\resources.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\reptile.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\reptile-d.pdb" /debug /machine:I386 /out:"Bin/reptile-d.exe" /pdbtype:sept /libpath:"lib/openssl/win32/lib" 
LINK32_OBJS= \
	"$(INTDIR)\advscan.obj" \
	"$(INTDIR)\banner.obj" \
	"$(INTDIR)\dcom.obj" \
	"$(INTDIR)\fphost.obj" \
	"$(INTDIR)\lsass.obj" \
	"$(INTDIR)\mssql.obj" \
	"$(INTDIR)\netbios.obj" \
	"$(INTDIR)\netdde.obj" \
	"$(INTDIR)\svchost.obj" \
	"$(INTDIR)\thcsql.obj" \
	"$(INTDIR)\wins.obj" \
	"$(INTDIR)\wkssvc.obj" \
	"$(INTDIR)\commands.obj" \
	"$(INTDIR)\crypt.obj" \
	"$(INTDIR)\download.obj" \
	"$(INTDIR)\driveinfo.obj" \
	"$(INTDIR)\ftpd.obj" \
	"$(INTDIR)\fu.obj" \
	"$(INTDIR)\info.obj" \
	"$(INTDIR)\irc.obj" \
	"$(INTDIR)\loaddlls.obj" \
	"$(INTDIR)\netstatp.obj" \
	"$(INTDIR)\netutils.obj" \
	"$(INTDIR)\processes.obj" \
	"$(INTDIR)\protocol.obj" \
	"$(INTDIR)\pstore.obj" \
	"$(INTDIR)\redirect.obj" \
	"$(INTDIR)\regcontrol.obj" \
	"$(INTDIR)\reptile.obj" \
	"$(INTDIR)\secure.obj" \
	"$(INTDIR)\service.obj" \
	"$(INTDIR)\sniffer.obj" \
	"$(INTDIR)\socks4.obj" \
	"$(INTDIR)\speedtest.obj" \
	"$(INTDIR)\threads.obj" \
	"$(INTDIR)\utility.obj" \
	"$(INTDIR)\vscan.obj" \
	"$(INTDIR)\resources.res"

".\Bin\reptile-d.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("reptile.dep")
!INCLUDE "reptile.dep"
!ELSE 
!MESSAGE Warning: cannot find "reptile.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "reptile - Win32 Release" || "$(CFG)" == "reptile - Win32 Debug"
SOURCE=.\advscan.cpp

"$(INTDIR)\advscan.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\banner.cpp

"$(INTDIR)\banner.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\dcom.cpp

"$(INTDIR)\dcom.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\fphost.cpp

"$(INTDIR)\fphost.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\lsass.cpp

"$(INTDIR)\lsass.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\mssql.cpp

"$(INTDIR)\mssql.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\netbios.cpp

"$(INTDIR)\netbios.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\netdde.cpp

"$(INTDIR)\netdde.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\svchost.cpp

"$(INTDIR)\svchost.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\thcsql.cpp

"$(INTDIR)\thcsql.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\wins.cpp

"$(INTDIR)\wins.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\wkssvc.cpp

"$(INTDIR)\wkssvc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\commands.cpp

"$(INTDIR)\commands.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\crypt.cpp

"$(INTDIR)\crypt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\download.cpp

"$(INTDIR)\download.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\driveinfo.cpp

"$(INTDIR)\driveinfo.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ftpd.cpp

"$(INTDIR)\ftpd.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\fu.cpp

"$(INTDIR)\fu.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\info.cpp

"$(INTDIR)\info.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\irc.cpp

"$(INTDIR)\irc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\loaddlls.cpp

"$(INTDIR)\loaddlls.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\netstatp.cpp

"$(INTDIR)\netstatp.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\netutils.cpp

"$(INTDIR)\netutils.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\processes.cpp

"$(INTDIR)\processes.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\protocol.cpp

"$(INTDIR)\protocol.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\pstore.cpp

"$(INTDIR)\pstore.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\redirect.cpp

"$(INTDIR)\redirect.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\regcontrol.cpp

"$(INTDIR)\regcontrol.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\reptile.cpp

"$(INTDIR)\reptile.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\secure.cpp

"$(INTDIR)\secure.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\service.cpp

"$(INTDIR)\service.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\sniffer.cpp

"$(INTDIR)\sniffer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\socks4.cpp

"$(INTDIR)\socks4.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\speedtest.cpp

"$(INTDIR)\speedtest.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\threads.cpp

"$(INTDIR)\threads.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\utility.cpp

"$(INTDIR)\utility.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\vscan.cpp

"$(INTDIR)\vscan.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Misc\resources.rc

!IF  "$(CFG)" == "reptile - Win32 Release"

!ELSEIF  "$(CFG)" == "reptile - Win32 Debug"


"$(INTDIR)\resources.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\resources.res" /i "Misc" /d "_DEBUG" $(SOURCE)


!ENDIF 


!ENDIF 

