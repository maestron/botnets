/* lpack.c -- LZO example program: a simple file packer

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
// NOTE: this is an example program, so do not use to backup your data
//
// This program lacks things like sophisticated file handling but is
// pretty complete regarding compression - it should provide a good
// starting point for adaption for you applications.
//
// Please study LZO.FAQ and simple.c first.
**************************************************************************/

#include <lzo1x.h>
#include "lutil.h"

static const char *progname = NULL;

static unsigned long total_in = 0;
static unsigned long total_out = 0;
static lzo_bool debug = 0;

/* magic file header for lpack-compressed files */
static const unsigned char magic[7] =
	{ 0x00, 0xe9, 0x4c, 0x5a, 0x4f, 0xff, 0x1a };


/*************************************************************************
// file IO
**************************************************************************/

lzo_uint xread(FILE *f, lzo_voidp buf, lzo_uint len, lzo_bool allow_eof)
{
	lzo_uint l;

	l = lzo_fread(f,buf,len);
	if (l > len)
	{
		fprintf(stderr,"\nsomething's wrong with your C library !!!\n");
		exit(1);
	}
	if (l != len && !allow_eof)
	{
		fprintf(stderr,"\nread error - premature end of file\n");
		exit(1);
	}
	total_in += l;
	return l;
}

lzo_uint xwrite(FILE *f, const lzo_voidp buf, lzo_uint len)
{
	if (f != NULL && lzo_fwrite(f,buf,len) != len)
	{
		fprintf(stderr,"\nwrite error  (disk full ?)\n");
		exit(1);
	}
	total_out += len;
	return len;
}


int xgetc(FILE *f)
{
	unsigned char c;
	xread(f,(lzo_bytep) &c,1,0);
	return c;
}

void xputc(FILE *f, int c)
{
	unsigned char cc = (unsigned char) c;
	xwrite(f,(lzo_bytep) &cc,1);
}

/* read and write portable 32-bit integers */

lzo_uint32 xread32(FILE *f)
{
	unsigned char b[4];
	lzo_uint32 v;

	xread(f,b,4,0);
	v  = (lzo_uint32) b[3] <<  0;
	v |= (lzo_uint32) b[2] <<  8;
	v |= (lzo_uint32) b[1] << 16;
	v |= (lzo_uint32) b[0] << 24;
	return v;
}

void xwrite32(FILE *f, lzo_uint32 v)
{
	unsigned char b[4];

	b[3] = (unsigned char) (v >>  0);
	b[2] = (unsigned char) (v >>  8);
	b[1] = (unsigned char) (v >> 16);
	b[0] = (unsigned char) (v >> 24);
	xwrite(f,b,4);
}


/*************************************************************************
// compress
//
// possible improvement: we could use overlapping compression to
//   save some memory - see overlap.c. This would require some minor
//   changes in the decompression code as well, because if a block
//   turns out to be incompressible we would still have to store it in its
//   compressed (slightly enlarged) form because the original (uncompressed)
//   data would have been lost during the overlapping compression.
**************************************************************************/

int do_compress(FILE *fi, FILE *fo, int level, lzo_uint block_size)
{
	int r = 0;
	lzo_byte *in = NULL;
	lzo_byte *out = NULL;
	lzo_byte *wrkmem = NULL;
	lzo_uint in_len;
	lzo_uint out_len;
	lzo_uint32 wrk_len = 0;
	lzo_uint32 flags = 1;
	int method = 0x1;
	lzo_uint32 checksum;

	total_in = total_out = 0;

/*
 * Step 1: write magic header, flags & block size, init checksum
 */
 	xwrite(fo,magic,sizeof(magic));
	xwrite32(fo,flags);
	xputc(fo,method);			/* compression method */
	xputc(fo,level);			/* compression level */
	xwrite32(fo,block_size);
	checksum = lzo_adler32(0,NULL,0);

/*
 * Step 2: allocate compression buffers and work-memory
 */
	in = (lzo_bytep) lzo_malloc(block_size);
	out = (lzo_bytep) lzo_malloc(block_size + block_size / 64 + 16 + 3);
#if !defined(LZO_999_UNSUPPORTED)
	if (level == 9)
		wrk_len = LZO1X_999_MEM_COMPRESS;
	else
#endif
		wrk_len = LZO1X_1_MEM_COMPRESS;
	wrkmem = (lzo_bytep) lzo_malloc(wrk_len);
	if (in == NULL || out == NULL || wrkmem == NULL)
	{
		printf("%s: out of memory\n", progname);
		r = 1;
		goto err;
	}

/*
 * Step 3: process blocks
 */
 	for (;;)
	{
		/* read block */
		in_len = xread(fi,in,block_size,1);
		if (in_len <= 0)
			break;

		/* update checksum */
		checksum = lzo_adler32(checksum,in,in_len);

		/* clear wrkmem (not needed, only for debug purposes) */
		if (debug)
			lzo_memset(wrkmem,0xff,wrk_len);

		/* compress block */
#if !defined(LZO_999_UNSUPPORTED)
		if (level == 9)
			r = lzo1x_999_compress(in,in_len,out,&out_len,wrkmem);
		else
#endif
			r = lzo1x_1_compress(in,in_len,out,&out_len,wrkmem);
		if (r != LZO_E_OK || out_len > in_len + in_len / 64 + 16 + 3)
		{
			/* this should NEVER happen */
			printf("internal error - compression failed: %d\n", r);
			r = 2;
			goto err;
		}

		/* write uncompressed block size */
		xwrite32(fo,in_len);

		if (out_len < in_len)
		{
			/* write compressed block */
			xwrite32(fo,out_len);
			xwrite(fo,out,out_len);
		}
		else
		{
			/* not compressible - write uncompressed block */
			xwrite32(fo,in_len);
			xwrite(fo,in,in_len);
		}
	}

	/* write EOF marker */
	xwrite32(fo,0);

	/* write checksum */
	xwrite32(fo,checksum);

	r = 0;
err:
	lzo_free(wrkmem);
	lzo_free(out);
	lzo_free(in);
	return r;
}


/*************************************************************************
// decompress / test
//
// We are using overlapping (in-place) decompression to save some
// memory - see overlap.c.
**************************************************************************/

int do_decompress(FILE *fi, FILE *fo)
{
	int r = 0;
	lzo_byte *buf = NULL;
	lzo_uint buf_len;
	unsigned char m [ sizeof(magic) ];
	lzo_uint32 flags;
	int method;
	int level;
	lzo_uint block_size;
	lzo_uint32 checksum;

	total_in = total_out = 0;

/*
 * Step 1: check magic header, read flags & block size, init checksum
 */
 	if (xread(fi,m,sizeof(magic),1) != sizeof(magic) ||
	    memcmp(m,magic,sizeof(magic)) != 0)
    {
		printf("%s: header error - this file is not compressed by lpack\n", progname);
		r = 1;
		goto err;
	}
	flags = xread32(fi);
	method = xgetc(fi);
	level = xgetc(fi);
	if (method != 1)
	{
		printf("%s: header error - invalid method %d (level %d)\n",
		        progname, method, level);
		r = 2;
		goto err;
	}
	block_size = xread32(fi);
	if (block_size < 1024 || block_size > 1024*1024L)
	{
		printf("%s: header error - invalid block size %ld\n",
		        progname, (long) block_size);
		r = 3;
		goto err;
	}
	checksum = lzo_adler32(0,NULL,0);

/*
 * Step 2: allocate buffer for in-place decompression
 */
	buf_len = block_size + block_size / 64 + 16 + 3;
	buf = (lzo_bytep) lzo_malloc(buf_len);
	if (buf == NULL)
	{
		printf("%s: out of memory\n", progname);
		r = 4;
		goto err;
	}

/*
 * Step 3: process blocks
 */
 	for (;;)
	{
		lzo_byte *in;
		lzo_byte *out;
		lzo_uint in_len;
		lzo_uint out_len;

		/* read uncompressed size */
		out_len = xread32(fi);

		/* exit if last block (EOF marker) */
		if (out_len == 0)
			break;

		/* read compressed size */
		in_len = xread32(fi);

		/* sanity check of the size values */
		if (in_len > block_size || out_len > block_size ||
		    in_len == 0 || in_len > out_len)
		{
			printf("%s: block size error - data corrupted\n", progname);
			r = 5;
			goto err;
		}

		/* place compressed block at the top of the buffer */
 		in = buf + buf_len - in_len;
 		out = buf;

		/* read compressed block data */
		xread(fi,in,in_len,0);

		if (in_len < out_len)
		{
			/* decompress - use safe decompressor as data might be corrupted
			 * during a file transfer */
			lzo_uint new_len = out_len;

			r = lzo1x_decompress_safe(in,in_len,out,&new_len,NULL);
			if (r != LZO_E_OK || new_len != out_len)
			{
				printf("%s: compressed data violation\n", progname);
				r = 6;
				goto err;
			}
			/* write decompressed block */
			xwrite(fo,out,out_len);
			/* update checksum */
			if (flags & 1)
				checksum = lzo_adler32(checksum,out,out_len);
		}
		else
		{
			/* write original (incompressible) block */
			xwrite(fo,in,in_len);
			/* update checksum */
			if (flags & 1)
				checksum = lzo_adler32(checksum,in,in_len);
		}
	}

	/* read and verify checksum */
	if (flags & 1)
	{
		lzo_uint32 c = xread32(fi);
		if (c != checksum)
		{
			printf("%s: checksum error - data corrupted\n", progname);
			r = 7;
			goto err;
		}
	}

	r = 0;
err:
	lzo_free(buf);
	return r;
}


/*************************************************************************
//
**************************************************************************/

static void usage(void)
{
	printf("usage: %s [-9] input-file output-file  (compress)\n", progname);
	printf("usage: %s -d   input-file output-file  (decompress)\n", progname);
	printf("usage: %s -t   input-file...           (test)\n", progname);
	exit(1);
}


/* open input file */
static FILE *xopen_fi(const char *name)
{
	FILE *f;

	f = fopen(name,"rb");
	if (f == NULL)
	{
		printf("%s: cannot open input file %s\n", progname, name);
		exit(1);
	}
#if defined(HAVE_STAT) && defined(S_ISREG)
	{
		struct stat st;
#if defined(HAVE_LSTAT)
		if (lstat(name,&st) != 0 || !S_ISREG(st.st_mode))
#else
		if (stat(name,&st) != 0 || !S_ISREG(st.st_mode))
#endif
		{
			printf("%s: %s is not a regular file\n", progname, name);
			fclose(f);
			exit(1);
		}
	}
#endif
	return f;
}


/* open output file */
static FILE *xopen_fo(const char *name)
{
	FILE *f;

#if 1
	/* this is an example program, so make sure we don't overwrite a file */
	f = fopen(name,"rb");
	if (f != NULL)
	{
		printf("%s: file %s already exists -- not overwritten\n", progname, name);
		fclose(f);
		exit(1);
	}
#endif
	f = fopen(name,"wb");
	if (f == NULL)
	{
		printf("%s: cannot open output file %s\n", progname, name);
		exit(1);
	}
	return f;
}


/*************************************************************************
//
**************************************************************************/

int main(int argc, char *argv[])
{
	int i = 1;
	int r = 0;
	FILE *fi = NULL;
	FILE *fo = NULL;
	const char *in_name = NULL;
	const char *out_name = NULL;
	lzo_bool opt_decompress = 0;
	lzo_bool opt_test = 0;
	int opt_level = 1;
	lzo_uint opt_block_size = (256*1024L);

#if defined(__EMX__)
	_response(&argc,&argv);
	_wildcard(&argc,&argv);
#endif

	printf("\nLZO real-time data compression library (v%s, %s).\n",
	        lzo_version_string(), lzo_version_date());
	printf("Copyright (C) 1996-2002 Markus Franz Xaver Johannes Oberhumer\n\n");

	printf(
"*** DISCLAIMER ***\n"
"   This is an example program, do not use to backup your data !\n"
"   Get LZOP if you're interested into a full-featured packer.\n"
"   See http://www.oberhumer.com/opensource/lzop/\n"
"\n");

	progname = argv[0];
	while (i < argc && argv[i][0] == '-')
	{
		if (strcmp(argv[i],"-d") == 0)
			opt_decompress = 1;
		else if (strcmp(argv[i],"-t") == 0)
			opt_test = 1;
#if !defined(LZO_999_UNSUPPORTED)
		else if (strcmp(argv[i],"-9") == 0)
			opt_level = 9;
#endif
		else if (argv[i][1] == 'b' && argv[i][2])
		{
#if (LZO_UINT_MAX > UINT_MAX) && defined(HAVE_ATOL)
			lzo_int b = atol(&argv[i][2]);
#else
			lzo_int b = atoi(&argv[i][2]);
#endif
			if (b >= 1024L && b <= 1024*1024L)
				opt_block_size = b;
		}
		else if (strcmp(argv[i],"--debug") == 0)
			debug = 1;
		else
			usage();
		i++;
	}
	if (opt_test && i >= argc)
		usage();
	if (!opt_test && i + 2 != argc)
		usage();

/*
 * Step 1: initialize the LZO library
 */
	if (lzo_init() != LZO_E_OK)
	{
		printf("lzo_init() failed !!!\n");
		exit(1);
	}

/*
 * Step 2: process file
 */
 	if (opt_test)
	{
		while (i < argc && r == 0)
		{
 			in_name = argv[i++];
			fi = xopen_fi(in_name);
			r = do_decompress(fi,NULL);
			if (r == 0)
				printf("%s: %s tested ok (%ld -> %ld bytes)\n",
			        	progname, in_name, total_in, total_out);
			fclose(fi);
			fi = NULL;
		}
	}
 	else if (opt_decompress)
	{
 		in_name = argv[i++];
 		out_name = argv[i++];
		fi = xopen_fi(in_name);
		fo = xopen_fo(out_name);
		r = do_decompress(fi,fo);
		if (r == 0)
			printf("%s: decompressed %ld into %ld bytes\n",
			        progname, total_in, total_out);
	}
	else
	{
 		in_name = argv[i++];
 		out_name = argv[i++];
		fi = xopen_fi(in_name);
		fo = xopen_fo(out_name);
		r = do_compress(fi,fo,opt_level,opt_block_size);
		if (r == 0)
			printf("%s: compressed %ld into %ld bytes\n",
			        progname, total_in, total_out);
	}

	if (fi) fclose(fi);
	if (fo) fclose(fo);
	return r;
}

/*
vi:ts=4
*/

