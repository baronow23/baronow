#pragma once



// text ��½� ���� ��Ʈ �Ӽ�
enum BNE_FONT_STYLE
{
	BNE_FS_NORMAL,
	BNE_FS_NORMAL_LINE,
	BNE_FS_BOLD,
	BNE_FS_BOLD_LINE,
};


// ���̾�α� ����
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


	// floating ���
	BNE_DT_FBUTTON,
	BNE_DT_FMESSAGE,

	
	// Ȯ��
	BNE_DT_FAKEMODAL,
	BNE_DT_FAKEMODALEX
};


// ����� ���� üũ �ɼ�
enum BNE_MONITOR_CHECK
{
	BNE_MC_NONE,
	BNE_MC_WORK,
	BNE_MC_MONITOR,
};


// ���콺 ����
enum BNE_MOUSEACTION
{
	BNE_MA_NONE	= 0,
	BNE_MA_OVER	= 1,

	BNE_MA_LDN	= 10,
	BNE_MA_LDDN	= 11,	// ����Ŭ��
	BNE_MA_LUP	= 12,
	//BNE_MA_LUPO	= 13,	// ĸ�Ļ��¿��� ������ �ۿ��� �߻�

	BNE_MA_RDN	= 20,
	//BNE_MA_RDDN	= 21,
	BNE_MA_RUP	= 22,
};



// Refrence ������ ���� (�׸����)
enum BNE_REFITEM_STATE
{
	BNE_RIS_DISABLE,
	BNE_RIS_NORMAL,
	BNE_RIS_FOCUS,
	BNE_RIS_SELECT,
};


// ��Ʈ�� ����
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



// �θ������ ���� �κ�
enum BNE_VARSIZE
{
	BNE_VS_DEFAULT,	// szOffset ����
	BNE_VS_WIDTH,	// ���� ũ�⸸ ����
	BNE_VS_HEIGHT,	// ���� ũ�⸸ ����
	BNE_VS_ALL,		// ����, ���� ��� ����
};
*/
