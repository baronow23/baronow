#pragma once

enum BNE_POPUPITEM_TYPE
{
	BNE_PI_SEPARATOR,	// ���м�
	BNE_PI_POPUP,		// ���� �޴� ������ �޴�
	BNE_PI_ITEM,		// �Ϲ� ������
	BNE_PI_ITEM_CHK,	// üũ ������
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
	CRect				m_rcItem;			// ��� ����
	UINT				m_piSection[4];		// �� ���� ���� ( 0:�����̹���, 1:����, 2:����Ű, 3:�����̹���);


	// �� ���� ����
	BNS_TextInfo*		m_pLeftText;
	BNS_TextInfo*		m_pRightText;
	BNS_ImageInfo*		m_pLeftImage;
	BNS_ImageInfo*		m_pLeftTextImage;
	BNS_ImageInfo*		m_pRightImage;


	bool	m_bEnable;
	bool	m_bCheck;
	TCHAR	m_cHotKey;


public:
	// ������ ���ҽ� ����
	// �ؽ�Ʈ �� �̹��� ũ�Ⱑ iHeight���� ũ�� ����
	bool	SetImage(UINT iSectionIndex, BNS_ImageInfo* pImageInfo);
	bool	SetText(UINT iSectionIndex, BNS_TextInfo* ppTextInfo, CDC* pDC, bool bCopyText = true);


	// ���� �޴� (�������� ������ �޴� �־���, ������ �����ۿ��� ó��)
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

