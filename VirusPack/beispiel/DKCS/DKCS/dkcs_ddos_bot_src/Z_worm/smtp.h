//-----------------------------------------------------------------
// this file is a part of: DKCS LoadSystem v. 0.1a
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
// Special work for Panda
//-----------------------------------------------------------------
#include "sok.h"
#include "rnd.h"
//-----------------------------------------------------------------
#define CTT_PLAIN (char*)sz_ctt_plain
#define CTT_HTML (char*)sz_ctt_html
#define CE_WINDOWS1251 (char*)sz_ce_windows1251
#define SMTP_SEND_SUCCESS 1
#define SMTP_SEND_ERROR 0
#define SMTP_CONNECT_ERROR -1
#define SMTP_RESOLVE_ERROR -2
#define SMTP_SOCKET_ERROR -3
#define SMTP_LOGIN_FAILED -4
//-----------------------------------------------------------------
const char Base64Alph[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char BoundaryAlph[] = "0123456789ABCDEF";
const char sz_ce_windows1251[] = "windows-1251";
const char sz_ctt_plain[] = "plain";
const char sz_ctt_html[] = "html";
//-----------------------------------------------------------------
typedef struct _ATTACHLIST{
    char file_path[MAX_PATH];
    char attach_name[32];
    _ATTACHLIST* next;
} ATTACHLIST, *LPATTACHLIST;
//-----------------------------------------------------------------
typedef struct _MAILSTRUCT{
  char smtp_server[64];
  int smtp_port;
  char smtp_user[64];
  char smtp_pass[64];
  char mail_from[64];
  char rcpt_to[64];
  char header_from[128];
  char header_subject[128];
  char* content_text_type;
  char* charset_encoding;
  char* text;
  LPATTACHLIST attachs;
} MAILSTRUCT;
//-----------------------------------------------------------------
typedef ATTACHLIST* LPATTACHLIST;
typedef MAILSTRUCT* LPMAILSTRUCT;
//-----------------------------------------------------------------
void gen_boundary(char* out){
	int i;
	for(i = 0; i < 32; i++){
		*out = *(BoundaryAlph + (_rand() % 16));
		out ++;
	}
}
//-----------------------------------------------------------------
int base64_encode_rn(unsigned char* in, int len, char* out){
	unsigned char c;
	char* out_begin = out;
	unsigned char* in_begin = in;
	int i = 0;

    while(in - in_begin < len){
		switch(i){
case 0:
	*out = *(Base64Alph + (*in >> 2));
	break;
case 1:
	*out = *(Base64Alph + (((c << 4) | (*in >> 4)) & 0x3F));
	break;
case 2:
	*out = *(Base64Alph + (((c << 2) | (*in >> 6)) & 0x3F));
	out ++;
	*out = *(Base64Alph + (*in & 0x3F));
	break;
		}
		i = (i + 1) % 3;
		c = *in;
		out ++;
		in ++;
	}
	if(i > 0){
        if(i == 1)
            *out = *(Base64Alph + ((c << 4) & 0x3F));
        else
            *out = *(Base64Alph + ((c << 2) & 0x3F));
        out ++;
        while(i <= 2){
            *out = '=';
            out ++;
            i ++;
		}
	}
    *out = '\r';
    out ++;
	*out = '\n';
	out ++;
	return (out - out_begin);
}
//-----------------------------------------------------------------
int smtp_connect(LPMAILSTRUCT email){

    struct sockaddr_in saddr;
    struct hostent* hp;
	int s = socket(AF_INET, SOCK_STREAM, 0);

	if(s == -1)
		return 0;
    hp = gethostbyname(email->smtp_server);
    if(((int)hp == 0) || ((int)hp == -1)){
        closesocket(s);return 0;
        
	}
	memset(&saddr, 0, sizeof(struct sockaddr_in));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = *(int*)hp->h_addr;
	saddr.sin_port = htons(email->smtp_port);
	if(connect(s, (struct sockaddr*)&saddr, sizeof(struct sockaddr_in)) == -1){
		closesocket(s);
		return 0;
	}
	return s;
}
//-----------------------------------------------------------------
int smtp_answer(int s, LPREADLINESTRUCT lpRLS){

    char min1 = '0'; char max1 = '9';
	char min2 = '0'; char max2 = '9';
	char min3 = '0'; char max3 = '9';
	int first_loop = 1;
	
	for(;;){
		if(sreadline(s, lpRLS, "\r\n", 2) <= 0)
			return 0;
        if(lpRLS->StrLen > 3)
            if((*(lpRLS->lpBuff) >= min1) && (*(lpRLS->lpBuff) <= max1))
				if((*(lpRLS->lpBuff + 1) >= min2) && (*(lpRLS->lpBuff + 1) <= max2))
					if((*(lpRLS->lpBuff + 2) >= min3) && (*(lpRLS->lpBuff + 2) <= max3)){
						if(*(lpRLS->lpBuff + 3) == '\x20')
							break;
						if(first_loop)
							if(*(lpRLS->lpBuff + 3) == '-'){
								first_loop = 0;
								min1 = *(lpRLS->lpBuff);  min2 = *(lpRLS->lpBuff+1); min3 = *(lpRLS->lpBuff+2);
								max1 = min1; max2 = min2; max3 = min3;
							}
					}
					if(first_loop)
						return 0;
	}
	*(lpRLS->lpBuff + 3) = '\x00';
	return atoi(lpRLS->lpBuff);
}
//-----------------------------------------------------------------
int smtp_login(int s, LPMAILSTRUCT email, LPREADLINESTRUCT lpRLS){
    
	char buff[128];
    int len, b64_len;

    for(;;){
        if(!swrite(s, "AUTH LOGIN\r\n", 12))
			break;
		if(smtp_answer(s, lpRLS) != 334)
			break;
        len = (int)strlen(email->smtp_user);
        b64_len = base64_encode_rn((unsigned char*)email->smtp_user, len, buff);
        if(!swrite(s, buff, b64_len))
			break;
        if(smtp_answer(s, lpRLS) != 334)
			break;
        len = (int)strlen(email->smtp_pass);
		b64_len = base64_encode_rn((unsigned char*)email->smtp_pass, len, buff);
		if(!swrite(s, buff, b64_len))
			break;
		if(smtp_answer(s, lpRLS) != 235)
			break;
        return 1;
        
	}
	return 0;
}
//-----------------------------------------------------------------
int smtp_send_text(int s, LPMAILSTRUCT email, char* boundary){
    
	char buff[128];
	int enc_len, b64_len;
	int len = 1;
	char* pos;

    for(;;){
        if(!swrite(s, "--", 2))
			break;
        if(!swrite(s, boundary, 32))
			break;
        if(!swrite(s, "\r\nContent-Type: text/", 21))
			break;
        if(!swrite(s, email->content_text_type, (int)strlen(email->content_text_type)))
			break;
        if(!swrite(s, "; charset=\"", 11))
			break;
        if(!swrite(s, email->charset_encoding, (int)strlen(email->charset_encoding)))
			break;
        if(!swrite(s, "\"\r\nContent-Transfer-Encoding: base64\r\n\r\n", 40))
			break;
        len = (int)strlen(email->text);
        pos = email->text;
        while(len > 0){
            enc_len = (len > 57) ? 57 : len;
            b64_len = base64_encode_rn((unsigned char*)pos, enc_len, buff);
            if(!swrite(s, buff, b64_len)) break;
			len -= enc_len;
			pos += enc_len;
        }
		break;
	}
	return (len == 0);
}
//-----------------------------------------------------------------
int smtp_send_attachs(int s, LPMAILSTRUCT email, char* boundary){
    
	LPATTACHLIST attach = email->attachs;
	int enc_len, b64_len;
	char buff[64];
	char b64_buff[128];
	FILE* fid;

    while(attach){
        fid = fopen(attach->file_path, "rb");
        if(fid){
            if(!swrite(s, "--", 2))
				break;
			if(!swrite(s, boundary, 32))
				break;
			if(!swrite(s, "\r\nContent-Type: application/octet-stream; name=\"", 48))
				break;
			if(!swrite(s, attach->attach_name, (int)strlen(attach->attach_name)))
				break;
			if(!swrite(s, "\"\r\nContent-Transfer-Encoding: base64\r\n\r\n", 40))
				break;
			while(!feof(fid)){
                enc_len = (int)fread(buff, 1, 57, fid);
                b64_len = base64_encode_rn((unsigned char*)buff, enc_len, b64_buff);
                if(!swrite(s, b64_buff, b64_len))
					break;
			}
			enc_len = feof(fid);
			fclose(fid);
			if(!enc_len)
				return 0;
		}
		else
			return 0;
		attach = attach->next;
	}
	return (attach == 0);
}
//-----------------------------------------------------------------
int smtp_sendmail(LPMAILSTRUCT email, LPREADLINESTRUCT lpRLS){
    
	char boundary[32];
	int code = SMTP_CONNECT_ERROR;
	int s = smtp_connect(email);
	
	while(s){
        code = SMTP_SEND_ERROR;
        if(smtp_answer(s, lpRLS) != 220)
			break;
		if(!swrite(s, "HELO localhost\r\n", 16))
			break;
		if(smtp_answer(s, lpRLS) != 250)
			break;
		if(!smtp_login(s, email, lpRLS)){
			code = SMTP_LOGIN_FAILED;
			break;
		}
		if(!swrite(s, "MAIL FROM: ", 11))
			break;
        if(!swrite(s, email->mail_from, (int)strlen(email->mail_from)))
			break;
		if(!swrite(s, "\r\n", 2))
			break;
		if(smtp_answer(s, lpRLS) != 250)
			break;
		if(!swrite(s, "RCPT TO: ", 9))
			break;
		if(!swrite(s, email->rcpt_to, (int)strlen(email->rcpt_to)))
			break;
		if(!swrite(s, "\r\n", 2))
			break;
		if(smtp_answer(s, lpRLS) != 250)
			break;
		if(!swrite(s, "DATA\r\n", 6))
			break;
		if(smtp_answer(s, lpRLS) != 354)
			break;
		if(email->header_from){
            if(!swrite(s, "From: ", 6))
				break;
			if(!swrite(s, email->header_from, (int)strlen(email->header_from)))
				break;
			if(!swrite(s, "\r\n", 2))
				break;
		}
		if(email->header_subject){
            if(!swrite(s, "Subject: ", 9))
				break;
			if(!swrite(s, email->header_subject, (int)strlen(email->header_subject)))
				break;
			if(!swrite(s, "\r\n", 2))
				break;
		}
		gen_boundary(boundary);
		if(!swrite(s, "MIME-Version: 1.0\r\nContent-Type: multipart/mixed; boundary=\"", 60))
			break;
		if(!swrite(s, boundary, 32))
			break;
		if(!swrite(s, "\"\r\n", 3))
			break;
		if(email->text)
			if(!smtp_send_text(s, email, boundary))
				break;
		if(email->attachs)
			if(!smtp_send_attachs(s, email, boundary))
				break;
		if(!swrite(s, "--", 2))
			break;
		if(!swrite(s, boundary, 32))
			break;
		if(!swrite(s, "--\r\n", 4))
			break;
		if(!swrite(s, ".\r\n", 3))
			break;
		if(smtp_answer(s, lpRLS) != 250)
			break;
		code = SMTP_SEND_SUCCESS;
		break;
	}
	if(s){
        if(!swrite(s, "QUIT\r\n", 6))
			code = SMTP_SEND_ERROR;
		else if(smtp_answer(s, lpRLS) != 221)
			code = SMTP_SEND_ERROR;
		closesocket(s);
	}
	return code;
}
//-----------------------------------------------------------------