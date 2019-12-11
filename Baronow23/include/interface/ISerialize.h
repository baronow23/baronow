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
		InvalidParameter,		// �б⾲�� ���� ������ ���� (nullptr)

		// write error
		OutOfMemory,			// �޸� �Ҵ� ���� (buffer length = 0)

		// read error
		FileNotFound,			// ���� ����
		IndexOverflow,			// ���� ��ġ���� ��û�� �����͸� ���� �� �ִ� ������ ������
		InvalidProtocol,		// �б� ��û�� ������ Ÿ�� �Ǵ� ũ��� ��ϵ� ������ ������
		InsufficientBuffer,		// buffer �б� ����
		WrongGuid,				// �о�� guid != ISerialize::GetClassGuid
		WrongVersion,			// �о�� version != ISerialize::GetClassVersion
								// ����� ����ó�� �ϵ��� ���� -> �ٸ����� OnReadStream �Ķ���ͷ� ����

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
	// �б� ���� �ܺ� �������̽�
	StreamResult ReadStream(_In_ baro::Stream &stream, bool bReadHeader);
	StreamResult WriteStream(_Ret_ baro::Stream &stream, bool bWriteHeader) const;


public :
	// subclass ���� ���� guid, version
	virtual GUID GetClassGuid(void) const;		// default : s_DefaultGuid
	virtual float GetClassVersion(void) const;	// default : 1.0


private :
	// Read/WriteStream ���ο��� guid, version üũ�� ȣ��
	virtual baro::StreamResult OnReadStream(_In_ baro::Stream &stream, float fReadVersion = 0) = 0;
	virtual baro::StreamResult OnWriteStream(_Ret_ baro::Stream &stream) const = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////
};