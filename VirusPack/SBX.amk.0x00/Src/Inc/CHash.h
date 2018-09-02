#ifndef __CHASH_H__
#define __CHASH_H__

#include <winioctl.h>

class CHash
{
public:
	CHash();
	~CHash();

public:
	void	Get			(char *out);

private:
	void	Rot			(char *out);
	bool	GDG			(DISK_GEOMETRY *pdg);
	void	GetHash		(char *out);
	void	CryptHash	(char *out);
};

#endif