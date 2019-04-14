#ifndef SheepAI_h__
#define SheepAI_h__

#include "Component.h"

class CTransform;
class CSheepAI : public CComponent
{
private:
	explicit CSheepAI(void);
	virtual ~CSheepAI(void);
public:
	virtual _ulong Update(const float& fTimeDelta)override;
	virtual HRESULT Post_Initialize(void)override;
	virtual _ulong Release(void)override;
private:
	CTransform* m_pTransform;
};
#endif // !SheepAI_h__
