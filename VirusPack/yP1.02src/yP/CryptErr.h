/* CryptErr.h --

   This file is part of the "yoda's Protector".

   Copyright (C) 2004-2005 Ashkbiz Danehkar
   Copyright (C) 2000-2001 yoda/FReAK2FReAK
   All Rights Reserved.

   yoda's Protector library are free software; you can redistribute them
   and/or modify them under the terms of the GNU General Public License as
   published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYRIGHT.TXT.
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Ashkbiz Danehkar
   <ashkbiz@yahoo.com>
*/
#pragma once

//------- ERROR --------
#define MemErr					1
#define PEErr					2
#define FileErr					3
#define NoRoom4SectionErr		4
#define FsizeErr				5
#define SecNumErr				6
#define IIDErr					7
#define FileISProtect			8
#define PEnotValid				9
#define PEisCOMRuntime			10
#define DLLnotSupport			11
#define WDMnotSupport			12
#define TServernotSupport		13
#define SYSnotSupport			14
#define NOSEHnotSupport			15
#define NOBINDnotSupport		16
#define PackSectionName			17

void ShowErr(unsigned char numErr);