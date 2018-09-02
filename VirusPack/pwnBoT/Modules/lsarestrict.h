#ifndef NO_LSARESTRICT
void InitLsaString(PLSA_UNICODE_STRING LsaString, LPWSTR String);
NTSTATUS SetPrivilegeOnAccount(LSA_HANDLE PolicyHandle, PSID AccountSid, LPWSTR PrivilegeName, BOOL bEnable);
DWORD AddPrivilegeToAccount(LSA_HANDLE PolicyHandle, LPWSTR AccountName, LPWSTR PrivilegeName);
DWORD SearchForPrivilegedAccounts(LPWSTR PrivilegeName, BOOL bEnable=FALSE);
#endif