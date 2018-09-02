#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

#define MAX_KEY_SIZE	64
#define MAX_STRING_SIZE	256

void PrintToFile(unsigned char *data, int len, FILE *f) 
{
	int i;
	char temp[5];

	for(i = 0; i < len; i++, data++)
	{
		memset(temp, 0, sizeof(temp));
		sprintf(temp, "\\x%02X", *data);
		fputs(temp, f);
	}	
}

void PrintToFileChar(unsigned char c, FILE *f) 
{
	char temp[5] = {0};

	sprintf(temp, "\\x%02X", c);
	fputs(temp, f);	
}



char *Encode(unsigned char *string, unsigned char *key)
{
	unsigned int i, j;

	for (i = 0; i < strlen(string); i++)
	{
		for (j = 0; j < strlen(key); j++)
			string[i] ^= key[j];

		string[i] = ~ string[i];
	}

	return string;
}

/*
unsigned char EncodeChar(unsigned char c, unsigned char *key)
{
	unsigned int i;

	for (i = 0; i < strlen(key); i++)
	{
		c ^= key[i];
	}

	c = ~ c;

	return c;	
}
*/

int main(int argc, char *argv[])
{
	FILE			*in, *out;
	unsigned char	key[MAX_KEY_SIZE] = {0};
	unsigned char	string[MAX_STRING_SIZE] = {0};
	unsigned char	data[MAX_STRING_SIZE] = {0};
	int				c;
	int				i = 0, k = 0;
	BOOL			active = FALSE;

	printf("\n\nXOR encoder by iserdo v0.3 for DCI bot\n");
	printf("Copyright (c) 2007\n");
	printf("iserdo@gmail.com\n\n");

	if (argc < 4)
	{
		printf("Usage: %s <key> <inputfile> <outputfile>\n\n", argv[0]);
		printf("Example: %s hiu342 strings.cfg strings.h\n\n", argv[0]);
		return 0;
	}

	strncpy(key, argv[1], sizeof(key));

	in = fopen(argv[2], "rt");
	out = fopen(argv[3], "wt");
	if (in == NULL || out == NULL)
	{
		printf("Failed to open file(s)!\n");
		return 0;
	}

	while ((c = fgetc(in)) != EOF)
	{
		if (c == '\"')
		{
			if (!active)
			{
				active = TRUE;
				memset(data, 0, sizeof(data));
			}
			else
			{
				active = FALSE;
				printf("String: %s, encoded: ", data);
				PrintToFile(Encode(data, key), strlen(data), out);
				printf("%s\n", data);
			}
			fputc(c, out);
			continue;
		}

		if (active)
		{
			_snprintf(data, sizeof(data) - 1, "%s%c", data, c);
		}
		else
			fputc(c, out);
	}

/*		if (c == ' ' && k == 0)
		{
			k = 1;
			i = 0;
			memset(data, 0, sizeof(data));
		}
		else if (c == '\n' || c == '\r')
		{
			k = 0;
			i = 0;

			if (strlen(data) == 0 || strlen(string) == 0)
			{
				fputs("\n", out);
				continue;
			}

			printf("String: %s, value: %s, encoded: ", string, data);

			fputs("\t{", out);
			fputs(string, out);
			fputs(", \"", out);
			PrintToFile(Encode(data, key), strlen(data), out);
			fputs("\", 0},\n", out);

			printf("%s\n", data);

			memset(data, 0, sizeof(data));
			memset(string, 0, sizeof(string));
		}
		else
		{
			if (!k)
				string[i] = c;
			else
				data[i] = c;

			i++;
		}

	}

	if (strlen(data) != 0 && strlen(string) != 0)
	{
		printf("String: %s, value: %s, encoded: ", string, data);

		fputs("\t{", out);
		fputs(string, out);
		fputs(", \"", out);
		PrintToFile(Encode(data, key), strlen(data), out);
		fputs("\", 0},\n", out);
		//fputs("\\x00\", \"\"},\n", out);

		printf("%s\n", data);
	}*/

	fputs("\nchar decode_key[] = \"", out);
	fputs(key, out);
	fputs("\";\n", out);

	printf("Key is: %s\n", key);

	fclose(in);
	fclose(out);

	system("pause");

	return 0;
}