/* |  _ \ \ \/ /    / |___ \ / _ \ TesT |  \/  |/ _ \|  _ \    \ \   / /___ \ 
   | |_) | \  /_____| | __) | | | |_____| |\/| | | | | | | |____\ \ / /  __) |
   |  _ <  /  \_____| |/ __/| |_| |_____| |  | | |_| | |_| |_____\ V /  / __/ 
   |_| \_\/_/\_\ BuZ|_|_____|\___/      |_|  |_|\___/|____/  BuZ  \_/  |_____|
   ---------------------------------------------------------------------------
   --MSSQL-NTPASS-SYM06010-MS04007-MS06040-VNCBRUTE-PSTORE-FIREFOX-SP2PATCH---  
   ---------------------------------------------------------------------------
               Greets To: THE REAL CODERS & The Ryan1918 Crew !!
 */
#define EN0	0	/* MODE == encrypt */
#define DE1	1	/* MODE == decrypt */

extern void deskey(unsigned char *, int);
/*		      hexkey[8]     MODE
 * Sets the internal key register according to the hexadecimal
 * key contained in the 8 bytes of hexkey, according to the DES,
 * for encryption or decryption according to MODE.
 */

extern void usekey(unsigned long *);
/*		    cookedkey[32]
 * Loads the internal key register with the data in cookedkey.
 */

extern void cpkey(unsigned long *);
/*		   cookedkey[32]
 * Copies the contents of the internal key register into the storage
 * located at &cookedkey[0].
 */

extern void des(unsigned char *, unsigned char *);
/*		    from[8]	      to[8]
 * Encrypts/Decrypts (according to the key currently loaded in the
 * internal key register) one block of eight bytes at address 'from'
 * into the block at address 'to'.  They can be the same.
 */

/* d3des.h V5.09 rwo 9208.04 15:06 Graven Imagery
 ********************************************************************/
