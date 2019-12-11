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


	bool	Open(CString strPath);	// strPath = ":memory:" 지정시 메모리 DB로 사용
	bool	Close(void);


	bool	GetTableInfo(_In_ CString strTable,
						 _Ret_ std::vector<CString> &vCol,
						 _Ret_ int &iRowCount);
	

	// vColumns[0]은 key로 고정함
	bool	CreateTable(CString strTable, vector<CString> &vFieldName);
	bool	DeleteTable(CString strTable);
	

	// 일괄 처리시 사용
	// Begin~Commit 사이에는 반드시 한 번 이상의 query가 수행되어야 함
	// 미수행시 close에서 에러 -_-
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

	
	// 컬럼은 테이블 생성시 고정될 수 있도록 하고 부득이한 경웨 사용
	bool	InsertField(CString strTable, CString strColumn);
	bool	DeleteField(CString strTable, CString strColumn);	// DROP 지원않함


	// strCondition == _T("")면 전체 삭제함
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


	// query문 직접 작성후 호출용
	// cbQueryResult가 있을 경우 호출지점에서 쿼리 결과 확인하여 사용 cbQueryResult 반환값을 QueryDirect 반환값으로 사용함

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
