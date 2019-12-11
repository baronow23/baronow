#pragma once


// @todo 최적화 않됬음 (중단)

class BN25_TYPE BNC_RefTreeControl : public BNC_BaseRefItemControl
{
	friend class BNC_RefTreeView;


public:
	BNC_RefTreeControl(void);
	virtual ~BNC_RefTreeControl(void);
	

private :
	BNC_RefTreeView*	m_pParentView;


////////////////////////////////////////////////////////////////////////////////
// 트리 아이템 
////////////////////////////////////////////////////////////////////////////////
private:
	// 아이템 관리를 위해 가상으로 존재하는 최상위 루트
	// 상위 부모를 갖지 않는 유일한 객체
	BNC_ReferenceItem		m_VirtualRoot;
	BNC_RefTreeItemOption*	m_pRootOpt;
	

	// 사용자가 Insert 시킨 실제 아이템
	// 1) 부모 key가 없으면 Item을 NULL로 지정하면 m_VirtualRoot가 부모가 되며 실제로는 최상위 루트가 됨
	// 2) 스크롤링이나, 윈도우 사이즈 변경시 전체 아이템위치를 갱신하는 것은 부하가 발생하므로 최상위 루트(m_VirtualRoot의 자식) 만 갱신함
	// 3) 각 아이템의 위치(GetItemTop, GetItemBottom)는 부모위치(bottom)에서의 상대값을 사용하며 
	//    그릴 필요가 있을 때 화면에 보이는 절대위치를 추적하여 적용함
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
// BNC_BaseRefItemControl 필수 메서드
////////////////////////////////////////////////////////////////////////////////////////////////
private:
	// 특정 아이템만 다시 그림
	void	OnRedrawItem(BNC_ReferenceItem* pItem, BNE_REFITEM_STATE state);


	// 마우스 명령 아이템 다시 그리기
	void	OnDrawMouseItem(CDC* pDC, CDC* pItemDC, CDC* pResDC, BNC_ReferenceItem *pItem);


	// 특정 마우스가 위치한 아이템과 클라이언트 좌표 top 얻기
	bool	OnFindItem(_Ret_ CPoint &ptClientToItem, _Ret_ BNC_ReferenceItem **ppItem);


	// 마우스 조작으로 이벤트 발생
	void	OnUpdateEvent(BNE_MOUSEACTION action, BNC_ReferenceItem *pEventItem);


////////////////////////////////////////////////////////////////////////////////////////////////
// BNC_RefTreeControl 고유 메서드
////////////////////////////////////////////////////////////////////////////////////////////////
private:
	BNC_RefTreeItemOption*	GetOption(BNC_ReferenceItem* pItem);
	

	// @todo ************* 한개든 여러개든 무조건 UpdateAfterInsert로 갱신하시오 ****************
	// SortString 0번 인덱스에는 strKey로 설정되며 SyncRect 0번 인덱스는 펼침 영역으로 사용됨 
	// 아이템 추가시마다 정렬 및 스크롤 위치 갱신을 위해서는 bUpdate를 false로 설정하고
	// UpdateAfterInsert() 사용
	bool	Insert(bool		bFolder,
				   CString	&strKey,
				   CString	&strPKey,
				   void*	pRefData,
				   BNC_ReferenceItem &Item,
				   bool		bExtend,
				   bool		bUpdate,
				   UINT		iOptWidth);


	// @todo ************* pTargetParent = NULL 값 넣으시오 *****************
	// 아이템 삽입, 삭제등을 일괄처리하면서 update를 하지 않았을 경우 호출
	// 마지막에 sort까지 하지 않았을 경우 컨테이너 참조 문제 발생하므로 반드시 호출해 줄 것
	void	UpdateAfterInsert(BNC_ReferenceItem* pTargetParent, bool bEndScroll, bool bApplyLastSort);


	/*
	// 최초 아이템 삽입후 전체 갱신 필요시 호출 
	// 1. 정렬
	// 2. 루트 리스트 위치 수정
	// 3. 보여지는 최상위 루트 리스트 업데이트
	void	UpdateAll(UINT uiRefStringIndex, bool bAsecending, int iEqualRefIndex = -1, bool bEqualAsecnding = true);
	*/


	// 삭제 (대량삭제로 bUpdate false 사용시 sort혹은 UpdateAfterInsert호출 필수)
	void	Clear(bool bReDraw, bool bRelease = false);
	bool	Delete(CString strKey, bool bUpdate);
	
	
	// 상위모든 부모 컨테이너와 메모리 반납
	void	DeleteContainer(bool bIsFoler, BNC_RefTreeItemOption* pBeginParent, BNC_ReferenceItem* pDelete);


	// 정렬
	// 정렬 대상 아이템(폴더만 가능), NULL 지정시 전체수행
	// uiRefStringIndex : 정렬 대상 인덱스
	// bAsecending : 오름차순 여부
	// bWidthSubfolders : 모든 하위 폴더도 같이 정렬 
	// iEqualRefIndex : uiRefStringIndex 결과가 같을 때 추가 비교할 인덱스
	// bEqualAsecnding : iEqualRefIndex 오름차순 여부
	bool	SortString(BNC_ReferenceItem* pTargetParent,
					   UINT uiRefStringIndex,
					   bool bAsecending,
					   bool bWithSubfolders		= false,
					   int	iEqualRefIndex		= -1,
					   bool bEqualAsecnding		= true,
					   bool bRedraw				= true);
	

	// pItem의 폴더, 확장여부를 확인하고 pItem의 자식이 포함된 가장 하단의 위치 반환
	int		GetApplyExtendBottom(BNC_ReferenceItem *pItem);


	// 아이템의 변경시 (추가, 삭제, 펼쳐짐, 좁혀짐) 호출되며
	// 부모 아이템의 확장 높이를 수정함 (최상위까지 방문)
	void	ModifyParentExHeight(BNC_ReferenceItem* pParentItem, int iAddExHeight);


	// child 리스트 위치 갱신 (삽입, 삭제, 펼침시)
	void	UpdateChildListPos(UINT iBeginIndex, BNC_ReferenceItem *pParentItem);


	// 보여지는 최상이 루트 리스트 업데이트(시작, 끝 인덱스)
	void	UpdateTopRootVisibleIndex(void);


	// 특정 아이템 다시 그림
	void	RedrawItem(CString strKey);

	// pItem부터 하위 자식들을 모두 그림
	// 그리기 영역을 벗어나면 false 반환
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

	
	// 화면에 보이는 실제 top 위치 반환
	int		GetRealTopPos(const BNC_ReferenceItem *pItem);

	
	// 펼침/좁힘
	bool	ExtendItem(BNC_ReferenceItem *pItem, bool bExtend, bool bReDraw = true);
	bool	ExtendItem(CString strKey, bool bExtend, bool bReDraw = true);

	
public :
	// 아이템 상태 변경
	void	EnableItem(CString strKey, bool bEnable, bool bRedraw);
	bool	IsItemEnable(CString strKey);


	BNC_ReferenceItem* GetItemPtr(CString &strKey);
	UINT	GetVisiableHeight(void);
	UINT	SetTreeScroll(const BNC_ReferenceItem *pItem, int iTopShift, bool bForce, bool bRedraw);
	UINT	SetTreeScroll(int iVerScroll, bool bForce = false, bool bRedraw = false);
	UINT	SetTreeScrollNoUpate(int iVerScroll);
	UINT	GetTreeScroll(void);
	bool	IsEndScroll(void);


	// 보여지는 아이템의 최대 넓이 반환 (NULL 입력)
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
	//afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);	// 부모에서 컨트롤 할 것
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
