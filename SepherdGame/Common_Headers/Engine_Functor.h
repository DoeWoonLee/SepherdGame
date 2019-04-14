#ifndef Engine_Functor_h__
#define Engine_Functor_h__

namespace Engine
{
	class CDeleteSingle
	{
	public:
		explicit CDeleteSingle(void) {}
		~CDeleteSingle() {}
	public:	// operator
		template <typename T> void operator () (T& pInstance)
		{
			if(nullptr != pInstance)
			{
				delete pInstance;
				pInstance = nullptr;
			}
		}
	};

	class CDeletePair
	{
	public:
		explicit CDeletePair(void){}
		~CDeletePair() {}
	public: // operator
		template <typename T> void operator () (T& Pair)
		{
			if(nullptr != Pair.second)
			{
				delete Pair.second;
				Pair.second = nullptr;
			}
		}
	};

	class CReleaseSingle
	{
	public:
		explicit CReleaseSingle(void) {}
		~CReleaseSingle(void) {}
		template <typename T> void operator () (T& pInstance)
		{
			if(nullptr != pInstance)
			{
				pInstance->Release();
				pInstance = nullptr;
			}
		}
	};

	class CReleasePair
	{
	public:
		explicit CReleasePair(void) {}
		~CReleasePair(void) {}
		template <typename T> void operator () (T& Pair)
		{
			if(nullptr != Pair.second)
			{
				Pair.second->Release();
				Pair.second = nullptr;
			}
		}
	};
	class CReleasePairWithString
	{
	public:
		explicit CReleasePairWithString(void) {}
		~CReleasePairWithString(void) {}
		template <typename T> void operator () (T& Pair)
		{
			if (nullptr != Pair.second)
			{
				delete[] Pair.first;
				Pair.second->Release();
				Pair.second = nullptr;
			}
		}
	};

	class CTagFinder
	{
	public:
		explicit CTagFinder(const TCHAR* pTag) : m_pTag(pTag) {}
		~CTagFinder(void) {}
	public:
		template <typename T> bool operator () (T& Pair)
		{
			int iResult = lstrcmp(m_pTag, Pair.first);

			if(0 == iResult)
				return true;
			return false;
		}
	private:
		const TCHAR*		m_pTag;
	};

	class CTagAsciiFinder
	{
	public:
		explicit CTagAsciiFinder(const char* pTag) : m_pTag(pTag) {}
		~CTagAsciiFinder(void) {}
	public:
		template <typename T> bool operator () (T& Pair)
		{
			int iResult = strcmp(m_pTag, Pair.first);

			if (0 == iResult)
				return true;
			return false;
		}
	private:
		const char*		m_pTag;
	};

	

}

#endif // Engine_Functor_h__
