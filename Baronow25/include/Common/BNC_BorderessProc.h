#pragma once

#include <versionhelpers.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")



#ifndef WM_NCUAHDRAWCAPTION
#define WM_NCUAHDRAWCAPTION (0x00AE)
#endif
#ifndef WM_NCUAHDRAWFRAME
#define WM_NCUAHDRAWFRAME (0x00AF)
#endif


#define BND_BORDERESS_PROC_PARAMS	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam
#define BND_BORDERESS_PROC_CALL		hWnd, message, wParam, lParam

#define BND_BORDERESS_DEFAULT_COLORKEY	RGB(255, 0, 255)


////////////////////////////////////////////////////////////////////////
// BNS_BorderessProcAttribute::dwState


// 내부 업데이트
#define BND_BRP_STATE_ENABLE				0x10000000
#define BND_BRP_STATE_USING_MOVE			0x20000000
#define BND_BRP_STATE_USING_SIZE			0x40000000

#define BND_BRP_STATE_DWM_COMPOSITION		0x01000000
#define BND_BRP_STATE_DWM_OPAQUE			0x02000000
#define BND_BRP_STATE_ACTIVE_THEME			0x04000000

#define BND_BRP_STATE_NC_CLICK				0x00100000
#define BND_BRP_STATE_NC_DEFAULT			0x00200000
#define BND_BRP_STATE_NC_CUSTOM				0x00400000
#define BND_BRP_STATE_NC_TRANSFORM			0x00800000
#define BND_BRP_STATE_PAUSE_CAPTURE			0x00010000


// initialize 사용자 설정
#define BND_BRP_STATE_USING_ALPHA			0x00000001
#define BND_BRP_STATE_USING_COLORKEY		0x00000002
#define BND_BRP_STATE_USING_CUSTOM_RESIZE	0x00000004
#define BND_BRP_STATE_USING_DWM_FRAME		0x00000008
////////////////////////////////////////////////////////////////////////


struct BNS_BorderessProcAttribute
{
	BNS_BorderessProcAttribute(void)
	{
		Clear();
	};

	void Clear(void)
	{

		dwState	= BND_BRP_STATE_USING_ALPHA | BND_BRP_STATE_USING_DWM_FRAME;

#ifdef _USING_BORDERESS_CUSTOM_
		dwState	|= BND_BRP_STATE_USING_CUSTOM_RESIZE;
#endif
	
		btAlpha		= 255;
		colorKey	= 0;
		iHiddenFrm	= 0;

		bStretchCaption = true;
		iStretchCaption = 0;
	};
	
	DWORD		dwState;
	BYTE		btAlpha;
	COLORREF	colorKey;
	int			iHiddenFrm;

	bool		bStretchCaption;
	int			iStretchCaption;
};


class BNC_FakeWindow;
class BN25_TYPE BNC_BorderessProc
{
public:
	BNC_BorderessProc();
	~BNC_BorderessProc();
	

private:
	HWND		m_hTarget;
	HWND		m_hRootClient;
	WNDPROC		m_pOldProc;
	DWORD		m_dwRestoreStyle;
	BNS_BorderessProcAttribute	m_Attribute;
	BNC_FakeWindow *m_pFakeWindow;

	
	DWORD		m_dwDwmColorization;
	CRect		m_rcApplyRgn;
	CSize		m_szClient;
	CSize		m_szWndMin;
	CSize		m_szWndMax;


	UINT	m_uiHitTest;
	CSize	m_szLBtnMargins;
	CRect	m_rcLastUpdate;
	CRect	m_rcWndNcClick;
	WINDOWPOS m_LastWinPos;



	// rootclient에 가려져 있던 부분 투명색(nullbrush)으로 채워지지 않는 경우 기본색으로 칠해주기 위함
	CBrush	m_brushBkgnd;

	
public :
#ifdef _USING_TRANSPARENT_RESIZING_
	CRect	m_rcBeforeCustomRoot;
#endif


private:
	static LRESULT	CALLBACK WndProc(BND_BORDERESS_PROC_PARAMS);
	static bool AssertValid(BNC_BorderessProc *pProc, HWND hWnd);

	static HHOOK				s_KeyHook;
	static HHOOK				s_MouseHook;
	static BNC_BorderessProc	*s_pHookTarget;
	static LRESULT	CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT	CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

private:
	LRESULT DefWindowProc(BND_BORDERESS_PROC_PARAMS);
	LRESULT OldWndProc(BND_BORDERESS_PROC_PARAMS);


private:
	LRESULT OnDestroy(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnEraseBkgnd(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnPaint(BND_BORDERESS_PROC_PARAMS);
	
	LRESULT OnNcActivate(BND_BORDERESS_PROC_PARAMS);
	LRESULT	OnNcCalcSize(BND_BORDERESS_PROC_PARAMS);
	LRESULT	OnNcHitTest(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnNcPaint(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnNcMouseMove(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnNcLBtnDown(BND_BORDERESS_PROC_PARAMS);
	
	LRESULT OnThemeChanged(BND_BORDERESS_PROC_PARAMS, bool bUpdate = true);
	LRESULT OnDwmCompositionChanged(BND_BORDERESS_PROC_PARAMS, bool bUpdate = true, bool bInInitialize = false);
	LRESULT OnDwmColorizationColorChanged(BND_BORDERESS_PROC_PARAMS, bool bUpdate = true);

	LRESULT OnSetIcon(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnSetText(BND_BORDERESS_PROC_PARAMS);

	LRESULT OnSizing(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnWindowPosChanging(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnWindowPosChanged(BND_BORDERESS_PROC_PARAMS);
	
	
	LRESULT OnMouseMove(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnLBtnDown(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnLBtnUp(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnLButtonDblClk(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnCaptureChanged(BND_BORDERESS_PROC_PARAMS);
	LRESULT OnGetMinMaxInfo(BND_BORDERESS_PROC_PARAMS);
	

//private:
public :
	void	Clear(void);

private :
	bool	IsAutoHideBar(UINT uiEdge, CRect rcMonitor);
	void	UpdateRegion(void);
	inline void UpdateState(BOOL bAdd, DWORD dwFlags);

	void	UpdateHook(bool bEnable);
	bool	KeydownProcess(DWORD dwKey);
	bool	MouseProcess(void);


	// HTCLIENT
	// HTCAPTION
	// HTLEFT ~ HTBOTTOMRIGHT
	UINT	GetHitTest(const CPoint &point);
	void	UpdateCursor(UINT uiHitTest);
	void	UpdateNonClientClick(bool bEnable);
	bool	UpdateResizing(CPoint ptMove);


	// 특정모니터의 iVertical이 반영된 영역(top, bottom margins 적용)의
	// out 영역에 pt 포함여부
	// return 모니터 번호
	int		PtOutMonitor(CPoint &pt, int iVertical);


	// OnWindowPosChanged 에서 호출
	// default 처리되는 nc 리사이징을 custom으로 변경
	// return false : 변경않함
	bool	TransformNcDefaultToCustom(BND_BORDERESS_PROC_PARAMS);

	// OnMouseMove에서 호출
	// custom 처리되는 nc 리사이징을 default로 변경
	// return false : 변경 않함(최종)
	bool	TransformNcCustomToDefault(HWND hWnd, CPoint &ptClient, _Ret_ CPoint &ptScreen);
	


public:
	bool	Initialize(HWND hTarget, HWND hRootClient, BNS_BorderessProcAttribute *pAttribute);
	bool	UpdateLayered(BYTE btAlpha);
	
	int		GetHiddenFrameSize(void) const;
	bool	IsEnable(void) const;
	bool	CheckState(DWORD dwFlags) const;
	bool	DrawTransparent(CDC *pDC, _Ret_ CRect *prcExclude = NULL);
	const BNS_BorderessProcAttribute* GetAttribute(void);	


	void	UpdateMouseCaption(bool bStretch, int iStretch);
	UINT	GetHitTest(void);

public :
	// 창상태에 상관없는 hit test code 반환
	// HTCLIENT
	// HTLEFT ~ HTBOTTOMRIGHT
	UINT	GetHitTest(const CPoint &point, const CSize &szClient);
};

