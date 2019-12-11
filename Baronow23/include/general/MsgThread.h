#pragma once

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
// non export
class MsgThread : public CWinThread
{
	DECLARE_DYNCREATE(MsgThread)

protected:
	MsgThread();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	
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
	// ����Ŭ�������� ó������ ��� return false ��ȯ (oldProcó��)
	virtual bool DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) = 0;


	// CreateInstance/ReleaseInstance ó�� ������ ȣ��
	// MsgProcedure(ture)�� ��� ����Ŭ���� ���������� ȣ�� �ʵ� ����!!
	virtual void OnCreateInstance(void) {};
	virtual void OnReleaseInstance(void) {};


	// ������ �Ҹ�õ� ���� ���� ó�� �����찡 ����ֱ� �������� ȣ��
	virtual void OnPreDestoryProcWindow(void) {};


	// �ν��Ͻ� ����� �����ִ� �޽��� ó���� �ʿ��� �� ó��
	// ex) ����� �޽��� �Ķ���Ϳ��� ���� �޸� ������ �ʿ��� ����
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


	// MsgProcedure ��� Ŭ�������� ������޽��� �� ����� �ʵǼ� �ϴ� ����
	__declspec(deprecated)
	BOOL	PostThreadMessage(UINT message, WPARAM wParam, LPARAM lParam);


};
//////////////////////////////////////////////////////////////////////////////////////////
}; };