#ifndef __MESSAGE_H__
#define __MESSAGE_H__

class CMessage
{
public:
	CString	sChatString;
	CString	sSrc;
	CString	sDest;
	CString	sHost;
	CString	sIdentd;

	CString	sReplyTo;
	CString	sCmd;

	bool	bSilent;
	bool	bNotice;
	bool	bOutchan;
};

#endif // __MESSAGE_H__
