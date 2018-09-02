/* Programmer: J. Buzzi
Date: 07/28004
Email: kingbuzzman@msn.com
Project Name: kROT13 1.0 */
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
char *code(char *);
void Clipit(char chr[255]);
void CHK(char *MSG ,char *InBuf, int MAX, char chr);
int main (void)


    {
    	char l[255], *p;
    	int i;
    	
    	printf("kROT13 Encoder/Decoder v1.0 by: KBM\n\nType the encoded/decoded text to get it decoded/encoded:\n\n");


        	do {
        		CHK("> " , l, 254, ' ');
        		p = code(l);
        		printf("* %s\n\nDo you want to save it to the clipboard? (Y/N)(N) ",p);
        		
        		i = getch(); printf("%c\n", i);
        		
        		if (i == 'y' || i == 'Y')


            		{
            			Clipit(p); i = '\0';
            		}
            		
            		printf("Do you want to quit? (Y/N)(N) ");
            		i = getch(); printf("%c\n\n", i);
            	
            	} while(!(i == 'y' || i == 'Y'));
            	
            	printf("\t***ROT13 v.1.0 by J. Buzzi\nLast built %s at %s", __DATE__, __TIME__); getch();
            	
            	return 0;
        }

        char *code(char *chr)


            {
            	char cbuf[255];
            	static char buf[255];
            	int i;
            	
            	strcpy(cbuf, chr); strcpy(buf, cbuf);
            	
            	for(i = 0; i < strlen(cbuf); i++)


                	{
                		if (cbuf[i] >= 65 && cbuf[i] <= 90 || cbuf[i] >= 97 && cbuf[i] <= 122)


                    		{
                    			if (cbuf[i] >= 65 && cbuf[i] <= 77 || cbuf[i] >= 97 && cbuf[i] <= 109) buf[i] = cbuf[i]+13;
                    			else if (cbuf[i] > 109) buf[i] = cbuf[i]+12-122+97;
                    			else if (cbuf[i] > 77 && cbuf[i] <=90) buf[i] = cbuf[i]+12-90+65;
                    		}
                    		else buf[i] = cbuf[i];
                    	}
                    	return buf;
                }

                void Clipit(char chr[255]) //Thanks Michael Pickens for clipboard code.


                    {
                    	OpenClipboard(NULL);
                    	EmptyClipboard();
                    	
                    HGLOBAL h = GlobalAlloc(GHND | GMEM_SHARE, strlen(chr) + 1);
                    	strcpy((LPSTR)GlobalLock(h), chr);
                    	GlobalUnlock(h);
                    	
                    SetClipboardData(CF_TEXT, h);
                    	CloseClipboard(); 
                }

                void CHK(char *MSG ,char *InBuf, int MAX, char chr)


                    {
                    	int i = 0, geth = 0, Amou = 0;
                    	printf("%s", MSG);
                    	
                    	do


                        	{
                        		geth = getch();
                        		if(!(geth == 13))


                            		{
                            			if(geth == '\b')


                                			{
                                				if(i!= 0)


                                    				{
                                    					printf("\b \b");
                                    					InBuf[i] = '\0';
                                    					i--;
                                    				}
                                    			}
                                    			else if (i >= MAX && geth != '\n') 


                                        			{
                                        				printf("\nError: Max lenth is %i\n", MAX); 
                                        				CHK(MSG,InBuf, MAX, chr);
                                        				return;
                                        			}
                                        			else if(geth == 13) printf("\b \b");
                                        			else 

                                            			{
                                            				InBuf[i] = geth;
                                            				if (chr == '*'){ printf("%c", chr);}
                                            				else {printf("%c", geth);}
                                            				i++;
                                            			}
                                            		}
                                            	} while(geth != 13);
                                            	InBuf[i] = '\0';
                                            	printf("\n");
                                        }