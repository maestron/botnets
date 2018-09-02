#######################################################
# pBot v2
# a PHP IRC drone for use with RFI exploits
# by skorikov 
#######################################################

-------------------------------------------------------
# WHAT DOES IT DO                                     #
-------------------------------------------------------
This bot connects to an IRC server of your choice
and provides a shell-like interface allowing you to 
do such things as download, read, delete and execute 
files and gather information about the server


-------------------------------------------------------
# DISCLAIMER                                          #
-------------------------------------------------------
This application is provided for educational 
and penetration testing purposes only. I take no
responsibility for any damage you cause to your own 
machine or anyone elses as a result of using this code.

So please, don't fuck yourself over by leaving it
sitting on a server that doesn't belong to you.

-------------------------------------------------------
# LICENSE                                             #
-------------------------------------------------------
Modify, Redistribute, Rename, Rewrite, Bake a cake.


-------------------------------------------------------
# SUPPORT                                             #
-------------------------------------------------------
If you find a bug, please let me know. However, if 
you are looking for me to make special modifications
for you, you are on your own unless you want to pay me.


-------------------------------------------------------
# COMMAND REFERENCE                                   #
-------------------------------------------------------

NOTE: bot will recieve commands via PRIVMSG and TOPIC

login <password>
logout
die: make the bot disconnect and exit
raw <cmd>: send a raw IRC command
ls [path]: list contents of directory
cat <file>: read the contents of a file
pwd: print working directory
cd <path>: change working directory
rm <path>: remove file
touch <path>: touch a file
symlink <to path> <from path>: symlink a file
chown <path> <user>: change owner of a file
chmod <path> <permissions>: change permissions of a file
mkdir <path>: create a directory
rmdir <path>: remove directory
cp <from path> <to path>: copy a file
mail <rcpt to> <mail from> <subject> <message>: send an email
md5 <string>: print MD5 hash
dns <hostname/IP>: resolve a hostname or IP address
opme: make the bot give you +o
restart: restart the bot
rndnick [maxrand]: generate a new random nick
php <code>: execute some PHP code
dl <URL> <path>: download a file
srvinfo: display server information
portopen <host> <port>: check to see if a port on a host is open
uname: print server uname
cmd <command>: execute a shell command
execute <command/path>: execute a command or file


:) enjoy.