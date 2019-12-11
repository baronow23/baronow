#pragma once

namespace bapi 
{
	// ��� ����� �������� ã�Ƽ� ��ȯ
	// lprcBoundary �����ϸ� ���� ����͸� ����
	BN23_API(baro::MonitorInfo) GetMonitorInfo(LPRECT lprcBoundary = nullptr);
	

	// �ָ���� ���� ��ȯ
	BN23_API(CRect) GetPrimaryArea(void);
	BN23_API(CRect) GetPrimaryWork(void);


	// hwnd �Ǵ� lprcWindow�� ��ġ�ϰ� �ִ°��� �۾����� ��ȯ
	BN23_API(CRect) GetCurrentWorkArea(HWND hwnd);
	BN23_API(CRect) GetCurrentWorkArea(LPRECT lprcWindow);


	// hwnd �Ǵ� lprcWindow�� ��ġ�ϰ� �ִ°��� ����Ϳ��� ��ȯ
	BN23_API(CRect) GetCurrentMonitorArea(HWND hwnd);
	BN23_API(CRect) GetCurrentMonitorArea(LPRECT lprcWindow);

	
	// �ʱ�ȭ �� MonitorInfo�� m_szMax, m_rcBoundary�� ����
	// �ǽð� �����Ͱ� �ʟG�� �� ���
	BN23_API(CSize) GetMonitorResolution(void);		
	BN23_API(CSize) GetMonitorMaxResolution(void);


	// ������(hwnd) �Ǵ� ��������(lprcWindow)�� �����ִ� ����͵��� �ջ�� ���� ��ȯ (������� �̻� ����)
	// ex) �����1(1280*1024), �����2(1024*768)�̰� �����1,2�� �����ִٸ�  2304*1024ũ���� �����쿵�� ��ȯ
	BN23_API(CRect) GetMonitorExArea(HWND hwnd);		
	BN23_API(CRect) GetMonitorExArea(LPRECT lprcWindow);


	// ��ü ����� �����ȿ� rect�� ���ԵǾ����� �������� üũ
	BN23_API(void) IsRectInMonitorArea(CRect rect, bool &bLeft, bool &bTop, bool &bRight, bool &bBottom);
	BN23_API(void) IsRectInMonitorAreaEx(CRect rect, bool &bLT, bool &bRT, bool &bRB, bool &bLB);
};