#include "stdafx.h"

// THIS FILE INCLUDES OLD AND BUGGY CODE
// DONT USE IT!

/*
		//user closed connection?
		if(strstr(CTemp->szLine, "QUIT "))
		{
			//get name of sender
			for(int i=1; i<(int)strlen(CTemp->szLine); i++)
			{
				if(CTemp->szLine[i]=='!')
				{
					for(int a=1; a<i; a++)
					{
						szTemp[a-1]=CTemp->szLine[a];
						szTemp[a]=0;
					}
					break;
				}
			}

			CTemp->DeleteAuthedUser(szTemp);
		}
		*/

		/*
		//message from channel?
		if(strstr(CTemp->szLine, "PRIVMSG "))
		{
			//get name of sender
			for(int i=1; i<(int)strlen(CTemp->szLine); i++)
			{
				if(CTemp->szLine[i]=='!')
				{
					for(int a=1; a<i; a++)
					{
						szTemp[a-1]=CTemp->szLine[a];
						szTemp[a]=0;
					}
					break;
				}
			}
			
			//reset to zero against errors
			memset(szTo, 0, MSG_SIZE);
			
			//find first space char 
			//find user for the message (very lame method)
			for(int a=0; a<(int)strlen(CTemp->szLine); a++)
			{
				if(CTemp->szLine[a]==' ')
				{
					//find second space char
					for(int c=a+1; c<(int)strlen(CTemp->szLine); c++)
					{
						if(CTemp->szLine[c]==' ')
						{
							//search for end
							for(int d=c+1; d<(int)strlen(CTemp->szLine); d++)
							{
								if(CTemp->szLine[d]==':')
								{
									//copy in szTo
									iTemp=0;
									for(int b=c+1; b<(d-1); b++)
									{
										szTo[iTemp]=CTemp->szLine[b];
										iTemp+=1;
									}
									break;
								}
							}
							break;
						}
					}
					break;
				}
			}	
			
			//find the data of line (message, command and so on)
			for(int i=1; i<(int)strlen(CTemp->szLine); i++)
			{
				if(CTemp->szLine[i]==':')
				{
					//against parsing own reply lines
					if(!strstr(CTemp->szLine+i+1, "\x03\x34"))
					{
						//now parse the recieved messages
						CTemp->ParseMessages(CTemp->szLine+i+1, szTemp, szTo);
						break;
					}
				}
			}
		}
		*/