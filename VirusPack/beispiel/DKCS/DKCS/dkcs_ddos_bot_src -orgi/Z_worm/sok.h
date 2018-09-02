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
#define BUFFER_OVERFLOW -1;
#define SOCKET_TIMEOUT -2;
#define INVALID_PARAM -3;
//-----------------------------------------------------------------
typedef struct{
	char*	lpBuff;
	int		BuffSize;
	int		StrLen;
	char*	lpNextBuff;
	int		BytesLeft;
} READLINESTRUCT;
//-----------------------------------------------------------------
typedef READLINESTRUCT* LPREADLINESTRUCT;
//-----------------------------------------------------------------
int CreateREADLINESTRUCT(LPREADLINESTRUCT hStruct, int BuffSize){
    if(BuffSize > 0){
        hStruct->lpBuff = (char*)malloc(BuffSize);
        if(hStruct->lpBuff){
            hStruct->BuffSize = BuffSize;
            hStruct->StrLen = 0;
            hStruct->lpNextBuff = NULL;
            hStruct->BytesLeft = 0;
            return 1;
        }
	}
	return 0;
}
//-----------------------------------------------------------------
int FreeREADLINESTRUCT(LPREADLINESTRUCT hStruct){
    if(hStruct)
        if(hStruct->lpBuff){
			free(hStruct->lpBuff);
			return 1;
		}
	return 0;
}
//-----------------------------------------------------------------
char* FindNextBuff(char* lpBuff, int buff_size, char* lpSubBuff, int subbuff_size){

	int i, j;

	if((buff_size > 0)&&(subbuff_size > 0)&&(subbuff_size <= buff_size)){
        for(i = 0, j = 0; i < buff_size; i++){
			if(lpBuff[i] == lpSubBuff[j]){
                j++;
			}else{
				i -= j;
				j = 0;
			}
			if(j == subbuff_size)
				return lpBuff + i + 1;
			else if(buff_size - i - 1 < subbuff_size - j)
				break;
		}
	}
	return 0;
}
//-----------------------------------------------------------------
int swrite(SOCKET s, char* Buff, int buff_size){
	int bytes;
	while(buff_size > 0){
        bytes = send(s, Buff, buff_size, 0);
		if((bytes == 0)||(bytes == SOCKET_ERROR))
			return 0;
		buff_size -= bytes;
		Buff += bytes;
  }
  return 1;
}
//-----------------------------------------------------------------
int sread(SOCKET s, char* Buff, int buff_size){
    int bytes;
    while(buff_size > 0){
        bytes = recv(s, Buff, buff_size, 0);
        if((bytes == 0)||(bytes == SOCKET_ERROR))
            return 0;
        buff_size -= bytes;
		Buff += bytes;
	}
	return 1;
}
//-----------------------------------------------------------------
int sreadline(SOCKET s, LPREADLINESTRUCT hStruct, char* EndBytes, int EndBytesCount){
    int bytes_readed = 0;
	int bytes = hStruct->BytesLeft;
	if(EndBytesCount == 0)
		return INVALID_PARAM;
	if(bytes)
		memcpy(hStruct->lpBuff, hStruct->lpNextBuff, bytes);
    for(;;){
        if(bytes_readed >= EndBytesCount){
            bytes_readed -= EndBytesCount - 1;
			bytes += EndBytesCount - 1;
		}
		hStruct->lpNextBuff = FindNextBuff(hStruct->lpBuff + bytes_readed, bytes, EndBytes, EndBytesCount);
		bytes_readed += bytes;
		if(hStruct->lpNextBuff)
			break;
		if(bytes_readed == hStruct->BuffSize)
			return BUFFER_OVERFLOW;
        bytes = recv(s, (char*)(hStruct->lpBuff + bytes_readed), hStruct->BuffSize - bytes_readed, 0);
		if((bytes == 0)||(bytes == SOCKET_ERROR))
			return 0;
	}
	hStruct->lpNextBuff[-EndBytesCount] = 0x00;
	hStruct->StrLen = hStruct->lpNextBuff - hStruct->lpBuff - EndBytesCount;
	hStruct->BytesLeft = hStruct->lpBuff + bytes_readed - hStruct->lpNextBuff;
	return 1;
}
//-----------------------------------------------------------------