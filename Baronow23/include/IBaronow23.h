#pragma once

#include <set>
#include <map>
#include <list>
#include <deque>
#include <vector>
#include <tuple>
#include <unordered_map>

#include <mutex>
#include <atomic>
#include <memory>
#include <thread>

#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;


#include <locale.h>		// setlocale
#include <sys/stat.h>	// __stati64
#include <atlimage.h>	// CImage


#include <Wininet.h>
#pragma comment(lib, "Wininet.lib") 


// 파일 버전 얻기용
#pragma comment(lib, "version.lib")


#include <Lm.h>
#pragma comment(lib, "netapi32.lib")


#include <wincrypt.h>
#pragma comment(lib, "advapi32")
#pragma comment(lib, "crypt32")

#include <atlcoll.h>

#include "Dwmapi.h"
#pragma comment (lib, "Dwmapi")


//#include <shellscalingapi.h>
//#pragma comment(lib, "Shcore.lib")


// warning C4100 : 참조되지 않은 정식 매개 변수입니다.
// warning C4189 : 지역 변수가 초기화되었으나 참조되지 않았습니다.
#pragma warning( disable : 4100 )
#pragma warning( disable : 4189 )


///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _BARONOW23_EXPORT_
#define BN23_TYPE		__declspec(dllexport)
#define BN23_TEMPLATE	extern
#else
#define BN23_TYPE		__declspec(dllimport)
#define BN23_TEMPLATE
#endif

#define BN23_CLASS		BN23_TYPE		//class BN23_TYPE
#define BN23_API(ret)	BN23_TYPE ret

#ifndef _AFXDLL
#define _AFXDLL
#endif

// sqlite 사용 안할꺼면 주석 처리
#define _USING_SQLITE_


////////////////////////////////////////////////////////////////////////////////////////////////////////
// 4byte hex 읽기

// h0 부터 시작
//#define RSHIFT_BIT(hPos)		( 28 - ( hPos * 4) )
//#define DWORD_BYTE(dw, hPos)	(BYTE)( ((0xf << RSHIFT_BIT(hPos)) & dw) >> RSHIFT_BIT(hPos) )
//#define RSHIFT_WORD(hPos)		( 24 - ( hPos * 8) )
//#define DWORD_WORD(dw, wPos)	(WORD)( ((0xff << RSHIFT_WORD(wPos)) & dw) >> RSHIFT_WORD(wPos) )

// h1 부터 시작
#define RSHIFT_BIT(hPos)		( 32 - ( hPos * 4) )
#define DWORD_BYTE(dw, hPos)	(BYTE)( ((0xf << RSHIFT_BIT(hPos)) & dw) >> RSHIFT_BIT(hPos) )
#define RSHIFT_WORD(hPos)		( 32 - ( hPos * 8) )
#define DWORD_WORD(dw, wPos)	(WORD)( ((0xff << RSHIFT_WORD(wPos)) & dw) >> RSHIFT_WORD(wPos) )


////////////////////////////////////////////////////////////////////////////////////////////////////////
// 8바이트 MAKE_LONG
#ifndef MAKE_LONGLONG
#define MAKE_LONGLONG(hi, lo)	( (LONGLONG(DWORD(hi) & 0xffffffff) << 32 ) | LONGLONG(DWORD(lo) & 0xffffffff) )
#endif 

#ifndef LO_LONG
#define LO_LONG(l64)			( (DWORD_PTR)(((LONGLONG)(l64)) & 0xffffffff) )
#endif

#ifndef HI_LONG
#define HI_LONG(l64)			( (DWORD_PTR)((((LONGLONG)(l64)) >> 32) & 0xffffffff) )
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)	{ if(p) { (p)->Release(); (p) = nullptr; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)	{ if(p) { delete p; p = nullptr;	} }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete [] p; p = nullptr;	} }
#endif

#ifndef ASSERT_RETNONE
#define ASSERT_RETNONE(p) {  auto f = (p); ASSERT(f); if(!(f)) { return; } }
#endif


#ifndef ASSERT_RETVAL
#define ASSERT_RETVAL(p, ret) {  auto f = (p); ASSERT(f); if(!(f)) { return ret; } }
#endif


#ifndef ASSERT_RET_FALSE
#define ASSERT_RET_FALSE(p) ASSERT_RETVAL(p, false)
#endif

#ifndef ASSERT_RET_TRUE
#define ASSERT_RET_TRUE(p) ASSERT_RETVAL(p, true)
#endif

/*
#ifndef IF_NOTEQUAL_RETURN
#define IF_NOTEQUAL_RETURN(func, compare) { auto ret = (func); if(ret != compare) { return ret; }   }
#endif

#ifndef ASSERT_IF_NOTEQUAL_RETURN
#define ASSERT_IF_NOTEQUAL_RETURN(func, compare) { auto ret = (func); if(ret != compare) { ASSERT(0); return ret; }   }
#endif
*/



////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __FUNCTIONT__
#ifdef _UNICODE
#define __FUNCTIONT__	__FUNCTIONW__
#else
#define __FUNCTIONT__	__FUNCTION__
#endif
#endif 


#ifndef __FILET__
#ifdef _UNICODE
#define __FILET__	__FILEW__
#else
#define __FILET__	__FILE__
#endif
#endif


#ifndef _todo
	#define LINE1(x) #x
	#define LINE(x) LINE1(x)
	#define _todo(msg) message(__FILE__"("LINE(__LINE__)") : [TODO] " msg)
#endif




///////////////////////////////////////////////////////////////////////////////////////////////////
#define ADJUST_RANGE(_num, _min, _max)	 { if(_num < _min) _num = _min; else if(_num > _max) _num = _max; }



#include "global/Logger.h"
#include "global/AutoLock.h"
#include "global/Performance.h"
#include "global/Utility.h"


#include "template/TBuffer.h"
#include "template/TSingleton.h"
#include "template/TNumerical.h"
#include "template/TContainer.h"

#include "interface/ISerialize.h"

#include "graphics/BitmapDC.h"
#include "graphics/PointCoord.h"
#include "graphics/CustomGraph.h"
#include "graphics/GradientRect.h"

#include "crypt/CryptFactory.h"
#include "crypt/CryptBuffer.h"
#include "crypt/A256B64.h"

#include "general/Stream.h"
#include "general/MsgThread.h"

#include "system/SystemInfo.h"
#include "system/MonitorInfo.h"


#ifdef _USING_SQLITE_
#include "database/SqliteQueryResult.h"
#include "database/Sqlite.h"
#include "database/SqliteBinary.h"
#endif


#include "api/gdi.h"
#include "api/file.h"
#include "api/time.h"
#include "api/crypt.h"
#include "api/image.h"
#include "api/string.h"
#include "api/system.h"
#include "api/window.h"
#include "api/numeric.h"
#include "api/monitor.h"
#include "api/factory.h"
#include "api/registry.h"

