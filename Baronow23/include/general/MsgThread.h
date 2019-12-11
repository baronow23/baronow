#pragma once

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
// non export
class MsgThread : public CWinThread
{
	DECLARE_DYNCREATE(MsgThread)

protected:
	MsgThread();           // 동적 만들기에 사용되는 protected 생성자입니다.
	
public:
	virtual ~MsgThread();

private :
	bool	m_bInitialize;
	CWnd	m_ProcWnd;

public :
	bool	IsInitialize(void);
	HWND	GetProcHwnd(void);
	

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();


protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnIdle(LONG lCount);


private:
	//void OnMessageTest(WPARAM wParam, LPARAM lParam);
};
//////////////////////////////////////////////////////////////////////////////////////////
};


// MsgProcedure
namespace baro { namespace helper {
//////////////////////////////////////////////////////////////////////////////////////////
class BN23_CLASS MsgProcedure
{
public :
	MsgProcedure(bool bCreateInstance = true);
	virtual ~MsgProcedure(void);

private :
	HANDLE	m_hThread;
	HWND	m_hProcWnd;
	WNDPROC	m_pOldProc;

protected:
	CRITICAL_SECTION m_csProc;


public :
	bool	m_bNetConnected;


private :
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static bool AssertValid(MsgProcedure *pProc, HWND hWnd);


private :
	// 서브클래스에서 처리않할 경우 return false 반환 (oldProc처리)
	virtual bool DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) = 0;


	// CreateInstance/ReleaseInstance 처리 성공시 호출
	// MsgProcedure(ture)일 경우 서브클래스 생성전으로 호출 않됨 유의!!
	virtual void OnCreateInstance(void) {};
	virtual void OnReleaseInstance(void) {};


	// 스레드 소멸시도 직전 아직 처리 윈도우가 살아있기 마지막에 호출
	virtual void OnPreDestoryProcWindow(void) {};


	// 인스턴스 종료시 남아있는 메시지 처리가 필요할 때 처리
	// ex) 사용자 메시지 파라미터에서 동적 메모리 해제가 필요한 경우등
	virtual void OnDisposalMessage(MSG &) {};


public :
	bool	CreateInstance(int nPriority = THREAD_PRIORITY_NORMAL);
	void	ReleaseInstance(void);


public :
	HANDLE	GetThreadHandle(void);
	DWORD	GetThreadID(void);
	HWND	GetWindowHwnd(void);
	bool	UpdateNetState(void);
	
	LRESULT SendWndMessage(UINT message, WPARAM wParam, LPARAM lParam);
	BOOL	PostWndMessage(UINT message, WPARAM wParam, LPARAM lParam);


	// MsgProcedure 상속 클래스에서 스레드메시지 맵 사용이 않되서 일단 막음
	__declspec(deprecated)
	BOOL	PostThreadMessage(UINT message, WPARAM wParam, LPARAM lParam);


};
//////////////////////////////////////////////////////////////////////////////////////////
}; };