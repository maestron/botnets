#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <windns.h>
#include <iphlpapi.h>
#include "xdns.h"
#pragma comment(lib, "ws2_32.lib")

#define mx_alloc(n) ((void*)HeapAlloc(GetProcessHeap(),0,(n)))
#define mx_free(p) {HeapFree(GetProcessHeap(),0,(p));}

#define TYPE_MX 15
#define CLASS_IN 1

#pragma pack(push, 1)
struct dnsreq_t {
	WORD id;
	WORD flags;
	WORD qncount;
	WORD ancount;
	WORD nscount;
	WORD arcount;
};
#pragma pack(pop)

struct mx_rrlist_t {
	struct mx_rrlist_t *next;
	char domain[260];
	WORD rr_type;
	WORD rr_class;
	WORD rdlen;
	int rdata_offs;
};

static int mx_dns2qname(const char *domain, unsigned char *buf)
{
	int i, p, t;
	for (i=0,p=0;;) {
		if (domain[i] == 0) break;
		for (t=i; domain[t] && (domain[t] != '.'); t++);
		buf[p++] = (t - i);
		while (i < t) buf[p++] = domain[i++];
		if (domain[i] == '.') i++;
	}
	buf[p++] = '\0';
	return p;
}

static int mx_make_query(int sock, struct sockaddr_in *dns_addr, const char *domain, WORD req_flags)
{
	unsigned char buf[1024];
	int i, tmp;

	memset(buf, 0, sizeof(buf));
	i = 0;
	*(WORD *)(buf+i) = (WORD)(GetTickCount() & 0xFFFF); i += 2;
	*(WORD *)(buf+i) = req_flags; i += 2;		/* flags */
	*(WORD *)(buf+i) = htons(0x0001); i += 2;	/* qncount */
	*(WORD *)(buf+i) = 0; i += 2;
	*(WORD *)(buf+i) = 0; i += 2;
	*(WORD *)(buf+i) = 0; i += 2;

	tmp = mx_dns2qname(domain, buf+i); i += tmp;
	*(WORD *)(buf+i) = htons(TYPE_MX); i += 2;
	*(WORD *)(buf+i) = htons(CLASS_IN); i += 2;

	tmp = sendto(sock, buf, i, 0, (struct sockaddr *)dns_addr, sizeof(struct sockaddr_in));
	return (tmp <= 0) ? 1 : 0;
}

static int mx_skipqn(unsigned char *buf, int pos, int len, struct dnsreq_t *reply_hdr)
{
	int i, n;
	for (i=0; (i<ntohs(reply_hdr->qncount)) && (pos < len);) {
		n = buf[pos];
		if (n == 0) {
			pos += 5;
			i++;
		} else if (n < 64) {
			pos += 1+n;
		} else {
			pos += 6;
			i++;
		}
	}
	return pos;
}

static int mx_decode_domain(unsigned char *buf, int pos, int len, char *out)
{
	int retpos=0, sw, n, j, out_pos;
	*out = 0;

	for (sw=0, out_pos=0; pos < len;) {
		if (out_pos >= 255)
			break;
		n = (unsigned char)buf[pos];
		if (n == 0) {
			pos++;
			break;
		} else if (n < 64) {
			pos++;
			for (j=0; j<n; j++)
				out[out_pos++] = buf[pos++];
			out[out_pos++] = '.';
		} else {
			if (sw == 0) retpos=pos+2;
			sw = 1;
			n = ntohs(*(WORD *)(buf+pos)) & 0x3FFF;
			pos = n;
			if (pos >= len) break;
		}
	}

	while (out_pos > 0)
		if (out[out_pos-1] != '.') break; else out_pos--;
	out[out_pos] = 0;

	return (sw == 0) ? pos : retpos;
}

static void mx_free_rrlist(struct mx_rrlist_t *p)
{
	struct mx_rrlist_t *q;
	while (p != NULL) {
		q = p->next;
		mx_free(p);
		p = q;
	}
}

static struct mx_rrlist_t *mx_parse_rr(unsigned char *buf, int reply_len)
{
	struct mx_rrlist_t *root, *top, *newrr, tmp_rr;
	struct dnsreq_t *reply_hdr;
	int i, j, rr, rr_count;

	root = top = NULL;
	reply_hdr = (struct dnsreq_t *)buf;

	if (reply_len < 12) return NULL;
	i = 12;
	i = mx_skipqn(buf, i, reply_len, reply_hdr);

	if (i >= reply_len)
		return NULL;

	rr_count = reply_hdr->ancount + reply_hdr->nscount + reply_hdr->arcount;
	for (rr=0,newrr=NULL; (rr < rr_count) && (i < reply_len); rr++) {
		memset(&tmp_rr, '\0', sizeof(struct mx_rrlist_t));
		i = mx_decode_domain(buf, i, reply_len, tmp_rr.domain);
		if ((i+10) >= reply_len) break;
		tmp_rr.rr_type = ntohs(*(WORD*)(buf+i)); i += 2;
		tmp_rr.rr_class = ntohs(*(WORD*)(buf+i)); i += 2;
		i += 4;		/* 32-bit TTL */
		tmp_rr.rdlen = ntohs(*(WORD*)(buf+i)); i += 2;
		tmp_rr.rdata_offs = i;
		if ((tmp_rr.rdlen < 0) || ((i+tmp_rr.rdlen) > reply_len)) break;

		j = sizeof(struct mx_rrlist_t) + 16;
		newrr = (struct mx_rrlist_t *)mx_alloc(j);
		if (newrr == NULL) break;
		memset((char *)newrr, '\0', j);
		*newrr = tmp_rr;
		i += tmp_rr.rdlen;

		newrr->next = NULL;
		if (top == NULL) {
			root = top = newrr;
		} else {
			top->next = newrr;
			top = newrr;
		}
	}
	return root;
}

static struct mxlist_t *my_get_mx_list2(struct sockaddr_in *dns_addr, const char *domain, int *err_stat)
{
	int sock, reply_len, rrcode, buf_size;
	int loc_retry;
	struct timeval tv;
	struct fd_set fds;
	unsigned char *buf;
	unsigned short query_fl;
	struct dnsreq_t *reply_hdr;
	struct mx_rrlist_t *rrlist=NULL, *rr1;
	struct mxlist_t *mxlist_root, *mxlist_top, *mxlist_new;

	*err_stat = 1;

	buf_size = 4096;
	buf = (char *)mx_alloc(buf_size);
	if (buf == NULL) return NULL;

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == 0 || sock == INVALID_SOCKET) {
		mx_free(buf);
		return NULL;
	}

	for (loc_retry=0; loc_retry<2; loc_retry++) {
		mxlist_root = mxlist_top = NULL;

		if (loc_retry == 0)
			query_fl = htons(0x0100);
		else
			query_fl = htons(0);

		if (mx_make_query(sock, dns_addr, domain, query_fl))
			continue;

		FD_ZERO(&fds); FD_SET(sock, &fds);
		tv.tv_sec = 12; tv.tv_usec = 0;
		if (select(0, &fds, NULL, NULL, &tv) <= 0)
			continue;

		memset(buf, '\0', sizeof(buf));
		reply_len = recv(sock, buf, buf_size,0);
		if (reply_len <= 0 || reply_len <= sizeof(struct dnsreq_t))
			continue;

		reply_hdr = (struct dnsreq_t *)buf;

		rrcode = ntohs(reply_hdr->flags) & 0x0F;
		if (rrcode == 3) {
			*err_stat = 2;
			break;
		}
		if ((rrcode == 2) && (ntohs(reply_hdr->flags) & 0x80)) {
			*err_stat = 2;
			break;
		}
		if (rrcode != 0)
			continue;

		rrlist = mx_parse_rr(buf, reply_len);
		if (rrlist == NULL)
			continue;

		mxlist_root = mxlist_top = NULL;
		for (rr1=rrlist; rr1; rr1=rr1->next) {
			if ((rr1->rr_class != CLASS_IN) || (rr1->rr_type != TYPE_MX) || (rr1->rdlen < 3))
				continue;
			mxlist_new = (struct mxlist_t *)mx_alloc(sizeof(struct mxlist_t));
			if (mxlist_new == NULL) break;
			memset(mxlist_new, 0, sizeof(struct mxlist_t));

			mxlist_new->pref = ntohs(*(WORD *)(buf+rr1->rdata_offs+0));
			mx_decode_domain(buf, rr1->rdata_offs+2, reply_len, mxlist_new->mx);
			if (mxlist_new->mx[0] == 0) {
				mx_free(mxlist_new);
				continue;
			}

			if (mxlist_top == NULL) {
				mxlist_root = mxlist_top = mxlist_new;
			} else {
				mxlist_top->next = mxlist_new;
				mxlist_top = mxlist_new;
			}
		}

		if (mxlist_root == NULL) {
			mx_free_rrlist(rrlist);
			continue;
		}

		mx_free_rrlist(rrlist);
		break;
	}
	mx_free(buf);
	closesocket(sock);
	return mxlist_root;
}

struct mxlist_t *my_get_mx_list(struct sockaddr_in *dns_addr, const char *domain)
{
	struct mxlist_t *list;
	int i, e;
	for (i=0; i<2; i++) {
		list = my_get_mx_list2(dns_addr, domain, &e);
		if (list != NULL) return list;
		if (e == 2)		/* permanent error */
			break;
		Sleep(100);
	}
	return NULL;
}

//-----------------------------------------------------------------------------

typedef DNS_STATUS (WINAPI *DNSQUERYA)(IN PCSTR pszName, IN WORD wType, IN DWORD Options, IN PIP4_ARRAY aipServers OPTIONAL, IN OUT PDNS_RECORD *ppQueryResults OPTIONAL, IN OUT PVOID *pReserved OPTIONAL);

static struct mxlist_t *getmx_dnsapi(const char *domain)
{
	HINSTANCE hDnsapi;
	DNSQUERYA pDnsQuery_A;
	DNS_RECORD *pQueryResults, *pQueryRec;
	DNS_STATUS statusDns;
	char szDnsApi[] = "dnsapi.dll";
	struct mxlist_t *mx_root, *mx_top, *mx_new;

	hDnsapi = GetModuleHandle(szDnsApi);
	if (hDnsapi == NULL) {
		hDnsapi = LoadLibrary(szDnsApi);
		if (hDnsapi == NULL) return NULL;
	}
	pDnsQuery_A = (DNSQUERYA)GetProcAddress(hDnsapi, "DnsQuery_A");
	if (pDnsQuery_A == NULL) return NULL;

	statusDns = pDnsQuery_A(domain, DNS_TYPE_MX, DNS_QUERY_STANDARD, NULL, &pQueryResults, NULL);
	if (statusDns != ERROR_SUCCESS) return NULL;

	mx_root = mx_top = NULL;
	for (pQueryRec=pQueryResults; pQueryRec; pQueryRec = pQueryRec->pNext) {
		if (pQueryRec->wType != DNS_TYPE_MX) continue;
		mx_new = (struct mxlist_t *)mx_alloc(sizeof(struct mxlist_t));
		if (mx_new == NULL) break;
		memset(mx_new, '\0', sizeof(struct mxlist_t));
		mx_new->pref = pQueryRec->Data.MX.wPreference;
		lstrcpyn(mx_new->mx, pQueryRec->Data.MX.pNameExchange, 255);
		if (mx_top == NULL) {
			mx_root = mx_top = mx_new;
		} else {
			mx_top->next = mx_new;
			mx_top = mx_new;
		}
	}
	return mx_root;
}

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *GetNetworkParams_t)(PFIXED_INFO, PULONG);

static struct mxlist_t *getmx_mydns(const char *domain)
{
	static const char szIphlpapiDll[] = "iphlpapi.dll";
	HINSTANCE hIphlpapi;
	GetNetworkParams_t pGetNetworkParams;
	char *info_buf;
	FIXED_INFO *info;
	IP_ADDR_STRING *pa;
	DWORD dw, info_buf_size;
	struct sockaddr_in addr;
	struct mxlist_t *mxlist;

	hIphlpapi = GetModuleHandle(szIphlpapiDll);
	if (hIphlpapi == NULL || hIphlpapi == INVALID_HANDLE_VALUE)
		hIphlpapi = LoadLibrary(szIphlpapiDll);
	if (hIphlpapi == NULL || hIphlpapi == INVALID_HANDLE_VALUE) return NULL;
	pGetNetworkParams = (GetNetworkParams_t)GetProcAddress(hIphlpapi, "GetNetworkParams");
	if (pGetNetworkParams == NULL) return NULL;

	info_buf_size = 16384;
	info_buf = (char *)mx_alloc(info_buf_size);
	dw = info_buf_size;
	info = (FIXED_INFO *)info_buf;
	if (pGetNetworkParams(info, &dw) != ERROR_SUCCESS)
		return NULL;

	for (mxlist=NULL,pa=&info->DnsServerList; pa; pa=pa->Next) {
		if (pa->IpAddress.String == NULL) continue;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(53);
		addr.sin_addr.s_addr = inet_addr(pa->IpAddress.String);
		if (addr.sin_addr.s_addr == 0 || addr.sin_addr.s_addr == 0xFFFFFFFF) {
			struct hostent *h = gethostbyname(pa->IpAddress.String);
			if (h == NULL) continue;
			addr.sin_addr = *(struct in_addr *)h->h_addr_list[0];
		}
		if (addr.sin_addr.s_addr == 0 || addr.sin_addr.s_addr == 0xFFFFFFFF)
			continue;

		mxlist = my_get_mx_list(&addr, domain);
		if (mxlist != NULL) break;
	}
	mx_free(info_buf);
	return mxlist;
}

//-----------------------------------------------------------------------------

struct mxlist_t *get_mx_list(const char *domain)
{
	struct mxlist_t *p;
	if ((p = getmx_dnsapi(domain)) != NULL)
		return p;
	else
		return getmx_mydns(domain);
}

void free_mx_list(struct mxlist_t *p)
{
	struct mxlist_t *q;
	while (p != NULL) {
		q = p->next;
		mx_free(p);
		p = q;
	}
}
