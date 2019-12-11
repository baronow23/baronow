#pragma once



//////////////////////////////////////////////////////////////////////////////////////////////////////
// 사용자 정의
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define BND_WM_THREAD				WM_APP + 1		// 다른 쓰레드에서 보내는 이벤트
#define BND_WM_CLIENT				WM_APP + 2		// 클라이언트에서 팝업으로 보내는 이벤트
#define BND_WM_NOTIFY				WM_APP + 3		// 다른 윈도우에서 보내는 이벤트




//////////////////////////////////////////////////////////////////////////////////////////////////////
// System
//////////////////////////////////////////////////////////////////////////////////////////////////////

// WPARAM : ID
// LPARAM : Mouse Event (WM_LBUTTONDOWN, WM_RBUTTONDOWN)
#define BND_WM_SYSTRAY			WM_APP + 4		// 시스템 트레이 아이콘에 발생한 마우스 이벤트



// WPARAM : ID
// LPARAM : BNS_PopupMenuItem* (NULL일경우 메뉴 숨겨짐)
#define BND_WM_CONTEXTMENU		WM_APP + 5		// 팝업메뉴 이벤트



// WPARAM : 애니메이션 시간 (0지정시 사용않함)
// LPARAM : HWND (hAfterInsert)
#define BND_WM_FOREGROUND		WM_APP + 6


// 블로킹된 모달이 있을 때 close, destroywnd 발생시나 내부사용
// 추가로 BND_WM_DESTROYBLOCK는 특정 client에서 OnDestroy 딜레이가 필요할 때 내부 사용
#define BND_WM_CLOSEBLOCK		WM_APP + 7
#define BND_WM_DESTROYBLOCK		WM_APP + 8


//////////////////////////////////////////////////////////////////////////////////////////////////////
// non-overried
//////////////////////////////////////////////////////////////////////////////////////////////////////

// BaseClient의 m_vpTabstop에 등록된 윈도우가 Focus 되었을 때 
// m_uiPosTabstop의 변경 처리를 요구하는 메시지
// WPARAM = CWnd*
#define BND_WM_TABSTOP			WM_APP + 9






//////////////////////////////////////////////////////////////////////////////////////////////////////
// Control
// 전항목 LOWORD(wParam) = ID
//////////////////////////////////////////////////////////////////////////////////////////////////////

// HIWORD(wParam) = BNE_BTN_STATE, 
// LOWORD(lParam) = CPoint.x
// HIWORD(lParam) = CPoint.y
// BNE_BTN_STATE_DOWN 발생시 S_OK 반환하지 않으면 버튼상태 BNE_BTN_STATE_NORMAL로 변경 않함
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


// 윈도우 다시 그리기
// 조건 1 : m_LastWindowPosChanged.m_lfElapseTime > WPARAM 일 경우
// 조건 2 : 자신+child가 포커싱 되어있지 않을 때 (LPARAM 0아닐 때 체크)
// popup 은 등록된 rootclient의 OnRedraw 호출
// 모든 baseclient는 등록된 모든 자식 baseclient OnRedraw 호출함
#define BND_WM_REDRAW				WM_APP + 20



// 클립보드 이미지 붙혀넣기 (리치에디트 사용)
#define BND_WM_PASTE_IMAGE			WM_APP + 21


// 투명도 변경
// BNC_TransparentAnimation 스레드내에서 바로 접근하던 방식을 메시지 기반으로 변경
// WPARAM : 0~255 alpha
// LPARAM : 1(begin), 2(update), 3(end)
// return : 적용된 alpha값
#define BND_WM_TRANSPARENT			WM_APP + 22



// 웹브라우저 (BNC_HtmlBrowser, BNC_HtmlBrowserClient) 처리용
// WPARAM : BNE_WEBEVENT
// LPARAM : BNE_WEBEVENT 타입별 상이함
#define BND_WM_HTML_WEBEVENT		WM_APP + 23


// HPC_DShowVideo 자체처리 이벤트
#define BND_WM_DSHOW_VIDEO			WM_APP + 24



// 테스트중
#define BND_WM_RESIZECLIENT			WM_APP + 25


////////////////////////////////////////////////////////////////////////////////////

#define BND_WM_LAST_RESERVED		WM_APP + 26
