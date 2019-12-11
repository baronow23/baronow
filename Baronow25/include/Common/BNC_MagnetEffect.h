#pragma once

class BN25_TYPE BNC_MagnetEffect
{
public :
	static bool OnWindowPosChanging(WINDOWPOS* lpwndpos, bool bExceptUnderWindow = true, ULONG offset = 10);
	static bool OnSizing(CWnd* pWnd, UINT fwSide, LPRECT pRect, bool bExceptUnderWindow = true, ULONG offset = 10);

	// 디스플레이 해상도 변경시 App에서 한번 호출해 줄것
	static void SetMonitorInfo(void);


private :
	static BOOL CALLBACK FindTargetWindowProc(HWND hwnd, LPARAM lParam);
	static void CheckMagnetSegment(void);
	static void AddTargetWindow(CRect rcTarget);
};
