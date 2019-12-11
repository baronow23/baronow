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
	// CRect(0, 0, sz.cx, sz.cy)����
	// rect�� ptOffset, dwFixPoint�� ����� rcSync ������Ʈ
	void	Update(CSize &szTarget, bool bForce = false);


	// CRect(0, 0, sz.cx, sz.cy)�����ȿ� �ִ� pt�� m_rcSync�� ���ԵǴ��� ����
	bool	PtInSyncRect(CSize &sz, CPoint &pt);



	//  ���콺 Ʈ��ŷ ����
	void	SetEnable(bool bEnable);
	bool	IsEnable(void) const;
	bool	IsInit(void) const;
	

	// SetRect���� offset ����
	void	ModifyOffset(CPoint ptOffset);


	// Rect ���� ����
	void	SetForceRect(CRect &rect);

	
	// �־��� depth�� ���� m_rect�ʱ� ��ġ ����
	//void	ApplyDepth(UINT uiDepth);

	

public :
	HCURSOR m_hCursor;		// default hand, child�� �ش� ����


private :
	bool	m_bInit;
	bool	m_bEnable;
	CRect	m_rect;
	CPoint	m_ptOffset;
	DWORD	m_dwSyncPoint;

	CSize	m_szUpdate;
	CRect	m_rcSync;


	
		

	// �ɼ� (�ʱ� ���� ��ǥ���� ���������� �̵���ų ��) : Ʈ����� depth�� ���� �̵�ó��
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

