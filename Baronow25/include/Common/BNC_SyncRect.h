#pragma once


class BN25_TYPE BNC_SyncRect : public baro::CheckPointer
{
	friend class BNC_ReferenceItem;
	friend class BNC_ReferenceItemEx;

private:
	static UINT s_uiCreateCount;
	static UINT s_uiDestroyCount;

public:
	static UINT	GetCreateCount(void);
	static UINT	GetAliveCount(void);


public:
	BNC_SyncRect(void);
	virtual ~BNC_SyncRect();
	BNC_SyncRect(const BNC_SyncRect &rhs);
	BNC_SyncRect& operator = (const BNC_SyncRect &rhs);


public :
	void	SetRect(CRect rect			= CRect(0, 0, 0, 0),
					DWORD dwSyncPoint	= BND_FIXPOINT_DEFAULT,
					CPoint ptOffset		= CPoint(0, 0),
					CSize szTarget		= CSize(0, 0),
					bool bUpdate		= false);
	
	void	SetRect(BNC_SyncRect &rect);
	void	ModifyRect(const CRect &rect);
	void	ModifyRect(const CRect &rect, const CPoint &ptOffset);

	const CRect*	GetSyncRect(void) const;



public:
	// CRect(0, 0, sz.cx, sz.cy)에서
	// rect에 ptOffset, dwFixPoint가 적용된 rcSync 업데이트
	void	Update(CSize &szTarget, bool bForce = false);


	// CRect(0, 0, sz.cx, sz.cy)범위안에 있는 pt가 m_rcSync에 포함되는지 여부
	bool	PtInSyncRect(CSize &sz, CPoint &pt);



	//  마우스 트레킹 무시
	void	SetEnable(bool bEnable);
	bool	IsEnable(void) const;
	bool	IsInit(void) const;
	

	// SetRect이후 offset 변경
	void	ModifyOffset(CPoint ptOffset);


	// Rect 강제 조정
	void	SetForceRect(CRect &rect);

	
	// 주어진 depth에 따라 m_rect초기 위치 변경
	//void	ApplyDepth(UINT uiDepth);

	

public :
	HCURSOR m_hCursor;		// default hand, child는 해당 없음


private :
	bool	m_bInit;
	bool	m_bEnable;
	CRect	m_rect;
	CPoint	m_ptOffset;
	DWORD	m_dwSyncPoint;

	CSize	m_szUpdate;
	CRect	m_rcSync;


	
		

	// 옵션 (초기 설정 좌표에서 가로축으로 이동시킬 값) : 트리등에서 depth에 따라 이동처리
	//UINT	m_uiDepthMul;	
	//UINT	m_uiDefaultDepthBlank;
	
	

//2017.03.09
////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector<CRect>	m_vChildRect;
	std::vector<UINT>	m_vChildRef;
	
public :
	UINT	GetChildRectCount(void);
	void	ResetChildRect(std::vector<CRect> &vChildRect, std::vector<UINT> vChildRef);
	int		PtInChild(CPoint &pt);
};

