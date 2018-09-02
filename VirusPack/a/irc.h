struct 
irc_d {
   int auth;
   int sock;
   int connected;
   char channel[0x40];
   char alias[0x40];
   char password[0x40];
};

struct irc_d irc;

void IrcMain();
void IrcSend(char *);
void IrcJoin(char *);
void IrcParse(char *);

