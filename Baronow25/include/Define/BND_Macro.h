#pragma once

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)	{ if(p) { (p)->Release(); (p)=NULL; } }
#endif


#ifndef SAFE_DELETE
#define SAFE_DELETE(p)	{ if(p){ delete p; p = NULL; } }
#endif


// 단순 vc2017 warning 없애기
#define MAKEINTRESOURCE_EX(i)	MAKEINTRESOURCE( LOWORD(i) )




