#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <vector>
using namespace std;

class cString
{
public:

	//constructors
	cString( char *szString )
	{
		datasize	= (int)strlen(szString);
		stringdata	= new char[datasize];
		strcpy( stringdata, szString );
	}

	cString( const char *szString )
	{
		cString((char*)szString);
	}

	cString( string szString )
	{
		cString(szString.c_str());
	}

	//comparison
	bool		Matches( char *data1, char *data2 );
	bool		Matches( const char *data1, const char *data2 );
	bool		Matches( string data1, string data2 );

	bool		Matches( char *data );						//only use on initiated class
	bool		Matches( const char *data );				//only use on initiated class
	bool		Matches( string data );						//only use on initiated class

	bool		WildcardMatches( char *data, char *wildcard );
	bool		WildcardMatches( const char *data, const char *wildcard );
	bool		WildcardMatches( string data, string wildcard );

	bool		WildcardMatches( char *wildcard );			//only use on initiated class
	bool		WildcardMatches( const char *wildcard );	//only use on initiated class
	bool		WildcardMatches( string wildcard );			//only use on initiated class

	//string manipulation
	void		add( char* adddata ){ strcat(stringdata,adddata); }
	void		add( const char* adddata ){ add((char*)adddata); }
	void		add( string adddata ){ add(adddata.c_str()); }

	string		substring( string stringdata, int start, int length = 0 )
	{
		return (length>0) ? stringdata.substr( start, length ) : stringdata.substr( start );
	}

	char*		substring( char *stringdata, int start, int length = 0 )
	{
		return substring((string)stringdata, start, length);
	}

	const char*	substring( const char *stringdata, int start, int length = 0 )
	{
		return substring((char*)stringdata, start, length);
	}
	

	//conversion
	string		ToString();									//only use on initiated class
	string		ToString( char* data );
	string		ToString( const char *data );
	string		ToString( cString* data );

	char*		ToCharArray();								//only use on initiated class
	char*		ToCharArray( string data );
	char*		ToCharArray( cString* data );

	int			len(){return datasize;}

	//why would you need this?
	cString*	ToThis(){return this;}

private:

	//destruct (private for a reason)
	~cString()
	{
		memset( stringdata, 0, datasize );
	}

	//data
	char*		stringdata;
	int			datasize;
	
};