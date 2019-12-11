#pragma once


enum BNE_VERTICAL_INTERSECT
{
	// ■■
	// ----
	// □□
	// ----
	// □□
	BNE_VI_TOP,


	// □□
	// ----
	// ■■
	// ----
	// □□
	BNE_VI_CENTER,


	// □□
	// ----
	// □□
	// ----
	// ■■
	BNE_VI_BOTTOM,
};



#include "BNC_ReferenceItemExOption.h"
class BN25_TYPE BNC_ReferenceItemEx : public baro::CheckPointer
{
	friend class BNC_BaseRefItemControlEx;
	friend class BNC_RefListControlEx;
	friend class BNC_ReferenceItemEx;

	

public:
	BNC_ReferenceItemEx(void);
	BNC_ReferenceItemEx(UINT iSortCount, UINT iRectCount, BNC_ReferenceItemExOption* pOptPtr);
	BNC_ReferenceItemEx(const BNC_ReferenceItemEx &rhs);
	BNC_ReferenceItemEx& operator = (const BNC_ReferenceItemEx &rhs);
	virtual  ~BNC_ReferenceItemEx();


private:
	static UINT s_uiCreateCount;
	static UINT s_uiDestroyCount;
	

public:
	static UINT	GetCreateCount(void);
	static UINT	GetAliveCount(void);


private :
	// List, Tree 컨트롤에서 삽입할 때 지정함
	CString		m_strKey;			// List에서는 중복/공백 허용 (그룹 개념으로 사용)
	CString		m_strPKey;
	void*		m_pRefData;			// 참조 데이터(사용자 지정)


	// 확장 필드 (필수!!)
	BNC_ReferenceItemExOption*		m_pOptPtr;


private :
	UINT		m_uiSequence;
	int			m_iVisibleIndex;	// 화면에 보여지는 index (상위 부모에서 갱신)
	bool		m_bEnable;


	UINT		m_uiSortCount;
	UINT		m_uiRectCount;
	std::vector<CString*>		m_vpStrSort;
	std::vector<BNC_SyncRect*>	m_vpSyncRect;
	

	// Top, Bottom은 컨트롤에서 업데이트하며 스크롤링된 컨트롤 좌표임
	UINT	m_piItemTop[BND_REFITEMEX_IDXCOUNT];



public :
	BNE_MOUSEACTION		m_MouseAction;
	CPoint				m_ptMouse;				// 아이템 로컬 좌표
	CPoint				m_ptMouseRectIdx;		// ptMouse가 해당하는 Rect 인덱스 (-1이면 해당없음)


	BNE_MOUSEACTION		m_MouseActionOld;
	CPoint				m_ptMouseOld;		
	CPoint				m_ptMouseRectIdxOld;


	// 사용자 지정 플래그
	UINT	m_uiUserFlags;


	// drag 설정
	int		m_iTextRectIndex;
	CPoint	m_ptTextOffset;

	
private :
	// 소멸자와 operator(=)외에서 호출 금지
	void	Clear(void);


public:
	bool	SetEnable(bool bEnable);
	bool	SetSyncRectEnable(UINT index, bool bEnable);

	
public :
	UINT	TargetWidthToIndex(int iTargetWidth);


public :
	bool	IsEnable(void) const;
	void*	GetReferenceData(void) const;
	BNC_ReferenceItemExOption*	GetExOption(void) const;


	UINT			GetSequenceNumber(void) const;
	int				GetVisibleIndex(void) const;
	UINT			GetSortStringCount(void) const;
	UINT			GetSyncRectCount(void) const;
	const CString*	GetItemKey(void) const;
	const CString*	GetItemPKey(void) const;


	// 참조 옵션 설정
	void	SetOptionPtr(BNC_ReferenceItemExOption* pOptPtr);


	// 생성자에서 지정한 숫자까지만 설정 가능
	bool			SetSortString(UINT index, CString str);
	bool			SetSyncRect(UINT index, BNC_SyncRect& rect);
	bool			ModifySyncRect(UINT index, const CRect &rect);
	bool			ModifySyncRect(UINT index, const CRect &rect, const CPoint &ptOffset);
	const CString*	GetSortString(UINT index) const;
	const CRect*	GetSyncRect(UINT index) const;
	BNC_SyncRect*	GetSyncRectPtr(UINT index);
	bool			SetSyncRectCursor(UINT index) const;



	void	SetItemTop(UINT iTargetWidth, UINT uiTop);
	UINT	GetItemTop(UINT iTargetWidth) const;
	UINT	GetItemBottom(UINT iTargetWidth) const;
	UINT	GetItemHeight(UINT iTargetWidth) const;


	void	SetItemIdxTop(UINT idx, UINT uiTop);
	UINT	GetItemIdxTop(UINT idx) const;
	UINT	GetItemIdxBottom(UINT idx) const;
	UINT	GetItemIdxHeight(UINT idx) const;
	BNE_VERTICAL_INTERSECT	GetIntersect(UINT idx, int iScroll, int iVisibleHeight) const;

	
	// ptItem	: 아이템 로컬 좌표
	// return	: 이전 action과 RectIdx가 다르면 true
	bool	UpdateMouseAction(BNE_MOUSEACTION action, CPoint &ptItem);
	

	// Sync Rect 업데이트
	void	UpdateSyncRect(int iTargetWidth) const;
	

	BNE_MOUSEACTION	GetMouseAction(void) const;
	BNE_MOUSEACTION	GetMouseActionOld(void) const;
	int				GetMouseRectIndex(void) const;
	int				GetMouseRectIndexOld(void) const;
	CPoint			GetMouseRectIndexPoint(void) const;
	CPoint			GetMouseRectIndexPointOld(void) const;


	// 마우스 위치가 -1일 때의 기본 커서
	//void	SetDefaultCursor(CPoint ptItem);

	//2017.03.09
	////////////////////////////////////////////////////////////////////////////////////////////////////////

//private :
public :
	void	ResetLinkInfo(UINT idxSyncRect, std::vector<CRect> &vChildRect, std::vector<UINT> vChildRef);

public :
	UINT	GetLinkRectCount(UINT idxSyncRect);
	void	SetLinkFocus(int index);
	CString GetFocusLinkString(void) const;


	//2017.08.02
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	SetTextRect(int index, CPoint ptOffset);
	bool	UpdateTextOffset(CPoint ptOffset);
	int		DrawText(CDC* pItemDC, int iBaseLine, CSize szItem, int iVisibleHeight, CPoint ptLT, CFont *pLinkFont,
					 COLORREF clrTxtNormal, COLORREF clrLink, COLORREF clrLinkFocus,
					 COLORREF clrDragBk, COLORREF clrDragTxt, int iOffsetTop);

private :
	bool	UpdateTextRect(void) const;
	bool	OnDragEnter(CPoint &ptItem, CSize &szItem, bool bDblClick);
	bool	OnDragMove(CPoint &ptItem, CSize &szItem);
	bool	OnDragLeave(void);

public :
	bool	OnDragAll(void);
	bool	OnDragCopy(void);
};
