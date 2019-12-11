#pragma once


// BNC_BaseLayered 대화 상자입니다.
#include <mutex>
class BN25_TYPE BNC_BaseLayered : public CDialog
{
	DECLARE_DYNAMIC(BNC_BaseLayered)

public:
	BNC_BaseLayered(void);
	virtual ~BNC_BaseLayered();


private :
	HWND m_hInitParent;
	baro::Performance m_CheckBegin;
	baro::Performance m_CheckDelay;

	DWORD			m_dwInitStyle;
	DWORD			m_dwInitStyleEx;


private :
	recursive_mutex		m_mutex;
	CBitmap				m_CacheBitmap;
	CSize				m_szSource;


protected :
	CPoint				m_ptLayerd;
	CSize				m_szLayerd;
	byte				m_btOpacity;


protected :
	UINT	m_uiTimerID;
	UINT	m_uiTimerDelay;
	DWORD	m_dwBlendFlags;


private :
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);

	
protected:
	virtual BOOL OnInitDialog();


private:
	// return true : lfCallDelay 업데이트
	virtual bool OnAnimation(double lfProgress, double lfCallDelay) = 0;


public :
	bool	create(CWnd *pParent, bool bTransparent = false);
	void	StopHide(void);


public :
	// 신규 이미지 사용
	bool	UpdateLayerImage(_In_		Gdiplus::Image *pImage,
							 _In_opt_	byte	*pbtOpacity = nullptr,		// 투명도 지정 (0~255)
							 _In_opt_	CPoint	*pptLayred	= nullptr,		// layered 시킬 pImage의 left-top
							 _In_opt_	CSize	*pszLayred	= nullptr,		// layered 시킬 크기
							 _In_opt_	CSize	*pszStretch	= nullptr,		// 리사이징 시킬 크기 (pszLayerd 필수)
							 _In_opt_	CPoint	*pptWindow	= nullptr);		// 변경시킬 윈도우 left-top


	// 신규 비트맵 사용
	bool	UpdateLayerBitmap(_In_		CBitmap *pBitmap,
							  _In_		CSize	szSrc,
							  _In_opt_	byte	*pbtOpacity = nullptr,
							  _In_opt_	CPoint	*pptLayred	= nullptr,
							  _In_opt_	CSize	*pszLayred	= nullptr,
							  _In_opt_	CPoint	*pptWindow	= nullptr);


	// 이전 cache로 업데이트
	bool	UpdateLayer(_In_opt_	byte	*pbtOpacity = nullptr,		// 투명도 지정 (0~255)
						_In_opt_	CPoint	*pptLayred	= nullptr,		// layered 시킬 pImage의 left-top
						_In_opt_	CSize	*pszLayred	= nullptr,		// layered 시킬 크기
						_In_opt_	CPoint	*pptWindow	= nullptr);		// 변경시킬 윈도우 left-top


private :
	bool	CommitLayer(_In_	 byte btOpacity,
						_In_	 CPoint ptLayred,
						_In_	 CSize szLayred,
						_In_opt_ CPoint *pptWindow);

private :
	virtual void OnCommitLayer(CDC* pDC, byte btOpacity, CPoint ptLT, CSize sz);
	virtual void OnStopHide(void);

			
private :
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
