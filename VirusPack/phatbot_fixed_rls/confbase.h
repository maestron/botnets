#ifndef __CONFBASE_H__
#define __CONFBASE_H__

// Type for CVar value
typedef struct conf_cvar_s {
	char		*szName;		// The name of the CVar
	char		*szValue;		// The CVars value
	char		*szCryptKey;	// The Sappire encryption key (leave empty for no encryption)
	char		*szMD5;			// The MD5 hash of the value (to prevent exe hacking)
} conf_cvar;

// Type for User
typedef struct conf_user_s {
	conf_cvar	 cUsername;		// The username
	conf_cvar	 cPasswordMD5;	// The passwords MD5 hash
	conf_cvar	 cHostmask;		// The host mask
	conf_cvar	 cIdentdmask;	// The identd mask
} conf_user;

// Type for Server
typedef struct conf_server_s {
	conf_cvar	 cChanPass;		// The channels password
	conf_cvar	 cMainChan;		// The main channel
	conf_cvar	 cNickPrefix;	// The nick prefix
	conf_cvar	 cPort;			// The port to connect to
	conf_cvar	 cServer;		// The server to connect to
	conf_cvar	 cServPass;		// The password of the server
	conf_cvar	 cUseSSL;		// Use SSL to connect ?
} conf_server;

#endif // __CONFBASE_H__
