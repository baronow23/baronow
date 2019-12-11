#pragma once


class BN25_TYPE BNC_SimpleHScrollbar : public BNC_BaseControl
{
	DECLARE_DYNAMIC(BNC_SimpleHScrollbar)


public:
	BNC_SimpleHScrollbar(void);
	virtual ~BNC_SimpleHScrollbar(void);



private :
	bool	m_bFirstVisible;


protected :
	BNS_ScrollbarLayout		m_layout;
	CRect	m_rcAbleArea;	// rcMargin�� ������ ���� ����
	CRect	m_rcBar;		// Bar����
	bool	m_bMinBar;		// �ּһ����� bar����

	int		m_iLength;		// Ÿ�� ������ ����
	int		m_iPos;			// �������� ��� ��ġ

	bool	m_bFocus;		// ��Ŀ������
	bool	m_bEndPos;		// ��ũ�� ��ġ ������ �̵�����


	// ���콺 ���� üũ
	bool	m_bLBtnDn;	
	CPoint	m_ptLBtnMouse;		// �������콺 ������ �� ���콺 ��ǥ
	int		m_iFocusDnLeft;		// bar���� ������ m_rcBar.left���� �Ÿ�
	int		m_iFocusDnRight;	// bar���� Ŭ���� m_rcBar.right���� �Ÿ�


	// ��ũ�ѹ� ��� ���콺 �̵��� üũ (LBtnDown ����)
	int		m_iOldMovePos;
	CPoint	m_ptLBtnPos0;
	

public :
	bool	m_bAutoHide;
	CWnd*	m_pCaptureAfterRelease;


private:
	// Overriding 
	bool OnCreate(void);
	void OnUpdateSize(int cx, int cy);
	bool OnDraw(CDC* pMemDC, CDC* pResDC);



	// ��ũ��ũ�� �� Ÿ�� ������ ���� ����� ȣ��
	// m_uiPos, m_rcBar �����
	void	UpdateScroll(bool bReDraw);


	
	// ��ũ�ѿ����� ��ġ(y)�� ��� ������ ��ġ(y) ��ȣ��ȯ
	int		ClientPosToTargetPos(int iPos);
	int		TargetPosToClientPos(int iPos);


protected :
	// �θ𿡰� ��ũ�� ��ġ �޽��� ����
	void	SendScrollPos(void);	
	
	
public :
	void	SetLayout(BNS_ScrollbarLayout *pLayout, bool bRedraw = false);
	void	SetLength(int iLength, bool bUpdateNotify, bool bReDraw);
	void	SetPos(int iPos, bool bUpdateNotify, bool bReDraw);
	int		GetPos(void) const;
	int		GetLength(void) const;
	int		GetLayoutWidth(void) const;
	void	SetPosLength(int iPos, int iLength);
	bool	IsLBtnDown(void);



protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
};
