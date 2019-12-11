#pragma once


class BN25_TYPE BNC_RefListControl :	public BNC_BaseRefItemControl
{
	friend class BNC_RefListView;


public:
	BNC_RefListControl(void);
	virtual ~BNC_RefListControl(void);
	

private :
	UINT				m_uiTotalItemHeight;				// ��ü ������ ����
	BNC_RefListView*	m_pParentView;
	std::vector<BNC_ReferenceItem*>			m_vpItemList;	// Item (src)
	std::map<CString, BNC_ReferenceItem*>	m_mpItemRef;	// Item (ref);

	
	// SynRect Client
	BNC_BaseClient*		m_pSyncWindow;
	BNC_ReferenceItem*	m_pSyncWindowItem;
	UINT				m_idxSyncRect;


////////////////////////////////////////////////////////////////////////////////
private:
	bool OnCreate(void);
	void OnUpdateSize(int cx, int cy);
	bool OnDraw(CDC* pMemDC, CDC* pResDC);
	

////////////////////////////////////////////////////////////////////////////////////////////////
// BNC_BaseRefItemControl �ʼ� �޼���
////////////////////////////////////////////////////////////////////////////////////////////////
private :
	// Ư�� �����۸� �ٽ� �׸�
	void	OnRedrawItem(BNC_ReferenceItem* pItem, BNE_REFITEM_STATE state);
	

	// ���콺 ��� ������ �ٽ� �׸���
	void	OnDrawMouseItem(CDC* pDC, CDC* pItemDC, CDC* pResDC, BNC_ReferenceItem *pItem);


	// ptMouse : ��ũ�� ���� ���� Ŭ���̾�Ʈ ���콺 ��ǥ�� �Է¹ް�
	// ������ Client ��ǥ�� ��ȯ�Ǿ� ��ȯ
	bool	OnFindItem(_Ret_ CPoint &ptClientToItem, _Ret_ BNC_ReferenceItem** ppFindItem);		


	// ���콺 �������� �̺�Ʈ �߻�
	void	OnUpdateEvent(BNE_MOUSEACTION action, BNC_ReferenceItem *pEventItem);


	
////////////////////////////////////////////////////////////////////////////////////////////////
// BNC_RefListControl ���� �޼���
////////////////////////////////////////////////////////////////////////////////////////////////
private :
	BNC_ReferenceItem*	GetItemPtr(UINT index);
	BNC_ReferenceItem*	GetItemPtr(CString &strKey);
	bool				GetItemList(std::vector<BNC_ReferenceItem*> &vList);
	int					GetItemCount(void);


	// ������ �߰�
	// return : �߰��� index
	// ������ �߰��ø��� ���� �� ��ũ�� ��ġ ������ ���ؼ��� bUpdate�� false�� �����ϰ�
	// UpdateAfterInsert() ��� (iBeginIndex�� return ������ ���)
	int		Insert(CString &strKey, const void* pRefData, BNC_ReferenceItem &Item, bool bUpdate);

	
	// ������ ����, �������� �ϰ�ó���ϸ鼭 update�� ���� �ʾ��� ��� ȣ��
	// �������� sort���� ���� �ʾ��� ��� �����̳� ���� ���� �߻��ϹǷ� �ݵ�� ȣ���� �� ��
	void	UpdateAfterInsert(UINT iBeginIndex, bool bEndScroll, bool bApplyLastSort);



	// ���� (�뷮������ bUpdate false ���� sortȤ�� UpdateAfterInsertȣ�� �ʼ�)
	void	Clear(bool bReDraww, bool bRelease = false);
	int		DeleteFromIndex(UINT index, bool bUpdate);
	int		DeleteFromPtr(const BNC_ReferenceItem* ptr, UINT iIdxFindBegin, bool bUpdate);
	int		DeleteFromKey(CString strKey, UINT iIdxFindBegin, bool bUpdate, bool bSeekEnd);
	int		DeleteFromSequnece(UINT uiSequence, UINT iIdxFindBegin, bool bUpdate);
	

	// ���� ȣ�� (�����ʿ��� ������ ����)
	void	DeleteRefernce(BNC_ReferenceItem* pItem);


	// ���� ���ڿ� ����
	bool	ModifySortString(LPCTSTR strItemKey, UINT uiSortIndex, LPCTSTR strSort);
	


	// ����
	// uiRefStringIndex : ���� ��� �ε���
	// bAsecending : �������� ����
	// iEqualRefIndex : uiRefStringIndex ����� ���� �� �߰� ���� �ε���
	// bEqualAsecnding : iEqualRefIndex �������� ����
	void	SortString(UINT uiRefStringIndex,
					   bool bAsecending,
					   int iEqualRefIndex	= -1,
					   bool bEqualAsecnding	= true);

	void	SortSequence(bool bAsecending);


	// ������ �׸��� ��ġ(top, bottom) ���� : index(���� ������ �ε���)
	// ���� ������ ȣ��
	void	UpdateItemPos(bool bMoveEndScroll, int index);



	// ȭ�鿡 �������� �ε��� ����
	// ����, ����, ��ũ�� ��ġ ����(Ŭ���̾�Ʈ ũ�� ���� ����)�� ȣ��
	void	UpdateVisibleIndex(void);



public :
	// ������ ���� ����
	void	EnableItemIdx(UINT index, bool bEnable, bool bRedraw);
	void	EnableItemPtr(BNC_ReferenceItem* pItem, bool bEnable, bool bRedraw);
	bool	IsItemIdxEnable(UINT index);
	bool	IsItemPtrEnable(BNC_ReferenceItem* pItem);



	UINT	GetItemTotalHeight(void);
	UINT	SetListScroll(int iVerScroll, bool bForce = false, bool bRedraw = false);
	UINT	GetListScroll(void);

	
	// ������ �ٽ� �׸��� (����� ȣ��)
	void	RedrawItem(CString strKey);
	void	RedrawItem(BNC_ReferenceItem* pItem);



	// �ܺ� ȣ��, ������ �ʿ䰡 ���� �� �������� �ε����� ���� (cs ���)
	void	UpdateOnlyVisibleIndex(void);


	// Option, SyncRect Window
	void	SyncWindowClear(void);
	void	SyncWindowHide(void);
	void	SyncWindowUpdate(void);


	// ȭ�鿡 ���̴� �ֻ�� ������ ��ȯ
	BNC_ReferenceItem* GetVisibleTopItem(void);


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
protected :
	DECLARE_MESSAGE_MAP()

public :
	afx_msg void OnDestroy();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
