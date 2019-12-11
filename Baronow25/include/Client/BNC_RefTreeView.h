#pragma once


class BN25_TYPE BNC_RefTreeView : public BNC_BaseClient
{
public:
	BNC_RefTreeView();
	virtual ~BNC_RefTreeView();


protected :
	BNC_RefTreeControl		m_TreeControl;
	BNC_SimpleVScrollbar	m_vScrollbar;
	BNC_SimpleHScrollbar	m_hScrollbar;


public :
	// ���� �������� �޽��� ������ �� �ʿ��� ��Ʈ�� ID ����
	USHORT	m_idTree;
	USHORT	m_idScroll;
	USHORT	m_idScroll2;	// ���ν�ũ��
	


	// ��ũ�ѹ� ����� ������ ��뿩�� (������ width - m_iFixBlank)
	int		m_iFixBlank;
	bool	m_bUseVarCtlPos;


	// ���� ��ũ�� ��뿩�� (������ ������ �����Ǿ���)
	bool	m_bUsingHorScroll;


	// ���콺 ĸ�� �Ǿ����� �� Ű���� up-down���� ��ũ�Ѹ�
	bool	m_bUsingKeyScroll;


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
		if(BNC_RefTreeView::OnCreate() == false)
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
		BNC_RefTreeView::OnUpdateClient(cx, cy);
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	}
	*/

	
	bool	OnDraw(CDC* pMemDC, CDC* pResDC);
	/*
	{
		if(BNC_RefTreeView::OnDraw(pMemDC, pResDC) == false)
		{
			return false;
		}
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
		return true;
	}
	*/


	LRESULT OnMessageTree(WPARAM wParam, LPARAM lParam);
	/*
	{
		LRESULT result = BNC_RefTreeView::OnMessageList(wParam, lParam);
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
		return result;
	}
	*/

	
	LRESULT	OnMessageScroll(WPARAM wParam, LPARAM lParam);
	/*
	{
		LRESULT result = BNC_RefTreeView::OnMessageScroll(wParam, lParam);
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
		return result;
	}
	*/
	

protected :
	BNC_ReferenceItem*	GetItemPtr(CString strKey);


protected :
	virtual void UpdateControl(int cx, int cy, bool bUpdateScroll);
	void UpdateControlEx(int cx, int cy, bool bUpdateScroll);
	int	GetRealTopPos(const BNC_ReferenceItem *pItem);

public :
	virtual UINT GetDeferChildCount(void);
	

public :
	virtual void OnRedraw(bool bTopMsg);


	// �������� �ϳ��� ���� �� �׸���
	virtual void OnDrawNoData(CDC* pMemDC, CDC* pResDC);


	// ������ �׸��� (�� �������� 0,0 ��ġ�� �׸��� ��)
	// index : ����Ʈ �ε���
	virtual void OnDrawItem(CDC* pItemDC, CDC* pResDC, BNC_ReferenceItem *pItem, BNE_REFITEM_STATE state, const CSize &szItem) = 0;


	// @todo ************* �Ѱ��� �������� ������ UpdateAfterInsert�� �����Ͻÿ� ****************
	// SortString 0�� �ε������� strKey�� �����Ǹ� SyncRect 0�� �ε����� ��ħ �������� ���� 
	// ������ �߰��ø��� ���� �� ��ũ�� ��ġ ������ ���ؼ��� bUpdate�� false�� �����ϰ�
	// UpdateAfterInsert() ���
	bool	Insert(bool bFolder,
				   CString strKey,
				   CString strPKey,
				   void* pRefData,
				   BNC_ReferenceItem &Item,
				   bool bExtend = true,
				   bool bUpdate = false,
				   UINT iOptWidth = 0);


	// @todo ************* pTargetParent = NULL �� �����ÿ� *****************
	// ������ ����, �������� �ϰ�ó���ϸ鼭 update�� ���� �ʾ��� ��� ȣ��
	// �������� sort���� ���� �ʾ��� ��� �����̳� ���� ���� �߻��ϹǷ� �ݵ�� ȣ���� �� ��
	void	UpdateAfterInsert(BNC_ReferenceItem* pTargetParent, bool bEndScroll, bool bApplyLastSort);


	// ����
	void	ClearItem(bool bReDraw);
	bool	Delete(CString strKey, bool bUpdate = true);


	// ��ũ�� ������Ʈ
	void	UpdateScroll(void);
	void	SetTreeScroll(int iPos);

	// ��ũ�� ��ġ�� ���� �ִ��� üũ
	bool	IsEndScroll(void);


	/*
	// ���� ������ ������ ��ü ���� �ʿ�� ȣ�� 
	// 1. ����
	// 2. ��Ʈ ����Ʈ ��ġ ����
	// 3. �������� �ֻ��� ��Ʈ ����Ʈ ������Ʈ
	void	UpdateAll(UINT uiRefStringIndex,
					  bool bAsecending,
					  int iEqualRefIndex = -1,
					  bool bEqualAsecnding = true);
	*/



	// ��ü ������ UpdateAll �̿�
	// ���� (������ ���콺 �׼� �ʱ�ȭ��)
	// ���� ��� ������(������ ����), NULL ������ ��ü����
	// uiRefStringIndex : ���� ��� �ε���
	// bAsecending : �������� ����
	// bWidthSubfolders : ��� ���� ������ ���� ���� 
	// iEqualRefIndex : uiRefStringIndex ����� ���� �� �߰� ���� �ε���
	// bEqualAsecnding : iEqualRefIndex �������� ����
	void	SortString(BNC_ReferenceItem* pTargetParent,
					   UINT uiRefStringIndex,
					   bool bAsecending,
					   bool bWidthSubfolders	= false,
					   int	iEqualRefIndex		= -1,
					   bool bEqualAsecnding		= true);


	// ��ħ/����
	bool	ExtendItem(BNC_ReferenceItem *pItem, bool bExtend, bool bReDraw = true);
	bool	ExtendItem(CString strKey, bool bExtend, bool bReDraw = true);



	// Ư�� ������ ����
	// return 0 : strKey = _T("")
	// return -1 : ����Ű ������ ����
	// return 0�̻� : ����Ű ������ top ��ġ
	int		SetSelectItem(CString strKey, bool bMoveScroll);
	
	
	// �ɼ� : �׻� �ϳ��� �������� ���õǵ��� ����
	void	SetUseStaySelect(bool bEnable);


	// Ư�� ������ �׸��� ����
	void	RedrawItem(CString strKey);


	// Sync Window
	void	SetSyncRectWindow(BNC_BaseClient *pSyncWindow,
							  BNC_ReferenceItem *pSyncItem,
							  UINT idxSyncRect);


	UINT	GetFolderCount(void);
	UINT	GetFileCount(void);


public :
	void	OnNotifyMouseWheel(UINT nFlags, short zDelta);
	bool	OnNotifyKeyDown(WPARAM wKey);

protected :
	DECLARE_MESSAGE_MAP()


public :
	afx_msg void OnDestroy();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

