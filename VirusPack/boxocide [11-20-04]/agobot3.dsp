# Microsoft Developer Studio Project File - Name="agobot3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=agobot3 - Win32 Debug No OpenSSL Internal
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "agobot3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "agobot3.mak" CFG="agobot3 - Win32 Debug No OpenSSL Internal"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "agobot3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "agobot3 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "agobot3 - Win32 Release Console" (based on "Win32 (x86) Application")
!MESSAGE "agobot3 - Win32 Release No OpenSSL" (based on "Win32 (x86) Application")
!MESSAGE "agobot3 - Win32 Release Console No OpenSSL" (based on "Win32 (x86) Application")
!MESSAGE "agobot3 - Win32 Debug No OpenSSL" (based on "Win32 (x86) Application")
!MESSAGE "agobot3 - Win32 Debug Internal" (based on "Win32 (x86) Application")
!MESSAGE "agobot3 - Win32 Debug No OpenSSL Internal" (based on "Win32 (x86) Application")
!MESSAGE "agobot3 - Win32 Release Console Test" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "agobot3"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "agobot3 - Win32 Release"

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
# ADD CPP /nologo /G6 /MD /W3 /Gi /GX /Og /Os /Oy /Gf /Gy /I "lib/stlport" /I "lib/pcre/win32" /I "lib/libpcap/include" /I "lib/xlibc/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "__CLEANUP_SEH" /YX /FD /c
# SUBTRACT CPP /Ox /Ow /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 msvcrt.lib msvcprt.lib gdi32.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib dnsapi.lib pcre.lib odbc32.lib odbccp32.lib ole32.lib wpcap.lib packet.lib iphlpapi.lib npptools.lib version.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib /out:"bin/win32/agobot3.exe" /libpath:"lib/pcre/win32" /libpath:"lib/libpcap/lib" /ignore:4033
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MDd /W3 /Gm /Gi /GX /ZI /Od /I "lib/stlport" /I "lib/pcre/win32" /I "lib/libpcap/include" /I "lib/xlibc/include" /D "_DEBUG" /D "DBGCONSOLE" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "__CLEANUP_SEH" /FAs /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winspool.lib comdlg32.lib oleaut32.lib uuid.lib gdi32.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib dnsapi.lib pcre.lib odbc32.lib odbccp32.lib ole32.lib wpcap.lib packet.lib iphlpapi.lib npptools.lib version.lib /nologo /subsystem:windows /map /debug /machine:I386 /out:"bin/win32/agobot3_debug.exe" /pdbtype:sept /libpath:"lib/pcre/win32" /libpath:"lib/libpcap/lib" /ignore:4033
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "agobot3___Win32_Release_Console"
# PROP BASE Intermediate_Dir "agobot3___Win32_Release_Console"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "agobot3___Win32_Release_Console"
# PROP Intermediate_Dir "agobot3___Win32_Release_Console"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /Zp1 /MD /W3 /GX /O1 /Ob0 /I "lib/ZThread/win32/include" /I "lib/openssl/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /FR /YX /FD /c
# ADD CPP /nologo /G6 /MD /W3 /Gi /GX /Ow /Og /Os /Oy /Gf /Gy /I "lib/stlport" /I "lib/pcre/win32" /I "lib/libpcap/include" /I "lib/xlibc/include" /D "NDEBUG" /D "DBGCONSOLE" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "__CLEANUP_SEH" /FR /YX /FD /c
# SUBTRACT CPP /Ox
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 msvcrt.lib msvcprt.lib ZThread.lib oldnames.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib ssleay32.lib libeay32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib /out:"bin/win32/agobot3.exe" /libpath:"lib/ZThread/win32/lib" /libpath:"lib/openssl/lib"
# ADD LINK32 gdi32.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib dnsapi.lib pcre.lib odbc32.lib odbccp32.lib ole32.lib wpcap.lib packet.lib iphlpapi.lib npptools.lib version.lib /nologo /subsystem:windows /machine:I386 /out:"bin/win32/agobot3_console.exe" /libpath:"lib/pcre/win32" /libpath:"lib/libpcap/lib" /ignore:4033
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "agobot3___Win32_Release_No_OpenSSL"
# PROP BASE Intermediate_Dir "agobot3___Win32_Release_No_OpenSSL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "agobot3___Win32_Release_No_OpenSSL"
# PROP Intermediate_Dir "agobot3___Win32_Release_No_OpenSSL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /Ob0 /I "lib/pthreads/win32" /I "lib/openssl/win32/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "ADNS_JGAA_WIN32" /FR /YX /FD /c
# ADD CPP /nologo /G6 /MD /W3 /Gi /GX /Og /Os /Oy /Gf /Gy /I "lib/stlport" /I "lib/pcre/win32" /I "lib/libpcap/include" /I "lib/xlibc/include" /D "NDEBUG" /D "XLIBC_NO_OPENSSL" /D "AGOBOT_NO_OPENSSL" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "__CLEANUP_SEH" /YX /FD /c
# SUBTRACT CPP /Ox /Ow /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 msvcrt.lib msvcprt.lib oldnames.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib ssleay32.lib libeay32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib /out:"bin/win32/agobot3.exe" /libpath:"lib/ZThread/win32/lib" /libpath:"lib/openssl/win32/lib"
# ADD LINK32 msvcrt.lib msvcprt.lib gdi32.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib dnsapi.lib pcre.lib odbc32.lib odbccp32.lib ole32.lib packet.lib wpcap.lib iphlpapi.lib npptools.lib version.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib /out:"bin/win32/agobot3_nossl.exe" /libpath:"lib/pcre/win32" /libpath:"lib/libpcap/lib" /ignore:4033
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "agobot3___Win32_Release_Console_No_OpenSSL"
# PROP BASE Intermediate_Dir "agobot3___Win32_Release_Console_No_OpenSSL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "agobot3___Win32_Release_Console_No_OpenSSL"
# PROP Intermediate_Dir "agobot3___Win32_Release_Console_No_OpenSSL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /Ob0 /I "lib/pthreads/win32" /I "lib/openssl/win32/include" /D "NDEBUG" /D "DBGCONSOLE" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "ADNS_JGAA_WIN32" /FR /YX /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GX /Ow /Og /Os /Oy /Gf /Gy /I "lib/stlport" /I "lib/pcre/win32" /I "lib/libpcap/include" /I "lib/xlibc/include" /D "NDEBUG" /D "DBGCONSOLE" /D "XLIBC_NO_OPENSSL" /D "AGOBOT_NO_OPENSSL" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "__CLEANUP_SEH" /FR /YX /FD /c
# SUBTRACT CPP /Ox
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 msvcrt.lib msvcprt.lib oldnames.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib ssleay32.lib libeay32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib /out:"bin/win32/agobot3.exe" /libpath:"lib/ZThread/win32/lib" /libpath:"lib/openssl/win32/lib"
# ADD LINK32 gdi32.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib dnsapi.lib pcre.lib odbc32.lib odbccp32.lib ole32.lib wpcap.lib packet.lib iphlpapi.lib npptools.lib version.lib /nologo /subsystem:windows /pdb:none /machine:I386 /out:"bin/win32/agobot3_console_nossl.exe" /libpath:"lib/pcre/win32" /libpath:"lib/libpcap/lib" /ignore:4033
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "agobot3___Win32_Debug_No_OpenSSL"
# PROP BASE Intermediate_Dir "agobot3___Win32_Debug_No_OpenSSL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "agobot3___Win32_Debug_No_OpenSSL"
# PROP Intermediate_Dir "agobot3___Win32_Debug_No_OpenSSL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "lib/pthreads/win32" /I "lib/openssl/win32/include" /D "_DEBUG" /D "DBGCONSOLE" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "ADNS_JGAA_WIN32" /FAs /FR /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MDd /W3 /Gm /Gi /GX /ZI /Od /I "lib/stlport" /I "lib/pcre/win32" /I "lib/libpcap/include" /I "lib/xlibc/include" /D "_DEBUG" /D "DBGCONSOLE" /D "XLIBC_NO_OPENSSL" /D "AGOBOT_NO_OPENSSL" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "__CLEANUP_SEH" /FAs /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winspool.lib comdlg32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib ssleay32D.lib libeay32D.lib /nologo /subsystem:windows /map /debug /machine:I386 /out:"bin/win32/agobot3d.exe" /pdbtype:sept /libpath:"lib/ZThread/win32/lib" /libpath:"lib/openssl/win32/lib"
# SUBTRACT BASE LINK32 /profile
# ADD LINK32 winspool.lib comdlg32.lib oleaut32.lib uuid.lib gdi32.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib dnsapi.lib pcre.lib odbc32.lib odbccp32.lib ole32.lib wpcap.lib packet.lib iphlpapi.lib npptools.lib version.lib /nologo /subsystem:windows /map /debug /machine:I386 /out:"bin/win32/agobot3_debug.exe" /pdbtype:sept /libpath:"lib/pcre/win32" /libpath:"lib/libpcap/lib" /ignore:4033
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "agobot3___Win32_Debug_Internal"
# PROP BASE Intermediate_Dir "agobot3___Win32_Debug_Internal"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "agobot3___Win32_Debug_Internal"
# PROP Intermediate_Dir "agobot3___Win32_Debug_Internal"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /MTd /W3 /Gm /Gi /GX /ZI /Od /I "lib/stlport" /I "lib/pcre" /I "lib/libpcap/include" /I "lib/xlibc/include" /D "_DEBUG" /D "DBGCONSOLE" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "__CLEANUP_SEH" /FAs /FR /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MDd /W3 /Gm /Gi /GX /ZI /Od /I "lib/stlport" /I "lib/pcre/win32" /I "lib/libpcap/include" /I "lib/xlibc/include" /D "_DEBUG" /D "DBGCONSOLE" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "__CLEANUP_SEH" /FAs /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winspool.lib comdlg32.lib oleaut32.lib uuid.lib gdi32.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib dnsapi.lib pcre.lib /nologo /subsystem:windows /map /debug /machine:I386 /out:"bin/win32/agobot3_debug.exe" /pdbtype:sept /libpath:"lib/pcre" /libpath:"lib/libpcap/lib" /ignore:4033
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winspool.lib comdlg32.lib oleaut32.lib uuid.lib gdi32.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib dnsapi.lib pcre.lib odbc32.lib odbccp32.lib ole32.lib wpcap.lib packet.lib iphlpapi.lib npptools.lib version.lib /nologo /subsystem:windows /map /debug /machine:I386 /out:"bin/win32/agobot3_debug.exe" /pdbtype:sept /libpath:"lib/pcre/win32" /libpath:"lib/libpcap/lib" /ignore:4033
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "agobot3___Win32_Debug_No_OpenSSL_Internal"
# PROP BASE Intermediate_Dir "agobot3___Win32_Debug_No_OpenSSL_Internal"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "agobot3___Win32_Debug_No_OpenSSL_Internal"
# PROP Intermediate_Dir "agobot3___Win32_Debug_No_OpenSSL_Internal"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /MTd /W3 /Gm /Gi /GX /ZI /Od /I "lib/stlport" /I "lib/pcre" /I "lib/libpcap/include" /I "lib/xlibc/include" /D "_DEBUG" /D "DBGCONSOLE" /D "XLIBC_NO_OPENSSL" /D "AGOBOT_NO_OPENSSL" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "__CLEANUP_SEH" /FAs /FR /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MDd /W3 /Gm /Gi /GX /ZI /Od /I "lib/stlport" /I "lib/pcre/win32" /I "lib/libpcap/include" /I "lib/xlibc/include" /D "_DEBUG" /D "DBGCONSOLE" /D "XLIBC_NO_OPENSSL" /D "AGOBOT_NO_OPENSSL" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "__CLEANUP_SEH" /FAs /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winspool.lib comdlg32.lib oleaut32.lib uuid.lib gdi32.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib dnsapi.lib pcre.lib /nologo /subsystem:windows /map /debug /machine:I386 /out:"bin/win32/agobot3_debug.exe" /pdbtype:sept /libpath:"lib/pcre" /libpath:"lib/libpcap/lib" /ignore:4033
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winspool.lib comdlg32.lib oleaut32.lib uuid.lib gdi32.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib dnsapi.lib pcre.lib odbc32.lib odbccp32.lib ole32.lib wpcap.lib packet.lib iphlpapi.lib npptools.lib version.lib /nologo /subsystem:windows /map /debug /machine:I386 /out:"bin/win32/agobot3_debug.exe" /pdbtype:sept /libpath:"lib/pcre/win32" /libpath:"lib/libpcap/lib" /ignore:4033
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "agobot3___Win32_Release_Console_Test"
# PROP BASE Intermediate_Dir "agobot3___Win32_Release_Console_Test"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "agobot3___Win32_Release_Console_Test"
# PROP Intermediate_Dir "agobot3___Win32_Release_Console_Test"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /Zp1 /MT /W3 /GX /Ow /Og /Os /Oy /Gf /Gy /I "lib/stlport" /I "lib/pcre" /I "lib/libpcap/include" /I "lib/xlibc/include" /D "NDEBUG" /D "DBGCONSOLE" /D "XLIBC_NO_OPENSSL" /D "AGOBOT_NO_OPENSSL" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "__CLEANUP_SEH" /FR /YX /FD /c
# SUBTRACT BASE CPP /Ox
# ADD CPP /nologo /G6 /MD /W3 /Gi /GX /ZI /Od /Oy /I "lib/stlport" /I "lib/pcre/win32" /I "lib/libpcap/include" /I "lib/xlibc/include" /D "NDEBUG" /D "DBGCONSOLE" /D "XLIBC_NO_OPENSSL" /D "AGOBOT_NO_OPENSSL" /D "WIN32" /D "_WINDOWS" /D "FORCE_UNICODE" /D "__CLEANUP_SEH" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib gdi32.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib dnsapi.lib pcre.lib /nologo /subsystem:windows /pdb:none /machine:I386 /out:"bin/win32/agobot3_console_nossl.exe" /libpath:"lib/pcre" /libpath:"lib/libpcap/lib" /ignore:4033
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 gdi32.lib kernel32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib netapi32.lib mpr.lib psapi.lib dnsapi.lib pcre.lib odbc32.lib odbccp32.lib ole32.lib wpcap.lib packet.lib iphlpapi.lib npptools.lib version.lib /nologo /subsystem:windows /pdb:none /map /debug /machine:I386 /out:"bin/win32/agobot3_console_nossl.exe" /libpath:"lib/pcre/win32" /libpath:"lib/libpcap/lib" /ignore:4033
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "agobot3 - Win32 Release"
# Name "agobot3 - Win32 Debug"
# Name "agobot3 - Win32 Release Console"
# Name "agobot3 - Win32 Release No OpenSSL"
# Name "agobot3 - Win32 Release Console No OpenSSL"
# Name "agobot3 - Win32 Debug No OpenSSL"
# Name "agobot3 - Win32 Debug Internal"
# Name "agobot3 - Win32 Debug No OpenSSL Internal"
# Name "agobot3 - Win32 Release Console Test"
# Begin Group "source files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "main"

# PROP Default_Filter ""
# Begin Group "Protocol Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\irc.cpp
# End Source File
# Begin Source File

SOURCE=.\smtp.cpp

!IF  "$(CFG)" == "agobot3 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\smtp_logic.cpp

!IF  "$(CFG)" == "agobot3 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\telnet.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\bnc.cpp
# End Source File
# Begin Source File

SOURCE=.\bot.cpp
# End Source File
# Begin Source File

SOURCE=.\cmdline.cpp
# End Source File
# Begin Source File

SOURCE=.\cmdshell.cpp
# End Source File
# Begin Source File

SOURCE=.\commands.cpp
# End Source File
# Begin Source File

SOURCE=.\config.cpp
# End Source File
# Begin Source File

SOURCE=.\cplugin.cpp
# End Source File
# Begin Source File

SOURCE=.\crypter.cpp
# End Source File
# Begin Source File

SOURCE=.\cvar.cpp
# End Source File
# Begin Source File

SOURCE=.\installer.cpp
# End Source File
# Begin Source File

SOURCE=.\logic.cpp
# End Source File
# Begin Source File

SOURCE=.\mac.cpp
# End Source File
# Begin Source File

SOURCE=.\mainctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\message.cpp
# End Source File
# Begin Source File

SOURCE=.\object.cpp
# End Source File
# Begin Source File

SOURCE=.\pcapbin.cpp
# End Source File
# Begin Source File

SOURCE=.\pcapclass.cpp
# End Source File
# Begin Source File

SOURCE=.\pcapclass.h
# End Source File
# Begin Source File

SOURCE=.\polymorph.cpp
# End Source File
# Begin Source File

SOURCE=.\sdcompat.cpp
# End Source File
# Begin Source File

SOURCE=.\sniffer.cpp
# End Source File
# Begin Source File

SOURCE=.\utilcmd.cpp
# End Source File
# Begin Source File

SOURCE=.\utility.cpp
# End Source File
# End Group
# Begin Group "scanner"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\baglescanner.cpp
# End Source File
# Begin Source File

SOURCE=.\dcom2scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\dcomscanner.cpp
# End Source File
# Begin Source File

SOURCE=.\doomscanner.cpp
# End Source File
# Begin Source File

SOURCE=.\dwscanner.cpp
# End Source File
# Begin Source File

SOURCE=.\httpscanner.cpp
# End Source File
# Begin Source File

SOURCE=.\locscanner.cpp
# End Source File
# Begin Source File

SOURCE=.\lsassscanner.cpp
# End Source File
# Begin Source File

SOURCE=.\nbscanner.cpp
# End Source File
# Begin Source File

SOURCE=.\optixscanner.cpp
# End Source File
# Begin Source File

SOURCE=.\pwds.cpp
# End Source File
# Begin Source File

SOURCE=.\scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlscanner.cpp
# End Source File
# Begin Source File

SOURCE=.\upnpscanner.cpp
# End Source File
# Begin Source File

SOURCE=.\wksscanner.cpp
# End Source File
# Begin Source File

SOURCE=.\wormride.cpp
# End Source File
# End Group
# Begin Group "ddos"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ddos.cpp
# End Source File
# Begin Source File

SOURCE=.\httpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\phaticmp.cpp
# End Source File
# Begin Source File

SOURCE=.\phatsyn.cpp
# End Source File
# Begin Source File

SOURCE=.\synflood.cpp
# End Source File
# Begin Source File

SOURCE=.\targa3.cpp
# End Source File
# Begin Source File

SOURCE=.\udpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\wonk.cpp
# End Source File
# End Group
# Begin Group "shellcode source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shellcode.cpp
# End Source File
# End Group
# Begin Group "redirect"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\redir_gre.cpp
# End Source File
# Begin Source File

SOURCE=.\redir_http.cpp
# End Source File
# Begin Source File

SOURCE=.\redir_https.cpp
# End Source File
# Begin Source File

SOURCE=.\redir_socks.cpp
# End Source File
# Begin Source File

SOURCE=.\redir_socks5.cpp
# End Source File
# Begin Source File

SOURCE=.\redir_tcp.cpp
# End Source File
# Begin Source File

SOURCE=.\redirect.cpp
# End Source File
# End Group
# Begin Group "3rd Party Source"

# PROP Default_Filter ""
# Begin Group "FTPLib Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ftplib\ftplib.cpp
# End Source File
# End Group
# Begin Group "MD5 Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\md5\md5c.cpp
# End Source File
# End Group
# End Group
# Begin Group "harvest"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\harvest_aol.cpp
# End Source File
# Begin Source File

SOURCE=.\harvest_cdkeys.cpp
# End Source File
# Begin Source File

SOURCE=.\harvest_emails.cpp
# End Source File
# Begin Source File

SOURCE=.\harvest_registry.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\config.def

!IF  "$(CFG)" == "agobot3 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Agobot3 Header"

# PROP Default_Filter ""
# Begin Group "Protocol Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\irc.h
# End Source File
# Begin Source File

SOURCE=.\smtp.h

!IF  "$(CFG)" == "agobot3 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\smtp_logic.h

!IF  "$(CFG)" == "agobot3 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\telnet.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\bnc.h
# End Source File
# Begin Source File

SOURCE=.\bot.h
# End Source File
# Begin Source File

SOURCE=.\bothooks.h
# End Source File
# Begin Source File

SOURCE=.\cmdbase.h
# End Source File
# Begin Source File

SOURCE=.\cmdline.h
# End Source File
# Begin Source File

SOURCE=.\cmdopt.h
# End Source File
# Begin Source File

SOURCE=.\cmdshell.h
# End Source File
# Begin Source File

SOURCE=.\commands.h
# End Source File
# Begin Source File

SOURCE=.\confbase.h
# End Source File
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\cplugin.h
# End Source File
# Begin Source File

SOURCE=.\crypter.h
# End Source File
# Begin Source File

SOURCE=.\cvar.h
# End Source File
# Begin Source File

SOURCE=.\installer.h
# End Source File
# Begin Source File

SOURCE=.\logic.h
# End Source File
# Begin Source File

SOURCE=.\mac.h
# End Source File
# Begin Source File

SOURCE=.\main.h
# End Source File
# Begin Source File

SOURCE=.\mainctrl.h
# End Source File
# Begin Source File

SOURCE=.\message.h
# End Source File
# Begin Source File

SOURCE=.\modules.h
# End Source File
# Begin Source File

SOURCE=.\object.h
# End Source File
# Begin Source File

SOURCE=.\pcapbin.h
# End Source File
# Begin Source File

SOURCE=.\polymorph.h
# End Source File
# Begin Source File

SOURCE=.\sdcompat.h
# End Source File
# Begin Source File

SOURCE=.\sniffer.h
# End Source File
# Begin Source File

SOURCE=.\utilcmd.h
# End Source File
# Begin Source File

SOURCE=.\utility.h
# End Source File
# End Group
# Begin Group "Scanner Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\pwds.h
# End Source File
# Begin Source File

SOURCE=.\scanner.h
# End Source File
# Begin Source File

SOURCE=.\wormride.h
# End Source File
# End Group
# Begin Group "DDOS Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ddos.h
# End Source File
# End Group
# Begin Group "Shellcode Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shellcode.h
# End Source File
# End Group
# Begin Group "Redirect Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\redir_gre.h
# End Source File
# Begin Source File

SOURCE=.\redir_http.h
# End Source File
# Begin Source File

SOURCE=.\redir_https.h
# End Source File
# Begin Source File

SOURCE=.\redir_socks.h
# End Source File
# Begin Source File

SOURCE=.\redir_socks5.h
# End Source File
# Begin Source File

SOURCE=.\redir_tcp.h
# End Source File
# Begin Source File

SOURCE=.\redirect.h
# End Source File
# End Group
# Begin Group "3rd Party Header"

# PROP Default_Filter ""
# Begin Group "FTPLib Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ftplib\ftplib.h
# End Source File
# End Group
# Begin Group "MD5 Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\md5\global.h
# End Source File
# Begin Source File

SOURCE=.\md5\md5.h
# End Source File
# End Group
# Begin Group "3DNow! Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3dnow.h
# End Source File
# End Group
# Begin Group "PCRE Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\pcre\pcre.h
# End Source File
# End Group
# End Group
# Begin Group "Harvest Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\harvest_aol.h
# End Source File
# Begin Source File

SOURCE=.\harvest_cdkeys.h
# End Source File
# Begin Source File

SOURCE=.\harvest_emails.h
# End Source File
# Begin Source File

SOURCE=.\harvest_registry.h
# End Source File
# End Group
# Begin Group "XLibC Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\xlibc\include\buffer.h
# End Source File
# Begin Source File

SOURCE=.\lib\xlibc\include\consdbg.h
# End Source File
# Begin Source File

SOURCE=.\lib\xlibc\include\cstring.h
# End Source File
# Begin Source File

SOURCE=.\lib\xlibc\include\cthread.h
# End Source File
# Begin Source File

SOURCE=.\lib\xlibc\include\random.h
# End Source File
# Begin Source File

SOURCE=.\lib\xlibc\include\rc4lib.h
# End Source File
# Begin Source File

SOURCE=.\lib\xlibc\include\sockets.h
# End Source File
# Begin Source File

SOURCE=.\lib\xlibc\include\xlibc.h
# End Source File
# End Group
# End Group
# Begin Group "Documents"

# PROP Default_Filter "txt"
# Begin Group "Licenses"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\apl.txt
# End Source File
# End Group
# Begin Group "CmdRef"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\doc\!New\Command Reference.htm"
# End Source File
# End Group
# Begin Group "FAQ"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\doc\!New\FAQ.htm"
# End Source File
# End Group
# Begin Group "CSS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\doc\!New\setting.css"
# End Source File
# End Group
# Begin Source File

SOURCE=.\changes.txt
# End Source File
# Begin Source File

SOURCE=.\disclaimer.txt
# End Source File
# Begin Source File

SOURCE=.\files.txt
# End Source File
# Begin Source File

SOURCE=.\doc\PCRE.txt
# End Source File
# Begin Source File

SOURCE=.\doc\rules.txt
# End Source File
# Begin Source File

SOURCE=.\todo.txt
# End Source File
# End Group
# Begin Group "Makefiles"

# PROP Default_Filter ""
# Begin Group "MD5"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\md5\Makefile.am
# End Source File
# End Group
# Begin Group "FTPLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ftplib\Makefile.am
# End Source File
# End Group
# Begin Source File

SOURCE=.\configure.ac
# End Source File
# Begin Source File

SOURCE=.\Makefile.am
# End Source File
# End Group
# Begin Group "Binaries"

# PROP Default_Filter ""
# Begin Group "PCap"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\libpcap\npf2k.sys
# End Source File
# Begin Source File

SOURCE=.\lib\libpcap\packet.dll
# End Source File
# Begin Source File

SOURCE=.\lib\libpcap\wpcap.dll
# End Source File
# End Group
# Begin Group "Stealth"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\asmstub.OBJ
# End Source File
# End Group
# Begin Group "XLibC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\xlibc\lib\xlibc_release_nossl.lib

!IF  "$(CFG)" == "agobot3 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\lib\xlibc\lib\xlibc_debug.lib

!IF  "$(CFG)" == "agobot3 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\lib\xlibc\lib\xlibc_debug_nossl.lib

!IF  "$(CFG)" == "agobot3 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\lib\xlibc\lib\xlibc_release.lib

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\lib\xlibc\lib\xlibc_release_console.lib

!IF  "$(CFG)" == "agobot3 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\lib\xlibc\lib\xlibc_release_console_nossl.lib

!IF  "$(CFG)" == "agobot3 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# End Group
# End Group
# Begin Group "ASM Files"

# PROP Default_Filter ""
# Begin Group "Encoder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\asmsrc\encoder\agoenc.asm

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asmsrc\encoder\rolloop.asm

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asmsrc\encoder\rorloop.asm

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asmsrc\encoder\swaploop.asm

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asmsrc\encoder\xorloop.asm

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asmsrc\encoder\xorloop2.asm

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asmsrc\encoder\xorloop3.asm

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# End Group
# Begin Group "AVKill"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\asmsrc\avkill\avkill.asm

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# End Group
# Begin Group "Shellcode"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\asmsrc\shellcode\agoshell.asm

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asmsrc\shellcode\encoder.asm

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# End Group
# Begin Group "Shellcode UDTF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\asmsrc\shellcode_udtf\agoshell.asm

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asmsrc\shellcode_udtf\encoder.asm

!IF  "$(CFG)" == "agobot3 - Win32 Release"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console No OpenSSL"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Debug No OpenSSL Internal"

!ELSEIF  "$(CFG)" == "agobot3 - Win32 Release Console Test"

!ENDIF 

# End Source File
# End Group
# End Group
# End Target
# End Project
