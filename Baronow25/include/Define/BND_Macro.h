#pragma once

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)	{ if(p) { (p)->Release(); (p)=NULL; } }
#endif


#ifndef SAFE_DELETE
#define SAFE_DELETE(p)	{ if(p){ delete p; p = NULL; } }
#endif


// �ܼ� vc2017 warning ���ֱ�
#define MAKEINTRESOURCE_EX(i)	MAKEINTRESOURCE( LOWORD(i) )




