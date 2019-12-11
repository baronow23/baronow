#pragma once

// ����� ������ ��
enum BNE_BTN_STATE
{
	BNE_BTN_STATE_NORMAL	= 0,
	BNE_BTN_STATE_FOCUS		= 1,
	BNE_BTN_STATE_DOWN		= 2,
	BNE_BTN_STATE_DISABLE	= 3,

	// Ȯ�� (���º��� ���� ��Ƽ�� ����)
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
	// ��ư ���� �׸���
	CBitmap*		m_pResBitmapPtr;
	Gdiplus::Image* m_pResImagePtr;
	CPoint			m_ptResource;
	CSize			m_szResource;
	UINT			m_uiResourceLine;

	/////////////////////////////////////////
	// ��ư �׵θ� �׸���
	bool			m_bDrawEdge;
	COLORREF		m_pEdgeColor;


public :
	// �ؽ�Ʈ ���
	CString				m_strResource;
	CRect				m_rcTextBlank;
	CSize				m_szTextDraw;		// m_strResource�� ����ϱ� ���� ũ�� (m_rcTextBlank ������)
	COLORREF			m_pTextColor[4];
	BNE_FONT_STYLE		m_pFontStyle[4];
	UINT				m_uiTextAlign;
	int					m_iCharExtra;		// ���ڰ���
	CPoint				m_ptTextAdd;		// ���� �ؽ�Ʈ ��� ��ġ ���� ��
	

protected:
	CFont			m_fontNormal;
	CFont			m_fontNormalLine;
	CFont			m_fontBold;
	CFont			m_fontBoldLine;


	// ����
	BNE_BTN_STATE	m_State;
	BNE_BTN_STATE	m_StateAnimation;
	bool			m_bLBtnDn;
	bool			m_bRBtnDn;
	bool			m_bEntry;
	bool			m_bUseAlwaysDown;
	UINT			m_uiMouseMoveCount;	// ReleaseCapture���� ����



	// ��ư Ŭ���ø��� �θ𿡰� �˸����� ����
	baro::Performance m_chkAnimation;
	bool	m_bEnableDownStateAnimation;
	UINT	m_uiEndStateAnimationTime;
	float	m_fStateAnimationRatio;
	

public :
	// ���� �̹��� ���ҽ� ���
	bool	m_bUsingeSingleImage;


	// FOCUS �̺�Ʈ �� �׸��� �н�
	bool	m_bPassFocusState;


	// �ӽ�
	TCHAR	m_cID;

public :

	// Ŀ�� ����(Focus, Down ����)
	void	SetCursor(HCURSOR hCursor);


	// ��� ����
	void	SetUseParentBk(bool bEnable);
	void	SetBkColor(COLORREF clrNormal, COLORREF clrFocus, COLORREF clrDown, COLORREF clrDisable, bool bRedraw = false);
	void	SetBkColor(COLORREF clrAll, bool bRedraw = false);

	// �׵θ� ����
	void	SetEdgeColor(COLORREF clrEdge);


	// ��ư ���¿� ���� �׸��� (�Ѱ����� ��� ����)
	CString GetText(void);
	void	SetTextBlank(CRect rcBlank);
	void	SetTextResource(CString str, bool bRedraw = false, bool bUpdateFit = true);
	void	SetTextResource(CString str, CRect rcBlank, int iCharExtra = 0, bool bRedraw = false, bool bUpdateFit = true);
	void	SetTextAlign(UINT uiAlign);
	void	SetBitmapResource(CBitmap* pBitmapPtr, CPoint ptLeftTop, CSize szQuarter, bool bRedraw = false);
	void	SetImageResource(Gdiplus::Image* pImagePtr, CPoint ptLeftTop, CSize szQuarter, bool bRedraw = false);


	// SetBitmapResource, SetImageResource �ɼ�
	void	SetResourceLine(UINT uiResLine, bool bRedraw = true);
	UINT	GetResourceLine(void);


	// SetStateText �ɼ�
	void	SetTextFont(LPCTSTR strFont, UINT iHeight, int iLetterSpacing, bool bRedraw = false);
	void	SetTextFontStyle(BNE_FONT_STYLE normal, BNE_FONT_STYLE down, BNE_FONT_STYLE focus, BNE_FONT_STYLE disable, bool bRedraw = false);
	void	SetTextColor(COLORREF clrNormal, COLORREF clrFocus, COLORREF clrDown, COLORREF clrDisable, bool bRedraw = false);

	void	SetTextColor(COLORREF clrAll, bool bRedraw = false);
	CSize	GetTextDisplaySize(void);
	void	SetWindowPosFromText(void);

	
	// �׻� �ٿ���·� �������� ����
	void	EnableAlwaysDown(bool bEnable, bool bRedraw = false);
	
	
	// ���� ���� ����
	void			SetState(BNE_BTN_STATE state);
	void			SetStateAnimation(BNE_BTN_STATE stBegin, BNE_BTN_STATE stEnd, UINT uiStay);
	BNE_BTN_STATE	GetState(void);
	

	// ��ư Ŭ���ø��� �θ� Ŭ���̾�Ʈ�� �̺�Ʈ ���� ���
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

