///////////////////////////////////////////////////////////////////////////////////////
// Filename ProcessName.h
// 
// Author: fuzen_op
// Email:  fuzen_op@yahoo.com or fuzen_op@rootkit.com
//
// Description: Globals and function prototypes used by ProcessName.c
//
// Date:    5/27/2003
// Version: 1.0

ULONG gul_ProcessNameOffset;	 // Global variable set in DriverEntry

#define PROCNAMELEN 16           // In the EPROCESS struct the image name 
								 // is 16 characters long

ULONG GetLocationOfProcessName(PEPROCESS); // Get offset of process name in
