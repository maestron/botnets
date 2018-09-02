#include <string.h>

class CoderDecoder{
	
	char* encryptionTable;
	
public:
	CoderDecoder();
	char* encode(char*);
	char* decode(char*);
};

// this is the constructor
CoderDecoder::CoderDecoder()
{
	//this character array holds all ASCII values from 32 to 126
	//in jumbled up order to be exchanged with the message characters.
	encryptionTable = "=wertyKLZXCuio345pasdfGHJVBNM1267890-.{}[]:;'><,?/|\\\"_+qQWEjklzxcvbYUIOP~!@#$%^&*()FghnmRTASD` ";
}

/*
Please note that the characters are minused 32 when encrypting 
and plussed 32 when decrypting, this does not mean its a encryption formula.
This is done because the ASCII values from 0 to 32 cannot be typed on the
keyboard,so it is ignored for simplicity purposes.
Thus the encryption table holds only 94 characters from total of 127.
*/

char* CoderDecoder::encode(char* message)
{
	int i;
	int length = strlen(message);
	
	char *encryptedMessage = new char[length];
	
	for(i=0;i<length;i++)
	{
		//convert to ASCII number
		int j = (int)message[i];
		//match it with coresponding value in table and then swap.
		encryptedMessage[i] = encryptionTable[j-32];
		
	}
	
	encryptedMessage[i] = '\0';
	
	return encryptedMessage;
}

char* CoderDecoder::decode(char* message)
{
	unsigned int i,j;
	unsigned int length = strlen(message);
	
	char *decryptedMessage = new char[length];
	
	/* here we compare the character on the encrypted string to the
	table and then swap it back to the original character*/
	for(i=0;i<length;i++)
	{
		for (j=0;j<strlen(encryptionTable);j++)
			if(encryptionTable[j] == message[i])
			{
				decryptedMessage[i] = char(j+32);
			}
	}
	
	decryptedMessage[i] = '\0';
	
	return decryptedMessage;
}
