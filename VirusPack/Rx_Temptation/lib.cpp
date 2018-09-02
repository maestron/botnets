#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_EMAIL

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

char *strrchr(const char *str, char ch)
{
	register char *start = (char *)str;
	while (*str++);
	while (--str != start && *str != ch);
	if (*str == (char)ch) return((char *)str);
	return NULL;
}

char *strchr(const char *str, char ch)
{
	while (*str && *str != ch) str++;
	return (*str == ch) ? (char *)str : NULL;
}

int memcmpi(unsigned char *p, unsigned char *q, int len)
{
	while (len--)
		if (tolower(*p++) != tolower(*q++)) return 1;
	return 0;
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

int cat_wsprintf(LPTSTR lpOutput, LPCTSTR lpFormat, ...)
{
	register int ret;
	va_list arglist;
	va_start(arglist, lpFormat);
	ret = wvsprintf(lpOutput + lstrlen(lpOutput), lpFormat, arglist);
	va_end(arglist);
	return ret;
}
#endif