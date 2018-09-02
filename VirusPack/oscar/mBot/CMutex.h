

#ifndef __CMUTEX_H__
#define __CMUTEX_H__

#include <windows.h>
#include <string>

using namespace std;

class CMutex
{
private:
	HANDLE hMutex;
public:
	CMutex();
	~CMutex();
	void DoConsole();
};

#endif // __CMUTEX_H__

