#pragma once

struct BN25_TYPE BNS_TextInfo
{
public :
	BNS_TextInfo();
	~BNS_TextInfo();
	void Draw(CDC* pMemDC, UINT iState, int iOffset);
	void Draw(CDC* pMemDC, UINT iState, int iOffset, BNS_TextInfo *pTxtStyle);


	BNS_TextInfo(const BNS_TextInfo& rhs);
	BNS_TextInfo& operator=(const BNS_TextInfo& rhs);


public :
	// ���ҽ�
	CFont*		pFontPtr;
	CString		str;
	COLORREF	pColor[4];


	// �ɼ�
	TCHAR		cHotKey;


	// ��� ��ġ
	CPoint		draw;
};

