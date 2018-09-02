# Wedit Makefile for project sd
SRCDIR=c:\windows\desktop\coding\sd
CFLAGS=-Ic:\lcc\include  -O 
CC=$(LCCROOT)\bin\lcc.exe
LINKER=$(LCCROOT)\bin\lcclnk.exe
OBJS=\
	sdbot05b.obj \
	poobot.res

LIBS=shell32.lib wininet.lib wsock32.lib
EXE=autoupdate.exe

$(EXE):	$(OBJS) Makefile
	$(LINKER)  -s -subsystem windows -o $(SRCDIR)\lcc\autoupdate.exe $(OBJS) $(LIBS)

# Build sdbot05b.c
SDBOT05B_C=\

sdbot05b.obj: $(SDBOT05B_C) $(SRCDIR)\sdbot05b.c
	$(CC) -c $(CFLAGS) $(SRCDIR)\sdbot05b.c

# Build poobot.res
POOBOT_RC=\

poobot.res:	$(POOBOT_RC) $(SRCDIR)\poobot.rc
	$(LCCROOT)\bin\lrc.exe -I$(SRCDIR) -Ic:\lcc\include  $(SRCDIR)\poobot.rc

link:
	$(LINKER)  -s -subsystem windows -o $(SRCDIR)\lcc\autoupdate.exe $(OBJS) $(LIBS)

clean:
	del $(OBJS) c:\windows\desktop\coding\sd\lcc\autoupdate.exe
