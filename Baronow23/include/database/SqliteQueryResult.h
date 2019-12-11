#pragma once


namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
class BN23_CLASS SqliteQueryResult
{
	friend class Sqlite;

private :
	SqliteQueryResult(void* pq);
	~SqliteQueryResult();

private :
	void *m_pQueryResult;

public :
	int numFields();

	int fieldIndex(LPCTSTR szField);
	LPCTSTR fieldName(int nCol);

	LPCTSTR fieldDeclType(int nCol);
	int fieldDataType(int nCol);

	LPCTSTR fieldValue(int nField);
	LPCTSTR fieldValue(LPCTSTR szField);

	int getIntField(int nField, int nNullValue=0);
	int getIntField(LPCTSTR szField, int nNullValue=0);

	double getFloatField(int nField, double fNullValue=0.0);
	double getFloatField(LPCTSTR szField, double fNullValue=0.0);

	LPCTSTR getStringField(int nField, LPCTSTR szNullValue=_T(""));
	LPCTSTR getStringField(LPCTSTR szField, LPCTSTR szNullValue=_T(""));

	const unsigned char* getBlobField(int nField, int& nLen);
	const unsigned char* getBlobField(LPCTSTR szField, int& nLen);

	bool fieldIsNull(int nField);
	bool fieldIsNull(LPCTSTR szField);

	bool eof();
	void nextRow();
	void finalize();
};
//////////////////////////////////////////////////////////////////////////////////////////
};

