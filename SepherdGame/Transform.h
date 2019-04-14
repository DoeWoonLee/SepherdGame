#ifndef Transform_h__
#define Transform_h__

#include "Component.h" 
class CTransform : public CComponent
{
	DECLARE_COMPONENT(CTransform)
	DECLARE_CREATOR(CTransform, void)
private:
	explicit CTransform(void);
	virtual ~CTransform(void);
public:
	void Set_Position(float fX, float fY);
	
public:
	virtual void Render(void)override;
	virtual _ulong Release(void)override;
public:
	_vec2 m_vPosition;

};
#endif // !Transform_h__
