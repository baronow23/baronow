#pragma once

#include "template/TBuffer.h"
#include "crypt/CryptFactory.h"
#include "interface/ISerialize.h"

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
// CString를 제외한 깊은복사가 필요한 대상은 templte 메서드 사용금지!
// ISerialize 상속받아 Read/WriteStream()을 사용할 것!!
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
	// 이어서 데이터 쓰기
	StreamResult AddPair(_In_ const void* pData, size_t iDataBytes);
	

	// 프로토콜에 따라 변동되므로 데이터의 메모리 크기나 문자열의 길이와 상이함!!
	// NextRead에서 사용
	StreamResult Get(size_t idxPos, _Ret_ void* pData, size_t iDataBytes, _Ret_opt_ size_t *piRetBytes = nullptr) const;
	StreamResult Get(size_t idxPos, _Ret_ CString &strRead, _Ret_opt_ size_t *piRetBytes = nullptr) const;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// vector 일괄 처리용
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
	// map 일괄 처리용
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
	// 지정 파일에서 헤더 또는 바디만 읽기
	static StreamResult ReadHeader(const CString &strPath, _Ret_ StreamHeader &header, _In_opt_ size_t iMaxSize = INT_MAX);
	static StreamResult ReadBody(const CString &strPath, bool bSeekHeader, _Ret_ TBuffer<BYTE> &body, _In_opt_ size_t iMaxSize = INT_MAX);


	// 파일 읽기
	// 헤더 읽기 생략, m_pHeader 생성 여부에 따라 읽기 위치 결정
	bool ReadBody(CString &strPath);


	// m_pHeader가 생성되어 있을 경우만 readHeader에 헤더를 읽고, bCompareVer 체크 
	// 읽은 헤더는 m_pHeader에 업데이트하지 않음!!!
	bool Import(CString &strPath, bool bCompareVer, _Ret_ StreamHeader &readHeader);


	// 파일 쓰기
	bool Export(CString &strPath, bool bOverWrite = false);


	// 읽기, 쓰기 성공시 기록된 파일 경로
	CString GetFilePath(void) const;


	// 초기화 때 생성된 헤더 반환
	const StreamHeader* GetInitHeaderPtr(void) const;
	   

	// 기록된 데이터 암호화 후처리
	bool Encrypt(const CryptHandle &crypt);
	bool Encrypt(const std::shared_ptr<CryptHandle> pCrypt);
	bool Decrypt(const CryptHandle &crypt);
	bool Decrypt(const std::shared_ptr<CryptHandle> pCrypt);
		


	// TBuffer 메서드 접근
	void Reset(void); // TBuffer초기화후 기본 guid, version 작성됨
	const BYTE* GetBuffer(size_t idxBegin = 0);
	size_t GetLength(void);


	// 마지막 처리 결과
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
	// 이어서 데이터 쓰기
	// return 추가된 크기 (내부에서 하나라도 실패한다면 최종 0)
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
	// 초기화된 m_idxNextReadPos를 기준으로 읽기
	// 성공시 읽어온 길이만큼 m_idxNextReadPos 이동
	// return 읽어온 바이너리 길이(bytes)
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
	// CStringA, CStringW 개별 작성하기 귀찮아서...
	// CStringT 만 허용
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