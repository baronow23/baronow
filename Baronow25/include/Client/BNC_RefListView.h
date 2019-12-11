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
	// 상위 부모에게 메시지 전달할 때 필요한 컨트롤 ID 지정
	USHORT		m_idList;
	USHORT		m_idScroll;


	// 스크롤바 등장시 가변폭 사용여부 (지정시 width - m_iFixBlank)
	int			m_iFixBlank;
	bool		m_bUseVarCtlPos;


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
		if(BNC_RefListView::OnCreate() == false)
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
		BNC_RefListView::OnUpdateClient(cx, cy);
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	}
	*/

	
	bool	OnDraw(CDC* pMemDC, CDC* pResDC);
	/*
	{
		if(BNC_RefListView::OnDraw(pMemDC, pResDC) == false)
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
		LRESULT result = BNC_RefListView::OnMessageList(wParam, lParam);
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
		return result;
	}
	*/

	
	LRESULT	OnMessageScroll(WPARAM wParam, LPARAM lParam);
	/*
	{
		LRESULT result = BNC_RefListView::OnMessageScroll(wParam, lParam);
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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


	// 아이템이 하나도 없을 때 그리기
	virtual void OnDrawNoData(CDC* pMemDC, CDC* pResDC);


	// 아이템 그리기 (각 아이템은 0,0 위치에 그리면 됨)
	// index : 리스트 인덱스
	virtual void OnDrawItem(CDC* pItemDC, CDC* pResDC, BNC_ReferenceItem *pItem, BNE_REFITEM_STATE state, const CSize &szItem) = 0;


	// 아이템 추가
	// return : 추가된 index
	// 아이템 추가시마다 정렬 및 스크롤 위치 갱신을 위해서는 bUpdate를 false로 설정하고
	// UpdateAfterInsert() 사용할 것
	int		Insert(CString strKey, const void* pRefData, BNC_ReferenceItem &Item, bool bUpdate);


	// 아이템 삽입, 삭제등을 일괄처리하면서 update를 하지 않았을 경우 호출
	// 마지막에 sort까지 하지 않았을 경우 컨테이너 참조 문제 발생하므로 반드시 호출해 줄 것
	void	UpdateAfterInsert(int iBeginIndex, bool bEndScroll, bool bApplyLastSort);



	// 삭제
	void	ClearItem(bool bReDraw);
	int		DeleteItemFromIndex(UINT index, bool bUpdate);
	int		DeleteItemFromPtr(const BNC_ReferenceItem* ptr, UINT iIdxFindBegin, bool bUpdate);
	int		DeleteItemFromKey(CString strKey, UINT iIdxFindBegin, bool bUpdate, bool bSeekEnd);
	int		DeleteItemFromSequnece(UINT uiSequence, UINT iIdxFindBegin, bool bUpdate);


	// 정렬 문자열 변경
	bool	ModifySortString(LPCTSTR strItemKey, UINT uiSortIndex, LPCTSTR strSort);


	// 정렬
	void	SortString(UINT uiRefStringIndex, bool bAsecending, int iEqualRefIndex = -1, bool bEqualAsecnding = true);
	void	SortSequence(bool bAsecending);


	// 스크롤 업데이트
	void	UpdateScroll(void);
	void	SetListScroll(int iPos);


	// 아이템 다시 그리기 (사용자 호출)
	void	RedrawItem(CString strKey);
	void	RedrawItem(BNC_ReferenceItem* pItem);

	// 외부 호출, 정렬할 필요가 없을 때 보여지는 인덱스만 갱신 (cs 사용)
	void	UpdateOnlyVisibleIndex(void);


	// 아이템 상태 변경
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

