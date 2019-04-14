#ifndef Timer_h__
#define Timer_h__


class  CTimer
{
private:
	explicit CTimer(void);
	virtual ~CTimer(void);
public:
	float Get_TimeDelta(void){
		return m_fTimeDelta;}
public:
	HRESULT Init_Timer(void);
	void Set_TimeDelta(void);
public:
	static CTimer* Create(void);
private:
	LARGE_INTEGER		m_FrameTime;
	LARGE_INTEGER		m_FixTime;
	LARGE_INTEGER		m_LastTime;
	LARGE_INTEGER		m_CpuTick;
private:
	float				m_fTimeDelta;
public:
	virtual ULONG Release(void);
};


#endif // Timer_h__
