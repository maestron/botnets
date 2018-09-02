/*  ya.bot  */

#ifndef NO_INSTALLWORMRIDE

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original module by ???
//29A-8\Utilities\29A-8.009
//botbotbotbotbotbotbotbotbotbotbotbotbot

#include <string.h>

/* XDE v1.02 eXtended length disassembler engine, based on LDE/ADE engines */

#ifndef __XDE_H__
#define __XDE_H__

/* table indexes */

#define TBL_NORMAL 0             /* table index: normal opcodes             */
#define TBL_0F     256           /* table index: 0F-prefixed opcodes        */
#define TBL_80_83  512           /* table index: 80/81/82/83 /ttt           */
#define TBL_F6     520           /* table index: F6 /ttt                    */
#define TBL_F7     528           /* table index: F7 /ttt                    */
#define TBL_FE     536           /* table index: FE /ttt                    */
#define TBL_FF     544           /* table index: FF /ttt                    */
#define TBL_max    552              /* total entries in the xde_table[]        */
#define TBL_size   (TBL_max*4)   /* total xde_table[] size, in BYTEs        */

/* instruction flags */

#define C_SPECIAL  0             /* NOT A FLAG, must be zero                */
#define C_ADDR1    0x00000001    /* }                                       */
#define C_ADDR2    0x00000002    /* } when OR'ed, we have total addr size   */
#define C_ADDR4    0x00000004    /* }                                       */
#define C_MODRM    0x00000008    /* there is MOD<reg|ttt>R/M                */
#define C_SIB      0x00000010    /* there is SIB                            */
#define C_ADDR67   0x00000020    /* address size = defaddr                  */
#define C_DATA66   0x00000040    /* data size = defdata                     */
#define C_UNDEF    0x00000080    /* register values become UNDEFINED        */
#define C_DATA1    0x00000100    /* }                                       */
#define C_DATA2    0x00000200    /* } when OR'ed, we have total data size   */
#define C_DATA4    0x00000400    /* }                                       */
#define C_BAD      0x00000800    /* "bad", i.e. rarely used instruction     */
#define C_REL      0x00001000    /* it is jxx/call/...                      */
#define C_STOP     0x00002000    /* it is ret/jmp/...                       */
#define C_OPSZ8    0x00004000    /* operand size is 8 bits, otherwise 16/32 */
#define C_SRC_FL   0x00008000    /* put XSET_FL to src_set                  */
#define C_DST_FL   0x00010000    /* put XSET_FL to dst_set                  */
#define C_MOD_FL   (C_SRC_FL+C_DST_FL)
#define C_SRC_REG  0x00020000    /* src_set |= f(REG)                       */
#define C_DST_REG  0x00080000    /* dst_set |= f(REG)                       */
#define C_MOD_REG  (C_SRC_REG+C_DST_REG)
#define C_SRC_RM   0x00040000    /* src_set |= f(R/M)  can be used w/o modrm*/
#define C_DST_RM   0x00100000    /* dst_set |= f(R/M)  can be used w/o modrm*/
#define C_MOD_RM   (C_SRC_RM+C_DST_RM)
#define C_SRC_ACC  0x00200000    /* src_set |= XSET_AL || AX || EAX         */
#define C_DST_ACC  0x00400000    /* dst_set |= XSET_AL || AX || EAX         */
#define C_MOD_ACC  (C_SRC_ACC+C_DST_ACC)
#define C_SRC_R0   0x00800000    /* src_set |= f(opcode & 0x07)             */
#define C_DST_R0   0x01000000    /* dst_set |= f(opcode & 0x07)             */
#define C_MOD_R0   (C_SRC_R0+C_DST_R0)
#define C_PUSH     0x02000000    /* dst_set |= XSET_ESP | XSET_MEM          */
#define C_POP      0x04000000    /* dst_set |= XSET_ESP, src_set |= XSET_MEM*/
#define C_x_shift  27
#define C_x_00001  0x08000000
#define C_x_00010  0x10000000
#define C_x_00100  0x20000000
#define C_x_01000  0x40000000
#define C_x_10000  0x80000000
#define C_x_mask   0xF8000000
#define C_ERROR    0xFFFFFFFF    /* invalid instruction                     */

#define XDE_CMD(fl)  ((fl) & C_x_mask)      /* extract CMD from flags       */

#define C_CMD_other  ( 0 << C_x_shift)      /* 0=other, used if undefined   */
#define C_CMD_CALL   ( 1 << C_x_shift)
#define C_CMD_xxx    ( 2 << C_x_shift)
#define C_CMD_last   (31 << C_x_shift)

/* "object set", stored into src_set && dst_set */

#define XSET_AL    0x00000001
#define XSET_AH    0x00000002
#define XSET_AX    0x00000003
#define XSET_EAX   0x0000000F
#define XSET_CL    0x00000010
#define XSET_CH    0x00000020
#define XSET_CX    0x00000030
#define XSET_ECX   0x000000F0
#define XSET_DL    0x00000100
#define XSET_DH    0x00000200
#define XSET_DX    0x00000300
#define XSET_EDX   0x00000F00
#define XSET_BL    0x00001000
#define XSET_BH    0x00002000
#define XSET_BX    0x00003000
#define XSET_EBX   0x0000F000
#define XSET_SP    0x00010000
#define XSET_ESP   0x00030000
#define XSET_BP    0x00100000
#define XSET_EBP   0x00300000
#define XSET_SI    0x01000000
#define XSET_ESI   0x03000000
#define XSET_DI    0x10000000
#define XSET_EDI   0x30000000
#define XSET_ALL16 0x11113333
#define XSET_ALL32 0x3333FFFF
#define XSET_FL    0x00040000   /* flags                                    */
#define XSET_MEM   0x00080000   /* memory (any address)                     */
#define XSET_OTHER 0x00400000   /* other registers (seg,fpu,cr*,xmm,...)    */
#define XSET_DEV   0x00800000   /* io-ports                                 */
#define XSET_rsrv1 0x04000000
#define XSET_rsrv2 0x08000000
#define XSET_rsrv3 0x40000000
#define XSET_rsrv4 0x80000000
#define XSET_UNDEF 0xFFFFFFFF   /* all values become undefined              */

#pragma pack(push)
#pragma pack(1)

/* instruction is splitted into this structure by xde_disasm()              */
/* then, instruction can be merged from this structure by xde_asm()         */

struct xde_instr
{
  unsigned char  defaddr;        /* 2 or 4, depends on 0x67 prefix          */
  unsigned char  defdata;        /* 2 or 4, depends on 0x66 prefix          */
  unsigned long  len;            /* total instruction length                */
  unsigned long  flag;           /* set of C_xxx flags                      */
  unsigned long  addrsize;       /* size of address (or 0)                  */
  unsigned long  datasize;       /* size of data (or 0)                     */
  unsigned char  p_lock;         /* 0 or F0                                 */
  unsigned char  p_66;           /* 0 or 66                                 */
  unsigned char  p_67;           /* 0 or 67                                 */
  unsigned char  p_rep;          /* 0 or F2/F3                              */
  unsigned char  p_seg;          /* 0 or 26/2E/36/3E/64/65                  */
  unsigned char  opcode;         /* opcode byte (if 0x0F, opcode2 is set)   */
  unsigned char  opcode2;        /* if opcode==0x0F, contains 2nd opcode    */
  unsigned char  modrm;          /* modr/m byte (if C_MODRM)                */
  unsigned char  sib;            /* sib byte (if C_SIB)                     */
//
// example: add eax, ebx
//
// description        READ   WRITE  formula
//
// source regs        +      ?      src_set                      {eax|ebx}
// destination regs   ?      +      dst_set                      {eax|flags}
// modified regs      +      +      dst_set & src_set            {eax}
// read-only regs     +      -      src_set & ~dst_set           {ebx}
// write-only regs    -      +      dst_set & ~src_set           {flags}
//
  unsigned long  src_set;        /* SRC object set (instr. will READ 'em)   */
  unsigned long  dst_set;        /* DST object set (instr. will WRITE 'em)  */
//
  union
  {
  unsigned char  addr_b[8];      /* address bytes, size = addrsize          */
  unsigned short addr_w[4];
  unsigned long  addr_d[2];
  signed char    addr_c[8];
  signed short   addr_s[4];
  signed long    addr_l[2];
  };
  union
  {
  unsigned char  data_b[8];      /* data (imm) bytes, size = datasize       */
  unsigned short data_w[4];
  unsigned long  data_d[2];
  signed char    data_c[8];
  signed short   data_s[4];
  signed long    data_l[2];
  };
}; /* struct xde_instr */

#pragma pack(pop)

int __cdecl xde_disasm(/* IN */ unsigned char *opcode,
                       /* OUT */ struct xde_instr *diza);

int __cdecl xde_asm(/* OUT */ unsigned char* opcode,
                    /* IN */ struct xde_instr* diza);

#endif /* __XDE_H__ */

/* EOF */

/* XDE v1.02 eXtended length disassembler engine, based on LDE/ADE engines */

/* NOTE: opcodes marked with C_SPECIAL(==0) are also analyzed in the XDE.C */

unsigned long xde_table[ TBL_max ] =
{
          // add modrm
/* 00 */  C_MODRM+C_DST_FL+C_SRC_REG+C_MOD_RM+C_OPSZ8,
/* 01 */  C_MODRM+C_DST_FL+C_SRC_REG+C_MOD_RM,
/* 02 */  C_MODRM+C_DST_FL+C_MOD_REG+C_SRC_RM+C_OPSZ8,
/* 03 */  C_MODRM+C_DST_FL+C_MOD_REG+C_SRC_RM,
          // add al, c8
/* 04 */  C_DATA1+C_DST_FL+C_MOD_ACC+C_OPSZ8,
          // add ax/eax, c16/32
/* 05 */  C_DATA66+C_DST_FL+C_MOD_ACC,
          // push es
/* 06 */  C_BAD+C_PUSH+C_SPECIAL,
          // pop es
/* 07 */  C_BAD+C_POP+C_SPECIAL,
          // or modrm
/* 08 */  C_MODRM+C_DST_FL+C_SRC_REG+C_MOD_RM+C_OPSZ8,
/* 09 */  C_MODRM+C_DST_FL+C_SRC_REG+C_MOD_RM,
/* 0A */  C_MODRM+C_DST_FL+C_MOD_REG+C_SRC_RM+C_OPSZ8,
/* 0B */  C_MODRM+C_DST_FL+C_MOD_REG+C_SRC_RM,
          // or al, c8
/* 0C */  C_DATA1+C_DST_FL+C_MOD_ACC+C_OPSZ8,
          // or ax/eax, c16/32
/* 0D */  C_DATA66+C_DST_FL+C_MOD_ACC,
          // push cs
/* 0E */  C_BAD+C_PUSH+C_SPECIAL,
          // 0F-prefix
/* 0F */  C_SPECIAL,
          // adc modrm
/* 10 */  C_MODRM+C_BAD+C_MOD_FL+C_SRC_REG+C_MOD_RM+C_OPSZ8,
/* 11 */  C_MODRM+      C_MOD_FL+C_SRC_REG+C_MOD_RM,
/* 12 */  C_MODRM+C_BAD+C_MOD_FL+C_MOD_REG+C_SRC_RM+C_OPSZ8,
/* 13 */  C_MODRM+      C_MOD_FL+C_MOD_REG+C_SRC_RM,
          // adc al, c8
/* 14 */  C_DATA1+C_BAD+C_MOD_FL+C_MOD_ACC+C_OPSZ8,
          // adc ax/eax, c16/32
/* 15 */  C_DATA66+C_BAD+C_MOD_FL+C_MOD_ACC,
          // push ss
/* 16 */  C_BAD+C_PUSH+C_SPECIAL,
          // pop ss
/* 17 */  C_BAD+C_POP+C_SPECIAL,
          // sbb modrm
/* 18 */  C_MODRM+C_BAD+C_MOD_FL+C_SRC_REG+C_MOD_RM+C_OPSZ8,
/* 19 */  C_MODRM+      C_MOD_FL+C_SRC_REG+C_MOD_RM,
/* 1A */  C_MODRM+C_BAD+C_MOD_FL+C_MOD_REG+C_SRC_RM+C_OPSZ8,
/* 1B */  C_MODRM+      C_MOD_FL+C_MOD_REG+C_SRC_RM,
          // sbb al, c8
/* 1C */  C_DATA1+C_BAD+C_MOD_FL+C_MOD_ACC+C_OPSZ8,
          // sbb ax/eax, c16/32
/* 1D */  C_DATA66+C_BAD+C_MOD_FL+C_MOD_ACC,
          // push ds
/* 1E */  C_BAD+C_PUSH+C_SPECIAL,
          // pop ds
/* 1F */  C_BAD+C_POP+C_SPECIAL,
          // and modrm
/* 20 */  C_MODRM+C_DST_FL+C_SRC_REG+C_MOD_RM+C_OPSZ8,
/* 21 */  C_MODRM+C_DST_FL+C_SRC_REG+C_MOD_RM,
/* 22 */  C_MODRM+C_DST_FL+C_MOD_REG+C_SRC_RM+C_OPSZ8,
/* 23 */  C_MODRM+C_DST_FL+C_MOD_REG+C_SRC_RM,
          // and al, c8
/* 24 */  C_DATA1+C_DST_FL+C_MOD_ACC+C_OPSZ8,
          // and ax/eax, c16/32
/* 25 */  C_DATA66+C_DST_FL+C_MOD_ACC,
          // es:
/* 26 */  C_BAD+C_SPECIAL,
          // daa
/* 27 */  C_BAD+C_MOD_FL+C_OPSZ8+C_MOD_ACC,
          // sub modrm
/* 28 */  C_MODRM+C_DST_FL+C_SRC_REG+C_MOD_RM+C_OPSZ8,
/* 29 */  C_MODRM+C_DST_FL+C_SRC_REG+C_MOD_RM,
/* 2A */  C_MODRM+C_DST_FL+C_MOD_REG+C_SRC_RM+C_OPSZ8,
/* 2B */  C_MODRM+C_DST_FL+C_MOD_REG+C_SRC_RM,
          // sub al, c8
/* 2C */  C_DATA1+C_DST_FL+C_MOD_ACC+C_OPSZ8,
          // sub ax/eax, c16/32
/* 2D */  C_DATA66+C_DST_FL+C_MOD_ACC,
          // cs:
/* 2E */  C_BAD+C_SPECIAL,
          // das
/* 2F */  C_BAD+C_MOD_FL+C_OPSZ8+C_MOD_ACC,
          // xor modrm
/* 30 */  C_MODRM+C_DST_FL+C_SRC_REG+C_MOD_RM+C_OPSZ8,
/* 31 */  C_MODRM+C_DST_FL+C_SRC_REG+C_MOD_RM,
/* 32 */  C_MODRM+C_DST_FL+C_MOD_REG+C_SRC_RM+C_OPSZ8,
/* 33 */  C_MODRM+C_DST_FL+C_MOD_REG+C_SRC_RM,
          // xor al, c8
/* 34 */  C_DATA1+C_DST_FL+C_MOD_ACC+C_OPSZ8,
          // xor ax/eax, c16/32
/* 35 */  C_DATA66+C_DST_FL+C_MOD_ACC,
          // ss:
/* 36 */  C_BAD+C_SPECIAL,
          // aaa
/* 37 */  C_BAD+C_MOD_FL+C_OPSZ8+C_MOD_ACC+C_SPECIAL,
          // cmp modrm
/* 38 */  C_MODRM+C_DST_FL+C_SRC_REG+C_SRC_RM+C_OPSZ8,
/* 39 */  C_MODRM+C_DST_FL+C_SRC_REG+C_SRC_RM,
/* 3A */  C_MODRM+C_DST_FL+C_SRC_REG+C_SRC_RM+C_OPSZ8,
/* 3B */  C_MODRM+C_DST_FL+C_SRC_REG+C_SRC_RM,
          // cmp al, c8
/* 3C */  C_DATA1+C_DST_FL+C_SRC_ACC+C_OPSZ8,
          // cmp ax, c16/32
/* 3D */  C_DATA66+C_DST_FL+C_SRC_ACC,
          // ds:
/* 3E */  C_BAD+C_SPECIAL,
          // aas
/* 3F */  C_BAD+C_MOD_FL+C_OPSZ8+C_MOD_ACC+C_SPECIAL,
          // inc ax/eax
/* 40 */  0+C_MOD_FL+C_MOD_R0,
/* 41 */  0+C_MOD_FL+C_MOD_R0,
/* 42 */  0+C_MOD_FL+C_MOD_R0,
/* 43 */  0+C_MOD_FL+C_MOD_R0,
/* 44 */  C_BAD+C_MOD_FL+C_MOD_R0,
/* 45 */  0+C_MOD_FL+C_MOD_R0,
/* 46 */  0+C_MOD_FL+C_MOD_R0,
          // inc di/edi
/* 47 */  0+C_MOD_FL+C_MOD_R0,
          // dec ax/eax
/* 48 */  0+C_MOD_FL+C_MOD_R0,
/* 49 */  0+C_MOD_FL+C_MOD_R0,
/* 4A */  0+C_MOD_FL+C_MOD_R0,
/* 4B */  0+C_MOD_FL+C_MOD_R0,
/* 4C */  C_BAD+C_MOD_FL+C_MOD_R0,
/* 4D */  0+C_MOD_FL+C_MOD_R0,
/* 4E */  0+C_MOD_FL+C_MOD_R0,
          // dec di/edi
/* 4F */  0+C_MOD_FL+C_MOD_R0,
          // push ax/eax
/* 50 */  0+C_PUSH+C_SRC_R0,
/* 51 */  0+C_PUSH+C_SRC_R0,
/* 52 */  0+C_PUSH+C_SRC_R0,
/* 53 */  0+C_PUSH+C_SRC_R0,
/* 54 */  0+C_PUSH+C_SRC_R0,
/* 55 */  0+C_PUSH+C_SRC_R0,
/* 56 */  0+C_PUSH+C_SRC_R0,
          // push di/edi
/* 57 */  0+C_PUSH+C_SRC_R0,
          // pop ax/eax
/* 58 */  0+C_POP+C_DST_R0,
/* 59 */  0+C_POP+C_DST_R0,
/* 5A */  0+C_POP+C_DST_R0,
/* 5B */  0+C_POP+C_DST_R0,
/* 5C */  C_BAD+C_POP+C_DST_R0,
/* 5D */  0+C_POP+C_DST_R0,
/* 5E */  0+C_POP+C_DST_R0,
          // pop di/edi
/* 5F */  0+C_POP+C_DST_R0,
          // pusha/pushad
/* 60 */  C_BAD+C_PUSH+C_SPECIAL,
          // popa/popad
/* 61 */  C_BAD+C_POP+C_SPECIAL,
          // bound
/* 62 */  C_MODRM+C_BAD+C_UNDEF,
          // arpl
/* 63 */  C_MODRM+C_BAD+C_UNDEF,
          // fs:
/* 64 */  C_SPECIAL,
          // gs:
/* 65 */  C_BAD+C_SPECIAL,
          // 66-prefix
/* 66 */  C_SPECIAL,
          // 67-prefix
/* 67 */  C_SPECIAL,
          // push c16/32
/* 68 */  C_DATA66+C_PUSH,
          // imul r,r,c16/32
/* 69 */  C_MODRM+C_DATA66+C_DST_FL+C_MOD_REG+C_SRC_RM,
          // push c8
/* 6A */  C_DATA1+C_PUSH,
          // imul r,r,c8
/* 6B */  C_MODRM+C_DATA1+C_DST_FL+C_MOD_REG+C_SRC_RM,
          // insb
/* 6C */  C_BAD+C_SRC_FL+C_DST_RM+C_SPECIAL,
          // insd
/* 6D */  C_BAD+C_SRC_FL+C_DST_RM+C_SPECIAL,
          // outsb
/* 6E */  C_BAD+C_SRC_FL+C_SRC_RM+C_SPECIAL,
          // outsd
/* 6F */  C_BAD+C_SRC_FL+C_SRC_RM+C_SPECIAL,
          // jxx short
/* 70 */  C_DATA1+C_REL+C_BAD+C_UNDEF,
/* 71 */  C_DATA1+C_REL+C_BAD+C_UNDEF,
/* 72 */  C_DATA1+C_REL+C_UNDEF,
/* 73 */  C_DATA1+C_REL+C_UNDEF,
/* 74 */  C_DATA1+C_REL+C_UNDEF,
/* 75 */  C_DATA1+C_REL+C_UNDEF,
/* 76 */  C_DATA1+C_REL+C_UNDEF,
/* 77 */  C_DATA1+C_REL+C_UNDEF,
/* 78 */  C_DATA1+C_REL+C_UNDEF,
/* 79 */  C_DATA1+C_REL+C_UNDEF,
/* 7A */  C_DATA1+C_REL+C_BAD+C_UNDEF,
/* 7B */  C_DATA1+C_REL+C_BAD+C_UNDEF,
/* 7C */  C_DATA1+C_REL+C_UNDEF,
/* 7D */  C_DATA1+C_REL+C_UNDEF,
/* 7E */  C_DATA1+C_REL+C_UNDEF,
/* 7F */  C_DATA1+C_REL+C_UNDEF,
          // ttt: 0=add 1=or 2=adc 3=sbb 4=and 5=sub 6=xor 7=cmp
          // ttt [r/m]:8, imm8
/* 80 */  C_MODRM+C_DATA1+C_SPECIAL,
          // ttt [r/m]:16/32, imm16/32
/* 81 */  C_MODRM+C_DATA66+C_SPECIAL,
          // ttt [r/m]:8, imm8
/* 82 */  C_MODRM+C_DATA1+C_BAD+C_SPECIAL,
          // ttt [r/m]:16/32, imm8
/* 83 */  C_MODRM+C_DATA1+C_SPECIAL,
          // test [r/m]:8, r8
/* 84 */  C_MODRM+C_DST_FL+C_SRC_REG+C_SRC_RM+C_OPSZ8,
          // test [r/m]:16/32, r16/32
/* 85 */  C_MODRM+C_DST_FL+C_SRC_REG+C_SRC_RM,
          // xchg [r/m]:8, r8
/* 86 */  C_MODRM+C_MOD_REG+C_MOD_RM+C_OPSZ8,
          // xchg [r/m]:16/32, r16/32
/* 87 */  C_MODRM+C_MOD_REG+C_MOD_RM,
          // mov [r/m]:8, r8
/* 88 */  C_MODRM+C_DST_RM+C_SRC_REG+C_OPSZ8,
          // mov [r/m]:16/32, r16/32
/* 89 */  C_MODRM+C_DST_RM+C_SRC_REG,
          // mov r8, [r/m]:8
/* 8A */  C_MODRM+C_DST_REG+C_SRC_RM+C_OPSZ8,
          // mov r16/32, [r/m]:16/32
/* 8B */  C_MODRM+C_DST_REG+C_SRC_RM,
          // mov [r/m]:16, sreg
/* 8C */  C_MODRM+C_BAD+C_DST_RM+C_SPECIAL,
          // lea r16/32, [r/m]
/* 8D */  C_MODRM+C_DST_REG+C_SRC_RM+C_SPECIAL,
          // mov sreg, [r/m]:16
/* 8E */  C_MODRM+C_BAD+C_DST_RM+C_SPECIAL,
          // pop [r/m]:16/32
/* 8F */  C_MODRM+C_POP+C_DST_RM+C_SPECIAL,
          // nop
/* 90 */  0,
          // xchg ecx, eax
/* 91 */  0+C_MOD_R0+C_MOD_ACC,
/* 92 */  0+C_MOD_R0+C_MOD_ACC,
/* 93 */  C_BAD+C_MOD_R0+C_MOD_ACC,
/* 94 */  C_BAD+C_MOD_R0+C_MOD_ACC,
/* 95 */  C_BAD+C_MOD_R0+C_MOD_ACC,
/* 96 */  C_BAD+C_MOD_R0+C_MOD_ACC,
          // xchg edi, eax
/* 97 */  C_BAD+C_MOD_R0+C_MOD_ACC,
          // cwde
/* 98 */  C_BAD+C_SPECIAL,
          // cdq
/* 99 */  0+C_SPECIAL,
          // call far
/* 9A */  C_DATA66+C_DATA2+C_BAD+C_UNDEF+C_CMD_CALL,
          // fwait
/* 9B */  0+C_UNDEF,                                      /* fpu */
          // pushf
/* 9C */  C_BAD+C_PUSH+C_SRC_FL,
          // popf
/* 9D */  C_BAD+C_POP+C_DST_FL,
          // sahf
/* 9E */  C_BAD+C_DST_FL+C_SPECIAL,
          // lahf
/* 9F */  C_BAD+C_SRC_FL+C_SPECIAL,
          // mov al, [imm8]
/* A0 */  C_ADDR67+C_DST_ACC+C_SRC_RM+C_OPSZ8,
          // mov ax/eax, [imm16/32]
/* A1 */  C_ADDR67+C_DST_ACC+C_SRC_RM,
          // mov [imm8], al
/* A2 */  C_ADDR67+C_SRC_ACC+C_DST_RM+C_OPSZ8,
          // mov [imm16/32], ax/eax
/* A3 */  C_ADDR67+C_SRC_ACC+C_DST_RM,
          // movsb
/* A4 */  0+C_SRC_FL+C_MOD_RM+C_SPECIAL,
          // movsd
/* A5 */  0+C_SRC_FL+C_MOD_RM+C_SPECIAL,
          // cmpsb
/* A6 */  0+C_MOD_FL+C_SRC_RM+C_SPECIAL,
          // cmpsd
/* A7 */  0+C_MOD_FL+C_SRC_RM+C_SPECIAL,
          // test al, c8
/* A8 */  C_DATA1+C_DST_FL+C_SRC_ACC+C_OPSZ8,
          // test ax/eax, c16/32
/* A9 */  C_DATA66+C_DST_FL+C_SRC_ACC,
          // stosb
/* AA */  0+C_SRC_FL+C_DST_RM+C_OPSZ8+C_SRC_ACC+C_SPECIAL,
          // stosd
/* AB */  0+C_SRC_FL+C_DST_RM+C_SRC_ACC+C_SPECIAL,
          // lodsb
/* AC */  0+C_SRC_FL+C_SRC_RM+C_OPSZ8+C_DST_ACC+C_SPECIAL,
          // lodsd
/* AD */  C_BAD+C_SRC_FL+C_SRC_RM+C_DST_ACC+C_SPECIAL,
          // scasb
/* AE */  0+C_SRC_FL+C_DST_FL+C_SRC_RM+C_OPSZ8+C_SRC_ACC+C_SPECIAL,
          // scasd
/* AF */  C_BAD+C_SRC_FL+C_DST_FL+C_SRC_RM+C_SRC_ACC+C_SPECIAL,
          // mov al, c8
/* B0 */  C_DATA1+C_DST_R0+C_OPSZ8,
/* B1 */  C_DATA1+C_DST_R0+C_OPSZ8,
/* B2 */  C_DATA1+C_DST_R0+C_OPSZ8,
/* B3 */  C_DATA1+C_DST_R0+C_OPSZ8,
/* B4 */  C_DATA1+C_DST_R0+C_OPSZ8,
/* B5 */  C_DATA1+C_DST_R0+C_OPSZ8,
/* B6 */  C_DATA1+C_BAD+C_DST_R0+C_OPSZ8,
          // mov bh, c8
/* B7 */  C_DATA1+C_BAD+C_DST_R0+C_OPSZ8,
          // mov ax/eax, c16/32
/* B8 */  C_DATA66+C_DST_R0,
/* B9 */  C_DATA66+C_DST_R0,
/* BA */  C_DATA66+C_DST_R0,
/* BB */  C_DATA66+C_DST_R0,
/* BC */  C_DATA66+C_BAD+C_DST_R0,
/* BD */  C_DATA66+C_DST_R0,
/* BE */  C_DATA66+C_DST_R0,
          // mov di/edi, c16/32
/* BF */  C_DATA66+C_DST_R0,
          // ttt: 0=rol 1=ror 2=rcl 3=rcr 4=shl 5=shr 6=sal 7=sar
          // shift-ttt [r/m]:8, imm8
/* C0 */  C_MODRM+C_DATA1+C_DST_FL+C_DST_RM+C_OPSZ8+C_SPECIAL,
          // shift-ttt [r/m]:16/32, imm8
/* C1 */  C_MODRM+C_DATA1+C_DST_FL+C_DST_RM+C_SPECIAL,
          // retn c16
/* C2 */  C_DATA2+C_STOP+C_UNDEF,
          // retn
/* C3 */  C_STOP+C_UNDEF,
          // les
/* C4 */  C_MODRM+C_BAD+C_DST_REG+C_SRC_RM+C_SPECIAL,
          // lds
/* C5 */  C_MODRM+C_BAD+C_DST_REG+C_SRC_RM+C_SPECIAL,
          // ttt=000, other illegal
          // mov [r/m], imm8
/* C6 */  C_MODRM+C_DST_RM+C_DATA1+C_SPECIAL,
          // mov [r/m], imm16/32
/* C7 */  C_MODRM+C_DST_RM+C_DATA66+C_SPECIAL,
          // enter
/* C8 */  C_DATA2+C_DATA1+C_MOD_RM+C_SPECIAL,
          // leave
/* C9 */  0+C_SRC_RM+C_SPECIAL,
          // retf c16
/* CA */  C_DATA2+C_STOP+C_BAD+C_UNDEF,
          // retf
/* CB */  C_STOP+C_BAD+C_UNDEF,
          // int3
/* CC */  C_BAD,
          // int n
/* CD */  C_DATA1+C_UNDEF,
          // into
/* CE */  C_BAD+C_UNDEF,
          // iret
/* CF */  C_STOP+C_BAD+C_UNDEF,
          // ttt: 0=rol 1=ror 2=rcl 3=rcr 4=shl 5=shr 6=sal 7=sar
          // shift-ttt [r/m]:8, 1
/* D0 */  C_MODRM+C_DST_FL+C_MOD_RM+C_OPSZ8+C_SPECIAL,
          // shift-ttt [r/m]:16/32, 1
/* D1 */  C_MODRM+C_DST_FL+C_MOD_RM+C_SPECIAL,
          // shift-ttt [r/m]:8, cl
/* D2 */  C_MODRM+C_DST_FL+C_MOD_RM+C_OPSZ8+C_SPECIAL,
          // shift-ttt [r/m]:16/32, cl
/* D3 */  C_MODRM+C_DST_FL+C_MOD_RM+C_SPECIAL,
          // aam nn
/* D4 */  C_DATA1+C_BAD+C_DST_FL+C_SPECIAL,
          // aad nn
/* D5 */  C_DATA1+C_BAD+C_DST_FL+C_SPECIAL,
          // setalc
/* D6 */  C_BAD+C_SRC_FL+C_OPSZ8+C_DST_ACC,
          // xlat
/* D7 */  C_BAD+C_OPSZ8+C_MOD_ACC+C_SRC_RM+C_SPECIAL,
/* D8 */  C_MODRM+C_UNDEF,                   /* fpu */
/* D9 */  C_MODRM+C_UNDEF,                   /* fpu */
/* DA */  C_MODRM+C_UNDEF,                   /* fpu */
/* DB */  C_MODRM+C_UNDEF,                   /* fpu */
/* DC */  C_MODRM+C_UNDEF,                   /* fpu */
/* DD */  C_MODRM+C_UNDEF,                   /* fpu */
/* DE */  C_MODRM+C_UNDEF,                   /* fpu */
/* DF */  C_MODRM+C_UNDEF,                   /* fpu */
          // loopne
/* E0 */  C_DATA1+C_REL+C_BAD+C_UNDEF,
          // loope
/* E1 */  C_DATA1+C_REL+C_BAD+C_UNDEF,
          // loop
/* E2 */  C_DATA1+C_REL+C_UNDEF,
          // jecxz
/* E3 */  C_DATA1+C_REL+C_UNDEF,
          // in al, nn
/* E4 */  C_DATA1+C_BAD+C_OPSZ8+C_DST_ACC+C_SPECIAL,
          // in ax/eax, nn
/* E5 */  C_DATA1+C_BAD+C_DST_ACC+C_SPECIAL,
          // out nn, al
/* E6 */  C_DATA1+C_BAD+C_OPSZ8+C_SRC_ACC+C_SPECIAL,
          // out nn, ax/eax
/* E7 */  C_DATA1+C_BAD+C_SRC_ACC+C_SPECIAL,
          // call near
/* E8 */  C_DATA66+C_REL+C_UNDEF+C_CMD_CALL,
          // jmp near
/* E9 */  C_DATA66+C_REL+C_STOP+C_UNDEF,
          // jmp far
/* EA */  C_DATA66+C_DATA2+C_BAD+C_STOP+C_UNDEF,
          // jmp short
/* EB */  C_DATA1+C_REL+C_STOP+C_UNDEF,
          // in al, dx
/* EC */  C_BAD+C_OPSZ8+C_DST_ACC+C_SPECIAL,
          // in ax/eax, dx
/* ED */  C_BAD+C_DST_ACC+C_SPECIAL,
          // out dx, al
/* EE */  C_BAD+C_OPSZ8+C_SRC_ACC+C_SPECIAL,
          // out dx, ax/eax
/* EF */  C_BAD+C_SRC_ACC+C_SPECIAL,
          // lock prefix
/* F0 */  C_BAD+C_SPECIAL,
          //
/* F1 */  C_BAD+C_UNDEF,
          // repne
/* F2 */  C_SPECIAL,
          // repe
/* F3 */  C_SPECIAL,
          // hlt
/* F4 */  C_BAD,
          // cmc
/* F5 */  C_BAD+C_MOD_FL,
          // ttt: 0=test 1=??? 2=not 3=neg 4=mul 5=imul 6=div 7=idiv
/* F6 */  C_MODRM+C_SPECIAL,
/* F7 */  C_MODRM+C_SPECIAL,
          // clc
/* F8 */  0+C_DST_FL,
          // stc
/* F9 */  0+C_DST_FL,
          // cli
/* FA */  C_BAD+C_DST_FL,
          // sti
/* FB */  C_BAD+C_DST_FL,
          // cld
/* FC */  0+C_DST_FL,
          // std
/* FD */  0+C_DST_FL,
          // ttt: 0=inc 1=dec 2=??? 3=??? 4=??? 5=??? 6=??? 7=???
/* FE */  C_MODRM+C_SPECIAL,
          // ttt: 0=inc 1=dec 2=callnear 3=callfar 4=jmpnear 5=jmpfar 6=push 7=???
/* FF */  C_MODRM+C_SPECIAL,

/* 2nd half of the table, 0F-prefixed opcodes */

             // /0=SLDT /1=STR /2=LLDT /3=LTR /4=VERR /5=VERW /6=??? /7=???
/* 0F 00 */  C_MODRM+C_UNDEF,
             // /0=SGDT /1=SIDT /2=LGDT /3=LIDT /4=SMSW /5=??? /6=LMSW /7=INVPLG
/* 0F 01 */  C_MODRM+C_UNDEF,
             // LAR r16/32, [r/m]:16/32
/* 0F 02 */  C_MODRM+C_UNDEF,
             // LSL r16/32, [r/m]:16/32
/* 0F 03 */  C_MODRM+C_UNDEF,
/* 0F 04 */  C_ERROR,
/* 0F 05 */  C_ERROR,
             // CLTS
/* 0F 06 */  C_UNDEF,
/* 0F 07 */  C_ERROR,
             // INVD
/* 0F 08 */  C_UNDEF,
             // WBINVD
/* 0F 09 */  C_UNDEF,
             // ???
/* 0F 0A */  C_UNDEF,
             // UD2
/* 0F 0B */  C_UNDEF,
/* 0F 0C */  C_ERROR,
/* 0F 0D */  C_ERROR,
/* 0F 0E */  C_ERROR,
/* 0F 0F */  C_ERROR,
             //
/* 0F 10 */  C_ERROR,
/* 0F 11 */  C_ERROR,
/* 0F 12 */  C_ERROR,
/* 0F 13 */  C_ERROR,
/* 0F 14 */  C_ERROR,
/* 0F 15 */  C_ERROR,
/* 0F 16 */  C_ERROR,
/* 0F 17 */  C_ERROR,
/* 0F 18 */  C_ERROR,
/* 0F 19 */  C_ERROR,
/* 0F 1A */  C_ERROR,
/* 0F 1B */  C_ERROR,
/* 0F 1C */  C_ERROR,
/* 0F 1D */  C_ERROR,
/* 0F 1E */  C_ERROR,
/* 0F 1F */  C_ERROR,
/* 0F 20 */  C_ERROR,
/* 0F 21 */  C_ERROR,
/* 0F 22 */  C_ERROR,
/* 0F 23 */  C_ERROR,
/* 0F 24 */  C_ERROR,
/* 0F 25 */  C_ERROR,
/* 0F 26 */  C_ERROR,
/* 0F 27 */  C_ERROR,
/* 0F 28 */  C_ERROR,
/* 0F 29 */  C_ERROR,
/* 0F 2A */  C_ERROR,
/* 0F 2B */  C_ERROR,
/* 0F 2C */  C_ERROR,
/* 0F 2D */  C_ERROR,
/* 0F 2E */  C_ERROR,
/* 0F 2F */  C_ERROR,
             // WRMSR
/* 0F 30 */  C_UNDEF,
/* 0F 31 */  C_ERROR,
/* 0F 32 */  C_ERROR,
/* 0F 33 */  C_ERROR,
/* 0F 34 */  C_ERROR,
/* 0F 35 */  C_ERROR,
/* 0F 36 */  C_ERROR,
/* 0F 37 */  C_ERROR,
/* 0F 38 */  C_ERROR,
/* 0F 39 */  C_ERROR,
/* 0F 3A */  C_ERROR,
/* 0F 3B */  C_ERROR,
/* 0F 3C */  C_ERROR,
/* 0F 3D */  C_ERROR,
/* 0F 3E */  C_ERROR,
/* 0F 3F */  C_ERROR,
/* 0F 40 */  C_ERROR,
/* 0F 41 */  C_ERROR,
/* 0F 42 */  C_ERROR,
/* 0F 43 */  C_ERROR,
/* 0F 44 */  C_ERROR,
/* 0F 45 */  C_ERROR,
/* 0F 46 */  C_ERROR,
/* 0F 47 */  C_ERROR,
/* 0F 48 */  C_ERROR,
/* 0F 49 */  C_ERROR,
/* 0F 4A */  C_ERROR,
/* 0F 4B */  C_ERROR,
/* 0F 4C */  C_ERROR,
/* 0F 4D */  C_ERROR,
/* 0F 4E */  C_ERROR,
/* 0F 4F */  C_ERROR,
/* 0F 50 */  C_ERROR,
/* 0F 51 */  C_ERROR,
/* 0F 52 */  C_ERROR,
/* 0F 53 */  C_ERROR,
/* 0F 54 */  C_ERROR,
/* 0F 55 */  C_ERROR,
/* 0F 56 */  C_ERROR,
/* 0F 57 */  C_ERROR,
/* 0F 58 */  C_ERROR,
/* 0F 59 */  C_ERROR,
/* 0F 5A */  C_ERROR,
/* 0F 5B */  C_ERROR,
/* 0F 5C */  C_ERROR,
/* 0F 5D */  C_ERROR,
/* 0F 5E */  C_ERROR,
/* 0F 5F */  C_ERROR,
/* 0F 60 */  C_ERROR,
/* 0F 61 */  C_ERROR,
/* 0F 62 */  C_ERROR,
/* 0F 63 */  C_ERROR,
/* 0F 64 */  C_ERROR,
/* 0F 65 */  C_ERROR,
/* 0F 66 */  C_ERROR,
/* 0F 67 */  C_ERROR,
/* 0F 68 */  C_ERROR,
/* 0F 69 */  C_ERROR,
/* 0F 6A */  C_ERROR,
/* 0F 6B */  C_ERROR,
/* 0F 6C */  C_ERROR,
/* 0F 6D */  C_ERROR,
/* 0F 6E */  C_ERROR,
/* 0F 6F */  C_ERROR,
/* 0F 70 */  C_ERROR,
/* 0F 71 */  C_ERROR,
/* 0F 72 */  C_ERROR,
/* 0F 73 */  C_ERROR,
/* 0F 74 */  C_ERROR,
/* 0F 75 */  C_ERROR,
/* 0F 76 */  C_ERROR,
/* 0F 77 */  C_ERROR,
/* 0F 78 */  C_ERROR,
/* 0F 79 */  C_ERROR,
/* 0F 7A */  C_ERROR,
/* 0F 7B */  C_ERROR,
/* 0F 7C */  C_ERROR,
/* 0F 7D */  C_ERROR,
/* 0F 7E */  C_ERROR,
/* 0F 7F */  C_ERROR,
             // jxx near
/* 0F 80 */  C_DATA66+C_REL+C_UNDEF,
/* 0F 81 */  C_DATA66+C_REL+C_UNDEF,
/* 0F 82 */  C_DATA66+C_REL+C_UNDEF,
/* 0F 83 */  C_DATA66+C_REL+C_UNDEF,
/* 0F 84 */  C_DATA66+C_REL+C_UNDEF,
/* 0F 85 */  C_DATA66+C_REL+C_UNDEF,
/* 0F 86 */  C_DATA66+C_REL+C_UNDEF,
/* 0F 87 */  C_DATA66+C_REL+C_UNDEF,
/* 0F 88 */  C_DATA66+C_REL+C_UNDEF,
/* 0F 89 */  C_DATA66+C_REL+C_UNDEF,
/* 0F 8A */  C_DATA66+C_REL+C_UNDEF,
/* 0F 8B */  C_DATA66+C_REL+C_UNDEF,
/* 0F 8C */  C_DATA66+C_REL+C_UNDEF,
/* 0F 8D */  C_DATA66+C_REL+C_UNDEF,
/* 0F 8E */  C_DATA66+C_REL+C_UNDEF,
/* 0F 8F */  C_DATA66+C_REL+C_UNDEF,
             /* setxx */
/* 0F 90 */  C_MODRM+C_UNDEF,
/* 0F 91 */  C_MODRM+C_UNDEF,
/* 0F 92 */  C_MODRM+C_UNDEF,
/* 0F 93 */  C_MODRM+C_UNDEF,
/* 0F 94 */  C_MODRM+C_UNDEF,
/* 0F 95 */  C_MODRM+C_UNDEF,
/* 0F 96 */  C_MODRM+C_UNDEF,
/* 0F 97 */  C_MODRM+C_UNDEF,
/* 0F 98 */  C_MODRM+C_UNDEF,
/* 0F 99 */  C_MODRM+C_UNDEF,
/* 0F 9A */  C_MODRM+C_UNDEF,
/* 0F 9B */  C_MODRM+C_UNDEF,
/* 0F 9C */  C_MODRM+C_UNDEF,
/* 0F 9D */  C_MODRM+C_UNDEF,
/* 0F 9E */  C_MODRM+C_UNDEF,
/* 0F 9F */  C_MODRM+C_UNDEF,
             // push fs
/* 0F A0 */  C_PUSH+C_SPECIAL,
             // pop fs
/* 0F A1 */  C_POP+C_SPECIAL,
             // cpuid
/* 0F A2 */  C_SPECIAL,
             // bt [r/m]:16/32, r16/32
/* 0F A3 */  C_MODRM+C_DST_FL+C_SRC_REG+C_SRC_RM,
             // shld [r/m]:16/32, r16/32, imm8
/* 0F A4 */  C_MODRM+C_DST_FL+C_DATA1+C_MOD_RM+C_SRC_REG,
             // shld [r/m]:16/32, r16/32, CL
/* 0F A5 */  C_MODRM+C_DST_FL+C_MOD_RM+C_SRC_REG+C_SPECIAL,
/* 0F A6 */  C_ERROR,
/* 0F A7 */  C_ERROR,
             // push gs
/* 0F A8 */  C_PUSH+C_SPECIAL,
             // pop gs
/* 0F A9 */  C_POP+C_SPECIAL,
             // RSM
/* 0F AA */  C_UNDEF,
             // bts [r/m]:16/32, r16/32
/* 0F AB */  C_MODRM+C_DST_FL+C_MOD_RM+C_SRC_REG,
             // shrd [r/m]:16/32, r16/32, imm8
/* 0F AC */  C_MODRM+C_DST_FL+C_DATA1+C_MOD_RM+C_SRC_REG,
             // shrd [r/m]:16/32, r16/32, CL
/* 0F AD */  C_MODRM+C_DST_FL+C_MOD_RM+C_SRC_REG+C_SPECIAL,
/* 0F AE */  C_ERROR,
             // imul r16/32, [r/m]:16/32
/* 0F AF */  C_MODRM+C_DST_FL+C_MOD_REG+C_SRC_RM,
             // cmpxchg [r/m]:8, r8
/* 0F B0 */  C_MODRM+C_DST_FL+C_MOD_RM+C_SRC_REG+C_MOD_ACC+C_OPSZ8,
             // cmpxchg [r/m]:16/32, r16/32
/* 0F B1 */  C_MODRM+C_DST_FL+C_MOD_RM+C_SRC_REG+C_MOD_ACC,
             // lss reg, r/m
/* 0F B2 */  C_MODRM+C_BAD+C_DST_REG+C_SRC_RM+C_SPECIAL,
             // btr [r/m]:16/32, r16/32
/* 0F B3 */  C_MODRM+C_DST_FL+C_MOD_RM+C_SRC_REG,
             // lfs reg, r/m
/* 0F B4 */  C_MODRM+C_BAD+C_DST_REG+C_SRC_RM+C_SPECIAL,
             // lgs reg, r/m
/* 0F B5 */  C_MODRM+C_BAD+C_DST_REG+C_SRC_RM+C_SPECIAL,
             // movzx r16/32, [r/m]:8
/* 0F B6 */  C_MODRM+C_DST_REG+C_SRC_RM,
             // movzx 32, [r/m]:16
/* 0F B7 */  C_MODRM+C_DST_REG+C_SRC_RM,
/* 0F B8 */  C_ERROR,
/* 0F B9 */  C_ERROR,
             // ttt: 1=??? 2=??? 3=??? 4=bt 5=bts 6=btr 7=btc
             // ttt [r/m], imm8
/* 0F BA */  C_MODRM+C_DATA1+C_DST_FL+C_SRC_RM+C_SPECIAL,
             // btc [r/m]:16/32, r16/32
/* 0F BB */  C_MODRM+C_DST_FL+C_MOD_RM+C_SRC_REG,
             // bsf r16/32, [r/m]:16/32
/* 0F BC */  C_MODRM+C_DST_FL+C_DST_REG+C_SRC_RM,
             // bsr r16/32, [r/m]:16/32
/* 0F BD */  C_MODRM+C_DST_FL+C_DST_REG+C_SRC_RM,
             // movsx r16/32, [r/m]:8
/* 0F BE */  C_MODRM+C_DST_REG+C_SRC_RM,
             // movsx r32, [r/m]:16
/* 0F BF */  C_MODRM+C_DST_REG+C_SRC_RM,
             // xadd [r/m]:8, r8
/* 0F C0 */  C_MODRM+C_DST_FL+C_MOD_REG+C_MOD_RM+C_OPSZ8,
             // xadd [r/m]:16/32, r16/32
/* 0F C1 */  C_MODRM+C_DST_FL+C_MOD_REG+C_MOD_RM,
/* 0F C2 */  C_ERROR,
/* 0F C3 */  C_ERROR,
/* 0F C4 */  C_ERROR,
/* 0F C5 */  C_ERROR,
/* 0F C6 */  C_ERROR,
/* 0F C7 */  C_ERROR,
             // BSWAP r32
/* 0F C8 */  C_MOD_R0,
/* 0F C9 */  C_MOD_R0,
/* 0F CA */  C_MOD_R0,
/* 0F CB */  C_MOD_R0,
/* 0F CC */  C_MOD_R0,
/* 0F CD */  C_MOD_R0,
/* 0F CE */  C_MOD_R0,
/* 0F CF */  C_MOD_R0,
/* 0F D0 */  C_ERROR,
/* 0F D1 */  C_ERROR,
/* 0F D2 */  C_ERROR,
/* 0F D3 */  C_ERROR,
/* 0F D4 */  C_ERROR,
/* 0F D5 */  C_ERROR,
/* 0F D6 */  C_ERROR,
/* 0F D7 */  C_ERROR,
/* 0F D8 */  C_ERROR,
/* 0F D9 */  C_ERROR,
/* 0F DA */  C_ERROR,
/* 0F DB */  C_ERROR,
/* 0F DC */  C_ERROR,
/* 0F DD */  C_ERROR,
/* 0F DE */  C_ERROR,
/* 0F DF */  C_ERROR,
/* 0F E0 */  C_ERROR,
/* 0F E1 */  C_ERROR,
/* 0F E2 */  C_ERROR,
/* 0F E3 */  C_ERROR,
/* 0F E4 */  C_ERROR,
/* 0F E5 */  C_ERROR,
/* 0F E6 */  C_ERROR,
/* 0F E7 */  C_ERROR,
/* 0F E8 */  C_ERROR,
/* 0F E9 */  C_ERROR,
/* 0F EA */  C_ERROR,
/* 0F EB */  C_ERROR,
/* 0F EC */  C_ERROR,
/* 0F ED */  C_ERROR,
/* 0F EE */  C_ERROR,
/* 0F EF */  C_ERROR,
/* 0F F0 */  C_ERROR,
/* 0F F1 */  C_ERROR,
/* 0F F2 */  C_ERROR,
/* 0F F3 */  C_ERROR,
/* 0F F4 */  C_ERROR,
/* 0F F5 */  C_ERROR,
/* 0F F6 */  C_ERROR,
/* 0F F7 */  C_ERROR,
/* 0F F8 */  C_ERROR,
/* 0F F9 */  C_ERROR,
/* 0F FA */  C_ERROR,
/* 0F FB */  C_ERROR,
/* 0F FC */  C_ERROR,
/* 0F FD */  C_ERROR,
/* 0F FE */  C_ERROR,
/* 0F FF */  C_ERROR,

/* additional tables, added in XDE */

                /* ttt: 0=add 1=or 2=adc 3=sbb 4=and 5=sub 6=xor 7=cmp */
                /* x=0..3 */
/* 8x /0 */  C_DST_FL+C_MOD_RM,
/* 8x /1 */  C_DST_FL+C_MOD_RM,
/* 8x /2 */  C_MOD_FL+C_MOD_RM,
/* 8x /3 */  C_MOD_FL+C_MOD_RM,
/* 8x /4 */  C_DST_FL+C_MOD_RM,
/* 8x /5 */  C_DST_FL+C_MOD_RM,
/* 8x /6 */  C_DST_FL+C_MOD_RM,
/* 8x /7 */  C_DST_FL+C_SRC_RM,
                /* ttt: 0=test 1=??? 2=not 3=neg 4=mul 5=imul 6=div 7=idiv */
/* F6 /0 */  C_DATA1+C_DST_FL+C_SRC_RM,
/* F6 /1 */  C_BAD,
/* F6 /2 */  C_DST_FL+C_MOD_RM,
/* F6 /3 */  C_DST_FL+C_MOD_RM,
/* F6 /4 */  C_DST_FL+C_SRC_RM+C_SPECIAL,
/* F6 /5 */  C_DST_FL+C_SRC_RM+C_SPECIAL,
/* F6 /6 */  C_DST_FL+C_SRC_RM+C_SPECIAL,
/* F6 /7 */  C_DST_FL+C_SRC_RM+C_SPECIAL,
                /* ttt: 0=test 1=??? 2=not 3=neg 4=mul 5=imul 6=div 7=idiv */
/* F7 /0 */  C_DATA66+C_DST_FL+C_SRC_RM,
/* F7 /1 */  C_BAD,
/* F7 /2 */  C_DST_FL+C_MOD_RM,
/* F7 /3 */  C_DST_FL+C_MOD_RM,
/* F7 /4 */  C_DST_FL+C_SRC_RM+C_SPECIAL,
/* F7 /5 */  C_DST_FL+C_SRC_RM+C_SPECIAL,
/* F7 /6 */  C_DST_FL+C_SRC_RM+C_SPECIAL,
/* F7 /7 */  C_DST_FL+C_SRC_RM+C_SPECIAL,
                /* ttt: 0=inc 1=dec 2=??? 3=??? 4=??? 5=??? 6=??? 7=??? */
/* FE /0 */  C_MOD_FL+C_MOD_RM,
/* FE /1 */  C_MOD_FL+C_MOD_RM,
/* FE /2 */  C_BAD,
/* FE /3 */  C_BAD,
/* FE /4 */  C_BAD,
/* FE /5 */  C_BAD,
/* FE /6 */  C_BAD,
/* FE /7 */  C_BAD,
             /* ttt: 0=inc 1=dec 2=callnear 3=callfar 4=jmpnear 5=jmpfar 6=push 7=??? */
/* FF /0 */  C_MOD_FL+C_MOD_RM,
/* FF /1 */  C_MOD_FL+C_MOD_RM,
/* FF /2 */  C_UNDEF+C_CMD_CALL,
/* FF /3 */  C_UNDEF+C_CMD_CALL,
/* FF /4 */  C_STOP+C_UNDEF,
/* FF /5 */  C_STOP+C_UNDEF,
/* FF /6 */  C_PUSH+C_SRC_RM,
/* FF /7 */  C_BAD

}; /* unsigned long xde_table[512] */

/* EOF */

/* XDE v1.02 eXtended length disassembler engine, based on LDE/ADE engines */

#define XDE32_DEFAULT_ADDR      32      /* 16 or 32, changed by 0x67 prefix */
#define XDE32_DEFAULT_DATA      32      /* 16 or 32, changed by 0x66 prefix */

unsigned long /*__inline*/ reg2xset(int reg_sz /*1,2,4*/, unsigned long reg)
{
  if (reg_sz == 1)
    return reg == 0 ? XSET_AL :
           reg == 1 ? XSET_CL :
           reg == 2 ? XSET_DL :
           reg == 3 ? XSET_BL :
           reg == 4 ? XSET_AH :
           reg == 5 ? XSET_CH :
           reg == 6 ? XSET_DH :
                      XSET_BH;
  else
  if (reg_sz == 2)
    return reg == 0 ? (XSET_AX|XSET_AL|XSET_AH) :
           reg == 1 ? (XSET_CX|XSET_CL|XSET_CH) :
           reg == 2 ? (XSET_DX|XSET_DL|XSET_DH) :
           reg == 3 ? (XSET_BX|XSET_BL|XSET_BH) :
           reg == 4 ? XSET_SP :
           reg == 5 ? XSET_BP :
           reg == 6 ? XSET_SI :
                      XSET_DI;
  else /* if (reg_sz == 4) */
    return reg == 0 ? (XSET_EAX|XSET_AX|XSET_AL|XSET_AH) :
           reg == 1 ? (XSET_ECX|XSET_CX|XSET_CL|XSET_CH) :
           reg == 2 ? (XSET_EDX|XSET_DX|XSET_DL|XSET_DH) :
           reg == 3 ? (XSET_EBX|XSET_BX|XSET_BL|XSET_BH) :
           reg == 4 ? (XSET_ESP|XSET_SP) :
           reg == 5 ? (XSET_EBP|XSET_BP) :
           reg == 6 ? (XSET_ESI|XSET_SI) :
                      (XSET_EDI|XSET_DI);
} /* reg2xset() */

/* returns:                                                                 */
/*   0 if error                                                             */
/*   instruction length (== diza.len) if OK                                 */

int __cdecl xde_disasm(/* IN */ unsigned char *opcode,
                       /* OUT */ struct xde_instr *diza)
{
  unsigned char c, *p;
  unsigned long flag, a, d, i, xset;
  unsigned long mod, reg, rm, index, base;

  p = opcode;

  memset(diza, 0x00, sizeof(struct xde_instr));

  diza->defdata = XDE32_DEFAULT_ADDR/8;
  diza->defaddr = XDE32_DEFAULT_DATA/8;

  flag = 0;

  if (*(unsigned short*)p == 0x0000) flag |= C_BAD;
  if (*(unsigned short*)p == 0xFFFF) flag |= C_BAD;

  while(1)
  {

    c = *p++;

    if (c == 0x66)
    {
      if (diza->p_66 != 0) flag |= C_BAD;        /* twice */
      diza->p_66 = 0x66;
      diza->defdata = (XDE32_DEFAULT_DATA^32^16)/8;
      continue;
    }

    if (c == 0x67)
    {
      if (diza->p_67 != 0) flag |= C_BAD;        /* twice */
      diza->p_67 = 0x67;
      diza->defaddr = (XDE32_DEFAULT_ADDR^32^16)/8;
      continue;
    }

    if ((c == 0x26) || (c == 0x2E) || (c == 0x36) || (c == 0x3E) ||
        (c == 0x64) || (c == 0x65))
    {
      if (diza->p_seg != 0) flag |= C_BAD;       /* twice */
      diza->p_seg = c;
      continue;
    }

    if ((c == 0xF2) || (c == 0xF3))
    {
      if (diza->p_rep != 0) flag |= C_BAD;       /* twice */
      diza->p_rep = c;
      continue;
    }

    if (c == 0xF0)
    {
      if (diza->p_lock != 0) flag |= C_BAD;      /* twice */
      diza->p_lock = c;
      continue;
    }

    break;

  } /* do while prefix found */

  /* check after all prefixes, because 66 and F2/F3 can be swapped */
  if (diza->p_rep)
  {
    xset = XSET_FL | (diza->defdata == 2 ? XSET_CX : XSET_ECX);
    diza->src_set |= xset;
    diza->dst_set |= xset;
  }

  /* instruction flags by opcode */
  flag |= xde_table[ TBL_NORMAL + c ];

  if (flag == C_ERROR) return 0;

  diza->opcode = c;

  if (c == 0x0F)
  {
    c = *p++;

    /* 2nd opcode */

    flag |= xde_table[ TBL_0F + c ]; /* from the 2nd half of the table */

    if (flag == C_ERROR) return 0;

    diza->opcode2 = c;

    /* 0F-prefixed "special" opcodes */

    if ( (c == 0xB2) || (c == 0xB4) || (c == 0xB5) || /* lss/lfs/lgs reg,r/m */
         (c == 0xA1) || (c == 0xA9) )                 /* pop fs, gs */
      diza->dst_set |= XSET_OTHER;

    if ((c == 0xA0) || (c == 0xA8))  /* push fs, gs */
      diza->src_set |= XSET_OTHER;

    if (c == 0xA2) /* cpuid */
    {
      diza->src_set |= XSET_EAX;
      diza->dst_set |= XSET_EAX|XSET_EBX|XSET_ECX|XSET_EDX;
    }

    if ((c == 0xA5) || (c == 0xAD))   /* shld/shrd r/m, reg, CL */
      diza->src_set |= XSET_CL;

  }
  else
  {
    /* "special" opcodes */

    if ((c == 0xA4) || (c == 0xA5) || /* movsb, movsd */
        (c == 0xA6) || (c == 0xA7))   /* cmpsb, cmpsd */
    {
      /* 66 or 67 ? */
      xset = diza->defaddr == 2 ? (XSET_SI | XSET_DI) : (XSET_ESI | XSET_EDI);
      diza->src_set |= xset;
      diza->dst_set |= xset;
    }

    if ((c == 0xAC) || (c == 0xAD)) /* lodsb, lodsd */
    {
      xset = diza->defaddr == 2 ? XSET_SI : XSET_ESI;
      diza->src_set |= xset;
      diza->dst_set |= xset;
    }

    if ((c == 0xAA) || (c == 0xAB) || /* stosb, stosd */
        (c == 0xAE) || (c == 0xAF))   /* scasb, scasd */
    {
      xset = diza->defaddr == 2 ? XSET_DI : XSET_EDI;
      diza->src_set |= xset;
      diza->dst_set |= xset;
    }

    if ((c == 0x6C) || (c == 0x6D)) /* insb, insd */
    {
      /* 66/67 ? */
      xset = XSET_DEV | (diza->defaddr == 2 ? XSET_DI : XSET_EDI);
      diza->src_set |= xset | XSET_DX;
      diza->dst_set |= xset;
    }
    if ((c == 0x6E) || (c == 0x6F)) /* outsb, outsd */
    {
      xset = XSET_DEV | (diza->defaddr == 2 ? XSET_SI : XSET_ESI);
      diza->src_set |= xset | XSET_DX;
      diza->dst_set |= xset;
    }

    if (c == 0x9E) /* sahf */
      diza->src_set |= XSET_AH;
    if (c == 0x9F) /* lahf */
      diza->dst_set |= XSET_AH;

    if (c == 0x98) /* cbw, cwde */
    {
      diza->src_set |= diza->defdata == 2 ? XSET_AL : XSET_AX;
      diza->dst_set |= diza->defdata == 2 ? XSET_AX : XSET_EAX;
    }
    if (c == 0x99) /* cwd, cdq */
    {
      diza->src_set |= diza->defdata == 2 ? XSET_AX : XSET_EAX;
      diza->dst_set |= diza->defdata == 2 ? XSET_DX : XSET_EDX;
    }

    if ((c == 0x37) || (c == 0x3F)) /* aaa, aas */
    {
      diza->src_set |= XSET_AH;
      diza->dst_set |= XSET_AH;
    }

    if ((c == 0xD4) || (c == 0xD5)) /* aam xx, aad xx */
    {
      diza->src_set |= c == 0xD4 ? XSET_AL : XSET_AX;
      diza->dst_set |= XSET_AX;
    }

    if (c == 0x60) /* pusha */
      diza->src_set |= diza->defdata == 2 ? XSET_ALL16 : XSET_ALL32;
    if (c == 0x61) /* popa */
      diza->dst_set |= diza->defdata == 2 ? XSET_ALL16 : XSET_ALL32;

    if ((c == 0xE4) || (c == 0xE5) || /* in al|(e)ax, NN */
        (c == 0xE6) || (c == 0xE7))   /* out NN, al|(e)ax */
    {
      /* 66,67 ? */
      diza->src_set |= XSET_DEV;
      diza->dst_set |= XSET_DEV;
    }

    if ((c == 0xEC) || (c == 0xED)) /* in al|(e)ax, dx */
    {
      /* 66,67 ? */
      diza->src_set |= XSET_DEV | XSET_DX;
      diza->dst_set |= XSET_DEV;
    }
    if ((c == 0xEE) || (c == 0xEF)) /* out dx, al|(e)ax */
    {
      /* 66,67 ? */
      diza->src_set |= XSET_DEV;
      diza->dst_set |= XSET_DEV | XSET_DX;
    }

    /* push es, cs, ss, ds */
    if ((c == 0x06) || (c == 0x0E) || (c == 0x16) || (c == 0x1E))
      diza->src_set |= XSET_OTHER;

    if ((c == 0x07) || (c == 0x17) || (c == 0x1F) ||  /* pop es, ss, ds */
        (c == 0xC4) || (c == 0xC5)) /* les/lds reg, r/m */
      diza->dst_set |= XSET_OTHER;

    if (c == 0xD7) /* xlat */
      diza->src_set |= diza->defaddr == 2 ? XSET_BX : XSET_EBX;

    if ((c == 0xC8) || (c == 0xC9)) /* enter xxxx, yy || leave */
    {
      xset = diza->defaddr == 2 ? (XSET_SP | XSET_BP) : (XSET_ESP | XSET_EBP);
      diza->src_set |= xset;
      diza->dst_set |= xset;
    }

    if (c == 0x8C)  /* mov [r/m]:16, sreg */
      diza->src_set |= XSET_OTHER;
    if (c == 0x8E)  /* mov sreg, [r/m]:16 */
      diza->dst_set |= XSET_OTHER;
  }

  if (flag & C_MODRM)
  {
    c = *p++;

    diza->modrm = c;

    mod = c & 0xC0;
    reg = (c & 0x38) >> 3;       /* reg or ttt */
    rm  = c & 0x07;

    c = diza->opcode;

    /* ttt-opcodes (reg==ttt) */

    /* shift */
    if ((c == 0xC0) || (c == 0xC1) || ((c >= 0xD0) && (c <= 0xD3)))
    {
      // ttt: 0=rol 1=ror 2=rcl 3=rcr 4=shl 5=shr 6=sal 7=sar
      if ((reg == 2) || (reg == 3)) /* rcl, rcr -- uses CF */
        diza->src_set |= XSET_FL;
      if ((c == 0xD2) || (c == 0xD3))
        diza->src_set |= XSET_CL;
    }

    if ( (c == 0xC6) || (c == 0xC7) ||  /* mov [r/m], imm8/16/32 */
         (c == 0x8F) )                  /* pop [r/m] */
      // ttt=000, other illegal
      if (reg != 0) flag |= C_BAD;

    if ((c >= 0x80) && (c <= 0x83)) flag |= xde_table[ TBL_80_83  + reg ];

    if (c == 0xBA)
      if (reg >= 5)                 /* bts/btr/btc [r/m], imm8 */
        flag |= C_DST_RM;

    if (c == 0xF6) flag |= xde_table[ TBL_F6 + reg ];
    if (c == 0xF7) flag |= xde_table[ TBL_F7 + reg ];
    if (c == 0xFE) flag |= xde_table[ TBL_FE + reg ];
    if (c == 0xFF) flag |= xde_table[ TBL_FF + reg ];

    if ((c == 0xF6) || (c == 0xF7))
    {
      if ((reg == 4) || (reg == 5)) /* mul/imul r/m */
      {
        if (c == 0xF6)
        {
          diza->src_set |= XSET_AL;
          diza->dst_set |= XSET_AX;
        }
        else
        if (diza->defaddr == 2)
        {
          diza->src_set |= XSET_AX;
          diza->dst_set |= XSET_DX | XSET_AX;
        }
        else
        {
          diza->src_set |= XSET_EAX;
          diza->dst_set |= XSET_EDX | XSET_EAX;
        }
      }
      if ((reg == 6) || (reg == 7)) /* div/idiv r/m */
      {
        if (c == 0xF6)
        {
          diza->src_set |= XSET_AX;
          diza->dst_set |= XSET_AX;
        }
        else
        if (diza->defaddr == 2)
        {
          diza->src_set |= XSET_DX | XSET_AX;
          diza->dst_set |= XSET_DX | XSET_AX;
        }
        else
        {
          diza->src_set |= XSET_EDX | XSET_EAX;
          diza->dst_set |= XSET_EDX | XSET_EAX;
        }
      }
    } /* F6/F7 */

    if (flag == C_ERROR) return 0;

    xset = reg2xset(flag & C_OPSZ8 ? 1 : diza->defdata, reg);
    if (flag & C_SRC_REG) diza->src_set |= xset;
    if (flag & C_DST_REG) diza->dst_set |= xset;

    if (mod == 0xC0)
    {
      xset = reg2xset(flag & C_OPSZ8 ? 1 : diza->defdata, rm);
      /* defaddr (0x67) prefix --> ??? */
      if (flag & C_DST_RM) diza->dst_set |= xset;

      if ( (diza->opcode == 0x0F) &&
           ( (diza->opcode2 == 0xB6) ||  /* movzx, movsx */
             (diza->opcode2 == 0xB7) ||
             (diza->opcode2 == 0xBE) ||
             (diza->opcode2 == 0xBF) ) )
        xset = reg2xset(diza->defdata==4?2:1, rm);

      if (flag & C_SRC_RM) diza->src_set |= xset;
    }
    else
    {
      if (diza->opcode != 0x8D) /* LEA: doesnt access memory contents */
      {
        diza->src_set |= XSET_OTHER;  /* since we have sreg:[xxx] */
        if (flag & C_SRC_RM) diza->src_set |= XSET_MEM;
      }

      if (flag & C_DST_RM) diza->dst_set |= XSET_MEM;

      if (diza->defaddr == 4)
      {
        /* 32-bit MODR/M */

        if (mod == 0x40)
        {
          flag |= C_ADDR1;
        }
        else
        if (mod == 0x80)
        {
          flag |= C_ADDR4;
        }

        if (rm == 4)
        {

          /* SIB */

          flag |= C_SIB;
          c = *p++;
          diza->sib = c;

          //scale = c & 0xC0;
          index = (c & 0x38) >> 3;
          base  = c & 0x07;

          if (base == 5)
          {
            xset = (mod == 0 ? 0 : XSET_EBP) | reg2xset(4, index);
            if (mod == 0) flag |= C_ADDR4;
            if (flag & C_SRC_RM) diza->src_set |= xset;
            if (flag & C_DST_RM) diza->src_set |= xset;
          }
          else
          {
            xset = reg2xset(4, base);
            if (flag & C_SRC_RM) diza->src_set |= xset;
            if (flag & C_DST_RM) diza->src_set |= xset;

            if (index != 0x05)
            {
              xset = reg2xset(4, index);
              if (flag & C_SRC_RM) diza->src_set |= xset;
              if (flag & C_DST_RM) diza->src_set |= xset;
            }
          }

        }
        else
        {
          /* no sib, just modr/m 32 */

          if ((mod == 0x00) && (rm == 0x05))
            flag |= C_ADDR4;
          else
          {
            xset = reg2xset(4, rm);
            if (flag & C_SRC_RM) diza->src_set |= xset;
            if (flag & C_DST_RM) diza->src_set |= xset;
          }

        }
      }
      else
      {
        /* 16-bit MODR/M */

        if (mod == 0x40)
        {
          flag |= C_ADDR1;
        }
        else
        if (mod == 0x80)
        {
          flag |= C_ADDR2;
        }
        else /* mod == 0x00 */
        {
          if (rm == 0x06)
            flag |= C_ADDR2;
        }

        if ((mod != 0x00) || (rm != 0x06))
        {
          xset = rm == 0 ? (XSET_BX | XSET_SI) :
                 rm == 1 ? (XSET_BX | XSET_DI) :
                 rm == 2 ? (XSET_BP | XSET_SI) :
                 rm == 3 ? (XSET_BP | XSET_DI) :
                 rm == 4 ? XSET_SI :
                 rm == 5 ? XSET_DI :
                 rm == 6 ? XSET_BP :
                           XSET_BX;
          if (flag & C_SRC_RM) diza->src_set |= xset;
          if (flag & C_DST_RM) diza->src_set |= xset;
        }

      }
    }
  } /* C_MODRM */
  else
  {
    /* its not modr/m, check for mem ref */

    if (flag & C_SRC_RM) diza->src_set |= XSET_MEM;
    if (flag & C_DST_RM) diza->dst_set |= XSET_MEM;

  }

  if (flag & C_UNDEF)
  {
    diza->src_set = XSET_UNDEF;
    diza->dst_set = XSET_UNDEF;
  }

  xset = reg2xset(diza->defdata, c & 0x07);
  if (flag & C_SRC_R0) diza->src_set |= xset;
  if (flag & C_DST_R0) diza->dst_set |= xset;

  if (flag & C_SRC_FL) diza->src_set |= XSET_FL;
  if (flag & C_DST_FL) diza->dst_set |= XSET_FL;

  xset = diza->defaddr == 2 ? XSET_SP : XSET_ESP; // incorrect, need stk seg sz
  if (flag & C_PUSH)
  {
    diza->src_set |= xset;                              // +
    diza->dst_set |= xset | XSET_MEM;
  }
  if (flag & C_POP)
  {
    diza->src_set |= xset | XSET_MEM;                   // +
    diza->dst_set |= xset;
  }

  xset = flag & C_OPSZ8 ? XSET_AL : diza->defdata == 2 ? XSET_AX : XSET_EAX;
  if (flag & C_SRC_ACC) diza->src_set |= xset;
  if (flag & C_DST_ACC) diza->dst_set |= xset;

  a =  flag & (C_ADDR1 | C_ADDR2 | C_ADDR4);
  d = (flag & (C_DATA1 | C_DATA2 | C_DATA4)) >> 8;

  if (flag & C_ADDR67) a += diza->defaddr;
  if (flag & C_DATA66) d += diza->defdata;

  for(i=0; i<a; i++)
    diza->addr_b[i] = *p++;

  for(i=0; i<d; i++)
    diza->data_b[i] = *p++;

  diza->flag     = flag;
  diza->addrsize = a;
  diza->datasize = d;
  diza->len      = p - opcode;

  return diza->len;

} /* int __cdecl xde_disasm() */

/* returns: diza.len                                                        */

int __cdecl xde_asm(/* OUT */ unsigned char* opcode,
                    /* IN */ struct xde_instr* diza)
{
  unsigned char* p;
  int i;

  p = opcode;

  if (diza->p_seg )               *p++ = diza->p_seg;
  if (diza->p_lock)               *p++ = diza->p_lock;
  if (diza->p_rep )               *p++ = diza->p_rep;
  if (diza->p_67  )               *p++ = diza->p_67;
  if (diza->p_66  )               *p++ = diza->p_66;
  *p++ = diza->opcode;
  if (diza->opcode == 0x0F)       *p++ = diza->opcode2;
  if (diza->flag & C_MODRM)       *p++ = diza->modrm;
  if (diza->flag & C_SIB)         *p++ = diza->sib;
  for(i=0; i<(int)diza->addrsize; i++) *p++ = diza->addr_b[i];
  for(i=0; i<(int)diza->datasize; i++) *p++ = diza->data_b[i];

  return p - opcode;

} /* int __cdecl xde_asm() */

/* EOF */
#endif