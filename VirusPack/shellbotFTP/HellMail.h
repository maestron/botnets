/** HellMail.h **/

#include "vInclude.h"
#include "CThread.h"

class CMail : public CThread {
public:
	virtual void *Run();
};

