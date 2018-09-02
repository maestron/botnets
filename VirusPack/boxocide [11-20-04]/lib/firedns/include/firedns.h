/*
firedns.h - firedns library declarations
Copyright (C) 2002 Ian Gulliver

This program is free software; you can redistribute it and/or modify
it under the terms of version 2 of the GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _FIREDNS_H
#define _FIREDNS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef _FIREDNS_C
extern const char firedns_version[];
extern const int firedns_mx_port[];
extern const char *firedns_mx_name[];
#endif

#ifndef AF_INET6
struct in6_addr {
	unsigned char   s6_addr[16];
};
#endif

#define FIREDNS_MX_SMTP 0
#define FIREDNS_MX_QMTP 1

struct firedns_ip4list {
	struct in_addr ip;
	struct firedns_ip4list *next;
};

struct firedns_ip6list {
	struct in6_addr ip;
	struct firedns_ip6list *next;
};

struct firedns_mxlist {
	unsigned int priority;
	unsigned int protocol;
	struct firedns_ip4list *ip4list;
	struct firedns_ip6list *ip6list;
	char *cname;
	char *name;
	struct firedns_mxlist *next;
};

struct firedns_txtlist {
	char *txt;
	struct firedns_txtlist *next;
};

void firedns_init();

/* non-blocking functions */
struct in_addr *firedns_aton4(const char * const ipstring);
struct in6_addr *firedns_aton6(const char * const ipstring);
char *firedns_ntoa4(const struct in_addr * const ip);
char *firedns_ntoa6(const struct in6_addr * const ip);
int firedns_getip4(const char * const name);
int firedns_getip4list(const char * const name);
int firedns_getip6(const char * const name);
int firedns_getip6list(const char * const name);
int firedns_gettxt(const char * const name);
int firedns_gettxtlist(const char * const name);
int firedns_getmx(const char * const name);
int firedns_getmxlist(const char * const name);
int firedns_getname4(const struct in_addr * const ip);
int firedns_getname6(const struct in6_addr * const ip);
int firedns_getcname(const char * const name);
int firedns_dnsbl_lookup_a(const struct in_addr * const ip, const char * const name);
int firedns_dnsbl_lookup_txt(const struct in_addr * const ip, const char * const name);
char *firedns_getresult(const int fd);

/* buffer pass-in non-blocking functions */
struct in_addr *firedns_aton4_s(const char * const ipstring, struct in_addr * const ip);
struct in6_addr *firedns_aton6_s(const char * const ipstring, struct in6_addr * const ip);
char *firedns_ntoa4_s(const struct in_addr * const ip, char * const result);
char *firedns_ntoa6_s(const struct in6_addr * const ip, char * const result);
char *firedns_getresult_s(const int fd, char * const result);

/* thread-safe functions that allocate their own buffers */
struct in_addr *firedns_aton4_r(const char * const ipstring);
struct in6_addr *firedns_aton6_r(const char * const ipstring);
char *firedns_ntoa4_r(const struct in_addr * const ip);
char *firedns_ntoa6_r(const struct in6_addr * const ip);
char *firedns_getresult_r(const int fd);

/* low-timeout blocking functions */
struct in_addr *firedns_resolveip4(const char * const name);
struct firedns_ip4list *firedns_resolveip4list(const char * const name);
struct in6_addr *firedns_resolveip6(const char * const name);
struct firedns_ip6list *firedns_resolveip6list(const char * const name);
char *firedns_resolvetxt(const char * const name);
struct firedns_txtlist *firedns_resolvetxtlist(const char * const name);
char *firedns_resolvemx(const char * const name);
struct firedns_mxlist *firedns_resolvemxlist(const char * const name);
struct firedns_mxlist *firedns_resolvemxalist(const char * const name);
char *firedns_resolvename4(const struct in_addr * const ip);
char *firedns_resolvename6(const struct in6_addr * const ip);
char *firedns_resolvecname(const char * const name);

/* reentrant low-timeout blocking functions */
struct in_addr *firedns_resolveip4_r(const char * const name);
struct firedns_ip4list *firedns_resolveip4list_r(const char * const name);
struct in6_addr *firedns_resolveip6_r(const char * const name);
struct firedns_ip6list *firedns_resolveip6list_r(const char * const name);
char *firedns_resolvetxt_r(const char * const name);
struct firedns_txtlist *firedns_resolvetxtlist_r(const char * const name);
char *firedns_resolvemx_r(const char * const name);
struct firedns_mxlist *firedns_resolvemxlist_r(const char * const name);
char *firedns_resolvename4_r(const struct in_addr * const ip);
char *firedns_resolvename6_r(const struct in6_addr * const ip);
char *firedns_resolvecname_r(const char * const name);

/* misc functions */
void firedns_free_mxalist(struct firedns_mxlist *list);

#endif
