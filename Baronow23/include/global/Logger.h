#pragma once


namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
	// 0 : °ËÁ¤		// 8 : ¿¬°ËÁ¤ (È¸»ö)
	// 1 : ÆÄ¶û		// 9 : ¿¬ÆÄ¶û
	// 2 : ÃÊ·Ï		// A : ¿¬ÃÊ·Ï
	// 3 : ¿Á»ö		// B : ¿¬¿Á»ö
	// 4 : »¡°­		// C : ¿¬»¡°­
	// 5 : ÀÚÁÖ		// D : ¿¬ÀÚÁÖ
	// 6 : ³ë¶û		// E : ¿¬³ë¶û
	// 7 : Èò»ö		// F : ¹àÀºÈò»ö
	
	enum class TextColor
	{
		BLACK = 0,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		YELLOW,
		WHITE,

		LIGHT_BLACK = 8,
		LIGHT_BLUE,
		LIGHT_GREEN,
		LIGHT_CYAN,
		LIGHT_RED,
		LIGHT_MAGENTA,
		LIGHT_YELLOW,
		LIGHT_WHITE,
	};


	namespace logger
	{
		BN23_API(void)	SetMainThreadID(DWORD dwThreadID);
		BN23_API(void)	Trace(TextColor color, LPCTSTR lpszFile, LONG iLine, LPCTSTR lpszFunc, LPCTSTR lpszFormat, ...);
		BN23_API(void)	TraceConstruct(LPCTSTR lpszFunc, bool bPrint = true);
		BN23_API(void)	TraceDestruct(LPCTSTR lpszFunc, bool bPrint = true);
		BN23_API(void)	TraceBuffer(TextColor TxtColor, const BYTE* pDataPtr, size_t iLength);

		BN23_API(void)	Begin(bool bUseConsoleTrace, bool bWriteLog, bool bDisableScreenSaver = false);
		BN23_API(void)	End(void);
		BN23_API(bool)	IsRunning(void);
		BN23_API(bool)	IsVisible(void);
		BN23_API(void)	ShowConsole(bool bShow);
		BN23_API(void)	EnablePrint(bool bEnable);

		BN23_API(CString) GetClassName(CString strFunc);
		BN23_API(CString) GetMethodName(CString strFunc);

	};

//////////////////////////////////////////////////////////////////////////////////////////
};

#ifdef _DEBUG

	#define _traceW(...)			baro::logger::Trace(baro::TextColor::WHITE, __FILET__, __LINE__, __FUNCTIONT__, __VA_ARGS__)
	#define _traceWC(clr, ...)		baro::logger::Trace(clr, __FILET__, __LINE__, __FUNCTIONT__, __VA_ARGS__)

	#define _trace(...)				_traceW( L ## __VA_ARGS__ )
	#define _traceC(clr, ...)		_traceWC( clr, L ## __VA_ARGS__ )

	#define _traceBlack(...)		_traceWC(baro::TextColor::LIGHT_BLACK,	L ## __VA_ARGS__)	
	#define _traceBlue(...)			_traceWC(baro::TextColor::LIGHT_BLUE,	L ## __VA_ARGS__)	
	#define _traceGreen(...)		_traceWC(baro::TextColor::LIGHT_GREEN,	L ## __VA_ARGS__)
	#define _traceCyan(...)			_traceWC(baro::TextColor::LIGHT_CYAN,	L ## __VA_ARGS__)
	#define _traceRed(...)			_traceWC(baro::TextColor::LIGHT_RED,	L ## __VA_ARGS__)
	#define _traceMagenta(...)		_traceWC(baro::TextColor::LIGHT_RED,	L ## __VA_ARGS__)
	#define _traceYellow(...)		_traceWC(baro::TextColor::LIGHT_YELLOW, L ## __VA_ARGS__)
	#define _traceWhite(...)		_traceWC(baro::TextColor::LIGHT_YELLOW, L ## __VA_ARGS__)

	#define _traceErr(...)			_traceWC(baro::TextColor::LIGHT_RED, L ## __VA_ARGS__)
	#define _traceSysErr(code)		_traceC( baro::TextColor::LIGHT_RED, "(0x%08X) %s", code, (LPCTSTR)bapi::MakeErrorString(code))
	#define _traceGdiErr(status)	if(status != Gdiplus::Status::Ok){ _traceC( baro::TextColor::LIGHT_RED, "(0x%08X) %s", status, (LPCTSTR)bapi::MakeGdiErrorString(status)); }
	#define _traceException(e)		_traceC( baro::TextColor::LIGHT_RED, "%s", (LPCTSTR)bapi::MakeExceptionString(e))

	#define _traceString(str)		_trace("%s", (LPCTSTR)str)
	#define _traceLine				_traceC(baro::TextColor::LIGHT_MAGENTA, "--------------------------------------------------------------")

	#define _trace_construct		baro::logger::TraceConstruct(__FUNCTIONT__)
	#define _ntrace_construct		baro::logger::TraceConstruct(__FUNCTIONT__, false)
	#define _trace_destruct			baro::logger::TraceDestruct(__FUNCTIONT__)
	#define _ntrace_destruct		baro::logger::TraceDestruct(__FUNCTIONT__, false)

	#define _trace_callstack		_traceC(baro::TextColor::LIGHT_BLACK, "")
	#define _trace_checkstack		_traceC(baro::TextColor::LIGHT_CYAN, "")

	#define _trace_begin_perc		baro::Performance chkPerc
	#define _trace_end_perc			chkPerc.Check(); _trace("%lf", chkPerc.m_lfElapseTime)

	#define _className				baro::logger::GetClassName(__FUNCTIONT__)
	#define _methodName				baro::logger::GetMethodName(__FUNCTIONT__)

	#define _beginPerformance		Performance perc;
	#define _resetPerformance		perc.Reset();
	#define _checkPerformance		{ perc.Check(); _traceC( baro::TextColor::LIGHT_YELLOW, "	%lf ms", perc.m_lfElapseTime); perc.Reset(); }

#else

	#define _traceW(...)
	#define _traceWC(clr, ...)
	#define _trace(...)		
	#define _traceC(clr, ...)
	#define _traceBlack(...)		
	#define _traceBlue(...)			
	#define _traceGreen(...)	
	#define _traceCyan(...)		
	#define _traceRed(...)		
	#define _traceMagenta(...)	
	#define _traceYellow(...)	
	#define _traceWhite(...)	
	#define _traceErr(...)	
	#define _traceSysErr(code)
	#define _traceGdiErr(status)
	#define _traceException(e)

	#define _traceString(str)
	#define _traceLine		

	#define _trace_construct
	#define _ntrace_construct
	#define _trace_destruct	
	#define _ntrace_destruct

	#define _trace_callstack
	#define _trace_checkstack

	#define _trace_begin_perc
	#define _trace_end_perc

	#define _className
	#define _methodName

	#define _beginPerformance
	#define _resetPerformance
	#define _checkPerformance

#endif