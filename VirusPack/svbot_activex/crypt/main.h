#include < windows.h >
#include < stdio.h >

void printcfg( char *pszFmt, ... )
{
	if ( strlen(pszFmt) >= 1024 ) return;

	va_list va = {0};
	va_start( va, pszFmt );
	char szBuf[1024]="";
	_vsnprintf( szBuf, sizeof(szBuf)-1, pszFmt, va );
	va_end( va );

	FILE *f = fopen( "config.txt", "a+" );
	if ( f )
	{
		fprintf( f, "%s\n", szBuf );
		fclose( f );
		printf( "%s\n", szBuf );
	}
}

char *blah( char *str )
{
	static char out[512];
	memset( out, 0, 512 );

	char tmp[12]="";

//	int i;

	for ( int i = 0; i < (int)strlen(str); i++ )
	{
		memset( tmp, 0, 12 );
		_snprintf( tmp, sizeof(tmp), "\\x%2.2X", (u_char)str[i] );
		strcat( out, tmp );
	}

	return out;
}

int rrand(int min, int max)
{
//	srand(GetTickCount());

	if (min == max)
		return min;

	return rand() % (max - min + 1) + min;
}

void crypt( u_char *inp, DWORD inplen, u_char *key, DWORD keylen )
{
	if ( !key ) return;

	unsigned char Sbox[256]={0}, Sbox2[256]={0}, temp = 0 , k = 0;
	unsigned long i=0, j=0, t=0, x=0;

    //initialize sbox i
	for ( i = 0; i < 256U; i++ ) Sbox[i] = (unsigned char)i;

	//initialize the sbox2 with user key
	for(i = 0; i < 256U ; i++) 
	{
		if(j == keylen) j = 0;
		Sbox2[i] = key[j++];
	}    

	j = 0 ; //Initialize j
	//scramble sbox1 with sbox2
	for(i = 0; i < 256; i++)
	{
		j = (j + (unsigned long) Sbox[i] + (unsigned long) Sbox2[i]) % 256U ;
		temp =  Sbox[i];                    
		Sbox[i] = Sbox[j];
		Sbox[j] =  temp;
	}

	i = j = 0;
	for(x = 0; x < inplen; x++) 
	{
		//increment i
		i = (i + 1U) % 256U;
		//increment j
		j = (j + (unsigned long) Sbox[i]) % 256U;

		//Scramble SBox #1 further so encryption routine will
		//will repeat itself at great interval
		temp = Sbox[i];
		Sbox[i] = Sbox[j] ;
		Sbox[j] = temp;

		//Get ready to create pseudo random  byte for encryption key
		t = ((unsigned long) Sbox[i] + (unsigned long) Sbox[j]) %  256U ;

		//get the random byte
		k = Sbox[t];

		//xor with the data and done
		inp[x] = (unsigned char)(inp[x] ^ k);
	}
}

u_char *decrypt( char *buf, int size, char *key )
{
	static u_char *wat = (u_char *)malloc( size + 1 );

	memcpy( wat, buf, size );

//	crypt( (u_char*)wat, strlen((char *)wat), (u_char *)key, strlen((char *)key) );
	crypt( wat, strlen((char *)wat), (u_char *)key, strlen(key) );

	return wat;
}