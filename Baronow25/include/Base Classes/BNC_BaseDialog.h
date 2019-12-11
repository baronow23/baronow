#pragma once

class BN25_TYPE BNC_BaseDialogTracer : public baro::TSingleton<BNC_BaseDialogTracer>
{
	friend class BNC_BaseDialog;
public :
	BNC_BaseDialogTracer(baro::TSingleton<BNC_BaseDialogTracer>::_token);
	~BNC_BaseDialogTracer(void);

private :
	baro::CriticalSection	m_cs;
	set<HWND>	m_shAliveDialog;


private :
	bool	Insert(HWND hWnd);
	bool	Delete(HWND hWnd);


public :
	set<HWND>	GetAliveDialog(void);
	bool			IsAlive(HWND hWnd);
	BNC_BaseDialog*	FromPopupPtr(CWnd *pWnd);
	HWND			FromPopupHwnd(CWnd *pWnd);
};

//using BNC_BaseDialogTracerInstance = BNC_BaseDialogTracer::GetInstance();
#define BNC_BaseDialogTracerInstance BNC_BaseDialogTracer::GetInstance()	





#include "../Popup/BNC_FakeBorder.h"
#include "BNC_BaseClient.h"

#define SC_MAXIMIZE_EX			0xF031
#define NCTYPE_READONLY			protected


#define BND_SYNC_ZORDER		0x0001
#define BND_SYNC_POSITION	0x0002 
#define BND_SYNC_BLENDING	0x0004
#define BND_SYNC_VISIBLE	0x0008
#define BND_SYNC_ENABLE		0x0010
#define BND_SYNC_ALL		(BND_SYNC_ZORDER | BND_SYNC_POSITION | BND_SYNC_BLENDING | BND_SYNC_VISIBLE | BND_SYNC_ENABLE)


const UINT WM_TASKBARCREATED = ::RegisterWindowMessage(_T("TaskbarCreated"));
//WM_RELOADTRAYICON

class BNC_BaseModal;
class BNC_FakeModal;
class BNC_BaseFloating;
class BNC_FloatingMessage;
class BN25_TYPE BNC_BaseDialog : public CDialog
{
	friend class BNC_FakeWindow;
	DECLARE_DYNAMIC(BNC_BaseDialog)

	 
	// 생성입니다.
public:
	BNC_BaseDialog(void);
	BNC_BaseDialog(UINT nDialogID, CWnd* pParent = NULL);
	virtual ~BNC_BaseDialog(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


	////////////////////////////////////////////////////////////////////////////////////////////////
	// static
	////////////////////////////////////////////////////////////////////////////////////////////////

public:
	// Overlay, Anmation등 내부 효과로 사용할 Dialog ID 
	// CWinApp::Initinstance()에서 반드시 지정 할 것 
	static UINT		s_uiDefaultTemplate;

	
private:
	static atomic<UINT>		s_uiCreateCount;
	static atomic<UINT>		s_uiDestroyCount;
	static CSize			s_szMaxMonitorRes;
	static CRect			s_rcLastNormalRect;


public:
	static UINT				GetCreateCount(void);
	static UINT				GetAliveCount(void);
	static CSize			GetMaxMonitorResolution();
	static void				ShowRestoreWindow(HWND hWnd, HWND hAfterInsert = NULL, bool bActivate = true, bool bSync = true);


	// 메인 app에서 OnDisplayChange 수신시 한번 호출
	static void				UpdateDisplayChange(WPARAM wParam, LPARAM lParam);



	// BNC_BaseDialog를 상속받은 다이얼로그를 보이기
	// 특정 다이얼로그의 상대적 위치 적용과 모니터 영역 체크 포함
	static void ShowSyncDialog(BNC_BaseDialog*	pDialog,
							   double lfAnimation = 200,
							   const CWnd* pAfterInsert= NULL,
							   HWND		hTarget		= NULL,
							   DWORD	dwFixPoint	= BND_FIXPOINT_CC,
							   CPoint	ptOffset	= CPoint(0, 0));
	

	// rcTarget의 dwFixPoint위치에 szWnd + ptOffset 결과가 적용된 ptWnd 반환
	// ptWnd + szWnd의 어느 위치도 전체 모니터 안에 포함되어 있지 않으면 false 반환
	// prcMonitor가 있으면 prcMonitor로 한정함
	static bool	GetFixPoint(IN CRect &rcTarget,
							IN DWORD dwFixPoint,
							IN CPoint &ptOffset,
							IN CSize &szWnd,
							OUT CPoint &ptWnd,
							IN CRect* prcMonitor);

	
public:
	BNE_DIALOG_TYPE		GetDlgType(void);
	CWnd*				GetInitParent(void);


protected :
	BNC_FakeBorder		m_FakeBorder;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 내부에서 업데이트되는 항목, 
	// 외부 수정 금지 (상속 클래스 포함)
	// 일일이 Get 메서드 만들기 귀찮으니 읽기용으로만 사용할 것
	////////////////////////////////////////////////////////////////////////////////////////////////
NCTYPE_READONLY:
	BNE_DIALOG_TYPE	m_DlgType;

	// create()에서 bChildDialog를 true로 사용할 때, GetParent() 값이
	// create()에서 지정한 pParentWnd와 달라지므로 저장해 놓음
	CWnd*	m_pInitParent;


	// 모달로 해당 윈도우를 블록시킨 윈도우
	CWnd*	m_pCurBlockWnd;


	// 다이얼로그 속성
	bool	m_bIsModaless;		// 타입
	bool	m_bAppWindow;
	bool	m_bUseResizing;
	bool	m_bEnableTopmost;
	bool	m_bChildWindow;
	DWORD	m_dwInitStyle;
	DWORD	m_dwInitStyleEx;
	const CWnd*	m_pInitWndInsertAfter;


	// 상태
	bool	m_bOnClose;
	bool	m_bIsCreate;
	bool	m_bIsActivate;
	bool	m_bIsMaximize;
	bool	m_bIsMaximizeEx;
	BOOL	m_bDwmComposited;


	// 크기
	CSize	m_szClient;
	CSize	m_szWindowMin;
	CSize	m_szWindowMax;		// 기본값 : s_szMaxMonitorRes 사용
	CRect	m_rcDefaultWnd;
	CRect	m_rcOutside;
	CRect	m_rcMaximizeBefore;	// 최대화, 최대화확장 명령 수행전 윈도우 위치
	CRect	m_rcLastVisible;	// 최종 윈도우 위치 (iconic 제외)
	BOOL	m_bEnterMoveZoom;	// OnEnterSizeMove 호출당시 IsZoom 상태


	BNC_BorderessProc	m_BorderessProc;
	bool				m_bUsingBorderessProc;
	DWORD				m_dwIgnoreBorderessFlags;


protected:
	// 팝업의 상태 변경(UpdatePopupStatus) 및 포커스 전달 받은 루트 클라이언트 등록
	BNC_BaseClient*		m_pRootClientPtr;
	bool				m_bAutoRootClientPos; // 항상 테두리 안쪽 위치에 m_pRootClientPtr 배치


	// 동적생성시 DestroyWindow에서 자동 삭제 지정 여부
	bool	m_bAutoDelete;


public :
	BNC_BaseDialog(const BNC_BaseDialog&) = delete;
	BNC_BaseDialog& operator= (const BNC_BaseDialog) = delete;


	////////////////////////////////////////////////////////////////////////////////////////////////
	// Mouse Action
	////////////////////////////////////////////////////////////////////////////////////////////////
protected:
	CPoint	m_ptLBtnDown;
	CPoint	m_ptNCLBtnDown;
	CSize	m_szNCLBtnDownSize;			// NCLBtnDown시 윈도우 크기
	bool	m_bSucceedLastMagnetEffect;	// 자석효과 완료(m_bEnableMagnetEffect == true 일 때)


	bool	m_bClickEdge;				// 리사이징 영역 클릭여부
	bool	m_bPauseCapture;
	UINT	m_uiHitTest;				// 마우스 클릭시 WM_NCLBUTTONDOWN 날릴 지점



	////////////////////////////////////////////////////////////////////////////////////////////////
	// 옵션 : 기본
	////////////////////////////////////////////////////////////////////////////////////////////////

public:
	bool		m_bUseStretchCaption;		// 창의 모든 영역을 캡션으로 사용할지 여부
	int			m_iUseCaptionHeight;		// 창이동이 가능한 캡션바 크기(m_bUseStretchCaption이 false 일 때)
	bool		m_bIgnoreAltF4;				// Alt + F4 종료 차단 (BNC_BaseModal에서는 m_bIgnoreExitKey ture로 동작함)
	bool		m_bUsingEscClose;			// esc close사용여부 (모달리스에서만 사용할 것)
	bool		m_bEnableMagnetEffect;		// 자석효과 사용여부 (default : false)
	bool		m_bClickAtivateRedraw;		// 마우스 클릭으로 활성화시 OnRedraw 발생 시킬지 여부

	CSize		m_szWindowDefault;			// 초기 윈도우 크기
	COLORREF	m_colorEdge1;
	COLORREF	m_colorEdge2;
	COLORREF	m_colorBG;
	bool		m_bDrawEdge;
	UINT		m_iBltCount;


	// 사용자 커스텀 사용
	DWORD		m_dwUserState;


	// 마지막 창 이동시간 체크
	baro::Performance	m_LastWindowPosChanged;


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 옵션 : System Tray
	////////////////////////////////////////////////////////////////////////////////////////////////

protected:
	HICON			m_hIcon;
	NOTIFYICONDATA	m_SystrayData;
	UINT m_uiTaskbarCreated;	// 윈도우 탐색기 재시작 체크

public:
	void	SystemTrayInsert(LPCTSTR strTip, UINT uiIconRes, UINT uiMsgID, CString strGUID);
	void	SystemTrayDelete(void);
	void	SystemTrayModify(UINT uiIconRes);
	void	SystemTrayCheckRestore(void);
	const NOTIFYICONDATA* GetSystemTrayData(void);
	

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 옵션 : Animation
	////////////////////////////////////////////////////////////////////////////////////////////////

protected:
	// 투명 애니메이션
	BNC_TransparentAnimation	m_TransparentAnimation;

	// 이동 애니메이션 : Animation(false~) 호출 당시위치와 DC
	CRect m_rcAnimation;
	CDC	 m_DcAnimation;


public:
	// 투명 애니메이션 실행
	void	RunTransparentAnimation(bool bShow, double lfDelay = 100, const CWnd* pAfterInsert = NULL, bool bShowActivate = true);
	bool	IsAnimationVisible(void);
	virtual void OnFirstTransparentAnimation(BYTE btAlpha);
	//virtual void UpdateTransparentAnimationRange(OUT BYTE &btMin, OUT BYTE &btMax);


	// 이동 애니메이션
	void	Animation(bool bAvtive, CPoint *pptBegin = NULL, CPoint *pptEnd = NULL, double lfMilliSec = 200);
	void	CopyDC(OUT CDC *pCopyDC);


	// 작업표시줄 플래시 효과
	void RunFlashEffect(UINT uiCount = 3);


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 옵션 : Sync Position, Z-order
	////////////////////////////////////////////////////////////////////////////////////////////////
private:
	// 팝업에 종속되어 윈도우 크기나 위치가 변경 될 때마다 동기화 시켜줄 윈도우와 마지막 적용된 윈도우 위치
	vector<BNC_BaseDialog*>	m_vSyncPosition;
	CRITICAL_SECTION				m_csSyncPosition;
	WINDOWPOS						m_wndposUpdate;
	WINDOWPOS						m_wndposCheck;
	

	static CPoint s_ptHidePos;			// 창이 숨겨질 때 좌표(시스템) : 디폴트 (-32000, -32000)

public:
	static UINT s_uiAnimationDelay;		// 애니메이션 시간 : 디폴트 200


private:
	// Z-order 동기화
	vector<BNC_BaseDialog*>	m_vSyncZorder;
	CRITICAL_SECTION				m_csSyncZorder;


private:
	// 업데이트
	void	UpdateSyncPosition(WINDOWPOS* lpwndpos);
	void	UpdateSyncZorder(void);


public :
	void	UpdateSyncPosition(void);


private :
	// show/hide sync
	void	OnShowWindowSync(BOOL bShow, WINDOWPOS* lpwndpos);


private:
	// 추가, 제거
	bool	RegSyncPosition(bool bInsert, BNC_BaseDialog* pSyncDlg);
	bool	RegSyncZorder(bool bInsert, BNC_BaseDialog* pSyncDlg);

	

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 옵션 : Sync Position (Client)
	////////////////////////////////////////////////////////////////////////////////////////////////
public:
	BNS_SyncPos	m_SyncPos;


public:
	// 부모윈도우의 위치, 크기에 따라 동기화 시킬 정보
	// pAfterInsert 사용 않함
	// z-order는 RegSyncPosition()에 등록된 순서 유지
	// ptOffset, szOffset은 상대값
	void	SetSyncPos(DWORD dwFixPoint, CPoint ptOffset, DWORD dwVarSize, CSize szOffset, CWnd* pAfterInsert = NULL, bool bUpdate = true);



protected:
	void	GetUpdateSyncPos(int x, int y, int cx, int cy, OUT CPoint &pt, OUT CSize &sz, OUT UINT &uiFlags);


	// x, y, cx, cy는 동기화 시킬 윈도우 정보임
	// pAfterInsert 미지정시 InitFloating() 파라미터 pAfterInsert 사용
	void	SetSyncWindowPos(HDWP hdwp, const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT uiAddFlags);


	// SetSyncWindowPos안에서 GetUpdateSyncPos 계산후 조정이 필요할 때 호출
	virtual bool OnSyncWindowPos(HDWP hdwp, const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT uiAddFlags);



	////////////////////////////////////////////////////////////////////////////////////////////////
	// 옵션 : 각 팝업별 하나씩 가질 수 있는 내부 플로팅
	////////////////////////////////////////////////////////////////////////////////////////////////
	//private:
protected:
	BNC_BaseFloating*		m_pDisableOverlay;		// EnableWindow(FALSE) 상태 오버레이
	BNC_FloatingMessage*	m_pSystemMessage;
	BNC_BaseFloating*		m_pInactiveOverlay;

	
private:
	// Z-order 관리
	BNC_BaseDialog*		m_pFirstZorder;	 // m_vSyncPosition[0] > m_pSystemMessage > m_pDisableOverlay
	BNC_BaseDialog*		m_pLastZorder;	 // m_pDisableOverlay > m_pSystemMessage > m_pLastFloating
	int					m_iFloatingCount;


protected:
	BYTE		m_btDisableOverlay;
	COLORREF	m_clrDisableOverlay;

	BYTE		m_btSysMsgAlphaBegin;
	BYTE		m_btSysMsgAlphaEnd;
	//COLORREF	m_clrSystemMessage;


	BYTE		m_btInactiveOverlay;
	COLORREF	m_clrInAvtiveOverlay;

	// m_pDisableOverlay 동시사용시 메시지 zorder를 가장 나중으로 사용 (다이얼로그 생성전에 유효)
	bool		m_bSysMsgLastZorder;

	bool		m_bHideSysMsgOnMinMax;	// 최소, 최대화 상태일 때 감춤 
	bool		m_bHideSysMsgOnVisible;	// show/hide 변경될 때 감춤
	

public:
	// 다이얼로그 생성전 사용여부 지정되어야 함 
	bool		m_bUseDisableOverlay;	// 생성 이후 수정은 Enable에서 등장여부 결정함)
	bool		m_bUseSystemMessage;	// 생성 이후 수정 변화 없음
	bool		m_bUseInactiveOverlay;


private:
	bool	CreateSystemMessage(void);
	bool	CreateDisableOverlay(void);
	bool	CreateInactiveOverlay(void);


public:
	void	ShowDisableOverlay(bool bShow);
	void	ShowSystemMessage(UINT uiDelayShow,
							  UINT uiDelayStay,
							  UINT uiDelayHide,
							  LPCTSTR strMsg,
							  bool bAnimation = true,
							  bool bAlignCenter = true);


	void	ShowSystemMessage(UINT uiDelayShow,
							  UINT uiDelayStay,
							  UINT uiDelayHide,
							  LPCTSTR strMsg,
							  COLORREF clrBk,
							  bool bAnimation = true,
							  bool bAlignCenter = true);

	
	void	ShowSystemMessage(UINT uiDelayShow,
							  UINT uiDelayStay,
							  UINT uiDelayHide,
							  CBitmap* pImagePtr,
							  CPoint ptImagePos,
							  CSize szImageSize,
							  bool bAnimation = true);
	void	HideSystemMessage(bool bAnimation);
	BNC_FloatingMessage*	GetSystemMessagePtr(void);
	BNC_BaseFloating*		GetDisableOverlayPtr(void);


	virtual void OnUpdateSystemMessagePos(BNS_SyncPos *pSyncPos);


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 옵션 : Window Layered
	////////////////////////////////////////////////////////////////////////////////////////////////
private:
	// 팝업에 종속되어 윈도우 투명도가 변경되었을 때 동기화 처리할 윈도우
	set<BNC_BaseDialog*>	m_sSyncBlendingDlg;
	CRITICAL_SECTION			m_csSyncBlending;


protected:
	bool		m_bUseColorkey;			// 칼라키 사용 여부
	COLORREF	m_colorTransparent;		// m_bUseColorkey가 true일 때 지정한 colorKey


	// 투명값
	// m_btSyncAlpha = 128(50%)이고 m_btAlpha가 25(10%)면 최종 알파는 255 * 0.5 * 0.1
	BYTE		m_btSyncAlpha;			// 동기화 될 종속 윈도우의 알파값
	BYTE		m_btAlpha;				// 투명 설정값 SetTransparent 적용되며 m_btSyncAlpha를 넘어설 수 없음



NCTYPE_READONLY:
	CRITICAL_SECTION	m_csSyncLayer;
	bool				m_bUpdateLayeredWindow;	// UpdateLayeredWindow() 사용여부
	Gdiplus::Image*		m_pLayerImagePtr;		// 적용된 이미지
	CPoint				m_ptLayerImagePos;		// 리소스상 위치
	CSize				m_szLayerImageSize;
	CSize				m_szLayerImageStretch;

	CDC*				m_pLayerCDC;			// SetLayerCDC
	CSize				m_szLayerCDC;

	CBitmap*			m_pLayerBitmapPtr;		// SetLayerBitmap
	CSize				m_szLayerBitmapStretch;



private:
	// 투명 처리 동기화 시킬 다이얼로그 추가 제거
	bool	RegSyncBlending(bool bInsert, BNC_BaseDialog* pSyncDlg);


public:
	// 투명 설정 (레이어드 미적용 체크후 변경, m_bUseTransparent 활성)
	void				SetTransparentAnimationRange(BYTE btMin, BYTE btMax);
	pair<BYTE, BYTE>	GetTransparentAnimationRange(void);
	void	SetSyncAlpha(BYTE btSync);
	BYTE	SetAlpha(BYTE btAlpha, bool bCheck = false);		// Sync 적용된 결과 반환
	BYTE	GetAlpha(void);
	BYTE	GetApplySyncAlpha(void);


	// WS_EX_LAYERED 설정
	void	EnableWindowLayered(bool bEnable, bool bReDraw);


	// pImage로 윈도우 레이어 업데이트
	// BNC_BaseFloating에서 사용시 m_dwVarSize, m_szOffset 무시됨
	bool	SetLayerCDC(CDC *pLayerCDC, CSize szBitmap);
	bool	SetLayerBitmap(CBitmap *pBitmapPtr);
	bool	SetLayerBitmapEx(CBitmap *pBitmapPtr, CSize szStretch);
	bool	SetLayerImage(Gdiplus::Image *pImagePtr, CPoint ptImage, CSize szImage);
	bool	SetLayerImageEx(Gdiplus::Image *pImagePtr, CPoint ptImage, CSize szImage, CSize szStretch);


protected:
	void	SetLayeredWindowAttributesEx(BYTE btAlpha);


protected:
	void	ResetLayerInfo(void);
	bool	UpdateLayerCDC(CDC* pDC, CSize szBitmap, BYTE btAlpha);
	bool	UpdateLayerBitmap(CBitmap *pBitmapPtr, CSize szBitmap, BYTE btAlpha);
	bool	UpdateLayerBitmapEx(CBitmap *pBitmapPtr, CSize szBitmap, CSize szStretch, BYTE btAlpha);
	bool	UpdateLayerImage(Gdiplus::Image *pImagePtr, CPoint ptImage, CSize szImage, BYTE btAlpha);
	bool	UpdateLayerImageEx(Gdiplus::Image *pImagePtr, CPoint ptImage, CSize szImage, CSize szStretch, BYTE btAlpha);

	BOOL	UpdateLayeredWindowEx(CDC* pDCDst, POINT *pptDst, SIZE *psize,
								  CDC* pDCSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);


public:
	virtual void	OnUpdateWindowRgn(int iWidth, int iHeight);


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 옵션 : Sync Visible, Enable Window
	////////////////////////////////////////////////////////////////////////////////////////////////
private:
	// 팝업의 Visible, Enable 상태와 동기화 시킬 윈도우
	set<BNC_BaseDialog*>	m_sSyncVisibleDlg;
	CRITICAL_SECTION			m_csSyncVisible;
	BOOL						m_bVisibleSyncState;

	set<BNC_BaseDialog*>	m_sSyncEnableDlg;
	CRITICAL_SECTION			m_csSyncEnable;
	BOOL						m_bEnableSyncState;


public:

	// 일시적인 사용설정
	// ex) 부모 윈도우가 데스크톱이 아닌 모달리스에서
	//  Enable 상태가 변경되면 부모 상태도 같이 변경되는데
	// 부모의 DisableOverlay와 등록된 동기 윈도우의 변경을 원치 않을 때
	// 일시적으로 false로 변경후 true로 되돌려서 사용
	bool	m_bUseVisibleSync;
	bool	m_bUseEnableSync;



private:
	// 동기화 다이얼로그 추가 제거
	bool	RegSyncVisible(bool bInsert, BNC_BaseDialog* pSyncDlg);
	bool	RegSyncEnable(bool bInsert, BNC_BaseDialog* pSyncDlg);


public:
	void	ResetSyncVisible(bool bOldHide);


	// OnShowWindow 동기화
	void	ShowWindowSync(BOOL bShow);


	// OnEnable 동기화
	void	EnableWindowSync(BOOL bEnable);



	////////////////////////////////////////////////////////////////////////////////////////////////
	// 옵션 : current를 blocking 시키기 위한 모달 사용시
	////////////////////////////////////////////////////////////////////////////////////////////////

private:
	BNC_BaseModal*	m_pBlockingModal;


public:
	INT_PTR	RunCallModal(BNC_BaseModal &Modal, bool bUseOverlay = false, BYTE btOverlayAlpha = 20, COLORREF clrOverlayBk = RGB(0, 0, 0));
	bool	EndCallModal(BNC_BaseModal &Modal);


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 옵션 : 기타
	////////////////////////////////////////////////////////////////////////////////////////////////

	// 마우스 휠 이벤트 다이렉트 전달 클라이언트 등록
	// 우선순위 : g_pCapture->m_pCaptureClient
private:
	BNC_BaseClient* m_pNotifyMouseWhell;

public:
	__declspec(deprecated) void SetNotifyMouseWhell(BNC_BaseClient* pNotify);



	////////////////////////////////////////////////////////////////////////////////////////////////
	// Fake modal
	////////////////////////////////////////////////////////////////////////////////////////////////
protected :
	shared_ptr<BNC_FakeModal> m_ActiveModal;

public :
	bool BeginFakeModalLoop(shared_ptr<BNC_FakeModal> pModal, UINT nDialogID = 0);
	void EndFakeModalLoop(BNC_FakeModal* pCallChild);
	void BreakFakeModalLoop(void);



	// TEST
protected:
	HDWP m_hdwp;

public:
	HDWP GetHDWP(void);



	////////////////////////////////////////////////////////////////////////////////////////////////
	// Overriding (정의 메시지)
	////////////////////////////////////////////////////////////////////////////////////////////////
private:
	virtual LRESULT OnDpiChange(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDisplayChange(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageSystray(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageContextMenu(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageForeground(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnCloseBlock(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDestroyBlock(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageClient(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageNotify(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageButton(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageCombo(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageEdit(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageList(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageProgress(WPARAM wParam, LPARAM lParam);
	virtual LRESULT	OnMessageScroll(WPARAM wParam, LPARAM lParam);
	virtual LRESULT	OnMessageSlider(WPARAM wParam, LPARAM lParam);
	virtual LRESULT	OnMessageTab(WPARAM wParam, LPARAM lParam);
	virtual LRESULT	OnMessageTree(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageFButton(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageHtmlWebEvent(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageRedraw(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMessageTransparent(WPARAM wParam, LPARAM lParam);
	virtual void OnTransparentUpdate(TransparentStep step, BYTE btAlpha, BYTE btMin, BYTE btMax, float fRatio);

	
public :
	// TEMP
	BYTE UpdateTransparent(TransparentStep step, BYTE btAlpha, BYTE btMin, BYTE btMax, float fRatio);


	////////////////////////////////////////////////////////////////////////////////////////////////
	// Overriding
	////////////////////////////////////////////////////////////////////////////////////////////////
private:
	virtual bool OnCreate(void);
	virtual void OnCreateDefaultPos(void);			// m_bIsMaximize, m_rcDefaultWnd 재설정 필요시
	virtual void OnUpdateSize(int cx, int cy);
	virtual	bool OnDraw(CDC* pMemDC, CDC* pResDC);
	virtual void OnDrawEnd(void);
	virtual void UpdateClickEdge(void);
	virtual void OnUpdateWindowStatus(BNE_POPUP_STATUS status);		// 창의 상태가 변경됨


	// 다이얼로그 생성시 추가 지정 윈도우 스타일 지정
	virtual DWORD	GetInitWindowStyle(void);
	virtual DWORD	GetInitWindowStyleEx(void);
	virtual UINT	GetInitWindowPosFlags(void);


	// 응용 단계에서 윈도우별 동작 상태를 지정할 필요가 있을 때 사용
	virtual DWORD	GetApplicationUserData(void);


public:
	// 루트 클라이언트의 m_bDrawPassPopup를 true로 설정할 때 그리기 작업 대신 수행
	virtual bool OnDrawRootClient(CDC* pMemDC, CDC* pResDC);


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 내부 처리
	////////////////////////////////////////////////////////////////////////////////////////////////
private:
	void	DefaultParams(void);	// 변수 초기화 (생성자 호출)
	void	Initialize(bool bAppWindow, bool bUseResizing, bool bChildDialog);
	UINT	CheckHitTest(CPoint point);
	void	SetClickEdge(bool bClick);
	void	UpdateCursor(UINT uiHitTest);
	void	UpdateClient(int cx, int cy);
	void	UpdateWindowPos(WINDOWPOS* lpwndpos);


	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
protected:
	void	DrawOutsideLine(CDC* pMemDC, COLORREF color);
	void	DrawOutsideLine(CDC* pMemDC);
	void	SetRoundCorner(bool bTop, bool bBottom, int iRadious, BOOL bRedraw);
	CRect	GetCenterArea(CWnd* pTarget, int cx, int cy, bool bAdjustWorkIn);
	CRect	CheckMonitorArea(CRect &rcTarget);
	void	NotifyRootClient(BNE_POPUP_STATUS status);
	void	SetWindowLongEx(int index, bool bInsert, DWORD dwStyle);

protected:
	void MouseMove(UINT &nFlags, CPoint &point);
	void LButtonDown(UINT &nFlags, CPoint &point);
	void LButtonUp(UINT &nFlags, CPoint &point);
	void LButtonDblClk(UINT &nFlags, CPoint &point);


	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
public:
	// if(pParentWnd == GetDesktopWindow())
	// {
	//		일반 z-order
	//		DestroyWindow() 처리 필요
	// }
	// else
	// {
	//		메인 윈도우 종속
	//		- 항상 메인 윈도우 위에 위치			
	//		- 시스템 명령에 반응 (minimize, restore)
	//		- 메인 죽을 때 소멸
	// }
	bool	create(UINT uiDialogID, CRect rcWindow, bool bUseCaption, bool bUseResizing, CWnd* pParentWnd = NULL, bool bChildDialog = false);


	// 등록된 root client 반환
	HWND	GetRootClient(void);


	void	Draw(CDC* pDC = NULL, RECT *prcClip = NULL, bool bChkVisible = true);
	void	EnableTopmost(bool bEnable);
	bool	IsEnableTopmost(void) const;
	void	ShowDefaultPos(void);


	// 보여지는 상태
	// 0(Hide)
	// 1(Iconic)
	// 2(Zoom)
	// 3(Show)
	UINT	GetVisiableStatus(void);


	// 동기화 설정 다이얼로그 등록/해제
	// dwFlags : 동기 범위( BND_SYNC_ )
	// return : 설정된 결과 ( BND_SYNC_ )
	DWORD	RegSyncDialog(bool bInsert, BNC_BaseDialog* pSyncDlg, DWORD dwFlags);



	// 외부에서 특정 윈도우(hTarget)에 맞게 등장 시킬 필요가 있을 때 호출
	// return true 반환시 내부에서 처리되는 것으로 판단함
	virtual bool ShowDialog(const CWnd* pAfterInsert, HWND hTarget, DWORD dwFixPoint, CPoint ptOffset, HWND hOption);
	void ShowDialogDefault(bool bActivate = true,
						   const CWnd* pAfterInsert = NULL,
						   HWND hTarget = NULL,
						   DWORD dwFixPoint = BND_FIXPOINT_CC,
						   CPoint ptOffset = CPoint(0, 0),
						   double lfAnimation = 200);


	// ShowDialog 오버라이딩 후 내부 호출
	// pt위치에 윈도우 보임 (않보이면 보이고, 보이면 foreground 시킴)
	void	ShowAnimation(const CWnd* pAfterInsert, CPoint &pt, double lfAnimateDelay);


	// 자동 삭제 설정 여부
	bool	IsAutoDelete(void);
	

	static	void SetForegroundWindowEx(HWND hWnd);
	void	SetForegroundWindowEx(void);
	CRect	GetDefaultWnd(void) const;


	// resizing 옵션 수정
	__declspec(deprecated) void EnableResizing(bool bEnable);


	// BorderessProc On/Off (생성시 초기화 되었을 경우만 동작함)
	bool	EnableBorderessProc(bool bEnable);


	// 최대화상태면 이전크기 반환, 최대화 아니면 최종 windowpos 상태 반환
	CRect	GetNormalRect(void);


	// 현재반영된 hittest 반환
	UINT	GetHitTest(void);


	// 최대화 (모니터 전체화면 포함) 체크
	bool IsZoomedEx(void);


	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

public:
	bool IsActivate(void) const 
	{
		return m_bIsActivate;
	};




	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	// 생성당시 스레드 ID
	// 동기가 필요한 부분에서 사용

protected :
	DWORD m_dwThreadID;
	CRect m_rcSetWindowEx;	// SetWindowPosEx 파라미터

public:
	DWORD GetThreadID(void);
	UINT GetSyncWindowPosFlag(void);
	UINT GetSyncWindowPosFlags(DWORD dwFlags);
	void SetWindowPosEx(const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);



	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////


public:
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);


protected:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();

public :
	virtual BOOL DestroyWindow();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();

	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);

	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnClose();

	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);

	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcDestroy();
	afx_msg void OnCompositionChanged();
	afx_msg void OnNcRenderingChanged(BOOL bIsRendering);

	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnEnterSizeMove();
	afx_msg void OnExitSizeMove();
};
