#pragma once



// text 출력시 지정 폰트 속성
enum BNE_FONT_STYLE
{
	BNE_FS_NORMAL,
	BNE_FS_NORMAL_LINE,
	BNE_FS_BOLD,
	BNE_FS_BOLD_LINE,
};


// 다이얼로그 종류
enum BNE_DIALOG_TYPE
{
	BNE_DT_BASE,


	// base
	BNE_DT_MODAL,
	BNE_DT_MODALESS,
	BNE_DT_OVERLAY,
	BNE_DT_ANIMATION,
	

	// modal
	BNE_DT_MSGBOX,


	// modaless
	BNE_DT_FLOATING,
	BNE_DT_INSTANT,


	// floating 상속
	BNE_DT_FBUTTON,
	BNE_DT_FMESSAGE,

	
	// 확장
	BNE_DT_FAKEMODAL,
	BNE_DT_FAKEMODALEX
};


// 모니터 영역 체크 옵션
enum BNE_MONITOR_CHECK
{
	BNE_MC_NONE,
	BNE_MC_WORK,
	BNE_MC_MONITOR,
};


// 마우스 조작
enum BNE_MOUSEACTION
{
	BNE_MA_NONE	= 0,
	BNE_MA_OVER	= 1,

	BNE_MA_LDN	= 10,
	BNE_MA_LDDN	= 11,	// 더블클릭
	BNE_MA_LUP	= 12,
	//BNE_MA_LUPO	= 13,	// 캡쳐상태에서 윈도우 밖에서 발생

	BNE_MA_RDN	= 20,
	//BNE_MA_RDDN	= 21,
	BNE_MA_RUP	= 22,
};



// Refrence 아이템 상태 (그리기용)
enum BNE_REFITEM_STATE
{
	BNE_RIS_DISABLE,
	BNE_RIS_NORMAL,
	BNE_RIS_FOCUS,
	BNE_RIS_SELECT,
};


// 컨트롤 상태
enum BNE_CONTROL_STATE
{
	BNE_CS_NORMAL,		// Button, Slider
	BNE_CS_FOCUS,		// Button, Slider, Edit
	BNE_CS_DOWN,		// Button, Slider
	BNE_CS_DISABLE,		// Button, Slider
	BNE_CS_KILL_FOCUS,	// Edit

};

/*
enum BNE_FIXPOINT
{
	BNE_FP_TOP_LEFT,
	BNE_FP_TOP_CENTER,
	BNE_FP_TOP_RIGHT,

	BNE_FP_CENTER_LEFT,
	BNE_FP_CENTER_CENTER,
	BNE_FP_CENTER_RIGHT,

	BNE_FP_BOTTOM_LEFT,
	BNE_FP_BOTTOM_CENTER,
	BNE_FP_BOTTOM_RIGHT,
};



// 부모사이즈 적용 부분
enum BNE_VARSIZE
{
	BNE_VS_DEFAULT,	// szOffset 적용
	BNE_VS_WIDTH,	// 가로 크기만 적용
	BNE_VS_HEIGHT,	// 세로 크기만 적용
	BNE_VS_ALL,		// 가로, 세로 모드 적용
};
*/
