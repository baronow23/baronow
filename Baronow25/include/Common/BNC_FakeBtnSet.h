#pragma once

class BNC_BaseClient;
class BN25_TYPE BNC_FakeBtnSet
{
public:
	BNC_FakeBtnSet();
	~BNC_FakeBtnSet();
	
private :
	BNC_BaseClient	*m_pTargetClient;
	vector<shared_ptr<BNC_FakeRect>> m_vpRect;


public :
	void	Initialize(BNC_BaseClient *pTarget,
					   UINT iUsingCount,
					   FakeRectDraw callbackDraw,
					   FakeRectCommand callbackCommand);
	bool	InitButton(UINT idx, CSize size, bool bUsingHandCursor, bool bUsingEllipseRect);


public :
	void	Move(UINT idx, CPoint ptLT, bool bShow);
	void	MoveEx(UINT idx, CPoint ptLT, bool bShow, int iUpdateID);
	void	Show(UINT idx, bool bShow);
	CRect	GetRect(UINT idx);
	void	DrawAll(Graphics &gdi, CDC* pMemDC, CDC* pResDC, bool bFocusLast);
	void	Draw(UINT idx, Graphics &gdi, CDC* pMemDC, CDC* pResDC);


	// 각 rect가 소유한 id 오름차순으로 정렬
	void	SortFromID(void);


public :
	// 마우스 이벤트, true 반환시 대상 윈도우 프로시저 처리하지 말 것
	bool	MouseMove(UINT uiFlags, CPoint point);
	bool	MouseLBtnDown(UINT uiFlags, CPoint point);
	bool	MouseLBtnUp(UINT uiFlags, CPoint point);
	void	MouseReset(UINT idx);
	void	MouseReset(void);
};

