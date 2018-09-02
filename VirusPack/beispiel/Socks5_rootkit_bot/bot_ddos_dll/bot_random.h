USHORT GetRandomNum(DWORD from,DWORD to)
{
	USHORT uPort = 0;
	srand((unsigned)time(NULL)+rand());
	
	while(uPort < from || uPort > to)
	{
		uPort = (unsigned short)rand();
	}
	return uPort;
}

char *GetRandomStr(BYTE blen,BYTE from,BYTE to,char *dst)
{
	char *retstr;
	BYTE i,b;
	retstr = dst;
	if(retstr)
	{
		for( i  = 0 ; i < blen ; i ++ )
		{
			for ( b = 0 ; b <= i ; b ++)
				*dst = (BYTE)GetRandomNum(from,to);
			dst++;
		}
	}	else	{
		return NULL;
	}
	//memcpy(dst,retstr,blen);

	return retstr;
}
