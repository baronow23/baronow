#pragma once


// @todo ����ȭ �ʉ��� (�ߴ�)

class BN25_TYPE BNC_RefTreeControl : public BNC_BaseRefItemControl
{
	friend class BNC_RefTreeView;


public:
	BNC_RefTreeControl(void);
	virtual ~BNC_RefTreeControl(void);
	

private :
	BNC_RefTreeView*	m_pParentView;


////////////////////////////////////////////////////////////////////////////////
// Ʈ�� ������ 
////////////////////////////////////////////////////////////////////////////////
private:
	// ������ ������ ���� �������� �����ϴ� �ֻ��� ��Ʈ
	// ���� �θ� ���� �ʴ� ������ ��ü
	BNC_ReferenceItem		m_VirtualRoot;
	BNC_RefTreeItemOption*	m_pRootOpt;
	

	// ����ڰ� Insert ��Ų ���� ������
	// 1) �θ� key�� ������ Item�� NULL�� �����ϸ� m_VirtualRoot�� �θ� �Ǹ� �����δ� �ֻ��� ��Ʈ�� ��
	// 2) ��ũ�Ѹ��̳�, ������ ������ ����� ��ü ��������ġ�� �����ϴ� ���� ���ϰ� �߻��ϹǷ� �ֻ��� ��Ʈ(m_VirtualRoot�� �ڽ�) �� ������
	// 3) �� �������� ��ġ(GetItemTop, GetItemBottom)�� �θ���ġ(bottom)������ ��밪�� ����ϸ� 
	//    �׸� �ʿ䰡 ���� �� ȭ�鿡 ���̴� ������ġ�� �����Ͽ� ������
	std::map<CString, BNC_ReferenceItem*> m_mpItem;

	UINT	m_uiFolderCount;
	UINT	m_uiFileCount;

	
public :
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
private:
	// Ư�� �����۸� �ٽ� �׸�
	void	OnRedrawItem(BNC_ReferenceItem* pItem, BNE_REFITEM_STATE state);


	// ���콺 ��� ������ �ٽ� �׸���
	void	OnDrawMouseItem(CDC* pDC, CDC* pItemDC, CDC* pResDC, BNC_ReferenceItem *pItem);


	// Ư�� ���콺�� ��ġ�� �����۰� Ŭ���̾�Ʈ ��ǥ top ���
	bool	OnFindItem(_Ret_ CPoint &ptClientToItem, _Ret_ BNC_ReferenceItem **ppItem);


	// ���콺 �������� �̺�Ʈ �߻�
	void	OnUpdateEvent(BNE_MOUSEACTION action, BNC_ReferenceItem *pEventItem);


////////////////////////////////////////////////////////////////////////////////////////////////
// BNC_RefTreeControl ���� �޼���
////////////////////////////////////////////////////////////////////////////////////////////////
private:
	BNC_RefTreeItemOption*	GetOption(BNC_ReferenceItem* pItem);
	

	// @todo ************* �Ѱ��� �������� ������ UpdateAfterInsert�� �����Ͻÿ� ****************
	// SortString 0�� �ε������� strKey�� �����Ǹ� SyncRect 0�� �ε����� ��ħ �������� ���� 
	// ������ �߰��ø��� ���� �� ��ũ�� ��ġ ������ ���ؼ��� bUpdate�� false�� �����ϰ�
	// UpdateAfterInsert() ���
	bool	Insert(bool		bFolder,
				   CString	&strKey,
				   CString	&strPKey,
				   void*	pRefData,
				   BNC_ReferenceItem &Item,
				   bool		bExtend,
				   bool		bUpdate,
				   UINT		iOptWidth);


	// @todo ************* pTargetParent = NULL �� �����ÿ� *****************
	// ������ ����, �������� �ϰ�ó���ϸ鼭 update�� ���� �ʾ��� ��� ȣ��
	// �������� sort���� ���� �ʾ��� ��� �����̳� ���� ���� �߻��ϹǷ� �ݵ�� ȣ���� �� ��
	void	UpdateAfterInsert(BNC_ReferenceItem* pTargetParent, bool bEndScroll, bool bApplyLastSort);


	/*
	// ���� ������ ������ ��ü ���� �ʿ�� ȣ�� 
	// 1. ����
	// 2. ��Ʈ ����Ʈ ��ġ ����
	// 3. �������� �ֻ��� ��Ʈ ����Ʈ ������Ʈ
	void	UpdateAll(UINT uiRefStringIndex, bool bAsecending, int iEqualRefIndex = -1, bool bEqualAsecnding = true);
	*/


	// ���� (�뷮������ bUpdate false ���� sortȤ�� UpdateAfterInsertȣ�� �ʼ�)
	void	Clear(bool bReDraw, bool bRelease = false);
	bool	Delete(CString strKey, bool bUpdate);
	
	
	// ������� �θ� �����̳ʿ� �޸� �ݳ�
	void	DeleteContainer(bool bIsFoler, BNC_RefTreeItemOption* pBeginParent, BNC_ReferenceItem* pDelete);


	// ����
	// ���� ��� ������(������ ����), NULL ������ ��ü����
	// uiRefStringIndex : ���� ��� �ε���
	// bAsecending : �������� ����
	// bWidthSubfolders : ��� ���� ������ ���� ���� 
	// iEqualRefIndex : uiRefStringIndex ����� ���� �� �߰� ���� �ε���
	// bEqualAsecnding : iEqualRefIndex �������� ����
	bool	SortString(BNC_ReferenceItem* pTargetParent,
					   UINT uiRefStringIndex,
					   bool bAsecending,
					   bool bWithSubfolders		= false,
					   int	iEqualRefIndex		= -1,
					   bool bEqualAsecnding		= true,
					   bool bRedraw				= true);
	

	// pItem�� ����, Ȯ�忩�θ� Ȯ���ϰ� pItem�� �ڽ��� ���Ե� ���� �ϴ��� ��ġ ��ȯ
	int		GetApplyExtendBottom(BNC_ReferenceItem *pItem);


	// �������� ����� (�߰�, ����, ������, ������) ȣ��Ǹ�
	// �θ� �������� Ȯ�� ���̸� ������ (�ֻ������� �湮)
	void	ModifyParentExHeight(BNC_ReferenceItem* pParentItem, int iAddExHeight);


	// child ����Ʈ ��ġ ���� (����, ����, ��ħ��)
	void	UpdateChildListPos(UINT iBeginIndex, BNC_ReferenceItem *pParentItem);


	// �������� �ֻ��� ��Ʈ ����Ʈ ������Ʈ(����, �� �ε���)
	void	UpdateTopRootVisibleIndex(void);


	// Ư�� ������ �ٽ� �׸�
	void	RedrawItem(CString strKey);

	// pItem���� ���� �ڽĵ��� ��� �׸�
	// �׸��� ������ ����� false ��ȯ
	bool	DrawChildItem(int iChildIndex,
						  CDC* pMemDC,
						  CDC* pResDC,
						  CDC* pItemDC,
						  BNC_ReferenceItem *pItem,
						  int iParentBottom,
						  bool &bFindSyncItem);


	bool	GetItemKey(BNC_ReferenceItem *pItem,
					   int iPos,
					   int iParentBottom,
					   _Ret_ BNC_ReferenceItem **ppItem,
					   _Ret_ int &iClientTop,
					   _Ret_ CPoint &ptClientToItem);

	
	// ȭ�鿡 ���̴� ���� top ��ġ ��ȯ
	int		GetRealTopPos(const BNC_ReferenceItem *pItem);

	
	// ��ħ/����
	bool	ExtendItem(BNC_ReferenceItem *pItem, bool bExtend, bool bReDraw = true);
	bool	ExtendItem(CString strKey, bool bExtend, bool bReDraw = true);

	
public :
	// ������ ���� ����
	void	EnableItem(CString strKey, bool bEnable, bool bRedraw);
	bool	IsItemEnable(CString strKey);


	BNC_ReferenceItem* GetItemPtr(CString &strKey);
	UINT	GetVisiableHeight(void);
	UINT	SetTreeScroll(const BNC_ReferenceItem *pItem, int iTopShift, bool bForce, bool bRedraw);
	UINT	SetTreeScroll(int iVerScroll, bool bForce = false, bool bRedraw = false);
	UINT	SetTreeScrollNoUpate(int iVerScroll);
	UINT	GetTreeScroll(void);
	bool	IsEndScroll(void);


	// �������� �������� �ִ� ���� ��ȯ (NULL �Է�)
	UINT	GetVisibleMaxWidth(void);


	// Option, SyncRect Window
	void	SyncWindowClear(void);
	void	SyncWindowHide(void);
	void	SyncWindowUpdate(void);


	UINT	GetFolderCount(void);
	UINT	GetFileCount(void);


private :
	void	GetVisibleMaxWidth(BNC_ReferenceItem *pItem, UINT &uiMaxWidth);


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
protected :
	DECLARE_MESSAGE_MAP()

public :
	afx_msg void OnDestroy();
	//afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);	// �θ𿡼� ��Ʈ�� �� ��
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
