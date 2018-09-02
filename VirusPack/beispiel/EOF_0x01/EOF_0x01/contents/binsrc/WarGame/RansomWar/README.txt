-- README --

-- Introduction --

Hi, this is a shitty example of ransomware, If somebody doesn't know what a ransomware
is I will explain it.
Basically a ransomware is a malware that makes something of evil to the user's system,
for example it can delete files or encrypt them.
The user can avoid this sending something to the author of the malware, a "ransom" so he can
get back his files.
This is only coded for fun so this ransomware will not ask user for nothing :)

-- How it works --

This shit works in a simple ways: encrypts every file on every drive ( only DRIVE_REMOTE and
FIXED_DRIVE ) that could contain important data like documents or images.
It only skips executable, dll files,ini files,drv and vxd files that are used by system.
The encryption used is given by the blowfish algorithm to make a stronger encryption.
I didn't use CryptoAPI provided by Windows but an excellent external implementation of this
algo called "Tiny crypt library".
You can find it at http://tomstdenis.home.dhs.org/zips/crypt.zip

-- Final words --

If you want you can contact me for suggestions,ideas,bugs ... at wargame89@yahoo.it.
Ok good reading !

-- EOF -- 