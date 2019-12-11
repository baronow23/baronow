#pragma once


class BN25_TYPE BNC_RefListView : public BNC_BaseClient
{
public:
	BNC_RefListView();
	virtual ~BNC_RefListView();


protected :
	BNC_RefListControl		m_ListControl;
	BNC_SimpleVScrollbar	m_vScrollbar;
	

public:
	// ���� �θ𿡰� �޽��� ������ �� �ʿ��� ��Ʈ�� ID ����
	USHORT		m_idList;
	USHORT		m_idScroll;


	// ��ũ�ѹ� ����� ������ ��뿩�� (������ width - m_iFixBlank)
	int			m_iFixBlank;
	bool		m_bUseVarCtlPos;


	// ���콺 ĸ�� �Ǿ����� �� Ű���� up-down���� ��ũ�Ѹ�
	bool		m_bUsingKeyScroll;


	// ��Ʈ�� ���ϴ� �ڸ���
	short	m_iCtlOffTop;
	short	m_iCtlOffBottom;
	

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��� �������̵��� �� ȣ������ ��
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected :
	bool	OnCreate(void);
	/*
	{
		if(BNC_RefListView::OnCreate() == false)
		{
			return false;
		}
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
		return true;
	}
	*/


	void	OnUpdateClient(int cx, int cy);
	/*
	{
		BNC_RefListView::OnUpdateClient(cx, cy);
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	}
	*/

	
	bool	OnDraw(CDC* pMemDC, CDC* pResDC);
	/*
	{
		if(BNC_RefListView::OnDraw(pMemDC, pResDC) == false)
		{
			return false;
		}
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
		return true;
	}
	*/


	LRESULT OnMessageList(WPARAM wParam, LPARAM lParam);
	/*
	{
		LRESULT result = BNC_RefListView::OnMessageList(wParam, lParam);
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
		return result;
	}
	*/

	
	LRESULT	OnMessageScroll(WPARAM wParam, LPARAM lParam);
	/*
	{
		LRESULT result = BNC_RefListView::OnMessageScroll(wParam, lParam);
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
		return result;
	}
	*/


public :
	void OnNotifyMouseWheel(UINT nFlags, short zDelta);
	bool OnNotifyKeyDown(WPARAM wKey);


public :
	BNC_ReferenceItem*	GetItemPtr(UINT index);
	BNC_ReferenceItem*	GetItemPtr(CString strKey);
	bool				GetItemList(std::vector<BNC_ReferenceItem*> &vList);
	int					GetItemCount(void);

	const BNC_SimpleVScrollbar*	GetVerticalScrollCtl(void);


public :
	virtual UINT GetDeferChildCount(void);
	virtual void UpdateControl(int cx, int cy, bool bUpdateScroll);
	

	virtual void OnRedraw(bool bTopMsg);


	// �������� �ϳ��� ���� �� �׸���
	virtual void OnDrawNoData(CDC* pMemDC, CDC* pResDC);


	// ������ �׸��� (�� �������� 0,0 ��ġ�� �׸��� ��)
	// index : ����Ʈ �ε���
	virtual void OnDrawItem(CDC* pItemDC, CDC* pResDC, BNC_ReferenceItem *pItem, BNE_REFITEM_STATE state, const CSize &szItem) = 0;


	// ������ �߰�
	// return : �߰��� index
	// ������ �߰��ø��� ���� �� ��ũ�� ��ġ ������ ���ؼ��� bUpdate�� false�� �����ϰ�
	// UpdateAfterInsert() ����� ��
	int		Insert(CString strKey, const void* pRefData, BNC_ReferenceItem &Item, bool bUpdate);


	// ������ ����, �������� �ϰ�ó���ϸ鼭 update�� ���� �ʾ��� ��� ȣ��
	// �������� sort���� ���� �ʾ��� ��� �����̳� ���� ���� �߻��ϹǷ� �ݵ�� ȣ���� �� ��
	void	UpdateAfterInsert(int iBeginIndex, bool bEndScroll, bool bApplyLastSort);



	// ����
	void	ClearItem(bool bReDraw);
	int		DeleteItemFromIndex(UINT index, bool bUpdate);
	int		DeleteItemFromPtr(const BNC_ReferenceItem* ptr, UINT iIdxFindBegin, bool bUpdate);
	int		DeleteItemFromKey(CString strKey, UINT iIdxFindBegin, bool bUpdate, bool bSeekEnd);
	int		DeleteItemFromSequnece(UINT uiSequence, UINT iIdxFindBegin, bool bUpdate);


	// ���� ���ڿ� ����
	bool	ModifySortString(LPCTSTR strItemKey, UINT uiSortIndex, LPCTSTR strSort);


	// ����
	void	SortString(UINT uiRefStringIndex, bool bAsecending, int iEqualRefIndex = -1, bool bEqualAsecnding = true);
	void	SortSequence(bool bAsecending);


	// ��ũ�� ������Ʈ
	void	UpdateScroll(void);
	void	SetListScroll(int iPos);


	// ������ �ٽ� �׸��� (����� ȣ��)
	void	RedrawItem(CString strKey);
	void	RedrawItem(BNC_ReferenceItem* pItem);

	// �ܺ� ȣ��, ������ �ʿ䰡 ���� �� �������� �ε����� ���� (cs ���)
	void	UpdateOnlyVisibleIndex(void);


	// ������ ���� ����
	void	EnableItemIdx(UINT index, bool bEnable, bool bRedraw);
	void	EnableItemPtr(BNC_ReferenceItem* pItem, bool bEnable, bool bRedraw);
	bool	IsItemIdxEnable(UINT index);
	bool	IsItemPtrEnable(BNC_ReferenceItem* pItem);

	

	// Sync Window
	void	SetSyncRectWindow(BNC_BaseClient *pSyncWindow,
							  BNC_ReferenceItem *pSyncItem,
							  UINT idxSyncRect);



	void	SetUseStaySelect(bool bEnable);
	int		SetSelectItem(CString strKey, bool bMoveScroll);
	BNC_ReferenceItem* GetSelectItem(void);
	void	ResetMouseRectIndex(BNC_ReferenceItem* pItem, bool bReDraw);

protected :
	DECLARE_MESSAGE_MAP()


public :
	afx_msg void OnDestroy();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

