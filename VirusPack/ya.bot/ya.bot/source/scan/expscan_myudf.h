/*  ya.bot  */

#ifndef NO_EXPSCAN
#ifndef NO_EXPSCANMYUDF
bool expscan_myudf(SExpScanInfo s_esi);

#define my_socket SOCKET
#define MYSQL_ERRMSG_SIZE 200

struct st_vio;
typedef struct st_vio Vio;
typedef char my_bool;
typedef unsigned __int64 my_ulonglong;

enum enum_field_types
{
		FIELD_TYPE_DECIMAL,
		FIELD_TYPE_TINY,
		FIELD_TYPE_SHORT,
		FIELD_TYPE_LONG,
		FIELD_TYPE_FLOAT,
		FIELD_TYPE_DOUBLE,
		FIELD_TYPE_NULL,
		FIELD_TYPE_TIMESTAMP,
		FIELD_TYPE_LONGLONG,
		FIELD_TYPE_INT24,
		FIELD_TYPE_DATE,
		FIELD_TYPE_TIME,
		FIELD_TYPE_DATETIME,
		FIELD_TYPE_YEAR,
		FIELD_TYPE_NEWDATE,
		FIELD_TYPE_ENUM = 247,
		FIELD_TYPE_SET = 248,
		FIELD_TYPE_TINY_BLOB = 249,
		FIELD_TYPE_MEDIUM_BLOB = 250,
		FIELD_TYPE_LONG_BLOB = 251,
		FIELD_TYPE_BLOB = 252,
		FIELD_TYPE_VAR_STRING = 253,
		FIELD_TYPE_STRING = 254
};

enum mysql_status
{
		MYSQL_STATUS_READY,
		MYSQL_STATUS_GET_RESULT,
		MYSQL_STATUS_USE_RESULT
};

typedef struct st_net
{
	Vio* vio;
	my_socket fd;
	int fcntl;
	unsigned char *buff,*buff_end,*write_pos,*read_pos;
	char last_error[MYSQL_ERRMSG_SIZE];
	unsigned int last_errno,max_packet,timeout,pkt_nr;
	unsigned char error;
	my_bool return_errno,compress;
	my_bool no_send_ok;
	unsigned long remain_in_buf,length, buf_length, where_b;
	unsigned int *return_status;
	unsigned char reading_or_writing;
	char save_char;
} NET;

typedef struct st_mysql_field 
{
	char *name;
	char *table;
	char *def;
	enum enum_field_types type;
	unsigned int length;
	unsigned int max_length;
	unsigned int flags;
	unsigned int decimals;
} MYSQL_FIELD;

typedef struct st_used_mem 
{
	struct st_used_mem *next;
	unsigned int left;
	unsigned int size;
} USED_MEM;

typedef struct st_mem_root 
{
	USED_MEM *free;
	USED_MEM *used;
	USED_MEM *pre_alloc;
	unsigned int min_malloc;
	unsigned int block_size;
	void (*error_handler)(void);
} MEM_ROOT;

struct st_mysql_options 
{
	unsigned int connect_timeout,client_flag;
	my_bool compress,named_pipe;
	unsigned int port;
	char *host,*init_command,*user,*password,*unix_socket,*db;
	char *my_cnf_file,*my_cnf_group, *charset_dir, *charset_name;
	my_bool use_ssl;
	char *ssl_key;
	char *ssl_cert;
	char *ssl_ca;
	char *ssl_capath;
};

typedef struct charset_info_st
{
	UINT number;
	const char *name;
	UCHAR *ctype;
	UCHAR *to_lower;
	UCHAR *to_upper;
	UCHAR *sort_order;
	UINT strxfrm_multiply;
	int (*strcoll)(const UCHAR *, const UCHAR *);
	int (*strxfrm)(UCHAR *, const UCHAR *, int);
	int (*strnncoll)(const UCHAR *, int, const UCHAR *, int);
	int (*strnxfrm)(UCHAR *, const UCHAR *, int, int);
	my_bool (*like_range)(const char *, UINT, PCHAR, UINT, char *, char *, UINT *, UINT *);
	UINT mbmaxlen;
	int (*ismbchar)(const char *, const char *);
	my_bool (*ismbhead)(UINT);
	int (*mbcharlen)(UINT);
} CHARSET_INFO;

typedef struct st_mysql
{
	NET	net;
	typedef char *connector_fd;
	char *host, *user, *passwd, *unix_socket, *server_version, *host_info, *info, *db;
	unsigned int port,client_flag,server_capabilities;
	unsigned int protocol_version;
	unsigned int field_count;
	unsigned int server_status;
	unsigned long thread_id;
	my_ulonglong affected_rows;
	my_ulonglong insert_id;
	my_ulonglong extra_info;
	unsigned long packet_length;
	enum mysql_status status;
	MYSQL_FIELD	*fields;
	MEM_ROOT field_alloc;
	my_bool free_me;
	my_bool reconnect;
	struct st_mysql_options options;
	char scramble_buff[9];
	struct charset_info_st *charset;
	unsigned int server_language;
} MYSQL;
#endif
#endif