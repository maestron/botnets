#include "../Headers/includes.h"

// kernel32.dll function variables
GCNA fGetComputerName;

// user32.dll function variables
IW fIsWindow;

// ws2_32.dll function variables
WSAS fWSAStartup;
WSASo fWSASocket;
WSAGLE fWSAGetLastError;
WSAC fWSACleanup;
SOCK fsocket;
CON fconnect;
INTOA finet_ntoa;
IADDR finet_addr;
HTONS fhtons;
HTONL fhtonl;
SEND fsend;
SENDTO fsendto;
RECV frecv;
SSO fsetsockopt;
GSN fgetsockname;
GHN fgethostname;
GHBN fgethostbyname;
GPN fgetpeername;
CLSO fclosesocket;
SD fshutdown;

// wininet.dll function variables
IGCS fInternetGetConnectedState;
IGCSE fInternetGetConnectedStateEx;
HOR fHttpOpenRequest;
HSR fHttpSendRequest;
FGF fFtpGetFile;
FPF fFtpPutFile;
IC fInternetConnect;
IO fInternetOpen;
IOU fInternetOpenUrl;
ICU fInternetCrackUrl;
IRF fInternetReadFile;
ICH fInternetCloseHandle;

HANDLE ih;

// shell32.dll function variables
SE fShellExecute;
SHCN fSHChangeNotify;

//shlwapi.dll function variables
PRFS fPathRemoveFileSpec;


// icmp.dll function variables
#ifndef NO_PINGUDP
ICF fIcmpCreateFile;
ISE fIcmpSendEcho;
ICH fIcmpCloseHandle;
#endif

BOOL LoadDLLs(void) 
{
	// dynamically load kernel32.dll
	HMODULE kernel32_dll = GetModuleHandle("kernel32.dll");
	if (kernel32_dll) {
		fGetComputerName = (GCNA)GetProcAddress(kernel32_dll, "GetComputerNameA");
	}

	// dynamically load user32.dll
 	HMODULE user32_dll = LoadLibrary("user32.dll");
    if (user32_dll) {
		fIsWindow = (IW)GetProcAddress(user32_dll,"IsWindow");
	}

    // dynamically load ws2_32.dll
 	HMODULE ws2_32_dll = LoadLibrary("ws2_32.dll");
    if (ws2_32_dll) {
	 	fWSAStartup = (WSAS)GetProcAddress(ws2_32_dll,"WSAStartup");
		fWSASocket = (WSASo)GetProcAddress(ws2_32_dll,"WSASocketA");
		fWSAGetLastError = (WSAGLE)GetProcAddress(ws2_32_dll,"WSAGetLastError");
		fWSACleanup = (WSAC)GetProcAddress(ws2_32_dll,"WSACleanup");
  		fsocket = (SOCK)GetProcAddress(ws2_32_dll,"socket");
		fconnect = (CON)GetProcAddress(ws2_32_dll,"connect");
		finet_ntoa = (INTOA)GetProcAddress(ws2_32_dll,"inet_ntoa");
		finet_addr = (IADDR)GetProcAddress(ws2_32_dll,"inet_addr");
		fhtons = (HTONS)GetProcAddress(ws2_32_dll,"htons");
		fhtonl = (HTONL)GetProcAddress(ws2_32_dll,"htonl");
		fsend = (SEND)GetProcAddress(ws2_32_dll,"send");
		fsendto = (SENDTO)GetProcAddress(ws2_32_dll,"sendto");
		frecv = (RECV)GetProcAddress(ws2_32_dll,"recv");
		fsetsockopt = (SSO)GetProcAddress(ws2_32_dll,"setsockopt");
		fgetsockname = (GSN)GetProcAddress(ws2_32_dll,"getsockname");
		fgethostname = (GHN)GetProcAddress(ws2_32_dll,"gethostname");
		fgethostbyname = (GHBN)GetProcAddress(ws2_32_dll,"gethostbyname");
		fgetpeername = (GPN)GetProcAddress(ws2_32_dll,"getpeername");
		fclosesocket = (CLSO)GetProcAddress(ws2_32_dll,"closesocket");
		fshutdown = (SD)GetProcAddress(ws2_32_dll,"shutdown");
	}

	// dynamically load wininet.dll
	HMODULE wininet_dll = LoadLibrary("wininet.dll");
    if (wininet_dll) {
		fInternetGetConnectedState = (IGCS)GetProcAddress(wininet_dll, "InternetGetConnectedState");
	 	fInternetGetConnectedStateEx = (IGCSE)GetProcAddress(wininet_dll, "InternetGetConnectedStateEx");
	 	fHttpOpenRequest = (HOR)GetProcAddress(wininet_dll, "HttpOpenRequestA");
	 	fHttpSendRequest = (HSR)GetProcAddress(wininet_dll, "HttpSendRequestA");
		fFtpGetFile = (FGF)GetProcAddress(wininet_dll, "FtpGetFileA");
		fFtpPutFile = (FPF)GetProcAddress(wininet_dll, "FtpPutFileA");
	 	fInternetConnect = (IC)GetProcAddress(wininet_dll, "InternetConnectA");
	 	fInternetOpen = (IO)GetProcAddress(wininet_dll, "InternetOpenA");
	 	fInternetOpenUrl = (IOU)GetProcAddress(wininet_dll, "InternetOpenUrlA");
	 	fInternetCrackUrl = (ICU)GetProcAddress(wininet_dll, "InternetCrackUrlA");
	 	fInternetReadFile = (IRF)GetProcAddress(wininet_dll, "InternetReadFile");
	 	fInternetCloseHandle = (ICH)GetProcAddress(wininet_dll, "InternetCloseHandle");

		if (fInternetOpen) {
				ih = fInternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
				if (ih == NULL) ih = 0;
		}
	}

	// dynamically load shell32.dll
 	HMODULE shell32_dll = LoadLibrary("shell32.dll");
    if (shell32_dll) {
	 	fShellExecute = (SE)GetProcAddress(shell32_dll,"ShellExecuteA");
		fSHChangeNotify = (SHCN)GetProcAddress(shell32_dll,"SHChangeNotify");
	}

	// dynamically load shlwapi.dll
 	HMODULE shlwapi_dll = LoadLibrary("shlwapi.dll");
    if (shlwapi_dll) {
	 	fPathRemoveFileSpec = (PRFS)GetProcAddress(shlwapi_dll ,"PathRemoveFileSpecA");
	}

	#ifndef NO_PINGUDP
	// dynamically load icmp.dll
 	HMODULE icmp_dll = LoadLibrary("icmp.dll");
    if (icmp_dll) {
	 	fIcmpCreateFile = (ICF)GetProcAddress(icmp_dll,"IcmpCreateFile");
 		fIcmpCloseHandle = (ICH)GetProcAddress(icmp_dll,"IcmpCloseHandle");
 		fIcmpSendEcho = (ISE)GetProcAddress(icmp_dll,"IcmpSendEcho");
	}
	#endif

	return TRUE;
}
