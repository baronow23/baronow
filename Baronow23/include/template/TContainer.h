#pragma once


namespace bapi 
{
	//--------------------------------------------------------------------------------
	// map �����̳� �߰�
	// �ߺ�key ������ false ��ȯ
	template <typename _Key, typename _Val>
	bool InsertMap(_In_ _Key key, _In_ _Val value, _Ret_ map<_Key, _Val> &m)
	{
		auto ret = m.insert(  make_pair(key, value) );
		if(ret.second == false)
		{
			_trace("	exist key");
			return false;
		}

		// _trace("	%X size %d", &m, m.size());
		// ASSERT(value.get() == ret.first->second.get());
		return true;
	};


	//--------------------------------------------------------------------------------
	// map �����̳� ����
	// key�� ã�� �� ������ false ��ȯ
	template <typename _Key, typename _Val>
	bool EraseMap(_In_ _Key key, _Ret_ map<_Key, _Val> &m)
	{
		auto itFind = m.find(key);
		if(itFind == m.end())
		{
			return false;
		}

		m.erase(itFind);
		_trace("	[%08X] remain size %d", &m, m.size());
		return true;
	};


	//--------------------------------------------------------------------------------
	// multimap ���� : callback ��ȯ true�� ����
	// return ������ ��� ������
	template <typename _Key, typename _Val>
	size_t EraseMultimap(_In_ size_t maxDelete, _In_ _Key key,
						 _Ret_ multimap<_Key, _Val> &mm,
						 _Ret_ std::function<bool(_Val)>cbCallback)
	{
		ASSERT_RETVAL(cbCallback, 0);

		size_t erase = 0;
		auto itEqual = mm.equal_range(key);

		auto it = itEqual.first;
		while(it != itEqual.second)
		{
			if(cbCallback(it->second))
			{
				erase++;
				it = mm.erase(it);
				if(erase >= maxDelete)
				{
					break;
				}
			}
			else
			{
				++it;
			}
		}

		_trace("	[%08X] erase %d, remain size %d", &mm, erase, mm.size());
		return erase;
	};


	//--------------------------------------------------------------------------------
	// map Ž��
	// ������ nullptr ��ȯ
	template <typename _Key, typename _Val>
	_Val FindMap(_In_ _Key key, _In_ map<_Key, _Val> &m)
	{
		auto itFind = m.find(key);
		if(itFind == m.end())
		{
			_traceC(TextColor::LIGHT_MAGENTA, "	not found");
			return nullptr;
		}
		return itFind->second;
	};
	

	//--------------------------------------------------------------------------------
	// multimap Ž��
	// ������ vector�� ��Ƽ� ��ȯ
	template <typename _Key, typename _Val>
	vector<_Val> FindMultimap(_In_ _Key key, _In_ multimap<_Key, _Val> &mm)
	{
		vector<_Val> ret;
		auto itList = mm.equal_range(key);
		for(auto it = itList.first; it != itList.second; it++)
		{
			ret.push_back( it->second );
		}

		if(ret.size() == 0)
		{
			_traceC(TextColor::LIGHT_MAGENTA, "	not found");
		}
		return ret;
	};


};




