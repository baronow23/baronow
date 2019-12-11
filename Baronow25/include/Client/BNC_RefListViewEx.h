#pragma once


class BN25_TYPE BNC_RefListViewEx : public BNC_BaseClient
{
public:
	BNC_RefListViewEx();
	virtual ~BNC_RefListViewEx();


protected :
	BNC_RefListControlEx	m_ListControlEx;
	BNC_SimpleVScrollbar	m_vScrollbar;
	int						m_iListWidth;


	int		m_iScrollPosMaxBegin;
	int		m_iScrollPosMaxEnd;
	int		m_iScrollPosResBegin;
	int		m_iScrollPosResEnd;
	bool	m_bCheckResotreSize;
	

public:
	// ���� �θ𿡰� �޽��� ������ �� �ʿ��� ��Ʈ�� ID ����
	USHORT		m_idList;
	USHORT		m_idScroll;


	// ��ũ�ѹ� ����� ������ ��뿩�� (������ width - m_iFixBlank)
	int			m_iFixBlank;


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
		if(BNC_RefListViewEx::OnCreate() == false)
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
		BNC_RefListViewEx::OnUpdateClient(cx, cy);
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	}
	*/

	
	bool	OnDraw(CDC* pMemDC, CDC* pResDC);
	/*
	{
		if(BNC_RefListViewEx::OnDraw(pMemDC, pResDC) == false)
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
		LRESULT result = BNC_RefListViewEx::OnMessageList(wParam, lParam);
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
		return result;
	}
	*/

	
	LRESULT	OnMessageScroll(WPARAM wParam, LPARAM lParam);
	/*
	{
		LRESULT result = BNC_RefListViewEx::OnMessageScroll(wParam, lParam);
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
		return result;
	}
	*/


public :
	void OnNotifyMouseWheel(UINT nFlags, short zDelta);
	bool OnNotifyKeyDown(WPARAM wKey);


protected :
	const BNC_ReferenceItemEx*	GetItemPtr(UINT index);
	const BNC_ReferenceItemEx*	GetItemPtr(CString strKey);
	virtual void UpdateControl(int cx, int cy, bool bUpdateScroll);


protected :
	void OnUpdatePopupStatus(BNE_POPUP_STATUS status);


public :
	virtual UINT GetDeferChildCount(void);


public :
	virtual void OnRedraw(bool bTopMsg);


	// �������� �ϳ��� ���� �� �׸���
	virtual void OnDrawNoData(CDC* pMemDC, CDC* pResDC);


	// ������ �׸��� (�� �������� 0,iTop ��ġ�� �׸��� ��
	// iBaseLine�� 0�� �ƴѰ��(�������ش�) ��¾������� Ŭ���̾�Ʈ ������ ��� �����ϰ� �ִٴ� �ǹ��̸�
	// iBaseLine�� �����Ͽ� �׸� ��ġ�� �����ؾ���
	// index : ����Ʈ �ε���
	virtual void OnDrawItem(CDC* pItemDC, CDC* pResDC, BNC_ReferenceItemEx *pItem, BNE_REFITEM_STATE state,
							int iBaseLine, const CSize szItem, int iVisibleHeight) = 0;


	// ������ �߰�
	// return : �߰��� index
	// ������ �߰��ø��� ���� �� ��ũ�� ��ġ ������ ���ؼ��� bUpdate�� false�� �����ϰ�
	// UpdateAfterInsert() ����� ��
	int		Insert(CString &strKey, void* pRefData, BNC_ReferenceItemEx &Item, bool bAutoDeleateOption, bool bUpdate);
	

	// ������ ����, �������� �ϰ�ó���ϸ鼭 update�� ���� �ʾ��� ��� ȣ��
	// �������� sort���� ���� �ʾ��� ��� �����̳� ���� ���� �߻��ϹǷ� �ݵ�� ȣ���� �� ��
	void	UpdateAfterInsert(int iBeginIndex, bool bEndScroll, bool bApplyLastSort);



	// ����
	void	ClearItem(bool bReDraw);
	int		DeleteItemFromIndex(UINT index, bool bUpdate);
	int		DeleteItemFromPtr(const BNC_ReferenceItemEx* ptr, UINT iIdxFindBegin, bool bUpdate);
	int		DeleteItemFromKey(CString strKey, UINT iIdxFindBegin, bool bUpdate, bool bSeekEnd);
	int		DeleteItemFromSequnece(UINT uiSequence, UINT iIdxFindBegin, bool bUpdate);


	// ����
	void	SortString(UINT uiRefStringIndex, bool bAsecending, int iEqualRefIndex = -1, bool bEqualAsecnding = true);
	void	SortSequence(bool bAsecending);


	// ��ũ�� ������Ʈ
	void	UpdateScroll(void);
	void	SetListScroll(int iPos);	// ������ ������ �̵�
	UINT	GetListScroll(void);
	UINT	GetEndScroll(void);


	// ��ũ�� end üũ
	bool	IsEndScroll(void);


	// ������ �ٽ� �׸��� (����� ȣ��)
	bool	RedrawItem(CString strKey);
	

	// Sync Window
	void	SetSyncRectWindow(BNC_BaseClient *pSyncWindow,
							  BNC_ReferenceItemEx *pSyncItem,
							  UINT idxSyncRect);
	
protected :
	DECLARE_MESSAGE_MAP()


public :
	afx_msg void OnDestroy();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};

