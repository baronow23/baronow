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
	// 부모 윈도우는 NULL 이며 m_pTargetWnd 등장 위치 확인용으로 사용
	CWnd*	m_pTargetWnd;
	BNC_BaseDialog* m_pUseOverlayPtr;


	// Enter(+Space), Esc키 종료 무시
	bool	m_bIgnoreExitKey;


	// modal loop종료시 외부에서 체크하기 위한 this 참조 변수
	// Init에서 this 등록
	// close, cancel, ok에서 null 할당
	BNC_BaseModal **m_ppRefCurrent;


	// 최초 등장시 숨김
	bool	m_bInitHide;



private :
	// 블록킹 시킬 다이얼로그 (옵션)
	// close시 해제알림 용도
	BNC_BaseDialog *m_pBlocking;


	// OnOk로 종료
	bool	m_bOkClose;

	
public :
	// 대상 윈도우 상태 체크(감춰짐, 최소화) 및 오버레이 다이얼로그 필요시 사용
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
