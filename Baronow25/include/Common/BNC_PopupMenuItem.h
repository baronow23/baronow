#pragma once

enum BNE_POPUPITEM_TYPE
{
	BNE_PI_SEPARATOR,	// 구분선
	BNE_PI_POPUP,		// 하위 메뉴 가지는 메뉴
	BNE_PI_ITEM,		// 일반 아이템
	BNE_PI_ITEM_CHK,	// 체크 아이템
};


class BNC_PopupMenu;
class BN25_TYPE BNC_PopupMenuItem
{
	friend class BNC_PopupMenu;
public:
	BNC_PopupMenuItem(UINT uiItemID,
					  BNE_POPUPITEM_TYPE type,
					  UINT	iLeft,
					  UINT	iTop,
					  UINT	iHeight		= 25,
					  UINT	iSection1	= 30,
					  UINT	iSection2	= 150,
					  UINT	iSection3	= 50,
					  UINT	iSection4	= 20,
					  TCHAR cHotKey		= _T('\0'));

	~BNC_PopupMenuItem();


private:
	UINT				m_uiItemID;
	BNE_POPUPITEM_TYPE	m_type;
	BNC_PopupMenu		*m_pChildMenu;
	CRect				m_rcItem;			// 출력 영역
	UINT				m_piSection[4];		// 각 영역 넓이 ( 0:좌측이미지, 1:내용, 2:단축키, 3:우측이미지);


	// 각 섹션 정보
	BNS_TextInfo*		m_pLeftText;
	BNS_TextInfo*		m_pRightText;
	BNS_ImageInfo*		m_pLeftImage;
	BNS_ImageInfo*		m_pLeftTextImage;
	BNS_ImageInfo*		m_pRightImage;


	bool	m_bEnable;
	bool	m_bCheck;
	TCHAR	m_cHotKey;


public:
	// 아이템 리소스 지정
	// 텍스트 및 이미지 크기가 iHeight보다 크면 실패
	bool	SetImage(UINT iSectionIndex, BNS_ImageInfo* pImageInfo);
	bool	SetText(UINT iSectionIndex, BNS_TextInfo* ppTextInfo, CDC* pDC, bool bCopyText = true);


	// 하위 메뉴 (동적으로 생성한 메뉴 넣어줌, 삭제는 아이템에서 처리)
	void			SetChildMenu(BNC_PopupMenu** ppChild);
	BNC_PopupMenu*	GetChildMenu(void);


	UINT	GetID(void);

public:
	BNE_POPUPITEM_TYPE	GetType(void);
	CRect				GetArea(void);
	bool				IsEnable(void);
	bool				IsCheck(void);
	void				Draw(CDC* pMemDC, Gdiplus::Graphics *pGraphics, UINT iState, int iOffset, BNS_TextInfo *pLeftTxtStyle);


	BNS_TextInfo*		GetLeftTextPtr(void);
	BNS_TextInfo*		GetRightTextPtr(void);
	BNS_ImageInfo*		GetLeftImagePtr(void);
	BNS_ImageInfo*		GetLeftTextImagePtr(void);
	BNS_ImageInfo*		GetRightImagePtr(void);
};

