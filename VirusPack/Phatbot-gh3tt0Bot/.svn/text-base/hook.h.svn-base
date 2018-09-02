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

#ifndef __HOOK_H__
#define __HOOK_H__

#ifdef WIN32

typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation = 0,
    SystemPerformanceInformation = 2,
    SystemTimeOfDayInformation = 3,
    SystemProcessInformation = 5,
    SystemProcessorPerformanceInformation = 8,
    SystemInterruptInformation = 23,
    SystemExceptionInformation = 33,
    SystemRegistryQuotaInformation = 37,
    SystemLookasideInformation = 45
} SYSTEM_INFORMATION_CLASS;

typedef NTSTATUS (*NtQuerySystemInfoFunc)(SYSTEM_INFORMATION_CLASS SystemInformationClass, \
										  void *pSystemInformation, \
										  unsigned long lSystemInformationLength, \
										  unsigned long *lReturnLength);

class CHook : public CThread {
public:
			 CHook();
	virtual	~CHook();
	void	*Run();
	void	 Hook(HANDLE hProcess);
private:
	HMODULE  m_hDLL;
};

#else

// FIXME: Implement for linux
class CHook;

#endif // WIN32

#endif // __HOOK_H__
