#pragma once



// �θ�������� �ݵ��  BNC_BaseClient �̿�����!!

class BN25_TYPE BNC_EditboxEx : public BNC_BaseClient
{
public:
	BNC_EditboxEx();
	virtual ~BNC_EditboxEx();


private :
	// �Է� ����Ʈ ��ü
	BNC_Edit	m_Edit;
	USHORT		m_uiEditID;


	// ũ�� ����
	CRect		m_rcBlank;		// �Է� ����Ʈ���� �����¿� ����
	int			m_iTextWidth;	// ��°����� �ؽ�Ʈ ����(�ȼ���ǥ)
	int			m_iFontHeight;	// ��Ʈũ��
	int			m_iEditHeight;


	// ���� ��Ʈ
	CFont		m_fontNormal;
	CFont		m_fontBold;


	// ����Ʈ ��Ŀ�� ���¿� ���� �׷��� �׵θ�
	COLORREF	m_pColorEdge[2];
	CPen		m_pPenEdge[2];
	
	// �׵θ� ��� ���� ; true : �簢 �׵θ� ǥ�� | false : ���ٷ� ǥ�� (�α��� ��)
	bool		m_bUseBorder;


private :
	// �ɼ� : delete ��ư ���� ����
	//(�ؽ�Ʈ ���� ���� �� �������� ���� �� ������)
	BNC_Button	m_btnClear;
	CPoint		m_ptBtnClearPos;	// x = Ŭ���̾�Ʈ right��ġ���� �������� ��ġ�� ��, y = Ŭ���̾�Ʈ top ���� ��ġ
	


	// ����Ʈ ������ ������ �̹��� ���� ����
	CBitmap*		m_pGuideBmPtr;
	Gdiplus::Image* m_pGuideImgPtr;
	CPoint			m_ptGuideImageDraw;	// ��� ��ġ (LeftTop)
	CPoint			m_ptGuideImage;		// ���ҽ� ��ġ
	CSize			m_szGuideImage;		// ���ҽ� ũ��


	// ����Ʈ ������ ������ �̹��� ���� ���� (Focus ����)
	CBitmap*		m_pGuideBmPtr2;
	Gdiplus::Image* m_pGuideImgPtr2;
	CPoint			m_ptGuideImageDraw2;	// ��� ��ġ (LeftTop)
	CPoint			m_ptGuideImage2;		// ���ҽ� ��ġ
	CSize			m_szGuideImage2;		// ���ҽ� ũ��



public :
	// true : �Է� �ؽ�Ʈ�� ���� �� �������� ������ �� ������ (default = false)
	// false : show/hide ����� ���� (ShowClearButton���)
	bool	m_bAutoClearButton;

	
	// SetText, AddEOL, SetState ȣ��� bAfterEvent�� false�� �����ϰų� 
	// Ư�� ������ ����Ʈ �ڽ� ������Ʈ�� �Ͻ������� �ް���� ���� �� 1ȸ�� ���Ͽ� �θ𿡰� �̺�Ʈ �߻� ����
	bool	m_bPassNextUpdateNoti;



private:
	bool	OnCreate(void);
	void	OnModifyPopupPtr(BNC_BaseDialog* pNewPopup);
	void	OnUpdateSize(int cx, int cy);				
	bool	OnDraw(CDC* pMemDC, CDC* pResDC);			
	LRESULT OnMessageEdit(WPARAM wParam, LPARAM lParam);
	LRESULT OnMessageButton(WPARAM wParam, LPARAM lParam);


public:
	// create ���� ��Ʈ�� ����
	bool	CreateEdit(USHORT m_uiEventID, CRect rcBlank, CString strFont, int iFontHeight, DWORD dwStyle, bool bUseBorder = true);
	bool	CreateClearButtonBm(USHORT uiEventID, CPoint ptSyncRT, CBitmap *pBitmapPtr, CPoint ptRes, CSize szRes4);
	bool	CreateClearButtonImg(USHORT uiEventID, CPoint ptSyncRT, Gdiplus::Image* pImgPtr, CPoint ptRes, CSize szRes4, COLORREF clrBk);
	void	SetClearBtnTooltip(CString strTip);


	// ���̵� �̹��� ����
	void	SetGuideBitmap(CBitmap* pBitmapPtr, CPoint ptDrawPos, CPoint ptRes, CSize szRes);
	void	SetGuideImage(Gdiplus::Image* pImgPtr, CPoint ptDrawPos, CPoint ptRes, CSize szRes);

	void	SetGuideBitmapFocus(CBitmap* pBitmapPtr, CPoint ptDrawPos, CPoint ptRes, CSize szRes);
	void	SetGuideImageFocus(Gdiplus::Image* pImgPtr, CPoint ptDrawPos, CPoint ptRes, CSize szRes);


	// ����Ʈ �ڽ� �Է� ���ڰ� ���� �� ������ �޽��� ���
	// ���� �Է��� ���۵Ǹ� �޽����� ������� �Է¹��ڰ� �������� �ٽ� ���
	// pFont �������� initalize���� ������ ��Ʈ ���
	void	SetGuideText(CString strGuide);
	void	SetGuideText(CString strGuide, COLORREF color, CFont* pFontPtr);
	void	SetGuideTextAdd(CString strGuideLast, COLORREF color);



	// ���, �ؽ�Ʈ ���� ���� EnableWindow(FALSE)�� ���� �ؽ�Ʈ �� ���� �ʵǰ� ȸ������ ǥ����
	void	SetTextColor(COLORREF clrFocus, COLORREF clrUnFocus, bool bReDraw = true);
	void	SetBkColor(COLORREF clrEnable, COLORREF clrDisable, bool bReDraw = true);


	// �׵θ� ���� ����
	void	SetEdgeColor(COLORREF clrUnFocus, COLORREF clrFocus, bool bReDraw = true);


	// �ؽ�Ʈ ����, ��ȯ
	void	SetText(CString str, bool bReDraw = true, bool bAfterEvent = true);
	CString	GetText(void);
	int		GetNumber(void);
	int		GetTextLength(void);

	void	SetState(BNC_EditState &state, bool bReDraw, bool bFocus, bool bAfterEvent = true);
	void	GetState(BNC_EditState &state);


	// �ؽ�Ʈ �ִ� ���� ����
	void	SetLimitText(UINT uiMax);


	// ����Ʈ �ڽ���Ʈ�� ��ȯ
	CEdit* GetEditCtl(void)
	{
		return &m_Edit;
	};

	// ������ �Է�Ű ��ȯ
	WPARAM	GetLastPressKey(void);


	// ���� �ؽ�Ʈ �������� ���ڿ� ����
	void	AddEOL(CString str, bool bSelect, bool bAfterEvent = true);


	// m_bAutoClearButton�� false�� ���� ����
	void	ShowClearButton(bool bShow);



private:

	// ȣ�����Ŀ� ũ��Ƽ�� ���� ����� �� ��!!!
	void	UpdateTextExtent(const HDC hDC, const CString &srcStr, CString &destStr, int iMaxExtent);


	// ����Ʈ �ؽ�Ʈ ����� show/hide ������Ʈ
	void	UpdateDeleteButton(void);


protected:
	DECLARE_MESSAGE_MAP()
	

public:
	afx_msg void OnDestroy();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

