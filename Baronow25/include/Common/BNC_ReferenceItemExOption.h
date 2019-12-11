#pragma once


#define BND_REFITEMEX_MAXWIDTH		1920	// blank�� ���Ե� �ִ� ����
#define BND_REFITEMEX_MINWIDTH		50		// blank�� ���Ե� �ּ� ���� (���ϴ� ���  default�� ä��)
#define BND_REFITEMEX_IDXSTEP		10
#define BND_REFITEMEX_IDXCOUNT	BND_REFITEMEX_MAXWIDTH / BND_REFITEMEX_IDXSTEP


// IDXSTEP ������ ���κ� �߸� ����
#define BND_REFITEMEX_MAXWIDTH_EX	(BND_REFITEMEX_MAXWIDTH - BND_REFITEMEX_IDXSTEP)


class BN25_TYPE BNC_ReferenceItemExOptionLine : public baro::CheckPointer
{
private:
	static UINT s_uiCreateCount;
	static UINT s_uiDestroyCount;

public:
	static UINT	GetCreateCount(void);
	static UINT	GetAliveCount(void);


public :
	BNC_ReferenceItemExOptionLine(void);
	virtual ~BNC_ReferenceItemExOptionLine(void);
	BNC_ReferenceItemExOptionLine(const BNC_ReferenceItemExOptionLine &rhs);
	BNC_ReferenceItemExOptionLine& operator=(const BNC_ReferenceItemExOptionLine &rhs);
	void Reset(void);
	void Add(CString str, bool bLink, bool bFocus, bool bDrag, UINT idxLink);

	bool bComposite;
	int iLineTop;
	CString strLine;

	std::vector<CString>	vStr;
	std::vector<bool>		vbLink;
	std::vector<bool>		vbFocus;
	std::vector<bool>		vbDrag;
	std::vector<UINT>		viLinkIdx;
};

class BN25_TYPE BNC_ReferenceItemExOptionDrag
{

public :
	BNC_ReferenceItemExOptionDrag(void);
	~BNC_ReferenceItemExOptionDrag(void);
	BNC_ReferenceItemExOptionDrag(const BNC_ReferenceItemExOptionDrag &rhs);
	BNC_ReferenceItemExOptionDrag& operator=(const BNC_ReferenceItemExOptionDrag &rhs);
	bool operator==(const BNC_ReferenceItemExOptionDrag &rhs) const;
	void Reset(void);
	bool IsValid(void);
	bool IsSelect(void);
	
	int		iBeginLine;
	int		iEndLine;
	int		iBeginChar;
	int		iEndChar;
};


class BN25_TYPE BNC_ReferenceItemExOption : public baro::CheckPointer
{
	friend class BNC_RefListControlEx;
	friend class BNC_ReferenceItemEx;


public:
	BNC_ReferenceItemExOption(void);
	BNC_ReferenceItemExOption(const BNC_ReferenceItemExOption &rhs);
	virtual ~BNC_ReferenceItemExOption(void);
	BNC_ReferenceItemExOption& operator = (const BNC_ReferenceItemExOption &rhs);


private:
	static UINT s_uiCreateCount;
	static UINT s_uiDestroyCount;
	

public:
	static UINT	GetCreateCount(void);
	static UINT	GetAliveCount(void);

	
	
public :
	// InitializeString ������Ʈ
	bool	m_bInitialize;


private :
	USHORT	m_piVarHeight[BND_REFITEMEX_IDXCOUNT];
	

		
	// UpdateStringPos ������Ʈ
	int						m_iCheckWidth;		// ������ UpdateStringPos ���� ����
	CSize					m_szLastUpdate;		// cx : ���� ���� �ؽ�Ʈ ����, cy : �� ��°����� ����
	std::vector<CString>	m_vStrSource;		// ���� ���ڿ����� �ٹٲ� ������ �и�
	std::vector<short>		m_vRefLineIdx;		// m_viLineCount, m_viLineTop �ε����� ��ġ���� ���ڿ� m_vStrSource ��ġ
	std::vector<int>		m_viLineStartPos;	// m_vSrcSourc�� �����ϰ� �ִ�  ���ڿ��� ���� ��ġ
	std::vector<int>		m_viLineCount;		// �� ���θ��� ����� �� �ִ� m_strVarText�� ��
	std::vector<int>		m_viLineTop;		// �� ������ ��� top ��ġ (0�� �ε����� ���̴� 0��)



#ifdef _UNICODE
public :
	std::vector<BYTE>	m_vCharSize;	// ���� ���� ũ��
	std::vector<int>	m_vCharPos;		// m_vCharSize���� m_vStrSource ������ ������ ���� ��ġ ( ũ�� == m_vStrSource.size())

	bool				m_bUseSingleChar;
	int					m_iCharHeight;
#endif



public:
	// �ʱ� ����� ����
	UINT		m_uiDefaultHeight;	// ���� �⺻ ���� (���� ������ ���� = m_uiDefaultHeight + m_piVarHeight)
	CString		m_strVarText;		// ���� �ؽ�Ʈ
	CFont*		m_pFontPtr;			// ���� �ؽ�Ʈ ��¿� ������ ��Ʈ
	UINT		m_iHorBlank;		// Ŭ���̾�Ʈ ������ ����
	UINT		m_iSpacing;			// �ٹٲ� �߻��� �ٰ���(px)
	UINT		m_iBlankHeight;		// ���鹮���� �� ������ ����
	
	
public :
	// �ʱ� �ѹ��� ȣ��
	void	InitializeString(CDC* pDC);


	// pDC�� iWidth�� �´� �ؽ�Ʈ ����
	// text ��°����� ũ��
	CSize	UpdateStringPos(CDC* pDC, int iWidth);
	

	
public :
	bool	FindCharCut(CString str, TCHAR cFind, CString &strLeft, CString &strRight) const;
	CSize	GetLastUpdateSize(void) const;
	UINT	GetHeight(UINT iTargetWidth) const;
	UINT	GetIdxHeight(UINT index) const;
	UINT	GetLineCount(void) const;
	bool	GetLineInfo(UINT index, CString &strLine, int &iLineTop) const;
	int		GetLineTop(UINT index) const;


//2017.03.08
////////////////////////////////////////////////////////////////////////////////////////////////////////
public :
	bool m_bUsingLinkInfo;

public :
	bool	SplitSpace(_In_ const CString &strSrc, _Ret_ CString &strFirstSub, _Ret_ int &idxBeginEnd);
	bool	GetLineInfoEx(_In_ UINT idxLine, _Ret_ const BNC_ReferenceItemExOptionLine **ppLineInfo);
	UINT	GetLinkCount(void) const;
	CString GetLinkString(UINT idxLink) const;


private :	
	void InitializeLinkInfo(void);
	BNC_ReferenceItemExOptionLine	m_LineInfo;
	std::map<UINT, UINT>	m_mLinkRef;		// key:source line, value: ref index (m_vLinkLine, m_vptLinkPos)
	std::vector<UINT>		m_vLinkLine;	
	std::vector<CPoint>		m_vLinkPos;
	int						m_iFocusLink;
////////////////////////////////////////////////////////////////////////////////////////////////////////


//2017.08.02
#ifdef _UNICODE
public :
	bool	m_bUsingTextDrag;

private:
	CRect	m_rcTextArea;		// �巡�׷� ����� �ؽ�Ʈ ����
	CPoint	m_ptTextOffset;		// ó�� �ؽ�Ʈ ���� ��ġ

	BNC_ReferenceItemExOptionDrag	m_DragSource;
	BNC_ReferenceItemExOptionDrag	m_DragVisible;
	BNC_ReferenceItemExOptionDrag	m_DragEnter;
	
	
	bool	UpdateDragReference(void);
	bool	UpdateDragData(BNC_ReferenceItemExOptionDrag ret);
	bool	GetDragVisibleFromDragSource(int iSearchBegin, int iSrcLine, int iSrcChar, _Ret_ int &iVisibleLine, _Ret_ int &iVisibleChar);

	bool	OnDragAll(void);
	bool	OnDragCopy(void);
	bool	OnDragEnter(CPoint &ptItem, CSize &szItem, bool bDblClick);
	bool	OnDragMove(CPoint &ptItem, CSize &szItem);
	bool	OnDragLeave(void);
	void	GetDragPoint(_In_ CPoint ptLT, _In_ bool bDblClick, _Ret_ BNC_ReferenceItemExOptionDrag &ret);
	int		GetLineIndex(_In_ CPoint ptLT, _Ret_ bool &bEOL);
	bool	AddDragInfo(int idxLine, CString str, int insertBegin, int insertEnd,
						bool bLink, bool bFocus, UINT idxLink);
	void	SetTextArea(CRect rect, CPoint ptTxtOffset);
	
public :
	bool		IsSelectAll(void);
	bool		IsDragSelect(void);
	CString		GetDragString(void);
	bool		DragStringToClipboard(void);
#endif
};

