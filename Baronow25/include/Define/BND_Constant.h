#pragma once


#define BND_DEFAULT_FONT	_T("Malgun Gothic")
//#define BND_DEFAULT_FONT _T("Dotum")


// 고정 타이머 ID (사용자 정의 사용 금지)
#define BND_TIMERID_UPDATE_INITPOS		0xFFFFFF00
#define BND_TIMERID_UPDATE_TRANSPARENT	0xFFFFFF01
#define BND_TIMERID_UPDATE_FLOATING		0xFFFFFF02
#define BND_TIMERID_UPDATE_ANIMATION	0xFFFFFF03
#define BND_TIMERID_FLOATING_MESSAGE	0xFFFFFF04
#define BND_TIMERID_OVERLAY_SHOW		0xFFFFFF05
#define BND_TIMERID_OVERLAYCHILD_SHOW	0xFFFFFF06
#define BND_TIMERID_POPUPCHILD_SHOW		0xFFFFFF07
#define BND_TIMERID_POPUPCHILD_HIDE		0xFFFFFF08
#define BND_TIMERID_BTN_ANIMATION		0xFFFFFF09


////////////////////////////////////////////////////////////////////////////////
// 부모윈도우로부터 고정시킬 위치지정
#define BND_FIXPOINT_DEFAULT	0x0000		// 위치 변경 없음
#define BND_FIXPOINT_TOP		0x0001		// offset.y 적용
#define BND_FIXPOINT_BOTTOM		0x0002		// offset.y 적용
#define BND_FIXPOINT_VCENTER	0x0004		// 수직축 중심		// m_ptOffset.y 무시
#define BND_FIXPOINT_LEFT		0x0010		// offset.x 적용
#define BND_FIXPOINT_RIGHT		0x0020		// offset.x 적용
#define BND_FIXPOINT_HCENTER	0x0040		// 가로축 중심		// m_ptOffset.x 무시

#define BND_FIXPOINT_TL			BND_FIXPOINT_TOP	 | BND_FIXPOINT_LEFT
#define BND_FIXPOINT_TC			BND_FIXPOINT_TOP	 | BND_FIXPOINT_HCENTER
#define BND_FIXPOINT_TR			BND_FIXPOINT_TOP	 | BND_FIXPOINT_RIGHT
#define BND_FIXPOINT_CL			BND_FIXPOINT_VCENTER | BND_FIXPOINT_LEFT
#define BND_FIXPOINT_CC			BND_FIXPOINT_VCENTER | BND_FIXPOINT_HCENTER
#define BND_FIXPOINT_CR			BND_FIXPOINT_VCENTER | BND_FIXPOINT_RIGHT
#define BND_FIXPOINT_BL			BND_FIXPOINT_BOTTOM	 | BND_FIXPOINT_LEFT
#define BND_FIXPOINT_BC			BND_FIXPOINT_BOTTOM	 | BND_FIXPOINT_HCENTER
#define BND_FIXPOINT_BR			BND_FIXPOINT_BOTTOM	 | BND_FIXPOINT_RIGHT



////////////////////////////////////////////////////////////////////////////////
#define BND_VARSIZE_DEFAULT		0x0000		// 초기 offset 적용 (이후 사이즈 변경 없음)
#define BND_VARSIZE_WIDTH		0x0001		// offset.cx 적용
#define BND_VARSIZE_HEIGHT		0x0002		// offset.cy 적용
#define BND_VARSIZE_ALL			BND_VARSIZE_WIDTH | BND_VARSIZE_HEIGHT


////////////////////////////////////////////////////////////////////////////////
// 기타 고정 메시지 ID

#define BND_RICHEDIT_PASTE_MENU		0xFFFF
#define BND_RICHEDIT_PASTE_TEXT		0xFFF0
#define BND_RICHEDIT_PASTE_IMAGE	0xFFF1


////////////////////////////////////////////////////////////////////////////////
// 사용자가 조작한 윈도우 리사이징 기본 플래그

#define BND_RESIZE_WINDOW_FLAGS		(SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOZORDER )
#define BND_RESIZE_CLIENT_FLAGS		(SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOZORDER )
#define BND_RESIZE_CONTROL_FLAGS	(SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOZORDER )


////////////////////////////////////////////////////////////////////////////////
#define		_USING_OVERLAY_ANIMATION_

#define		_USING_BORDERESS_PROC_
/*#define		_USING_BORDERESS_FAKEWND_*/
#define		_USING_BORDERESS_NCSIZE_
//#define		_USING_BORDERESS_CUSTOM_

/*
#define		_USING_TOP_COMPOSITED_
#define		_USING_CLIENT_COMPOSITED_	
#define		_USING_CONTROL_COMPOSITED_	
*/


#ifdef			_USING_BORDERESS_CUSTOM_
	//#define		_USING_HIDDEN_FRAME_
	#ifndef		_USING_TOP_COMPOSITED_
		#define _USING_TOP_COMPOSITED_INSTANCE_
		//#define _USING_TRANSPARENT_RESIZING_ //테스트중
	#endif
#endif