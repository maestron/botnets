/*  ya.bot  */

#include "bot.h"

#ifndef NO_DEBUG
void debug_print(char *pszOutput, ...)
{
	char szArguments[MASBUF], szBuffer[MASBUF], szDate[32], szTime[32];
	va_list va;
		GetDateFormat(LOCALE_USER_DEFAULT, 0, NULL, string_debugdate, szDate, sizeof(szDate));
		GetTimeFormat(LOCALE_USER_DEFAULT,
				TIME_FORCE24HOURFORMAT,
				NULL,
				string_debugtime,
				szTime,
				sizeof(szTime));
		_snprintf(szBuffer, sizeof(szBuffer) - 1, string_debugprint, szDate, szTime);
		va_start(va, pszOutput);
		_vsnprintf(szArguments, sizeof(szArguments) - 1, pszOutput, va);
		va_end(va);
		strncat(szBuffer, szArguments, (sizeof(szBuffer) - strlen(szBuffer)) - 1);
		strncat(szBuffer, "\r\n", (sizeof(szBuffer) - strlen(szBuffer)) - 1);

#ifndef NO_DEBUGCONSOLE
		printf(szBuffer);
#endif
#ifndef NO_DEBUGDEBUGGER
		OutputDebugString(szBuffer);
#endif
#ifndef NO_DEBUGFILE
	FILE *f;
		f = fopen(debuglogfilename, string_debugfileappend);
	if (f)
			fprintf(f, szBuffer);
		fclose(f);
#endif

		return;
}
#endif