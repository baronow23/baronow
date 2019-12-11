#pragma once


///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _BARONOW25_EXPORT_
#define BN25_TYPE		__declspec(dllexport)
#define BN25_TEMPLATE	extern
#else
#define BN25_TYPE		__declspec(dllimport)
#define BN25_TEMPLATE
#endif

#define BN25_CLASS		class BN25_TYPE
#define BN25_API(ret)	BN25_TYPE ret


#define BND_USING_TRANSPARENT_ANIMATION


// 모달리스 보이거나 감출 때 투명애니메이션 되는 시간
#define HPD_TIME_MODALESS_ANIMATION	200		


////////////////////////////////////////////////////////////////////
// Define
#include "Define/BND_Macro.h"
#include "Define/BND_Message.h"
#include "Define/BND_Constant.h"
#include "Define/BND_Enumeration.h"


////////////////////////////////////////////////////////////////////
// Common (비윈도우 객체)

#include "Common/BNC_Template.h"
#include "Common/BNS_SyncPos.h"
#include "Common/BNS_TextInfo.h"
#include "Common/BNS_ImageInfo.h"
#include "Common/BNC_SyncRect.h"
#include "Common/BNC_MouseControl.h"
#include "Common/BNC_DrawString.h"
#include "Common/BNC_DrawObject.h"
#include "Common/BNC_TransparentAnimation.h"
#include "Common/BNC_PopupMenuItem.h"
#include "Common/BNC_ReferenceItem.h"
#include "Common/BNC_ReferenceItemEx.h"
#include "Common/BNC_ReferenceItemExOption.h"
#include "Common/BNC_ReferenceItemSort.h"
#include "Common/BNC_ReferenceItemSelecter.h"
#include "Common/BNC_RefTreeItemOption.h"
#include "Common/BNC_CaptureKeyboardMouse.h"
#include "Common/BNC_HyperLink.h"
#include "Common/BNC_StaticObject.h"
#include "Common/BNC_MagnetEffect.h"
#include "Common/BNC_GDI.h"
#include "Common/BNC_Graphics.h"
#include "Common/BNC_ClipboardImage.h"
#include "Common/BNC_DwmColorControl.h"
#include "Common/BNC_BorderessProc.h"
#include "Common/BNC_WindowSync.h"
#include "Common/BNC_WindowLayered.h"
#include "Common/BNC_DpiPoint.h"
#include "Common/BNC_FakeRect.h"
#include "Common/BNC_FakeBtnSet.h"
#include "Common/BNC_HtmlMetaInfo.h"
#include "Common/BNC_Base64Low.h"



////////////////////////////////////////////////////////////////////
// Base Classes
#include "Base Classes/BNC_BaseControl.h"
#include "Base Classes/BNC_BaseSliderCtrl.h"
#include "Base Classes/BNC_BaseClient.h"
#include "Base Classes/BNC_BaseDialog.h"
#include "Base Classes/BNC_BaseModal.h"
#include "Base Classes/BNC_BaseModaless.h"
#include "Base Classes/BNC_BaseOverlay.h"
#include "Base Classes/BNC_BaseFloating.h"
#include "Base Classes/BNC_BaseInstant.h"
#include "Base Classes/BNC_BaseRefItemControl.h"
#include "Base Classes/BNC_BaseRefItemControlEx.h"
#include "Base Classes/BNC_BaseLayered.h"



////////////////////////////////////////////////////////////////////
// Control
#include "Control/BNC_Button.h"
#include "Control/BNC_ButtonEx.h"
#include "Control/BNC_Editbox.h"
#include "Control/BNC_RichEditbox.h"
#include "Control/BNC_RichEditboxEx.h"
#include "Control/BNC_TabControl.h"
#include "Control/BNC_FloatingButton.h"
#include "Control/BNC_SimpleVScrollbar.h"
#include "Control/BNC_SimpleHScrollbar.h"
#include "Control/BNC_RefListControl.h"
#include "Control/BNC_RefListControlEx.h"
#include "Control/BNC_RefTreeControl.h"
#include "Control/BNC_DummyListControl.h"
#include "Control/BNC_Titlebar.h"
#include "Control/BNC_FakeModal.h"


////////////////////////////////////////////////////////////////////
// Client
#include "Client/BNC_RefListView.h"
#include "Client/BNC_RefListViewEx.h"
#include "Client/BNC_RefTreeView.h"
#include "Client/BNC_EditboxEx.h"
#include "Client/BNC_DummyListView.h"
#include "Client/BNC_HtmlBrowser.h"



////////////////////////////////////////////////////////////////////
// Popup 
#include "Popup/BNC_AnimationDialog.h"
#include "Popup/BNC_PopupMenu.h"
#include "Popup/BNC_FloatingMessage.h"
#include "Popup/BNC_FadeAnimation.h"
#include "Popup/BNC_MessageBox.h"
#include "Popup/BNC_AsyncMessageBox.h"
#include "Popup/BNC_FakeWindow.h"


namespace IBaronow25
{
	BN25_API(void)		Initialize(void);
	BN25_API(void)		ExitInstnace(void);

	BN25_API(void)		ReleaseCapture(void);
	BN25_API(LRESULT)	SendControlMessage(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

	BN25_API(void)		ShowWindowCheck(DWORD dwWndThreadID, DWORD dwCurThreadID, CWnd *pWnd, int iCmd);
	BN25_API(void)		ShowWindowCheck(BNC_BaseDialog* pWnd, int iCmd);
	BN25_API(void)		ShowWindowCheck(BNC_BaseClient* pWnd, int iCmd);
	BN25_API(void)		ShowWindowCheck(BNC_BaseControl* pWnd, int iCmd);
	BN25_API(void)		ShowWindowCheck(BNC_BaseDialog &wnd, int iCmd);
	BN25_API(void)		ShowWindowCheck(BNC_BaseClient &wnd, int iCmd);
	BN25_API(void)		ShowWindowCheck(BNC_BaseControl &wnd, int iCmd);


	BN25_API(void)		ShowAsyncMessagebox(BNC_BaseDialog *pTarget,
											LPCTSTR lpszCaption, LPCTSTR lpszMessage, bool bUseCancel = false,
											UINT uiBeepType = MB_ICONASTERISK,
											COLORREF clrCaption = VSCLR_TEXT, COLORREF clrMessage = VSCLR_VARIABLE,
											std::function<void(INT_PTR)> cbResult = nullptr);
};

////////////////////////////////////////////////////////////////////



// 단순 vc2017 warning 없애기
#define MAKEINTRESOURCE_EX(i)	MAKEINTRESOURCE( LOWORD(i) )

