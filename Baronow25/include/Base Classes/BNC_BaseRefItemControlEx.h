#pragma once

class BNC_RefListViewEx;
class BN25_TYPE BNC_BaseRefItemControlEx : public BNC_BaseControl
{
public:
	BNC_BaseRefItemControlEx();
	virtual ~BNC_BaseRefItemControlEx();


protected :
	// BNC_ReferenceItem ����ȭ��
	CRITICAL_SECTION	m_cs;

	UINT				m_piTotalItemHeight[BND_REFITEMEX_IDXCOUNT];
	UINT				m_iCurWidthIndex;		// ���� Ŭ���̾�Ʈ ũ�⿡ �´� idx;


	// ���콺 ������� ���� ó���� ������ ������
	std::set<BNC_ReferenceItemEx*>		m_sSelectItem;
	BNC_ReferenceItemEx*				m_pLastSelectItem;
	BNC_ReferenceItemEx*				m_pLastClickUpItem;
	BNC_ReferenceItemEx*				m_pNewMouseItem;
	BNC_ReferenceItemEx*				m_pOldMouseItem;


	// ȭ�鿡 ���̴� �ε��� (Ʈ�������� root ���� ���ϵ� �ε���)
	int		m_idxVisibleBegin;
	int		m_idxVisibleEnd;

	
	UINT	m_uiSequence;			// ���Ե� ������ ��ȣ
	bool	m_bDrawing;				// �׸��� �۾� ó���� (UpdateMouseAction ���õ�)
	CSize	m_szMaxItem;			// ������ �ִ� ũ��(clear ������ ����)
	CSize	m_szScroll;				// ��ũ�� ����

	
	// ������ ���� �� (���Ŭ�������� ������Ʈ)
	BNS_ReferenceItemSortOption	m_LastSortOption;

	
	// Drag Select Item
	BNC_ReferenceItemEx *m_pDragTarget;
	CPoint				m_ptDragBeginItem;
	CPoint				m_ptDragBeginClient;
	bool				m_bDragMove;


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
	bool	UpdateLBtnSelect(UINT nFlags, BNC_ReferenceItemEx* pOnFindItem, CPoint &ptItem);
	bool	UpdateRBtnSelect(UINT nFlags, BNC_ReferenceItemEx* pOnFindItem, CPoint &ptItem);
	
	
	// ���콺 ���� ������ ����
	void	UpdateMouseItem(BNC_ReferenceItemEx* pUpdate);


	// ���콺 �׼� ��
	bool	IsCompareMouseAction(BNC_ReferenceItemEx* pItem1, BNC_ReferenceItemEx* pItem2);


	// ���콺 �̺�Ʈ ������ �ٽ� �׸���
	virtual void	DrawMouseActionItem(bool bDrawLastSelect);


	// Drag Function
	void	DragEnter(BNC_ReferenceItemEx* pItem, CPoint &ptClient, CPoint &ptItem, bool bDblClick);
	void	DragMove(CPoint &ptClient);

public :
	void	DragLeave(void);
	
private :
	virtual bool OnDragEnter(BNC_ReferenceItemEx *pDragTarget, CPoint &ptItem, bool bDblClick);
	virtual bool OnDragMove(BNC_ReferenceItemEx *pDragTarget, CPoint &ptItem);
	virtual bool OnDragLeave(BNC_ReferenceItemEx *pDragTarget);


protected :
	void	ClearMouseItem(bool bUpdate = true);


	// ���콺 ���۵� ������
	const BNC_ReferenceItemEx*				GetNewMouseItem(void);
	const BNC_ReferenceItemEx*				GetOldMouseItem(void);
	const BNC_ReferenceItemEx*				GetLastSelectItem(void);
	const std::set<BNC_ReferenceItemEx*>	GetSelectItemList(void);


	// ������ ������ ȣ�� �� ��
	void	UpdateDeleteItem(BNC_ReferenceItemEx* pItem);
	

	// �⺻ ������ �׸��� (�� �������� 0,0 ��ġ�� �׸��� ��)
	void	DefaultDrawItem(CDC* pItemDC, CDC* pResDC, BNC_ReferenceItemEx *pItem, BNE_REFITEM_STATE state, const CSize szItem);


	// ������ �׸��� ����
	virtual BNE_REFITEM_STATE	GetItemState(BNC_ReferenceItemEx* pItem);



	
	

//////////////////////////////////////////////////////////////////////////////////////////////////////////
protected :
	// �θ� view ��ȯ
	virtual BNC_RefListViewEx* GetParentView(void) = 0;


	// Ư�� �����۸� �ٽ� �׸�
	virtual void OnRedrawItem(BNC_ReferenceItemEx* pItem, BNE_REFITEM_STATE state) = 0;
	

	// ���콺 ��� ������ �ٽ� �׸��� (DrawMouseActionItem ���� ȣ��)
	virtual void OnDrawMouseItem(CDC* pDC, CDC* pItemDC, CDC* pResDC, BNC_ReferenceItemEx *pItem) = 0;


	// Ŭ���̾�Ʈ ��ǥ�� �Է¹޾Ƽ� ������ ã�� (UpdateMouseAction ���� ȣ��)
	// ������ ��ǥ�� ��ȯ�� ����� ã�� ������ ��ȯ
	virtual bool OnFindItem(_Ret_ CPoint &ptClientToItem, _Ret_ BNC_ReferenceItemEx** ppOnFindItem) = 0;



	// ���콺 �������� �̺�Ʈ �߻�
	virtual void OnUpdateEvent(BNE_MOUSEACTION action, BNC_ReferenceItemEx *pEventItem) = 0;


public :
	// ���� ������ ����
	void	SetSelectItem(BNC_ReferenceItemEx* pItem);


public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnDestroy();
};

