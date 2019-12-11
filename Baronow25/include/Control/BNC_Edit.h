#pragma once



enum BNE_EDIT_EVENT
{
	BNE_EDIT_EVENT_FOCUS,
	BNE_EDIT_EVENT_UPDATE,
	BNE_EDIT_EVENT_SYSKEY,
	BNE_EDIT_EVENT_MOUSE_RDN,
	BNE_EDIT_EVENT_CF_IMAGE,	// LPARAM : BNC_ClipboardImage*

	// ���̵� �׸��� �Ϸ��� �θ𿡰� ����
	// LPARAM : *CDC (���� ��� �ʿ�� ���)
	BNE_EDIT_EVENT_DRAW_GUIDE,
};


class BN25_TYPE BNC_EditState
{
public :
	BNC_EditState()
	{
		_ntrace_construct;
		iSelStart = 0;
		iSelEnd = 0;
	};
	~BNC_EditState()
	{
		_ntrace_destruct;
	};

	BNC_EditState(const BNC_EditState &rhs)
	{
		(*this) = rhs;
	};

	BNC_EditState& operator=(const BNC_EditState &rhs)
	{
		strText		= rhs.strText;
		iSelStart	= rhs.iSelStart;
		iSelEnd		= rhs.iSelEnd;
		return (*this);
	};

	CString strText;
	int		iSelStart;
	int		iSelEnd;
};



// BNC_Edit
class BN25_TYPE BNC_Edit : public CEdit
{
	DECLARE_DYNAMIC(BNC_Edit)

public :
	BNC_Edit();
	~BNC_Edit();


private:
	int		m_iFocus;
	CSize	m_szClient;
	
	// ����Ʈ �ؽ�Ʈ
	CString		m_strEdit;
	CString		m_strOldEdit;
	int			m_iLength;
	CFont		*m_pNormalFontPtr;
	CFont		*m_pBoldFontPtr;
	CFont		*m_pSelectFontPtr;


	// enterŰ ������ �� �ؽ�Ʈ
	// ���� ����� ������ �޽��� �߻� ����
	CString		m_strEnter;


	// �ؽ�Ʈ ���Է½� ������ ���̵�
	CString		m_strGuide;
	CFont		*m_pGuideFontPtr;
	COLORREF	m_colorGuide;

	CString		m_strGuideAdd;
	COLORREF	m_colorGuideAdd;
	

	// ���, �ؽ�Ʈ ��
	COLORREF	m_colorEnableBk;
	COLORREF	m_colorDisableBk;
	COLORREF	m_colorTextFocus;
	COLORREF	m_colorTextUnFocus;
	CBrush		m_brushEnableBk;
	CBrush		m_brushDisableBk;
	CBrush		m_brushNull;


public :
	// ������ �Էµ� Ű
	WPARAM	m_LastKey;


	// ��Ÿ ����� �ɼ�
	bool	m_bUseSwitchBold;	// Ctrl + BŰ�� �ؽ�Ʈ bold ��ȯ
	bool	m_bUseDialMode;		// ���̾�Ű������ ��� (0~9, *, #�� ���)
	bool	m_bUseArrowKey;		// ����Ű �Է½� ���� : SendMessage�� 1��ȯ�� ����Ʈ �ڽ� �Է� ����
	bool	m_bUsePageKey;		// home/end/page up-down Ű ���� : SendMessage�� 1��ȯ�� ����Ʈ �ڽ� �Է� ����

private :
	//void	UpdateInvalidate();
	void	SetSelectFont(CFont* pFont, bool bRedraw = true);
	void	DrawGuideText(void);
	void	DrawGuideText(CDC* pDC);
	void	DrawGuideTextFinish(CDC *pDC, int x, int y, CString &strGuide);
	bool	IsDialKey(WPARAM wKey);


public :
	void	AddEOL(void);
	void	DrawGuideText(CDC* pMemDC, CPoint &point);



public :
	void		SetText(LPCTSTR strText, bool bRedraw);
	CString		GetText(void);
	int			GetTextLength(void);
	void		SetGuideText(CString strGuide);
	void		SetGuideText(CString strGuide, COLORREF color, CFont* pFontPtr = NULL, bool bReDraw = false);
	void		SetGuideTextAdd(CString strGuideLast, COLORREF color);
	void		SetFontPtr(CFont* pNormal, CFont* pBold, bool bSelectNormal);
	COLORREF	GetBkColor(void);
	

	// ���, �ؽ�Ʈ ���� ���� EnableWindow(FALSE)�� ���� �ؽ�Ʈ �� ���� �ʵǰ� ȸ������ ǥ����
	void	SetTextColor(COLORREF clrFocus, COLORREF clrUnFocus, bool bReDraw = false);
	void	SetBkColor(COLORREF clrEnable, COLORREF clrDisable, bool bReDraw = false);

	


protected :
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()


public :
	afx_msg void	OnDestroy();
	afx_msg void	OnPaint();
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);


	//afx_msg HBRUSH	CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void	OnEnUpdate();
	afx_msg void	OnEnSetfocus();
	afx_msg void	OnEnKillfocus();
	

	afx_msg BOOL	OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg HBRUSH	CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};


