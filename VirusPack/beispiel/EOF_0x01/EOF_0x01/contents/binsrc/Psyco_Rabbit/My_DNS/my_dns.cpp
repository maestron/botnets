/***************************************************************************
 *   Copyright (C) 29/04/2006 by Psyco_Rabbit                              *
 *   PsycoRabbit@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the Berkeley Software Distribution (BSD)        *
 *   License.                                                              *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY.                                             *
 *                                                                         *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>



using namespace std;

int main()
{
 struct hostent *host;                            //it contains informations about host
 struct in_addr addr;                             //in this struct there is our address
 char address[32];
 string c;


 do{
 cout<<"DNS by Psyco_Rabbit"<<endl;
 cout<<"1-hostname --> ip"<<endl;
 cout<<"2-ip --> hostname"<<endl;
 string i;
 cin>>i;
 while (i!="1" && i!="2"){
   cout<<"Type 1 or 2!"<<endl;
   cin>>i;
  }

 char s[32];
 cout<<"Type address:"<<endl;
 cin>>s;

 if (i=="1"){
 if ((host=gethostbyname(s))==NULL)                             //system call to obtain ip address by hostname
    herror("gethostbyname");
 else{
    inet_ntop(AF_INET,host->h_addr,address,sizeof(address));    //transform h_addr in a readable format
    cout<<address<<endl;
   }
 }


 if (i=="2"){
 if ((inet_aton(s, &addr))==0)
    herror("inet_aton");
 if ((host=gethostbyaddr(&addr,sizeof(addr),AF_INET))==NULL)    //system call to obtain hostname by ip address
    herror("gethostbyaddr");
 else cout<<host->h_name<<endl;

 }


 cout<<"Do you want to continue? y/n"<<endl;
 cin>>c;
 while (c!="n" && c!="y")
    cin>>c;
 }while (c!="n");


 return EXIT_SUCCESS;
}
