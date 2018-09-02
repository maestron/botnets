#ifndef __HYDRA_HDS_H_
#define __HYDRA_HDS_H_

/* glibc headers */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdarg.h>
#include <wait.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/ip.h>
#include <linux/tcp.h>

/* hydra headers */
#include "hydra_main.h"
#include "hydra_conf.h"
#include "hydra_utils.h"
#include "hydra_irc.h"
#include "hydra_mesg.h"
#include "hydra_reqs.h"
#include "hydra_scan.h"
#include "hydra_synf.h"

/* redefinition */
#undef EXIT_FAILURE
#define EXIT_FAILURE -1

#endif
