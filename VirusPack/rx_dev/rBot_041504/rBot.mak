# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=rBot - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to rBot - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "rBot - Win32 Release" && "$(CFG)" != "rBot - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "rBot.mak" CFG="rBot - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rBot - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "rBot - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rBot - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
OUTDIR=.
INTDIR=.

ALL : "$(OUTDIR)\rBot.exe"

CLEAN : 
	-@erase "$(INTDIR)\rBot.obj"
	-@erase "$(OUTDIR)\rBot.exe"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"rBot.pch" /YX /c 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/rBot.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/rBot.pdb" /machine:I386 /out:"$(OUTDIR)/rBot.exe" 
LINK32_OBJS= \
	"$(INTDIR)\rBot.obj"

"$(OUTDIR)\rBot.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "rBot - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
OUTDIR=.
INTDIR=.

ALL : "$(OUTDIR)\rBot.exe"

CLEAN : 
	-@erase "$(INTDIR)\rBot.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\rBot.exe"
	-@erase "$(OUTDIR)\rBot.ilk"
	-@erase "$(OUTDIR)\rBot.pdb"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"rBot.pch" /YX /c 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/rBot.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/rBot.pdb" /debug /machine:I386 /out:"$(OUTDIR)/rBot.exe" 
LINK32_OBJS= \
	"$(INTDIR)\rBot.obj"

"$(OUTDIR)\rBot.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx.obj:
   $(CPP) $(CPP_PROJ) $<  

.c.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "rBot - Win32 Release"
# Name "rBot - Win32 Debug"

!IF  "$(CFG)" == "rBot - Win32 Release"

!ELSEIF  "$(CFG)" == "rBot - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\rBot.cpp
DEP_CPP_RBOT_=\
	".\advscan.h"\
	".\aliaslog.h"\
	".\autostart.h"\
	".\beagle.h"\
	".\capture.h"\
	".\cdkeys.h"\
	".\configs.h"\
	".\crc32.h"\
	".\crypt.h"\
	".\dameware.h"\
	".\dcc.h"\
	".\dcom.h"\
	".\dcom2.h"\
	".\ddos.h"\
	".\defines.h"\
	".\download.h"\
	".\driveinfo.h"\
	".\ehandler.h"\
	".\externs.h"\
	".\findfile.h"\
	".\findpass.h"\
	".\fphost.h"\
	".\functions.h"\
	".\globals.h"\
	".\httpd.h"\
	".\icmpflood.h"\
	".\ident.h"\
	".\includes.h"\
	".\irc_send.h"\
	".\keylogger.h"\
	".\kuang2.h"\
	".\loaddlls.h"\
	".\lsass.h"\
	".\misc.h"\
	".\mssql.h"\
	".\mydoom.h"\
	".\net.h"\
	".\netbios.h"\
	".\netdevil.h"\
	".\netutils.h"\
	".\optix.h"\
	".\passwd.h"\
	".\pingudp.h"\
	".\processes.h"\
	".\psniff.h"\
	".\rBot.h"\
	".\redirect.h"\
	".\remotecmd.h"\
	".\rlogind.h"\
	".\rndnick.h"\
	".\scan.h"\
	".\secure.h"\
	".\session.h"\
	".\shellcode.h"\
	".\socks4.h"\
	".\sub7.h"\
	".\synflood.h"\
	".\sysinfo.h"\
	".\tcpflood.h"\
	".\tcpip.h"\
	".\tftpd.h"\
	".\threads.h"\
	".\upnp.h"\
	".\visit.h"\
	".\webdav.h"\
	".\wildcard.h"\
	

"$(INTDIR)\rBot.obj" : $(SOURCE) $(DEP_CPP_RBOT_) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
