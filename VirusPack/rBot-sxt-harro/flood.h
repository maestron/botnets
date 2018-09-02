

 void clone_send(char *buf);
 void load_clones(char * Clone_Server,int Clone_port,int num_clones);
 char * clone_nick(char *strbuf);

typedef struct clone_struct {
	BOOL used;//if true socket is in use
	SOCKET sock;
	HANDLE Handle;
	char server[512];
	int port;
} clonestr;

//structure to store data used by diferend threads

typedef struct threads_struct2 {
	char C_name[250];//the discription of the thread showed with the threads command
	int id; 
	HANDLE Threat_Handle;	//handle to the thread. Threat_Handle = CreateThread(.....);
	SOCKET reply_sock;	//this is the socket where the replys go to
	SOCKET Threads_sock;	//this socket will be closed when you kill the thread 
	int int_1; //to store a number  
	int int_2;
	int int_3;
	char chan[250];		//string that holds the channel/nickname where the replys go to set to null when its a dcc chat
	char string1[MAX_PATH]; //can be used to store strings
	char string2[MAX_PATH];
} thread2;