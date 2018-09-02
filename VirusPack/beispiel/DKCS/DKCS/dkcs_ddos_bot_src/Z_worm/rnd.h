//-----------------------------------------------------------------
// this file is a part of: DKCS LoadSystem v. 0.1a
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
// Special work for Panda
//-----------------------------------------------------------------
unsigned long rs_randseed;
//-----------------------------------------------------------------
void _srand(){
	rs_randseed = GetTickCount();
}
//-----------------------------------------------------------------
unsigned long _rand(){
	rs_randseed++;
	return (rs_randseed*0xF02CE551) + 0x7FF2742B;
}
//-----------------------------------------------------------------