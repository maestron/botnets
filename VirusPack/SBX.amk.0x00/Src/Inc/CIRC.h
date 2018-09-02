#ifndef __CIRC_H__
#define __CIRC_H__

class CIRC
{
public:
	CIRC();
	~CIRC();

public:
	bool Connect	(char *srv, int port);
	int  Send		(char *msg, ...);
	bool Recv		();
	void Privmsg	(char *dest, char *msg, ...);
	void Disconnect (char *msg, ...);
	void HandleMsg	(char *msg);
	bool CanCon		();
	void SetNick	(int Type, int len);
	bool Identify	(char *srvpass);

public:
	char  *nick;

private:
	SOCKET sock;
};

#endif