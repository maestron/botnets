
#ifndef __SNIFFER_H__
#define __SNIFFER_H__

class CSniffer : public CThread {
public:
			 CSniffer();
	virtual	~CSniffer();

	void	*Run();
};

#endif // __SNIFFER_H__
