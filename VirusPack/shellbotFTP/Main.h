// CMain Class
#include "vInclude.h"

class CMain {
public:
	void ExecuteCmd(vector <string> iBuffer, int position, string cmd);
	void Auth(vector <string> iBuffer);
	bool sTopic;
	bool sLogin;
	bool sOnJoinTopic;
	string sTemp;
	bool CheckUser(string sUser);
};

