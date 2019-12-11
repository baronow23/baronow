#pragma once

class BN25_TYPE BNC_BaseFloating : public BNC_BaseModaless
{
	friend class BNC_BaseDialog;


public:
	BNC_BaseFloating();
	virtual ~BNC_BaseFloating();


public:
	bool	m_bMouseMoveInitParent;		// ������ ����ߴ� �˾� ������ ���콺�� �̵��� �� �ְ� ���
	bool	m_MouseClockParentActive;	// ���콺 Ŭ���� â ���� �˾��� Ȱ��ȭ�ϰ� â����

private :
	bool OnDraw(CDC* pMemDC, CDC* pResDC);
	


protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();


public:
	afx_msg void OnDestroy();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

};

