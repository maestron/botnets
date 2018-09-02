#ifdef WIN32
#ifndef __KEYLOGGER_H__
#define __KEYLOGGER_H__

class CKeyLog : public CThread {
public:
			 CKeyLog();
	virtual	~CKeyLog();

	void	*Run();
};

#endif // __KEYLOGGER_H__
#endif