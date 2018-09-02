/* this ALWAYS GENERATED file contains the RPC client stubs */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 02 13:10:49 2007
 */
/* Compiler settings for dnsxpl.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: allocation ref bounds_check enum stub_data , use_epv
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#if defined( _ALPHA_ )
#include <stdarg.h>
#endif

#include "dnsxpl.h"

#define TYPE_FORMAT_STRING_SIZE   27                                
#define PROC_FORMAT_STRING_SIZE   71                                

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;

/* Standard interface: cluuid, ver. 5.0,
   GUID={0x50abc2a4,0x574d,0x40b3,{0x9d,0x66,0xee,0x4f,0xd5,0xfb,0xa0,0x76}} */

handle_t dns;


static const RPC_CLIENT_INTERFACE cluuid___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0x50abc2a4,0x574d,0x40b3,{0x9d,0x66,0xee,0x4f,0xd5,0xfb,0xa0,0x76}},{5,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE cluuid_ClientIfHandle = (RPC_IF_HANDLE)& cluuid___RpcClientInterface;

extern const MIDL_STUB_DESC cluuid_StubDesc;

static RPC_BINDING_HANDLE cluuid__MIDL_AutoBindHandle;


void DnssrvOperation( 
    /* [in] */ long parama,
    /* [string][in] */ unsigned char __RPC_FAR *paramb,
    /* [in] */ long paramc,
    /* [string][in] */ unsigned char __RPC_FAR *paramd,
    /* [in] */ long parame,
    /* [in] */ unsigned char __RPC_FAR *paramf)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(!paramb)
        {
        RpcRaiseException(RPC_X_NULL_REF_POINTER);
        }
    if(!paramd)
        {
        RpcRaiseException(RPC_X_NULL_REF_POINTER);
        }
    if(!paramf)
        {
        RpcRaiseException(RPC_X_NULL_REF_POINTER);
        }
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&cluuid_StubDesc,
                          0);
        
        
        _Handle = dns;
        
        
        _StubMsg.BufferLength = 4U + 12U + 11U + 13U + 11U + 2U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)paramb,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)paramd,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = parama;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)paramb,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = paramc;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)paramd,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = parame;
        
        *(( unsigned char __RPC_FAR * )_StubMsg.Buffer)++ = *paramf;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


long DnssrvQuery( 
    /* [string][unique][in] */ wchar_t __RPC_FAR *parama,
    /* [string][unique][in] */ unsigned char __RPC_FAR *paramb,
    /* [string][unique][in] */ unsigned char __RPC_FAR *paramc,
    /* [in] */ long __RPC_FAR *paramd,
    /* [out] */ long __RPC_FAR *parame)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(!paramd)
        {
        RpcRaiseException(RPC_X_NULL_REF_POINTER);
        }
    if(!parame)
        {
        RpcRaiseException(RPC_X_NULL_REF_POINTER);
        }
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&cluuid_StubDesc,
                          1);
        
        
        _Handle = dns;
        
        
        _StubMsg.BufferLength = 16U + 23U + 24U + 11U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)parama,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)paramb,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[14] );
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)paramc,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[14] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)parama,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)paramb,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[14] );
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)paramc,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[14] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *paramd;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
        
        *parame = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


void DnssrvComplexOperation( void)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&cluuid_StubDesc,
                          2);
        
        
        _Handle = dns;
        
        
        _StubMsg.BufferLength = 0U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


void DnssrvEnumRecords( void)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&cluuid_StubDesc,
                          3);
        
        
        _Handle = dns;
        
        
        _StubMsg.BufferLength = 0U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


void DnssrvUpdateRecord( void)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&cluuid_StubDesc,
                          4);
        
        
        _Handle = dns;
        
        
        _StubMsg.BufferLength = 0U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


void DnssrvOperation2( void)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&cluuid_StubDesc,
                          5);
        
        
        _Handle = dns;
        
        
        _StubMsg.BufferLength = 0U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


long DnssrvQuery2( 
    /* [in] */ long parama,
    /* [in] */ long paramb,
    /* [string][unique][in] */ wchar_t __RPC_FAR *paramc,
    /* [string][unique][in] */ unsigned char __RPC_FAR *paramd,
    /* [string][unique][in] */ unsigned char __RPC_FAR *parame,
    /* [out] */ long __RPC_FAR *paramf,
    /* [out] */ long __RPC_FAR *paramg)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(!paramf)
        {
        RpcRaiseException(RPC_X_NULL_REF_POINTER);
        }
    if(!paramg)
        {
        RpcRaiseException(RPC_X_NULL_REF_POINTER);
        }
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&cluuid_StubDesc,
                          6);
        
        
        _Handle = dns;
        
        
        _StubMsg.BufferLength = 4U + 4U + 16U + 23U + 24U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)paramc,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)paramd,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[14] );
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)parame,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[14] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = parama;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = paramb;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)paramc,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)paramd,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[14] );
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)parame,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[14] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[44] );
        
        *paramf = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        *paramg = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


static const MIDL_STUB_DESC cluuid_StubDesc = 
    {
    (void __RPC_FAR *)& cluuid___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &dns,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x10001, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  2 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  4 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/*  6 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  8 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 10 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/* 12 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 14 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 16 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */
/* 18 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */
/* 20 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 22 */	NdrFcShort( 0xa ),	/* Type Offset=10 */
/* 24 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 26 */	NdrFcShort( 0xe ),	/* Type Offset=14 */
/* 28 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 30 */	NdrFcShort( 0xe ),	/* Type Offset=14 */
/* 32 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 34 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */
/* 36 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 38 */	NdrFcShort( 0x16 ),	/* Type Offset=22 */
/* 40 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 42 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */
/* 44 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 46 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 48 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 50 */	NdrFcShort( 0xa ),	/* Type Offset=10 */
/* 52 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 54 */	NdrFcShort( 0xe ),	/* Type Offset=14 */
/* 56 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 58 */	NdrFcShort( 0xe ),	/* Type Offset=14 */
/* 60 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 62 */	NdrFcShort( 0x16 ),	/* Type Offset=22 */
/* 64 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 66 */	NdrFcShort( 0x16 ),	/* Type Offset=22 */
/* 68 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  4 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  8 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 10 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 12 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 14 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 16 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 18 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 20 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 22 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 24 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */

			0x0
        }
    };
