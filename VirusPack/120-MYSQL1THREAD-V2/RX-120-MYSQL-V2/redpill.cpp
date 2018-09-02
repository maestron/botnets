#include "Inc.h"
#include "Fun.h"
#include "Ext.h" 

int _redpill () {
	unsigned char m[2+4], rpill[] = "\x0f\x01\x0d\x00\x00\x00\x00\xc3";
	*((unsigned*)&rpill[3]) = (unsigned)m;
	((void(*)())&rpill)();
	return (m[5]>0xd0) ? 1 : 0;
}