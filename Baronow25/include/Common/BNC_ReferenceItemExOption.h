#pragma once


#define BND_REFITEMEX_MAXWIDTH		1920	// blank가 포함된 최대 넓이
#define BND_REFITEMEX_MINWIDTH		50		// blank가 포함된 최소 넓이 (이하는 모두  default로 채움)
#define BND_REFITEMEX_IDXSTEP		10
#define BND_REFITEMEX_IDXCOUNT	BND_REFITEMEX_MAXWIDTH / BND_REFITEMEX_IDXSTEP


// IDXSTEP 문제로 끝부분 잘림 방지
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
	// InitializeString 업데이트
	bool	m_bInitialize;


private :
	USHORT	m_piVarHeight[BND_REFITEMEX_IDXCOUNT];
	

		
	// UpdateStringPos 업데이트
	int						m_iCheckWidth;		// 마지막 UpdateStringPos 갱신 넓이
	CSize					m_szLastUpdate;		// cx : 가장 넓은 텍스트 넓이, cy : 총 출력가능한 높이
	std::vector<CString>	m_vStrSource;		// 원본 문자열에서 줄바꿈 추출후 분리
	std::vector<short>		m_vRefLineIdx;		// m_viLineCount, m_viLineTop 인덱스의 위치값의 문자열 m_vStrSource 위치
	std::vector<int>		m_viLineStartPos;	// m_vSrcSourc를 참조하고 있는  문자열의 시작 위치
	std::vector<int>		m_viLineCount;		// 각 라인마다 출력할 수 있는 m_strVarText의 수
	std::vector<int>		m_viLineTop;		// 각 라인의 출력 top 위치 (0번 인덱스의 높이는 0임)



#ifdef _UNICODE
public :
	std::vector<BYTE>	m_vCharSize;	// 개별 문자 크기
	std::vector<int>	m_vCharPos;		// m_vCharSize에서 m_vStrSource 라인의 마지막 문자 위치 ( 크기 == m_vStrSource.size())

	bool				m_bUseSingleChar;
	int					m_iCharHeight;
#endif



public:
	// 초기 사용자 설정
	UINT		m_uiDefaultHeight;	// 고정 기본 높이 (최종 아이템 높이 = m_uiDefaultHeight + m_piVarHeight)
	CString		m_strVarText;		// 가변 텍스트
	CFont*		m_pFontPtr;			// 가변 텍스트 출력에 적용할 폰트
	UINT		m_iHorBlank;		// 클라이언트 가로축 여백
	UINT		m_iSpacing;			// 줄바꿈 발생시 줄간격(px)
	UINT		m_iBlankHeight;		// 공백문자일 때 적용할 높이
	
	
public :
	// 초기 한번만 호출
	void	InitializeString(CDC* pDC);


	// pDC의 iWidth에 맞는 텍스트 갱신
	// text 출력가능한 크기
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
	CRect	m_rcTextArea;		// 드래그로 사용할 텍스트 영역
	CPoint	m_ptTextOffset;		// 처음 텍스트 시작 위치

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

