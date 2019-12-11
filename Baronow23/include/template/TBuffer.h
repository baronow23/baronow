#pragma once


namespace baro { 
//////////////////////////////////////////////////////////////////////////////////////////
template <typename _Type> class TBuffer
{
public:
	explicit TBuffer(void) : m_pData(nullptr)
	{
		_ntrace_construct;
		Reset();
	};

	explicit TBuffer(size_t sLength) : m_pData(nullptr)
	{
		_ntrace_construct;
		Reset(nullptr, sLength);
	};

	explicit TBuffer(const _Type *pData, size_t sLength) : m_pData(nullptr)
	{
		_ntrace_construct;
		Reset(pData, sLength);
	};
	
	explicit TBuffer(std::initializer_list<_Type> list) : m_pData(nullptr)
	{
		_ntrace_construct;
		Reset(nullptr, list.size());

		_Type *pData = m_pData;
		if(pData)
		{
			for(auto data : list)
			{
				CopyMemory(pData, &data, sizeof(_Type));
				pData += sizeof(_Type);
			}
		}
	};

	// explicit ���� vs2013���� ���� ����
	TBuffer(const TBuffer & rhs) : m_pData(nullptr)
	{
		_ntrace_construct;
		*this = rhs;
	};

	TBuffer& operator = (const TBuffer & rhs) 
	{
		//_trace("");
		Reset(rhs.m_pData, rhs.m_iLength);
		return *this;
	};

	virtual ~TBuffer(void)
	{
		_ntrace_destruct;
		Reset();
	};



	//TBuffer(TBuffer &&rhs) = delete;
	//TBuffer& operator = (TBuffer &&) = delete;


	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	void Reset(const _Type *pData = nullptr, size_t sLength = 0)
	{
		if(m_pData)
		{
			delete[] m_pData;
			m_pData = nullptr;
		}

		m_iLength = 0;
		if(pData)
		{
			ASSERT_RETNONE(sLength);
			m_pData = new _Type[sLength];
			if(m_pData)
			{
				m_iLength = sLength;
				CopyMemory(m_pData, pData, sizeof(_Type) * sLength);
			}
		}
		else if(sLength)
		{
			m_pData = new _Type[sLength];
			if(m_pData)
			{
				m_iLength = sLength;
				SecureZeroMemory(m_pData, sizeof(_Type) * sLength);
			}
		}
	};


	const _Type* GetBuffer(size_t iBeginPos = 0) const
	{
		if(m_pData == nullptr || iBeginPos >= m_iLength)
		{
			return nullptr;
		}

		return &m_pData[iBeginPos];
	};


	// TODO
	_Type* LockBuffer(void)
	{
		return m_pData;
	};


	size_t GetLength(void) const
	{
		return m_iLength;
	};


	_Type At(size_t idxPos) const
	{
		if(m_pData == nullptr || idxPos >= m_iLength)
		{
			return _Type();
		}

		return m_pData[idxPos];
	};


	_Type Front(void) const
	{
		if(m_pData == nullptr || m_iLength == 0)
		{
			return _Type();
		}

		return m_pData[0];
	};


	_Type Back(void) const
	{
		if(m_pData == nullptr || m_iLength == 0)
		{
			return _Type();
		}

		return m_pData[m_iLength-1];
	};


	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	bool Set(size_t idxPos, _Type val)
	{
		if(m_pData == nullptr || idxPos >= m_iLength)
		{
			return false;
		}
		m_pData[idxPos] = val;
		return true;
	};

	
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	// idxBegin���� iCount������ ����� ����
	bool Trim(size_t idxBegin, size_t iCountLength)
	{
		ASSERT_RETVAL(iCountLength, false);
		if(m_pData == nullptr) return false;
		if(idxBegin + iCountLength > m_iLength) return false;

		// ����ũ��� ��ü
		*this = TBuffer<_Type>(&m_pData[idxBegin], iCountLength);
		return true;
	};


	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	// idxSrc ��ġ�� pCopyData�� iCopyLength ��ŭ ����
	// m_pData�� ������ ��� ���Ҵ� ó�� 
	// ���� : return m_pData ����
	// ���� : 0
	size_t Update(size_t idxSrc, const _Type* pCopyData, size_t iCopyLength)
	{
		ASSERT_RETVAL(pCopyData && iCopyLength, 0);
		ASSERT_RETVAL(iCopyLength, 0);

		if(m_pData == nullptr)
		{
			Reset(nullptr, idxSrc + iCopyLength);
		}
		else if(idxSrc + iCopyLength > m_iLength)
		{
			auto length = idxSrc + iCopyLength;
			auto pReAlloc = (_Type*)realloc(m_pData, sizeof(_Type) * length);
			if(pReAlloc == nullptr)
			{
				return 0;
			}
			
			m_iLength = idxSrc + iCopyLength;
			m_pData = pReAlloc;
		}


		// out of memory
		if(m_pData == nullptr)
		{
			m_iLength = 0;
			return 0;
		}
		
		CopyMemory(&m_pData[idxSrc], pCopyData, sizeof(_Type) * iCopyLength);
		return m_iLength;
	};

	size_t Append(const _Type* pCopyData, size_t iCopyLength)
	{
		return Update(m_iLength, pCopyData, iCopyLength);
	};

	/*
	size_t Append(_Type rhs)
	{
		return Update(m_iLength, &rhs, sizeof(rhs));
	};
	*/

	size_t Append(const _Type &rhs)
	{
		return Update(m_iLength, &rhs, sizeof(rhs));
	};


	size_t Append(const TBuffer<_Type> &rhs)
	{
		return Update(m_iLength, rhs.m_pData, rhs.m_iLength);
	};


	template <typename _WriteType>
	size_t Append(const _WriteType &data)
	{
		return Update(m_iLength, (BYTE*)&data, sizeof(data));
	};




	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	// m_pData[idxSrc] ���� iCopyLength��ŭ pData�� ����
	// ���� : return iCopyLength
	// ���� : 0 (������ ���� ����)
	size_t Read(size_t idxSrc, _Ret_ void* pData, size_t iCopyLength) const
	{
		ASSERT_RETVAL(m_pData && m_iLength, 0);
		ASSERT_RETVAL(pData && iCopyLength, 0);

		if(idxSrc + iCopyLength > m_iLength)
		{
			return 0;
		}

		CopyMemory(pData, &m_pData[idxSrc], iCopyLength);
		return iCopyLength;
	};


	size_t Read(size_t idxSrc, _Ret_ TBuffer &rhs, size_t iCopyLength) const
	{
		if(rhs.m_iLength < iCopyLength)
		{
			rhs.Reset(nullptr, iCopyLength);
		}
		return Read(idxSrc, rhs.m_pData, iCopyLength);
	};


	template <typename _ReadType>
	size_t Read(size_t idxSrc, _Ret_ _ReadType &data) const
	{
		return Read(idxSrc, &data, sizeof(data));
	};



	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	// debug

	void PrintHexByte(baro::TextColor txtColor, size_t iMaxBytes = INT_MAX) const
	{
		if(m_pData == nullptr || m_iLength == 0)
		{
			return;
		}


		DWORD dwPitch = sizeof(_Type);
		if(iMaxBytes > m_iLength * dwPitch)
		{
			iMaxBytes = m_iLength * dwPitch;
		}


		const BYTE* pData = (BYTE*)m_pData;
		CString str = bapi::MakeString(_T("%02X"), pData[0]);

		for(size_t i=1; i<iMaxBytes; i++)
		{
			str += _T(" ") + bapi::MakeString(_T(" %02X"), pData[i]);
		}
		_traceC(txtColor, "[%d] %s", iMaxBytes, (LPCTSTR)str);
	};


protected:
	_Type	*m_pData;
	size_t	m_iLength;
};
//////////////////////////////////////////////////////////////////////////////////////////
};
