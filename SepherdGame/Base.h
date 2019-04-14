#ifndef Base_h__
#define Base_h__

typedef unsigned long _ulong;

class CBase
{
protected:
	explicit CBase(void);
	explicit CBase(const CBase& Instance);
	virtual ~CBase(void);
public:
	void Add_Ref(void) {
		++m_dwRefCnt;
	}
	virtual _ulong Release(void) {
		return m_dwRefCnt--;
	}
protected:
	_ulong m_dwRefCnt;
};

#endif // !Base_h__
