/**************
** Structure **
**************/
#pragma pack(push, 1)
struct zip_header_t
{
    DWORD signature;
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

struct zip_eod_t
{
    DWORD signature;
    WORD disk_no;
    WORD disk_dirst;
    WORD disk_dir_entries;
    WORD dir_entries;
    DWORD dir_size;
    DWORD dir_offs;
    WORD comment_len;
};

struct zip_dir_t
{
    DWORD signature;
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

/*************
** Function **
*************/
zip_store(char *in, char *out, char *store_as);