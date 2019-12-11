#pragma once

class BN25_TYPE BNC_MessageBox : public BNC_BaseModal
{
public:
	BNC_MessageBox(UINT nDialogID, CWnd *pTarget, CWnd *pParent);
	virtual ~BNC_MessageBox();


public :
	static CFont*	s_pFontTitle;
	static CFont*	s_pFontSubstance;


private :
	BNC_TempClient	m_RootClient;
	BNC_Button*		m_pBtnOK;
	BNC_Button*		m_pBtnCancel;


protected :
	COLORREF		m_colorTitle;
	COLORREF		m_colorControl;
	// ������ ���� ���


	BNC_DrawString					m_Title;
	std::vector<BNC_DrawString*>	m_vSubstance;
	
	
	UINT		m_uiHeightTitle;	// Ÿ��Ʋ�� ���� 
	UINT		m_uiHeightControl;	// ��Ʈ�� ����
	UINT		m_uiHeightTop;		// ���� ���� ��� ����
	UINT		m_uiHeightBottom;	// ���� ���� �ϴ� ����
	UINT		m_uiHeightSpacing;	// ���� �ٰ���



	// ���� ������ ��� ����
	bool	m_bUseDefaultWidth;
	UINT	m_uiDefaultWidth;
	

private :
	// ����ó��
	void	Clear(void);
	void	UpdateSize(void);
	LRESULT OnMessageButton(WPARAM wParam, LPARAM lParam);


protected :
	CPoint	GetButtonPos(HWND hButton, int iCenter);



private :
	// ��ư ��Ÿ�� ���� (�ɼ�)
	virtual bool OnSetButton(BNC_Button* pBtnOK, BNC_Button* pBtnCancel);	
	

	// ��ư ��ġ ������ (�ɼ�)
	virtual void OnButtonPos(HDWP &hdwp, HWND hBtnOK, HWND hBtnCancel);

	
	// Clinet �׸��� ������
	virtual bool OnDrawRootClient(CDC* pMemDC, CDC* pResDC);
	


public :
	// Ÿ��Ʋ�� �̻��� _T("") �Է�
	// strSubstance ���� �ٹٲ��� '/n' �Ǵ� '/r/n'
	bool	InitMessageBox(CString strTitle, CString strSubstance, bool bUseCancel);


	// iTitle : Ÿ��Ʋ�� ����
	// iControl : Ȯ��/��� ��Ʈ�� ���� ����
	// iTop : ���� ��� ��� ����
	// iBottom : ���� ��� �ϴ� ����
	// iSpacing : ���� �� �߰� ����
	void	SetHeight(UINT uiTitle, UINT uiControl, UINT uiTop, UINT uiBottom, UINT uiSpacing);



	// Title ��� ��Ÿ��
	void	SetTitleStyle(CFont* pFontPtr,
						COLORREF color,
						UINT uiAlign = TA_LEFT,
						UINT uiLeftBlank = 5,
						UINT uiRightBlank = 5);



	// ���� ��� ��Ÿ�� (�ϰ� ����)
	void	SetSubstanceStyle(CFont* pFontPtr,
							  COLORREF color,
							  UINT uiAlign = TA_CENTER,
							  UINT uiLeftBlank = 10,
							  UINT uiRightBlank = 10);


	// ���� ��� ��Ÿ�� (���� ����)
	// index�� InitMessageBox() ���� �Է��� strSubstance �ٹٲ� ����
	bool	SetSubstanceStyle(UINT index,
							  CFont* pFontPtr,
							  COLORREF color,
							  UINT uiAlign = TA_CENTER,
							  UINT uiLeftBlank = 10,
							  UINT uiRightBlank = 10);

	

	// ���� �ɼ� ���� : ShowMessage() �̻��� (DoModal(), Modal() ���� ȣ���) 
	void	UpdateMessage(void);


	// UpdateMessage() ������ Modal() ó����
	INT_PTR	ModalMessage(bool bUseOverlay = true, BYTE btOverlayAlpha = 25, COLORREF clrOverlayBk = RGB(0, 0, 0));


protected :
	virtual BOOL OnInitDialog();
	
public :
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

