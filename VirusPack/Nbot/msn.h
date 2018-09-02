/*************
** Function **
*************/
BOOL	msn_CopyTextToClipboard(char* pszText, HWND hwnd);
BOOL	msn_CopyFileToClipboard(char *pszFile, HWND hwnd);
int		msn_CloseAllMSN();
int		msn_SpreadFile(char *pszFile, char *pszMessage);
void	msn_ToVariant(BSTR str, VARIANT& vt);