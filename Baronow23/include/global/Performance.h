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
	LARGE_INTEGER m_PercFreq;		// pc Ŭ��Ȯ��
	LARGE_INTEGER m_ClockStart;		// Start()���� Ŭ��
	LARGE_INTEGER m_ClockCheck;		// Start() ~ CheckElapse() ������ Ŭ��
	LARGE_INTEGER m_ClockCall;		// lfPassSec�� �ʰ��� CheckElapse���� ���� CheckElapse������ Ŭ��
	LARGE_INTEGER m_ClockPass;

	double	m_lfElapseTime;			// Start() ~ CheckElapse() ������ �ð�(ms)
	double	m_lfElapseCall;			// Start�Ǵ� CheckElapse���� ���� CheckElapse������ �ð�(ms)
	double	m_lfPassSec;			// CheckElapse()�� ȣ���� �ð��� ���� �ð����� ������ false ��ȯ

	UINT	m_uiElapseSecCount;		// ����ī��Ʈ(1��)
	UINT	m_uiElapseHalfSecCount;	// ����ī��Ʈ(0.5��)

	// FPS
	double	m_lfCheckCount;			// CheckElapse() ȣ�� Ƚ��
	double	m_lfTotalFPS;			// CheckElapse() ȣ�� FPS
	double	m_lf500msAgoElapseSum;	// �ֱ� 0.5�� ������ lfElapseCall ��
	double	m_lf500msAgoFPS;		// lf500msAgoElapseSum�� FPS ��ȯ
	double	m_lf500msAgoCount;		// �ֱ� 0.5�� ������ CheckElapse() ȣ�� ī��Ʈ


public:
	void Reset(void);
	bool Check(void);
};
//////////////////////////////////////////////////////////////////////////////////////////
};