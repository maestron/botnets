#ifndef __HYDRA_SYNF_H_
#define __HYDRA_SYNF_H_

/* variables. */
unsigned int srchost;
unsigned int dsthost;
unsigned short uport;
unsigned int useconds;

/* some headers. */
struct send_tcp
{
  struct iphdr ip;
  struct tcphdr tcp;
} send_tcp;

struct pseudo_header
{
  unsigned int source_address;
  unsigned int dest_address;
  unsigned char placeholder;
  unsigned char protocol;
  unsigned short tcp_length;
  struct tcphdr tcp;
} pseudo_header;

#endif
