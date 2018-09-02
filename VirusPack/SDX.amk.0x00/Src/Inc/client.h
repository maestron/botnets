/* From `client.cpp': */
#include <stdarg.h>
char * getsockip (int s );
int getret (int s );
/* From `memmem.cpp': */
void * mymemmem (const void *haystack , int haystack_len , const void *needle , int needle_len );
/* From `socket.cpp': */
char * getip (int s );
void do_select2 (int socket , int tv_sec );
void do_select (int socket );
int read_line (int sock , char **buf );
