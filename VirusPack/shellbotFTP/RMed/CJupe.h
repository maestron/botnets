#include <vector>
#include <string>

#define WHOIS_DELAY 3
#define SENDMSG "WATCH JIN SURVIVE, I KNOW ALOT OF YALL SURPRISED"

typedef struct {
	SOCKET Socket;
	string s_Server;
	int iPort;
	string s_NickToJupe;
} JInfo;

class CJupe {
public:
	static bool Connect(JInfo *jClient);
	static vector <string> ParseIRCBuffer(string vBuffer, string type);
	static void Send(SOCKET Socket, const char* vBuffer,...);
	static void RunningThread(LPVOID lpClient);
	static string RndNick(string vPrefix);
	static unsigned long ResolveAddress(string server);
	static void WhoisThread(LPVOID lpClient);


	static bool bRunning;
	static bool bInitiated;
	static bool bReply;
	static bool bCheck1, bCheck2;

	static int iDelay;

};

