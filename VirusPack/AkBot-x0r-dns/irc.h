struct ircs
{
	char me[32];
	char nick[32];
	char user[16];
	char host[128];
	SOCKET sock;
};

char *irc_rndnick();

bool irc_connect();

void irc_send(const char *msg, ...);

void irc_privmsg(const char *target, const char *msg, ...);

void irc_getinfo(const char *address);

void irc_parse(const char *line);