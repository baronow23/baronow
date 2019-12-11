#pragma once


class BN25_TYPE BNC_BaseRefItemControl : public BNC_BaseControl
{
public:
	BNC_BaseRefItemControl();
	virtual ~BNC_BaseRefItemControl();


protected :
	// BNC_ReferenceItem ����ȭ��
	CRITICAL_SECTION	m_cs;


	// ���콺 ������� ���� ó���� ������ ������
	std::set<BNC_ReferenceItem*>	m_sSelectItem;
	BNC_ReferenceItem*				m_pLastSelectItem;
	BNC_ReferenceItem*				m_pLastClickUpItem;
	BNC_ReferenceItem*				m_pNewMouseItem;
	BNC_ReferenceItem*				m_pOldMouseItem;


	// ȭ�鿡 ���̴� �ε��� (Ʈ�������� root ���� ���ϵ� �ε���)
	int		m_idxVisibleBegin;
	int		m_idxVisibleEnd;
	 
	
	UINT	m_uiSequence;			// ���Ե� ������ ��ȣ
	bool	m_bDrawing;				// �׸��� �۾� ó���� (UpdateMouseAction ���õ�)
	CSize	m_szMaxItem;			// ������ �ִ� ũ��(clear ������ ����)
	CSize	m_szScroll;				// ��ũ�� ����


	// ������ ���� �� (���Ŭ�������� ������Ʈ)
	BNS_ReferenceItemSortOption	m_LastSortOption;


public:
	COLORREF	m_colorBG;
	bool		m_bUseMultiSelect;
	bool		m_bUseStaySelect;		// �׻� �ϳ��� ������ ����
	int			m_iSelProcessIdx;		// ������ ���ÿ� ������ RectIndex �� (���� �ε������� ���ų� ������ ���� ó��)

private :
	// ���콺 ���� ���� ����
	// Ư�� �ε��� ���� ����Ǹ� ���� �׷��ְ� �θ𿡰� �޽��� ����
	// ���� CS ���
	void	UpdateMouseAction(UINT nFlags, BNE_MOUSEACTION action, CPoint &ptClient);
	bool	UpdateLBtnSelect(UINT nFlags, BNC_ReferenceItem* pOnFindItem, CPoint &ptItem);
	bool	UpdateRBtnSelect(UINT nFlags, BNC_ReferenceItem* pOnFindItem, CPoint &ptItem);
	
	
	// ���콺 ���� ������ ����
	void	UpdateMouseItem(BNC_ReferenceItem* pUpdate);


	// ���콺 �׼� ��
	bool	IsCompareMouseAction(BNC_ReferenceItem* pItem1, BNC_ReferenceItem* pItem2);


	// ���콺 �̺�Ʈ ������ �ٽ� �׸���
	virtual void	DrawMouseActionItem(bool bDrawLastSelect);



protected :
	void	ClearMouseItem(bool bUpdate = true);


	// ���콺 ���۵� ������
	const BNC_ReferenceItem*			GetNewMouseItem(void);
	const BNC_ReferenceItem*			GetOldMouseItem(void);
	const BNC_ReferenceItem*			GetLastSelectItem(void);
	const std::set<BNC_ReferenceItem*>	GetSelectItemList(void);


	// ������ ������ ȣ�� �� ��
	void	UpdateDeleteItem(BNC_ReferenceItem* pItem);
	

	// �⺻ ������ �׸��� (�� �������� 0,0 ��ġ�� �׸��� ��)
	void	DefaultDrawItem(CDC* pItemDC, CDC* pResDC, const BNC_ReferenceItem *pItem, BNE_REFITEM_STATE state, const CSize &szItem);


	// ������ �׸��� ����
	virtual BNE_REFITEM_STATE	GetItemState(BNC_ReferenceItem* pItem);
	

//////////////////////////////////////////////////////////////////////////////////////////////////////////
protected :
	// Ư�� �����۸� �ٽ� �׸�
	virtual void OnRedrawItem(BNC_ReferenceItem* pItem, BNE_REFITEM_STATE state) = 0;
	

	// ���콺 ��� ������ �ٽ� �׸��� (DrawMouseActionItem ���� ȣ��)
	virtual void OnDrawMouseItem(CDC* pDC, CDC* pItemDC, CDC* pResDC, BNC_ReferenceItem *pItem) = 0;


	// Ŭ���̾�Ʈ ��ǥ�� �Է¹޾Ƽ� ������ ã�� (UpdateMouseAction ���� ȣ��)
	// ������ ��ǥ�� ��ȯ�� ����� ã�� ������ ��ȯ
	virtual bool OnFindItem(_Ret_ CPoint &ptClientToItem, _Ret_ BNC_ReferenceItem** ppOnFindItem) = 0;



	// ���콺 �������� �̺�Ʈ �߻�
	virtual void OnUpdateEvent(BNE_MOUSEACTION action, BNC_ReferenceItem *pEventItem) = 0;


public :
	// ���� ������ ����
	void	SetSelectItem(BNC_ReferenceItem* pItem);
	BNC_ReferenceItem* GetSelectItem(void);

	// mouse rect reset
	void	ResetMouseRectIndex(BNC_ReferenceItem* pItem, bool bReDraw);


public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
};

