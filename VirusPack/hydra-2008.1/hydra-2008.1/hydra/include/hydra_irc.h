#ifndef __HYDRA_IRC_H_
#define __HYDRA_IRC_H_

#define static_rcv 32

/* socket/requests structures. */
typedef struct
{
  int s_fd;
  struct hostent *s_hs;
  struct sockaddr_in s_addr;
} sock_t;

typedef struct
{
  char rs_a[128];
  char rs_b[static_rcv]; 
  char rs_c[static_rcv];
  char rso_a[static_rcv];
  char rso_b[static_rcv];
  char rso_c[static_rcv];
  char rso_d[static_rcv];
  char rso_e[static_rcv];
} reqs_t;

/* variables & misc. */
pid_t pid;

int max_pids, pid_status;
unsigned int recv_bytes;

char *data_ptr;
char netbuf[sizebuf];

#endif
