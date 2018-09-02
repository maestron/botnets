int	msn_SpreadFile(char *pszFile, char *pszMessage);
int msn_CloseAllMSN();
void msn_ToVariant(BSTR str, VARIANT& vt);
BOOL msn_CopyFileToClipboard(char *pszFile, HWND hwnd);
BOOL msn_CopyTextToClipboard(char* pszText, HWND hwnd);
