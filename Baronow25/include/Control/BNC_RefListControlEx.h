#pragma once


class BN25_TYPE BNC_RefListControlEx :	public BNC_BaseRefItemControlEx
{
	friend class BNC_RefListViewEx;


public:
	BNC_RefListControlEx(void);
	virtual ~BNC_RefListControlEx(void);
	

private :
	BNC_RefListViewEx*	m_pParentView;
	std::vector<BNC_ReferenceItemEx*>			m_vpItemList;	// Item (src)
	std::map<CString, BNC_ReferenceItemEx*>		m_mpItemRef;	// Item (ref);
	

	// BNC_ReferenceItemEx�� BNC_ReferenceItemExOption ���� ��� (insert�� ������ ��鸸 ����)
	std::map<CString, BNC_ReferenceItemExOption*>	m_mDeleteOption;


	// SynRect Client
public :
	BNC_BaseClient*			m_pSyncWindow;
	BNC_ReferenceItemEx*	m_pSyncWindowItem;
	UINT					m_idxSyncRect;


////////////////////////////////////////////////////////////////////////////////
private:
	bool OnCreate(void);
	void OnUpdateSize(int cx, int cy);
	bool OnDraw(CDC* pMemDC, CDC* pResDC);
	

////////////////////////////////////////////////////////////////////////////////////////////////
// BNC_BaseRefItemControl �ʼ� �޼���
////////////////////////////////////////////////////////////////////////////////////////////////
private :
	// �θ� view ��ȯ
	BNC_RefListViewEx* GetParentView(void);


	// Ư�� �����۸� �ٽ� �׸�
	void	OnRedrawItem(BNC_ReferenceItemEx* pItem, BNE_REFITEM_STATE state);
	

	// ���콺 ��� ������ �ٽ� �׸���
	void	OnDrawMouseItem(CDC* pDC, CDC* pItemDC, CDC* pResDC, BNC_ReferenceItemEx *pItem);


	// ptMouse : ��ũ�� ���� ���� Ŭ���̾�Ʈ ���콺 ��ǥ�� �Է¹ް�
	// ������ Client ��ǥ�� ��ȯ�Ǿ� ��ȯ
	bool	OnFindItem(_Ret_ CPoint &ptClientToItem, _Ret_ BNC_ReferenceItemEx** ppFindItem);		


	// ���콺 �������� �̺�Ʈ �߻�
	void	OnUpdateEvent(BNE_MOUSEACTION action, BNC_ReferenceItemEx *pEventItem);



private :
	void	DrawItemClip(CDC* pBltDC, CDC* pItemDC, CDC* pResDC, BNC_ReferenceItemEx *pItem);
	
////////////////////////////////////////////////////////////////////////////////////////////////
// BNC_RefListControlEx ���� �޼���
////////////////////////////////////////////////////////////////////////////////////////////////
private :
	BNC_ReferenceItemEx*	GetItemPtr(UINT index);
	BNC_ReferenceItemEx*	GetItemPtr(CString &strKey);


	// ������ �߰�
	// return : �߰��� index
	// ������ �߰��ø��� ���� �� ��ũ�� ��ġ ������ ���ؼ��� bUpdate�� false�� �����ϰ�
	// UpdateAfterInsert() ��� (iBeginIndex�� return ������ ���)
	int		Insert(CString &strKey, void* pRefData, BNC_ReferenceItemEx &Item, bool bAutoDeleateOption, bool bUpdate);

	
	// ������ ����, �������� �ϰ�ó���ϸ鼭 update�� ���� �ʾ��� ��� ȣ��
	// �������� sort���� ���� �ʾ��� ��� �����̳� ���� ���� �߻��ϹǷ� �ݵ�� ȣ���� �� ��
	void	UpdateAfterInsert(UINT iBeginIndex, bool bEndScroll, bool bApplyLastSort);
	

	// ���� (�뷮������ bUpdate false ���� sortȤ�� UpdateAfterInsertȣ�� �ʼ�)
	void	Clear(bool bReDraw, bool bRelease = false);
	int		DeleteFromIndex(UINT index, bool bUpdate);
	int		DeleteFromPtr(const BNC_ReferenceItemEx* ptr, UINT iIdxFindBegin, bool bUpdate);
	int		DeleteFromKey(CString strKey, UINT iIdxFindBegin, bool bUpdate, bool bSeekEnd);
	int		DeleteFromSequnece(UINT uiSequence, UINT iIdxFindBegin, bool bUpdate);
	

	// ���� ȣ�� (pItem�� option�� �����ʿ��� ������ ����)
	void	DeleteRefernce(BNC_ReferenceItemEx* pItem);
	

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


	bool	OnDragAll(void);
	bool	OnDragCopy(void);
	bool	OnDragEnter(BNC_ReferenceItemEx *pDragTarget, CPoint &ptItem, bool bDblClick);
	bool	OnDragMove(BNC_ReferenceItemEx *pDragTarget, CPoint &ptItem);
	bool	OnDragLeave(BNC_ReferenceItemEx *pDragTarget);



public :
	// ������ ���� ����
	void	EnableItem(UINT index, bool bEnable, bool bRedraw);
	bool	IsItemEnable(UINT index);


	UINT	GetItemTotalHeight(void);
	UINT	GetItemTotalHeight(int iWidth);
	UINT	SetListScroll(int iVerScroll, bool bForce = false, bool bRedraw = false);
	UINT	GetListScroll(void);
	UINT	GetEndScroll(void);
	bool	IsEndScroll(void);

	
	// ������ �ٽ� �׸��� (����� ȣ��)
	bool	RedrawItem(CString strKey);


	// ������ ������ ��ȣ ��ȯ
	UINT	GetLastSequence(void);


	// ������ ���� ��ȯ
	UINT	GetItemCount(void);


	// ȭ�鿡 ���̴� �ֻ�� ������ ��ȯ
	BNC_ReferenceItemEx* GetVisibleTopItem(void);


	// Option, SyncRect Window
	void	SyncWindowClear(void);
	void	SyncWindowHide(void);
	void	SyncWindowUpdate(void);
	CRect	GetSyncWindowPos(int iWidth, int iScroll);


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
protected :
	DECLARE_MESSAGE_MAP()

public :
	afx_msg void OnDestroy();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
