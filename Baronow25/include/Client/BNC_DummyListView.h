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
	// 상위 부포에게 메시지 전달할 때 필요한 컨트롤 ID 지정
	USHORT		m_idList;
	USHORT		m_idScroll;


	// 마우스 캡쳐 되어있을 때 키보드 up-down으로 스크롤링
	bool		m_bUsingKeyScroll;


	// 컨트롤 상하단 자르기
	short	m_iCtlOffTop;
	short	m_iCtlOffBottom;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 상속 오버라이딩시 꼭 호출해줄 것
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected :
	bool	OnCreate(void);
	/*
	{
		if(BNC_DummyListView::OnCreate() == false)
		{
			return false;
		}
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
		return true;
	}
	*/


	void	OnUpdateClient(int cx, int cy);
	/*
	{
		BNC_DummyListView::OnUpdateClient(cx, cy);
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	}
	*/

	
	bool	OnDraw(CDC* pMemDC, CDC* pResDC);
	/*
	{
		if(BNC_DummyListView::OnDraw(pMemDC, pResDC) == false)
		{
			return false;
		}
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
		return true;
	}
	*/


	LRESULT OnMessageList(WPARAM wParam, LPARAM lParam);
	/*
	{
		LRESULT result = BNC_DummyListView::OnMessageList(wParam, lParam);
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
		return result;
	}
	*/

	
	LRESULT	OnMessageScroll(WPARAM wParam, LPARAM lParam);
	/*
	{
		LRESULT result = BNC_DummyListView::OnMessageScroll(wParam, lParam);
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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


	// 아이템이 하나도 없을 때 그리기
	__declspec(deprecated) virtual void OnDrawNoData(CDC* pMemDC, CDC* pResDC);
	virtual void OnDrawBackground(CDC* pMemDC, CDC* pResDC, bool bNoData);


	// 아이템 그리기 (각 아이템은 0,0 위치에 그리고, false 반환시 blt 않함
	virtual	bool OnDrawIndex(CDC* pItemDC, CDC* pResDC, int index, BNC_ReferenceItem* pItem, BNE_REFITEM_STATE state, const CSize &szItem) = 0;


	virtual UINT GetDeferChildCount(void);


	// 스크롤 업데이트
	void	UpdateScroll(void);
	void	SetListScroll(int iPos);
	int		GetListScroll(void);

	// 특정 sequence item 상단 위치 반환
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

