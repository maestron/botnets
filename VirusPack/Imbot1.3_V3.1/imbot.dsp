# Microsoft Developer Studio Project File - Name="imbot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=imbot - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "imbot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "imbot.mak" CFG="imbot - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "imbot - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W2 /GX /O1 /I "lib/openssl/win32/include" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "NDEBUG" /D "_AFXDLL" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386 /out:"Bin/imbot.exe" /libpath:"lib/openssl/win32/lib"
# SUBTRACT LINK32 /incremental:yes
# Begin Target

# Name "imbot - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cpp\commands.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\imbot.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\irc.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\mods.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\protocol.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\threads.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\cmd.h
# End Source File
# Begin Source File

SOURCE=.\h\commands.h
# End Source File
# Begin Source File

SOURCE=.\configs.h
# End Source File
# Begin Source File

SOURCE=.\h\defines.h
# End Source File
# Begin Source File

SOURCE=.\h\externs.h
# End Source File
# Begin Source File

SOURCE=.\h\functions.h
# End Source File
# Begin Source File

SOURCE=.\h\imbot.h
# End Source File
# Begin Source File

SOURCE=.\h\includes.h
# End Source File
# Begin Source File

SOURCE=.\h\irc.h
# End Source File
# Begin Source File

SOURCE=.\h\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\h\mods.h
# End Source File
# Begin Source File

SOURCE=.\h\protocol.h
# End Source File
# Begin Source File

SOURCE=.\h\threads.h
# End Source File
# Begin Source File

SOURCE=.\h\zipit.h
# End Source File
# End Group
# End Target
# End Project
