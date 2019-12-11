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

	 
	// �����Դϴ�.
public:
	BNC_BaseDialog(void);
	BNC_BaseDialog(UINT nDialogID, CWnd* pParent = NULL);
	virtual ~BNC_BaseDialog(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.


	////////////////////////////////////////////////////////////////////////////////////////////////
	// static
	////////////////////////////////////////////////////////////////////////////////////////////////

public:
	// Overlay, Anmation�� ���� ȿ���� ����� Dialog ID 
	// CWinApp::Initinstance()���� �ݵ�� ���� �� �� 
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


	// ���� app���� OnDisplayChange ���Ž� �ѹ� ȣ��
	static void				UpdateDisplayChange(WPARAM wParam, LPARAM lParam);



	// BNC_BaseDialog�� ��ӹ��� ���̾�α׸� ���̱�
	// Ư�� ���̾�α��� ����� ��ġ ����� ����� ���� üũ ����
	static void ShowSyncDialog(BNC_BaseDialog*	pDialog,
							   double lfAnimation = 200,
							   const CWnd* pAfterInsert= NULL,
							   HWND		hTarget		= NULL,
							   DWORD	dwFixPoint	= BND_FIXPOINT_CC,
							   CPoint	ptOffset	= CPoint(0, 0));
	

	// rcTarget�� dwFixPoint��ġ�� szWnd + ptOffset ����� ����� ptWnd ��ȯ
	// ptWnd + szWnd�� ��� ��ġ�� ��ü ����� �ȿ� ���ԵǾ� ���� ������ false ��ȯ
	// prcMonitor�� ������ prcMonitor�� ������
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
	// ���ο��� ������Ʈ�Ǵ� �׸�, 
	// �ܺ� ���� ���� (��� Ŭ���� ����)
	// ������ Get �޼��� ����� �������� �б�����θ� ����� ��
	////////////////////////////////////////////////////////////////////////////////////////////////
NCTYPE_READONLY:
	BNE_DIALOG_TYPE	m_DlgType;

	// create()���� bChildDialog�� true�� ����� ��, GetParent() ����
	// create()���� ������ pParentWnd�� �޶����Ƿ� ������ ����
	CWnd*	m_pInitParent;


	// ��޷� �ش� �����츦 ��Ͻ�Ų ������
	CWnd*	m_pCurBlockWnd;


	// ���̾�α� �Ӽ�
	bool	m_bIsModaless;		// Ÿ��
	bool	m_bAppWindow;
	bool	m_bUseResizing;
	bool	m_bEnableTopmost;
	bool	m_bChildWindow;
	DWORD	m_dwInitStyle;
	DWORD	m_dwInitStyleEx;
	const CWnd*	m_pInitWndInsertAfter;


	// ����
	bool	m_bOnClose;
	bool	m_bIsCreate;
	bool	m_bIsActivate;
	bool	m_bIsMaximize;
	bool	m_bIsMaximizeEx;
	BOOL	m_bDwmComposited;


	// ũ��
	CSize	m_szClient;
	CSize	m_szWindowMin;
	CSize	m_szWindowMax;		// �⺻�� : s_szMaxMonitorRes ���
	CRect	m_rcDefaultWnd;
	CRect	m_rcOutside;
	CRect	m_rcMaximizeBefore;	// �ִ�ȭ, �ִ�ȭȮ�� ��� ������ ������ ��ġ
	CRect	m_rcLastVisible;	// ���� ������ ��ġ (iconic ����)
	BOOL	m_bEnterMoveZoom;	// OnEnterSizeMove ȣ���� IsZoom ����


	BNC_BorderessProc	m_BorderessProc;
	bool				m_bUsingBorderessProc;
	DWORD				m_dwIgnoreBorderessFlags;


protected:
	// �˾��� ���� ����(UpdatePopupStatus) �� ��Ŀ�� ���� ���� ��Ʈ Ŭ���̾�Ʈ ���
	BNC_BaseClient*		m_pRootClientPtr;
	bool				m_bAutoRootClientPos; // �׻� �׵θ� ���� ��ġ�� m_pRootClientPtr ��ġ


	// ���������� DestroyWindow���� �ڵ� ���� ���� ����
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
	CSize	m_szNCLBtnDownSize;			// NCLBtnDown�� ������ ũ��
	bool	m_bSucceedLastMagnetEffect;	// �ڼ�ȿ�� �Ϸ�(m_bEnableMagnetEffect == true �� ��)


	bool	m_bClickEdge;				// ������¡ ���� Ŭ������
	bool	m_bPauseCapture;
	UINT	m_uiHitTest;				// ���콺 Ŭ���� WM_NCLBUTTONDOWN ���� ����



	////////////////////////////////////////////////////////////////////////////////////////////////
	// �ɼ� : �⺻
	////////////////////////////////////////////////////////////////////////////////////////////////

public:
	bool		m_bUseStretchCaption;		// â�� ��� ������ ĸ������ ������� ����
	int			m_iUseCaptionHeight;		// â�̵��� ������ ĸ�ǹ� ũ��(m_bUseStretchCaption�� false �� ��)
	bool		m_bIgnoreAltF4;				// Alt + F4 ���� ���� (BNC_BaseModal������ m_bIgnoreExitKey ture�� ������)
	bool		m_bUsingEscClose;			// esc close��뿩�� (��޸��������� ����� ��)
	bool		m_bEnableMagnetEffect;		// �ڼ�ȿ�� ��뿩�� (default : false)
	bool		m_bClickAtivateRedraw;		// ���콺 Ŭ������ Ȱ��ȭ�� OnRedraw �߻� ��ų�� ����

	CSize		m_szWindowDefault;			// �ʱ� ������ ũ��
	COLORREF	m_colorEdge1;
	COLORREF	m_colorEdge2;
	COLORREF	m_colorBG;
	bool		m_bDrawEdge;
	UINT		m_iBltCount;


	// ����� Ŀ���� ���
	DWORD		m_dwUserState;


	// ������ â �̵��ð� üũ
	baro::Performance	m_LastWindowPosChanged;


	////////////////////////////////////////////////////////////////////////////////////////////////
	// �ɼ� : System Tray
	////////////////////////////////////////////////////////////////////////////////////////////////

protected:
	HICON			m_hIcon;
	NOTIFYICONDATA	m_SystrayData;
	UINT m_uiTaskbarCreated;	// ������ Ž���� ����� üũ

public:
	void	SystemTrayInsert(LPCTSTR strTip, UINT uiIconRes, UINT uiMsgID, CString strGUID);
	void	SystemTrayDelete(void);
	void	SystemTrayModify(UINT uiIconRes);
	void	SystemTrayCheckRestore(void);
	const NOTIFYICONDATA* GetSystemTrayData(void);
	

	////////////////////////////////////////////////////////////////////////////////////////////////
	// �ɼ� : Animation
	////////////////////////////////////////////////////////////////////////////////////////////////

protected:
	// ���� �ִϸ��̼�
	BNC_TransparentAnimation	m_TransparentAnimation;

	// �̵� �ִϸ��̼� : Animation(false~) ȣ�� �����ġ�� DC
	CRect m_rcAnimation;
	CDC	 m_DcAnimation;


public:
	// ���� �ִϸ��̼� ����
	void	RunTransparentAnimation(bool bShow, double lfDelay = 100, const CWnd* pAfterInsert = NULL, bool bShowActivate = true);
	bool	IsAnimationVisible(void);
	virtual void OnFirstTransparentAnimation(BYTE btAlpha);
	//virtual void UpdateTransparentAnimationRange(OUT BYTE &btMin, OUT BYTE &btMax);


	// �̵� �ִϸ��̼�
	void	Animation(bool bAvtive, CPoint *pptBegin = NULL, CPoint *pptEnd = NULL, double lfMilliSec = 200);
	void	CopyDC(OUT CDC *pCopyDC);


	// �۾�ǥ���� �÷��� ȿ��
	void RunFlashEffect(UINT uiCount = 3);


	////////////////////////////////////////////////////////////////////////////////////////////////
	// �ɼ� : Sync Position, Z-order
	////////////////////////////////////////////////////////////////////////////////////////////////
private:
	// �˾��� ���ӵǾ� ������ ũ�⳪ ��ġ�� ���� �� ������ ����ȭ ������ ������� ������ ����� ������ ��ġ
	vector<BNC_BaseDialog*>	m_vSyncPosition;
	CRITICAL_SECTION				m_csSyncPosition;
	WINDOWPOS						m_wndposUpdate;
	WINDOWPOS						m_wndposCheck;
	

	static CPoint s_ptHidePos;			// â�� ������ �� ��ǥ(�ý���) : ����Ʈ (-32000, -32000)

public:
	static UINT s_uiAnimationDelay;		// �ִϸ��̼� �ð� : ����Ʈ 200


private:
	// Z-order ����ȭ
	vector<BNC_BaseDialog*>	m_vSyncZorder;
	CRITICAL_SECTION				m_csSyncZorder;


private:
	// ������Ʈ
	void	UpdateSyncPosition(WINDOWPOS* lpwndpos);
	void	UpdateSyncZorder(void);


public :
	void	UpdateSyncPosition(void);


private :
	// show/hide sync
	void	OnShowWindowSync(BOOL bShow, WINDOWPOS* lpwndpos);


private:
	// �߰�, ����
	bool	RegSyncPosition(bool bInsert, BNC_BaseDialog* pSyncDlg);
	bool	RegSyncZorder(bool bInsert, BNC_BaseDialog* pSyncDlg);

	

	////////////////////////////////////////////////////////////////////////////////////////////////
	// �ɼ� : Sync Position (Client)
	////////////////////////////////////////////////////////////////////////////////////////////////
public:
	BNS_SyncPos	m_SyncPos;


public:
	// �θ��������� ��ġ, ũ�⿡ ���� ����ȭ ��ų ����
	// pAfterInsert ��� ����
	// z-order�� RegSyncPosition()�� ��ϵ� ���� ����
	// ptOffset, szOffset�� ��밪
	void	SetSyncPos(DWORD dwFixPoint, CPoint ptOffset, DWORD dwVarSize, CSize szOffset, CWnd* pAfterInsert = NULL, bool bUpdate = true);



protected:
	void	GetUpdateSyncPos(int x, int y, int cx, int cy, OUT CPoint &pt, OUT CSize &sz, OUT UINT &uiFlags);


	// x, y, cx, cy�� ����ȭ ��ų ������ ������
	// pAfterInsert �������� InitFloating() �Ķ���� pAfterInsert ���
	void	SetSyncWindowPos(HDWP hdwp, const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT uiAddFlags);


	// SetSyncWindowPos�ȿ��� GetUpdateSyncPos ����� ������ �ʿ��� �� ȣ��
	virtual bool OnSyncWindowPos(HDWP hdwp, const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT uiAddFlags);



	////////////////////////////////////////////////////////////////////////////////////////////////
	// �ɼ� : �� �˾��� �ϳ��� ���� �� �ִ� ���� �÷���
	////////////////////////////////////////////////////////////////////////////////////////////////
	//private:
protected:
	BNC_BaseFloating*		m_pDisableOverlay;		// EnableWindow(FALSE) ���� ��������
	BNC_FloatingMessage*	m_pSystemMessage;
	BNC_BaseFloating*		m_pInactiveOverlay;

	
private:
	// Z-order ����
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

	// m_pDisableOverlay ���û��� �޽��� zorder�� ���� �������� ��� (���̾�α� �������� ��ȿ)
	bool		m_bSysMsgLastZorder;

	bool		m_bHideSysMsgOnMinMax;	// �ּ�, �ִ�ȭ ������ �� ���� 
	bool		m_bHideSysMsgOnVisible;	// show/hide ����� �� ����
	

public:
	// ���̾�α� ������ ��뿩�� �����Ǿ�� �� 
	bool		m_bUseDisableOverlay;	// ���� ���� ������ Enable���� ���忩�� ������)
	bool		m_bUseSystemMessage;	// ���� ���� ���� ��ȭ ����
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
	// �ɼ� : Window Layered
	////////////////////////////////////////////////////////////////////////////////////////////////
private:
	// �˾��� ���ӵǾ� ������ ������ ����Ǿ��� �� ����ȭ ó���� ������
	set<BNC_BaseDialog*>	m_sSyncBlendingDlg;
	CRITICAL_SECTION			m_csSyncBlending;


protected:
	bool		m_bUseColorkey;			// Į��Ű ��� ����
	COLORREF	m_colorTransparent;		// m_bUseColorkey�� true�� �� ������ colorKey


	// ����
	// m_btSyncAlpha = 128(50%)�̰� m_btAlpha�� 25(10%)�� ���� ���Ĵ� 255 * 0.5 * 0.1
	BYTE		m_btSyncAlpha;			// ����ȭ �� ���� �������� ���İ�
	BYTE		m_btAlpha;				// ���� ������ SetTransparent ����Ǹ� m_btSyncAlpha�� �Ѿ �� ����



NCTYPE_READONLY:
	CRITICAL_SECTION	m_csSyncLayer;
	bool				m_bUpdateLayeredWindow;	// UpdateLayeredWindow() ��뿩��
	Gdiplus::Image*		m_pLayerImagePtr;		// ����� �̹���
	CPoint				m_ptLayerImagePos;		// ���ҽ��� ��ġ
	CSize				m_szLayerImageSize;
	CSize				m_szLayerImageStretch;

	CDC*				m_pLayerCDC;			// SetLayerCDC
	CSize				m_szLayerCDC;

	CBitmap*			m_pLayerBitmapPtr;		// SetLayerBitmap
	CSize				m_szLayerBitmapStretch;



private:
	// ���� ó�� ����ȭ ��ų ���̾�α� �߰� ����
	bool	RegSyncBlending(bool bInsert, BNC_BaseDialog* pSyncDlg);


public:
	// ���� ���� (���̾�� ������ üũ�� ����, m_bUseTransparent Ȱ��)
	void				SetTransparentAnimationRange(BYTE btMin, BYTE btMax);
	pair<BYTE, BYTE>	GetTransparentAnimationRange(void);
	void	SetSyncAlpha(BYTE btSync);
	BYTE	SetAlpha(BYTE btAlpha, bool bCheck = false);		// Sync ����� ��� ��ȯ
	BYTE	GetAlpha(void);
	BYTE	GetApplySyncAlpha(void);


	// WS_EX_LAYERED ����
	void	EnableWindowLayered(bool bEnable, bool bReDraw);


	// pImage�� ������ ���̾� ������Ʈ
	// BNC_BaseFloating���� ���� m_dwVarSize, m_szOffset ���õ�
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
	// �ɼ� : Sync Visible, Enable Window
	////////////////////////////////////////////////////////////////////////////////////////////////
private:
	// �˾��� Visible, Enable ���¿� ����ȭ ��ų ������
	set<BNC_BaseDialog*>	m_sSyncVisibleDlg;
	CRITICAL_SECTION			m_csSyncVisible;
	BOOL						m_bVisibleSyncState;

	set<BNC_BaseDialog*>	m_sSyncEnableDlg;
	CRITICAL_SECTION			m_csSyncEnable;
	BOOL						m_bEnableSyncState;


public:

	// �Ͻ����� ��뼳��
	// ex) �θ� �����찡 ����ũ���� �ƴ� ��޸�������
	//  Enable ���°� ����Ǹ� �θ� ���µ� ���� ����Ǵµ�
	// �θ��� DisableOverlay�� ��ϵ� ���� �������� ������ ��ġ ���� ��
	// �Ͻ������� false�� ������ true�� �ǵ����� ���
	bool	m_bUseVisibleSync;
	bool	m_bUseEnableSync;



private:
	// ����ȭ ���̾�α� �߰� ����
	bool	RegSyncVisible(bool bInsert, BNC_BaseDialog* pSyncDlg);
	bool	RegSyncEnable(bool bInsert, BNC_BaseDialog* pSyncDlg);


public:
	void	ResetSyncVisible(bool bOldHide);


	// OnShowWindow ����ȭ
	void	ShowWindowSync(BOOL bShow);


	// OnEnable ����ȭ
	void	EnableWindowSync(BOOL bEnable);



	////////////////////////////////////////////////////////////////////////////////////////////////
	// �ɼ� : current�� blocking ��Ű�� ���� ��� ����
	////////////////////////////////////////////////////////////////////////////////////////////////

private:
	BNC_BaseModal*	m_pBlockingModal;


public:
	INT_PTR	RunCallModal(BNC_BaseModal &Modal, bool bUseOverlay = false, BYTE btOverlayAlpha = 20, COLORREF clrOverlayBk = RGB(0, 0, 0));
	bool	EndCallModal(BNC_BaseModal &Modal);


	////////////////////////////////////////////////////////////////////////////////////////////////
	// �ɼ� : ��Ÿ
	////////////////////////////////////////////////////////////////////////////////////////////////

	// ���콺 �� �̺�Ʈ ���̷�Ʈ ���� Ŭ���̾�Ʈ ���
	// �켱���� : g_pCapture->m_pCaptureClient
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
	// Overriding (���� �޽���)
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
	virtual void OnCreateDefaultPos(void);			// m_bIsMaximize, m_rcDefaultWnd �缳�� �ʿ��
	virtual void OnUpdateSize(int cx, int cy);
	virtual	bool OnDraw(CDC* pMemDC, CDC* pResDC);
	virtual void OnDrawEnd(void);
	virtual void UpdateClickEdge(void);
	virtual void OnUpdateWindowStatus(BNE_POPUP_STATUS status);		// â�� ���°� �����


	// ���̾�α� ������ �߰� ���� ������ ��Ÿ�� ����
	virtual DWORD	GetInitWindowStyle(void);
	virtual DWORD	GetInitWindowStyleEx(void);
	virtual UINT	GetInitWindowPosFlags(void);


	// ���� �ܰ迡�� �����캰 ���� ���¸� ������ �ʿ䰡 ���� �� ���
	virtual DWORD	GetApplicationUserData(void);


public:
	// ��Ʈ Ŭ���̾�Ʈ�� m_bDrawPassPopup�� true�� ������ �� �׸��� �۾� ��� ����
	virtual bool OnDrawRootClient(CDC* pMemDC, CDC* pResDC);


	////////////////////////////////////////////////////////////////////////////////////////////////
	// ���� ó��
	////////////////////////////////////////////////////////////////////////////////////////////////
private:
	void	DefaultParams(void);	// ���� �ʱ�ȭ (������ ȣ��)
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
	//		�Ϲ� z-order
	//		DestroyWindow() ó�� �ʿ�
	// }
	// else
	// {
	//		���� ������ ����
	//		- �׻� ���� ������ ���� ��ġ			
	//		- �ý��� ��ɿ� ���� (minimize, restore)
	//		- ���� ���� �� �Ҹ�
	// }
	bool	create(UINT uiDialogID, CRect rcWindow, bool bUseCaption, bool bUseResizing, CWnd* pParentWnd = NULL, bool bChildDialog = false);


	// ��ϵ� root client ��ȯ
	HWND	GetRootClient(void);


	void	Draw(CDC* pDC = NULL, RECT *prcClip = NULL, bool bChkVisible = true);
	void	EnableTopmost(bool bEnable);
	bool	IsEnableTopmost(void) const;
	void	ShowDefaultPos(void);


	// �������� ����
	// 0(Hide)
	// 1(Iconic)
	// 2(Zoom)
	// 3(Show)
	UINT	GetVisiableStatus(void);


	// ����ȭ ���� ���̾�α� ���/����
	// dwFlags : ���� ����( BND_SYNC_ )
	// return : ������ ��� ( BND_SYNC_ )
	DWORD	RegSyncDialog(bool bInsert, BNC_BaseDialog* pSyncDlg, DWORD dwFlags);



	// �ܺο��� Ư�� ������(hTarget)�� �°� ���� ��ų �ʿ䰡 ���� �� ȣ��
	// return true ��ȯ�� ���ο��� ó���Ǵ� ������ �Ǵ���
	virtual bool ShowDialog(const CWnd* pAfterInsert, HWND hTarget, DWORD dwFixPoint, CPoint ptOffset, HWND hOption);
	void ShowDialogDefault(bool bActivate = true,
						   const CWnd* pAfterInsert = NULL,
						   HWND hTarget = NULL,
						   DWORD dwFixPoint = BND_FIXPOINT_CC,
						   CPoint ptOffset = CPoint(0, 0),
						   double lfAnimation = 200);


	// ShowDialog �������̵� �� ���� ȣ��
	// pt��ġ�� ������ ���� (�ʺ��̸� ���̰�, ���̸� foreground ��Ŵ)
	void	ShowAnimation(const CWnd* pAfterInsert, CPoint &pt, double lfAnimateDelay);


	// �ڵ� ���� ���� ����
	bool	IsAutoDelete(void);
	

	static	void SetForegroundWindowEx(HWND hWnd);
	void	SetForegroundWindowEx(void);
	CRect	GetDefaultWnd(void) const;


	// resizing �ɼ� ����
	__declspec(deprecated) void EnableResizing(bool bEnable);


	// BorderessProc On/Off (������ �ʱ�ȭ �Ǿ��� ��츸 ������)
	bool	EnableBorderessProc(bool bEnable);


	// �ִ�ȭ���¸� ����ũ�� ��ȯ, �ִ�ȭ �ƴϸ� ���� windowpos ���� ��ȯ
	CRect	GetNormalRect(void);


	// ����ݿ��� hittest ��ȯ
	UINT	GetHitTest(void);


	// �ִ�ȭ (����� ��üȭ�� ����) üũ
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
	// ������� ������ ID
	// ���Ⱑ �ʿ��� �κп��� ���

protected :
	DWORD m_dwThreadID;
	CRect m_rcSetWindowEx;	// SetWindowPosEx �Ķ����

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
