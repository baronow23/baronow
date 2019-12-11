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
	// ����� ��ü, �۾� ����
	vector<CRect>	m_vArea;
	vector<CRect>	m_vWork;

	// �ָ���� ����
	int		m_idxPrimary;	// �ָ���� �ε��� (m_vArea, m_vWork)
	CRect	m_rcPriArea;
	CRect	m_rcPriWork;

	// ����ڸ���͸� ��� �����ϴ� ���
	// ex) 1920x1080 �ػ� ����Ͱ� �������� ������ ��� �����Ǿ� �ִٸ� 3840x1080 ���
	CRect	m_rcBoundary;	

	// ����͵��� ���� ū ����
	// ex) �����1(1920x1080) �����2(1080x1920) -> 1920x1920
	CSize	m_szMax;	

public :
	// ���� �ʱ�ȭ ���÷��� ���� ����� ȣ��
	void Reset(LPRECT rcTarget = nullptr);

	// ��ü ����� �����ȿ� rect�� ���ԵǾ����� �������� üũ
	void IsRectInMonitorArea(CRect rect, bool &bLeft, bool &bTop, bool &bRight, bool &bBottom);
	void IsRectInMonitorAreaEx(CRect rect, bool &bLT, bool &bRT, bool &bRB, bool &bLB);


#ifdef _DEBUG
	void Print(void);
#endif
};
//---------------------------------------------------------------------------------------
};