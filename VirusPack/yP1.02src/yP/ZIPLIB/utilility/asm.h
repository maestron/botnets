/* asm.h -- library assembler function prototypes

   This file is part of the LZO real-time data compression library.

   Copyright (C) 1996-2002 Markus Franz Xaver Johannes Oberhumer
   All Rights Reserved.

   The LZO library is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   The LZO library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the LZO library; see the file COPYING.
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Markus F.X.J. Oberhumer
   <markus@oberhumer.com>
 */



/*************************************************************************
//
**************************************************************************/

#if !defined(LZO_ASM_NAME)
#  if defined(__GNUC__)
#    define LZO_ASM_NAME(x)	__asm__("_" #x)
#  else
#    define LZO_ASM_NAME(x)
#  endif
#endif


#if !defined(LZO_NO_ASM) && !defined(__LZO_NO_ASM)
#  if defined(__LZO_i386) && (UINT_MAX == LZO_0xffffffffL)
#    if defined(__GNUC__) || defined(__WATCOMC__)
#      define LZO1C_HAVE_i386_DECOMPRESS_ASM
#      define LZO1F_HAVE_i386_DECOMPRESS_ASM
#      define LZO1X_HAVE_i386_DECOMPRESS_ASM
#      define LZO1Y_HAVE_i386_DECOMPRESS_ASM
#    endif
#  endif
#endif


/*************************************************************************
//
**************************************************************************/

#if 1
   /* LZO1B is not yet implemented in assembly */
#  define lzo1b_decompress_asm				0
#  define lzo1b_decompress_asm_safe			0
#  define lzo1b_decompress_asm_fast			0
#  define lzo1b_decompress_asm_fast_safe	0
#endif


#if defined(LZO1C_HAVE_i386_DECOMPRESS_ASM)
LZO_EXTERN_CDECL(int)
lzo1c_decompress_asm
                        ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
                        LZO_ASM_NAME(lzo1c_decompress_asm);
LZO_EXTERN_CDECL(int)
lzo1c_decompress_asm_safe
                        ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
                        LZO_ASM_NAME(lzo1c_decompress_asm_safe);
#  define lzo1c_decompress_asm_fast			0
#  define lzo1c_decompress_asm_fast_safe	0
#else
#  define lzo1c_decompress_asm				0
#  define lzo1c_decompress_asm_safe			0
#  define lzo1c_decompress_asm_fast			0
#  define lzo1c_decompress_asm_fast_safe	0
#endif


#if defined(LZO1F_HAVE_i386_DECOMPRESS_ASM)
#  define lzo1f_decompress_asm				0
#  define lzo1f_decompress_asm_safe			0
LZO_EXTERN_CDECL(int)
lzo1f_decompress_asm_fast
                        ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
                        LZO_ASM_NAME(lzo1f_decompress_asm_fast);
LZO_EXTERN_CDECL(int)
lzo1f_decompress_asm_fast_safe
                         (const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
                        LZO_ASM_NAME(lzo1f_decompress_asm_fast_safe);
#else
#  define lzo1f_decompress_asm				0
#  define lzo1f_decompress_asm_safe			0
#  define lzo1f_decompress_asm_fast			0
#  define lzo1f_decompress_asm_fast_safe	0
#endif


#if defined(LZO1X_HAVE_i386_DECOMPRESS_ASM)
LZO_EXTERN_CDECL(int)
lzo1x_decompress_asm    ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
                        LZO_ASM_NAME(lzo1x_decompress_asm);
LZO_EXTERN_CDECL(int)
lzo1x_decompress_asm_safe
                        ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
                        LZO_ASM_NAME(lzo1x_decompress_asm_safe);
LZO_EXTERN_CDECL(int)
lzo1x_decompress_asm_fast
                        ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
                        LZO_ASM_NAME(lzo1x_decompress_asm_fast);
LZO_EXTERN_CDECL(int)
lzo1x_decompress_asm_fast_safe
                         (const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
                        LZO_ASM_NAME(lzo1x_decompress_asm_fast_safe);
#else
#  define lzo1x_decompress_asm				0
#  define lzo1x_decompress_asm_safe			0
#  define lzo1x_decompress_asm_fast			0
#  define lzo1x_decompress_asm_fast_safe	0
#endif


#if defined(LZO1Y_HAVE_i386_DECOMPRESS_ASM)
LZO_EXTERN_CDECL(int)
lzo1y_decompress_asm    ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
                        LZO_ASM_NAME(lzo1y_decompress_asm);
LZO_EXTERN_CDECL(int)
lzo1y_decompress_asm_safe
                        ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
                        LZO_ASM_NAME(lzo1y_decompress_asm_safe);
LZO_EXTERN_CDECL(int)
lzo1y_decompress_asm_fast
                        ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
                        LZO_ASM_NAME(lzo1y_decompress_asm_fast);
LZO_EXTERN_CDECL(int)
lzo1y_decompress_asm_fast_safe
                         (const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ )
                        LZO_ASM_NAME(lzo1y_decompress_asm_fast_safe);
#else
#  define lzo1y_decompress_asm				0
#  define lzo1y_decompress_asm_safe			0
#  define lzo1y_decompress_asm_fast			0
#  define lzo1y_decompress_asm_fast_safe	0
#endif


/*
vi:ts=4:et
*/

