#pragma once

class BN25_TYPE BNC_BaseModal : public BNC_BaseDialog
{
	friend class BNC_BaseDialog;

public:
	BNC_BaseModal(UINT nDialogID, CWnd* pTarget, CWnd* pParent, BNC_BaseModal **ppRefCurrent = NULL, BNC_BaseDialog *pBlocking = NULL);
	virtual ~BNC_BaseModal(void);
	

private:
	static std::set<HWND>	s_sAliveModal;
	static					UINT s_uiCreateCount;
	static					UINT s_uiDestroyCount;


public:
	static std::set<HWND>	GetAliveModal(void);
	static UINT				GetCreateCount(void);
	static UINT				GetAliveCount(void);


public :
	bool	m_bForceBreak;


protected :
	// �θ� ������� NULL �̸� m_pTargetWnd ���� ��ġ Ȯ�ο����� ���
	CWnd*	m_pTargetWnd;
	BNC_BaseDialog* m_pUseOverlayPtr;


	// Enter(+Space), EscŰ ���� ����
	bool	m_bIgnoreExitKey;


	// modal loop����� �ܺο��� üũ�ϱ� ���� this ���� ����
	// Init���� this ���
	// close, cancel, ok���� null �Ҵ�
	BNC_BaseModal **m_ppRefCurrent;


	// ���� ����� ����
	bool	m_bInitHide;



private :
	// ���ŷ ��ų ���̾�α� (�ɼ�)
	// close�� �����˸� �뵵
	BNC_BaseDialog *m_pBlocking;


	// OnOk�� ����
	bool	m_bOkClose;

	
public :
	// ��� ������ ���� üũ(������, �ּ�ȭ) �� �������� ���̾�α� �ʿ�� ���
	INT_PTR Modal(bool bUseOverlay = false, BYTE btOverlayAlpha = 20, COLORREF clrOverlayBk = RGB(0, 0, 0));
	void	Break(void);
	bool	IsOkClose(void);

private :
	virtual void OnUpdateSize(int cx, int cy);
	virtual void OnBreak(void);
	virtual BOOL ContinueModal();


protected :
	DECLARE_MESSAGE_MAP()
	virtual BOOL CreateIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd = NULL, void* lpDialogInit = NULL);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	virtual void OnCancel();


public :
	afx_msg void OnDestroy();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnClose();


	
};
