#pragma once



//////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� ����
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define BND_WM_THREAD				WM_APP + 1		// �ٸ� �����忡�� ������ �̺�Ʈ
#define BND_WM_CLIENT				WM_APP + 2		// Ŭ���̾�Ʈ���� �˾����� ������ �̺�Ʈ
#define BND_WM_NOTIFY				WM_APP + 3		// �ٸ� �����쿡�� ������ �̺�Ʈ




//////////////////////////////////////////////////////////////////////////////////////////////////////
// System
//////////////////////////////////////////////////////////////////////////////////////////////////////

// WPARAM : ID
// LPARAM : Mouse Event (WM_LBUTTONDOWN, WM_RBUTTONDOWN)
#define BND_WM_SYSTRAY			WM_APP + 4		// �ý��� Ʈ���� �����ܿ� �߻��� ���콺 �̺�Ʈ



// WPARAM : ID
// LPARAM : BNS_PopupMenuItem* (NULL�ϰ�� �޴� ������)
#define BND_WM_CONTEXTMENU		WM_APP + 5		// �˾��޴� �̺�Ʈ



// WPARAM : �ִϸ��̼� �ð� (0������ ������)
// LPARAM : HWND (hAfterInsert)
#define BND_WM_FOREGROUND		WM_APP + 6


// ���ŷ�� ����� ���� �� close, destroywnd �߻��ó� ���λ��
// �߰��� BND_WM_DESTROYBLOCK�� Ư�� client���� OnDestroy �����̰� �ʿ��� �� ���� ���
#define BND_WM_CLOSEBLOCK		WM_APP + 7
#define BND_WM_DESTROYBLOCK		WM_APP + 8


//////////////////////////////////////////////////////////////////////////////////////////////////////
// non-overried
//////////////////////////////////////////////////////////////////////////////////////////////////////

// BaseClient�� m_vpTabstop�� ��ϵ� �����찡 Focus �Ǿ��� �� 
// m_uiPosTabstop�� ���� ó���� �䱸�ϴ� �޽���
// WPARAM = CWnd*
#define BND_WM_TABSTOP			WM_APP + 9






//////////////////////////////////////////////////////////////////////////////////////////////////////
// Control
// ���׸� LOWORD(wParam) = ID
//////////////////////////////////////////////////////////////////////////////////////////////////////

// HIWORD(wParam) = BNE_BTN_STATE, 
// LOWORD(lParam) = CPoint.x
// HIWORD(lParam) = CPoint.y
// BNE_BTN_STATE_DOWN �߻��� S_OK ��ȯ���� ������ ��ư���� BNE_BTN_STATE_NORMAL�� ���� ����
#define BND_WM_CTL_BUTTON			WM_APP + 10		


// HIWORD(wParam) = Select Tab Index
#define BND_WM_CTL_COMBO			WM_APP + 11	


// HIWORD(wParam) = BNE_EDIT_EVENT
// BNE_EDIT_EVENT_FOCUS  -> LPARAM : 0(off), 1(on)
// BNE_EDIT_EVENT_UPDATE -> LPARAM = *CString
// BNE_EDIT_EVENT_SYSKEY -> LPARAM = VK_
#define BND_WM_CTL_EDIT				WM_APP + 12	



// HIWORD(wParam) = BNE_MOUSEACTION
// lParam = BNC_ReferenceItem* 
#define BND_WM_CTL_LIST				WM_APP + 13


#define BND_WM_CTL_PROGRESS			WM_APP + 14


// lParam = Pos
#define BND_WM_CTL_SCROLL			WM_APP + 15



// HIWORD(wParam)   = BNE_MOUSESTATE 
// lParam			= Pos
#define BND_WM_CTL_SLIDER			WM_APP + 16



// HIWORD(wParam)	= index
#define BND_WM_CTL_TAB				WM_APP + 17



#define BND_WM_CTL_TREE				WM_APP + 18


// HIWORD(wParam) = BNE_MOUSESTATE 
// LOWORD(lParam) = CPoint.x
// HIWORD(lParam) = CPoint.y
#define BND_WM_CTL_FBUTTON			WM_APP + 19		


// ������ �ٽ� �׸���
// ���� 1 : m_LastWindowPosChanged.m_lfElapseTime > WPARAM �� ���
// ���� 2 : �ڽ�+child�� ��Ŀ�� �Ǿ����� ���� �� (LPARAM 0�ƴ� �� üũ)
// popup �� ��ϵ� rootclient�� OnRedraw ȣ��
// ��� baseclient�� ��ϵ� ��� �ڽ� baseclient OnRedraw ȣ����
#define BND_WM_REDRAW				WM_APP + 20



// Ŭ������ �̹��� �����ֱ� (��ġ����Ʈ ���)
#define BND_WM_PASTE_IMAGE			WM_APP + 21


// ���� ����
// BNC_TransparentAnimation �����峻���� �ٷ� �����ϴ� ����� �޽��� ������� ����
// WPARAM : 0~255 alpha
// LPARAM : 1(begin), 2(update), 3(end)
// return : ����� alpha��
#define BND_WM_TRANSPARENT			WM_APP + 22



// �������� (BNC_HtmlBrowser, BNC_HtmlBrowserClient) ó����
// WPARAM : BNE_WEBEVENT
// LPARAM : BNE_WEBEVENT Ÿ�Ժ� ������
#define BND_WM_HTML_WEBEVENT		WM_APP + 23


// HPC_DShowVideo ��üó�� �̺�Ʈ
#define BND_WM_DSHOW_VIDEO			WM_APP + 24



// �׽�Ʈ��
#define BND_WM_RESIZECLIENT			WM_APP + 25


////////////////////////////////////////////////////////////////////////////////////

#define BND_WM_LAST_RESERVED		WM_APP + 26
