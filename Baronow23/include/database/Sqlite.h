#pragma once

//#include "CppSqlite3U.h"
// return value : SQLITE_OK ~ SQLITE_DONE + CPPSQLITE_ERROR + BNSQL_ERR_PARAM
#define BNSQL_ERR_PARAM (1000 + 1)	// CPPSQLITE_ERROR = 1000


namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
class BN23_CLASS Sqlite
{
public:
	Sqlite();
	~Sqlite();

private :
	void*	m_pInterface;
	DWORD	m_dwLastError;


private :
	bool	ErrorParam(void);

	template <typename T>
	bool	Query(LPCTSTR lpszQuery, _Ret_ T &Result);
	bool	DML(LPCTSTR lpszQuery, _Ret_ int &iResult);


public :
	DWORD	GetLastError(void);
	CString GetLastErrorMessage(void);


	// strDeliter = _T(","), _T(" and ")
	CString MakeString(std::vector<CString> &vStr, CString strDelimeter);


	bool	Open(CString strPath);	// strPath = ":memory:" ������ �޸� DB�� ���
	bool	Close(void);


	bool	GetTableInfo(_In_ CString strTable,
						 _Ret_ std::vector<CString> &vCol,
						 _Ret_ int &iRowCount);
	

	// vColumns[0]�� key�� ������
	bool	CreateTable(CString strTable, vector<CString> &vFieldName);
	bool	DeleteTable(CString strTable);
	

	// �ϰ� ó���� ���
	// Begin~Commit ���̿��� �ݵ�� �� �� �̻��� query�� ����Ǿ�� ��
	// �̼���� close���� ���� -_-
	/*
		BeginTransaction();
		for(int i=0; i<10000; i++)
		{
			InsertColumn(...);
		}
		CommitTransaction();

	*/
	bool	BeginTransaction(void);
	bool	CommitTransaction(void);
	bool	RollbackTransaction(void);

	
	// �÷��� ���̺� ������ ������ �� �ֵ��� �ϰ� �ε����� ��� ���
	bool	InsertField(CString strTable, CString strColumn);
	bool	DeleteField(CString strTable, CString strColumn);	// DROP ��������


	// strCondition == _T("")�� ��ü ������
	bool	InsertRow(CString strTable, std::vector<CString> &vCol, std::vector<CString> &vVal, bool bTrace = true);
	bool	DeleteRow(CString strTable, CString strCondition = _T(""));



	// ex)
	// strSelect = "column1,column2"
	// strCondition = "(column3='3') and (column4='4' or column5='5')"
	bool	Select(_In_ CString strTable,
				   _Ret_ std::map<CString, std::vector<CString>> &mResult,
				   _In_ CString strSelect = _T(""),
				   _In_ CString strCondition = _T(""));


	// ex) 
	// strUpdate = "column1='value',column2='value'"
	// strCondition = "column1='condition'"
	bool	Update(_In_ CString strTable, _In_ CString strUpdate, _In_ CString strCondition);


	// query�� ���� �ۼ��� ȣ���
	// cbQueryResult�� ���� ��� ȣ���������� ���� ��� Ȯ���Ͽ� ��� cbQueryResult ��ȯ���� QueryDirect ��ȯ������ �����

	// ex)
	// bRet = QueryDirect("...", [](SqliteQueryResult&)
	// {
	//		..
	//		return bool;
	// });
	bool	QueryDirect(LPCTSTR lpszQuery, std::function<bool(SqliteQueryResult&)> cbQueryResult = nullptr);
	
	
};
//////////////////////////////////////////////////////////////////////////////////////////
};
