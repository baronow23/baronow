#pragma once



// InitFloating()�� dwVarSize�� BND_VARSIZE_DEFAULT�� ������

class BN25_TYPE BNC_FloatingMessage : public BNC_BaseFloating
{
public:
	BNC_FloatingMessage();
	virtual ~BNC_FloatingMessage();

	
public :
	// Default ���� (InitMessage �������� ���)
	static CFont*	s_pFontPtr;
	static COLORREF s_colorBG;
	static COLORREF s_colorText;
	static CRect	s_rcBlank;
	static int		s_iCharExtra;
	static UINT		s_uiRoundCorner;	// ���� �ڳ� ���
	static DWORD	s_dwGradation;
	


private :
	CRITICAL_SECTION	m_csMessage;


public :
	CFont*		m_pFontPtr;
	COLORREF	m_colorText;
	CRect		m_rcBlank;
	int			m_iCharExtra;


public :
	UINT		m_uiRoundCorner;
	DWORD		m_dwGradation;


protected :
	// ������ �ð�
	UINT		m_uiDelayShow;
	UINT		m_uiDelayStay;
	UINT		m_uiDelayHide;


	// ����
	BYTE		m_btAlphaBegin;
	BYTE		m_btAlphaEnd;


	// �޽��� ����
	std::vector<CString>	m_vMessage;
	std::vector<CSize>		m_vMessageDraw;
	int						m_iLineSpacing;
	bool					m_bAlignCenter;
	size_t					m_iMsgLine;

	CBitmap*				m_pImagePtr;
	CPoint					m_ptImagePos;
	CSize					m_szImageSize;


	CDC*					m_pMsgDC;
	Gdiplus::Bitmap*		m_pMsgBitmap;


public :
	void	InitMessage( CFont* pFontPtr, COLORREF colorBk, COLORREF colorText, CRect rcBlank = CRect(20, 10, 20, 10) );
	void	SetDelay(UINT uiDelayShow, UINT uiDelayStay, UINT uiDelayHide);
	void	SetAlphaRange(BYTE btMin, BYTE btMax);
	void	ShowMessage(CString strMessage, int iLineSpacing = 4, bool bAnimation = true, bool bAlignCenter = true);//, bool bTopMost = false);
	void	ShowImage(CBitmap* pImagePtr, CPoint ptImagePos, CSize szImageSize, bool bAnimation = true);//, bool bTopMost = false);
	void	HideMessage(bool bAnimation = true);
	

	// ShowMessage ȣ���� �����޽��� �Ͻ������� ���� ����
	// BNC_TransparentAnimation �����忡�� ù ��° ������Ʈ�� ȣ��
	void	OnFirstTransparentAnimation(BYTE btAlpha);
	///void	ClearMessage(void);
	

private :
	bool	OnDraw(CDC* pMemDC, CDC* pResDC);
	void	OnUpdateWindowStatus(BNE_POPUP_STATUS status);
	bool	FindStrCut(CString str, LPCTSTR strFind, CString &strLeft, CString &strRight);
	void	UpdateMessage(bool bAnimation = true);//, bool bTopMost = false);
	bool	UpdateLayerText(CSize &sz);


protected :
	virtual void OnDrawMsgDC(CDC *pMemDC, Gdiplus::Graphics &g, CSize &sz);
	virtual void OnDrawMsgDC(Gdiplus::Graphics &g, CSize &sz);


protected:
	virtual void OnUpdateSyncPos(CSize szUpdate);
	


public :
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
};

