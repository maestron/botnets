/*
 * aPLib compression library  -  the smaller the better :)
 *
 * Visual C/C++ header file
 *
 * Copyright (c) 1998-2003 by Joergen Ibsen / Jibz
 * All Rights Reserved
 */

#ifndef APLIB_H_INCLUDED
#define APLIB_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

unsigned int __cdecl aP_pack(unsigned char *source,
                             unsigned char *destination,
                             unsigned int length,
                             unsigned char *workmem,
                             int (__cdecl *callback) (unsigned int, unsigned int));

unsigned int __cdecl aP_workmem_size(unsigned int inputsize);

unsigned int __cdecl aP_max_packed_size(unsigned int inputsize);

unsigned int __cdecl aP_depack_asm(unsigned char *source, unsigned char *destination);

unsigned int __cdecl aP_depack_asm_fast(unsigned char *source, unsigned char *destination);

unsigned int __cdecl aP_crc32(unsigned char *source, unsigned int length);

unsigned int __cdecl aPsafe_pack(unsigned char *source,
                                 unsigned char *destination,
                                 unsigned int length,
                                 unsigned char *workmem,
                                 int (__cdecl *callback) (unsigned int, unsigned int));

unsigned int __cdecl aPsafe_check(unsigned char *source);

unsigned int __cdecl aPsafe_get_orig_size(unsigned char *source);

unsigned int __cdecl aPsafe_depack_asm(unsigned char *source, unsigned char *destination);

unsigned int __cdecl aPsafe_depack_asm_fast(unsigned char *source, unsigned char *destination);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APLIB_H_INCLUDED */
