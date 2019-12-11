#pragma once

// 상수값 고정할 것
enum BNE_BTN_STATE
{
	BNE_BTN_STATE_NORMAL	= 0,
	BNE_BTN_STATE_FOCUS		= 1,
	BNE_BTN_STATE_DOWN		= 2,
	BNE_BTN_STATE_DISABLE	= 3,

	// 확장 (상태변경 없이 노티만 보냄)
	BNE_BTN_STATE_RDOWN		= 4,
};

class BN25_TYPE BNC_Button : public BNC_BaseControl
{
public:
	BNC_Button();
	virtual ~BNC_Button();

protected :
	HCURSOR			m_hCursor;
	COLORREF		m_pBkColor[4];	// Normal, Focus, Down, Disable



	/////////////////////////////////////////
	// 버튼 상태 그리기
	CBitmap*		m_pResBitmapPtr;
	Gdiplus::Image* m_pResImagePtr;
	CPoint			m_ptResource;
	CSize			m_szResource;
	UINT			m_uiResourceLine;

	/////////////////////////////////////////
	// 버튼 테두리 그리기
	bool			m_bDrawEdge;
	COLORREF		m_pEdgeColor;


public :
	// 텍스트 사용
	CString				m_strResource;
	CRect				m_rcTextBlank;
	CSize				m_szTextDraw;		// m_strResource을 출력하기 위한 크기 (m_rcTextBlank 미적용)
	COLORREF			m_pTextColor[4];
	BNE_FONT_STYLE		m_pFontStyle[4];
	UINT				m_uiTextAlign;
	int					m_iCharExtra;		// 글자간격
	CPoint				m_ptTextAdd;		// 최종 텍스트 출력 위치 조정 값
	

protected:
	CFont			m_fontNormal;
	CFont			m_fontNormalLine;
	CFont			m_fontBold;
	CFont			m_fontBoldLine;


	// 제어
	BNE_BTN_STATE	m_State;
	BNE_BTN_STATE	m_StateAnimation;
	bool			m_bLBtnDn;
	bool			m_bRBtnDn;
	bool			m_bEntry;
	bool			m_bUseAlwaysDown;
	UINT			m_uiMouseMoveCount;	// ReleaseCapture에서 리셋



	// 버튼 클릭시마다 부모에게 알림여부 결정
	baro::Performance m_chkAnimation;
	bool	m_bEnableDownStateAnimation;
	UINT	m_uiEndStateAnimationTime;
	float	m_fStateAnimationRatio;
	

public :
	// 단일 이미지 리소스 사용
	bool	m_bUsingeSingleImage;


	// FOCUS 이벤트 및 그리기 패스
	bool	m_bPassFocusState;


	// 임시
	TCHAR	m_cID;

public :

	// 커서 설정(Focus, Down 상태)
	void	SetCursor(HCURSOR hCursor);


	// 배경 설정
	void	SetUseParentBk(bool bEnable);
	void	SetBkColor(COLORREF clrNormal, COLORREF clrFocus, COLORREF clrDown, COLORREF clrDisable, bool bRedraw = false);
	void	SetBkColor(COLORREF clrAll, bool bRedraw = false);

	// 테두리 설정
	void	SetEdgeColor(COLORREF clrEdge);


	// 버튼 상태에 따라 그리기 (한가지만 사용 가능)
	CString GetText(void);
	void	SetTextBlank(CRect rcBlank);
	void	SetTextResource(CString str, bool bRedraw = false, bool bUpdateFit = true);
	void	SetTextResource(CString str, CRect rcBlank, int iCharExtra = 0, bool bRedraw = false, bool bUpdateFit = true);
	void	SetTextAlign(UINT uiAlign);
	void	SetBitmapResource(CBitmap* pBitmapPtr, CPoint ptLeftTop, CSize szQuarter, bool bRedraw = false);
	void	SetImageResource(Gdiplus::Image* pImagePtr, CPoint ptLeftTop, CSize szQuarter, bool bRedraw = false);


	// SetBitmapResource, SetImageResource 옵션
	void	SetResourceLine(UINT uiResLine, bool bRedraw = true);
	UINT	GetResourceLine(void);


	// SetStateText 옵션
	void	SetTextFont(LPCTSTR strFont, UINT iHeight, int iLetterSpacing, bool bRedraw = false);
	void	SetTextFontStyle(BNE_FONT_STYLE normal, BNE_FONT_STYLE down, BNE_FONT_STYLE focus, BNE_FONT_STYLE disable, bool bRedraw = false);
	void	SetTextColor(COLORREF clrNormal, COLORREF clrFocus, COLORREF clrDown, COLORREF clrDisable, bool bRedraw = false);

	void	SetTextColor(COLORREF clrAll, bool bRedraw = false);
	CSize	GetTextDisplaySize(void);
	void	SetWindowPosFromText(void);

	
	// 항상 다운상태로 유지할지 변경
	void	EnableAlwaysDown(bool bEnable, bool bRedraw = false);
	
	
	// 상태 강제 변경
	void			SetState(BNE_BTN_STATE state);
	void			SetStateAnimation(BNE_BTN_STATE stBegin, BNE_BTN_STATE stEnd, UINT uiStay);
	BNE_BTN_STATE	GetState(void);
	

	// 버튼 클릭시마다 부모 클라이언트에 이벤트 전달 등록
	void			EnableDownStateProgress(bool bEnable, UINT uiEndProgressTime);
	float			GetStateAnimationRatio(void);

protected :
	bool			OnDraw(CDC* pMemDC, CDC* pResDC);
	virtual bool	OnDrawEx(CDC* pMemDC, CDC* pResDC, Gdiplus::Graphics *pGraphics, UINT iStateIndex);
	


protected :
	LRESULT	UpdateState(BNE_BTN_STATE State, const CPoint &ptMouse, bool bParentNotify, bool bRedraw = true);
	


public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

