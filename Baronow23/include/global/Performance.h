#pragma once

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
class BN23_CLASS Performance final
{
public:
	explicit Performance();
	~Performance();

	bool operator == (const Performance &rhs);
	bool operator != (const Performance &rhs);
	bool operator <	 (const Performance &rhs);
	bool operator <= (const Performance &rhs);
	bool operator >  (const Performance &rhs);
	bool operator >= (const Performance &rhs);
	

public:
	LARGE_INTEGER m_PercFreq;		// pc 클럭확인
	LARGE_INTEGER m_ClockStart;		// Start()때의 클럭
	LARGE_INTEGER m_ClockCheck;		// Start() ~ CheckElapse() 까지의 클럭
	LARGE_INTEGER m_ClockCall;		// lfPassSec를 초과한 CheckElapse부터 다음 CheckElapse까지의 클럭
	LARGE_INTEGER m_ClockPass;

	double	m_lfElapseTime;			// Start() ~ CheckElapse() 까지의 시간(ms)
	double	m_lfElapseCall;			// Start또는 CheckElapse부터 다음 CheckElapse까지의 시간(ms)
	double	m_lfPassSec;			// CheckElapse()를 호출한 시간이 설정 시간보다 적으면 false 반환

	UINT	m_uiElapseSecCount;		// 진행카운트(1초)
	UINT	m_uiElapseHalfSecCount;	// 진행카운트(0.5초)

	// FPS
	double	m_lfCheckCount;			// CheckElapse() 호출 횟수
	double	m_lfTotalFPS;			// CheckElapse() 호출 FPS
	double	m_lf500msAgoElapseSum;	// 최근 0.5초 동안의 lfElapseCall 합
	double	m_lf500msAgoFPS;		// lf500msAgoElapseSum을 FPS 변환
	double	m_lf500msAgoCount;		// 최근 0.5초 동안의 CheckElapse() 호출 카운트


public:
	void Reset(void);
	bool Check(void);
};
//////////////////////////////////////////////////////////////////////////////////////////
};