#pragma once


class BN25_TYPE BNC_AnimationDialog : public BNC_BaseDialog
{
public :
	BNC_AnimationDialog(void);
	~BNC_AnimationDialog(void);

private:
	static UINT s_uiCreateCount;
	static UINT s_uiDestroyCount;


public:
	static UINT	GetCreateCount(void);
	static UINT	GetAliveCount(void);



private :
	bool OnCreate(void);
	bool OnDraw(CDC* pMemDC, CDC* pResDC);


private :
	bool	m_bFirstUpdate;
	bool	m_bHideMode;
	CWnd*	m_pWndTarget;
	CDC*	m_pCopyDC;		// m_pWndTarget에서 복사한 CDC

	CSize	m_szSrc;
	CPoint	m_ptBegin;
	CPoint	m_ptEnd;

	CRect	m_rcTarget;


public :
	double	m_lfMilliSec;	// 애니메이션 시간

	


public :
	// 특정 위치로 이동(스케일링) 하면서 보이거나 감춰짐
	static void RunHide(CWnd* pWnd, CPoint ptEnd, CDC* pMemDC, double lfMilliSec);
	static void RunShow(CWnd* pWnd, CPoint ptBegin, CRect rcEnd, CDC* pMemDC, double lfMilliSec);


	// 투명하게 보여지거나 감춰짐
	static void RunHide(CWnd* pWnd, CDC* pMemDC, double lfMilliSec);
	static void RunShow(CWnd* pWnd, CDC* pMemDC, double lfMilliSec);


private :
	void	SetHide(CWnd* pWnd, CPoint ptEnd, CDC* pMemDC);
	void	SetShow(CWnd* pWnd, CPoint ptBegin, CRect rcEnd, CDC* pMemDC);
	void	SetAnimation(CDC* pMemDC);
	

public :
	void	SetTargetWindowPos(void);
	void	Update(double lfRatio);
	void	Update2(double lfRatio);
	void	UpdateFinal(void);


protected : 
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnDestroy();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//virtual BOOL OnInitDialog();
};
