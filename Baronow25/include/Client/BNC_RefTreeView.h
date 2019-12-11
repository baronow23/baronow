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
	// 상위 부포에게 메시지 전달할 때 필요한 컨트롤 ID 지정
	USHORT	m_idTree;
	USHORT	m_idScroll;
	USHORT	m_idScroll2;	// 가로스크롤
	


	// 스크롤바 등장시 가변폭 사용여부 (지정시 width - m_iFixBlank)
	int		m_iFixBlank;
	bool	m_bUseVarCtlPos;


	// 가로 스크롤 사용여부 (윈도우 생성전 지정되야함)
	bool	m_bUsingHorScroll;


	// 마우스 캡쳐 되어있을 때 키보드 up-down으로 스크롤링
	bool	m_bUsingKeyScroll;


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
		if(BNC_RefTreeView::OnCreate() == false)
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
		BNC_RefTreeView::OnUpdateClient(cx, cy);
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	}
	*/

	
	bool	OnDraw(CDC* pMemDC, CDC* pResDC);
	/*
	{
		if(BNC_RefTreeView::OnDraw(pMemDC, pResDC) == false)
		{
			return false;
		}
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
		return true;
	}
	*/


	LRESULT OnMessageTree(WPARAM wParam, LPARAM lParam);
	/*
	{
		LRESULT result = BNC_RefTreeView::OnMessageList(wParam, lParam);
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
		return result;
	}
	*/

	
	LRESULT	OnMessageScroll(WPARAM wParam, LPARAM lParam);
	/*
	{
		LRESULT result = BNC_RefTreeView::OnMessageScroll(wParam, lParam);
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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


	// 아이템이 하나도 없을 때 그리기
	virtual void OnDrawNoData(CDC* pMemDC, CDC* pResDC);


	// 아이템 그리기 (각 아이템은 0,0 위치에 그리면 됨)
	// index : 리스트 인덱스
	virtual void OnDrawItem(CDC* pItemDC, CDC* pResDC, BNC_ReferenceItem *pItem, BNE_REFITEM_STATE state, const CSize &szItem) = 0;


	// @todo ************* 한개든 여러개든 무조건 UpdateAfterInsert로 갱신하시오 ****************
	// SortString 0번 인덱스에는 strKey로 설정되며 SyncRect 0번 인덱스는 펼침 영역으로 사용됨 
	// 아이템 추가시마다 정렬 및 스크롤 위치 갱신을 위해서는 bUpdate를 false로 설정하고
	// UpdateAfterInsert() 사용
	bool	Insert(bool bFolder,
				   CString strKey,
				   CString strPKey,
				   void* pRefData,
				   BNC_ReferenceItem &Item,
				   bool bExtend = true,
				   bool bUpdate = false,
				   UINT iOptWidth = 0);


	// @todo ************* pTargetParent = NULL 값 넣으시오 *****************
	// 아이템 삽입, 삭제등을 일괄처리하면서 update를 하지 않았을 경우 호출
	// 마지막에 sort까지 하지 않았을 경우 컨테이너 참조 문제 발생하므로 반드시 호출해 줄 것
	void	UpdateAfterInsert(BNC_ReferenceItem* pTargetParent, bool bEndScroll, bool bApplyLastSort);


	// 삭제
	void	ClearItem(bool bReDraw);
	bool	Delete(CString strKey, bool bUpdate = true);


	// 스크롤 업데이트
	void	UpdateScroll(void);
	void	SetTreeScroll(int iPos);

	// 스크롤 위치가 끝에 있는지 체크
	bool	IsEndScroll(void);


	/*
	// 최초 아이템 삽입후 전체 갱신 필요시 호출 
	// 1. 정렬
	// 2. 루트 리스트 위치 수정
	// 3. 보여지는 최상위 루트 리스트 업데이트
	void	UpdateAll(UINT uiRefStringIndex,
					  bool bAsecending,
					  int iEqualRefIndex = -1,
					  bool bEqualAsecnding = true);
	*/



	// 전체 정렬은 UpdateAll 이용
	// 정렬 (수행후 마우스 액션 초기화됨)
	// 정렬 대상 아이템(폴더만 가능), NULL 지정시 전체수행
	// uiRefStringIndex : 정렬 대상 인덱스
	// bAsecending : 오름차순 여부
	// bWidthSubfolders : 모든 하위 폴더도 같이 정렬 
	// iEqualRefIndex : uiRefStringIndex 결과가 같을 때 추가 비교할 인덱스
	// bEqualAsecnding : iEqualRefIndex 오름차순 여부
	void	SortString(BNC_ReferenceItem* pTargetParent,
					   UINT uiRefStringIndex,
					   bool bAsecending,
					   bool bWidthSubfolders	= false,
					   int	iEqualRefIndex		= -1,
					   bool bEqualAsecnding		= true);


	// 펼침/좁힘
	bool	ExtendItem(BNC_ReferenceItem *pItem, bool bExtend, bool bReDraw = true);
	bool	ExtendItem(CString strKey, bool bExtend, bool bReDraw = true);



	// 특정 아이템 선택
	// return 0 : strKey = _T("")
	// return -1 : 지정키 아이템 없음
	// return 0이상 : 지정키 아이템 top 위치
	int		SetSelectItem(CString strKey, bool bMoveScroll);
	
	
	// 옵션 : 항상 하나의 아이템이 선택되도록 설정
	void	SetUseStaySelect(bool bEnable);


	// 특정 아이템 그리기 갱신
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

