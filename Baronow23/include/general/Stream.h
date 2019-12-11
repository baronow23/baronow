#pragma once

#include "template/TBuffer.h"
#include "crypt/CryptFactory.h"
#include "interface/ISerialize.h"

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
// CString�� ������ �������簡 �ʿ��� ����� templte �޼��� ������!
// ISerialize ��ӹ޾� Read/WriteStream()�� ����� ��!!
//////////////////////////////////////////////////////////////////////////////////////////
	
class BN23_CLASS StreamHeader final
{
public :
	
	explicit StreamHeader() :
		guid(GUID_NULL),
		fVersion(0),
		dwFlags(0),
		dwReserved(0)
	{
		_ntrace_construct;
		GetLocalTime(&st);
	};

	explicit StreamHeader(GUID _guid, float _fVersion, DWORD _dwFlags) :
		guid(_guid),
		fVersion(_fVersion),
		dwFlags(_dwFlags),
		dwReserved(0)
	{
		_ntrace_construct;
		GetLocalTime(&st);
	};

	explicit StreamHeader(const StreamHeader &rhs)
	{
		_ntrace_construct;
		*this = rhs;
	};

	StreamHeader& operator = (const StreamHeader &rhs)
	{
		st			= rhs.st;
		guid		= rhs.guid;
		fVersion	= rhs.fVersion;
		dwFlags		= rhs.dwFlags;
		dwReserved	= rhs.dwReserved;
		return *this;
	};

	~StreamHeader()
	{
		_ntrace_destruct;
	};


public :
	SYSTEMTIME st;
	GUID	guid;
	float	fVersion;
	DWORD	dwFlags;
	DWORD	dwReserved;
};


class BN23_CLASS Stream final : protected TBuffer<BYTE>
{
public:
	explicit Stream();
	explicit Stream(StreamHeader &header);
	explicit Stream(GUID guid, float fVersion, DWORD dwFlags);
	~Stream();

	
private :
	StreamHeader* m_pInitHeader;
	size_t	m_idxNextReadPos;
	TBuffer<TCHAR> m_pFilePath;
	StreamResult m_LastError;
	DWORD m_dwSysError;


private :
	// �̾ ������ ����
	StreamResult AddPair(_In_ const void* pData, size_t iDataBytes);
	

	// �������ݿ� ���� �����ǹǷ� �������� �޸� ũ�⳪ ���ڿ��� ���̿� ������!!
	// NextRead���� ���
	StreamResult Get(size_t idxPos, _Ret_ void* pData, size_t iDataBytes, _Ret_opt_ size_t *piRetBytes = nullptr) const;
	StreamResult Get(size_t idxPos, _Ret_ CString &strRead, _Ret_opt_ size_t *piRetBytes = nullptr) const;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// vector �ϰ� ó����
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename _Type>
	StreamResult NextWriteVector(const std::vector<_Type> &vData,
								 std::function<StreamResult(const _Type &write)> _WriteFunc)
	{
		// size
		size_t iSize = vData.size();
		__WriteStream(NextWrite<size_t>(iSize));
		

		// write
		for(size_t i=0; i<iSize; i++) 
		{
			__WriteStream(_WriteFunc(vData[i]));
		} 
		return StreamResult::Ok;
	};


	template <typename _Type>
	StreamResult NextReadVector(_Ret_ std::vector<_Type> &vData,
								std::function<StreamResult(_Ret_ _Type &read)> _ReadFunc)
	{
		vData.clear();
		
		// size
		size_t iSize = 0;
		__ReadStream(NextRead<size_t>(iSize));
		if(iSize == 0)
		{
			return StreamResult::Ok;
		}

		// read
		_Type readData;
		for(size_t i=0; i<iSize; i++)
		{
			__ReadStream(_ReadFunc(readData));
			vData.push_back(readData);
		}
		return StreamResult::Ok;
	};

	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// map �ϰ� ó����
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename _Key, typename _Value>
	StreamResult NextWriteMap(const std::map<_Key, _Value> &mData,
							  std::function<StreamResult(const _Key &key)> _WriteKey,
							  std::function<StreamResult(const _Value &value)> _WriteValue)
	{
		// size
		size_t iSize = mData.size();
		__WriteStream(NextWrite<size_t>(iSize));

		// write
		auto it = mData.begin();
		while(it != mData.end())
		{
			__WriteStream(_WriteKey(it->first));
			__WriteStream(_WriteValue(it->second));
			++it;
		}
		return StreamResult::Ok;
	};
	
	template <typename _Key, typename _Value>
	StreamResult NextReadMap(_Ret_ std::map<_Key, _Value> &mData,
							 std::function<StreamResult(_Ret_ _Key &read)> _ReadKey,
							 std::function<StreamResult(_Ret_ _Value &read)> _ReadValue)
	{
		mData.clear();

		// size
		size_t iSize = 0;
		__ReadStream(NextRead<size_t>(iSize));
		if(iSize == 0)
		{
			return StreamResult::Ok;
		}

		// read
		_Key key;
		_Value value;
		for(size_t i=0; i<iSize; i++)
		{
			__ReadStream(_ReadKey(key));
			__ReadStream(_ReadValue(value));
			mData.insert( std::make_pair(key, value) );
		}
		return StreamResult::Ok;
	};



public :
	// ���� ���Ͽ��� ��� �Ǵ� �ٵ� �б�
	static StreamResult ReadHeader(const CString &strPath, _Ret_ StreamHeader &header, _In_opt_ size_t iMaxSize = INT_MAX);
	static StreamResult ReadBody(const CString &strPath, bool bSeekHeader, _Ret_ TBuffer<BYTE> &body, _In_opt_ size_t iMaxSize = INT_MAX);


	// ���� �б�
	// ��� �б� ����, m_pHeader ���� ���ο� ���� �б� ��ġ ����
	bool ReadBody(CString &strPath);


	// m_pHeader�� �����Ǿ� ���� ��츸 readHeader�� ����� �а�, bCompareVer üũ 
	// ���� ����� m_pHeader�� ������Ʈ���� ����!!!
	bool Import(CString &strPath, bool bCompareVer, _Ret_ StreamHeader &readHeader);


	// ���� ����
	bool Export(CString &strPath, bool bOverWrite = false);


	// �б�, ���� ������ ��ϵ� ���� ���
	CString GetFilePath(void) const;


	// �ʱ�ȭ �� ������ ��� ��ȯ
	const StreamHeader* GetInitHeaderPtr(void) const;
	   

	// ��ϵ� ������ ��ȣȭ ��ó��
	bool Encrypt(const CryptHandle &crypt);
	bool Encrypt(const std::shared_ptr<CryptHandle> pCrypt);
	bool Decrypt(const CryptHandle &crypt);
	bool Decrypt(const std::shared_ptr<CryptHandle> pCrypt);
		


	// TBuffer �޼��� ����
	void Reset(void); // TBuffer�ʱ�ȭ�� �⺻ guid, version �ۼ���
	const BYTE* GetBuffer(size_t idxBegin = 0);
	size_t GetLength(void);


	// ������ ó�� ���
	StreamResult GetLastError(void);
	CString GetLastErrorString(void);


private :
	bool SetResult(StreamResult ret);


public :
	size_t GetCurrentReadPos(void)
	{
		return m_idxNextReadPos;
	};
	size_t GetReadRemainLength(void)
	{
		return m_iLength - m_idxNextReadPos;
	};


public :
	//////////////////////////////////////////////////////////////////////////////
	// �̾ ������ ����
	// return �߰��� ũ�� (���ο��� �ϳ��� �����Ѵٸ� ���� 0)
	//////////////////////////////////////////////////////////////////////////////

	// object
	template <typename _Type>
	StreamResult NextWrite(const _Type &data)
	{
		return AddPair(&data, sizeof(_Type));
	};


	template <typename _Type>
	StreamResult NextWrite(_In_ const std::vector<_Type> &vData)
	{
		return NextWriteVector<_Type>(vData, [&](const _Type &write)
		{
			return NextWrite<_Type>(write);
		});
	};


	///////////////////////////////////////////////////////
	// string
	StreamResult NextWrite(const CString &str)
	{
#ifdef _UNICODE
		return AddPair( (LPCTSTR)str, sizeof(TCHAR) * str.GetLength() );
#else 
		CStringA strA(str);
		return AddPair( (LPCSTR)strA, strA.GetLength() );
#endif
	};
	StreamResult NextWrite(const std::vector<CString> &vStr)
	{
		return NextWriteVector<CString>(vStr, [&](const CString &write)
		{
			return NextWrite(write);
		});
	};

	

	///////////////////////////////////////////////////////
	// map <type, type>
	template <typename _Key, typename _Value>
	StreamResult NextWrite(_In_ const std::map<_Key, _Value> &mData)
	{
		return NextWriteMap<_Key, _Value>(mData,
										  [&](const _Key &key){ return NextWrite<_Key>(key); },
										  [&](const _Value &value){ return NextWrite<_Value>(value); });
	};


	// map <type, string>
	template <typename _Key>
	StreamResult NextWrite(_In_ const std::map<_Key, CString> &mData)
	{
		return NextWriteMap<_Key, CString>(mData,
										  [&](const _Key &key){ return NextWrite<_Key>(key); },
										  [&](const CString &value){ return NextWrite(value); });
	};

	// map <string, type>
	template <typename _Value>
	StreamResult NextWrite(_In_ const std::map<CString, _Value> &mData)
	{
		return NextWriteMap<CString, _Value>(mData,
											[&](const CString &key){ return NextWrite(key); },
											[&](const _Value &value){ return NextWrite<_Value>(value); });
	};


	// map <string, string>
	StreamResult NextWrite(_In_ const std::map<CString, CString> &mData)
	{
		return NextWriteMap<CString, CString>(mData,
											 [&](const CString &key){ return NextWrite(key); },
											 [&](const CString &value){ return NextWrite(value); });
	};



	//////////////////////////////////////////////////////////////////////////////
	// �ʱ�ȭ�� m_idxNextReadPos�� �������� �б�
	// ������ �о�� ���̸�ŭ m_idxNextReadPos �̵�
	// return �о�� ���̳ʸ� ����(bytes)
	//////////////////////////////////////////////////////////////////////////////
	
	// object
	template <typename _Type>
	StreamResult NextRead(_Ret_ _Type &data)
	{
		size_t iRead = 0;
		__ReadStream(Get(m_idxNextReadPos, (void*)&data, sizeof(_Type), &iRead));
		m_idxNextReadPos += iRead;
		return StreamResult::Ok;
	};

	template <typename _Type>
	StreamResult NextRead(_Ret_ std::vector<_Type> &vData)
	{
		return NextReadVector<_Type>(vData, [&](_Ret_ _Type &read)
		{
			return NextRead<_Type>(read);
		});
	};


	///////////////////////////////////////////////////////
	// string
	StreamResult NextRead(_Ret_ CString &data)
	{
		size_t iRead = 0;
		__ReadStream(Get(m_idxNextReadPos, data, &iRead));
		m_idxNextReadPos += iRead;
		return StreamResult::Ok;
	};
	StreamResult NextRead(_Ret_ std::vector<CString> &vData)
	{
		return NextReadVector<CString>(vData, [&](_Ret_ CString &read)
		{
			return NextRead(read);
		});
	};
	
	
	///////////////////////////////////////////////////////
	// map <type, type>
	template <typename _Key, typename _Value>
	StreamResult NextRead(_Ret_ std::map<_Key, _Value> &mData)
	{
		return NextReadMap<_Key, _Value>(mData,
									   [&](_Key &key){ return NextRead<_Key>(key); },
									   [&](_Value &value){ return NextRead<_Value>(value); });
	};

	// map <type, string>
	template <typename _Key>
	StreamResult NextRead(_Ret_ std::map<_Key, CString> &mData)
	{
		return NextReadMap<_Key, CString>(mData,
										  [&](_Key &key){ return NextRead<_Key>(key); },
										  [&](CString &value){ return NextRead(value); });
	};

	// map <string, type>
	template <typename _Value>
	StreamResult NextRead(_Ret_ std::map<CString, _Value> &mData)
	{
		return NextReadMap<CString, _Value>(mData,
										  [&](CString &key){ return NextRead(key); },
										  [&](_Value &value){ return NextRead<_Value>(value); });
	};


	// map <string, string>
	StreamResult NextRead(_Ret_ std::map<CString, CString> &mData)
	{
		return NextReadMap<CString, CString>(mData,
											 [&](CString &key){ return NextRead(key); },
											 [&](CString &value){ return NextRead(value); });
	};



	//////////////////////////////////////////////////////////////////////////////
	// CStringA, CStringW ���� �ۼ��ϱ� �����Ƽ�...
	// CStringT �� ���
	//////////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE 
	using CStringX = CStringA;
#else
	using CStringX = CStringW;
#endif
	StreamResult NextWrite(const CStringX str) = delete;
	StreamResult NextWrite(const std::vector<CStringX> vStr) = delete;
	StreamResult NextWrite(_In_ const std::map<CStringX, CStringX> &mData) = delete;
	template <typename _Key> StreamResult NextWrite(_In_ const std::map<_Key, CStringX> &mData) = delete;
	template <typename _Val> StreamResult NextWrite(_In_ const std::map<CStringX, _Val> &mData) = delete;

	StreamResult NextRead(_Ret_ CStringX &data) = delete;
	StreamResult NextRead(_Ret_ std::vector<CStringX> &vData) = delete;
	StreamResult NextRead(_Ret_ std::map<CStringX, CStringX> &mData) = delete;
	template <typename _Key> StreamResult NextRead(_Ret_ std::map<_Key, CStringX> &mData) = delete;
	template <typename _Val> StreamResult NextRead(_Ret_ std::map<CStringX, _Val> &mData) = delete;
	

public :
	static TBuffer<BYTE> MakeBuffer(CString str);
	static CString MakeString(TBuffer<BYTE> &buffer);
};

//////////////////////////////////////////////////////////////////////////////////////////
};