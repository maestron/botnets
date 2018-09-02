/*
	from sapphire.h -- Interface for the Saphire II stream cipher.

	Dedicated to the Public Domain the author and inventor
	(Michael Paul Johnson).  This code comes with no warranty.
	Use it at your own risk.
*/

class CSapphire {
public:
	CSapphire(unsigned char *key=NULL,			// Calls initialize if a real
        unsigned char keysize=0);				// key is provided.  If none
												// is provided, call initialize
												// before encrypt or decrypt.
    ~CSapphire();								// Destroy cipher state information.

    void initialize(unsigned char *key,			// User key is used to set
		unsigned char keysize);					// up state information.
    void hash_init(void);						// Set up default hash.
    
	unsigned char encrypt(unsigned char b=0);	// Encrypt byte
												// or get a random byte.
    unsigned char decrypt(unsigned char b);		// Decrypt byte.

	void hash_final(unsigned char *hash,		// Copy hash value to hash
		unsigned char hashlength=20);			// Hash length (16-32)
    void burn(void);							// Destroy cipher state information.

private:
	unsigned char cards[256];					// A permutation of 0-255.
	unsigned char rotor,						// Index that rotates smoothly
		ratchet,								// Index that moves erratically
        avalanche,								// Index heavily data dependent
        last_plain,								// Last plain text byte
        last_cipher;							// Last cipher text byte
	
	unsigned char keyrand(int limit, unsigned char *user_key,
		unsigned char keysize, unsigned char *rsum, unsigned *keypos);
};
