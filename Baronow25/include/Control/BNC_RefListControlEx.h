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
	

	// BNC_ReferenceItemEx의 BNC_ReferenceItemExOption 삭제 대상 (insert에 지정한 놈들만 모음)
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
// BNC_BaseRefItemControl 필수 메서드
////////////////////////////////////////////////////////////////////////////////////////////////
private :
	// 부모 view 반환
	BNC_RefListViewEx* GetParentView(void);


	// 특정 아이템만 다시 그림
	void	OnRedrawItem(BNC_ReferenceItemEx* pItem, BNE_REFITEM_STATE state);
	

	// 마우스 명령 아이템 다시 그리기
	void	OnDrawMouseItem(CDC* pDC, CDC* pItemDC, CDC* pResDC, BNC_ReferenceItemEx *pItem);


	// ptMouse : 스크롤 되지 않은 클라이언트 마우스 좌표를 입력받고
	// 아이템 Client 좌표로 변환되어 반환
	bool	OnFindItem(_Ret_ CPoint &ptClientToItem, _Ret_ BNC_ReferenceItemEx** ppFindItem);		


	// 마우스 조작으로 이벤트 발생
	void	OnUpdateEvent(BNE_MOUSEACTION action, BNC_ReferenceItemEx *pEventItem);



private :
	void	DrawItemClip(CDC* pBltDC, CDC* pItemDC, CDC* pResDC, BNC_ReferenceItemEx *pItem);
	
////////////////////////////////////////////////////////////////////////////////////////////////
// BNC_RefListControlEx 고유 메서드
////////////////////////////////////////////////////////////////////////////////////////////////
private :
	BNC_ReferenceItemEx*	GetItemPtr(UINT index);
	BNC_ReferenceItemEx*	GetItemPtr(CString &strKey);


	// 아이템 추가
	// return : 추가된 index
	// 아이템 추가시마다 정렬 및 스크롤 위치 갱신을 위해서는 bUpdate를 false로 설정하고
	// UpdateAfterInsert() 사용 (iBeginIndex를 return 값으로 사용)
	int		Insert(CString &strKey, void* pRefData, BNC_ReferenceItemEx &Item, bool bAutoDeleateOption, bool bUpdate);

	
	// 아이템 삽입, 삭제등을 일괄처리하면서 update를 하지 않았을 경우 호출
	// 마지막에 sort까지 하지 않았을 경우 컨테이너 참조 문제 발생하므로 반드시 호출해 줄 것
	void	UpdateAfterInsert(UINT iBeginIndex, bool bEndScroll, bool bApplyLastSort);
	

	// 삭제 (대량삭제로 bUpdate false 사용시 sort혹은 UpdateAfterInsert호출 필수)
	void	Clear(bool bReDraw, bool bRelease = false);
	int		DeleteFromIndex(UINT index, bool bUpdate);
	int		DeleteFromPtr(const BNC_ReferenceItemEx* ptr, UINT iIdxFindBegin, bool bUpdate);
	int		DeleteFromKey(CString strKey, UINT iIdxFindBegin, bool bUpdate, bool bSeekEnd);
	int		DeleteFromSequnece(UINT uiSequence, UINT iIdxFindBegin, bool bUpdate);
	

	// 내부 호출 (pItem의 option과 참조맵에서 아이템 삭제)
	void	DeleteRefernce(BNC_ReferenceItemEx* pItem);
	

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


	bool	OnDragAll(void);
	bool	OnDragCopy(void);
	bool	OnDragEnter(BNC_ReferenceItemEx *pDragTarget, CPoint &ptItem, bool bDblClick);
	bool	OnDragMove(BNC_ReferenceItemEx *pDragTarget, CPoint &ptItem);
	bool	OnDragLeave(BNC_ReferenceItemEx *pDragTarget);



public :
	// 아이템 상태 변경
	void	EnableItem(UINT index, bool bEnable, bool bRedraw);
	bool	IsItemEnable(UINT index);


	UINT	GetItemTotalHeight(void);
	UINT	GetItemTotalHeight(int iWidth);
	UINT	SetListScroll(int iVerScroll, bool bForce = false, bool bRedraw = false);
	UINT	GetListScroll(void);
	UINT	GetEndScroll(void);
	bool	IsEndScroll(void);

	
	// 아이템 다시 그리기 (사용자 호출)
	bool	RedrawItem(CString strKey);


	// 마지막 시퀀스 번호 반환
	UINT	GetLastSequence(void);


	// 아이템 갯수 반환
	UINT	GetItemCount(void);


	// 화면에 보이는 최상단 아이템 반환
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
