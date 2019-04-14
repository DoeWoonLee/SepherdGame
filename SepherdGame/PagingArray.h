#ifndef PagingArray_h__
#define PagingArray_h__

#include "Engine_Define.h"

class Iterator
{
public:
	Iterator(const _uint& uiMemoryCnt, const _uint& uiDataSize) : m_uiMemoryCnt(uiMemoryCnt), m_uiDataSize(uiDataSize) {}
	Iterator& operator++()
	{
		m_uiArrayIdx++;
		if (m_uiArrayIdx == m_uiMemoryCnt) // Almost False
		{
			m_uiTotal += m_uiMemoryCnt;
			m_uiArrayIdx = 0;
			m_uiPageIdx++;
		}
		return *this;
	}
	bool check_range()
	{
		return (m_uiTotal + m_uiArrayIdx) < m_uiDataSize;
	}

	_uint m_uiPageIdx = 0;
	_uint m_uiArrayIdx = 0;
	_uint m_uiTotal = 0;
private:
	const _uint& m_uiDataSize;
	const _uint& m_uiMemoryCnt;
};

template<class T>
class CPagingArray
{
public:
	explicit CPagingArray(void) _NOEXCEPT
		: m_uiMemoryCnt(0), m_uiInstanceCnt(0)
	{

	}
	explicit CPagingArray(const _uint& uiMemoryCnt) _NOEXCEPT
		: m_uiMemoryCnt(uiMemoryCnt).m_uiInstanceCnt(0)
	{
		/*_uint uiMemorySize = sizeof(T);
		byte* pMemory = (byte*)malloc(uiMemoryCnt * uiMemorySize);
		for (_uint i = 0; i < uiMemoryCnt; ++i)
		{
		new (pMemory + (i*uiMemorySize)) T(nullptr);
		}
		m_vecPages.push_back((T*)pMemory);*/
		m_vecPages.push_back(new T[uiMemoryCnt]);
	}
	~CPagingArray(void)
	{
		for (_uint i = 0; i < m_vecPages.size(); ++i)
			delete[] m_vecPages[i];
		m_vecPages.clear();
	}
public:
	void set_initdata(const _uint& uiMemoryCnt) _NOEXCEPT
	{
		m_uiMemoryCnt = uiMemoryCnt;
	}
	void push_back(T& Data)
	{
		m_vecPages[m_uiPagingIdx][m_uiArrayCnt] = Data;
		++m_uiInstanceCnt;
		++m_uiArrayCnt;

		if (m_uiArrayCnt == m_uiMemoryCnt) // Almost False
		{
			m_uiArrayCnt = 0;
			++m_uiPagingIdx;

			// Not Aready Exist Next Data
			if (m_vecPages.size() - m_uiPagingIdx == 0)
				m_vecPages.push_back(new T[m_uiMemoryCnt]);
		}
		bEmpty = false;
	}
	T* get_end(void)
	{
		T& Data = m_vecPages[m_uiPagingIdx][m_uiArrayCnt];
		++m_uiInstanceCnt;
		++m_uiArrayCnt;

		if (m_uiArrayCnt == m_uiMemoryCnt) // Almost False
		{
			m_uiArrayCnt = 0;
			++m_uiPagingIdx;

			// Not Aready Exist Next Data
			if (m_vecPages.size() - m_uiPagingIdx == 0)
				m_vecPages.push_back(new T[m_uiMemoryCnt]);
		}
		bEmpty = false;

		return &Data;
	}
	void pop_back()
	{
		if (0 == m_uiInstanceCnt) _ASSERT(nullptr); // Almost False

		memset(&m_vecPages[m_uiInstanceCnt / m_uiMemoryCnt][m_uiInstanceCnt % m_uiMemoryCnt], 0, sizeof(T));
		--m_uiInstanceCnt;

		Check_EmptyPage();
	}
	T& swap_end(_uint uiIndex)
	{
		T Temp = (*this)[uiIndex];
		(*this)[uiIndex] = (*this)[m_uiInstanceCnt];
		(*this)[m_uiInstanceCnt] = Temp;

		m_uiInstanceCnt--;
		Check_EmptyPage();

		return (*this)[uiIndex];
	}
private:
	void Check_EmptyPage(void)
	{
		if (0 == m_uiArrayCnt) // Almost False 
		{
			--m_uiPagingIdx;// Page Index descent
			m_uiArrayCnt = m_uiMemoryCnt - 1;

			if (m_vecPages.size() - m_uiPagingIdx == 3)
			{
				// Page Array Descent
				delete[] m_vecPages[m_vecPages.size() - 1];
				m_vecPages.resize(m_vecPages.size() - 1);
			}
		}
		else
		{
			--m_uiArrayCnt;
			if (0 == m_uiInstanceCnt) // Almost False
			{
				bEmpty = true;
			}
		}
	}
public:
	_uint size()
	{
		return m_uiInstanceCnt;
	}
	void clear()
	{
		for (_uint i = 0; i < m_vecPages.size(); ++i)
			delete[] m_vecPages[i];
		m_vecPages.clear();

		m_uiInstanceCnt = 0;
		m_uiArrayCnt = 0;
		m_uiPagingIdx = 0;

		bEmpty = true;
	}

	Iterator Get_Iterartor(void)
	{
		return Iterator(m_uiMemoryCnt, m_uiInstanceCnt);
	}

	T& operator[](Iterator Iter)
	{
		return m_vecPages[Iter.m_uiPageIdx][Iter.m_uiArrayIdx];
	}
	template<typename diffrence_type>
	T& operator[](diffrence_type iIndex)
	{
		if (iIndex > (diffrence_type)m_uiInstanceCnt) _ASSERT(nullptr); // Almost False
		else if (bEmpty == true)  _ASSERT(nullptr); // Almost False

		return m_vecPages[iIndex / m_uiMemoryCnt][iIndex % m_uiMemoryCnt];
	}

private:

	std::vector<T*> m_vecPages;
	_uint m_uiMemoryCnt;
	_uint m_uiInstanceCnt = 0;
	_uint m_uiArrayCnt = 0;
	//
	_uint m_uiPagingIdx = 0;
	bool bEmpty = true;
};

#endif // !PagingArray_h__
