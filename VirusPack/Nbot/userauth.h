#include <vector>
using namespace std;

struct user_data_s
{
	string	username;
	string	password;
	string	usedhost;
	bool	loggedin;

	user_data_s()
	{
		username.clear();
		password.clear();
		usedhost.clear();
		loggedin = false;
	}
};

class cUserAuth
{
public:

	vector<user_data_s*> GetUsersInfo()
	{
		return Users;
	}

	bool AddUser( string Username, string Password )
	{
		//no auth? wtf idiot!
		if( Username.empty() && Password.empty() )
			return false;

		user_data_s *nu = new user_data_s;

		if( !nu )
			return false;

		nu->username = Username;
		nu->password = Password;

		Users.push_back( nu );

		return true;
	}

	bool LogoutUser( string Hostname )
	{
		for( int i = 0; i < (int)Users.size(); i++ )
		{
			user_data_s* cu = Users[i];

			if(!cu)return false;

			if( !strcmp( cu->usedhost.c_str(), Hostname.c_str() ) )
			{
				cu->usedhost.clear();
				cu->loggedin = false;
				return true;
			}
		}
		return false;
	}

	bool AuthHost( string Username, string Password, string Hostname )
	{
		for( int i = 0; i < (int)Users.size(); i++ )
		{
			user_data_s* cu = Users[i];

			if(!cu)return false;

			if( !strcmp( cu->username.c_str(), Username.c_str() )
				&& !strcmp( cu->password.c_str(), Password.c_str() ) )
			{
				cu->usedhost = Hostname;
				cu->loggedin = true;
				return true;
			}
		}

		return false;
	}

	bool AuthCheckLoop( string Hostname )
	{
		for( int i = 0; i < (int)Users.size(); i++ )
		{
			user_data_s* cu = Users[i];

			if(!cu)return false;

			if( !strcmp( cu->usedhost.c_str(), Hostname.c_str() ) )
			{
				return true;
			}
		}
		return false;
	}

private:

	vector<user_data_s*> Users;

};