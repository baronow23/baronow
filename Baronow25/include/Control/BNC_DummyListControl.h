#pragma once

class BN25_TYPE BNC_DummyListControl : public BNC_BaseControl
{
public:
	BNC_DummyListControl();
	~BNC_DummyListControl();


public :
	COLORREF	m_colorBG;


public :
	int		m_iFixHeight;		// ��������
	int		m_iUseCount;		// ��� ����
	int		m_idxMouse;			// ���콺 ���� �ε���
	int		m_idxVisibleTop;	// ȭ�鿡 �������� �ֻ�� �ε���
	int		m_idxVisibleBottom;	// ȭ�鿡 �������� ���ϴ� �ε���
	CSize	m_szScroll;			// ��ũ�Ѿ�

	BNE_MOUSEACTION		m_MouseAction;		// m_idxMouse�� ����
	BNC_ReferenceItem	m_MouseItem;		// syncrect �ϰ� ó���� ������
	

private:
	bool OnCreate(void);
	void OnUpdateSize(int cx, int cy);
	bool OnDraw(CDC* pMemDC, CDC* pResDC);


private :
	// ���콺 �̺�Ʈ ������Ʈ
	bool	UpdateMouseAction(UINT nFlags, BNE_MOUSEACTION action, CPoint &point);
	bool	UpdateMouseIndex(BNE_MOUSEACTION action, int index);
	void	RedrawIndex(int index, BNE_REFITEM_STATE state, BNC_ReferenceItem* pItem);
	void	ClearMouse(void);

public :
	void	Clear(bool bRedraw);
	void	Reset(UINT iFixHeight, UINT iUseCount, BNC_ReferenceItem &fixItem, bool bEndScroll, bool bRedraw);
	void	UpdateVisibleIndex(void);
	UINT	SetListScroll(int iVerScroll, bool bForce, bool bRedraw);
	UINT	GetListScroll(void);
	UINT	GetLastIndexBottom(void);

public :
	BNE_REFITEM_STATE	MouseActionToItemState(BNE_MOUSEACTION action);

public :
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

