#ifndef Frame_h__
#define Frame_h__


class  CFrame
{
private:
	explicit CFrame(void);
	virtual ~CFrame(void);
public:
	bool Get_FrameUpdate(const float& fTimeDelta);
public:
	HRESULT Init_FrameRate(const float& fLimitTime);
public:
	virtual ULONG Release(void);
public:
	static CFrame* Create(const float& fLimitFrame);
private:
	float		m_fFrameRate;	// ���� ���� �ɰ� ���� ���� ����
	float		m_fAccTimes;
};

#endif // Frame_h__
