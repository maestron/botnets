/*  ya.bot  */

#ifndef NO_CRYPTOSHA256
#define uint8 unsigned char
#define uint32 unsigned long int

typedef struct
{
	uint32 total[2];
	uint32 state[8];
	uint8 buffer[64];
} sha256_context;

void sha256_starts(sha256_context *ctx);
void sha256_update(sha256_context *ctx, uint8 *input, uint32 length);
void sha256_finish(sha256_context *ctx, uint8 digest[32]);
#endif