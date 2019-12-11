#pragma once

/*
namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
class BN23_CLASS SqliteBinary : public baro::CriticalSection
{
public :
	enum class TableType
	{
		MainTable,
		ConfTable,
	};

public:
	SqliteBinary();
	~SqliteBinary();

private :
	bool		m_bOpen;
	CString		m_strDBPath;
	std::vector<CString> m_vColumns;
	Sqlite	m_sqlite;


private :
	CString GetTableName(bool bMainTable);


public :
	bool Open(CString strPath);
	void Close(void);
	bool ResetFile(void);
	bool Insert(bool bMainTable, CString strKey, const BNC_BinaryObject &data, bool bOverWrite);
	bool Update(bool bMainTable, CString strKey, const BNC_BinaryObject &data);
	bool Delete(bool bMainTable, CString strKey);
	bool Get(bool bMainTable, CString strKey, _Ret_ BNC_BinaryObject &data);
	bool Get(bool bMainTable, _Ret_ std::vector<CString> &vStrKey, _Ret_ std::vector<BNC_BinaryObject*> &vData);
	bool Begin(void);
	bool End(bool bCommit);
};
//////////////////////////////////////////////////////////////////////////////////////////
};
*/