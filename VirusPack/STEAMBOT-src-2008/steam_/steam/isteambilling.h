//====== Copyright © 1996-2004, Valve Corporation, All rights reserved. =======
//
// Purpose: interface to Billings data in Steam
//
//=============================================================================

#ifndef ISTEAMBILLING_H
#define ISTEAMBILLING_H
#ifdef _WIN32
#pragma once
#endif

//-----------------------------------------------------------------------------
// Purpose: interface to billing
//-----------------------------------------------------------------------------
class ISteamBilling
{
public:
	// Sets the billing address in the ISteamBilling object for use by other ISteamBilling functions (not stored on server)
	virtual bool SetBillingAddress( const char *pchName, 
									const char *pchAddress1,
									const char *pchAddress2,
									const char *pchCity,
									const char *pchPostcode,
									const char *pchState,
									const char *pchCountry,
									const char *pchPhone ) = 0;
	// Gets any previous set billing address in the ISteamBilling object (not stored on server)
	virtual bool GetBillingAddress( char *pchName, 
									char *pchAddress1,
									char *pchAddress2,
									char *pchCity,
									char *pchPostcode,
									char *pchState,
									char *pchCountry,
									char *pchPhone ) = 0;
	// Sets the billing address in the ISteamBilling object for use by other ISteamBilling functions (not stored on server)
	virtual bool SetShippingAddress( const char *pchName, 
									const char *pchAddress1,
									const char *pchAddress2,
									const char *pchCity,
									const char *pchPostcode,
									const char *pchState,
									const char *pchCountry,
									const char *pchPhone ) = 0;
	// Gets any previous set billing address in the ISteamBilling object (not stored on server)
	virtual bool GetShippingAddress( char *pchName, 
									char *pchAddress1,
									char *pchAddress2,
									char *pchCity,
									char *pchPostcode,
									char *pchState,
									char *pchCountry,
									char *pchPhone ) = 0;
	// Ask the server for the final price of package: requires that ISteamBilling billing & shipping address are set (can be same)
	virtual bool GetFinalPrice( int32 nPackageID ) = 0;

	// Sets the credit card info in the ISteamBilling object for use by other ISteamBilling functions  (may eventually also be stored on server)
	virtual bool SetCardInfo( int32 eCreditCardType,
							  const char *pchCardNumber,
							  const char *pchCardHolderName,
							  const char *pchCardExpYear,
							  const char *pchCardExpMonth,
							  const char *pchCardCVV2 ) = 0;
	// Gets any credit card info in the ISteamBilling object (not stored on server)
	virtual bool GetCardInfo( int32 *eCreditCardType,
							  char *pchCardNumber,
							  char *pchCardHolderName,
							  char *pchCardExpYear,
							  char *pchCardExpMonth,
							  char *pchCardCVV2 ) = 0;

	// Ask the server to purchase a package: requires that ISteamBilling cardinfo, billing & shipping address are set
	virtual bool Purchase( int32 nPackageID,
						   int32 nExpectedCostCents,
		                   uint64 gidCardID, // if non-NIL, use a server stored card
						   bool bStoreCardInfo ) = 0;  // Should this cardinfo also be stored on the server
};


#define STEAMBILLING_INTERFACE_VERSION "SteamBilling001"

//already defined by updated isteamclient
//enum {	k_iSteamBillingCallbacks = 400 };

//-----------------------------------------------------------------------------
// Purpose: called when this client has received a finalprice message from a Billing
//-----------------------------------------------------------------------------
struct FinalPriceMsg_t
{
		enum { k_iCallback = k_iSteamBillingCallbacks + 1 };

		uint32 m_bSuccess;
		uint32 m_nBaseCost;
		uint32 m_nTotalDiscount;
		uint32 m_nTax;
		uint32 m_nShippingCost;
};

struct PurchaseMsg_t
{
		enum { k_iCallback = k_iSteamBillingCallbacks + 2 };

		uint32 m_bSuccess;
		int32 m_EPurchaseResultDetail;			// Detailed result information
};

#endif // ISTEAMBILLING_H
