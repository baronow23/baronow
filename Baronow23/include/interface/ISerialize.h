#pragma once


#ifndef _ReadStream
#define _ReadStream(func) { auto ret = (func); if(ret != StreamResult::Ok) { return ret; }   }
#endif

#ifndef _WriteStream
#define _WriteStream(func) { auto ret = (func); if(ret != StreamResult::Ok) { ASSERT(0); return ret; }   }
#endif

#ifndef _NextReadStream
#define _NextReadStream(stream, data) { auto ret = stream.NextRead(data); if(ret != StreamResult::Ok) { return ret; }   }
#endif

#ifndef _NextWriteStream
#define _NextWriteStream(stream, data) { auto ret = stream.NextWrite(data); if(ret != StreamResult::Ok) { ASSERT(0); return ret; }   }
#endif


#ifndef __ReadStream
#define __ReadStream(func) { m_LastError = (func); if(m_LastError != StreamResult::Ok) { return m_LastError; }   }
#endif

#ifndef __WriteStream
#define __WriteStream(func) { m_LastError = (func); if(m_LastError != StreamResult::Ok) { ASSERT(0); return m_LastError; }   }
#endif


namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////

	enum class StreamResult
	{
		Ok = 0,

		// read, write error
		InvalidParameter,		// 읽기쓰기 전달 포인터 오류 (nullptr)

		// write error
		OutOfMemory,			// 메모리 할당 실패 (buffer length = 0)

		// read error
		FileNotFound,			// 파일 없음
		IndexOverflow,			// 현재 위치에서 요청한 데이터를 읽을 수 있는 공간이 부족함
		InvalidProtocol,		// 읽기 요청한 데이터 타입 또는 크기와 기록된 정보가 상이함
		InsufficientBuffer,		// buffer 읽기 실패
		WrongGuid,				// 읽어온 guid != ISerialize::GetClassGuid
		WrongVersion,			// 읽어온 version != ISerialize::GetClassVersion
								// 사용자 예외처리 하도록 삭제 -> 다르더라도 OnReadStream 파라미터로 전달

		// crypt error
		EncryptError,
		DecryptError,


		// import, export error
		FileException,
		EmptyData,
		FilesizeOver,
		WrongHeaderSize,
		WrongHeaderProtocol,
		WrongHeaderData,
		WrongBodySize,
	};

	BN23_API(CString) GetStreamResultString(StreamResult ret);


class Stream;
class BN23_CLASS ISerialize : public CriticalSection
{
public:
	explicit ISerialize();
	virtual ~ISerialize();


public :
	static const GUID s_DefaultGuid;

	
public :
	// 읽기 쓰기 외부 인터페이스
	StreamResult ReadStream(_In_ baro::Stream &stream, bool bReadHeader);
	StreamResult WriteStream(_Ret_ baro::Stream &stream, bool bWriteHeader) const;


public :
	// subclass 개별 관리 guid, version
	virtual GUID GetClassGuid(void) const;		// default : s_DefaultGuid
	virtual float GetClassVersion(void) const;	// default : 1.0


private :
	// Read/WriteStream 내부에서 guid, version 체크후 호출
	virtual baro::StreamResult OnReadStream(_In_ baro::Stream &stream, float fReadVersion = 0) = 0;
	virtual baro::StreamResult OnWriteStream(_Ret_ baro::Stream &stream) const = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////
};