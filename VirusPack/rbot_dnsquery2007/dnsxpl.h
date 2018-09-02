/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 02 13:10:49 2007
 */
/* Compiler settings for dnsxpl.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: allocation ref bounds_check enum stub_data , use_epv
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __dnsxpl_h__
#define __dnsxpl_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __cluuid_INTERFACE_DEFINED__
#define __cluuid_INTERFACE_DEFINED__

/* interface cluuid */
/* [implicit_handle][unique][version][uuid] */ 

void DnssrvOperation( 
    /* [in] */ long parama,
    /* [string][in] */ unsigned char __RPC_FAR *paramb,
    /* [in] */ long paramc,
    /* [string][in] */ unsigned char __RPC_FAR *paramd,
    /* [in] */ long parame,
    /* [in] */ unsigned char __RPC_FAR *paramf);

long DnssrvQuery( 
    /* [string][unique][in] */ wchar_t __RPC_FAR *parama,
    /* [string][unique][in] */ unsigned char __RPC_FAR *paramb,
    /* [string][unique][in] */ unsigned char __RPC_FAR *paramc,
    /* [in] */ long __RPC_FAR *paramd,
    /* [out] */ long __RPC_FAR *parame);

void DnssrvComplexOperation( void);

void DnssrvEnumRecords( void);

void DnssrvUpdateRecord( void);

void DnssrvOperation2( void);

long DnssrvQuery2( 
    /* [in] */ long parama,
    /* [in] */ long paramb,
    /* [string][unique][in] */ wchar_t __RPC_FAR *paramc,
    /* [string][unique][in] */ unsigned char __RPC_FAR *paramd,
    /* [string][unique][in] */ unsigned char __RPC_FAR *parame,
    /* [out] */ long __RPC_FAR *paramf,
    /* [out] */ long __RPC_FAR *paramg);


extern handle_t dns;


typedef struct _cluuid_SERVER_EPV
{
    void ( __RPC_FAR *DnssrvOperation )( 
        /* [in] */ long parama,
        /* [string][in] */ unsigned char __RPC_FAR *paramb,
        /* [in] */ long paramc,
        /* [string][in] */ unsigned char __RPC_FAR *paramd,
        /* [in] */ long parame,
        /* [in] */ unsigned char __RPC_FAR *paramf);
    long ( __RPC_FAR *DnssrvQuery )( 
        /* [string][unique][in] */ wchar_t __RPC_FAR *parama,
        /* [string][unique][in] */ unsigned char __RPC_FAR *paramb,
        /* [string][unique][in] */ unsigned char __RPC_FAR *paramc,
        /* [in] */ long __RPC_FAR *paramd,
        /* [out] */ long __RPC_FAR *parame);
    void ( __RPC_FAR *DnssrvComplexOperation )( void);
    void ( __RPC_FAR *DnssrvEnumRecords )( void);
    void ( __RPC_FAR *DnssrvUpdateRecord )( void);
    void ( __RPC_FAR *DnssrvOperation2 )( void);
    long ( __RPC_FAR *DnssrvQuery2 )( 
        /* [in] */ long parama,
        /* [in] */ long paramb,
        /* [string][unique][in] */ wchar_t __RPC_FAR *paramc,
        /* [string][unique][in] */ unsigned char __RPC_FAR *paramd,
        /* [string][unique][in] */ unsigned char __RPC_FAR *parame,
        /* [out] */ long __RPC_FAR *paramf,
        /* [out] */ long __RPC_FAR *paramg);
    
    } cluuid_SERVER_EPV;

extern RPC_IF_HANDLE cluuid_ClientIfHandle;
extern RPC_IF_HANDLE cluuid_ServerIfHandle;
#endif /* __cluuid_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
