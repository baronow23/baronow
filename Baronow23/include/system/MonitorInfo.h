#pragma once

namespace baro {
//---------------------------------------------------------------------------------------
class BN23_CLASS MonitorInfo
{
public:
	MonitorInfo();
	MonitorInfo(const MonitorInfo &rhs);
	~MonitorInfo();

public :
	// 모니터 전체, 작업 영역
	vector<CRect>	m_vArea;
	vector<CRect>	m_vWork;

	// 주모니터 영역
	int		m_idxPrimary;	// 주모니터 인덱스 (m_vArea, m_vWork)
	CRect	m_rcPriArea;
	CRect	m_rcPriWork;

	// 사용자모니터를 모두 포함하는 경계
	// ex) 1920x1080 해상도 모니터가 수평으로 나란히 듀얼 구성되어 있다면 3840x1080 경계
	CRect	m_rcBoundary;	

	// 모니터들의 가장 큰 영역
	// ex) 모니터1(1920x1080) 모니터2(1080x1920) -> 1920x1920
	CSize	m_szMax;	

public :
	// 정보 초기화 디스플레이 상태 변경시 호출
	void Reset(LPRECT rcTarget = nullptr);

	// 전체 모니터 영역안에 rect가 포함되었는지 부위별로 체크
	void IsRectInMonitorArea(CRect rect, bool &bLeft, bool &bTop, bool &bRight, bool &bBottom);
	void IsRectInMonitorAreaEx(CRect rect, bool &bLT, bool &bRT, bool &bRB, bool &bLB);


#ifdef _DEBUG
	void Print(void);
#endif
};
//---------------------------------------------------------------------------------------
};