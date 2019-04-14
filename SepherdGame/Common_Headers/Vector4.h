#ifndef Vector4_h__
#define Vector4_h__
#pragma  warning (disable : 4275)

#include "Engine_Macro.h"
#include <DirectXMath.h>
using namespace DirectX;

typedef struct tagVector4 : public XMFLOAT4
{
	explicit tagVector4(float fX = 0.f, float fY = 0.f, float fZ = 0.f, float fW = 0.f)
		: XMFLOAT4(fX, fY, fZ, fW) {};
	explicit tagVector4(XMVECTOR vSimd);
	explicit tagVector4(_In_reads_(4) const float *pArray) : 
		XMFLOAT4(pArray) {}
	explicit tagVector4(XMFLOAT3& vVec3)
		: XMFLOAT4(vVec3.x, vVec3.y, vVec3.z, 0.f)	{}
	const tagVector4& TransformNormal(XMMATRIX mat);
	const tagVector4& TransformCoord(XMMATRIX mat);
	void Normalize(void);
	tagVector4& operator= (const tagVector4& Float4) { x = Float4.x; y = Float4.y; z = Float4.z; w = Float4.w; return *this; }

	XMVECTOR ToSIMD(void);
	void LoadSIMD(XMVECTOR vSimd);

	tagVector4 operator+(const tagVector4& AddedVec4);
	tagVector4 operator-(const tagVector4& AddedVec4);

	void operator+=(const tagVector4& AddedVec4);
	void operator*=(const tagVector4& AddedVec4);
	void operator/=(const tagVector4& AddedVec4);
	void operator-=(const tagVector4& AddedVec4);

	void operator*=(const float& Float);
	void operator/=(const float& Float);

	void operator+=(const XMVECTOR& Vector);
	void operator*=(const XMVECTOR& Vector);
	void operator/=(const XMVECTOR& Vector);
	void operator-=(const XMVECTOR& Vector);

	tagVector4 operator*(const float& fFloat);
	friend tagVector4 operator*(const float& fFloat, const tagVector4& rln);
	friend tagVector4 operator/(const float& fFloat, const tagVector4& Vector);
}_vec4;

inline tagVector4 operator*(const float& fFloat, const tagVector4& rln)
{
	return tagVector4(XMVectorScale(XMLoadFloat4(&rln), fFloat));
}
inline tagVector4 operator/(const float& fFloat, const tagVector4& Vector)
{
	return tagVector4(XMVectorSet(fFloat, fFloat, fFloat, fFloat) / XMLoadFloat4(&Vector));
}

#endif // !Vector4_h__
