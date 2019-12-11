#pragma once

#define BND_FAKERECT_OPT_SHOW	0x10000000	
#define BND_FAKERECT_OPT_RGN	0x01000000

class BNC_FakeRect;
using FakeRectDraw = std::function<void(Graphics&, CDC*, CDC*, BNC_FakeRect&)>;
using FakeRectCommand = std::function<void(int, int, int, bool)>;	// id, command, captureupdate(-1 해제, 0 변동없음, 1설정), bExecute(down-up 완료)

class BN25_TYPE BNC_FakeRect : public BNC_Instance<BNC_FakeRect>
{
public:
	BNC_FakeRect(HWND hParent, FakeRectDraw	callbackDraw, FakeRectCommand callbackCommand);
	~BNC_FakeRect();

	BNC_FakeRect(const BNC_FakeRect& rhs) = delete;
	BNC_FakeRect& operator = (const BNC_FakeRect& rhs) = delete;
	

private :
	HWND			m_hParent;
	FakeRectDraw	m_callbackDraw;
	FakeRectCommand m_callbackCommand;

	int		m_id;
	int		m_iCommand;	// BNE_BTN_STATE 매핑
	DWORD	m_dwState;
	bool	m_bEntryCapture;


public :
	CPoint	m_ptLT;
	CSize	m_size;
	CRect	m_rect;
	CRgn	m_rgn;
	HCURSOR m_hCursor;


public :
	void Initialize(int id, CPoint ptLT, CSize size, HCURSOR hCursor, DWORD dwState);
	void Move(CPoint ptLT, bool bShow);
	void MoveEx(CPoint ptLT, bool bShow, int iUpdateID);
	void Show(bool bShow);
	void Draw(Graphics &gdi, CDC* pMemDC, CDC* pResDC);


private :
	bool	CheckEntry(CPoint &point);
	bool	UpdateCommand(int iCommand, int iCaptureUpdate, bool bExecute);
	

public :
	int		GetID(void) const;
	int		GetCommand(void) const;
	DWORD	GetState(void) const;
	

public :
	bool	MouseMove(UINT uiFlags, CPoint point);
	bool	MouseLBtnDown(UINT uiFlags, CPoint point);
	bool	MouseLBtnUp(UINT uiFlags, CPoint point);
	void	MouseReset(void);
};

