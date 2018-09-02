#ifndef __CBOT_H__
#define __CBOT_H__

#include <windows.h>
#include "CIRC.h"
#include "CMac.h"
#include "CCrypt.h"
#include "Defines.h"
#include "config.h"

class CBot
{
public:
	CBot();
	~CBot();

public:
	void	Init	();
	void	Quit	(char *msg, ...);
	void	Remove	();
	void	MsgBx	(HWND hWnd, UINT Type, char *title, char *msg, ...);
	void	SetDest	(char *file);

public:
	CIRC	*IRC;
	CMac	*Mac;
	CCrypt	*Crypt;

	char	*MyPath;
	char	*DestPath;
	char	*DestFile;
};

#endif