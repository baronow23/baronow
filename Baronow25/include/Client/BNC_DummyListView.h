#pragma once


class BN25_TYPE BNC_DummyListView : public BNC_BaseClient
{
public:
	BNC_DummyListView();
	virtual ~BNC_DummyListView();


protected :
	BNC_DummyListControl	m_ListControl;
	BNC_SimpleVScrollbar	m_vScrollbar;


	
public:
	// ���� �������� �޽��� ������ �� �ʿ��� ��Ʈ�� ID ����
	USHORT		m_idList;
	USHORT		m_idScroll;


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
		if(BNC_DummyListView::OnCreate() == false)
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
		BNC_DummyListView::OnUpdateClient(cx, cy);
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	}
	*/

	
	bool	OnDraw(CDC* pMemDC, CDC* pResDC);
	/*
	{
		if(BNC_DummyListView::OnDraw(pMemDC, pResDC) == false)
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
		LRESULT result = BNC_DummyListView::OnMessageList(wParam, lParam);
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
		return result;
	}
	*/

	
	LRESULT	OnMessageScroll(WPARAM wParam, LPARAM lParam);
	/*
	{
		LRESULT result = BNC_DummyListView::OnMessageScroll(wParam, lParam);
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
		return result;
	}
	*/


public :
	void OnNotifyMouseWheel(UINT nFlags, short zDelta);
	bool OnNotifyKeyDown(WPARAM wKey);


protected :
	void	UpdateControl(int cx, int cy, bool bUpdateScroll);
	

public :
	virtual void OnRedraw(bool bTopMsg);


	// �������� �ϳ��� ���� �� �׸���
	__declspec(deprecated) virtual void OnDrawNoData(CDC* pMemDC, CDC* pResDC);
	virtual void OnDrawBackground(CDC* pMemDC, CDC* pResDC, bool bNoData);


	// ������ �׸��� (�� �������� 0,0 ��ġ�� �׸���, false ��ȯ�� blt ����
	virtual	bool OnDrawIndex(CDC* pItemDC, CDC* pResDC, int index, BNC_ReferenceItem* pItem, BNE_REFITEM_STATE state, const CSize &szItem) = 0;


	virtual UINT GetDeferChildCount(void);


	// ��ũ�� ������Ʈ
	void	UpdateScroll(void);
	void	SetListScroll(int iPos);
	int		GetListScroll(void);

	// Ư�� sequence item ��� ��ġ ��ȯ
	int		GetItemTopPos(int idx);


	///////////////////////////////////////////////////////////////////////////
	void	Clear(bool bRedraw);
	void	Reset(UINT iFixHeight, UINT iUseCount, BNC_ReferenceItem &fixItem, bool bEndScroll, bool bRedraw);
	void	UpdateVisibleIndex(void);
	int		GetUseCount(void)
	{
		return m_ListControl.m_iUseCount;
	};
	

protected :
	DECLARE_MESSAGE_MAP()


public :
	afx_msg void OnDestroy();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

