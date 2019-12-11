#pragma once


class BN25_TYPE BNC_RefListControl :	public BNC_BaseRefItemControl
{
	friend class BNC_RefListView;


public:
	BNC_RefListControl(void);
	virtual ~BNC_RefListControl(void);
	

private :
	UINT				m_uiTotalItemHeight;				// 전체 아이템 높이
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
// BNC_BaseRefItemControl 필수 메서드
////////////////////////////////////////////////////////////////////////////////////////////////
private :
	// 특정 아이템만 다시 그림
	void	OnRedrawItem(BNC_ReferenceItem* pItem, BNE_REFITEM_STATE state);
	

	// 마우스 명령 아이템 다시 그리기
	void	OnDrawMouseItem(CDC* pDC, CDC* pItemDC, CDC* pResDC, BNC_ReferenceItem *pItem);


	// ptMouse : 스크롤 되지 않은 클라이언트 마우스 좌표를 입력받고
	// 아이템 Client 좌표로 변환되어 반환
	bool	OnFindItem(_Ret_ CPoint &ptClientToItem, _Ret_ BNC_ReferenceItem** ppFindItem);		


	// 마우스 조작으로 이벤트 발생
	void	OnUpdateEvent(BNE_MOUSEACTION action, BNC_ReferenceItem *pEventItem);


	
////////////////////////////////////////////////////////////////////////////////////////////////
// BNC_RefListControl 고유 메서드
////////////////////////////////////////////////////////////////////////////////////////////////
private :
	BNC_ReferenceItem*	GetItemPtr(UINT index);
	BNC_ReferenceItem*	GetItemPtr(CString &strKey);
	bool				GetItemList(std::vector<BNC_ReferenceItem*> &vList);
	int					GetItemCount(void);


	// 아이템 추가
	// return : 추가된 index
	// 아이템 추가시마다 정렬 및 스크롤 위치 갱신을 위해서는 bUpdate를 false로 설정하고
	// UpdateAfterInsert() 사용 (iBeginIndex를 return 값으로 사용)
	int		Insert(CString &strKey, const void* pRefData, BNC_ReferenceItem &Item, bool bUpdate);

	
	// 아이템 삽입, 삭제등을 일괄처리하면서 update를 하지 않았을 경우 호출
	// 마지막에 sort까지 하지 않았을 경우 컨테이너 참조 문제 발생하므로 반드시 호출해 줄 것
	void	UpdateAfterInsert(UINT iBeginIndex, bool bEndScroll, bool bApplyLastSort);



	// 삭제 (대량삭제로 bUpdate false 사용시 sort혹은 UpdateAfterInsert호출 필수)
	void	Clear(bool bReDraww, bool bRelease = false);
	int		DeleteFromIndex(UINT index, bool bUpdate);
	int		DeleteFromPtr(const BNC_ReferenceItem* ptr, UINT iIdxFindBegin, bool bUpdate);
	int		DeleteFromKey(CString strKey, UINT iIdxFindBegin, bool bUpdate, bool bSeekEnd);
	int		DeleteFromSequnece(UINT uiSequence, UINT iIdxFindBegin, bool bUpdate);
	

	// 내부 호출 (참조맵에서 아이템 삭제)
	void	DeleteRefernce(BNC_ReferenceItem* pItem);


	// 정렬 문자열 변경
	bool	ModifySortString(LPCTSTR strItemKey, UINT uiSortIndex, LPCTSTR strSort);
	


	// 정렬
	// uiRefStringIndex : 정렬 대상 인덱스
	// bAsecending : 오름차순 여부
	// iEqualRefIndex : uiRefStringIndex 결과가 같을 때 추가 비교할 인덱스
	// bEqualAsecnding : iEqualRefIndex 오름차순 여부
	void	SortString(UINT uiRefStringIndex,
					   bool bAsecending,
					   int iEqualRefIndex	= -1,
					   bool bEqualAsecnding	= true);

	void	SortSequence(bool bAsecending);


	// 아이템 항목의 위치(top, bottom) 갱신 : index(삽입 삭제된 인덱스)
	// 삽입 삭제시 호출
	void	UpdateItemPos(bool bMoveEndScroll, int index);



	// 화면에 보여지는 인덱스 갱신
	// 삽입, 삭제, 스크롤 위치 변경(클라이언트 크기 변경 포함)시 호출
	void	UpdateVisibleIndex(void);



public :
	// 아이템 상태 변경
	void	EnableItemIdx(UINT index, bool bEnable, bool bRedraw);
	void	EnableItemPtr(BNC_ReferenceItem* pItem, bool bEnable, bool bRedraw);
	bool	IsItemIdxEnable(UINT index);
	bool	IsItemPtrEnable(BNC_ReferenceItem* pItem);



	UINT	GetItemTotalHeight(void);
	UINT	SetListScroll(int iVerScroll, bool bForce = false, bool bRedraw = false);
	UINT	GetListScroll(void);

	
	// 아이템 다시 그리기 (사용자 호출)
	void	RedrawItem(CString strKey);
	void	RedrawItem(BNC_ReferenceItem* pItem);



	// 외부 호출, 정렬할 필요가 없을 때 보여지는 인덱스만 갱신 (cs 사용)
	void	UpdateOnlyVisibleIndex(void);


	// Option, SyncRect Window
	void	SyncWindowClear(void);
	void	SyncWindowHide(void);
	void	SyncWindowUpdate(void);


	// 화면에 보이는 최상단 아이템 반환
	BNC_ReferenceItem* GetVisibleTopItem(void);


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
protected :
	DECLARE_MESSAGE_MAP()

public :
	afx_msg void OnDestroy();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
