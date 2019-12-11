#pragma once

namespace bapi 
{
	// 모든 모니터 구성정보 찾아서 반환
	// lprcBoundary 지정하면 포함 모니터만 얻어옴
	BN23_API(baro::MonitorInfo) GetMonitorInfo(LPRECT lprcBoundary = nullptr);
	

	// 주모니터 영역 반환
	BN23_API(CRect) GetPrimaryArea(void);
	BN23_API(CRect) GetPrimaryWork(void);


	// hwnd 또는 lprcWindow가 위치하고 있는곳의 작업영역 반환
	BN23_API(CRect) GetCurrentWorkArea(HWND hwnd);
	BN23_API(CRect) GetCurrentWorkArea(LPRECT lprcWindow);


	// hwnd 또는 lprcWindow가 위치하고 있는곳의 모니터영역 반환
	BN23_API(CRect) GetCurrentMonitorArea(HWND hwnd);
	BN23_API(CRect) GetCurrentMonitorArea(LPRECT lprcWindow);

	
	// 초기화 된 MonitorInfo의 m_szMax, m_rcBoundary와 동일
	// 실시간 데이터가 필욯알 때 사용
	BN23_API(CSize) GetMonitorResolution(void);		
	BN23_API(CSize) GetMonitorMaxResolution(void);


	// 윈도우(hwnd) 또는 지정영역(lprcWindow)에 걸쳐있는 모니터들의 합산된 영역 반환 (듀얼모니터 이상 포함)
	// ex) 모니터1(1280*1024), 모니터2(1024*768)이고 모니터1,2에 걸쳐있다면  2304*1024크기의 윈도우영역 반환
	BN23_API(CRect) GetMonitorExArea(HWND hwnd);		
	BN23_API(CRect) GetMonitorExArea(LPRECT lprcWindow);


	// 전체 모니터 영역안에 rect가 포함되었는지 부위별로 체크
	BN23_API(void) IsRectInMonitorArea(CRect rect, bool &bLeft, bool &bTop, bool &bRight, bool &bBottom);
	BN23_API(void) IsRectInMonitorAreaEx(CRect rect, bool &bLT, bool &bRT, bool &bRB, bool &bLB);
};