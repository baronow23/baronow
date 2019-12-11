#pragma once


class BN25_TYPE BNC_ReferenceItem : public baro::CheckPointer
{
	friend class BNC_BaseRefItemControl;
	friend class BNC_RefListControl;
	friend class BNC_RefTreeControl;
	friend class BNC_DummyListControl;
	

public:
	BNC_ReferenceItem(void);
	BNC_ReferenceItem(UINT uiItemHeight, UINT iSortCount, UINT iRectCount);
	BNC_ReferenceItem(const BNC_ReferenceItem &rhs);
	BNC_ReferenceItem& operator = (const BNC_ReferenceItem &rhs);
	virtual  ~BNC_ReferenceItem();


private:
	static UINT s_uiCreateCount;
	static UINT s_uiDestroyCount;
	

public:
	static UINT	GetCreateCount(void);
	static UINT	GetAliveCount(void);


private :
	// List, Tree 컨트롤에서 삽입할 때 지정함
	CString		m_strKey;	
	CString		m_strPKey;
	const void*	m_pRefData;			// 참조 데이터(사용자 지정)


private :
	UINT		m_uiSequence;
	int			m_iVisibleIndex;	// 화면에 보여지는 index (상위 부모에서 갱신)
	bool		m_bEnable;


	UINT		m_uiSortCount;
	UINT		m_uiRectCount;
	std::vector<CString*>		m_vpStrSort;
	std::vector<BNC_SyncRect*>	m_vpSyncRect;
	

	// Top, Bottom은 컨트롤에서 업데이트하며 스크롤링된 컨트롤 좌표임
	UINT		m_uiItemHeight;		// 아이템 높이
	UINT		m_uiItemTop;		// top (컨트롤 좌표)
	UINT		m_uiItemBottom;		// bottom (컨트롤 좌표)



public :
	//////////////////////////////////////////////////////
	// 가변 텍스트 정보
	//////////////////////////////////////////////////////
	bool		m_bUseVarText;		// 사용여부
	int			m_iVarOffset;		// 가변 텍스트가 출력될 수 있는 넓이 정의 ( 클라이언트 가로크기 - m_iVarOffset)
	CString		m_strVarText;		// 가변 높이에 사용할 텍스트 
	int			m_iVarTextSpacing;	// 줄바꿈 텍스트 사이 여백
	std::vector<CString*>	m_vpVarTextLine;	// 줄바꿈 적용된 텍스트(m_strVarText 분리)
	


public :
	BNE_MOUSEACTION		m_MouseAction;
	CPoint				m_ptMouse;				// 아이템 로컬 좌표
	int					m_iMouseRectIdx;		// ptMouse가 해당하는 Rect 인덱스 (-1이면 해당없음)

	BNE_MOUSEACTION		m_MouseActionOld;
	CPoint				m_ptMouseOld;		
	int					m_iMouseRectIdxOld;


	// BNC_ReferenceItem의 사용자 지정 확장 포인터
	void*				m_pOption;
	void*				m_pTemplate;


	// 사용자 지정값
	DWORD				m_dwFlags;


private :
	// 소멸자와 operator(=)외에서 호출 금지
	void	Clear(void);
	

//귀찬..
public :
	bool	SetEnable(bool bEnable);
	bool	SetSyncRectEnable(UINT index, bool bEnable);


public :
	bool			IsEnable(void) const;
	const void*		GetReferenceData(void) const;
	void*			GetOption(void) const;
	void*			GetTemplate(void) const;

	UINT			GetSequenceNumber(void) const;
	int				GetVisibleIndex(void) const;
	UINT			GetSortStringCount(void) const;
	UINT			GetSyncRectCount(void) const;
	const CString*	GetItemKey(void) const;
	const CString*	GetItemPKey(void) const;


	// 생성자에서 지정한 숫자까지만 설정 가능
	bool					SetSortString(UINT index, CString str);
	bool					SetSyncRect(UINT index, BNC_SyncRect& rect);
	bool					ModifySyncRect(UINT index, CRect &rect);
	bool					ModifySyncRect(UINT index, CRect &rect, CPoint &ptOffset);

	const CString*			GetSortString(UINT index) const;
	const CRect*			GetSyncRect(UINT index) const;
	const BNC_SyncRect*		GetSyncRectPtr(UINT index) const;
	bool					SetSyncRectCursor(UINT index) const;

	void	SetItemPos(UINT uiTop);
	UINT	GetItemHeight(void) const;
	UINT	GetItemTop(void) const;
	UINT	GetItemBottom(void) const;

	
	// ptItem	: 아이템 로컬 좌표
	// return	: 이전 action과 RectIdx가 다르면 true
	bool	UpdateMouseAction(BNE_MOUSEACTION action, const CPoint &ptItem);
	


	// Sync Rect 업데이트
	void	UpdateSyncRect(int iItemWidth) const;


	// Var Text 업데이트
	void	ClearVarTextLine(void);
	void	PushVarText(LPCTSTR lpszNextLine);


	BNE_MOUSEACTION	GetMouseAction(void) const;
	BNE_MOUSEACTION	GetMouseActionOld(void) const;
	int				GetMouseRectIndex(void) const;
	int				GetMouseRectIndexOld(void) const;
};
