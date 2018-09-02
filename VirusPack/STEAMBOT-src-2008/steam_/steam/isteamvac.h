#ifndef ISTEAMVAC_H
#define ISTEAMVAC_H
#ifdef _WIN32
#pragma once
#endif

#include "isteamclient.h"

// IVAC
// This is the wrapper class for all VAC functionaility in the client
class IVAC
{
public:
	virtual bool BVACCreateProcess(  
		void *lpVACBlob,
		unsigned int cbBlobSize,
		const char *lpApplicationName,
		char *lpCommandLine,
		uint32 dwCreationFlags,
		void *lpEnvironment,
		char *lpCurrentDirectory,
		uint32 nGameID
		) = 0;

	virtual void KillAllVAC() = 0;

	virtual uint8 *PbLoadVacBlob( int *pcbVacBlob ) = 0;
	virtual void FreeVacBlob( uint8 *pbVacBlob ) = 0;

	virtual void RealHandleVACChallenge( int nClientGameID, uint8 *pubChallenge, int cubChallenge ) = 0;
};

#endif