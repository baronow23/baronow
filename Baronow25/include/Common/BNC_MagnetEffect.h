#pragma once

class BN25_TYPE BNC_MagnetEffect
{
public :
	static bool OnWindowPosChanging(WINDOWPOS* lpwndpos, bool bExceptUnderWindow = true, ULONG offset = 10);
	static bool OnSizing(CWnd* pWnd, UINT fwSide, LPRECT pRect, bool bExceptUnderWindow = true, ULONG offset = 10);

	// ���÷��� �ػ� ����� App���� �ѹ� ȣ���� �ٰ�
	static void SetMonitorInfo(void);


private :
	static BOOL CALLBACK FindTargetWindowProc(HWND hwnd, LPARAM lParam);
	static void CheckMagnetSegment(void);
	static void AddTargetWindow(CRect rcTarget);
};
