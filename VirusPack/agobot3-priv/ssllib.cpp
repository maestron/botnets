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
#include "ssllib.h"

CSSLSocket::CSSLSocket()
{	m_psslCtx=NULL; m_pSSL=NULL; SSL_library_init(); m_bConnected=false; }

CSSLSocket::~CSSLSocket()
{	// Cleanup
	if(m_psslCtx) SSL_CTX_free(m_psslCtx);
	if(m_pSSL) { SSL_shutdown(m_pSSL); SSL_free(m_pSSL); }
	m_bConnected=false; }

bool CSSLSocket::Init()
{	m_bConnected=false;
	
	// Initialize the context, exit if fails
	m_psslCtx=SSL_CTX_new(SSLv3_method());	if(!m_psslCtx) return false;
	// Initialize the object, exit if fails
	m_pSSL=SSL_new(m_psslCtx);				if(!m_pSSL) return false;

	// Success
	return true; }

bool CSSLSocket::AttachToSocket(int sSocket)
{	m_bConnected=false;

	// Fail if not initialized
	if(!m_psslCtx || !m_pSSL) return false;

	// Store the socket, and attach it to the ssl object
	m_sSocket=sSocket;
	if(!SSL_set_fd(m_pSSL, m_sSocket)) return false;

	// Success
	return true; }

int CSSLSocket::GetSocket() { return m_sSocket; }

bool CSSLSocket::Accept()
{	m_bConnected=false;
	// Fail if not initialized
	if(!m_psslCtx || !m_pSSL) return false;
	if(SSL_accept(m_pSSL)==1)
	{	m_bConnected=true; return true; }
	else
	{	m_bConnected=false; return false; } }

bool CSSLSocket::Connect()
{	m_bConnected=false;
	// Fail if not initialized
	if(!m_psslCtx || !m_pSSL) return false;
	if(SSL_connect(m_pSSL)==1)
	{	m_bConnected=true; return true; }
	else
	{	m_bConnected=false; return false; } }

void CSSLSocket::Close()
{	SSL_shutdown(m_pSSL); m_bConnected=false; }

int CSSLSocket::Read(void *pBuf, int iNum)
{	if(!m_psslCtx || !m_pSSL || !m_bConnected) return 0;
	return SSL_read(m_pSSL, pBuf, iNum); }

int CSSLSocket::Write(const void *pBuf, int iNum)
{	if(!m_psslCtx || !m_pSSL || !m_bConnected) return 0;
	return SSL_write(m_pSSL, pBuf, iNum); }
