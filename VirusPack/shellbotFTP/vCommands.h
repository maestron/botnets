// CCmd Class
#include "vInclude.h"

class CCmd
{
public:
	void InterpretCmd(vector <string> iBuffer);
	void GetSpeakerName(vector <string> iBuffer);
	string msgTo;
	string serverAlias;
	bool Reply;

};