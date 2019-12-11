#pragma once

class BNC_RefListViewEx;
class BN25_TYPE BNC_BaseRefItemControlEx : public BNC_BaseControl
{
public:
	BNC_BaseRefItemControlEx();
	virtual ~BNC_BaseRefItemControlEx();


protected :
	// BNC_ReferenceItem 동기화용
	CRITICAL_SECTION	m_cs;

	UINT				m_piTotalItemHeight[BND_REFITEMEX_IDXCOUNT];
	UINT				m_iCurWidthIndex;		// 현재 클라이언트 크기에 맞는 idx;


	// 마우스 명령으로 변경 처리된 아이템 포인터
	std::set<BNC_ReferenceItemEx*>		m_sSelectItem;
	BNC_ReferenceItemEx*				m_pLastSelectItem;
	BNC_ReferenceItemEx*				m_pLastClickUpItem;
	BNC_ReferenceItemEx*				m_pNewMouseItem;
	BNC_ReferenceItemEx*				m_pOldMouseItem;


	// 화면에 보이는 인덱스 (트리에서는 root 직속 차일드 인덱스)
	int		m_idxVisibleBegin;
	int		m_idxVisibleEnd;

	
	UINT	m_uiSequence;			// 삽입된 시퀀스 번호
	bool	m_bDrawing;				// 그리기 작업 처리중 (UpdateMouseAction 무시됨)
	CSize	m_szMaxItem;			// 아이템 최대 크기(clear 전까지 유지)
	CSize	m_szScroll;				// 스크롤 범위

	
	// 마지막 정렬 값 (상속클래스에서 업데이트)
	BNS_ReferenceItemSortOption	m_LastSortOption;

	
	// Drag Select Item
	BNC_ReferenceItemEx *m_pDragTarget;
	CPoint				m_ptDragBeginItem;
	CPoint				m_ptDragBeginClient;
	bool				m_bDragMove;


public:
	COLORREF	m_colorBG;
	bool		m_bUseMultiSelect;
	bool		m_bUseStaySelect;		// 항상 하나의 선택을 유지
	int			m_iSelProcessIdx;		// 아이템 선택에 적용할 RectIndex 값 (지정 인덱스보다 같거나 작으면 선택 처리)

private :
	// 마우스 조작 상태 변경
	// 특정 인덱스 값이 변경되면 새로 그려주고 부모에게 메시지 보냄
	// 내부 CS 사용
	void	UpdateMouseAction(UINT nFlags, BNE_MOUSEACTION action, CPoint &ptClient);
	bool	UpdateLBtnSelect(UINT nFlags, BNC_ReferenceItemEx* pOnFindItem, CPoint &ptItem);
	bool	UpdateRBtnSelect(UINT nFlags, BNC_ReferenceItemEx* pOnFindItem, CPoint &ptItem);
	
	
	// 마우스 조작 아이템 변경
	void	UpdateMouseItem(BNC_ReferenceItemEx* pUpdate);


	// 마우스 액션 비교
	bool	IsCompareMouseAction(BNC_ReferenceItemEx* pItem1, BNC_ReferenceItemEx* pItem2);


	// 마우스 이벤트 아이템 다시 그리기
	virtual void	DrawMouseActionItem(bool bDrawLastSelect);


	// Drag Function
	void	DragEnter(BNC_ReferenceItemEx* pItem, CPoint &ptClient, CPoint &ptItem, bool bDblClick);
	void	DragMove(CPoint &ptClient);

public :
	void	DragLeave(void);
	
private :
	virtual bool OnDragEnter(BNC_ReferenceItemEx *pDragTarget, CPoint &ptItem, bool bDblClick);
	virtual bool OnDragMove(BNC_ReferenceItemEx *pDragTarget, CPoint &ptItem);
	virtual bool OnDragLeave(BNC_ReferenceItemEx *pDragTarget);


protected :
	void	ClearMouseItem(bool bUpdate = true);


	// 마우스 조작된 아이템
	const BNC_ReferenceItemEx*				GetNewMouseItem(void);
	const BNC_ReferenceItemEx*				GetOldMouseItem(void);
	const BNC_ReferenceItemEx*				GetLastSelectItem(void);
	const std::set<BNC_ReferenceItemEx*>	GetSelectItemList(void);


	// 아이템 삭제시 호출 할 것
	void	UpdateDeleteItem(BNC_ReferenceItemEx* pItem);
	

	// 기본 아이템 그리기 (각 아이템은 0,0 위치에 그리면 됨)
	void	DefaultDrawItem(CDC* pItemDC, CDC* pResDC, BNC_ReferenceItemEx *pItem, BNE_REFITEM_STATE state, const CSize szItem);


	// 아이템 그리기 상태
	virtual BNE_REFITEM_STATE	GetItemState(BNC_ReferenceItemEx* pItem);



	
	

//////////////////////////////////////////////////////////////////////////////////////////////////////////
protected :
	// 부모 view 반환
	virtual BNC_RefListViewEx* GetParentView(void) = 0;


	// 특정 아이템만 다시 그림
	virtual void OnRedrawItem(BNC_ReferenceItemEx* pItem, BNE_REFITEM_STATE state) = 0;
	

	// 마우스 명령 아이템 다시 그리기 (DrawMouseActionItem 내부 호출)
	virtual void OnDrawMouseItem(CDC* pDC, CDC* pItemDC, CDC* pResDC, BNC_ReferenceItemEx *pItem) = 0;


	// 클라이언트 좌표를 입력받아서 아이템 찾기 (UpdateMouseAction 내부 호출)
	// 아이템 좌표로 변환된 결과와 찾은 아이템 반환
	virtual bool OnFindItem(_Ret_ CPoint &ptClientToItem, _Ret_ BNC_ReferenceItemEx** ppOnFindItem) = 0;



	// 마우스 조작으로 이벤트 발생
	virtual void OnUpdateEvent(BNE_MOUSEACTION action, BNC_ReferenceItemEx *pEventItem) = 0;


public :
	// 선택 아이템 변경
	void	SetSelectItem(BNC_ReferenceItemEx* pItem);


public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnDestroy();
};

