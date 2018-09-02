/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2004 Ago and the Agobot team
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary and source may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.
	4. The person using this sourcecode is a developer of said sourcecode.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	This license may be changed without prior notice.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef __3DNOW_H__
#define __3DNOW_H__

// Stop the "no EMMS" warning, since it doesn't detect FEMMS properly
#pragma warning(disable:4799)

// Defines for operands.
#define _K3D_MM0 0xc0
#define _K3D_MM1 0xc1
#define _K3D_MM2 0xc2
#define _K3D_MM3 0xc3
#define _K3D_MM4 0xc4
#define _K3D_MM5 0xc5
#define _K3D_MM6 0xc6
#define _K3D_MM7 0xc7
#define _K3D_mm0 0xc0
#define _K3D_mm1 0xc1
#define _K3D_mm2 0xc2
#define _K3D_mm3 0xc3
#define _K3D_mm4 0xc4
#define _K3D_mm5 0xc5
#define _K3D_mm6 0xc6
#define _K3D_mm7 0xc7
#define _K3D_EAX 0x00
#define _K3D_ECX 0x01
#define _K3D_EDX 0x02
#define _K3D_EBX 0x03
#define _K3D_ESI 0x06
#define _K3D_EDI 0x07
#define _K3D_eax 0x00
#define _K3D_ecx 0x01
#define _K3D_edx 0x02
#define _K3D_ebx 0x03
#define _K3D_esi 0x06
#define _K3D_edi 0x07

// These defines are for compatibility with the previous version of the header file.
#define _K3D_M0   0xc0
#define _K3D_M1   0xc1
#define _K3D_M2   0xc2
#define _K3D_M3   0xc3
#define _K3D_M4   0xc4
#define _K3D_M5   0xc5
#define _K3D_M6   0xc6
#define _K3D_M7   0xc7
#define _K3D_m0   0xc0
#define _K3D_m1   0xc1
#define _K3D_m2   0xc2
#define _K3D_m3   0xc3
#define _K3D_m4   0xc4
#define _K3D_m5   0xc5
#define _K3D_m6   0xc6
#define _K3D_m7   0xc7
#define _K3D__EAX 0x00
#define _K3D__ECX 0x01
#define _K3D__EDX 0x02
#define _K3D__EBX 0x03
#define _K3D__ESI 0x06
#define _K3D__EDI 0x07
#define _K3D__eax 0x00
#define _K3D__ecx 0x01
#define _K3D__edx 0x02
#define _K3D__ebx 0x03
#define _K3D__esi 0x06
#define _K3D__edi 0x07

// General 3DNow! instruction format that is supported by 
// these macros. Note that only the most basic form of memory 
// operands are supported by these macros. 

#define InjK3DOps(dst,src,inst)                         \
{                                                       \
   _asm _emit 0x0f                                      \
   _asm _emit 0x0f                                      \
   _asm _emit ((_K3D_##dst & 0x3f) << 3) | _K3D_##src   \
   _asm _emit _3DNowOpcode##inst                        \
}

#define InjK3DMOps(dst,src,off,inst)                    \
{                                                       \
   _asm _emit 0x0f                                      \
   _asm _emit 0x0f                                      \
   _asm _emit (((_K3D_##dst & 0x3f) << 3) | _K3D_##src | 0x40) \
   _asm _emit off                                       \
   _asm _emit _3DNowOpcode##inst                        \
}

#define InjMMXOps(dst,src,inst)                         \
{                                                       \
   _asm _emit 0x0f                                      \
   _asm _emit _3DNowOpcode##inst                        \
   _asm _emit ((_K3D_##dst & 0x3f) << 3) | _K3D_##src   \
}

#define InjMMXMOps(dst,src,off,inst)                    \
{                                                       \
   _asm _emit 0x0f                                      \
   _asm _emit _3DNowOpcode##inst                        \
   _asm _emit (((_K3D_##dst & 0x3f) << 3) | _K3D_##src | 0x40) \
   _asm _emit off                                       \
}

#define _3DNowOpcodePF2ID    0x1d
#define _3DNowOpcodePFACC    0xae
#define _3DNowOpcodePFADD    0x9e
#define _3DNowOpcodePFCMPEQ  0xb0
#define _3DNowOpcodePFCMPGE  0x90
#define _3DNowOpcodePFCMPGT  0xa0
#define _3DNowOpcodePFMAX    0xa4
#define _3DNowOpcodePFMIN    0x94
#define _3DNowOpcodePFMUL    0xb4
#define _3DNowOpcodePFRCP    0x96
#define _3DNowOpcodePFRCPIT1 0xa6
#define _3DNowOpcodePFRCPIT2 0xb6
#define _3DNowOpcodePFRSQRT  0x97
#define _3DNowOpcodePFRSQIT1 0xa7
#define _3DNowOpcodePFSUB    0x9a
#define _3DNowOpcodePFSUBR   0xaa
#define _3DNowOpcodePI2FD    0x0d
#define _3DNowOpcodePAVGUSB  0xbf
#define _3DNowOpcodePMULHRW  0xb7
#define _3DNowOpcodePFNACC   0x8a
#define _3DNowOpcodePFPNACC  0x8e
#define _3DNowOpcodePSWAPD   0xbb
#define _3DNowOpcodePMINUB   0xda
#define _3DNowOpcodePMAXUB   0xde
#define _3DNowOpcodePMINSW   0xea
#define _3DNowOpcodePMAXSW   0xee
#define _3DNowOpcodePMULHUW  0xe4
#define _3DNowOpcodePAVGB    0xe0
#define _3DNowOpcodePAVGW    0xe3
#define _3DNowOpcodePSADBW   0xf6
#define _3DNowOpcodePMOVMSKB 0xd7
#define _3DNowOpcodePMASKMOVQ   0xf7
#define _3DNowOpcodePINSRW   0xc4
#define _3DNowOpcodePEXTRW   0xc5
#define _3DNowOpcodePSHUFW   0x70
#define _3DNowOpcodeMOVNTQ   0xe7
#define _3DNowOpcodePREFETCHT 0x18


#define PF2ID(dst,src)      InjK3DOps(dst, src, PF2ID)
#define PFACC(dst,src)      InjK3DOps(dst, src, PFACC)
#define PFADD(dst,src)      InjK3DOps(dst, src, PFADD)
#define PFCMPEQ(dst,src)    InjK3DOps(dst, src, PFCMPEQ)
#define PFCMPGE(dst,src)    InjK3DOps(dst, src, PFCMPGE)
#define PFCMPGT(dst,src)    InjK3DOps(dst, src, PFCMPGT)
#define PFMAX(dst,src)      InjK3DOps(dst, src, PFMAX)
#define PFMIN(dst,src)      InjK3DOps(dst, src, PFMIN)
#define PFMUL(dst,src)      InjK3DOps(dst, src, PFMUL)
#define PFRCP(dst,src)      InjK3DOps(dst, src, PFRCP)
#define PFRCPIT1(dst,src)   InjK3DOps(dst, src, PFRCPIT1)
#define PFRCPIT2(dst,src)   InjK3DOps(dst, src, PFRCPIT2)
#define PFRSQRT(dst,src)    InjK3DOps(dst, src, PFRSQRT)
#define PFRSQIT1(dst,src)   InjK3DOps(dst, src, PFRSQIT1)
#define PFSUB(dst,src)      InjK3DOps(dst, src, PFSUB)
#define PFSUBR(dst,src)     InjK3DOps(dst, src, PFSUBR)
#define PI2FD(dst,src)      InjK3DOps(dst, src, PI2FD)
#define PAVGUSB(dst,src)    InjK3DOps(dst, src, PAVGUSB)
#define PMULHRW(dst,src)    InjK3DOps(dst, src, PMULHRW)

#define FEMMS                                   \
{                                               \
   _asm _emit 0x0f                              \
   _asm _emit 0x0e                              \
}

#define PREFETCH(src)                           \
{                                               \
   _asm _emit 0x0f                              \
   _asm _emit 0x0d                              \
   _asm _emit (_K3D_##src & 0x07)               \
}

/* Prefetch with a short offset, < 127 or > -127
   Carefull!  Doesn't check for your offset being
   in range. */

#define PREFETCHM(src,off)					    \
{                                               \
   _asm _emit 0x0f                              \
   _asm _emit 0x0d								\
   _asm _emit (0x40 | (_K3D_##src & 0x07))		\
   _asm _emit off								\
}

/* Prefetch with a long offset */

#define PREFETCHMLONG(src,off)					\
{                                               \
   _asm _emit 0x0f                              \
   _asm _emit 0x0d								\
   _asm _emit (0x80 | (_K3D_##src & 0x07))		\
   _asm _emit (off & 0x000000ff)				\
   _asm _emit (off & 0x0000ff00) >>	8			\
   _asm _emit (off & 0x00ff0000) >>	16			\
   _asm _emit (off & 0xff000000) >>	24			\
}

#define PREFETCHW(src)                          \
{                                               \
   _asm _emit 0x0f                              \
   _asm _emit 0x0d                              \
   _asm _emit (0x08 | (_K3D_##src & 0x07))      \
}

#define PREFETCHWM(src,off)                     \
{                                               \
   _asm _emit 0x0f                              \
   _asm _emit 0x0d                              \
   _asm _emit 0x48 | (_K3D_##src & 0x07)        \
   _asm	_emit off								\
}

#define PREFETCHWMLONG(src,off)                 \
{                                               \
   _asm _emit 0x0f                              \
   _asm _emit 0x0d                              \
   _asm _emit 0x88 | (_K3D_##src & 0x07)        \
   _asm _emit (off & 0x000000ff)				\
   _asm _emit (off & 0x0000ff00) >>	8			\
   _asm _emit (off & 0x00ff0000) >>	16			\
   _asm _emit (off & 0xff000000) >>	24			\
}

#define CPUID                                   \
{                                               \
    _asm _emit 0x0f                             \
    _asm _emit 0xa2                             \
}


/* Defines for new, K7 opcodes */
#define SFENCE                                  \
{                                               \
    _asm _emit 0x0f                             \
    _asm _emit 0xae                             \
    _asm _emit 0xf8                             \
}

#define PFNACC(dst,src)         InjK3DOps(dst,src,PFNACC)
#define PFPNACC(dst,src)        InjK3DOps(dst,src,PFPNACC)
#define PSWAPD(dst,src)         InjK3DOps(dst,src,PSWAPD)
#define PMINUB(dst,src)         InjMMXOps(dst,src,PMINUB)
#define PMAXUB(dst,src)         InjMMXOps(dst,src,PMAXUB)
#define PMINSW(dst,src)         InjMMXOps(dst,src,PMINSW)
#define PMAXSW(dst,src)         InjMMXOps(dst,src,PMAXSW)
#define PMULHUW(dst,src)        InjMMXOps(dst,src,PMULHUW)
#define PAVGB(dst,src)          InjMMXOps(dst,src,PAVGB)
#define PAVGW(dst,src)          InjMMXOps(dst,src,PAVGW)
#define PSADBW(dst,src)         InjMMXOps(dst,src,PSADBW)
#define PMOVMSKB(dst,src)       InjMMXOps(dst,src,PMOVMSKB)
#define PMASKMOVQ(dst,src)      InjMMXOps(dst,src,PMASKMOVQ)
#define PINSRW(dst,src,msk)     InjMMXOps(dst,src,PINSRW) _asm _emit msk
#define PEXTRW(dst,src,msk)     InjMMXOps(dst,src,PEXTRW) _asm _emit msk
#define PSHUFW(dst,src,msk)     InjMMXOps(dst,src,PSHUFW) _asm _emit msk
#define MOVNTQ(dst,src)         InjMMXOps(src,dst,MOVNTQ)
#define PREFETCHNTA(mem)        InjMMXOps(mm0,mem,PREFETCHT)
#define PREFETCHT0(mem)         InjMMXOps(mm1,mem,PREFETCHT)
#define PREFETCHT1(mem)         InjMMXOps(mm2,mem,PREFETCHT)
#define PREFETCHT2(mem)         InjMMXOps(mm3,mem,PREFETCHT)


/* Memory/offset versions of the opcodes */
#define PAVGUSBM(dst,src,off)   InjK3DMOps(dst,src,off,PAVGUSB)
#define PF2IDM(dst,src,off)     InjK3DMOps(dst,src,off,PF2ID)
#define PFACCM(dst,src,off)     InjK3DMOps(dst,src,off,PFACC)
#define PFADDM(dst,src,off)     InjK3DMOps(dst,src,off,PFADD)
#define PFCMPEQM(dst,src,off)   InjK3DMOps(dst,src,off,PFCMPEQ)
#define PFCMPGEM(dst,src,off)   InjK3DMOps(dst,src,off,PFCMPGE)
#define PFCMPGTM(dst,src,off)   InjK3DMOps(dst,src,off,PFCMPGT)
#define PFMAXM(dst,src,off)     InjK3DMOps(dst,src,off,PFMAX)
#define PFMINM(dst,src,off)     InjK3DMOps(dst,src,off,PFMIN)
#define PFMULM(dst,src,off)     InjK3DMOps(dst,src,off,PFMUL)
#define PFRCPM(dst,src,off)     InjK3DMOps(dst,src,off,PFRCP)
#define PFRCPIT1M(dst,src,off)  InjK3DMOps(dst,src,off,PFRCPIT1)
#define PFRCPIT2M(dst,src,off)  InjK3DMOps(dst,src,off,PFRCPIT2)
#define PFRSQRTM(dst,src,off)   InjK3DMOps(dst,src,off,PFRSQRT)
#define PFRSQIT1M(dst,src,off)  InjK3DMOps(dst,src,off,PFRSQIT1)
#define PFSUBM(dst,src,off)     InjK3DMOps(dst,src,off,PFSUB)
#define PFSUBRM(dst,src,off)    InjK3DMOps(dst,src,off,PFSUBR)
#define PI2FDM(dst,src,off)     InjK3DMOps(dst,src,off,PI2FD)
#define PMULHRWM(dst,src,off)   InjK3DMOps(dst,src,off,PMULHRW)


/* Memory/offset versions of the K7 opcodes */
#define PFNACCM(dst,src,off)     InjK3DMOps(dst,src,off,PFNACC)
#define PFPNACCM(dst,src,off)    InjK3DMOps(dst,src,off,PFPNACC)
#define PSWAPDM(dst,src,off)     InjK3DMOps(dst,src,off,PSWAPD)
#define PMINUBM(dst,src,off)     InjMMXMOps(dst,src,off,PMINUB)
#define PMAXUBM(dst,src,off)     InjMMXMOps(dst,src,off,PMAXUB)
#define PMINSWM(dst,src,off)     InjMMXMOps(dst,src,off,PMINSW)
#define PMAXSWM(dst,src,off)     InjMMXMOps(dst,src,off,PMAXSW)
#define PMULHUWM(dst,src,off)    InjMMXMOps(dst,src,off,PMULHUW)
#define PAVGBM(dst,src,off)      InjMMXMOps(dst,src,off,PAVGB)
#define PAVGWM(dst,src,off)      InjMMXMOps(dst,src,off,PAVGW)
#define PSADBWM(dst,src,off)     InjMMXMOps(dst,src,off,PSADBW)
#define PMOVMSKBM(dst,src,off)   InjMMXMOps(dst,src,off,PMOVMSKB)
#define PMASKMOVQM(dst,src,off)  InjMMXMOps(dst,src,off,PMASKMOVQ)
#define PINSRWM(dst,src,off,msk) InjMMXMOps(dst,src,off,PINSRW) _asm _emit msk
#define PSHUFWM(dst,src,off,msk) InjMMXMOps(dst,src,off,PSHUFW) _asm _emit msk
#define MOVNTQM(dst,src,off)     InjMMXMOps(src,dst,off,MOVNTQ)
#define PREFETCHNTAM(mem,off)    InjMMXMOps(mm0,mem,off,PREFETCHT)
#define PREFETCHT0M(mem,off)     InjMMXMOps(mm1,mem,off,PREFETCHT)
#define PREFETCHT1M(mem,off)     InjMMXMOps(mm2,mem,off,PREFETCHT)
#define PREFETCHT2M(mem,off)     InjMMXMOps(mm3,mem,off,PREFETCHT)


#else

/* Assume built-in support for 3DNow! opcodes, replace macros with opcodes */
#define PAVGUSB(dst,src)    pavgusb     dst,src
#define PF2ID(dst,src)      pf2id       dst,src
#define PFACC(dst,src)      pfacc       dst,src
#define PFADD(dst,src)      pfadd       dst,src
#define PFCMPEQ(dst,src)    pfcmpeq     dst,src
#define PFCMPGE(dst,src)    pfcmpge     dst,src
#define PFCMPGT(dst,src)    pfcmpgt     dst,src
#define PFMAX(dst,src)      pfmax       dst,src
#define PFMIN(dst,src)      pfmin       dst,src
#define PFMUL(dst,src)      pfmul       dst,src
#define PFRCP(dst,src)      pfrcp       dst,src
#define PFRCPIT1(dst,src)   pfrcpit1    dst,src
#define PFRCPIT2(dst,src)   pfrcpit2    dst,src
#define PFRSQRT(dst,src)    pfrsqrt     dst,src
#define PFRSQIT1(dst,src)   pfrsqit1    dst,src
#define PFSUB(dst,src)      pfsub       dst,src
#define PFSUBR(dst,src)     pfsubr      dst,src
#define PI2FD(dst,src)      pi2fd       dst,src
#define PMULHRW(dst,src)    pmulhrw     dst,src
#define PREFETCH(src)       prefetch    src
#define PREFETCHW(src)      prefetchw   src

#define PAVGUSBM(dst,src,off)   pavgusb     dst,[src+off]
#define PF2IDM(dst,src,off)     PF2ID       dst,[src+off]
#define PFACCM(dst,src,off)     PFACC       dst,[src+off]
#define PFADDM(dst,src,off)     PFADD       dst,[src+off]
#define PFCMPEQM(dst,src,off)   PFCMPEQ     dst,[src+off]
#define PFCMPGEM(dst,src,off)   PFCMPGE     dst,[src+off]
#define PFCMPGTM(dst,src,off)   PFCMPGT     dst,[src+off]
#define PFMAXM(dst,src,off)     PFMAX       dst,[src+off]
#define PFMINM(dst,src,off)     PFMIN       dst,[src+off]
#define PFMULM(dst,src,off)     PFMUL       dst,[src+off]
#define PFRCPM(dst,src,off)     PFRCP       dst,[src+off]
#define PFRCPIT1M(dst,src,off)  PFRCPIT1    dst,[src+off]
#define PFRCPIT2M(dst,src,off)  PFRCPIT2    dst,[src+off]
#define PFRSQRTM(dst,src,off)   PFRSQRT     dst,[src+off]
#define PFRSQIT1M(dst,src,off)  PFRSQIT1    dst,[src+off]
#define PFSUBM(dst,src,off)     PFSUB       dst,[src+off]
#define PFSUBRM(dst,src,off)    PFSUBR      dst,[src+off]
#define PI2FDM(dst,src,off)     PI2FD       dst,[src+off]
#define PMULHRWM(dst,src,off)   PMULHRW     dst,[src+off]

#endif // __3DNOW_H__
