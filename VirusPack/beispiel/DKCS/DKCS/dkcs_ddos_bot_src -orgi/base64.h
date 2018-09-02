//-----------------------------------------------------------------
// this file is a part of: DKCS WORM.DDoS bot v 0.1
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//-----------------------------------------------------------------
void Base64Encode(char *buf, char *obuf, int len){

    int	i;
    
	for(i=0; i<len-2; i+=3){
        *obuf++ = b64[(buf[i]>>2) & 0x3F];
        *obuf++ = b64[((buf[i] & 0x3)<<4 | ((int)(buf[i+1] & 0xF0)>>4))];
        *obuf++ = b64[((buf[i+1] & 0xF)<<2) | ((int)(buf[i+2] & 0xC0)>>6)];
        *obuf++ = b64[buf[i+2] & 0x3F];
	}
	if(i<len){
        *obuf++ = b64[(buf[i]>>2) & 0x3F];
		if(i == (len-1)){
            *obuf++ = b64[((buf[i] & 0x3)<<4)];
            *obuf++ = '=';
		}else{
            *obuf++ = b64[((buf[i] & 0x3)<<4 | ((int)(buf[i+1] & 0xf0)>>4))];
            *obuf++ = b64[((buf[i+1] & 0xf)<<2)];
		}
		*obuf++ = '=';
	}
	*obuf++ = '\0';
}
//-----------------------------------------------------------------