

#ifndef NO_FILE
int delete_file(char *szPath);
bool execute_file(char *szPath, int iVisibility);
bool extract_resource(char *szResName, char *szResType, char *szExtractPath);
bool file_exists(char *szPath);
bool open_file(char *szPath);
#endif