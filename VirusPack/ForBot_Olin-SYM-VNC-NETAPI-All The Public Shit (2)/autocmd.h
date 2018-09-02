#include "cstring.h"
#include "cthread.h"

#ifndef __AUTOCMD_H__
#define __AUTOCMD_H__
class CAutoCmd : public CThread {
public:
 CAutoCmd();
virtual	~CAutoCmd();
void	*Run();
void Command(CString Command,CString ReplyTo,bool silent, bool notice);
};
#endif


